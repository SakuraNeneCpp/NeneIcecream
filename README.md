# NeneIcecream
PythonのIceCreamのC++版です. printデバッグを支援します.
```cpp
#include <NeneIcecream/NeneIcecream.hpp>

int f(int a, int b){
    return a*b-a-b;
}

int main(){
    int a = 3141;
    int b = 5926;
    ic(a + b);
    ic(f(a, b));
    return 0;
}
```
```
ic [test.cpp:10] a + b = 9067
ic [test.cpp:11] f(a, b) = 18604499
```
(ファイル名) + (行番号) + (式) + (結果) の順に標準出力します.

```cpp
#include <NeneIcecream/NeneIcecream.hpp>

int main(){
    int a = 2;
    int b = 3;
    int c = ic(a + b);
    ic(c);
    return 0;
}
```
```
ic [test.cpp:6] a + b = 5
ic [test.cpp:7] c = 5
```
関数 `ic()` は戻り値として入力された式の結果を返します.