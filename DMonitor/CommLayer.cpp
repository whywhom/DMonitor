// CommLayer.cpp : 实现文件
//

#include "stdafx.h"
#include <math.h>
#include "DMonitor.h"
#include "CommLayer.h"
#include "SerialPort.h"

CEvent g_event;
// CCommLayer

IMPLEMENT_DYNAMIC(CCommLayer, CCmdTarget)


CCommLayer::CCommLayer()
{
	m_bConnectEffective=false;
	setBaudrate(115200);
}

CCommLayer::~CCommLayer()
{
}


BEGIN_MESSAGE_MAP(CCommLayer, CCmdTarget)
END_MESSAGE_MAP()



// CCommLayer 消息处理程序
//建立连接

Connect_type CCommLayer::GetConnectType()
{
	return m_ConnectType;
}
void CCommLayer::SetConnectType(Connect_type type)
{
	m_ConnectType = type;
}

UINT CCommLayer::getBaudrate()
{
	return baudrate;
}
void CCommLayer::setBaudrate(UINT band)
{
	baudrate = band;
}

/**************************************************************************/
/***  specifications;              ***/
/***  NAME   = FromGBToUNICODE;       ***/
/***  FUNCTION  = GB码转换为UNICODE   ***/
/***  DATE   = 2014/07/11;           ***/
/***  AUTHOR  = wuhaoyong;              ***/
/***  INPUT   = *pData-GB字符串,*nDataLen-GB字符串有效长度,*pwDataLen-转换为UNICODE的长度;               ***/
/***  OUTPUT  = *pwBuffer-UNICODE字符串;               ***/
/***  END OF SPECIFICATIONS;            ***/
/**************************************************************************/
wchar_t *CCommLayer::FromGBToUNICODE(char *pData, int *nDataLen,
                                     int*pwDataLen)
{
    UINT nCodePage = 936; //GBK
    int nLength = MultiByteToWideChar(nCodePage, 0, pData,  - 1, NULL, 0);
    wchar_t *pwBuffer = new wchar_t[nLength + 1];
    *pwDataLen = MultiByteToWideChar(nCodePage, 0, pData,  - 1, pwBuffer, nLength);
    return pwBuffer;
}
/**************************************************************************/
/***  specifications;              ***/
/***  NAME   = FromUNICODEToGB;       ***/
/***  FUNCTION  = UNICODE转换为GB码   ***/
/***  DATE   = 2014/07/11;           ***/
/***  AUTHOR  = wuhaoyong;              ***/
/***  INPUT   = *pData-UNICODE字符串,*nwDataLen-UNICODE字符串有效长度,*pDataLen-转换为GB的长度;               ***/
/***  OUTPUT  = *pBuffer-GB字符串;               ***/
/***  END OF SPECIFICATIONS;            ***/
/**************************************************************************/
char *CCommLayer::FromUNICODEToGB(wchar_t *pData, int *nwDataLen,
                                  int*pDataLen)
{
    int m_WDateLen=*nwDataLen;

    UINT nCodePage = 936; //GB2312
    *pDataLen = WideCharToMultiByte(nCodePage, 0, pData,  (m_WDateLen/2), NULL, 0, NULL, NULL);
    char *pBuffer = new char[ *pDataLen + 1];
    memset(pBuffer, 0,  *pDataLen + 1);
    WideCharToMultiByte(nCodePage, 0, pData,  - 1, pBuffer,  *pDataLen, NULL, NULL);
    delete []pData;
    pData = NULL;
    return pBuffer;
}
DWORD CCommLayer::CreatConnect( )
{
	SetConnectType(TYPE_INIT);
    memset(SubKey,0,sizeof(SubKey));
    m_FuncReturnValue = GetRegisterdComPort(SubKey,&comnumber);
    if(m_FuncReturnValue == 0)
    {
        num=comnumber;
        for(DWORD i=0;i<comnumber;i++)
        {
            m_FuncReturnValue = SelectComPort();
			////TRACE(_T("m_FuncReturnValue = %d\n"),m_FuncReturnValue);
            if(m_FuncReturnValue==2)
            {
                return COMM_ERROE_HARDWARE_CONNECT_FAIL;//main program call waiting result
            }
            else if(m_FuncReturnValue==1)
            {
                continue;
            }
            else
            {
                //send data
                m_FuncReturnValue = SendVerification();
                if (::WaitForSingleObject(g_event, 2000) ==WAIT_OBJECT_0)
                {
                    g_event.ResetEvent();
                    if(m_bConnectEffective==true)
                    {
                        return COMM_SUCCESS;
                    }
                    else
                    {
                        m_SerialPort.ClosePort();//关闭串口
                        continue;
                    }
                }
                else
                {
                    //send data
                    m_FuncReturnValue = SendVerification();
                    if (::WaitForSingleObject(g_event, 2000) ==WAIT_OBJECT_0)
                    {
                        g_event.ResetEvent();
                        if(m_bConnectEffective==TRUE)
                        {
                            return COMM_SUCCESS;
                        }
                        else
                        {
                            m_SerialPort.ClosePort();//关闭串口
                            continue;
                        }
                    }
                    else
                    {
                        m_SerialPort.ClosePort();//关闭串口
                        if(m_SerialPort.m_bThreadAlive)
                        {
                            if(m_SerialPort.m_Thread->m_hThread!=NULL)
                            {
                                TerminateThread (m_SerialPort.m_Thread->m_hThread, 0);
                                m_SerialPort.m_Thread=NULL;
                                m_SerialPort.m_bThreadAlive=FALSE;
                            }
                        }
                        continue;
                    }
                }
            }
        }
        return COMM_ERROE_HARDWARE_CONNECT_FAIL;//main program call waiting result
    }
    else
    {
        //enum com port error
        return COMM_ERROE_HARDWARE_CONNECT_FAIL;//main program call waiting result
    }
}
/**************************************************************************/
/***  specifications;              ***/
/***  NAME   = GetRegisterdComPort;       ***/
/***  FUNCTION  = enumerates the values for the specified open registry key   ***/
/***  DATE   = 2014/07/11;           ***/
/***  AUTHOR  = wuhaoyong;              ***/
/***  INPUT   = ;               ***/
/***  OUTPUT  = ;               ***/
/***  END OF SPECIFICATIONS;            ***/
/**************************************************************************/
int CCommLayer::GetRegisterdComPort(SubKeyInfo_type* SubKey, DWORD* number)
{
    const HKEY registerkey=HKEY_LOCAL_MACHINE;
    const LPCTSTR kename=_T("HARDWARE\\DEVICEMAP\\SERIALCOMM");
    HKEY qusbregisterkey;   //father key handle

    /////////////////////////////////////
    //加入这些语句防止RegEnumValue函数在release版本下工作不正常！2014/07/11
    for(int i=0;i<array_size;i++)
    {
        SubKey[i].SubKeyNameLength=80;
        SubKey[i].SubKeyValueLength=80;
    }
    /////////////////////////////////////

    DWORD subkeyindex=0;         //temp index
    LONG returnvalue;
    DWORD type_1=REG_SZ;

    //opens the specified registry key. Note that key names are not case sensitive.
    returnvalue=RegOpenKeyEx(registerkey,kename,0,KEY_READ,&qusbregisterkey);
    //If the function succeeds, the return value is ERROR_SUCCESS.
    if(returnvalue!=ERROR_SUCCESS)
    {
        return 1;//error
    }

    do
    {
        //enumerates the values for the specified open registry key. The function copies one indexed value name and data block for the key each time it is called.
        returnvalue=RegEnumValue(qusbregisterkey,subkeyindex,
                                 SubKey[subkeyindex].SubKeyName,
                                 &(SubKey[subkeyindex].SubKeyNameLength),
                                 NULL,&type_1,(LPBYTE)(SubKey[subkeyindex].SubKeyValue),
                                 &(SubKey[subkeyindex].SubKeyValueLength));
        if(returnvalue!=ERROR_SUCCESS)  //If the function succeeds, the return value is ERROR_SUCCESS.
        {
            if(returnvalue==ERROR_NO_MORE_ITEMS)  //there are no more values
            {
                break;
            }
            else
            {   //取子键名出错！
                RegCloseKey(qusbregisterkey);
                return 1;
            }
        }
        subkeyindex++;
    }
    while(1);
    RegCloseKey(qusbregisterkey);
    *number=subkeyindex;
    return 0;
}

