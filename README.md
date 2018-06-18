zrunscript
==========

W32TeXのrunscrみたいなやつ

## 使い方

例えば、`foo.py`というPythonスクリプトを`foo`というコマンド名で起動させたい場合：

  * 実行パスの通ったディレクトリに`foo.py`を置く。
  * 同じディレクトリに`zrunscript.cfg`を置く。
  * `zrunscript.exe`を`foo.exe`という名前でコピーし、同じディレクトリに置く。

## zrunscript.cfgの書き方

以下の例のように、`.<拡張子> = <起動コマンド名>`の形式の行を書く。先頭が`.`でない行は無視される。

```
.pl   = perl
.py   = python
```

※コマンドにオプションを付けることはできない。

## ライセンス

MITライセンスの下で配布される。  
This software is distributed under the MIT License.

--------------------
Takayuki YATO (aka. "ZR")  
https://github.com/zr-tex8r
