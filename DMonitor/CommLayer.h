
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
    TYPE_NONE,//未连接状态
	TYPE_INIT,//初始化搜索可用端口时
	TYPE_COMM,//链接已建立，随时准备发送接收数据
}Connect_type;
// CCommLayer 命令目标

class CCommLayer : public CCmdTarget
{
	DECLARE_DYNAMIC(CCommLayer)
public:
	HWND fatherHwnd;  //调用的应用程序窗口指针。
	CSerialPort m_SerialPort;
    SubKeyInfo_type SubKey[array_size];//sub keys

    int m_FuncReturnValue;
    DWORD comnumber;//有效的COM口数量
    DWORD num;//有效的COM口数量
    WORD m_RetryTimes;
    BYTE m_WriteBuffer[COMM_BUFFER_BASESIZE];//send buffer
    WORD m_WriteBufferSize;
    BYTE m_ReceiveBuff[4*COMM_BUFFER_BASESIZE];//receive buffer
    WORD m_ReceiveBufferSize;
    BOOL ReceivewholePacket;     //接收的是整个packet
	UINT8 sendCmd[COMM_BUFFER_BASESIZE];//通信层发送数据 buffer
	WORD sendDataSize;
    bool m_bConnectEffective; //连接有效,断开连接后此值为FALSE
    BOOL bTaskCanceled;//执行取消函数接口
    WORD m_wlocalReceivePtr;         //数据bytes接收位置
    BYTE m_Mingroup;//组号最小序号
	BYTE m_Maxgroup;//组号最大序号
    Event_type m_EventStatus;
    bool isNewData;//检测到开头是“$LQRD”则认为是新数据

	BOOL m_bISAddField;  
private:
	Connect_type m_ConnectType;
	UINT  baudrate;   // 波特率
public:
	CCommLayer();
	virtual ~CCommLayer();
	//////////////以下对外接口/////////////////
	DWORD CreatConnect( );
	Connect_type GetConnectType();
	void SetConnectType(Connect_type type);
	//////////////以上对外接口/////////////////
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


