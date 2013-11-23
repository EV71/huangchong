#include "StdAfx.h"
#include "Server.h"


#define THREAD_EXIT_CODE 0xdead

/**
* @Fn: CloseSocket()
* @Brief: closesocket()�İ�������
* @param c: s ���رյ�socket
* @param n: void
* @Return: void
*/


void CloseSocket(SOCKET &s)
{
    CString strTmp;
    if(s != INVALID_SOCKET)
    {
        int iRet=closesocket(s);
        if(iRet !=0)
        {
            strTmp.Format("�ر�socketʧ��,Error Code:%d",WSAGetLastError());
            OutputDebugString(strTmp);
            CPowerInfo::WLog(strTmp);
            return;
        }

        s = INVALID_SOCKET;
    }
}

/*
@Fn: Recvn() 
@Brief: ����len �ֽں�ŷ���
@param c: s socket pBuff: ����buffer ͷָ��,len:���յ��ֽ���
@param n: void
@return :�ɹ� ����0,���� -1
*/


int Recvn(SOCKET s, char * buff, int len)
{
    CString strTmp;
    int nToRead = len;
    int nRecv = 0;

    while (nToRead > 0)
    {
        nRecv = recv(s, buff, nToRead, 0);

        if (nRecv <= 0)
        {
            strTmp.Format("recvn errcode %d \n",WSAGetLastError());
            OutputDebugString(strTmp);
            CPowerInfo::WLog(strTmp);
            return -1;
        }

        buff += nRecv;
        nToRead -= nRecv;
    }

    return 0;
}

Server* Server::m_pServer = NULL;

Server::Server(void):m_sListen(INVALID_SOCKET)
,m_hListenThread(NULL)
,m_bShutDown(FALSE)
,m_pClientCtx(NULL)
,m_hCheckThread(NULL)
{
    Server::m_pServer = this;
    InitializeCriticalSectionAndSpinCount(&m_csList, 4000);
    

}

Server::~Server(void)
{
    DeleteCriticalSection(&m_csList);

}

BOOL Server::StartServer()
{
    CString strTmp;
    m_sListen = socket(AF_INET,SOCK_STREAM,0);
    if(m_sListen == INVALID_SOCKET)
    {
        strTmp.Format("create listen socket fail,with error code:%d",WSAGetLastError());
        OutputDebugString(strTmp);
        CPowerInfo::WLog(strTmp);
        return FALSE;
    }
    
     int iRet = 0;
    
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(CMD_LISTEN_PORT);
    
    BOOL bSet = TRUE;
    iRet = setsockopt(m_sListen,SOL_SOCKET,SO_REUSEADDR,(const char *)&bSet,sizeof(BOOL));
    
    if(iRet != 0)
    {
        strTmp.Format("skid---set listen socket addr reuse fail,with error code:%d",WSAGetLastError());
        OutputDebugString(strTmp);
        CPowerInfo::WLog(strTmp);
        return FALSE;
    }
    
    iRet = bind(m_sListen,(const sockaddr*)&addr,sizeof(addr));
    
    if(iRet != 0)
    {
        strTmp.Format("skid--bind socket fail,with error code:%d",WSAGetLastError());
        OutputDebugString(strTmp);
        CPowerInfo::WLog(strTmp);
        return FALSE;
    }
    
    iRet = listen(m_sListen,SOMAXCONN);
    
    if(iRet != 0)
    {
        strTmp.Format("skid--------listen() fail,with error code:%d",WSAGetLastError());
        OutputDebugString(strTmp);
        CPowerInfo::WLog(strTmp);
        return FALSE;
    }
    
    m_bShutDown = FALSE;
    
    m_hListenThread = CreateThread(NULL,0,ListenThreadFunc,this,0,NULL);
    if(m_hListenThread == NULL)
    {
        strTmp.Format("skid----���������߳�ʧ��,with error code :%d\n",GetLastError());
        OutputDebugString(strTmp);
        CPowerInfo::WLog(strTmp);
        return FALSE;
    }
    m_hCheckThread = CreateThread(NULL,0,CheckThreadFunc,this,0,NULL);
    if(m_hCheckThread == NULL)
    {
        strTmp.Format("skid----�����߳�����ʧ��,with error code��%d\n",GetLastError());
        OutputDebugString(strTmp);
        CPowerInfo::WLog(strTmp);
        return FALSE;
    }
    return TRUE;
    
        
}

