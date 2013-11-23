/**
@File: Server.h
@ClassName: Server
@Brief: 1���ฺ���������ͨ������������������Ӧ,
        2 ͬʱά�� �ͻ��˵�socket�б�
*/

#include "basicType.h"

#define MAX_DATA_LEN  1*1024
#pragma once

// �ͻ����б�ṹ

class Server;

typedef struct _tagClientContext
{
    _tagClientContext *pNext;
    Server *pServer;
    SOCKET sClient;
    HANDLE hRecvThread;
    char chClientIp[16];
    char chData[MAX_DATA_LEN];

    _tagClientContext():pNext(NULL)
        ,pServer(NULL)
        ,sClient(INVALID_SOCKET)
        ,hRecvThread(NULL)
        {
        ZeroMemory(chClientIp,sizeof(chClientIp));
        ZeroMemory(chData,sizeof(chData));

        }


}ClientContext,*pClientContext;


class Server
{
    public:
       
        
        BOOL StartServer();
        void StopServer();
        
        Server();
        virtual ~Server(void);
        
        
        inline static Server *GetInstance()
        {
            return m_pServer;
        }
        
 private:
    static Server * m_pServer;
  

    SOCKET m_sListen;  
    HANDLE m_hListenThread;

    volatile BOOL m_bShutDown;

    ClientContext *m_pClientCtx;

    CRITICAL_SECTION m_csList;
    HANDLE m_hCheckThread;

    int SendResponse(SOCKET s,short sType);
    int ProcessRecv(ClientContext *pClientCtx); 

    static DWORD WINAPI ListenThreadFunc(LPVOID lpParam);
    static DWORD WINAPI CheckThreadFunc(LPVOID lpParam);
    static DWORD WINAPI RecvThreadFunc(LPVOID lpParam);
    
    void DoCheck();

    void ProcessAccepted(SOCKET sClient,sockaddr_in &addr);
    
    
    
    void AddClientToList(ClientContext *pClientCtx);
    void RemoveAllClients();

        
        
};



  
