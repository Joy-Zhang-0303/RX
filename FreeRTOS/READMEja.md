Renesas RX マイコン FreeRTOS カーネル (V202212.00)
=========

<img src="../docs/Logo_freeRTOS.png" width="50%">

[英語版](README.md)

## 概要

Amazon FreeRTOS カーネルを RX マイコン用にポーティングしたコード、本体、及び修正されたコードです。   
   
オリジナルのコードは、ルネサス社純正コンパイラ CC-RX/GNU-RX やフレームワーク向けになっています。   
その為、それらの関係コードをカーネルソースから追い出して、開発環境の依存度を下げています。   

コードは基本的に gcc 用を使っています。
   
---

## RX220, RX24T のヒープサイズについて

- RX220, RX24T 用のプロジェクトがありますが、RX24T, RX220 の内蔵メモリは少なく、実際に利用する場合は、注意して下さい。
- RX220/Makefile の環境変数の設定で、このサイズを変更出来ます。
- RX24T/Makefile の環境変数の設定で、このサイズを変更出来ます。
　　　
```C
#define configTOTAL_HEAP_SIZE			( ( size_t ) ( RTOS_HEAP_SIZE * 1024 ) )
``` 
   
この設定は、メモリモデル「Source/portable/MemMang/heap_3.c」以外を使った場合に有効です。   
※「heap_3.c」は、malloc、free、を呼び出しています。

---
## プロジェクト・リスト

- [FreeRTOSConfig.h](FreeRTOSConfig.h)
- [main.cpp](main.cpp)
- READMEja.md
- README.md
- [Source (FreeRTOS Kernel sources)](Source)
- [RX220/Makefile](RX220/Makefile)
- [RX62N/Makefile](RX62N/Makefile)
- [RX631/Makefile](RX631/Makefile)
- [RX24T/Makefile](RX24T/Makefile)
- [RX26T/Makefile](RX26T/Makefile)
- [RX64M/Makefile](RX64M/Makefile)
- [RX71M/Makefile](RX71M/Makefile)
- [RX66T/Makefile](RX66T/Makefile)
- [RX65N/Makefile](RX65N/Makefile)
- [RX72N/Makefile](RX72N/Makefile)
- [RX72T/Makefile](RX72T/Makefile)
   
---
## カーネル修正箇所

### port.c

- Source/portable/GCC/RX600/port.c
- Source/portable/GCC/RX600v2/port.c
- Source/portable/GCC/RX700v3_DPFPU/port.c

```C
/* Hardware specifics. */
#if ( configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H == 1 )

    #include "platform.h"

#else /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

///    #include "iodefine.h"

#endif /* configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H */

...

BaseType_t xPortStartScheduler( void )
{
    extern void vApplicationSetupTimerInterrupt( void );

    /* Use pxCurrentTCB just so it does not get optimised away. */
    if( pxCurrentTCB != NULL )
    {
        /* Call an application function to set up the timer that will generate the
         * tick interrupt.  This way the application can decide which peripheral to
         * use.  A demo application is provided to show a suitable example. */
        vApplicationSetupTimerInterrupt();

        /* Enable the software interrupt. */
///        _IEN( _ICU_SWINT ) = 1;

        /* Ensure the software interrupt is clear. */
///        _IR( _ICU_SWINT ) = 0;

        /* Ensure the software interrupt is set to the kernel priority. */
///        _IPR( _ICU_SWINT ) = configKERNEL_INTERRUPT_PRIORITY;

        /* Start the first task. */
        prvStartFirstTask();
    }

    /* Should not get here. */
    return pdFAIL;
}
```

- 「vApplicationSetupTimerInterrupt();」内で、ソフトウェアー割り込みの設定も行います。
- なので、SWINT 関係の設定をコメントアウトしています。
- SWINT 関係のリソースにアクセスしないので、「iodefine.h」のインクルードが必要ありません。
- アプリケーション内で、タイマー関係（CMT）の設定を終えた後に、SWINT 関係の設定を行っています。

```C++
    void vApplicationSetupTimerInterrupt(void)
    {
        uint8_t intr = configKERNEL_INTERRUPT_PRIORITY;
        cmt_.start(configTICK_RATE_HZ, intr, vTickISR);

        device::icu_mgr::set_task(device::ICU::VECTOR::SWINT, vSoftwareInterruptISR);
        device::icu_mgr::set_level(device::ICU::VECTOR::SWINT, configKERNEL_INTERRUPT_PRIORITY);
    }
```

---

### portmacro.h

- Source/portable/GCC/RX600/portmacro.h
- Source/portable/GCC/RX600v2/portmacro.h
- Source/portable/GCC/RX700v3_DPFPU/portmacro.h

```C
#define portYIELD()                         \
    __asm volatile                          \
    (                                       \
        "PUSH.L R10                 \n"     \
        "MOV.L  #0x872E0, R10       \n"     \
        "MOV.B  #0x1, [R10]         \n"     \
        "MOV.L  [R10], R10          \n"     \
        "POP    R10                 \n"     \
    )

```

以前は、「MOV.L  [R10], R10」が奇妙なので、「CMP  [R10].UB, R10」としていました。   
ですが、オリジナルコードを優先して、元に戻してあります。   
※この３２ビット転送は、ハードウェアーマニュアルにある、注意点に違反するので、良くないと思っています。
※RX マイコンの構造的な問題で、そうする事に意味があるのかもしれません。
※以前に質問した事がありますが、何故そうなっているのか、明確な回答は得られませんでした。   
   
---
   
## サンプルプログラム

- サンプルでは、シリアル接続で文字列を出力します。
- マイコンにより異なるチャネルを使っているので、main.cpp の設定を確認して下さい。
- サンプルプログラムでは、３つのタスクを作成、起動します。
- Task1 は 500 ミリ秒毎にカウント値を出力
- Task2 は 100 ミリ秒毎にカウント値を出力
- Task3 は 1000 ミリ秒毎にカウント値を出力

FrrRTOS では、ハードウェアーリソースとして、タイマー割り込み CMT を使います。

このサンプルでは、CMT0 を割り当てています。

```C++
    typedef device::cmt_mgr<device::CMT0> CMT;
    CMT         cmt_;
```

FreeRTOS から呼び出される「vApplicationSetupTimerInterrupt」関数内で、その設定を行っています。   
※1000Hz (1ms) のタイマー割り込みです。   

---

## ライセンス

hirakuni45 RX C++ framework: MIT

FreeRTOS: MIT
