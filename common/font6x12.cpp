//=====================================================================//
/*!	@file
	@brief	６×１２フォント・クラス
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/font6x12.hpp"

namespace graphics {

	// 標準的 ASCII フォント
	const uint8_t font6x12::bitmap_[] = {
0x7F,0x18,0x86,0x61,0x18,0x86,0x61,0x18,0xFE,
0x95,0x5A,0xA9,0x95,0x5A,0xA9,0x95,0x5A,0xA9,
0x7F,0xD8,0xB6,0x6D,0xDB,0xB6,0x6D,0x1B,0xFE,
0xFF,0x5A,0xAF,0xF5,0x5A,0xAF,0xF5,0x5A,0xFF,
0xC1,0x70,0x3C,0xDF,0xFF,0x7F,0xCF,0x31,0x04,
0x40,0x30,0x1C,0xCF,0xF7,0x1C,0x43,0x00,0x00,
0x00,0x00,0x00,0xDF,0xF7,0x01,0x00,0x00,0x00,
0x40,0x30,0x18,0x0C,0xC6,0x18,0x43,0x00,0x00,
0x7F,0xD0,0x17,0x45,0x51,0x14,0x45,0x51,0x14,
0x3F,0xF0,0x03,0x00,0x00,0x00,0x00,0x00,0x00,
0x3F,0xF8,0xA2,0x28,0x8A,0xA2,0x28,0x8A,0xA2,
0x28,0x8A,0xA2,0x28,0x8A,0xA2,0x28,0x8A,0xA2,
0x28,0x8A,0xA2,0x28,0x8A,0xA2,0xE8,0x0B,0xFE,
0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x0F,0xFC,
0x45,0x51,0x14,0x45,0x51,0x14,0x45,0x1F,0xFC,
0x45,0x51,0x14,0x45,0x51,0x14,0x45,0x51,0x14,
0x00,0xE3,0xB5,0x0C,0xC3,0x30,0x0C,0xC3,0x00,
0x00,0xC3,0x30,0x0C,0xC3,0x30,0xAD,0xC7,0x00,
0x7F,0x10,0x04,0x41,0x10,0x04,0x41,0x10,0xFC,
0x3F,0x08,0x82,0x20,0x08,0x82,0x20,0x08,0xFE,
0x20,0x8C,0xF3,0xFE,0xFF,0xFB,0x3C,0x0E,0x83,
0x00,0x84,0x71,0xDE,0xE7,0x71,0x18,0x04,0x00,
0x1C,0xC7,0x71,0x1C,0xC7,0x71,0x1C,0xC7,0x01,
0x00,0x84,0x31,0xC6,0x60,0x30,0x18,0x04,0x00,
0xBC,0x7F,0x0C,0xC3,0x30,0x0C,0xC3,0x30,0x0C,
0xFF,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xCF,0x87,0xC3,0x30,0x0C,0xC3,0x30,0x0C,0xC3,
0x30,0x0C,0xC3,0x30,0x0C,0xC3,0x30,0x0C,0xC3,
0x30,0x0C,0xC3,0x30,0x0C,0xC3,0x30,0xFE,0x3D,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xFF,
0xC3,0x30,0x0C,0xC3,0x30,0x0C,0xC3,0xE1,0xF3,
0xC3,0x30,0x0C,0xC3,0x30,0x0C,0xC3,0x30,0x0C,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x04,0x41,0x10,0x04,0x01,0x00,0x04,0x01,0x00,
0x8A,0x52,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x8A,0xF2,0x29,0x8A,0xA2,0x28,0x9F,0xA2,0x00,
0x84,0x53,0x55,0x06,0x43,0x55,0x95,0x43,0x00,
0x52,0xD5,0x28,0x04,0xA1,0x58,0x55,0x02,0x00,
0x42,0x51,0x08,0x42,0x55,0x25,0x89,0x05,0x00,
0x06,0x21,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x08,0x41,0x08,0x82,0x20,0x08,0x04,0x81,0x00,
0x02,0x41,0x20,0x08,0x82,0x20,0x04,0x21,0x00,
0x00,0x40,0x54,0x95,0x53,0x55,0x04,0x00,0x00,
0x00,0x40,0x10,0xC4,0x47,0x10,0x04,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x21,0x00,
0x00,0x00,0x00,0xC0,0x03,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x86,0x01,0x00,
0x10,0x84,0x20,0x04,0x41,0x08,0x42,0x10,0x00,
0x80,0x91,0x24,0x49,0x92,0x24,0x89,0x01,0x00,
0x00,0x61,0x10,0x04,0x41,0x10,0x04,0x01,0x00,
0x80,0x91,0x24,0x08,0x21,0x08,0xC1,0x03,0x00,
0x80,0x91,0x24,0x88,0x81,0x24,0x89,0x01,0x00,
0x00,0xC2,0x30,0x8A,0x92,0x7C,0x08,0x02,0x00,
0xC0,0x13,0x04,0x47,0x82,0x24,0x89,0x01,0x00,
0x80,0x91,0x24,0xC1,0x91,0x24,0x89,0x01,0x00,
0xC0,0x83,0x20,0x04,0x41,0x08,0x82,0x00,0x00,
0x80,0x91,0x24,0x89,0x91,0x24,0x89,0x01,0x00,
0x80,0x91,0x24,0x89,0x83,0x24,0x89,0x01,0x00,
0x00,0x00,0x18,0x06,0x00,0x00,0x86,0x01,0x00,
0x00,0x00,0x18,0x06,0x00,0x00,0x06,0x21,0x00,
0x00,0x84,0x10,0x42,0x20,0x10,0x08,0x04,0x00,
0x00,0x00,0x3C,0x00,0xF0,0x00,0x00,0x00,0x00,
0x40,0x20,0x10,0x08,0x84,0x10,0x42,0x00,0x00,
0x80,0x91,0x24,0x08,0x41,0x00,0x04,0x01,0x00,
0x80,0x13,0x5D,0x55,0x75,0x25,0x91,0x03,0x00,
0x00,0x41,0x28,0x8A,0x12,0x7D,0x51,0x04,0x00,
0xC0,0x13,0x45,0xD1,0x13,0x45,0xD1,0x03,0x00,
0x80,0x13,0x45,0x41,0x10,0x44,0x91,0x03,0x00,
0xC0,0x91,0x44,0x51,0x14,0x45,0xC9,0x01,0x00,
0xC0,0x17,0x04,0xC1,0x13,0x04,0xC1,0x07,0x00,
0xC0,0x17,0x04,0xC1,0x13,0x04,0x41,0x00,0x00,
0x80,0x13,0x45,0x41,0x90,0x45,0x99,0x05,0x00,
0x40,0x14,0x45,0xD1,0x17,0x45,0x51,0x04,0x00,
0x80,0x43,0x10,0x04,0x41,0x10,0x84,0x03,0x00,
0x00,0x82,0x20,0x08,0x82,0x24,0x89,0x01,0x00,
0x40,0x92,0x14,0xC5,0x50,0x14,0x49,0x02,0x00,
0x40,0x10,0x04,0x41,0x10,0x04,0xC1,0x07,0x00,
0x40,0x14,0x6D,0xDB,0x56,0x55,0x55,0x05,0x00,
0x40,0x34,0x4D,0x55,0x55,0x65,0x59,0x04,0x00,
0x80,0x13,0x45,0x51,0x14,0x45,0x91,0x03,0x00,
0xC0,0x13,0x45,0xD1,0x13,0x04,0x41,0x00,0x00,
0x80,0x13,0x45,0x51,0x14,0x55,0x89,0x05,0x00,
0xC0,0x13,0x45,0xD1,0x93,0x44,0x51,0x04,0x00,
0x80,0x13,0x45,0x02,0x81,0x44,0x91,0x03,0x00,
0xC0,0x47,0x10,0x04,0x41,0x10,0x04,0x01,0x00,
0x40,0x14,0x45,0x51,0x14,0x45,0x91,0x03,0x00,
0x40,0x14,0x45,0x8A,0xA2,0x10,0x04,0x01,0x00,
0x40,0x55,0x55,0x55,0xA5,0x28,0x8A,0x02,0x00,
0x40,0x14,0x29,0x0A,0xA1,0x28,0x51,0x04,0x00,
0x40,0x14,0x29,0x0A,0x41,0x10,0x04,0x01,0x00,
0xC0,0x07,0x21,0x08,0x21,0x08,0xC1,0x07,0x00,
0x1C,0x41,0x10,0x04,0x41,0x10,0x04,0xC1,0x01,
0x40,0x14,0x29,0xCA,0x47,0x7C,0x04,0x01,0x00,
0x07,0x41,0x10,0x04,0x41,0x10,0x04,0x71,0x00,
0x84,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,
0x02,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x46,0xE2,0x24,0x89,0x05,0x00,
0x40,0x10,0x04,0x4F,0x14,0x45,0xD1,0x03,0x00,
0x00,0x00,0x00,0x4E,0x14,0x04,0x91,0x03,0x00,
0x00,0x04,0x41,0x5E,0x14,0x45,0x91,0x07,0x00,
0x00,0x00,0x00,0x4E,0xF4,0x05,0x91,0x03,0x00,
0x00,0x23,0x08,0x87,0x20,0x08,0x82,0x00,0x00,
0x00,0x00,0x00,0x56,0x62,0x04,0x4E,0xE4,0x00,
0x40,0x10,0x04,0x4F,0x14,0x45,0x51,0x04,0x00,
0x00,0x41,0x00,0x04,0x41,0x10,0x04,0x01,0x00,
0x00,0x41,0x00,0x04,0x41,0x10,0x04,0x31,0x00,
0x40,0x10,0x04,0x51,0x52,0x1C,0x49,0x04,0x00,
0x00,0x41,0x10,0x04,0x41,0x10,0x04,0x01,0x00,
0x00,0x00,0x00,0x4B,0x55,0x55,0x55,0x05,0x00,
0x00,0x00,0x00,0x4F,0x14,0x45,0x51,0x04,0x00,
0x00,0x00,0x00,0x4E,0x14,0x45,0x91,0x03,0x00,
0x00,0x00,0x00,0x4F,0x14,0x45,0x4F,0x10,0x00,
0x00,0x00,0x00,0x5E,0x14,0x45,0x1E,0x04,0x01,
0x00,0x00,0x00,0x9A,0x21,0x08,0x82,0x00,0x00,
0x00,0x00,0x00,0x4E,0x64,0x20,0x91,0x03,0x00,
0x80,0x20,0x08,0x87,0x20,0x08,0x02,0x03,0x00,
0x00,0x00,0x00,0x51,0x14,0x45,0x91,0x07,0x00,
0x00,0x00,0x00,0x51,0xA4,0x28,0x04,0x01,0x00,
0x00,0x00,0x00,0x55,0x55,0x29,0x8A,0x02,0x00,
0x00,0x00,0x00,0x91,0x42,0x10,0x4A,0x04,0x00,
0x00,0x00,0x00,0x51,0xA4,0x28,0x04,0x31,0x00,
0x00,0x00,0x00,0x1F,0x84,0x10,0xC2,0x07,0x00,
0x0C,0x41,0x10,0x84,0x40,0x10,0x04,0xC1,0x00,
0x04,0x41,0x10,0x04,0x41,0x10,0x04,0x41,0x10,
0x06,0x41,0x10,0x04,0x42,0x10,0x04,0x61,0x00,
0x56,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	};

	// プロポーショナル・フォントのテーブル
	// I: -1, i: -2, l: -2, r: -1
	const int8_t font6x12::width_tbl_[] = {
		4, 4, 5, 6, 6, 6, 6, 4, 5, 5, 6, 6, 4, 5, 4, 6,
		5, 4, 5, 5, 6, 5, 5, 5, 5, 5, 4, 4, 6, 5, 6, 5,
		6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 5, 5, 6, 6, 6, 6,
		6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 6,
		4, 6, 6, 6, 6, 6, 5, 6, 6, 3, 4, 6, 3, 6, 6, 6,
		6, 6, 5, 6, 5, 6, 6, 6, 6, 6, 6, 5, 5, 5, 6, 6
	};

}
