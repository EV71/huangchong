/**
@file: DataConvert.h
@Breif: ��Ҫ�Ǵ�������ת�����õ�Э���Ӧ������
@Author: skid
@Date:2011/09/26
@History:
*/
/* �����������ݵ�ת����Ҫ�ǽ���MYSQL���ݿ��еõ�������ת����Э������*/

#pragma once

#include "OpMySQL.h"
#include "basicType.h"
#include "Config.h"

class DataConvert
{
    public:
        
        DataConvert(CConfig &config);// ��ĳ�ʼ��
        
        virtual ~DataConvert(void);
        
        BOOL Init(CConfig &config);
        
        COpMySQL  m_opMysql;
        CMR_TrafficData *m_pTrafficData;

        UCI_TrafficData *m_pUCIData;
        
        
        BOOL m_bConnDB;
        
        CString m_strDBServer;
        CString m_strDBName;
        CString m_strDBUser;
        CString m_strDBPwd;
        CString m_strDBPort;
        
        INT64 m_tranid; // ������ˮ��
        INT64 m_uciid; // ���쳵����ˮ��
        
        MYSQL_RES* m_pRes; // �õ������ݼ�
		MYSQL_RES* m_pUCIRes; // �õ������ݼ�
     
        
        BOOL GetDBData(CStringArray &arr,BOOL bRealTime); // �ӹ������ж�ȡ1�й�������
        CMR_TrafficData* GetTrafficData();
        UCI_TrafficData *GetUCIData();
        BOOL ConvertData(CStringArray &arr); // �������ݿ��ж��������� ת���� Э���Ӧ������
        BOOL UpdateTrafficID(UINT64 nTrafficID, UINT16 nStatus); // �������ݿ�
        BOOL PutData(CStringArray &arr,int nIndex,CStringArray & arrField); // ����ȡ������ȡһ���ֶ���
        BOOL GetDBUCIData(CStringArray &arr,BOOL bRealTime);
        BOOL ConvertUCIData(CStringArray &arr);
        BOOL DelUCITmpInfo(UINT64 nUCIID);
        BOOL SaveTmpToDB();
        BOOL PutUCIData(CStringArray &arr,int nIndex,CStringArray & arrField);
        BOOL ReadJpegFile(CString strFile,UINT32 &nFileSize,int nType); // ��ȡͼƬ�ļ���С������
        
        CRITICAL_SECTION m_cs; // ��ȡ�ļ����ٽ���
        
};
