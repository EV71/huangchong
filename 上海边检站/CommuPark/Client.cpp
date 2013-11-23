#include "StdAfx.h"
#include "Client.h"
#include "windows.h"

CString g_strErr;
extern CRITICAL_SECTION g_csUCI;
extern CRITICAL_SECTION g_csSend;
extern CRITICAL_SECTION g_csMysql;
UINT16 CheckSum(UINT16* pBuffer, UINT32 nSize)
{
    UINT32 nChecksum = 0;

    while (nSize > 1)
    {
        nChecksum += *pBuffer++;
        nSize -= sizeof(UINT16);
    }

    if (nSize)
    {
        nChecksum += *(UINT8*)pBuffer;
    }

    nChecksum = (nChecksum >> 16) + (nChecksum & 0xffff);
    nChecksum += (nChecksum >>16);

    UINT16 u = (UINT16)(~nChecksum);

    return u;
}


CClient::CClient(CConfig &config):m_DataConvert(config)
{
    m_strPort = config.ReadConfig("Center","CenterPort","8682");
    m_strServerIP = config.ReadConfig("Center","CenterIp","10.100.40.130");
    m_nSendInterval = config.ReadConfig("Center","SendInterval",500); // ���ͼ��
	m_nSendUCIInterval = config.ReadConfig("Center","SendUCIInterval",1000); // ���ͼ��
    m_nUploadMode = config.ReadConfig("Center","UploadMode",0); //��ʷ��������
    
    m_bConnect = FALSE;
    
    InitializeCriticalSection(&m_csData);
    
}

CClient::~CClient(void)
{
     m_bConnect = FALSE;
    DeleteCriticalSection(&m_csData);
}

BOOL CClient::DoStart()
{
    m_hConnectEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
    m_hConnectThread = CreateThread(NULL,0,ReConnectThread,this,0,NULL);
    
    m_hSendEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
    m_hSendThread = CreateThread(NULL,0,SendThread,this,0,NULL);

    m_hSendUCIEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
    m_hSendUCIThread = CreateThread(NULL,0,SendUCIThread,this,0,NULL);
  
    
    return TRUE;
    
}

BOOL CClient::DoStop()
{
    m_tcpSocket.DisConnect();
    SetEvent(m_hConnectEvent);
    WaitForSingleObject(m_hConnectThread,INFINITE);
    if(m_hConnectThread)
    {
        CloseHandle(m_hConnectThread);
        m_hConnectThread = NULL;
    }
    
    SetEvent(m_hSendEvent);
    WaitForSingleObject(m_hSendThread,INFINITE);
    if(m_hSendThread)
    {
        CloseHandle(m_hSendThread);
        m_hSendThread = NULL; 
    }

    SetEvent(m_hSendUCIEvent);
    WaitForSingleObject(m_hSendUCIThread,INFINITE);
    if(m_hSendUCIThread)
    {
        CloseHandle(m_hSendUCIThread);
        m_hSendUCIThread = NULL;
    }
    
    if(m_hSendEvent)
    {
        CloseHandle(m_hSendEvent);
        m_hSendEvent = NULL;
    }
    if(m_hConnectEvent)
    {
        CloseHandle(m_hConnectEvent);
        m_hConnectEvent = NULL;
    }

    if(m_hSendUCIEvent)
    {
        CloseHandle(m_hSendUCIEvent);
        m_hSendUCIEvent = NULL;
    }
    return TRUE;
}

DWORD WINAPI CClient::ReConnectThread(LPVOID lpParam)
{
    CClient *pThis = (CClient*) lpParam;
    
    pThis->DoConnect();
    
    return 0;

}


DWORD WINAPI CClient::SendThread(LPVOID lpParam)
{
    CClient *pThis =  (CClient*)lpParam;
    pThis->DoProcessData();
    return 0;
}