/**************************************************************************/
/***  specifications;              ***/
/***  NAME   = SelectComPort;       ***/
/***  FUNCTION  = enumerates the com port   ***/
/***  DATE   = 2014/07/11;           ***/
/***  AUTHOR  = wuhaoyong;              ***/
/***  INPUT   = ;               ***/
/***  OUTPUT  = ;               ***/
/***  END OF SPECIFICATIONS;            ***/
/**************************************************************************/
int CCommLayer::SelectComPort(void)
{
	////TRACE(_T("SelectComPort\n"));
    BOOL m_bReturnvalue;
    CString comportname;
    num--;
    if(-1==num ||0xFFFFFFFF==num)
    {
        return 2;//no valid com port
    }
    //try initial,连接当前端口成功，发送验证码
    m_bReturnvalue=m_SerialPort.InitPort(SubKey[num].SubKeyValue);
    ////TRACE(_T("Initial %s\n"),SubKey[num].SubKeyValue);

    if(TRUE == m_bReturnvalue)
    {
        //连接当前端口成功
        if(m_SerialPort.StartMonitoring())
        {
            return 0;
        }
        else
        {
            //the MS is FAIL
            m_SerialPort.ClosePort();//关闭串口
            m_bConnectEffective=FALSE;
            return 1;
        }
    }
    else
    {
        return 1;
    }
    return 0;
}