DWORD Server::ListenThreadFunc(LPVOID lpParam)
{
    Server *pThis = (Server*)lpParam;
    
    CString strTmp;
    
    while(!pThis->m_bShutDown)
    {
        sockaddr_in addr;
        int addrLen = sizeof(sockaddr_in);
        
        SOCKET sClient = accept(pThis->m_sListen,(sockaddr*)&addr,&addrLen);
        
        if(INVALID_SOCKET == sClient)
        {
            return THREAD_EXIT_CODE;
        }
        
        //2 ���ӳ�ʱ
        int timeout = 2* 1000 * 60;
        
        setsockopt(sClient,SOL_SOCKET,SO_SNDTIMEO,(char*)&timeout,sizeof(timeout));
        setsockopt(sClient,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,sizeof(timeout));
        
        pThis->ProcessAccepted(sClient,addr);
        
        strTmp.Format("skid----���ݴ��������%s����!\n",inet_ntoa(addr.sin_addr));
        OutputDebugString(strTmp);
        CPowerInfo::WLog(strTmp);
        
        
    }
    
    strTmp.Format("skid------�����߳��˳�\n");
    OutputDebugString(strTmp);
    CPowerInfo::WLog(strTmp);
    return THREAD_EXIT_CODE;
    
}


void Server::ProcessAccepted(SOCKET sClient,sockaddr_in &addr)
{
    CString strTmp;
    ClientContext *pClientCtx = new ClientContext;
    
    if(pClientCtx == NULL)
    {
        CloseSocket(sClient);
        strTmp.Format("skid----new ClientContext fail\n");
        OutputDebugString(strTmp);
        CPowerInfo::WLog(strTmp);
        return;
    }
    pClientCtx->pServer = this;
    pClientCtx->sClient = sClient;
    strcpy_s(pClientCtx->chClientIp,16,inet_ntoa(addr.sin_addr));
    
    strTmp.Format("skid----�����µ�����:%s\n",pClientCtx->chClientIp);
    OutputDebugString(strTmp);
    CPowerInfo::WLog(strTmp);
    
    HANDLE hRecvThread = CreateThread(NULL,0,RecvThreadFunc,pClientCtx,CREATE_SUSPENDED,NULL);
    
    if(hRecvThread == NULL)
    {
        CloseSocket(sClient);
        if(pClientCtx)
        {
            delete pClientCtx;
            pClientCtx = NULL;
            strTmp.Format("skid---���������߳�ʧ��\n");
            OutputDebugString(strTmp);
            CPowerInfo::WLog(strTmp);
            return ;
        }
    }
    
    pClientCtx->hRecvThread = hRecvThread;
    AddClientToList(pClientCtx);
    ResumeThread(pClientCtx->hRecvThread);
    
}

void Server::AddClientToList(ClientContext *pClientCtx)
{
    EnterCriticalSection(&m_csList);
    ClientContext * p = m_pClientCtx;
    m_pClientCtx = pClientCtx;
    m_pClientCtx->pNext = p;
    LeaveCriticalSection(&m_csList);
}

void Server::RemoveAllClients()
{
    ClientContext *pHead = m_pClientCtx;
    
    while(pHead)
    {
        CloseSocket(pHead->sClient);
        if(pHead->hRecvThread)
        {
            WaitForSingleObject(pHead->hRecvThread,INFINITE);
            CloseHandle(pHead->hRecvThread);
            pHead->hRecvThread = NULL;
        }
       
        ClientContext *p = pHead;
        pHead = pHead->pNext;
        if(p)
        {
            delete p;
            p = NULL;
        }         
      
    }
    m_pClientCtx = NULL;

}

void Server::StopServer()
{
    CString strTmp;
    CloseSocket(m_sListen);
    strTmp.Format("skid---������ֹͣ��������");
    OutputDebugString(strTmp);
    CPowerInfo::WLog(strTmp);
    
    m_bShutDown = TRUE;
    
    WaitForSingleObject(m_hListenThread,INFINITE);
    if(m_hListenThread)
    {
        CloseHandle(m_hListenThread);
        m_hListenThread = NULL;
    }
    WaitForSingleObject(m_hCheckThread,INFINITE);
    if(m_hCheckThread)
    {
        CloseHandle(m_hCheckThread);
        m_hCheckThread = NULL;
    }
    
    RemoveAllClients();
    
}

DWORD Server::CheckThreadFunc(LPVOID lpParam)
{
    Server *pThis = (Server*)lpParam;
    while(!pThis->m_bShutDown)
    {
        Sleep(200);
        pThis->DoCheck();
    }
    return THREAD_EXIT_CODE;
}

