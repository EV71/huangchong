#pragma once
#include <windef.h>

class clsTDKJClass{
public:
    clsTDKJClass();
    ~clsTDKJClass();

    typedef unsigned (WINAPI * DSBDLL)(unsigned ComPort,char * OutString);
private:
    HMODULE m_hTDBJQ;
    DSBDLL m_funcDsbdll;
public:
    void TDKJ_Wait();//�ȴ�����
    void TDKJ_VoiceShow(int iMinutes,double iShouldPay,double iFinalPay);//���Ѻ���
    void TDKJ_Clear();//��������
    void TDKJ_Cmd(char * OutString);//��������
};