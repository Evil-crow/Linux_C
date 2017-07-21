##### Linux_C Chapter_VI系统编程

经历了前五章之后,正式开始了Linux下的编程学习

第六章,以文件操作为主,其实质算是**systemcall的引入**

这个目录下,是chmod命令的实现,

书上的代码,其实思路是比较清晰的

```
int main(int argc,char **argv)

int mode = atoi(argv[1]);

char path = argv[2];

chmod(path,mode);

return 0;

```

但是,程序的健壮性.你懂的,

所以,我决定把chmode命令的手动实现,继续下去,会进行Update,但是,现在

我得赶紧赶进度,去写ls的实现代码

不然就要完了....