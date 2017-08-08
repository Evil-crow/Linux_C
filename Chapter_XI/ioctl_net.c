#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

void init_net(void);                              //初始化网络并进行信息的获取

int main(void)
{
    printf("This PC's net information is below:\n");

    init_net( );                                  //调用函数
    return 0;
}

void init_net(void)
{
    unsigned char  eth_name[16];                  //保存接口名称
    unsigned char  mac_addr[6];                   //保存MAC网卡地址
    unsigned int   subnetmask;                    //子网掩码
    unsigned int   ipaddr;
    unsigned int   broadcast_ipaddr;

    int i;
    int sock;                                     //定义变量用来保存创建的套接字
    struct sockaddr_in sin;                       //定义变量储存IP地址
    struct ifreq ifr;                             //定义变量用来保存接口信息

    sock = socket(AF_INET,SOCK_DGRAM,0);          //创建套接字并保存
    if(sock == -1)
        perror("socket");                         //进行出错判断
    strcpy(eth_name,"eth0");                      //保存接口名称信息
    strcpy(ifr.ifr_name,eth_name);
    printf("eth name:\t%s\n",eth_name);           //打印名称

    /*获取并打印网卡地址*/
    if(ioctl(sock,SIOCGIFHWADDR,&ifr) < 0)
    {
        perror("ioctl");                          //获取网卡信息,并进行出错判断
    }
    memcpy(mac_addr,ifr.ifr_hwaddr.sa_data,6);   //拷贝信息
    printf("local: MAC:\t");
    for(i = 0;i < 5;i++)
    {
        printf("%.2x:",mac_addr[i]);
    }
    printf("%.2x\n",mac_addr[i]);

    /*获取并打印IP地址*/
    if(ioctl(sock,SIOCGIFADDR,&ifr) < 0)
        perror("ioctl");                          //获取IP地址.并进行打印
    memcpy(&sin,&ifr.ifr_addr,sizeof(sin));
    ipaddr = sin.sin_addr.s_addr;
    printf("local: eth0:\t%s\n",inet_ntoa(sin.sin_addr));

    /*获取并打印广播地址*/
    if(ioctl(sock,SIOCGIFBRDADDR,&ifr) < 0)
        perror("ioctl");
    memcpy(&sin,&ifr.ifr_addr,sizeof(sin));
    broadcast_ipaddr = sin.sin_addr.s_addr;
    printf("broadcast:\t%s\n",inet_ntoa(sin.sin_addr));

    /*获取并打印子网掩码*/
    if(ioctl(sock,SIOCGIFNETMASK,&ifr) < 0)
        perror("ioctl");
    memcpy(&sin,&ifr.ifr_addr,sizeof(sin));
    subnetmask = sin.sin_addr.s_addr;
    printf("subnetmask:\t%s\n",inet_ntoa(sin.sin_addr));

    close(sock);
}

/*这段代码的主要作用是获取主机的网络信息,
*
* 主要在于对于ioctl函数的使用上,整体思路是使用icontl获取信息,
*
* 其中掺杂了inet系函数的使用,整体结构,只是简单地顺序+选择结构
*
* 其中可能因为主机不匹配,信息不正确,eth0
*
* 所以我的主机信息为空,但是显而易见的是
*
* 此函数的使用是正确的
*/