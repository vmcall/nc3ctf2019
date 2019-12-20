#pragma once
#include <array>
#include "ppc.hpp"

class intro
{
public:
	intro() = default;
	~intro() = default;

	using flag_t = std::array<char, 0x18>;
	inline flag_t get_string(std::uint32_t key)
	{
		constexpr std::uint8_t encrypted_flag[] = 
		{
			0xE1, 0xC2, 0xED, 0xD2, 
			0x03, 0xDC, 0xF7, 0xBC, 
			0x0F, 0xF0, 0xEB, 0xBC, 
			0xF3, 0xBC, 0x19, 0xBA, 
			0xE5, 0xB8, 0xE5, 0xCC, 
			0xDF, 0xBC, 0xFF };

		auto flag = flag_t();

		// CALCULATE FIRST BYTE
		std::uint32_t first_byte = key;

		first_byte = ppc::__rlwinm(first_byte, 0x18, 0x8, 0x1f);
		first_byte = -first_byte - 31;
		first_byte = ppc::__rlwinm(first_byte, 0x1f, 0x19, 0x1f);

		flag.at(0) = static_cast<std::uint8_t>(first_byte);

		// BYTE SWAP AND TRUNCATE
		auto key_truncated = _byteswap_ushort((std::uint16_t)key);
		auto key_arr = reinterpret_cast<std::uint8_t*>(&key_truncated);

		for (size_t index = 1; index < flag.size() - 1; index++)
		{
			const std::uint32_t key_delta = encrypted_flag[index] - key_arr[index & 1];
			flag.at(index) = ppc::__rlwinm(key_delta, 0x1F, 0x19, 0x1F);
		}

		flag.at(flag.size() - 1) = 0x00;

		return flag;
	}

	// LITERALLY PPC IN C++
	// FUCK ME
	inline std::uint32_t get_hash(flag_t flag)
	{
		const auto flag_integers = reinterpret_cast<std::uint32_t*>(flag.data());

		std::uint32_t r8 = _byteswap_ulong(flag_integers[0]);
		std::uint32_t r6 = _byteswap_ulong(flag_integers[1]);
		std::uint32_t r7 = 0x7f7f7f7f;
		std::uint32_t r0 = 0x80808080;
		std::uint32_t r3 = r6 & r7;
		r6 ^= r8;
		r8 &= r7;
		r8 += r3;
		r6 &= r0;
		r3 = _byteswap_ulong(flag_integers[2]);
		r8 ^= r6;
		r6 = r8 & r7;
		std::uint32_t r10 = 0x18;
		r8 ^= r3;
		r3 &= r7;
		r6 += r3;
		r8 &= r0;
		r3 = _byteswap_ulong(flag_integers[3]);
		r8 ^= r6;
		r6 = r8 & r7;
		r8 ^= r3;
		r3 &= r7;
		r8 &= r0;
		r10 = r6 + r3;
		r6 = _byteswap_ulong(flag_integers[4]);
		r10 ^= r8;
		r3 = r10 & r7;
		r10 ^= r6;
		r6 &= r7;
		r10 &= r0;
		r3 += r6;
		r10 ^= r3;
		r8 = _byteswap_ulong(flag_integers[5]);
		r3 = r10 & r7;
		r7 &= r8;
		r10 ^= r8;
		r7 += r3;
		r10 &= r0;
		r10 ^= r7;
		r8 = ppc::__rlwinm(r10, 16, 16, 31);
		r3 = ppc::__rlwinm(r10, 8, 24, 31);
		r3 += r8;
		r8 = ppc::__rlwinm(r10, 24, 8, 31);
		r3 += r8;
		r3 += r10;
		r3 = ppc::__rlwinm(r3, 0, 24, 31);

		return r3;
	}
};