/**************************************************************************/
/***  specifications;              ***/
/***  NAME   = SendVerification;       ***/
/***  FUNCTION  = send verification data  ***/
/***  DATE   = 2014/07/11;           ***/
/***  AUTHOR  = wuhaoyong;              ***/
/***  INPUT   = ;               ***/
/***  OUTPUT  = ;               ***/
/***  END OF SPECIFICATIONS;            ***/
/**************************************************************************/
int CCommLayer::SendVerification(void)
{
	UINT8 sendStr[ ] = {'L','Q','S','K'};
	sendDataSize = GenerateSendData(sendStr,4);
    if(sendDataSize>0)
    {
        TransData((BYTE *)&sendCmd,sendDataSize);
    }
    else
    {
		return 1;
	}
    return 0;
}
/**************************************************************************/
/***  specifications;              ***/
/***  NAME   = SendCommand;       ***/
/***  FUNCTION  = 通信层给上层提供的发送接口  ***/
/***  DATE   = 2014/07/11;           ***/
/***  AUTHOR  = wuhaoyong;              ***/
/***  INPUT   = ;               ***/
/***  OUTPUT  = ;               ***/
/***  END OF SPECIFICATIONS;            ***/
/**************************************************************************/
int CCommLayer::SendCommand(BYTE* outbuff, DWORD dwSize)
{
	sendDataSize = GenerateSendData(outbuff, dwSize);
    if(sendDataSize>6)
    {
        TransData((BYTE *)&sendCmd,sendDataSize);
    }
    else
    {
		return 1;
	}
    return 0;
}
/**************************************************************************/
/***  specifications;              ***/
/***  NAME   = TransData;       ***/
/***  FUNCTION  = send data to the com port  ***/
/***  DATE   = 2014/07/11;           ***/
/***  AUTHOR  = wuhaoyong;              ***/
/***  INPUT   = ;               ***/
/***  OUTPUT  = ;               ***/
/***  END OF SPECIFICATIONS;            ***/
/**************************************************************************/
WORD CCommLayer::TransData(BYTE* outbuff, DWORD dwSize)
{
    WORD returnvalue;
    memset(m_WriteBuffer,0,sizeof(m_WriteBuffer));
	memcpy(m_WriteBuffer,outbuff,dwSize);
	returnvalue=m_SerialPort.WriteToPort(m_WriteBuffer,dwSize);
    //此处不能立即重置发送buffer，因为wirtefile还没有完成，此时重置，
    //会导致发送不成功，因而收不到相应的响应。
    return WORD(returnvalue);
}
/**************************************************************************/
/***  specifications;              ***/
/***  NAME   = RecvData;       ***/
/***  FUNCTION  = receive data from com port  ***/
/***  DATE   = 2014/07/11;           ***/
/***  AUTHOR  = wuhaoyong;              ***/
/***  INPUT   = ;               ***/
/***  OUTPUT  = ;               ***/
/***  END OF SPECIFICATIONS;            ***/
/**************************************************************************/
WORD CCommLayer::RecvData(BYTE* inbuff, WORD dwSize)
{
    BYTE localReceiveBuff[4*COMM_BUFFER_BASESIZE];     //接收到的原始数据的缓冲
    BOOL bEndPacket = TRUE;  //数据尾
    m_wlocalReceivePtr = 0;
    m_ReceiveBufferSize=0;
    memset(m_ReceiveBuff,0,sizeof(m_ReceiveBuff));
    memset(localReceiveBuff, 0, 4*COMM_BUFFER_BASESIZE);
	memset(m_ReceiveBuff, 0, 4*COMM_BUFFER_BASESIZE);
    memcpy(localReceiveBuff, inbuff, dwSize);
    //解包并做校验
    //while(bEndPacket == TRUE)
    {
		////TRACE(_T("CCommLayer::RecvData () dwSize = %02X \n"),dwSize);
		bEndPacket = CrcCheck(localReceiveBuff,dwSize);
        if(bEndPacket == TRUE)
        {
			if(GetConnectType() == TYPE_COMM)
			{
				memcpy(m_ReceiveBuff,&localReceiveBuff[0],dwSize);
				m_bConnectEffective = true;
				g_event.SetEvent();
#if 0
				TRACE0("CCommLayer RX = ");
				////TRACE(_T(" %02X\n"),dwSize);
				for(DWORD cont=0; cont < dwSize; cont++)
				{
					////TRACE(_T(" %02X"),inbuff[cont]);
				}
				TRACE0("\n");
#endif
				::SendMessage(fatherHwnd,WM_USER_RECEIVEDATA, dwSize, 0x0000);
			}
			else if(GetConnectType() == TYPE_INIT)
			{
				SetConnectType(TYPE_COMM);
				//判断返回值是否：LQRD
				if(localReceiveBuff[0] == '$' && localReceiveBuff[1] == 'L'
					&& localReceiveBuff[2] == 'Q'&& localReceiveBuff[3] == 'R'
					&& localReceiveBuff[2] == 'D' )
				{
					isNewData = true;
					memcpy(m_ReceiveBuff,&localReceiveBuff[0],dwSize);
					m_bConnectEffective = true;
					::SendMessage(fatherHwnd,WM_USER_RECEIVEDATA, dwSize, 0x0000);
				}
				else
				{
					isNewData = false;
					memcpy(m_ReceiveBuff,&localReceiveBuff[0],dwSize);
					m_bConnectEffective = true;
					g_event.SetEvent();
					::SendMessage(fatherHwnd,WM_USER_RECEIVEDATA, dwSize, 0x0000);
					}
					g_event.SetEvent();
			}
			else
			{
			}
        }
		else
		{
			if(GetConnectType() == TYPE_COMM)
			{
				//数据包解码错误
				g_event.SetEvent();
				::SendMessage(fatherHwnd,WM_USER_RECEIVEDATA, 0, 0x0001);
				return 1;
			}
			else if(GetConnectType() == TYPE_INIT)
			{
				m_bConnectEffective = false;
				g_event.SetEvent();
			}
			else
			{
			}		
		}
    }
    return WORD(dwSize);
}
/**************************************************************************/
/***  specifications;              ***/
/***  NAME   = CheckReceivePacketStatus;       ***/
/***  FUNCTION  = check crc of receive data   ***/
/***  DATE   = 2014/07/11;           ***/
/***  AUTHOR  = wuhaoyong;              ***/
/***  INPUT   = ;               ***/
/***  OUTPUT  = ;               ***/
/***  END OF SPECIFICATIONS;            ***/
/**************************************************************************/
bool CCommLayer::CheckReceivePacketStatus(BYTE *pbBuff, WORD *wSize)
{
	return true;   
}

