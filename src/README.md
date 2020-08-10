# 二重freeの例

## C
コンパイル方法：
```
gcc -o doublefree doublefree.c && ./doublefree
```
コンパイルは通るが，実行時に次のようなエラーが出る．
```
hello
doublefree(2110,0x104375dc0) malloc: *** error for object 0x7fe494405750: pointer being freed was not allocated
doublefree(2110,0x104375dc0) malloc: *** set a breakpoint in malloc_error_break to debug
zsh: abort      ./doublefree
```

## Rust
ビルド方法：
```
cargo build
```
そもそもビルドの時点でエラーが出る．
```
（略）
error[E0382]: borrow of moved value: `s1`
 --> src/main.rs:6:20
  |
2 |     let mut s1 = String::from("hello");
  |         ------ move occurs because `s1` has type `std::string::String`, which does not implement the `Copy` trait
3 |     
4 |     let _s2 = s1;
  |               -- value moved here
5 | 
6 |     println!("{}", s1);
  |                    ^^ value borrowed here after move

error: aborting due to previous error; 1 warning emitted
（略）
```