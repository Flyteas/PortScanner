/* TCP端口扫描工具  For Kali */
/* 2015.5.2 */
/* Mail: flyteas@gmail.com */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <time.h>
#include <arpa/inet.h>
#include <unistd.h>

int ScanPorts(char* ScanIP,int ScanStartPort,int ScanEndPort);  //端口扫描
int main(int argc,char** argv)
{
  if(argc != 4) //输出使用方法
  {
    printf("command: ProgramFileName TargetIP BeginPort EndPort \nexample: ./PortScaner 127.0.0.1 1 65535\n");
    return 0;
  }
  if(ScanPorts(argv[1],atoi(argv[2]),atoi(argv[3]))) //调用扫描
  {
      printf("Successful\n");
  }
  return 0;
}

int ScanPorts(char* ScanIP,int ScanStartPort,int ScanEndPort) //端口扫描
{
    int SocketFileObj;
    struct sockaddr_in SockAddr_Obj;
    clock_t ScanStartTime;
    clock_t ScanEndTime;
    double TimeUsed;
    int NowPort;
    if(!( ScanStartPort>=1 && ScanEndPort<=65535 && ScanStartPort<=ScanEndPort))  //判断用户输入端口范围合法性
    {
      printf("Scan port range error!\n");
      return 0;
    }
    printf("Scan Target:%s %d-%d\nScaning:\n",ScanIP,ScanStartPort,ScanEndPort);
    SockAddr_Obj.sin_family=AF_INET;
    SockAddr_Obj.sin_addr.s_addr=inet_addr(ScanIP);
    ScanStartTime=clock();  //扫描开始时间
    for(NowPort = ScanStartPort;NowPort <= ScanEndPort;NowPort++)  //扫描所有端口
    {
      SocketFileObj=socket(AF_INET,SOCK_STREAM,0);
      SockAddr_Obj.sin_port=htons(NowPort);
      if(connect(SocketFileObj,(struct sockaddr *)&SockAddr_Obj,sizeof(SockAddr_Obj)) >=0 )
      {
        printf("%s\t%d\topen\n",ScanIP,NowPort);
        sleep(0.01);
      }
      close(SocketFileObj);
    }
    ScanEndTime = clock(); //扫描结束时间
    TimeUsed = (double)(ScanEndTime-ScanStartTime)/CLOCKS_PER_SEC;
    printf("Time Used:   %lf seconds\n",TimeUsed);  //输出扫描用时
    return 1;
}