/**************************************************************************/
/***  specifications;              ***/
/***  NAME   = ChangeCStringToWORD;       ***/
/***  FUNCTION  = 针对组号，将字符串转为数字 ***/
/***  DATE   = 2014/07/11;           ***/
/***  AUTHOR  = wuhaoyong;              ***/
/***  INPUT   = ;               ***/
/***  OUTPUT  = ;               ***/
/***  END OF SPECIFICATIONS;            ***/
/**************************************************************************/
WORD CCommLayer::ChangeCStringToWORD (CString strChange)
{
    CString strTemp;
    WORD dwSum = 0;
    int nCharLength = strChange.GetLength ();
    for (int nTempCount = 0; nTempCount < nCharLength; nTempCount++)
    {
        if (strChange.GetAt (nTempCount) != ' ')
        {
            strTemp += strChange.GetAt (nTempCount);
        }
    }

    nCharLength = strTemp.GetLength ();
    if (nCharLength > 0)
    {
        dwSum = 0;
        for (int nTempCount = nCharLength; nTempCount > 0; nTempCount--)
        {
            dwSum = WORD(dwSum + (strTemp.GetAt (nCharLength - nTempCount) - 48) * pow ((float)10, (int)(nTempCount - 1)));
        }
    }
    return dwSum;
}