void Server::DoCheck()
{
    EnterCriticalSection(&m_csList);
    ClientContext *pClientCtx = m_pClientCtx;
    DWORD dwExitCode  =0;
    CString strTmp;
    while(pClientCtx)
    {
        if(!GetExitCodeThread(pClientCtx->hRecvThread,&dwExitCode))
        {
            break;
        }
        
        if(dwExitCode == STILL_ACTIVE)
        {
            pClientCtx = pClientCtx->pNext;
        }
        else if(dwExitCode == THREAD_EXIT_CODE)
        {
            CloseSocket(pClientCtx->sClient);
            
            if(pClientCtx->hRecvThread)
            {
                CloseHandle(pClientCtx->hRecvThread);
                pClientCtx->hRecvThread = NULL;
            }
            
            strTmp.Format("���ݴ��������%s�Ͽ�����\n",pClientCtx->chClientIp);
            OutputDebugString(strTmp);
            
            //�Ƴ���Ӧ�ͻ���������
            
            ClientContext *pHead = m_pClientCtx;
            while(pHead)
            {
                if(pHead == pClientCtx)
                {
                    if(m_pClientCtx == pClientCtx)
                    {
                        m_pClientCtx = pClientCtx->pNext;
                    }
                    pClientCtx = pClientCtx->pNext; //�ƶ���ǰָ��
                    
                    if(pHead)
                    {
                        delete pHead;
                        pHead = NULL;
                    }
                    break;
                }
                
                else if(pHead->pNext == pClientCtx)
                {
                    pHead->pNext = pClientCtx->pNext;
                    
                    ClientContext *p =  pClientCtx;
                    pClientCtx = pClientCtx->pNext;
                    if(p)
                    {
                        delete p;
                        p = NULL;
                    }
                    break;
                }
                pHead = pHead->pNext;
            }
        }
        
        else
        {
            strTmp.Format("���������̳߳����˳�,ip:%s,socket��%d",pClientCtx->chClientIp,pClientCtx->sClient);
            OutputDebugString(strTmp);
            break;
        }
    
    }
    
    LeaveCriticalSection(&m_csList);
    

}

DWORD WINAPI Server::RecvThreadFunc(LPVOID lpParam)
{
    CString strTmp;
    ClientContext *pClientCtx = (ClientContext*) lpParam;
    
    if(!pClientCtx)
    {
        return THREAD_EXIT_CODE;
    }
    
    fd_set fdread;
    FD_ZERO(&fdread);
    FD_SET(pClientCtx->sClient,&fdread);
    timeval tv;
    
    tv.tv_sec = 2;
    tv.tv_usec = 0;
    
    int iRet = select(0,&fdread,NULL,NULL,&tv);
    
    if(iRet > 0)
    {
        if(FD_ISSET(pClientCtx->sClient,&fdread))
        {
          //  DWORD dwTime = GetTickCount();
            strTmp.Format("���뺯��:ProcessRecv()\n");
            OutputDebugString(strTmp);
            CPowerInfo::WLog(strTmp);
            for(;;)
            {
                if(pClientCtx->pServer->ProcessRecv(pClientCtx) != 0)
                {
                    break;
                }
            }
            strTmp.Format("�뿪����:ProcessRecv()\n");
            OutputDebugString(strTmp);
            CPowerInfo::WLog(strTmp);
            
        }
    }
    
    else
    {
        strTmp.Format("Recv data timeout\n");
        OutputDebugString(strTmp);
        CPowerInfo::WLog(strTmp);
    }
    return THREAD_EXIT_CODE;
    
}

int Server::ProcessRecv(ClientContext *pClientCtx)
{
    CString strTmp;
    char *pRecvBuffer = pClientCtx->chData;
    
    SOCKET s = pClientCtx->sClient;
    
    int ilen = Recvn(s,pRecvBuffer,SYN_HEADER_SIZE);
    
    if(ilen != 0)
    {
        strTmp.Format("����ͬ��ͷʧ��\n");
        OutputDebugString(strTmp);
        CPowerInfo::WLog(strTmp);
        return -1;
    }
    
    for(int i =0;i <SYN_HEADER_SIZE;i++)
    {
        if(pRecvBuffer[i] != SynInfo[i])
        {
           OutputDebugString("ͬ��ͷ����\n");
           CPowerInfo::WLog("ͬ��ͷ����\n");
            return -1;
        }
    }
    GDW_PacketHead packetHead;
    ilen = Recvn(s,(char*)&packetHead,sizeof(packetHead));
    if(ilen != 0)
    {
        OutputDebugString("���ܰ�ͷ����\n");
        CPowerInfo::WLog("���ܰ�ͷ����\n");
        return -1;
    }

    if(CheckSum((UINT16*)&packetHead,sizeof(packetHead)) != 0)
    {
        OutputDebugString("У���ͷ���ݴ���\n");
        CPowerInfo::WLog("У���ͷ���ݴ���\n");
        return -1;
    }

    DWORD dwDatalen = packetHead.dwDataLen;
    // LOG_INFO("���յ������ݴ�С:%d",dwDatalen);

    if(dwDatalen >MAX_DATA_LEN)
    {
        strTmp.Format("�����������С����datasize:%d\n",dwDatalen);
        OutputDebugString(strTmp);
        CPowerInfo::WLog(strTmp);
        return -1;
    }

    ilen = Recvn(s,pRecvBuffer,dwDatalen);
    if(ilen != 0)
    {
        OutputDebugString("����������ʧ��\n");
        CPowerInfo::WLog("����������ʧ��\n");
        return -1;
    }
    ilen = SendResponse(s,packetHead.wDataType);
    if(ilen != 0)
    {
        OutputDebugString("���ͻ�����ʧ��\n");
        CPowerInfo::WLog("���ͻ�����ʧ��\n");
        return -1;
    }
    return 0;
}

/* ���ͻ����ĺ��� �д�Э�������ʵ�֣�Ŀǰ δʵ��
*/
int Server::SendResponse(SOCKET /*s*/,short /*sType*/)
{
    return 0;
    
}