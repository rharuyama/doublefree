# RustはCの二重free問題にどう対処しているか
## 概要
C(gcc)では二重freeを起こすコード`doublefree.c`でコンパイルが通ってしまい，実行時にエラーが出ます．Rust(cargo)では所有権の概念を導入することで，`main.rs`のようなコードではこの問題が解決されています．

## C
コンパイル方法：
```
gcc -o doublefree doublefree.c 
```
実行方法：
```
./doublefree
```
コンパイルは通るが，実行時に次のようなエラーが出ます．
```
hello
doublefree(2110,0x104375dc0) malloc: *** error for object 0x7fe494405750: pointer being freed was not allocated
doublefree(2110,0x104375dc0) malloc: *** set a breakpoint in malloc_error_break to debug
zsh: abort      ./doublefree
```
このエラーを除去するには，`doublefree.c`の最後の`free(s2)`を削除してください．

## Rust
ビルド方法：
```
cargo build
```
そもそもビルドの時点でエラーが出ます．
```
   Compiling doublefree v0.1.0 (/Users/ryoh/work/projects/doublefree)
error[E0382]: borrow of moved value: `s1`
 --> src/main.rs:7:20
  |
2 |     let s1 = String::from("hello");
  |         -- move occurs because `s1` has type `std::string::String`, which does not implement the `Copy` trait
3 |     
4 |     let _s2 = s1;
  |               -- value moved here
...
7 |     println!("{}", s1);
  |                    ^^ value borrowed here after move

error: aborting due to previous error

For more information about this error, try `rustc --explain E0382`.
error: could not compile `doublefree`.

To learn more, run the command again with --verbose.
```
参考までに，実行方法は：
```
cargo run
```
`String`は`Copy`を実装していない型のため，エラーを除去するにはデータのコピーを明示的にしなければなりません．`main.rs`の`let _s2 = s1`をコメントし，`let _s2 = s1.clone()`のコメントを外してください．
