#pragma once

#ifndef __SERIALPORT_H__
#define __SERIALPORT_H__
#include "PublicInterface.h"

#define WM_COMM_DSR_DETECTED  WM_USER+1 // The DSR (data-set-ready) signal changed state.
#define WM_COMM_RXCHAR    WM_USER+2 // A character was received and placed in the input buffer.

extern UINT SerialThreadProc1(LPVOID pParam);

class CSerialPort
{
public:
    CSerialPort(void);
	virtual ~CSerialPort(void);
public:
	BOOL    m_bThreadAlive;
	// thread
    CWinThread*   m_Thread;
	CWinThread*   m_MonitorThread;
public:
    DWORD m_nWriteSize;

    void ClosePort();
    // port initialisation
    BOOL  InitPort(LPCTSTR pCommPort, UINT baud = 115200, BYTE parity = NOPARITY, UINT databits = 8, UINT stopbits = 1, DWORD dwCommEvents = EV_RXCHAR|EV_DSR);
    HANDLE    m_hComm;
    // start/stop comm watching
    BOOL  StartMonitoring();
    BOOL  RestartMonitoring();
    BOOL  StopMonitoring();
    DWORD  GetWriteBufferSize();
    DWORD  GetCommEvents();
    DCB   GetDCB();
    WORD  WriteToPort(BYTE* string,DWORD n);
protected:
    // protected memberfunctions
    void  ProcessErrorMessage(WORD ErrorTag);
    static UINT CommThread(LPVOID pParam);
#if 0
	static UINT SerialMonitorThread(LPVOID pParam);
#endif
    static void ReceivePort(CSerialPort* port, COMSTAT comstat);
    static void WriteData(CSerialPort* port);
    
    // synchronisation objects
    CRITICAL_SECTION m_csCommunicationSync;
    
    // handles
    HANDLE    m_hWriteEvent;
    HANDLE    m_hShutdownEvent;
    // Event array.
    // One element is used for each event. There are two event handles for each port.
    // A Write event and a receive character event which is located in the overlapped structure (m_ov.hEvent).
    // There is a general shutdown when the port is closed.
    HANDLE    m_hEventArray[3];
    // structures
    OVERLAPPED   m_ov;
    COMMTIMEOUTS  m_CommTimeouts;
    DCB     m_dcb;
    // owner window
    CWnd*    m_pOwner;
    // misc
    CString    m_nPortNr;
    BYTE    m_szWriteBuffer[4*1024];//send buffer
    DWORD    m_nWriteBufferSize;
	DWORD    m_dwCommEvents;
};
#endif __SERIALPORT_H__