# 1 心得
## 1.1 有关`const&`
利用`const TypeName& var`修饰的形参，可以保护其在函数内不会发生改变
##  1.2 有关范围`for`循环
一般最好写成
```
for( auto& x : A ) { ; }
```
以引用的方式，防止没有对`A`进行操作。
对于类而言，要提供begin和end的方法，begin和end就是for循环的范围
## 1.3 行列优先
Eigen默认列优先
# 2 问题
## 2.1 看起来一个inline函数的声明和定义不能在不同cpp里