
#define	RETVAL_OK							0x0		///< ��ȷ
#define RETVAL_DEPLOYMEMT_FAIL				0x1		///< ����ʧ��
#define	RETVAL_SET_ALARM_CALL_BACK_FAIL		0x2		///< ���ñ����ص�����ʧ��
#define RETVAL_CLEAN_ALARM_FAIL				0x3		///< ��������ʧ��
#define RETVAL_CANCEL						0x4		///< ȡ��

#define RETVAL_ERROR						-0x1	///< ����
#define RETVAL_STOP_REALPLAY_ERROR			-0x2	///< ֹͣԤ������
#define RETVAL_LOGOUT_ERROR					-0x3	///< �ǳ��豸ʧ��
#define RETVAL_LOGIN_ERROR					-0x4	///< ��¼�豸ʧ��
#define RETVAL_DEVICE_NOT_LOGIN				-0x5	///< �豸û�е�¼
#define RETVAL_REALPLAY_ERROR				-0x6	///< Ԥ��ʧ��
#define RETVAL_INVALID_PARAM				-0x7	///< ��Ч����
#define RETVAL_GET_PLATE_INFO_ERROR			-0x8	///< ��ȡ������Ϣʧ��
#define RETVAL_SAVE_PIC_ERROR				-0x9	///< ����ͼƬʧ��
#define RETVAL_HAVE_NO_IMAGE				-0xA	///< û��ͼƬ
#define RETVAL_NOT_RECV_PIC					-0xB	///< ��ǰ����²�����ͼƬ
#define RETVAL_SHOOT_ERROR					-0xC	///< ץ��ʧ��
#define RETVAL_DEVICE_CONNECT_ERROR			-0xD	///< �豸������



#define SCCP_MAX_PLATEINFO_NUM				1				///< ��������ౣ�泵����Ϣ��Ŀ
#define SCCP_MAX_PIC_NUM					5				///< ͼƬ��������Ŀ
#define SCCP_MAX_PIC_SIZE				(1024 * 1024 * 2)	///< ÿ��ͼƬ������С

#define LOG_FILE_PATH					_T("C:\\ToHvShow_LogFile\\")		///< ��־�ļ�����·��

#define GET_PLATE_NUM						0x1				///< ��ȡ���ƺ���
#define GET_PLATE_COLOR						0x2				///< ��ȡ������ɫ
#define GET_CAR_NEAR_PIC					0x4				///< ��ȡ��������ͼƬ
#define GET_CAR_FAR_PIC						0x8				///< ��ȡԶ��ͼƬ
#define GET_PLATE_PIC						0x10			///< ��ȡ����ͼƬ
#define GET_PLATE_BIN_PIC					0x20			///< ��ȡ������ֵͼ