DWORD WINAPI CClient::SendUCIThread(LPVOID lpParam)
{
    CClient *pThis =  (CClient*)lpParam;
    pThis->DoUpdateUCI();
    return 0;
}

void CClient::DoConnect()
{
    do 
    {
        TCPSocket TCPSock;
        if (TCPSock.Connect(m_strServerIP.GetBuffer(0),atoi(m_strPort)))
        {
            m_bConnect = TRUE;
        }
        else
        {
            m_bConnect = FALSE;
        }
        
    } while (WaitForSingleObject(m_hConnectEvent,10*1000) != WAIT_OBJECT_0);// 10sһ������������һ��
}

void CClient::DoProcessData()
{
    CString strTmp;
    m_bConnect = m_tcpSocket.Connect(m_strServerIP.GetBuffer(0),atoi(m_strPort));
   
    
    while(WaitForSingleObject(m_hSendEvent,m_nSendInterval)!= WAIT_OBJECT_0)
    {
        if(m_bConnect) 
        {   
            CStringArray arrVal;
            if(!m_DataConvert.GetDBData(arrVal,m_nUploadMode))
            {
                strTmp.Format("û�д��ϴ��Ĺ�������\n");
                OutputDebugString(strTmp);
                CPowerInfo::WLog(strTmp);
                continue;                
            }
            if(!m_DataConvert.ConvertData(arrVal))
            {
				if(!m_DataConvert.UpdateTrafficID(m_DataConvert.m_tranid,2))
				{
					strTmp.Format("����ת������,�������ݿ�״̬Ϊ2����!\n");
					OutputDebugString(strTmp);
					CPowerInfo::WLog(strTmp);
				}//��ֹͼƬɾ�����ܼ�������
				strTmp.Format("����ת������\n");
                OutputDebugString(strTmp);
                CPowerInfo::WLog(strTmp);
                continue;
            }
			EnterCriticalSection(&g_csSend);
            if(!SendData(m_tcpSocket,1400))
            {
				strTmp.Format("���͹�������ʧ��\n");
                OutputDebugString(strTmp);
                CPowerInfo::WLog(strTmp);
                m_tcpSocket.DisConnect();
                Sleep(500);//�ȴ��������ͷ���Դ��
                m_bConnect = m_tcpSocket.Connect(m_strServerIP.GetBuffer(0),atoi(m_strPort)); // ����ʧ�ܺ������
				LeaveCriticalSection(&g_csSend);
                continue;
            }
			else
			{
				LeaveCriticalSection(&g_csSend);
			}
            if(!m_DataConvert.UpdateTrafficID(m_DataConvert.m_tranid,1))
            {
                strTmp.Format("���¹�����¼ʧ��!\n");
                OutputDebugString(strTmp);
                CPowerInfo::WLog(strTmp);
                continue;
            }
              
        }
    } 
}


