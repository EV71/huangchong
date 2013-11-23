/**
@FileName:  Config.h
@ClassName: CConfig
@Brief: �����ļ���д��

*/


#pragma once

class CConfig
{
    public:
        CConfig(CString strIniFile);
		CConfig(){};
        virtual ~CConfig(void);
           
        CString ReadConfig(LPCTSTR lpAppName,LPCTSTR  lpKey,LPCTSTR lpDefaultKey);
        int ReadConfig(LPCTSTR lpAppName, LPCTSTR lpKeyName, int nDefault); 
        BOOL WriteConfig(LPCTSTR lpAppName,LPCTSTR lpKeyName,LPCTSTR lpString);
        BOOL SetFilePath(CString strIniFile); //���������ļ�·��
        CString GetFilePath();
     private:
        CString m_strIniFile; // �����ļ�·��
        CRITICAL_SECTION m_cs; // �������ļ���
 };
