#pragma once
//=====================================================================//
/*!	@file
	@brief	遅延ユーティリティー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"
#ifdef RTOS
#include "FreeRTOS.h"
#include "task.h"
#endif

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ソフトウェアー待ち
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct delay {

		//-----------------------------------------------------------------//
		/*!
			@brief  単純ループ
			@param[in]	cnt	ループ回数
		*/
		//-----------------------------------------------------------------//
		static void loop(uint32_t cnt)
		{
			while(cnt > 0) {
				asm("nop");
				--cnt;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  マイクロ秒単位の待ち @n
					あまり正確では無く、速度に関連する設定に依存します。@n
					※キャッシュ有効、最高速度での物理計測によるパラメータ
			@param[in]	us	待ち時間（マイクロ秒）
		*/
		//-----------------------------------------------------------------//
		static void micro_second(uint32_t us)
		{
			while(us > 0) {
#if defined(SIG_RX621) || defined(SIG_RX62N)
				// RXv2 コア（最大 100MHz）
				// ※96MHz 動作、10uS で調整
				for(uint32_t n = 0; n < (device::clock_profile::ICLK / 5333333); ++n) {
					asm("nop");
				}
				asm("nop");
#elif defined(SIG_RX24T)
				// RXv2 コア（最大 80MHz）
				for(uint32_t n = 0; n < (device::clock_profile::ICLK / 4444444); ++n) {
					asm("nop");
				}
#elif defined(SIG_RX66T)
				// RXv3 コア（最大 160MHz）
				for(uint32_t n = 0; n < (device::clock_profile::ICLK / 3346666); ++n) {
					asm("nop");
				}
#elif defined(SIG_RX72T)
				// RXv3 コア（最大 200MHz）
				// 192MHz: 250KHz: (63) 3008239 -> 253.304KHz
				// 192MHz: 250KHz: (64) 3000000 -> 249.357KHz
				for(uint32_t n = 0; n < (device::clock_profile::ICLK / 3000000); ++n) {
					asm("nop");
				}
#elif defined(SIG_RX64M) || defined(SIG_RX63T) || defined(SIG_RX71M)
				// RXv2 コア（最大 100MHz、120MHz、240MHz）
				for(uint32_t n = 0; n < (device::clock_profile::ICLK / 4285714); ++n) {
					asm("nop");
				}
#elif defined(SIG_RX65N)
				// RXv2 コア（最大 120MHz）
				for(uint32_t n = 0; n < (device::clock_profile::ICLK / 4444444); ++n) {
					asm("nop");
				}
#elif defined(SIG_RX72N) || defined(SIG_RX72M)
				// RXv3 コア（最大 240MHz）
				// 240MHz: 78 : 20uS->50.763KHz
				// 240MHz: 79 : 20uS->50.127KHz
				for(uint32_t n = 0; n < (device::clock_profile::ICLK / 3037974); ++n) {
					asm("nop");
				}
#else
#  error "delay.hpp requires tune dummy operations"
#endif
				--us;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ミリ秒単位の待ち
			@param[in]	ms	待ち時間（ミリ秒）
		*/
		//-----------------------------------------------------------------//
		static void milli_second(uint32_t ms)
		{
#ifdef RTOS
			vTaskDelay(ms / portTICK_PERIOD_MS);
#else
			for(uint32_t i = 0; i < ms; ++i) {
				micro_second(1000);
			}
#endif
		}
	};
}
