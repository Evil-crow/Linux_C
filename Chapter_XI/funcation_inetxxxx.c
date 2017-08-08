/* 此段代码主要是用来进行测试inet系列函数的
 *
 * inet系列函数是用来把正常的字符串形式的IP地址
 *
 * 转换为符合大端字序的网络字节序
 *
 * 其中逻辑方面不是很强,主要是为了进行inet系列函数功能的熟悉
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc,char **argv)
{
    char             buffer[31];          //用来保存输入的IP地址
    int              ret = 0;             //用来保存inet系函数的返回值
    int              host = 0;            //用来保存提取到的主机地址
    int              network = 0;         //用来保存提取到的网络地址
    unsigned int     address = 0;         //保存提取到的地址
    struct in_addr   in;                  //用来保存socket绑定的IP地址

    in.s_addr = 0;                        //进行初始化

    /*输入一个以"."分隔的字符串IP地址*/
    printf("Please input your IP address:");
    fgets(buffer,31,stdin);               //从标准输入获取IP地址
    buffer[31] = '\0';                    //使字符串结束

    /*使用inet_aton函数*/
    if((ret = inet_aton(buffer,&in)) == 0)
    {
        printf("int_aton:\tinvalid address\n");            //提示输入不合法
    }
    else
        printf("inet_aton:\t0x%x\n",in.s_addr);           //输出转换结果

    /*使用inet_addr( )函数*/
    if((address = inet_addr(buffer)) == INADDR_NONE)
        printf("inet_attr:\tinvalid address\n");           //提示输入不合法
    else
        printf("inet_attr:\t0x%lx\n",in.s_addr);           //输出获得的网络字节序二进制IP地址

    /*使用inet_network( )函数*/
    if((address = inet_network(buffer))== -1)
        printf("address:\tinvalid address\n");              //提示输入不合法
    else
        printf("address:\t0x%lx\n",address);                //输出转换结果

    /*使用inet_ntoa( )函数*/
    if(inet_ntoa(in) == NULL)
        printf("inet_ntoa:\tinvalid address\n");
    else
        printf("inet_ntoa:\t%s\n",inet_ntoa(in));

    /*使用inet_lnaof( )与inet_netof(　)函数*/
    host = inet_lnaof(in);                                  //获取主机地址
    network = inet_netof(in);                               //获取网络地址
    printf("inet_lnaof:\t0x%x\n",host);
    printf("inet_netof:\t0x%x\n",network);

    in = inet_makeaddr(network,host);                       //组合主机地址与网络地址
    printf("inet_makeaddr:\t0x%x\n",in.s_addr);               //打印组合好的主机,网络字节序

    return 0;
}
