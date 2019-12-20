#include <iostream>

int main()
{
	constexpr std::uint8_t index_table[] = { 0x4, 0x1, 0x6, 0x7, 0x7, 0xA, 0x8, 0xB, 0xB, 0xF, 0xB, 0x12, 0xF, 0x15 };
	constexpr std::uint8_t xor_table[] = { 0x68, 0x67, 0x74, 0x64, 0x6D, 0x6B, 0x60, 0x75, 0x6F };

	std::printf("Calculating key...\n");
	std::printf("Key: ");

	std::uint32_t unlock_key = 0;
	for (size_t i = 0; i != 14; i++)
	{
		const auto value = xor_table[index_table[i] - i] ^ 1;
		unlock_key = 2 * (unlock_key + value);

		std::printf("%c", value);
	}

	std::printf("\n");
	std::printf("Unlock key: %X\n", unlock_key);
	std::printf("Flag: NC3{");

	// KEY TABLE USED TO ACCESS DATA
	constexpr std::uint8_t key_table[] = { 
		0xE8, 0xBC, 0x65, 0x6A, 0xE3, 0xBC, 0xE6, 
		0x51, 0xE1, 0xA2, 0x5F, 0x46, 0xED, 0xB7, 
		0x5F, 0x41, 0xED, 0xBC, 0x5F, 0x59, 0xED, 
		0xBC, 0x6C, 0x50, 0xEE, 0xA5, 0x6C, 0x50, 
		0xE5, 0xB6, 0x74, 0x50, 0xEA, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00 };

	// SETUP MODIFIED UNLOCK KEY
	std::uint8_t unlock_key_xor = unlock_key >> 16;
	std::uint32_t unlock_key_modif = unlock_key;
	std::uint8_t* unlock_key_raw = reinterpret_cast<std::uint8_t*>(&unlock_key_modif);

	unlock_key_raw[0] = unlock_key_xor;
	unlock_key_raw[2] = (std::uint8_t)unlock_key;
	unlock_key_raw[3] = 0;

	std::uint8_t xor_value = 0x54;


	for (std::size_t count = 0; 
		 count < 0x22; 
		 xor_value = key_table[count], unlock_key_xor = unlock_key_raw[(count + 1) & 3], count++)
	{
		char print_value = 0;

		if (count == 7)
		{
			print_value = '\x91'; //Æ
		}
		else if (count == 12)
		{
			print_value = 's';
		}
		else
		{
			print_value = (char)(xor_value ^ unlock_key_xor);
		}

		std::printf("%c", print_value);
	}

	std::printf("}\n");
}