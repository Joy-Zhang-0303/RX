Renesas RX65N/RX72N Envision Kit, RX64M オーディオ・プレイヤー
=========
<img src="../docs/AudioPlayer.jpg" width="80%">

<iframe width="560" height="315" src="https://www.youtube.com/embed/fdcX3VAOFLM" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

[English](README.md)
   
## 概要

 - RX マイコンで実現するオーディオプレイヤー
 - RX65N/RX72N Envision Kit で利用する場合、GUI での操作が可能
 - RX64M/RX72T では、コンソールから操作可能
 - WAV、MP3 形式のオーディオファイルの再生（最大：48KHz、16ビット）
 - ID3 タグ情報、アルバムアートの表示（RX65N/RX72N Envision Kit）
 - 内蔵 D/A の利用（RX64M、RX65N Envision Kit、RX72T）
 - 内蔵デジタルオーディオ出力利用（RX72N Envision Kit)
 - FreeRTOS を使った、マルチタスク処理
 - libmad を利用した、MP3 コーデックのデコード

---

## プロジェクト・リスト

 - main.cpp
 - audio_gui.hpp
 - FreeRTOSConfig.h
 - Makefile
 - sound/sound_out.hpp
 - sound/dac_stream.hpp
 - sound/codec_mgr.hpp"
   
---

## ハードウェアーの準備（RX65N Envision Kit)

<img src="../docs/AudioLead.jpg" width="60%">

 - SD カードインターフェースの準備
 - RX64M、RX72T、RX65N Envision Kit、オーディオの接続（DA0、DA1 から出力、GND レベルは、1.65V）3.3V p-p
 - RX72N Envision Kit (内蔵オーディオ出力を利用)
 - RX65N Envision Kit、P03_JOY_RIGHT_IRQ11 (DA0) Left 出力
 - RX65N Envision Kit、P05_IRQ13_SW (DA1) Right 出力
 - ファミコン（互換）パッドの接続（利用する場合、main.cpp で ENABLE_FAMIPAD を有効にする）
 - RX65N Envision Kit、Pmod (10) PB6_RXD9_PMOD_10 ---> RXD として使用 (コマンドラインインターフェースを利用する場合)
 - RX65N Envision Kit、Pmod ( 9) PB7_TXD9_PMOD_9  ---> TXD として使用 (コマンドラインインターフェースを利用する場合)
 - RXD/TXD は 115200 Baud, 8-bits, 1-Stop, No-Parity 内部動作表示等
 - RX72N Envision Kit (内蔵 USB シリアル利用)

---

## リソースの準備

 - SD カード、ルートに、「NoImage.jpg」ファイルをコピーしておく。
 - SD カードに、「mp3、wav」形式のファイルを書き込む。

---

## ビルド方法

 - ターゲットディレクトリーに移動
 - RX64M、RX65N (Envision Kit)、RX72N (Envision Kit)、RX72T
 - make する。
 - audio_sample.mot ファイルをマイコンに書き込む。

---

## タッチパネルでの操作方法

 - 「Sel」ボタンを押す事でファイラーが起動
 - 上下のドラッグで、ファイルフォーカス
 - 右ドラッグでファイル選択（ディレクトリーの場合、そのディレクトリーへ移動）
 - 左ドラッグで、一つ手前のディレクトリーへ移動
 - 三点タッチで、ファイラークローズ
 - 「<<」ボタンで曲の先頭から再生
 - 「Play/Pause」ボタンで一時停止と再開
 - 「>>」ボタンで次の曲を再生
 - ディレクトリー内では、曲の再生が終了したら、次の曲を再生

<img src="../docs/Filer.jpg" width="80%">
<img src="../docs/AudioPlayer2.JPG" width="80%">
<img src="../docs/AudioPlayer3.JPG" width="80%">

---

## ファミコン・パッドでの操作方法（現在は未サポート）

 - 「SELECT」ボタンで、ファイラーが有効になる。（もう一度押すと無効）
 - 上下ボタンで、ファイルフォーカス
 - 右ボタンで選択（ディレクトリーの場合、そのディレクトリーへ移動）
 - 左ボタンで、一つ手前のディレクトリーへ移動
 - 再生中、右ボタンで次の曲
 - 再生中、左ボタンでリプレイ
 - 再生中、「SELECT」で一時停止
 - 再生中「START」ボタンを押す事で、再生中断
 - 再生中は、曲の再生が終了したら、次の曲を再生

---

## MP3、WAV ファイルの対応状況

 - WAV 形式の場合、最大 48KHz、16 ビット、ステレオのファイルフォーマットまで対応
 - MP3 形式の場合、320Kbps まで対応 (44.1KHz, 48KHz, 16 Bits)
 - WAV 内タグのパース（一部）
 - ID3V2 タグのパース（ID3V1 タグは未対応）

---

## 不具合

- ファイル再生時、全体時間を取得する際、長い時間がかかる場合がある。（調査中）
- アルバムアートの表示が途中で途切れる場合がある。（調査中）
- GUI の描画で、カラーが変わる場合がある。（調査中）

---
   
## License
   
Audio Player: (MIT open source license)    
   
FreeRTOS: (MIT open source license)    
libmad: See libma/libmad/COPYRIGHT (G.P.L. v2)   
libpng: See libpng/libpng/LICENSE  (libpng license)   
zlib: (zlib License)   
picojpeg: 不明
