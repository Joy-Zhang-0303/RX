#pragma once
//=========================================================================//
/*!	@file
	@brief	I2C 制御ベースクラス @n
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <cstdint>
#include <functional>
#include "common/format.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  I2C base クラス（iica_io、si2c_io、sci_i2c_io 共通）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct i2c_base {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  送信、受信関数型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef std::function<void(void)> FUNC_TYPE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  速度タイプ型 @n
					※簡易 I2C では誤差が大きい。 @n
					※設定出来ない速度の場合、初期化で失敗する。
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class SPEED : uint32_t {
			_50K      =    50'000,	///<  50K b.p.s.
			STANDARD  =   100'000,	///< 100K b.p.s. (Standard mode)
			_100K     =   100'000,  ///< 100K b.p.s. (Even STANDARD)
			_150K     =   150'000,	///< 150K b.p.s.
			_200K     =   200'000,	///< 200K b.p.s.
			_250K     =   250'000,	///< 250K b.p.s.
			_300K     =   300'000,	///< 300K b.p.s.
			_350K     =   350'000,	///< 350K b.p.s.
			_400K	  =   400'000,	///< 400K b.p.s.
			FAST      =   400'000,	///< 400K b.p.s. 
            FAST_PLUS = 1'000'000   ///<   1M b.p.s.
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  動作モード型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class MODE : uint8_t {
            MASTER,       ///< マスターモード
            SLAVE,        ///< スレーブモード
        };


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ノイズ・フィルター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class NF : uint8_t {
			PH1  = 0b000,	///< フェーズ１段
			PH2  = 0b001,	///< フェーズ２段
			PH3  = 0b010,	///< フェーズ３段
			PH4  = 0b011,	///< フェーズ４段
			NONE = 0b100,	///< 無し
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I2C エラー型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		#ifdef ERROR  // こんな一般的名称を大域変数で定義する大馬鹿避け
		#undef ERROR
		#endif
		enum class ERROR : uint8_t {
			NONE,			///< エラー無し
			BUFF_SIZE,		///< バッファサイズを超えた転送
			START,			///< スタート（初期化）
			BUS_OPEN,		///< バス・オープン
			ADDRESS,		///< アドレス転送
            ACK,        	///< ACK エラー
			SEND_DATA,		///< 送信データ転送
			RECV_DATA,		///< 受信データ転送
			END,			///< 終了
			STOP,			///< ストップ・コンディション
			CLOCK_DIVIDE	///< クロック分周器の制限によるエラー
		};

		ERROR		error_;
	
		i2c_base() noexcept : error_(ERROR::NONE) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  I2C のエラー文字列の取得
			@return エラー文字列
		*/
		//-----------------------------------------------------------------//
		const char* get_error_str() const noexcept
		{
			switch(error_) {
			case ERROR::START:
				return "Start";
			case ERROR::BUS_OPEN:
				return "BUS Open";
			case ERROR::ADDRESS:
				return "Address";
			case ERROR::ACK:
				return "ACK";
			case ERROR::SEND_DATA:
				return "Send data";
			case ERROR::RECV_DATA:
				return "Recv data";
			case ERROR::END:
				return "End";
			case ERROR::STOP:
				return "Stop";
			case ERROR::CLOCK_DIVIDE:
				return "Clock divide";
			default:
				break;
			}
			return "Other";
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	最終エラーの取得
			@return エラー・タイプ
		 */
		//-----------------------------------------------------------------//
		auto get_last_error() const noexcept { return error_; }
    };
}