void CClient::DoUpdateUCI()
{
    CString strTmp;
    m_bConnect = m_tcpSocket.Connect(m_strServerIP.GetBuffer(0),atoi(m_strPort));
    while(WaitForSingleObject(m_hSendUCIEvent,m_nSendUCIInterval)!= WAIT_OBJECT_0)
    {
        if(m_bConnect) 
        {   
            CStringArray arrVal;
            if(!m_DataConvert.GetDBUCIData(arrVal,m_nUploadMode))
            {
                strTmp.Format("UCIû�д��ϴ��Ĺ�������\n");
                OutputDebugString(strTmp);
                CPowerInfo::WLog(strTmp);
                continue;                
            }
			EnterCriticalSection(&g_csUCI);
            if(!m_DataConvert.ConvertUCIData(arrVal))
            {
                strTmp.Format("UCI����ת������\n");
                OutputDebugString(strTmp);
                CPowerInfo::WLog(strTmp);
                continue;
            }
			EnterCriticalSection(&g_csSend);
            if(!SendData(m_tcpSocket,1405))
            {
                LeaveCriticalSection(&g_csSend);
				LeaveCriticalSection(&g_csUCI);
				strTmp.Format("UCI���͹�������ʧ��\n");
                OutputDebugString(strTmp);
                CPowerInfo::WLog(strTmp);
                m_bConnect = FALSE;
                continue;
            }
			else
			{
				LeaveCriticalSection(&g_csSend);
				LeaveCriticalSection(&g_csUCI);
			}
            if(!m_DataConvert.DelUCITmpInfo(m_DataConvert.m_uciid))
            {
                strTmp.Format("UCIɾ�����ݿ�ʧ��\n");
                OutputDebugString(strTmp);
                CPowerInfo::WLog(strTmp);
                continue;
            }
              
        }
		else
		{
			EnterCriticalSection(&g_csSend);
			m_tcpSocket.DisConnect();
			Sleep(500);//�ȴ��������ͷ���Դ��
			m_bConnect = m_tcpSocket.Connect(m_strServerIP.GetBuffer(0),atoi(m_strPort)); // ����ʧ�ܺ������
			LeaveCriticalSection(&g_csSend);
			strTmp.Format("UCI:DoUpdateUCI:���������粻ͨ\n");
			OutputDebugString(strTmp);
			CPowerInfo::WLog(strTmp);
		}
    } 
}

 BOOL CClient::SendData(TCPSocket &sock,UINT16 wCommand)
 {
    CString strTmp;
    GDW_PacketHead packetHead;
    MakeDataPacket(m_data,wCommand,packetHead);
    if(!sock.SendData((char*)SynInfo,sizeof(SynInfo)))
    {
        strTmp.Format("����ͬ��ͷʧ��!\n");
        OutputDebugString(strTmp);
        CPowerInfo::WLog(strTmp);
        return FALSE;
    }
    
    if(!sock.SendData((char*)&packetHead,sizeof(GDW_PacketHead)))
    {
        strTmp.Format("���Ͱ�ͷʧ��\n");
        OutputDebugString(strTmp);
        CPowerInfo::WLog(strTmp);
        return FALSE;
    }
    
    EnterCriticalSection(&m_csData);
    if(packetHead.dwDataLen)
    {
        if(!sock.SendData(&m_data[0],packetHead.dwDataLen))
        {
            LeaveCriticalSection(&m_csData);
            strTmp.Format("����������ʧ��\n");
            OutputDebugString(strTmp);
            CPowerInfo::WLog(strTmp);
            return FALSE;
        }
		else
		{
			LeaveCriticalSection(&m_csData);
		}
    }
    
    char chRecvSyn[6];
    if(!sock.RecvData(chRecvSyn,6))
    {
        strTmp.Format("����ͬ��ͷʧ��\n");
        OutputDebugString(strTmp);
        CPowerInfo::WLog(strTmp);
        return FALSE;
    }
    int i = 0;
    for(;i<sizeof(chRecvSyn);i++)
    {
        if(chRecvSyn[i] != SynInfo[i])
        {
            strTmp.Format("ͬ��ͷ����\n");
            OutputDebugString(strTmp);
            CPowerInfo::WLog(strTmp);
            return FALSE;
        }
    }
    if(!sock.RecvData((char*)&packetHead,sizeof(packetHead)))
    {
        strTmp.Format("�������ݰ�ʧ��\n");
        OutputDebugString(strTmp);
        CPowerInfo::WLog(strTmp);
        return FALSE;
    }
    
    if(packetHead.wCommandType != COMU_RESPONSE || CheckSum((UINT16*)&packetHead,sizeof(GDW_PacketHead)) != 0)
    {
        strTmp.Format("�������ݰ����ݴ���\n");
        OutputDebugString(strTmp);
        CPowerInfo::WLog(strTmp);
        return FALSE;
    }
    
    if(packetHead.wDataType == 1401)
    {   
        if(packetHead.dwDataLen != 8)
        {
            strTmp.Format("Уʱ���������ݴ���\n");
            OutputDebugString(strTmp);
            CPowerInfo::WLog(strTmp);
            return FALSE;
        }
        
        char chRecvData[8]={0};
        ZeroMemory(chRecvData,sizeof(chRecvData));
        if(!sock.RecvData(chRecvData,sizeof(chRecvData)))
        {
            strTmp.Format("����Уʱ���������ݴ���\n");
            OutputDebugString(strTmp);
            CPowerInfo::WLog(strTmp);
            return FALSE;
        }
        
        SYSTEMTIME st;
        ZeroMemory(&st,sizeof(SYSTEMTIME));
        memcpy(&st.wYear,chRecvData,2);
  
        st.wMonth = chRecvData[2];
        st.wDay = chRecvData[3];
        st.wHour = chRecvData[4];
        st.wMinute = chRecvData[5];
        st.wSecond = chRecvData[6];
 
        if(!::SetLocalTime(&st))
        {
            strTmp.Format("���±���ʱ��ʧ��,error code:%d\n",GetLastError());
            OutputDebugString(strTmp);
            CPowerInfo::WLog(strTmp);
            return FALSE;
        } 
        return TRUE;
    
    }
	//��֤���쳵����Ϣ�ϴ�������
	if(packetHead.wDataType == 1405)
	{   
		if(packetHead.dwDataLen != 0)
		{
			strTmp.Format("���쳵����Ϣ�ϴ����������ݴ���\n");
			OutputDebugString(strTmp);
			CPowerInfo::WLog(strTmp);
			return FALSE;
		}
		return TRUE;
	} 
    return TRUE;
  
 }
 
 BOOL CClient::MakeDataPacket(vector<char> &data,UINT16 wCommand,GDW_PacketHead& packetHead)
 {
    
    ZeroMemory(&packetHead,sizeof(GDW_PacketHead));
    
    switch(wCommand)
    {
        case 1400:
        case 1410:
            {
                packetHead.wCommandType = COMU_REQUEST;
                packetHead.wDataType = wCommand;
                
                CMR_TrafficData *pData = m_DataConvert.GetTrafficData();
                int i = 0;
                EnterCriticalSection(&m_csData);
                data.clear();
                for(;i<MINPACKETLEN;i++)
                {
                    data.push_back(((char*)(pData))[i]);
                }
                if(pData->nPlateJpegSize == 0 || pData->nPlateJpegSize >MAX_PLATE_JPEG_SIZE)
                {
                    for(i =0;i<sizeof(int);i++)
                    {
                        data.push_back(0);
                    }
                }
                else 
                {
                    int nPlateJpegSize = pData->nPlateJpegSize;
                    char *p = (char*)&nPlateJpegSize;
                    
                    //��������ͼƬ��С
                    for(i =0;i<sizeof(int);i++)
                    {
                        data.push_back(p[i]);
                    }
                    //��������ͼƬ����
                    for(i=0;i<nPlateJpegSize;i++)
                    {
                        data.push_back(((char*)(pData->pnPlateJpegData))[i]);
                    }

                }
                if(pData->nCarJpegSize == 0 || pData->nCarJpegSize > MAX_CAR_JPEG_SIZE)
                {                    
                    for(i =0;i<sizeof(int);i++)
                    {
                        data.push_back(0);
                    }
                }
                else 
                {
                    int nCarJpegSize = pData->nCarJpegSize;
                    char *p = (char*)&nCarJpegSize;
                    
                    //��������ͼƬ��С
                    for(i =0; i<sizeof(int);i++)
                    {
                        data.push_back(p[i]);
                    }
                    
                    // ��������ͼƬ����
                    for(i =0;i<nCarJpegSize;i++)
                    {
                        data.push_back(((char*)(pData->pnCarJpegData))[i]);
                    }
                }
                packetHead.dwDataLen = MINPACKETLEN + 2*sizeof(UINT32) + pData->nPlateJpegSize +pData->nCarJpegSize;
                
                packetHead.wCheckSum = CheckSum((UINT16*)&packetHead,sizeof(GDW_PacketHead));
                
                LeaveCriticalSection(&m_csData);
                
            }
            break;
            case 1401:
            {
                packetHead.wDataType = 1401;
                packetHead.wCommandType = COMU_REQUEST;
                packetHead.wCheckSum = CheckSum((UINT16*)&packetHead,sizeof(GDW_PacketHead));
                EnterCriticalSection(&m_csData);
                data.clear();
                LeaveCriticalSection(&m_csData);
            }
            break;
			case 1405:
			{
				packetHead.wDataType = wCommand;
				packetHead.wCommandType = COMU_REQUEST;
				packetHead.dwDataLen = 112;
				UCI_TrafficData *pUCIData = m_DataConvert.GetUCIData();
				
				data.clear();
				for(int i = 0;i<UCIPACKETLEN;i++)
				{
					data.push_back(((char*)(pUCIData))[i]);
				}
				packetHead.wCheckSum = CheckSum((UINT16*)&packetHead,sizeof(GDW_PacketHead));
				
			}
			break;
    }
    return TRUE;
    
 }
 
 BOOL CClient::Init(CConfig &config)
 {
    char chTmp[256] ={0};
    /**due this config has a problem that the default value is bad
       so I will don't use this config class and just use API to read from ini file*/
    m_strPort = config.ReadConfig("Center","CenterPort","8682");
    m_strServerIP = config.ReadConfig("Center","CenterIp","10.100.40.130");
    m_nSendInterval = config.ReadConfig("Center","SendInterval",500); // ���ͼ��
    m_nSendUCIInterval = config.ReadConfig("Center","SendUCIInterval",1000); // ���ͼ��
    m_nUploadMode = config.ReadConfig("Center","UploadMode",0); //��ʷ��������    
       
    return m_DataConvert.Init(config);
 }
 
 BOOL CClient::DoCheckTime()
 {
    CString strTmp;
    TCPSocket socket;
    BOOL bConnect;
   bConnect = socket.Connect(m_strServerIP,atoi(m_strPort));
   if(bConnect)
   {
       EnterCriticalSection(&g_csSend); 
	   if(!SendData(socket,1401))
        {
            LeaveCriticalSection(&g_csSend);
			strTmp.Format("skid---Уʱʧ��\n");
            OutputDebugString(strTmp);
            return FALSE;
        }
	   else
	   {
			LeaveCriticalSection(&g_csSend);
	   }
	   
        socket.DisConnect();
   }
   OutputDebugString("skid----Уʱ�ɹ�\n");
   return TRUE;
 }


 BOOL CClient::DoSendUCIData()
 {
	 CString strTmp;
	 //TCPSocket socket;
	 //BOOL bConnect;
	 m_tcpSocket.DisConnect();
	 m_bConnect = m_tcpSocket.Connect(m_strServerIP.GetBuffer(0),atoi(m_strPort));
	 if(m_bConnect)
	 {
		 EnterCriticalSection(&g_csSend);
		 if(!SendData(m_tcpSocket,1405))
		 {
			 LeaveCriticalSection(&g_csSend);
			 strTmp.Format("hc---���쳵����Ϣ�ϴ�ʧ��\n");
			 OutputDebugString(strTmp);
			 return FALSE;
		 }
		 else
		 {
			 LeaveCriticalSection(&g_csSend);
			 return TRUE;
		 }
	 }
	 else
	 {
		 strTmp.Format("hc---���粻ͨ\n");
		 OutputDebugString(strTmp);
		 return FALSE;
	 }
 }


  BOOL CClient::DoSaveTmpUCI()
 {
	if(m_DataConvert.SaveTmpToDB())
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
 }