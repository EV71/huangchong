#pragma once
#include "incMYSQL/mysql.h"
#include <WinSock.h>
#pragma  comment(lib,"lib/libmySQL.lib")

class COpMySQL
{
public:
	COpMySQL(void);
	~COpMySQL(void);

public:
	BOOL OpenConn(LPCTSTR szServerName,LPCTSTR szUserName,LPCTSTR szPassword,LPCTSTR szDBName,LPCTSTR szPort);
	void CloseConn();
	BOOL ExecuteSQL(LPCTSTR szSql);
	BOOL ExecuteMulSQL(LPCTSTR szSql[], int iNum);

	BOOL ExecuteSQL(CString strSql);
	BOOL ExecuteMulSQL(CString strSql[],int iNum);

	MYSQL_RES* OpenRecordset(LPCTSTR szSql);  /* if you openrecordset(), you should closerecordset first,and then 
											  you can excute Sql sentence,or you just excute sql sentence fail...*/

	void CloseRecordset(MYSQL_RES *pResult);
	BOOL GetConnState();

private:
	MYSQL m_connMysql; // mysql ���ݿ����Ӿ��
	MYSQL_RES *m_pResult; // ��ǰ��¼��ָ��
	MYSQL_ROW m_row;    //��ǰ��¼��
	CRITICAL_SECTION	m_csLock; // ��֤һ��ִֻ��һ��SQL���
	BOOL m_bConnState; // �������ݿ�ɹ� Ϊ TRUE,���� FALSE
};

