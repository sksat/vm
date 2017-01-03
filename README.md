###これはなに？
『自作エミュレータで学ぶx86アーキテクチャ』のエミュレータプログラムを参考にして作っているx86エミュレータです。
本のプログラムではいきなり32bitリアルモードだったものを、起動時には16bitリアルモードにして、QEMUみたいにOSをエミュレーションできるようにしたいと思っています。
自作OSのエミュレーションが目標です(そのため、GUIをつけます)。

###GUI  
GUI部分はOpenGLで作っています(OpenGLでマウスを吸い込む方法が分からないので知ってる人いたら教えてください)。

###ビルド方法  
Debian系のOSであれば、まずinstall.shを起動してfreeglutをインストールしてください。そうすれば、あとかmake runするだけでコンパイル・リンク・実行ができると思います。
g++ 5.4.0で確認しています。

###Information
[自作OS Advent Calendar 2016](http://www.adventar.org/calendars/1666)に[22日目の記事](http://sksat.hatenablog.com/entry/2016/12/21/231342)を書きました。

###動作画面
![HARIBOTE-UI](https://cdn-ak.f.st-hatena.com/images/fotolife/s/sksat/20161221/20161221185532.png)
