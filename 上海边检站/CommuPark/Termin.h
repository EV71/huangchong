
/**
@FileName: Termin.h
@ClassName: Termin
@Brief: ������ն��࣬�������������ϴ������Լ���������ͨ���ȴ� ���ݴ������������
*/
#pragma once

#include "Client.h"
#include "Server.h"
#include "Config.h"
class Termin
{
    public:
        Termin(CConfig &config);
        virtual ~Termin(void);
        Server m_server;
        CClient m_client; 
        
        BOOL Init(CConfig &config);
        
        BOOL Start();
        
        BOOL Stop();
        
        BOOL CheckTime(); 
	BOOL SendUCIData();
        BOOL SaveTmpUCI();

    private:
        BOOL m_bUpData;
        BOOL m_bListen;
};
