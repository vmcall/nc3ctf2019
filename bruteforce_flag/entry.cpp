#include <iostream>
#include <string>
#include "intro.hpp"

int main()
{
	std::printf("Calculating #intr0 key.\n");

	auto emulator = intro();
	
	for (size_t i = 0; i < 0x10000; i++)
	{
		const auto calculated_string = emulator.get_string(i);
		const auto hash = emulator.get_hash(calculated_string);
	
		// CHECK IF HASH MATCHES
		if (hash != 0xCD)
			continue;
	
		// CHECK IF VALID FLAG FORMAT
		// PRETTY DIRTY :-/
		bool invalid = false;
		for (size_t i = 0; 
			i < calculated_string.size() - 1; i++)
		{
			const auto character = calculated_string.at(i);
	
			if (character < ' ' ||  // ANY CLEARLY UNPRINTABLE CHARS ?
				static_cast<std::uint8_t>(character) > 0x92) 
			{
				invalid = true;
				break;
			}
		}
	
		if (invalid)
			continue;
	
		std::printf("Match at key %X\n", i);
		std::printf("  NC3{%s}\n", calculated_string.data());
	}
}