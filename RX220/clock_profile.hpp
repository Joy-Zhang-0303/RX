#pragma once
#ifndef NO_CLOCK_PROFILE
//=========================================================================//
/*!	@file
	@brief	RX220 グループ・クロック。プロファイル @n
            クロックジェネレータで発生させる周波数の定義 @n
			RX220 は PLL 回路が無いので、外部にクリスタルを接続する場合、 @n
			最大 20MHz 動作となる。 @n
			外部クロック入力でも最大は 20MHz となる。 @n
			最大速度を出す場合は、HOCO を利用する事になる。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <cstdint>

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  クロック・プロファイル・クラス @n
				・選択出来ない値を指定すると、コンパイルエラーとなる @n
				・詳細はハードウェアーマニュアル参照の事
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class clock_profile {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  発信器タイプ @n
					LOCO は、起動時のモードなので、設定する事はない。
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class OSC_TYPE : uint8_t {
			XTAL,	///< クリスタル接続（1～20MHz）
			CERA,	///< セラミック発振子リード品（16MHz ～ 20MHz）
			EXT,	///< 外部クロック入力（最大 20MHz）
			HOCO,	///< 内蔵高速オンチップオシレーター（BASE: 32MHz, 36.864MHz, 40MHz, 50MHz）
			LOCO,	///< 内蔵低速オンチップオシレーター (125KHz)
		};
#if 1
		static constexpr auto       OSCT        = OSC_TYPE::HOCO;	///< オシレーターの選択

		static constexpr bool		TURN_SBC	= false;			///< サブクロックを利用する場合「true」

#if 1
		static constexpr uint32_t   BASE		= 32'000'000;		///< ベースクロック

		static constexpr uint32_t   ICLK		= 32'000'000;		///< ICLK 周波数（最大32MHz）
		static constexpr uint32_t   PCLKB		= 32'000'000;		///< PCLKB 周波数（最大32MHz）
		static constexpr uint32_t   PCLKD		= 32'000'000;		///< PCLKD 周波数（最大32MHz）
		static constexpr uint32_t   FCLK		= 32'000'000;		///< FCLK 周波数（最大4 ～ 32MHz）
#else
		// オーバークロック
		static constexpr uint32_t   BASE		= 50'000'000;		///< ベースクロック

		static constexpr uint32_t   ICLK		= 50'000'000;		///< ICLK 周波数（最大32MHz）
		static constexpr uint32_t   PCLKB		= 50'000'000;		///< PCLKB 周波数（最大32MHz）
		static constexpr uint32_t   PCLKD		= 50'000'000;		///< PCLKD 周波数（最大32MHz）
		static constexpr uint32_t   FCLK		= 25'000'000;		///< FCLK 周波数（最大4 ～ 32MHz）
#endif

#else
		static constexpr auto       OSCT        = OSC_TYPE::XTAL;	///< オシレーターの選択
		static constexpr uint32_t   BASE		= 20'000'000;		///< ベースクロック

		static constexpr uint32_t   ICLK		= 20'000'000;		///< ICLK 周波数（最大32MHz）
		static constexpr uint32_t   PCLKB		= 20'000'000;		///< PCLKB 周波数（最大32MHz）
		static constexpr uint32_t   PCLKD		= 20'000'000;		///< PCLKD 周波数（最大32MHz）
		static constexpr uint32_t   FCLK		= 20'000'000;		///< FCLK 周波数（最大4 ～ 32MHz）
#endif

		/// ソフトウェアー遅延における定数（1マイクロ秒）
		static void delay_us() noexcept
		{
			// 定数（DELAY_MS）で指定すると、ループ数が少なくインライン展開され、予想した時間にならない為、直で’NOP’数で調整する。
			if(ICLK == 32'000'000) {  // 32MHz 用
				asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
				asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
				asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
				asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
			} else if(ICLK == 20'000'000) { // 20MHz 用
				asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
				asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
				asm("nop"); asm("nop"); asm("nop");
			} else {
				for(volatile uint8_t i = 0; i < (ICLK / 1'000'000) - 10; ++i) {
					asm("nop");
				}
			}
		}
		static constexpr bool		DELAY_T1	= true;			///< 微調整として、「nop」を１つ追加
		static constexpr bool		DELAY_T2	= true;			///< 微調整として、「nop」を１つ追加
	};
}

#endif
