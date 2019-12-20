#pragma once
#include <cstdint>
// https://gist.github.com/rygorous/1440600

namespace ppc
{
	static inline std::uint32_t ppcmask(std::uint32_t mb, std::uint32_t me)
	{
		std::uint32_t maskmb = ~0u >> mb;
		std::uint32_t maskme = ~0u << (31 - me);
		return (mb <= me) ? maskmb & maskme : maskmb | maskme;
	}

	static inline std::uint32_t rotl32(std::uint32_t x, std::uint32_t amount)
	{
		return (x << amount) | (x >> ((32 - amount) & 31));
	}

	[[gnu::flatten]]
	static inline std::uint32_t __rlwinm(std::uint32_t rs, std::uint32_t sh, std::uint32_t mb, std::uint32_t me)
	{
		return rotl32(rs, sh) & ppcmask(mb, me);
	}
}