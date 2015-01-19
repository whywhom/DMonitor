#pragma once
//通信层
//提供接口和连接操作
//20140707
#include "stdafx.h"		// 主符号

#define COMM_BUFFER_BASESIZE 1024

//消息类型定义
#define WM_USER_RECEIVEDATA (WM_USER+7)
#define WM_CONNECT_ERR      (WM_USER+8)
#define WM_CONNECT_OK      (WM_USER+9)
#define WM_JOBLOAD_OK      (WM_USER+10)

#define FEATURE_C_LANGUAGE
//错误类型
const DWORD COMM_SUCCESS=0x0000;//函数执行成功
const DWORD COMM_ERROE_PARA=0xF001;//传入参数错误
const DWORD COMM_ERROE_TIMEOUT=0xF002;//执行函数超时
const DWORD COMM_ERROE_UNINITIAL=0xF101;//执行失败，未初始化
const DWORD COMM_ERROE_NO_DRIVER=0xF102;//执行失败，相应资源不完整或者没有安装必需驱动等
const DWORD COMM_ERROE_RELEASE_FAIL=0xF103;//释放资源失败
const DWORD COMM_ERROE_NO_HARDWARE=0xF201;//数据线、红外、蓝牙等硬件适配器没有安装
const DWORD COMM_ERROE_HARDWARE_CONNECT_FAIL=0xF202;//硬件适配等无法连接，请重新操作或者配置相应功能
const DWORD COMM_ERROE_OPERATE_AGAIN=0xF301;//出现错误，请重新操作
const DWORD COMM_ERROE_DELETE_FAIL=0xF306;//删除出现错误
const DWORD COMM_ERROE_WRITE_FAIL=0xF307;//写入出现错误
const DWORD COMM_ERROE_DRIVER_FAIL=0xF401;//安装驱动失败
const DWORD COMM_ERROE_DRIVER_EXIST=0xF402;//已经安装过驱动
const DWORD COMM_ERROE_MALOCMEM_FAIL=0xF501;//申请空间失败
const DWORD COMM_ERROE_RELEASEMEM_FAIL=0xF502;//释放空间失败
const DWORD COMM_ERROE_CANCEL=0xEEE1;//取消操作


typedef struct _SEND_COMMAND_LIST
{
    CString cmd;
    UINT8* buf;
    DWORD size;
}SEND_COMMAND_LIST;

typedef struct _DATA_PART
{
	double iData;
	double iDeptData;//记录深度
	CString strData;
	CString strTag;//记录曲线名称
	CString strUnit;//记录曲线单位
	bool bAssign;
	int subIndex;//一个数据tag对应多个数据时，记录数据id，例如磁三分量有三个数据
}DATA_PART;

typedef struct _DATA_TEMP
{
	double dy;
	double dx;
	CString strDx;//横坐标数据的字符串
	CString strTag;//测试变量的标示，DEPT,TEMP等
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