/**************************************************************************/
/***  specifications;              ***/
/***  NAME   = ChangeCStringToDWORD;       ***/
/***  FUNCTION  = 针对组号，将字符串转为数字 ***/
/***  DATE   = 2014/07/11;           ***/
/***  AUTHOR  = wuhaoyong;              ***/
/***  INPUT   = ;               ***/
/***  OUTPUT  = ;               ***/
/***  END OF SPECIFICATIONS;            ***/
/**************************************************************************/
DWORD CCommLayer::ChangeCStringToDWORD (CString strChange)
{
    CString strTemp;
    DWORD dwSum = 0;
    int nCharLength = strChange.GetLength ();
    for (int nTempCount = 0; nTempCount < nCharLength; nTempCount++)
    {
        if (strChange.GetAt (nTempCount) != ' ')
        {
            strTemp += strChange.GetAt (nTempCount);
        }
    }

    nCharLength = strTemp.GetLength ();
    if (nCharLength > 0)
    {
        dwSum = 0;
        for (int nTempCount = nCharLength; nTempCount > 0; nTempCount--)
        {
            dwSum = DWORD(dwSum + (strTemp.GetAt (nCharLength - nTempCount) - 48) * pow ((float)10, (int)(nTempCount - 1)));
        }
    }
    return dwSum;
}

 /*
*	buf字符串字头为  $   发出的测量数据
*
*/
UINT8 CCommLayer::CrcCheck(UINT8 *buf)
{
	UINT8 i,crc,tcrc[2];
	crc = 0;

	for(i = 1;;i++)//因为buf[0]='$'，所以从1开始
	{
		if(*(buf+i) != '*') 
		{
			crc = crc + *(buf+i);
		}
		else 
		{
			tcrc[0] = crc % 16;
			tcrc[1] = crc / 16;
			if(tcrc[0] <= 9) tcrc[0] = 0x30 + tcrc[0];
			else tcrc[0] = 0x40 + tcrc[0] - 9;
			if(tcrc[1] <= 9) tcrc[1] = 0x30 + tcrc[1];
			else tcrc[1] = 0x40 + tcrc[1] - 9;
			break;
		}
	}

	if((*(buf+i+1) == tcrc[1]) && (*(buf+i+2) == tcrc[0])) 	return 0;//校验通过
	else return 1; //校验出错

} 
bool CCommLayer::CrcCheck(UINT8 *buf, WORD dwSize)
{
	UINT8 i,crc,tcrc[2];
	crc = 0;

	for(i = 1;i<dwSize;i++)//因为buf[0]='$'，所以从1开始
	{
		if(*(buf+i) != '*') 
		{
			crc = crc + *(buf+i);
		}
		else 
		{
			tcrc[0] = crc % 16;
			tcrc[1] = crc / 16;
			if(tcrc[0] <= 9) tcrc[0] = 0x30 + tcrc[0];
			else tcrc[0] = 0x40 + tcrc[0] - 9;
			if(tcrc[1] <= 9) tcrc[1] = 0x30 + tcrc[1];
			else tcrc[1] = 0x40 + tcrc[1] - 9;
			break;
		}
	}

	if((*(buf+i+1) == tcrc[1]) && (*(buf+i+2) == tcrc[0])) 	return true;//校验通过
	else return false; //校验出错

}
int CCommLayer::GenerateSendData(UINT8 *buf, int size)
{
	memset(sendCmd,0,sizeof(UINT8)*COMM_BUFFER_BASESIZE);
	*(sendCmd+0) = '$';
	UINT8 i = 0;
	UINT8 crc;
	UINT8 tcrc[2] = {0,0};
	crc = 0;

	for(i = 0;i<size;i++)
	{
		crc = crc + *(buf+i);
		*(sendCmd+1+i) = *(buf+i);
	}
	*(sendCmd+1+i) = '*';
	tcrc[0] = crc % 16;
	tcrc[1] = crc / 16;
	if(tcrc[0] <= 9)
	{
		tcrc[0] = 0x30 + tcrc[0];
	}
	else 
	{
		tcrc[0] = 0x40 + tcrc[0] - 9;
	}
	if(tcrc[1] <= 9) 
	{
		tcrc[1] = 0x30 + tcrc[1];
	}
	else 
	{
		tcrc[1] = 0x40 + tcrc[1] - 9;
	}
	*(sendCmd+i+2) = tcrc[1];
	*(sendCmd+i+3) = tcrc[0];
	*(sendCmd+i+4) = '\r';
	*(sendCmd+i+5) = '\n';
	return i+5+1;
}
