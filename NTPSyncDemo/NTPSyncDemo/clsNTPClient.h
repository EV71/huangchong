#ifndef CLS_NTP_CLIENT
#define CLS_NTP_CLIENT


#include <stdio.h>
#include <Windows.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <crtdbg.h>
#include <sys/timeb.h>
#include <time.h>

//#ifndef _DEBUG
//#define printf(x)
//#define printf(x, y)
//#endif

struct ntp_timestamp
{
	unsigned int secondsFrom1900;//1900��1��1��0ʱ0������������
	unsigned int fraction;//΢���4294.967296(=2^32/10^6)��
};

struct ntp_header
{
	union
	{
		struct 
		{
			char local_precision;//��ʾ����ʱ�Ӿ���Ϊ2^local_precision�롣local_precisionͨ��Ϊ������
			char poll_intervals;//��ʾ���Լ��Ϊ2^poll_intervals�롣
			unsigned char stratum;//NTP�������׼���0��ʾ��ָ����1��ʾУ׼��ԭ���ӡ�Ӧ��Ϊ0��
			unsigned char mode : 3;//ͨ��ģʽ��Ӧ��Ϊ3����ʾ��client��
			unsigned char version_number : 3;//NTPЭ��汾�š�Ӧ��Ϊ3��
			unsigned char leap_indicator : 2;//����ָʾ��һ����0��
		};
		int noname;
	};

	int root_delay;//�����ɸ���2^16��ʾһ�롣���庬��μ�RFC1305��
	int root_dispersion;//ֻ��Ϊ����2^16��ʾһ�롣���庬��μ�RFC1305��
	int reference_clock_identifier;//���庬��μ�RFC1305��һ����0��
};//û�д���Ļ���ntp_header�Ĵ�СӦ��Ϊ16�ֽڡ�

struct ntp_packet
{
	ntp_header header;
	//�����ĸ�ʱ���Ϊ����ʱ�䡣��������ʱ��λ�õġ�
	ntp_timestamp reference;//���庬��μ�RFC1305��һ����0��
	ntp_timestamp originate;//�ϴη���ʱ��
	ntp_timestamp receive;//����ʱ��
	ntp_timestamp transmit;//����ʱ��
};//û�д���Ļ���ntp_header�Ĵ�СӦ��Ϊ48�ֽڡ�


class clsNTPClient
{
public:
	clsNTPClient();
	~clsNTPClient();
private:
	inline unsigned int MicroSeconds2NTPFraction(unsigned int x);
	inline unsigned int NTPFraction2MicroSeconds(unsigned int x);
	bool SendNTPPacket(SOCKET sock, const sockaddr* to);
	bool RecvNTPPacket(SOCKET sock, ntp_packet& packet);
	bool MySetLocalTime(const ntp_packet& packet);
public:
	bool SetParams(char* chIP, int iPort, int iInterval);
	int AdjustTimeUDP();
	int AdjustTimeTCP();
	bool Start(CListBox *listbox);
	bool Stop();
public:
	static DWORD WINAPI ThreadProc(LPVOID lpParameter);
private:
	char m_chNTPServer[20];
	int m_iNTPPort;
	int m_iInterval;
public:
	static unsigned int m_siJAN1970;// = 0X83AA7E80;//=2208988800(1970/1/1 - 1900/1/1 in seconds)*/
	static bool m_threadflag;
	static CRITICAL_SECTION m_csflag;
	HANDLE m_hThreadEvent;
	HANDLE m_hThread;
	CListBox *m_lbListBox;
};

#endif