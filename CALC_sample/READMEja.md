Renesas RX65N/RX72N Envision Kit 関数電卓サンプル
=========

<img src="../docs/calc_sample.jpg" width="50%">

[English](README.md)
   
## 概要

 - 汎用関数電卓サンプル
 - RX65N/RX72N Envision Kit で利用する場合、GUI での操作が可能
 - グラフィックスを持たないマイコンではコンソールから操作可能
 - gmp mpfr ライブラリを使った、多倍長浮動小数点数
 - 250 桁の内部処理としている（もっと増やす事が出来るが、当面必要十分）
    
## プロジェクト・リスト

 - main.cpp
 - calc_gui.hpp
 - calc_symbol.hpp
 - calc_func.hpp
 - calc_cmd.hpp
 - RX64M/Makefile
 - RX71M/Makefile
 - RX66T/Makefile
 - RX72T/Makefile
 - RX65N/Makefile (LCD GUI 対応)
 - RX72N/Makefile (LCD GUI 対応)
   
### 利用ライブラリ

 - rxlib/lib/libgmp.a
 - rxlib/lib/libmpfr.a

### 主な利用クラス

 - common/basic_arith.hpp
 - common/mpfr.hpp
   
## ビルド方法

 - ターゲットディレクトリーに移動
 - make する。
 - calc_sample.mot ファイルをマイコンに書き込む。

## 利用関数

|関数名|機能|
|---|-------|
|sin|正弦（サイン）|
|cos|余弦（コサイン）|
|tan|正接（タンジェント）|
|asin|逆正弦（アークサイン）|
|acos|逆余弦（アークコサイン）|
|atan|逆正接（アークタンジェント）|
|log|基数 10 の対数関数|
|ln|基数 e の対数関数|
|x^y|X の Y 乗|
|x^-1|X の -1 乗（逆数）|
|x^2|二乗|
|sqrt|平方根（ルート）|
|exp|エクスポーネント１０|
|π|円周率|
|Deg|角度法、360|
|Rad|角度法、2 π|
|Grad|角度法、400|

---

## 今後の予定

- Wifi 対応で、ブラウザで表示と入力が出来るようにする
- 専用プログラム言語で、独自の演算を行う事が出来るようにする
- 関数式を入力してグラフ表示
- 柔軟で制限の無い１６進表示と変換など
- 数式処理（微分や積分など）


## tan(355/266) の解

```
# Rad
# tan(355/226)
 -7497258.185325587112905071831891248663417267943785263161571
```

-----
   
License
----
   
MIT open source license   

libgmp:  GNU LGPL v3 and GNU GPL v2   
libfrmp: GNU LGPL v3   
