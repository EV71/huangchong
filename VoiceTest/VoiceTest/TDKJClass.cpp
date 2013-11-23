#include "stdafx.h"
#include "TDKJClass.h"
clsTDKJClass::clsTDKJClass()
{
    m_hTDBJQ = NULL;
    m_funcDsbdll = NULL;
    m_hTDBJQ = LoadLibrary(L"Tdbjq.dll");
    if(m_hTDBJQ != NULL)
    {
        m_funcDsbdll = (DSBDLL)GetProcAddress(m_hTDBJQ, "dsbdll");  
    }
}
clsTDKJClass::~clsTDKJClass()
{
    if (m_hTDBJQ != NULL)
    {
        FreeLibrary(m_hTDBJQ);
        m_hTDBJQ = NULL;
    }
    m_funcDsbdll = NULL;
}
//�ȴ�����
void clsTDKJClass::TDKJ_Wait()
{
    if(m_funcDsbdll != NULL)
    {
        m_funcDsbdll(0,"&Sc$");
        m_funcDsbdll(0,"&C24����,���Եȣ�$");
        m_funcDsbdll(0,"W");
    }
}
//���Ѻ���
void clsTDKJClass::TDKJ_VoiceShow(int iMinutes,double iShouldPay,double iFinalPay)
{
    if(m_funcDsbdll != NULL && iMinutes > 0)
    {
        int iDay = (int)(iMinutes/1440);
        int iHour = (int)((iMinutes%1440)/60);
        int iMinute = (int)(((iMinutes%1440)%60));
        CString cstrParkingTime;
        CString cstrShouldPay;
        CString cstrFinalPay;
        CString cstrShouldPayVoice;
        CString cstrFinalPayVoice;
        cstrParkingTime.Format(_T("&C11ͣ��ʱ����"));
        if(iDay > 0)
        {
            cstrParkingTime.AppendFormat(_T("%d��"),iDay);
        }
        if(iHour > 0)
        {
            cstrParkingTime.AppendFormat(_T("%dСʱ"),iHour);
        }
        if(iMinute > 0)
        {
            cstrParkingTime.AppendFormat(_T("%d��"),iMinute);
        }
        cstrParkingTime.AppendFormat(_T("$"));
        cstrShouldPay.Format(_T("&C31Ӧ�գ�%0.2fԪ$"),iShouldPay);
        cstrFinalPay.Format(_T("&C41ʵ�գ�%0.2fԪ$"),iFinalPay);
        cstrShouldPayVoice.Format(_T("%fP"),iShouldPay);
        cstrFinalPayVoice.Format(_T("%fP"),iFinalPay);
        m_funcDsbdll(0,"&Sc$");//����
        USES_CONVERSION;
        m_funcDsbdll(0,W2A(cstrParkingTime.GetBuffer(0)));
        m_funcDsbdll(0,W2A(cstrShouldPay.GetBuffer(0)));
        m_funcDsbdll(0,"u");
        m_funcDsbdll(0,W2A(cstrShouldPayVoice.GetBuffer(0)));
        m_funcDsbdll(0,W2A(cstrFinalPay.GetBuffer(0)));
        m_funcDsbdll(0,"A");
        m_funcDsbdll(0,W2A(cstrFinalPayVoice.GetBuffer(0)));
        m_funcDsbdll(0,"X");
    }
}
//��������
void clsTDKJClass::TDKJ_Clear()
{
    if(m_funcDsbdll != NULL)
    {
        m_funcDsbdll(0,"&Sc$");
        m_funcDsbdll(0,"&C25лл�ݹˣ�$");
    }
}
//��������
void clsTDKJClass::TDKJ_Cmd(char * OutString)
{
    if(m_funcDsbdll != NULL)
    {
        m_funcDsbdll(0,OutString);
    }
}