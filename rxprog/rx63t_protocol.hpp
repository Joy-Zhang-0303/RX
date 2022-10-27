#pragma once
//=====================================================================//
/*!	@file
	@brief	RX63T プログラミング・プロトコル・クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "rs232c_io.hpp"
#include "rx_protocol.hpp"
#include <vector>

namespace rx63t {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	RX63T プログラミング・プロトコル・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class protocol {

		utils::rs232c_io	rs232c_;

		bool				verbose_ = false;

		bool				connection_ = false;

		rx::protocol::devices		devices_;
		rx::protocol::clock_modes	clock_modes_;
		uint8_t						clock_num_ = 0;
		rx::protocol::multipliers	multipliers_;
		rx::protocol::frequencies	frequencies_;
		rx::protocol::areas			boot_area_;
		rx::protocol::areas			area_;
		rx::protocol::areas			blocks_;
		uint32_t					prog_size_ = 0;
		bool						data_ = false;
		rx::protocol::areas			data_areas_;
		bool						id_protect_ = false;
		bool						pe_turn_on_ = false;
		bool						select_write_area_ = false;

		uint32_t	   				baud_speed_ = 0;
		speed_t						baud_rate_ = B9600;

		uint8_t						last_error_ = 0;

		bool command_(uint8_t cmd) {
			bool f = rs232c_.send(static_cast<char>(cmd));
			rs232c_.sync_send();
			return f;
		}

		bool read_(void* buff, uint32_t len, const timeval& tv) {
			return rs232c_.recv(buff, len, tv) == len;
		}

		bool read_(void* buff, uint32_t len) {
			timeval tv;
			tv.tv_sec  = 5;
			tv.tv_usec = 0;
			return rs232c_.recv(buff, len, tv) == len;
		}

		bool write_(const void* buff, uint32_t len) {
			uint32_t wr = rs232c_.send(buff, len);
			rs232c_.sync_send();
			return wr == len;
		} 

		uint32_t get32_(const uint8_t* p) {
			uint32_t v;
			v = p[0];
			v |= p[1] << 8;
			v |= p[2] << 16;
			v |= p[3] << 24;
			return v;
		}

		uint32_t get16_big_(const uint8_t* p) {
			uint32_t v;
			v = p[1];
			v |= p[0] << 8;
			return v;
		}

		uint32_t get32_big_(const uint8_t* p) {
			uint32_t v;
			v = p[3];
			v |= p[2] << 8;
			v |= p[1] << 16;
			v |= p[0] << 24;
			return v;
		}

		void put16_big_(uint8_t* p, uint32_t val) {
			p[0] = (val >> 8) & 0xff;
			p[1] = val & 0xff;
		}

		void put32_big_(uint8_t* p, uint32_t val) {
			p[0] = (val >> 24) & 0xff;
			p[1] = (val >> 16) & 0xff;
			p[2] = (val >> 8) & 0xff;
			p[3] =  val & 0xff;
		}

		uint8_t sum_(const uint8_t* buff, uint32_t len) {
			uint16_t sum = 0;
			for(uint32_t i = 0; i < len; ++i) {
				sum += *buff++;
			}
			return 0x100 - sum;
		}

		std::string out_section_(uint32_t n, uint32_t num) const {
			return (boost::format("#%02d/%02d: ") % n % num).str();
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		protocol() { }


		//-----------------------------------------------------------------//
		/*!
			@brief	接続
			@param[in]	path	シリアルデバイスパス
			@param[in]	brate	ボーレート
			@param[in]	rx		CPU 設定
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool bind(const std::string& path, uint32_t brate, const rx::protocol::rx_t& rx)
		{
			verbose_ = rx.verbose_;

			if(!start(path)) {
				std::cerr << "Can't open path: '" << path << "'" << std::endl;
				return false;
			}

			// コネクション
			if(!connection()) {
				std::cerr << "Can't connection." << std::endl;
				return false;
			}
			if(verbose_) {
				std::cout << "Connection OK." << std::endl;
			}

			// サポート・デバイス問い合わせ
			{
				if(!inquiry_device()) {
					std::cerr << "Inquiry device error." << std::endl;
					return false;
				}
				auto as = get_device();
				if(verbose_) {
					int i = 0;
					for(auto a : as) {
						++i;
						a.info(out_section_(i, as.size()));
					}
				}
				// デバイス選択
				if(!select_device(as[0].code_)) {
					std::cerr << "Select device error." << std::endl;
					return false;
				}
			}

			// クロック・モード問い合わせ
			{
				if(!inquiry_clock_mode()) {
					std::cerr << "Inquiry clock-mode error." << std::endl;
					return false;
				}
				auto as = get_clock_mode();
				if(verbose_) {
					int i = 0;
					for(auto a : as) {
						++i;
						a.info(out_section_(i, as.size()));
					}				
				}
				// クロック・モード選択
				if(!select_clock_mode(as[0])) {
					std::cerr << "Select clock-mode error." << std::endl;
					return false;
				}
			}

			// 逓倍比問い合わせ
			{
				if(!inquiry_multiplier()) {
					std::cerr << "Inquiry multiplier error." << std::endl;
					return false;
				}
				if(verbose_) {
					auto as = get_multiplier();
					int i = 0;
					for(auto a : as) {
						++i;
						a.info(out_section_(i, as.size()));
					}				
				}
			}

			// 動作周波数問い合わせ
			{
				if(!inquiry_frequency()) {
					std::cerr << "Inquiry frequency error." << std::endl;
					return false;
				}
				if(verbose_) {
					auto as = get_frequency();
					int i = 0;
					for(auto a : as) {
						++i;
						a.info(out_section_(i, as.size()));
					}				
				}
			}

			// ボーレート変更
			{
				if(!change_speed(rx, brate)) {
					std::cerr << "Can't change speed." << std::endl;
					return false;
				}
				if(verbose_) {
					auto sect = out_section_(1, 1);
					std::cout << sect << "Change baud rate: " << std::endl;
				}
			}

			// ユーザー・ブート領域問い合わせ
			{
				if(!inquiry_boot_area()) {
					std::cerr << "Inquiry boot-area error." << std::endl;
					return false;
				}
				if(verbose_) {
					auto as = get_boot_area();
					int i = 0;
					for(auto a : as) {
						++i;
						a.info(out_section_(i, as.size()) + "Boot ");
					}				
				}
			}

			// ユーザー領域問い合わせ
			{
				if(!inquiry_area()) {
					std::cerr << "Inquiry area error." << std::endl;
					return false;
				}
				if(verbose_) {
					auto as = get_area();
					int i = 0;
					for(auto a : as) {
						++i;
						a.info(out_section_(i, as.size()));
					}				
				}
			}

			// ブロック情報問い合わせ
			{
				if(!inquiry_block()) {
					std::cerr << "Inquiry block error." << std::endl;
					return false;
				}
				if(verbose_) {
					auto as = get_block();
					int i = 0;
					for(auto a : as) {
						++i;
						a.info(out_section_(i, as.size()));
					}				
				}
			}

			// プログラム・サイズ問い合わせ
			{
				if(!inquiry_prog_size()) {
					std::cerr << "Inquiry prog-size error." << std::endl;
					return false;
				}
				if(verbose_) {
					auto sz = get_prog_size();
					auto sect = out_section_(1, 1);
					std::cout << sect << (boost::format("Program size: %04X") % sz) << std::endl;
				}
			}

			// データ量域の有無問い合わせ
			{
				if(!inquiry_data()) {
					std::cerr << "Inquiry data error." << std::endl;
					return false;
				}
				if(verbose_) {
					auto sect = out_section_(1, 1);
					std::cout << sect << "Data area: ";
					if(get_data()) {
						std::cout << "true" << std::endl;
					} else {
						std::cout << "false" << std::endl;
					}
				}
			}

			// データ量域情報問い合わせ
			{
				if(!inquiry_data_area()) {
					std::cerr << "Inquiry data-area error." << std::endl;
					return false;
				}
				if(verbose_) {
					auto as = get_data_area();
					int i = 0;
					for(auto a : as) {
						++i;
						a.info(out_section_(i, as.size()) + "Data ");
					}				
				}
			}

			// P/E ステータスに移行
			{
				if(!turn_pe_status()) {
					std::cerr << "P/E status error." << std::endl;
					return false;
				}
				if(verbose_) {
					auto sect = out_section_(1, 1);
					std::cout << sect << "ID Protect: ";
					if(get_protect()) {
						std::cout << "true" << std::endl;
					} else {
						std::cout << "false" << std::endl;
					}					
				}
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@param[in]	path	シリアルデバイスパス
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool start(const std::string& path) {
			if(!rs232c_.open(path, B9600)) {
				return false;
			}
			if(!rs232c_.enable_RTS(false)) {
				return false;
			}
			if(!rs232c_.enable_DTR(false)) {
				return false;
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	コネクションの確立（startが成功したら呼ぶ）
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool connection() {
			bool ok = false;
			for(int i = 0; i < 30; ++i) {
				if(!command_(0x00)) {
					return false;
				}
				timeval tv;
				tv.tv_sec  = 0;
				tv.tv_usec = 10000;  // 10ms
				int ch = rs232c_.recv(tv);
				if(ch == 0x00) {
					ok =  true;
					break;
				}
			}
			if(!ok) return false;

			if(!command_(0x55)) {
				return false;
			}

			timeval tv;
			tv.tv_sec  = 1;
			tv.tv_usec = 0;
			int ch = rs232c_.recv(tv);
			if(ch == 0xff || ch != 0xE6) {
				return false;
			}

			connection_ = true;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	サポートデバイス問い合わせ（connection が成功したら呼ぶ）
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_device() {
			if(!connection_) return false;

			if(!command_(0x20)) {
				return false;
			}
			uint8_t head[3];
			if(!read_(head, 3)) {
				return false;
			}
			if(head[0] != 0x30) {
				return false;
			}
			uint32_t total = head[1];

			uint8_t tmp[256 + 16];
			if(!read_(tmp, total)) {
				return false;
			}

			if(sum_(tmp, total - 1) != tmp[total - 1]) {
				return false;
			}

			rx::protocol::device d;
			d.code_ = get32_(&tmp[1]);
			tmp[tmp[0] + 1] = 0;
			d.name_ = reinterpret_cast<const char*>(&tmp[5]);
			devices_.push_back(d);

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	デバイスを取得
			@return デバイス
		*/
		//-----------------------------------------------------------------//
		const rx::protocol::devices& get_device() const { return devices_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	デバイスを選択
			@param[in]	code	デバイス・コード
		*/
		//-----------------------------------------------------------------//
		bool select_device(uint32_t code) {
			if(!connection_) return false;

			uint8_t tmp[7];
			tmp[0] = 0x10;
			tmp[1] = 4;
			tmp[2] = code & 0xff;
			tmp[3] = (code >> 8) & 0xff;
			tmp[4] = (code >> 16) & 0xff;
			tmp[5] = (code >> 24) & 0xff;
			tmp[6] = sum_(tmp, 6);
			if(!write_(tmp, 7)) {
				return false;
			}
			uint8_t res[1];
			if(!read_(res, 1)) {
				return false;
			}
			if(res[0] == 0x06) {
				return true;
			} else if(res[0] == 0x90) {
				read_(res, 1);
				last_error_ = res[0];
			}
			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	クロック・モード問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_clock_mode() {
			if(!connection_) return false;

			if(!command_(0x21)) {
				return false;
			}

			uint8_t head[2];
			if(!read_(head, 2)) {
				return false;
			}
			if(head[0] != 0x31) {
				return false;
			}
			uint8_t tmp[256];
			if(!read_(tmp, head[1] + 1)) {
				return false;
			}
			for(int i = 0; i < static_cast<int>(head[1]); ++i) {
				rx::protocol::clock_mode cm;
				cm.type_ = tmp[i];
				clock_modes_.push_back(cm);
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	デバイスを取得
			@return デバイス
		*/
		//-----------------------------------------------------------------//
		const rx::protocol::clock_modes& get_clock_mode() const { return clock_modes_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	クロック・モードを選択
			@param[in]	cm	クロック・モード
		*/
		//-----------------------------------------------------------------//
		bool select_clock_mode(const rx::protocol::clock_mode& cm) {
			if(!connection_) return false;

			uint8_t tmp[4];
			tmp[0] = 0x11;
			tmp[1] = 1;
			tmp[2] = cm.type_;
			tmp[3] = sum_(tmp, 3);
			if(!write_(tmp, 4)) {
				return false;
			}
			uint8_t res[1];
			if(!read_(res, 1)) {
				return false;
			}
			if(res[0] == 0x06) {
				return true;
			} else if(res[0] == 0x91) {
				read_(res, 1);
				last_error_ = res[0];
			}
			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	逓倍比問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_multiplier() {
			if(!connection_) return false;

			if(!command_(0x22)) {
				return false;
			}

			uint8_t head[3];
			if(!read_(head, 3)) {
				return false;
			}
			if(head[0] != 0x32) {
				return false;
			}
			uint8_t tmp[256];
			if(!read_(tmp, head[1])) {
				return false;
			}

			clock_num_ = head[2];
			uint8_t i = 0;
			const uint8_t* p = tmp;
			while(i < (head[1] - 1)) {
				auto n = *p++;
				rx::protocol::multiplier mp;
				mp.list_.resize(n);
				for(int j = 0; j < n; ++j) mp.list_[j] = *p++;
				multipliers_.push_back(mp);
				i += n + 1;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	逓倍比を取得
			@return 逓倍比
		*/
		//-----------------------------------------------------------------//
		const rx::protocol::multipliers& get_multiplier() const { return multipliers_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	動作周波数問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_frequency() {
			if(!connection_) return false;

			if(!command_(0x23)) {
				return false;
			}

			uint8_t head[3];
			if(!read_(head, 3)) {
				return false;
			}
			if(head[0] != 0x33) {
				return false;
			}
			uint8_t tmp[256];
			if(!read_(tmp, head[1])) {
				return false;
			}

			auto num = head[2];
			const uint8_t* p = tmp;
			for(uint8_t i = 0; i < num; ++i) {
				rx::protocol::frequency q;
				q.min_ = static_cast<uint16_t>(p[1]) | (static_cast<uint16_t>(p[0]) << 8);
				p += 2;
				q.max_ = static_cast<uint16_t>(p[1]) | (static_cast<uint16_t>(p[0]) << 8);
				p += 2;
//				std::cout << (int)q.min_ << std::endl;
//				std::cout << (int)q.max_ << std::endl;
				frequencies_.push_back(q);
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	動作周波数を取得
			@return 動作周波数
		*/
		//-----------------------------------------------------------------//
		const rx::protocol::frequencies& get_frequency() const { return frequencies_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	新ビットレート選択
			@param[in]	rx		マイコン設定
			@param[in]	spped	シリアル速度
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool change_speed(const rx::protocol::rx_t& rx, uint32_t speed) {
			if(!connection_) return false;

			uint32_t nbr;
			switch(speed) {
			case 19200:
				nbr = 192;
				baud_rate_ = B19200;
				break;
			case 38400:
				nbr = 384;
				baud_rate_ = B38400;
				break;
			case 57600:
				nbr = 576;
				baud_rate_ = B57600;
				break;
			case 115200:
				nbr = 1152;
				baud_rate_ = B115200;
				break;
			case 230400:
				nbr = 2304;
				baud_rate_ = B230400;
				break;
			default:
				return false;
			}
			baud_speed_ = speed; 

			uint8_t cmd[10];
			cmd[0] = 0x3f;
			cmd[1] = 7;
			put16_big_(&cmd[2], nbr);
			put16_big_(&cmd[4], rx.master_);
			cmd[6] = 0x02;
			cmd[7] = rx.iclk_multi_;
			cmd[8] = rx.pclk_multi_;
			cmd[9] = sum_(cmd, 9);
			if(!write_(cmd, 10)) {
				return false;
			}
			uint8_t res[1];
			if(!read_(res, 1)) {
				return false;
			}
			if(res[0] == 0xbf) {
				read_(res, 1);
				last_error_ = res[0];
				return false;
			} else if(res[0] != 0x06) {
				return false;
			}

			usleep(25000);	// 25[ms]

			if(!rs232c_.change_speed(baud_rate_)) {
				return false;
			}

			if(!command_(0x06)) {
				return false;
			}
			if(!read_(res, 1)) {
				return false;
			}
			if(res[0] != 0x06) {
				return false;
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ユーザー・ブート領域問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_boot_area() {
			if(!connection_) return false;

			if(!command_(0x24)) {
				return false;
			}

			uint8_t head[3];
			if(!read_(head, 3)) {
				return false;
			}
			if(head[0] != 0x34) {
				return false;
			}
			uint8_t tmp[256];
			if(!read_(tmp, head[1])) {
				return false;
			}

			auto num = head[2];
			const uint8_t* p = tmp;
			for(uint8_t i = 0; i < num; ++i) {
				rx::protocol::area a;
				a.org_ = get32_big_(p);
				p += 4;
				a.end_ = get32_big_(p);
				p += 4;
				boot_area_.push_back(a);
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ユーザー・ブート領域を取得
			@return ユーザー・ブート領域
		*/
		//-----------------------------------------------------------------//
		const rx::protocol::areas& get_boot_area() const { return boot_area_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ユーザー領域問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_area() {
			if(!connection_) return false;

			if(!command_(0x25)) {
				return false;
			}

			uint8_t head[3];
			if(!read_(head, 3)) {
				return false;
			}
			if(head[0] != 0x35) {
				return false;
			}
			uint8_t tmp[256];
			if(!read_(tmp, head[1])) {
				return false;
			}

			auto num = head[2];
			const uint8_t* p = tmp;
			for(uint8_t i = 0; i < num; ++i) {
				rx::protocol::area a;
				a.org_ = get32_big_(p);
				p += 4;
				a.end_ = get32_big_(p);
				p += 4;
				area_.push_back(a);
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ユーザー領域を取得
			@return ユーザー領域
		*/
		//-----------------------------------------------------------------//
		const rx::protocol::areas& get_area() const { return area_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ブロック情報問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_block() {
			if(!connection_) return false;

			if(!command_(0x26)) {
				return false;
			}

			uint8_t head[4];
			if(!read_(head, 4)) {
				return false;
			}
			if(head[0] != 0x36) {
				return false;
			}

			auto num = head[3];
			for(uint8_t i = 0; i < num; ++i) {
				uint8_t tmp[8];
				if(!read_(tmp, 8)) {
					return false;
				}
				rx::protocol::area a;
				a.org_ = get32_big_(&tmp[0]);
				a.end_ = get32_big_(&tmp[4]);
				blocks_.push_back(a);			
			}

			uint8_t sum[1];
			if(!read_(sum, 1)) {
				return false;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ブロック情報を取得
			@return ブロック情報
		*/
		//-----------------------------------------------------------------//
		const rx::protocol::areas& get_block() const { return blocks_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	プログラム・サイズ問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_prog_size() {
			if(!connection_) return false;

			if(!command_(0x27)) {
				return false;
			}

			uint8_t head[5];
			if(!read_(head, 5)) {
				return false;
			}
			if(head[0] != 0x37) {
				return false;
			}

			prog_size_ = get16_big_(&head[2]);

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	プログラム・サイズを取得
			@return プログラム・サイズ
		*/
		//-----------------------------------------------------------------//
		uint32_t get_prog_size() const { return prog_size_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	データ量域有無問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_data() {
			if(!connection_) return false;

			if(!command_(0x2a)) {
				return false;
			}

			uint8_t head[4];
			if(!read_(head, 4)) {
				return false;
			}
			if(head[0] != 0x3a) {
				return false;
			}

			data_ = head[2] == 0x21;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	データ量域有無取得
			@return データ量域有無「true」ならデータ量域（有）
		*/
		//-----------------------------------------------------------------//
		bool get_data() const { return data_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	データ量域情報問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_data_area() {
			if(!connection_) return false;

			if(!command_(0x2b)) {
				return false;
			}

			uint8_t head[3];
			if(!read_(head, 3)) {
				return false;
			}
			if(head[0] != 0x3b) {
				return false;
			}

			auto num = head[2];
			for(uint8_t i = 0; i < num; ++i) {
				uint8_t tmp[8];
				if(!read_(tmp, 8)) {
					return false;
				}
				rx::protocol::area a;
				a.org_ = get32_big_(&tmp[0]);
				a.end_ = get32_big_(&tmp[4]);
				data_areas_.push_back(a);			
			}

			uint8_t sum[1];
			if(!read_(sum, 1)) {
				return false;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	データ量域情報を取得
			@return データ量域情報
		*/
		//-----------------------------------------------------------------//
		const rx::protocol::areas& get_data_area() const { return data_areas_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	P/E ステータス遷移
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool turn_pe_status() {
			if(!connection_) return false;

			if(!command_(0x40)) {
				return false;
			}

			timeval tv;
			tv.tv_sec  = 10;
			tv.tv_usec = 0;
			uint8_t head[1];
			if(!read_(head, 1, tv)) {
				return false;
			}
			if(head[0] == 0x26) {
				id_protect_ = false;
///				std::cout << "Return: 0x26" << std::endl;
			} else if(head[0] == 0x16) {
				id_protect_ = true;
///				std::cout << "Return: 0x16" << std::endl;
			} else if(head[0] == 0xc0) {
				if(!read_(head, 1, tv)) {
					return false;
				}
				last_error_ = head[0];
				return false;
			}

			pe_turn_on_ = true;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	プロテクト状態を取得
			@return プロテクト状態
		*/
		//-----------------------------------------------------------------//
		bool get_protect() const { return id_protect_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	イレース・ページ
			@param[in]	address	アドレス
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool erase_page(uint32_t address) {
#if 0
			if(!connection_) return false;
			if(!verification_) return false;

			char buff[4];
			buff[0] = 0x20;
			buff[1] = (address >> 8) & 0xff;
			buff[2] = (address >> 16) & 0xff;
			buff[3] = 0xD0;
			if(rs232c_.send(buff, 4) != 4) {
				return false;
			}
			rs232c_.sync_send();

			status st;
			if(!get_status(st)) {
				return false;
			}
			if(st.get_SR5() != 0) {
				return false;
			}

			return clear_status();
#endif
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	リード・ページ
			@param[in]	adr	アドレス
			@param[out]	dst	リード・データ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool read_page(uint32_t adr, uint8_t* dst) {
			if(!connection_) return false;
			if(!pe_turn_on_) return false;

			uint8_t cmd[12];
			cmd[0] = 0x52;
			cmd[1] = 9;
			cmd[2] = 0x01;  // user-area, data-area
			put32_big_(&cmd[3], adr);
			put32_big_(&cmd[7], 256);
			cmd[11] = sum_(cmd, 11);
			if(!write_(cmd, 12)) {
				return false;
			}

			{
				timeval tv;
				tv.tv_sec  = 5;
				tv.tv_usec = 0;
				uint8_t head[5];
				if(!read_(head, 5, tv)) {
					return false;
				}
				if(head[0] != 0x52) {
					return false;
				}
				auto rs = get32_big_(&head[1]);
				/// std::cout << "Read size: " << rs << std::endl;
				tv.tv_sec  = 5;
				tv.tv_usec = 0;
				if(!read_(dst, rs, tv)) {
//					std::cout << "Read error #0" << std::endl;
					return false;
				}
			}
			{
				timeval tv;
				tv.tv_sec  = 5;
				tv.tv_usec = 0;
				uint8_t sum[1];
				if(!read_(sum, 1, tv)) {
//					std::cout << "Read error #1" << std::endl;
					return false;
				}
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ユーザー・ブート／データ領域書き込み選択
			@param[in]	data	「true」ならデータ領域
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool select_write_area(bool data) {
			if(!connection_) return false;
			if(!pe_turn_on_) return false;

			// 領域選択
			uint8_t cmd;
			if(data) cmd = 0x43;
			else cmd = 0x42;
			if(!command_(cmd)) {
				return false;
			}

			timeval tv;
			tv.tv_sec  = 10;
			tv.tv_usec = 0;
			uint8_t head[1];
			if(!read_(head, 1, tv)) {
				return false;
			}
			if(head[0] != 0x06) {
				return false;
			}

			select_write_area_ = true;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ライト・ページ（２５６バイト）
			@param[in]	address	アドレス
			@param[in]	src	ライト・データ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool write_page(uint32_t address, const uint8_t* src) {
			if(!connection_) return false;
			if(!pe_turn_on_) return false;
			if(!select_write_area_) return false;

			uint8_t cmd[5 + 256 + 1];
			cmd[0] = 0x50;
///			std::cout << boost::format("Address: %08X") % address << std::endl;			
			if(address != 0xffffffff) {
				put32_big_(&cmd[1], address);
				std::memcpy(&cmd[5], src, 256);
				cmd[5 + 256] = sum_(cmd, 5 + 256);

				if(!write_(cmd, 5)) {
					select_write_area_ = false;
					return false;
				}
				for(uint32_t i = 0; i < 16; ++i) {
					if(!write_(&cmd[5 + i * 16], 16)) {
						select_write_area_ = false;
						return false;
					}
				}
				if(!write_(&cmd[5 + 256], 1)) {  // SUM
				  	select_write_area_ = false;
					return false;
				}
			} else {
				put32_big_(&cmd[1], address);
				select_write_area_ = false;
				cmd[5] = sum_(cmd, 5);
				if(!write_(cmd, 6)) {
					return false;
				}
			}

			// レスポンス
			timeval tv;
			tv.tv_sec  = 10;
			tv.tv_usec = 0;
			uint8_t head[1];
			if(!read_(head, 1, tv)) {
				select_write_area_ = false;
				return false;
			}
			if(head[0] != 0x06) {
				std::cout << "Respons error" << std::endl;
				select_write_area_ = false;
				if(head[0] != 0xd0) {
					return false;
				}
				if(!read_(head, 1, tv)) {
					return false;
				}
				last_error_ = head[0];
///				std::cout << boost::format("Write error code: %02X") % static_cast<uint32_t>(head[0]) << std::endl;
				return false;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	終了
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool end() {
			connection_ = false;
			pe_turn_on_ = false;
			select_write_area_ = false;
			return rs232c_.close();
		}

	};

}
