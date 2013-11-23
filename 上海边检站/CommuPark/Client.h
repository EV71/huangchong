/**
@FileName: Client.h
@Brief:  ����ฺ���������ݴ����������������ͣ�����ն˷������ϴ��������� ������Ӧ��
@ClassName: CClient
@Author: skid
@Date:   20110927
@History:  
*/

#pragma once

#include "TCPSocket.h"
#include "Config.h"
#include "DataConvert.h"




class CClient
{
    public:
        CClient(CConfig &config);
        virtual ~CClient(void);
        
        BOOL Init(CConfig &config);
        
        
        static DWORD WINAPI ReConnectThread(LPVOID lpParam); //�����߳�
        static DWORD WINAPI SendThread(LPVOID lpParam);     // �����߳�
        static DWORD WINAPI SendUCIThread(LPVOID lpParam);     // �����߳�
        
        BOOL MakeDataPacket(vector<char> &data,UINT16 wCommand,GDW_PacketHead& packetHead); // ���
         
        BOOL SendData(TCPSocket &sock,UINT16 wCommand); // �������ݰ�
     
        BOOL m_bConnect; // �Ƿ�������
        
        void DoConnect(); // �����̵߳�ʵ��
        void DoProcessData(); // ��������
        
        void DoUpdateUCI(); // �������쳵������
        
        BOOL GetConnect()
        {return m_bConnect;}
        
        TCPSocket m_tcpSocket;
        
        CString  m_strPort;      // 8682
        CString m_strServerIP;   // ���ݴ��������IP
        int m_nSendInterval; //�������ݵļ��ʱ��
        int m_nSendUCIInterval;
        int m_nUploadMode;       // �ϴ�ģʽ
        
        DataConvert m_DataConvert;
        
        vector<char> m_data;
        
        CRITICAL_SECTION m_csData; //buffer���ٽ���
        
        HANDLE m_hConnectEvent; //�����¼�
        HANDLE m_hSendEvent;   // �����¼�
        
        HANDLE m_hSendUCIEvent;
        
        HANDLE m_hConnectThread;
        HANDLE m_hSendThread;
        
        HANDLE m_hSendUCIThread;
        
        
        BOOL DoStart();  // �������ӿ�ʼ��������
        
        BOOL DoStop();  // �ر�����
        
        BOOL DoCheckTime();//Уʱ����

		BOOL DoSendUCIData();//�ϴ����쳵����Ϣ

        BOOL DoSaveTmpUCI();
        
        
        
};
