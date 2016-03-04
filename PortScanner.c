/* TCP�˿�ɨ�蹤��  For Kali */
/* 2015.5.2 */
/* Mail: flyteas@gmail.com */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <time.h>
#include <arpa/inet.h>
#include <unistd.h>

int ScanPorts(char* ScanIP,int ScanStartPort,int ScanEndPort);  //�˿�ɨ��
int main(int argc,char** argv)
{
  if(argc != 4) //���ʹ�÷���
  {
    printf("command: ProgramFileName TargetIP BeginPort EndPort \nexample: ./PortScaner 127.0.0.1 1 65535\n");
    return 0;
  }
  if(ScanPorts(argv[1],atoi(argv[2]),atoi(argv[3]))) //����ɨ��
  {
      printf("Successful\n");
  }
  return 0;
}

int ScanPorts(char* ScanIP,int ScanStartPort,int ScanEndPort) //�˿�ɨ��
{
    int SocketFileObj;
    struct sockaddr_in SockAddr_Obj;
    clock_t ScanStartTime;
    clock_t ScanEndTime;
    double TimeUsed;
    int NowPort;
    if(!( ScanStartPort>=1 && ScanEndPort<=65535 && ScanStartPort<=ScanEndPort))  //�ж��û�����˿ڷ�Χ�Ϸ���
    {
      printf("Scan port range error!\n");
      return 0;
    }
    printf("Scan Target:%s %d-%d\nScaning:\n",ScanIP,ScanStartPort,ScanEndPort);
    SockAddr_Obj.sin_family=AF_INET;
    SockAddr_Obj.sin_addr.s_addr=inet_addr(ScanIP);
    ScanStartTime=clock();  //ɨ�迪ʼʱ��
    for(NowPort = ScanStartPort;NowPort <= ScanEndPort;NowPort++)  //ɨ�����ж˿�
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
    ScanEndTime = clock(); //ɨ�����ʱ��
    TimeUsed = (double)(ScanEndTime-ScanStartTime)/CLOCKS_PER_SEC;
    printf("Time Used:   %lf seconds\n",TimeUsed);  //���ɨ����ʱ
    return 1;
}
