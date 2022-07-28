#pragma once
//=====================================================================//
/*!	@file
	@brief	８×１６フォント・クラス（東雲１６）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>

namespace graphics {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	フォント・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class font8x16 {
		// 標準的 ASCII フォント
		static constexpr uint8_t bitmap_[] = {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x08,0x08,0x1c,0x1c,0x3e,0x3e,0x7f,0x7f,0x3e,0x3e,0x1c,0x1c,0x08,0x08,0x00,0x00,
    0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0x00,0x00,
    0x00,0x11,0x11,0x11,0x1f,0x11,0x11,0x11,0x00,0x7c,0x10,0x10,0x10,0x10,0x10,0x10,
    0x00,0x1f,0x01,0x01,0x0f,0x01,0x01,0x01,0x7c,0x04,0x04,0x3c,0x04,0x04,0x04,0x00,
    0x00,0x0e,0x11,0x01,0x01,0x01,0x11,0x0e,0x00,0x3c,0x44,0x44,0x3c,0x14,0x24,0x44,
    0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x1f,0x00,0x7c,0x04,0x04,0x3c,0x04,0x04,0x04,
    0x00,0x00,0x1c,0x22,0x22,0x22,0x1c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x08,0x08,0x08,0x08,0x7f,0x08,0x08,0x08,0x08,0x00,0x7f,0x00,0x00,0x00,
    0x00,0x21,0x23,0x25,0x25,0x29,0x29,0x31,0x21,0x04,0x04,0x04,0x04,0x04,0x04,0x7c,
    0x00,0x00,0x11,0x11,0x11,0x0a,0x0a,0x04,0x00,0x7c,0x10,0x10,0x10,0x10,0x10,0x00,
    0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf8,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
    0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0xff,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
    0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
    0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0xf8,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
    0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x0f,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
    0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
    0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
    0x00,0x00,0x40,0x30,0x0c,0x03,0x0c,0x30,0x40,0x00,0x7f,0x00,0x7f,0x00,0x00,0x00,
    0x00,0x00,0x00,0x01,0x06,0x18,0x60,0x18,0x06,0x01,0x7f,0x00,0x7f,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0x24,0x24,0x24,0x24,0x22,0x21,0x00,0x00,
    0x00,0x00,0x00,0x00,0x40,0x20,0x10,0x7f,0x08,0x7f,0x04,0x02,0x01,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x30,0x48,0x08,0x08,0x08,0x3e,0x08,0x08,0x3c,0x4a,0x04,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x18,0x18,0x18,0x18,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x08,0x08,0x00,
    0x36,0x24,0x24,0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x48,0x48,0x48,0xfe,0x24,0x24,0x24,0x24,0x24,0x7f,0x12,0x12,0x12,0x12,0x00,
    0x08,0x1c,0x2a,0x49,0x49,0x09,0x0a,0x1c,0x28,0x48,0x49,0x49,0x2a,0x1c,0x08,0x08,
    0x80,0x86,0x49,0x49,0x29,0x29,0x16,0x10,0x08,0x68,0x94,0x94,0x92,0x92,0x61,0x01,
    0x00,0x1c,0x22,0x22,0x22,0x14,0x08,0x0c,0x52,0x51,0x21,0x21,0x52,0x8c,0x00,0x00,
    0x06,0x04,0x04,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x40,0x20,0x10,0x10,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x10,0x10,0x20,0x40,
    0x00,0x02,0x04,0x08,0x08,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x08,0x08,0x04,0x02,
    0x00,0x00,0x00,0x00,0x08,0x49,0x2a,0x1c,0x2a,0x49,0x08,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x7f,0x08,0x08,0x08,0x08,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x04,0x04,0x02,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x00,0x00,
    0x00,0x40,0x40,0x20,0x20,0x10,0x10,0x08,0x08,0x04,0x04,0x02,0x02,0x01,0x01,0x00,
    0x00,0x18,0x24,0x24,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x24,0x18,0x00,0x00,
    0x00,0x08,0x08,0x0c,0x0a,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,
    0x00,0x18,0x24,0x42,0x42,0x40,0x20,0x10,0x08,0x04,0x04,0x02,0x02,0x7e,0x00,0x00,
    0x00,0x1c,0x22,0x41,0x41,0x40,0x20,0x1c,0x20,0x40,0x41,0x41,0x22,0x1c,0x00,0x00,
    0x00,0x10,0x18,0x18,0x14,0x14,0x12,0x12,0x11,0x7f,0x10,0x10,0x10,0x10,0x00,0x00,
    0x00,0x3e,0x02,0x02,0x02,0x1d,0x23,0x41,0x40,0x40,0x41,0x41,0x22,0x1c,0x00,0x00,
    0x00,0x1c,0x22,0x02,0x01,0x01,0x1d,0x23,0x41,0x41,0x41,0x41,0x22,0x1c,0x00,0x00,
    0x00,0x7f,0x40,0x20,0x20,0x10,0x10,0x10,0x10,0x08,0x08,0x08,0x08,0x08,0x08,0x00,
    0x00,0x1c,0x22,0x41,0x41,0x41,0x22,0x1c,0x22,0x41,0x41,0x41,0x22,0x1c,0x00,0x00,
    0x00,0x1c,0x22,0x41,0x41,0x41,0x41,0x62,0x5c,0x40,0x40,0x41,0x22,0x1c,0x00,0x00,
    0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x18,0x10,0x10,0x08,0x00,0x00,
    0x00,0x00,0x00,0x40,0x20,0x10,0x08,0x04,0x04,0x08,0x10,0x20,0x40,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x7f,0x00,0x00,0x00,0x7f,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x02,0x04,0x08,0x10,0x20,0x20,0x10,0x08,0x04,0x02,0x00,0x00,0x00,
    0x00,0x1c,0x22,0x41,0x41,0x41,0x20,0x10,0x10,0x08,0x08,0x00,0x00,0x08,0x08,0x00,
    0x00,0x18,0x24,0x42,0x5a,0xad,0xa5,0xa5,0xa5,0x59,0x02,0x02,0x44,0x38,0x00,0x00,
    0x00,0x08,0x08,0x14,0x14,0x14,0x22,0x22,0x22,0x3e,0x41,0x41,0x41,0x41,0x00,0x00,
    0x00,0x0f,0x11,0x21,0x21,0x21,0x11,0x1f,0x21,0x41,0x41,0x41,0x21,0x1f,0x00,0x00,
    0x00,0x1c,0x22,0x42,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x42,0x22,0x1c,0x00,0x00,
    0x00,0x0f,0x11,0x21,0x21,0x41,0x41,0x41,0x41,0x41,0x21,0x21,0x11,0x0f,0x00,0x00,
    0x00,0x7f,0x01,0x01,0x01,0x01,0x01,0x3f,0x01,0x01,0x01,0x01,0x01,0x7f,0x00,0x00,
    0x00,0x7f,0x01,0x01,0x01,0x01,0x01,0x3f,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,
    0x00,0x18,0x24,0x42,0x02,0x01,0x01,0x71,0x41,0x41,0x41,0x42,0x66,0x58,0x00,0x00,
    0x00,0x41,0x41,0x41,0x41,0x41,0x41,0x7f,0x41,0x41,0x41,0x41,0x41,0x41,0x00,0x00,
    0x00,0x1c,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x1c,0x00,0x00,
    0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x42,0x24,0x18,0x00,0x00,
    0x00,0x42,0x42,0x22,0x22,0x12,0x1a,0x16,0x26,0x22,0x42,0x42,0x82,0x82,0x00,0x00,
    0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x7e,0x00,0x00,
    0x00,0x41,0x41,0x63,0x63,0x63,0x55,0x55,0x55,0x49,0x49,0x49,0x49,0x41,0x00,0x00,
    0x00,0x41,0x43,0x43,0x45,0x45,0x49,0x49,0x49,0x51,0x51,0x61,0x61,0x41,0x00,0x00,
    0x00,0x1c,0x22,0x22,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x22,0x22,0x1c,0x00,0x00,
    0x00,0x1f,0x21,0x41,0x41,0x41,0x21,0x1f,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,
    0x00,0x1c,0x22,0x22,0x41,0x41,0x41,0x41,0x41,0x41,0x5d,0x22,0x22,0x1c,0x10,0x60,
    0x00,0x1f,0x21,0x41,0x41,0x41,0x21,0x1f,0x11,0x21,0x21,0x21,0x41,0x41,0x00,0x00,
    0x00,0x1c,0x22,0x41,0x41,0x01,0x06,0x18,0x20,0x40,0x41,0x41,0x22,0x1c,0x00,0x00,
    0x00,0x7f,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,
    0x00,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x22,0x1c,0x00,0x00,
    0x00,0x41,0x41,0x41,0x41,0x22,0x22,0x22,0x14,0x14,0x14,0x08,0x08,0x08,0x00,0x00,
    0x00,0x49,0x49,0x49,0x49,0x49,0x49,0x55,0x55,0x36,0x22,0x22,0x22,0x22,0x00,0x00,
    0x00,0x41,0x22,0x22,0x14,0x14,0x08,0x14,0x14,0x14,0x22,0x22,0x41,0x41,0x00,0x00,
    0x00,0x41,0x41,0x22,0x22,0x22,0x14,0x14,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,
    0x00,0x7f,0x20,0x20,0x10,0x10,0x08,0x08,0x04,0x04,0x02,0x02,0x01,0x7f,0x00,0x00,
    0x78,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x78,
    0x00,0x01,0x01,0x02,0x02,0x04,0x04,0x08,0x08,0x10,0x10,0x20,0x20,0x40,0x40,0x00,
    0x0f,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x0f,
    0x08,0x14,0x22,0x41,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0x00,
    0x0c,0x04,0x04,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x3c,0x42,0x40,0x7c,0x42,0x41,0x41,0x61,0x5e,0x00,0x00,
    0x00,0x01,0x01,0x01,0x01,0x1d,0x23,0x41,0x41,0x41,0x41,0x41,0x23,0x1d,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x1c,0x22,0x41,0x01,0x01,0x01,0x41,0x22,0x1c,0x00,0x00,
    0x00,0x40,0x40,0x40,0x40,0x5c,0x62,0x41,0x41,0x41,0x41,0x41,0x62,0x5c,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x1c,0x22,0x41,0x41,0x7f,0x01,0x41,0x22,0x1c,0x00,0x00,
    0x00,0x30,0x08,0x08,0x08,0x3e,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0xdc,0x22,0x22,0x22,0x1c,0x02,0x1e,0x21,0x41,0x41,0x3e,
    0x00,0x02,0x02,0x02,0x02,0x3a,0x46,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x00,0x00,
    0x00,0x08,0x08,0x00,0x00,0x0c,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,
    0x00,0x10,0x10,0x00,0x00,0x18,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x08,0x06,
    0x00,0x02,0x02,0x02,0x02,0x42,0x22,0x12,0x0a,0x16,0x22,0x22,0x42,0x42,0x00,0x00,
    0x00,0x0c,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x37,0x49,0x49,0x49,0x49,0x49,0x49,0x49,0x49,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x3a,0x46,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x1c,0x22,0x41,0x41,0x41,0x41,0x41,0x22,0x1c,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x1d,0x23,0x41,0x41,0x41,0x41,0x23,0x1d,0x01,0x01,0x01,
    0x00,0x00,0x00,0x00,0x00,0x5c,0x62,0x41,0x41,0x41,0x41,0x62,0x5c,0x40,0x40,0x40,
    0x00,0x00,0x00,0x00,0x00,0x34,0x0c,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x3c,0x42,0x02,0x06,0x18,0x60,0x40,0x42,0x3c,0x00,0x00,
    0x00,0x00,0x08,0x08,0x08,0x3e,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x30,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x62,0x5c,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x41,0x41,0x41,0x22,0x22,0x14,0x14,0x08,0x08,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x49,0x49,0x49,0x49,0x55,0x55,0x22,0x22,0x22,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x41,0x22,0x14,0x14,0x08,0x14,0x14,0x22,0x41,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x41,0x41,0x22,0x22,0x14,0x14,0x18,0x08,0x08,0x04,0x03,
    0x00,0x00,0x00,0x00,0x00,0x7e,0x20,0x10,0x10,0x08,0x08,0x04,0x02,0x7f,0x00,0x00,
    0x20,0x10,0x10,0x10,0x10,0x10,0x10,0x08,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x20,
    0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
    0x02,0x04,0x04,0x04,0x04,0x04,0x04,0x08,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x02,
    0x00,0x00,0x00,0x06,0x49,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x0a,0x0a,0x04,0x00,
    0x00,0x7c,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x0f,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x08,0x08,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x7e,0x40,0x40,0x40,0x7e,0x20,0x20,0x10,0x10,0x08,0x04,0x02,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0x24,0x14,0x0c,0x04,0x02,0x02,0x01,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x08,0x0c,0x0a,0x09,0x08,0x08,0x08,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x04,0x3f,0x21,0x21,0x11,0x10,0x08,0x04,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3e,0x08,0x08,0x08,0x08,0x7f,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x7f,0x10,0x18,0x14,0x12,0x11,0x18,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x04,0x7c,0x27,0x14,0x08,0x08,0x08,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1e,0x10,0x10,0x10,0x7f,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3e,0x20,0x20,0x3e,0x20,0x20,0x3e,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x24,0x29,0x2a,0x22,0x10,0x10,0x08,0x04,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x7f,0x40,0x48,0x48,0x28,0x18,0x08,0x08,0x04,0x04,0x02,0x01,0x00,0x00,
    0x00,0x40,0x40,0x20,0x20,0x10,0x18,0x14,0x12,0x11,0x10,0x10,0x10,0x10,0x00,0x00,
    0x00,0x08,0x08,0x08,0x7f,0x41,0x41,0x41,0x41,0x20,0x20,0x10,0x08,0x04,0x00,0x00,
    0x00,0x00,0x00,0x7f,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0xff,0x00,0x00,0x00,
    0x00,0x10,0x10,0x10,0x7f,0x10,0x18,0x18,0x14,0x14,0x12,0x11,0x10,0x18,0x00,0x00,
    0x00,0x08,0x08,0x08,0x7f,0x48,0x48,0x48,0x48,0x44,0x44,0x44,0x42,0x31,0x00,0x00,
    0x00,0x04,0x04,0x3c,0x07,0x08,0x08,0x78,0x0f,0x10,0x10,0x10,0x10,0x10,0x00,0x00,
    0x00,0x04,0x04,0x7c,0x44,0x44,0x42,0x22,0x21,0x10,0x10,0x08,0x04,0x02,0x00,0x00,
    0x00,0x02,0x02,0x02,0x7e,0x12,0x12,0x12,0x11,0x10,0x08,0x08,0x04,0x02,0x00,0x00,
    0x00,0x00,0x00,0x7f,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7f,0x40,0x00,0x00,0x00,
    0x00,0x24,0x24,0x24,0x24,0x7f,0x24,0x24,0x24,0x24,0x20,0x10,0x08,0x04,0x00,0x00,
    0x00,0x00,0x06,0x08,0x00,0x00,0x43,0x44,0x20,0x20,0x10,0x08,0x04,0x03,0x00,0x00,
    0x00,0x00,0x00,0x7f,0x20,0x20,0x20,0x10,0x10,0x18,0x28,0x24,0x42,0x41,0x00,0x00,
    0x00,0x02,0x02,0x02,0x02,0x72,0x4e,0x23,0x12,0x02,0x02,0x02,0x02,0x7c,0x00,0x00,
    0x00,0x00,0x40,0x41,0x42,0x42,0x42,0x20,0x20,0x10,0x10,0x08,0x04,0x02,0x00,0x00,
    0x00,0x04,0x04,0x7c,0x44,0x42,0x46,0x2a,0x31,0x10,0x10,0x08,0x04,0x02,0x00,0x00,
    0x00,0x40,0x30,0x1e,0x10,0x10,0xff,0x10,0x10,0x10,0x10,0x08,0x04,0x02,0x00,0x00,
    0x00,0x00,0x04,0x44,0x49,0x49,0x42,0x22,0x20,0x10,0x10,0x08,0x04,0x02,0x00,0x00,
    0x00,0x00,0x7e,0x00,0x00,0x00,0x7f,0x10,0x10,0x10,0x10,0x08,0x04,0x02,0x00,0x00,
    0x00,0x04,0x04,0x04,0x04,0x0c,0x14,0x24,0x44,0x44,0x04,0x04,0x04,0x04,0x00,0x00,
    0x00,0x10,0x10,0x10,0x7f,0x10,0x10,0x10,0x10,0x10,0x08,0x08,0x04,0x02,0x00,0x00,
    0x00,0x00,0x00,0x3e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
    0x00,0x00,0x7e,0x40,0x40,0x24,0x28,0x10,0x30,0x28,0x48,0x44,0x02,0x01,0x00,0x00,
    0x08,0x08,0x08,0x7f,0x20,0x20,0x10,0x18,0x2c,0x4a,0x49,0x08,0x08,0x08,0x00,0x00,
    0x00,0x40,0x40,0x40,0x20,0x20,0x20,0x10,0x10,0x08,0x04,0x02,0x01,0x00,0x00,0x00,
    0x00,0x00,0x10,0x10,0x24,0x24,0x24,0x44,0x44,0x44,0x44,0x42,0x42,0x41,0x00,0x00,
    0x00,0x02,0x02,0x02,0x42,0x32,0x0e,0x02,0x02,0x02,0x02,0x02,0x02,0x7c,0x00,0x00,
    0x00,0x00,0x7f,0x40,0x40,0x40,0x40,0x20,0x20,0x10,0x10,0x08,0x04,0x02,0x00,0x00,
    0x00,0x00,0x04,0x04,0x0a,0x0a,0x11,0x11,0x20,0x40,0x80,0x00,0x00,0x00,0x00,0x00,
    0x00,0x08,0x08,0x08,0x7f,0x08,0x18,0x2a,0x2a,0x4a,0x4a,0x49,0x08,0x0c,0x00,0x00,
    0x00,0x00,0x00,0x7f,0x40,0x40,0x20,0x20,0x13,0x0c,0x08,0x10,0x20,0x20,0x00,0x00,
    0x00,0x06,0x18,0x20,0x00,0x00,0x06,0x18,0x20,0x00,0x07,0x18,0x20,0x40,0x00,0x00,
    0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x14,0x24,0x24,0x44,0x72,0x4f,0x40,0x00,0x00,
    0x00,0x20,0x20,0x20,0x20,0x26,0x18,0x10,0x30,0x48,0x08,0x04,0x02,0x01,0x00,0x00,
    0x00,0x00,0x7f,0x04,0x04,0x04,0x7f,0x04,0x04,0x04,0x04,0x04,0x78,0x00,0x00,0x00,
    0x00,0x04,0x04,0x04,0xe8,0x9c,0x4b,0x48,0x30,0x10,0x10,0x20,0x20,0x20,0x00,0x00,
    0x00,0x00,0x00,0x00,0x3e,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xff,0x00,0x00,0x00,
    0x00,0x00,0x7f,0x40,0x40,0x40,0x40,0x7e,0x40,0x40,0x40,0x40,0x40,0x7f,0x00,0x00,
    0x00,0x00,0x3e,0x00,0x00,0x00,0x7f,0x40,0x40,0x20,0x20,0x10,0x08,0x06,0x00,0x00,
    0x00,0x20,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x20,0x10,0x10,0x08,0x04,0x00,0x00,
    0x00,0x10,0x10,0x14,0x14,0x14,0x14,0x94,0x94,0x54,0x52,0x32,0x12,0x01,0x00,0x00,
    0x00,0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x42,0x22,0x22,0x12,0x0a,0x06,0x00,0x00,
    0x00,0x00,0x00,0x7f,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x7f,0x41,0x00,0x00,0x00,
    0x00,0x00,0x00,0x7f,0x41,0x41,0x41,0x41,0x40,0x20,0x20,0x10,0x08,0x04,0x00,0x00,
    0x00,0x00,0x00,0x03,0x04,0x40,0x40,0x40,0x20,0x20,0x10,0x08,0x04,0x03,0x00,0x00,
    0x00,0x09,0x12,0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x06,0x09,0x09,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	};

		// プロポーショナル・フォントのテーブル
		// I: -1, i: -2, l: -2, r: -1
		static constexpr int8_t width_tbl_[] = {
			//  !"#$%&'()*+,-./
			8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
			// 0123456789:;<=>?
			8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
			// @ABCDEFGHIJKLMNO
			8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8,
			// PQRTUVWXYZ[\]^_
			8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
			// `abcdefghijklmno
			8, 8, 8, 8, 8, 8, 8, 8, 8, 6, 8, 8, 6, 8, 8, 8,
			// pqrstuvwxyz{|}~
			8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
		};

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	文字の横幅
		*/
		//-----------------------------------------------------------------//
		static constexpr int8_t width = 8;


		//-----------------------------------------------------------------//
		/*!
			@brief	文字の高さ
		*/
		//-----------------------------------------------------------------//
		static constexpr int8_t height = 16;


		//-----------------------------------------------------------------//
		/*!
			@brief	文字のビットマップを取得
			@param[in]	code	文字コード
			@return 文字のビットマップ
		*/
		//-----------------------------------------------------------------//
		static const uint8_t* get(uint8_t code) noexcept {
			return &bitmap_[static_cast<uint16_t>(code) << 4];
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	プロポーショナル・フォント幅を取得
			@param[in]	code	文字コード
			@return 文字幅
		*/
		//-----------------------------------------------------------------//
		static int8_t get_width(uint8_t code) noexcept {
			if(code < 32 || code >= 128) return width;
			else return width_tbl_[code - 32];
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	カーニングを取得
			@param[in]	code	文字コード
			@return 文字幅
		*/
		//-----------------------------------------------------------------//
		static int8_t get_kern(uint8_t code) {
			switch(code) {
			case '!':
			case '|':
			case 'i':
			case 'l':
				return -1;
			}
			return 0;
		}
	};
}
