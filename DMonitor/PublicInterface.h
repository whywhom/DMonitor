#pragma once
//ͨ�Ų�
//�ṩ�ӿں����Ӳ���
//20140707
#include "stdafx.h"		// ������

#define COMM_BUFFER_BASESIZE 1024

//��Ϣ���Ͷ���
#define WM_USER_RECEIVEDATA (WM_USER+7)
#define WM_CONNECT_ERR      (WM_USER+8)
#define WM_CONNECT_OK      (WM_USER+9)
#define WM_JOBLOAD_OK      (WM_USER+10)

#define FEATURE_C_LANGUAGE
//��������
const DWORD COMM_SUCCESS=0x0000;//����ִ�гɹ�
const DWORD COMM_ERROE_PARA=0xF001;//�����������
const DWORD COMM_ERROE_TIMEOUT=0xF002;//ִ�к�����ʱ
const DWORD COMM_ERROE_UNINITIAL=0xF101;//ִ��ʧ�ܣ�δ��ʼ��
const DWORD COMM_ERROE_NO_DRIVER=0xF102;//ִ��ʧ�ܣ���Ӧ��Դ����������û�а�װ����������
const DWORD COMM_ERROE_RELEASE_FAIL=0xF103;//�ͷ���Դʧ��
const DWORD COMM_ERROE_NO_HARDWARE=0xF201;//�����ߡ����⡢������Ӳ��������û�а�װ
const DWORD COMM_ERROE_HARDWARE_CONNECT_FAIL=0xF202;//Ӳ��������޷����ӣ������²�������������Ӧ����
const DWORD COMM_ERROE_OPERATE_AGAIN=0xF301;//���ִ��������²���
const DWORD COMM_ERROE_DELETE_FAIL=0xF306;//ɾ�����ִ���
const DWORD COMM_ERROE_WRITE_FAIL=0xF307;//д����ִ���
const DWORD COMM_ERROE_DRIVER_FAIL=0xF401;//��װ����ʧ��
const DWORD COMM_ERROE_DRIVER_EXIST=0xF402;//�Ѿ���װ������
const DWORD COMM_ERROE_MALOCMEM_FAIL=0xF501;//����ռ�ʧ��
const DWORD COMM_ERROE_RELEASEMEM_FAIL=0xF502;//�ͷſռ�ʧ��
const DWORD COMM_ERROE_CANCEL=0xEEE1;//ȡ������


typedef struct _SEND_COMMAND_LIST
{
    CString cmd;
    UINT8* buf;
    DWORD size;
}SEND_COMMAND_LIST;

typedef struct _DATA_PART
{
	double iData;
	double iDeptData;//��¼���
	CString strData;
	CString strTag;//��¼��������
	CString strUnit;//��¼���ߵ�λ
	bool bAssign;
	int subIndex;//һ������tag��Ӧ�������ʱ����¼����id�����������������������
}DATA_PART;

typedef struct _DATA_TEMP
{
	double dy;
	double dx;
	CString strDx;//���������ݵ��ַ���
	CString strTag;//���Ա����ı�ʾ��DEPT,TEMP��
	bool bAssign;
	int subIndex;
}DATA_TEMP;

#define TIMER_CMD_DRAW 0x20
#define TIMER_CMD_TEST 0x21

#define TIME_REFRESH_REALTIME	1000
#define TIME_REFRESH_FILE	10

#define NO_PROCESSING 0x0
#define REALTIME_PROCESSING 0x1
#define FILEDATA_PROCESSING 0x2

#define FEATURE_TEMP
#define FEATURE_GR
#define FEATURE_RM
#define FEATURE_CCL
#define FEATURE_MAG
