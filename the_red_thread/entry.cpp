#include <iostream>
#include <windows.h>
#include "red_thread.hpp"

int main(std::int32_t argc, char** argv)
{
	if (argc < 2)
	{
		std::printf("Please input a key\n");
		return 0;
	}

	auto input_string = std::string(argv[1]);
	std::printf("Key (%X): %s\n", input_string.size(), input_string.c_str());

	char input[0x1000] = { 0x00 };
	std::memcpy(input, input_string.c_str(), input_string.size());
	auto calculated_input_array = red_thread::calculate_input(input);

	// auto output = red_thread::calculate_flag(input, calculated_input_array);
	// A STACK OPERATION USED WHEN THE BELOW ASSEMBLY IS COMPILED AS 
	// AN INDEPENDENT FUNCTION MESSES UP THE OUTPUT, SO LET'S INLINE
	// IT FOR NOW :-(

	auto output = calculated_input_array;

	__asm
	{
		vmovdqa xmm2, xmmword ptr xmm2_in // xmm2 = 0x01010101010101010101010101010101
		vmovdqa xmm3, xmmword ptr xmm3_in // xmm3 = 0x0F0B07030E0A06020D0905010C080400
		vmovdqa xmm4, xmmword ptr xmm4_in // xmm4 = 0x02020202020202020202020202020202
	}

	// Ik bent je vader, Matti.
	for (size_t i = 0; i < 0x70; i += 0x10)
	{
		__asm
		{
			mov edx, i								// Fucking MSVC

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

	for (auto character : output)
		std::printf("%c", character);

	return 0;
}