
#pragma once

#include "SerialPort.h"
#include "PublicInterface.h"
/*
#define WM_USER_RECEIVEDATA (WM_USER+7)
#define WM_CONNECT_ERR      (WM_USER+8)
#define WM_CONNECT_OK      (WM_USER+9)
#define WM_JOBLOAD_OK      (WM_USER+10)
*/
const int array_size =100;
const BYTE diag_maincmd =0x16;

extern CEvent g_event;

typedef struct
{
    DWORD  SubKeyIndex;
    TCHAR   SubKeyName[80];
    DWORD  SubKeyNameLength;
    TCHAR   SubKeyValue[80];
    DWORD  SubKeyValueLength;
}SubKeyInfo_type;

typedef enum
{
    UNSIGNALED,
    SIGNALED,
}Event_type;

typedef enum
{
    TYPE_NONE,//δ����״̬
	TYPE_INIT,//��ʼ���������ö˿�ʱ
	TYPE_COMM,//�����ѽ�������ʱ׼�����ͽ�������
}Connect_type;
// CCommLayer ����Ŀ��

class CCommLayer : public CCmdTarget
{
	DECLARE_DYNAMIC(CCommLayer)
public:
	HWND fatherHwnd;  //���õ�Ӧ�ó��򴰿�ָ�롣
	CSerialPort m_SerialPort;
    SubKeyInfo_type SubKey[array_size];//sub keys

    int m_FuncReturnValue;
    DWORD comnumber;//��Ч��COM������
    DWORD num;//��Ч��COM������
    WORD m_RetryTimes;
    BYTE m_WriteBuffer[COMM_BUFFER_BASESIZE];//send buffer
    WORD m_WriteBufferSize;
    BYTE m_ReceiveBuff[4*COMM_BUFFER_BASESIZE];//receive buffer
    WORD m_ReceiveBufferSize;
    BOOL ReceivewholePacket;     //���յ�������packet
	UINT8 sendCmd[COMM_BUFFER_BASESIZE];//ͨ�Ų㷢������ buffer
	WORD sendDataSize;
    bool m_bConnectEffective; //������Ч,�Ͽ����Ӻ��ֵΪFALSE
    BOOL bTaskCanceled;//ִ��ȡ�������ӿ�
    WORD m_wlocalReceivePtr;         //����bytes����λ��
    BYTE m_Mingroup;//�����С���
	BYTE m_Maxgroup;//���������
    Event_type m_EventStatus;
    bool isNewData;//��⵽��ͷ�ǡ�$LQRD������Ϊ��������

	BOOL m_bISAddField;  
private:
	Connect_type m_ConnectType;
	UINT  baudrate;   // ������
public:
	CCommLayer();
	virtual ~CCommLayer();
	//////////////���¶���ӿ�/////////////////
	DWORD CreatConnect( );
	Connect_type GetConnectType();
	void SetConnectType(Connect_type type);
	//////////////���϶���ӿ�/////////////////
	wchar_t * FromGBToUNICODE(char *pData,int *nDataLen,int *pwDataLen);
    char * FromUNICODEToGB(wchar_t *pData, int *nwDataLen, int *pDataLen);
    int SendCommand(BYTE* outbuff, DWORD dwSize);
    
    WORD TransData(BYTE* outbuff, DWORD dwSize);
    WORD RecvData(BYTE* inbuff, WORD dwSize);
    bool CheckReceivePacketStatus(BYTE *pbBuff, WORD *wSize);
    WORD ChangeCStringToWORD (CString strChange);
	DWORD ChangeCStringToDWORD (CString strChange);
	UINT8 CrcCheck(UINT8 *buf);
	bool CrcCheck(UINT8 *buf, WORD dwSize);
	int GenerateSendData(UINT8 *buf, int size);
	UINT getBaudrate();
	void setBaudrate(UINT band);
private:
	int GetRegisterdComPort(SubKeyInfo_type* SubKey, DWORD* number);
	int SelectComPort(void);
    int SendVerification(void);
protected:
	DECLARE_MESSAGE_MAP()
};


