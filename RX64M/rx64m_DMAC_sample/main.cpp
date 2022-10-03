//=====================================================================//
/*! @file
    @brief  RX64M DMAC サンプル @n
			・P07(176) ピンに赤色LED（VF:1.9V）を吸い込みで接続する @n
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

#include "common/sci_io.hpp"
#include "common/cmt_mgr.hpp"
#include "common/fixed_fifo.hpp"
#include "common/format.hpp"
#include "common/delay.hpp"
#include "common/command.hpp"

namespace {

	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;

	typedef device::cmt_mgr<device::CMT0> CMT;
	CMT		cmt_;

	typedef utils::fixed_fifo<char, 128> BUFFER;
	typedef device::sci_io<device::SCI1, BUFFER, BUFFER> SCI;
	SCI		sci_;

	utils::command<256> cmd_;

	/// DMAC 終了割り込み
	class dmac_task {
		uint32_t	count_;
	public:
		dmac_task() : count_(0) { }

		void operator() () {
			++count_;
		}

		uint32_t get_count() const { return count_; }
	};


	typedef device::dmac_mgr<device::DMAC0, dmac_task> DMAC_MGR;
	DMAC_MGR	dmac_mgr_;

	char	tmp_[256];
}

extern "C" {

	void sci_putch(char ch)
	{
		sci_.putch(ch);
	}

	char sci_getch(void)
	{
		return sci_.getch();
	}

	void sci_puts(const char *str)
	{
		sci_.puts(str);
	}

	uint16_t sci_length(void)
	{
		return sci_.recv_length();
	}
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	SYSTEM_IO::boost_master_clock();

	{  // タイマー設定（６０Ｈｚ）
		uint8_t int_level = 4;
		cmt_.start(60, int_level);
	}

	{  // SCI 設定
		uint8_t int_level = 2;
		sci_.start(115200, int_level);
	}

	utils::format("RX64M DMAC sample start\n");

	cmd_.set_prompt("# ");

	LED::DIR = 1;

	{
		uint8_t intr_level = 4;
		dmac_mgr_.start(intr_level);
	}

	// copy 機能の確認
	std::memset(tmp_, 0, sizeof(tmp_));
	std::strcpy(tmp_, "ASDFGHJKLQWERTYUZXCVBNMIOP");
	uint32_t copy_len = 16;
	dmac_mgr_.copy(&tmp_[0], &tmp_[128], copy_len, true); 

	utils::format("DMA Copy: %d\n") % copy_len;
	while(dmac_mgr_.probe()) ;

	utils::format("ORG(%d): '%s'\n") % std::strlen(tmp_) % tmp_;
	utils::format("CPY(%d): '%s'\n") % std::strlen(&tmp_[128]) % &tmp_[128];
	utils::format("DMAC task: %d\n") % dmac_mgr_.at_task().get_count();

	dmac_mgr_.fill(&tmp_[0], 4, copy_len, true);

	utils::format("DMA fill: %d\n") % copy_len;
	while(dmac_mgr_.probe()) ;

	utils::format("ORG(%d): '%s'\n") % std::strlen(tmp_) % tmp_;
	utils::format("DMAC task: %d\n") % dmac_mgr_.at_task().get_count();

	uint8_t val = 'Z';
	copy_len = 31;
	dmac_mgr_.memset(&tmp_[0], val, copy_len, true);

	utils::format("DMA memset: %d\n") % copy_len;
	while(dmac_mgr_.probe()) ;

	utils::format("ORG(%d): '%s'\n") % std::strlen(tmp_) % tmp_;
	utils::format("DMAC task: %d\n") % dmac_mgr_.at_task().get_count();


	uint32_t cnt = 0;
	while(1) {
		cmt_.sync();

		if(cmd_.service()) {

		}

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		LED::P = (cnt < 10) ? 0 : 1;
	}
}
