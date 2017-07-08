### 注意
これは古いプロジェクトです。現在は[こちらのリポジトリ](https://github.com/sk2sat/emu)で作業しています。

### これはなに？
『自作エミュレータで学ぶx86アーキテクチャ』のエミュレータプログラムを参考にして作っているx86エミュレータです。
本のプログラムではいきなり32bitリアルモードだったものを、起動時には16bitリアルモードにして、QEMUみたいにOSをエミュレーションできるようにしたいと思っています。
自作OSのエミュレーションが目標です(そのため、GUIをつけます)。

### GUI
GUI部分はOpenGLで作っています(OpenGLでマウスを吸い込む方法が分からないので知ってる人いたら教えてください)。

## Install

```
$ git clone https://github.com/sk2sat/vm.git
$ cd vm
$ ./install.sh
$ make
```

### Information
[自作OS Advent Calendar 2016](http://www.adventar.org/calendars/1666)に[22日目の記事](http://sksat.hatenablog.com/entry/2016/12/21/231342)を書きました。

### 動作画面(これはちょっとズルして作ったもので、はりぼてOSのエミュレーションは行っていません・・・)
![HARIBOTE-UI](https://cdn-ak.f.st-hatena.com/images/fotolife/s/sksat/20161221/20161221185532.png)
