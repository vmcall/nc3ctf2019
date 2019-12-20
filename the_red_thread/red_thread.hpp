#pragma once
#include "gen_table.hpp"
#include <array>
#include <immintrin.h>
#include <math.h>

alignas(32) const std::uint64_t xmm2_in[] = { 0x0101010101010101, 0x0101010101010101 };
alignas(32) const std::uint64_t xmm3_in[] = { 0x0D0905010C080400, 0x0F0B07030E0A0602 }; // { low, hi } - vpshufb mask
alignas(32) const std::uint64_t xmm4_in[] = { 0x0202020202020202, 0x0202020202020202 };

namespace red_thread
{
	using flag_t = std::array<std::uint8_t, 0x80>;
	__forceinline flag_t calculate_input(std::string_view string)
	{
		auto result = flag_t();

		for (size_t i = 0; i < 0x80; i++)
		{
			// CONVERT TO DOUBLE, CALCULATE SIN AND CONVERT BACK
			const auto index_double = _mm_cvtsi32_sd(__m128d{}, i);
			const auto sin_value = sin(*(double*)&index_double) * 4096.f;
			
			const std::uint32_t section_index = _mm_cvttsd_si32(*(__m128d*)&sin_value);
			
			const std::uint8_t character1 = string[(i + 0) % 0x40];
			const std::uint8_t character2 = string[(i + 1) % 0x40];
			const std::uint8_t character3 = string[(i + 2) % 0x40];
			const std::uint8_t table_val = red_thread::data_section[0x2000 + section_index];
			
			result.at(i) = character1 + character2 + (table_val ^ character3);
		}

		return result;
	}

	__forceinline flag_t calculate_flag(char* input, flag_t output)
	{
		__asm
		{
			vmovdqa xmm2, xmmword ptr xmm2_in // xmm2 = 0x01010101010101010101010101010101
			vmovdqa xmm3, xmmword ptr xmm3_in // xmm3 = 0x0F0B07030E0A06020D0905010C080400
			vmovdqa xmm4, xmmword ptr xmm4_in // xmm4 = 0x02020202020202020202020202020202
		}

		for (size_t i = 0; i < 0x70; i += 0x10)
		{
			__asm
			{
				mov edx, i								

				vmovdqu xmm0, output[edx]				// xmm0 = input_array_copy[edx]
				vpsubd xmm0, xmm0, xmm2					// xmm0 = xmm0 - xmm2
				vpsubw xmm1, xmm0, xmm4					// xmm1 = xmm0 - xmm4
				vmovdqu xmm0, xmmword ptr input			// xmm0 = input_arg
				vpshufb xmm0, xmm0, xmm3				// shuffle xmm0 according to mask xmm3
				vpaddb xmm0, xmm1, xmm0					// xmm0 = xmm1 + xmm0
				vpalignr xmm0, xmm0, xmm0, 0Fh			// xmm0 = "Concatenate xmm0 and xmm0, extract byte aligned result shifted to the right by constant value 0xF" https://www.felixcloutier.com/x86/palignr
				vpshufb xmm0, xmm0, xmm3				// shuffle xmm0 according to mask xmm3
				vmovdqu output[edx], xmm0				// input_array_copy[edx] = xmm0
			}
		}

		return output;
	}
}