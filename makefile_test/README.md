**初次接触makefile**

**虽然很早以前就知道makefile强大**

**而且也见过Windows程序员与Unix程序员的"圣战"就是以makefile嘲讽的**

**当然这些都是开玩笑的题外话**

****

**真正的意识到makefile的强大,在于其对于大项目的各项Complie能力**

**makefile的高端操作看了一下午,看得快吐了,,,**

**虽然大家可能用IDE的多,Java方向得就不用说了,C/C++可能还会用到一点(前提,你不用Clion,,**

_ _ _

说了那么多废话,进入正题.

进行,多文件编译,多接口,函数库的编译时,makefile是不二选择

我这个是一个简单的,makefile_test

里面包含的是:

> main.c      (主函数)

> result.c    (函数)

> stdio.h    (头文件)

> string.h   (头文件)

> makefile  (重点)

只要使用

```make```

命令,会自行编译的,最后会生成一个名为

string 的可执行文件,可以实现字符串的逆置功能

July 20, 2017 9:39 PM