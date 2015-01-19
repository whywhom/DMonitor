
// DMonitor.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "DMonitor.h"
#include "DMonitorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDMoniterApp

BEGIN_MESSAGE_MAP(CDMoniterApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDMoniterApp 构造
static HINSTANCE _hLangDLL = NULL;
CDMoniterApp::CDMoniterApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CDMoniterApp 对象

CDMoniterApp theApp;


// CDMoniterApp 初始化

BOOL CDMoniterApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("DMonitor"));
	/*wuhaoyong add CMutex*/
    //Creat CMutex
    hSem=NULL;
	strSemaphore.LoadString( IDS_SEMAPHORE );
    hSem=CreateSemaphore(NULL,1,1,strSemaphore);
    if(hSem)  //Creat CMutex success
    {
        //the CMutex exist
        if(ERROR_ALREADY_EXISTS==GetLastError())
        {
			strSemaphoreExist.LoadString( IDS_SEMAPHORE_ALREADY_EXISTS );
            AfxMessageBox(strSemaphoreExist);
            CloseHandle(hSem);      //Close CMutex
            return FALSE;           //Exit App
        }
    }
    else
    {
		strSemaphoreCreatFail.LoadString(IDS_SEMAPHORE_CREATE_FAIL);
        AfxMessageBox(strSemaphoreCreatFail);
        return FALSE;
    }
	exe_hInstance = GetModuleHandle(NULL);//获取hInstance wuhaoyong add
	if(0 == exe_hInstance)
	{
		return FALSE;
	}
	GetModulePath();//必要文件夹初始化
	CDMonitorDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

//根据_hLangDLL是否加载语言dll来判断使用语言库资源还是默认资源，默认为中文简体
CString CDMoniterApp::GetResString(UINT uStringID)
{
	CString resString;
	if (_hLangDLL)
		resString.LoadString(_hLangDLL, uStringID);
	if (resString.IsEmpty())
		resString.LoadString(theApp.exe_hInstance, uStringID);
	return resString;
}

void CDMoniterApp::GetModulePath()
{
	DWORD dwAttr = 0;
	/******
	TCHAR szPath[MAX_PATH];
	if(SUCCEEDED(SHGetFolderPath(NULL, 
									CSIDL_APPDATA, 
									NULL, 
									0, 
									szPath))) 
	{
		//临时文件夹路径
		TempPath = szPath;
		CString backupDir = _T("\\Temp\\");
		TempPath += backupDir;
		dwAttr=GetFileAttributes(TempPath);
		//若文件夹不存在，创建文件夹
		if(dwAttr==0xFFFFFFFF)
		{
			CreateDirectory(TempPath,NULL);
		}
	}
	******/
	TCHAR szModPath[_MAX_PATH] = {0};
	//GetModuleFileName(m_hInstance, szModPath, _MAX_PATH);
	SHGetSpecialFolderPath(NULL, szModPath, CSIDL_APPDATA, FALSE);
    szExePath = szModPath;
	szExePath += _T("\\");
	szExePath += AfxGetApp()->m_pszExeName;
    ModuleFilePath = szExePath;
	dwAttr=GetFileAttributes(ModuleFilePath);
	//若文件夹不存在，创建文件夹
	if(dwAttr==0xFFFFFFFF)
	{
		CreateDirectory(ModuleFilePath,NULL);
	}
	LogPath = ModuleFilePath + _T("\\Log\\");
	dwAttr=GetFileAttributes(LogPath);
	//若文件夹不存在，创建文件夹
	if(dwAttr==0xFFFFFFFF)
	{
		CreateDirectory(LogPath,NULL);
	}

	TempPath = ModuleFilePath + _T("\\Temp\\");
	//若文件夹不存在，创建文件夹
	dwAttr=GetFileAttributes(TempPath);
	if(dwAttr==0xFFFFFFFF)
	{
		CreateDirectory(TempPath,NULL);
	}

	DataPath = ModuleFilePath + _T("\\Data\\");
	//若文件夹不存在，创建文件夹
	dwAttr=GetFileAttributes(DataPath);
	if(dwAttr==0xFFFFFFFF)
	{
		CreateDirectory(DataPath,NULL);
	}

	JobPath = ModuleFilePath + _T("\\Jobs\\");
	//若文件夹不存在，创建文件夹
	dwAttr=GetFileAttributes(JobPath);
	if(dwAttr==0xFFFFFFFF)
	{
		CreateDirectory(JobPath,NULL);
	}

	ToolPath = ModuleFilePath + _T("\\Tools\\");
	//若文件夹不存在，创建文件夹
	dwAttr=GetFileAttributes(ToolPath);
	if(dwAttr==0xFFFFFFFF)
	{
		CreateDirectory(ToolPath,NULL);
	}

	IniFilePath = ModuleFilePath + _T("\\Config\\");
	//若文件夹不存在，创建文件夹
	dwAttr=GetFileAttributes(IniFilePath);
	if(dwAttr==0xFFFFFFFF)
	{
		CreateDirectory(IniFilePath,NULL);
	}

	strUnitsFile = IniFilePath + _T("Units.xml");
	dwAttr=GetFileAttributes(strUnitsFile);
	if(dwAttr==0xFFFFFFFF)
	{
		CreateDmFile(strUnitsFile);
	}

	strIniFilePath = IniFilePath + _T("config.ini");
	dwAttr=GetFileAttributes(strIniFilePath);
	if(dwAttr==0xFFFFFFFF)
	{
		CreateIniFile(strIniFilePath);
	}
#ifdef FEATURE_LOG
	LogFileName = LogPath + _T("log.txt");
#endif
	//绘图模板
	strCurveFile = IniFilePath + _T("workinfo.xml");
	dwAttr=GetFileAttributes(strCurveFile);
	if(dwAttr==0xFFFFFFFF)
	{
		bCurveFileExist = false;
	}
	else
	{
		bCurveFileExist = true;
	}
	return;
}

int CDMoniterApp::CreateIniFile(CString strFile)
{
	::WritePrivateProfileString(_T("TargetDepth"),_T("Depth1"),_T("100"),strFile); 
	::WritePrivateProfileString(_T("TargetDepth"),_T("Depth2"),_T("100"),strFile);
	return 0;
}

int CDMoniterApp::CreateDmFile(CString strFile)
{
	TiXmlDocument doc;
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "UTF-8", "yes" );
	doc.LinkEndChild( decl ); 
	TiXmlElement * element = new TiXmlElement( "Units" );
	////
	LinkElementeFuns(element,_T("mV"));
	LinkElementeFuns(element,_T("GAPI"));
	LinkElementeFuns(element,_T("CPS"));
	LinkElementeFuns(element,_T("us/m"));
	LinkElementeFuns(element,_T("m"));
	LinkElementeFuns(element,_T("cm"));
	LinkElementeFuns(element,_T("mm"));
	LinkElementeFuns(element,_T("uS"));
	LinkElementeFuns(element,_T("mS"));
	LinkElementeFuns(element,_T("S"));
	LinkElementeFuns(element,_T("rm"));
	LinkElementeFuns(element,_T("CCL"));
	LinkElementeFuns(element,_T("mag"));
	LinkElementeFuns(element,_T("MΩ"));
	LinkElementeFuns(element,_T("kΩ"));
	LinkElementeFuns(element,_T("Ω"));
	LinkElementeFuns(element,_T("Ω.m"));
    LinkElementeFuns(element,_T("s"));
    LinkElementeFuns(element,_T("S/m"));
    LinkElementeFuns(element,_T("mS/m"));
    LinkElementeFuns(element,_T("m/h"));
    LinkElementeFuns(element,_T("Kg"));
    LinkElementeFuns(element,_T("Kn"));
    LinkElementeFuns(element,_T("N"));
    LinkElementeFuns(element,_T("℃"));
    LinkElementeFuns(element,_T("℃/m"));
    LinkElementeFuns(element,_T("kg/m^3"));
    LinkElementeFuns(element,_T("g/cm^3"));
    LinkElementeFuns(element,_T("km"));
    LinkElementeFuns(element,_T("km^3"));
    LinkElementeFuns(element,_T("m^3"));
    LinkElementeFuns(element,_T("dm^3"));
    LinkElementeFuns(element,_T("m/s^2"));
    LinkElementeFuns(element,_T("mm/s^2"));
    LinkElementeFuns(element,_T("rad"));
    LinkElementeFuns(element,_T("mrad"));
    LinkElementeFuns(element,_T("urad"));
    LinkElementeFuns(element,_T("°"));
    LinkElementeFuns(element,_T("km^2"));
    LinkElementeFuns(element,_T("ha"));
    LinkElementeFuns(element,_T("dm^2"));
    LinkElementeFuns(element,_T("cm^2"));
    LinkElementeFuns(element,_T("mm^2"));
    LinkElementeFuns(element,_T("kg/s"));
    LinkElementeFuns(element,_T("m^3/s"));
    LinkElementeFuns(element,_T("m^3/min"));
    LinkElementeFuns(element,_T("m^3/d"));
    LinkElementeFuns(element,_T("L/s"));
    LinkElementeFuns(element,_T("Std.m3/m3"));
    LinkElementeFuns(element,_T("t"));
    LinkElementeFuns(element,_T("Mg/m^3"));
    LinkElementeFuns(element,_T("pu"));
    LinkElementeFuns(element,_T("J"));
    LinkElementeFuns(element,_T("Mev"));
    LinkElementeFuns(element,_T("MW"));
    LinkElementeFuns(element,_T("KW"));
    LinkElementeFuns(element,_T("W"));
    LinkElementeFuns(element,_T("Pa"));
    LinkElementeFuns(element,_T("kPa"));
    LinkElementeFuns(element,_T("MPa"));
    LinkElementeFuns(element,_T("ATM"));
    LinkElementeFuns(element,_T("PSI"));
    LinkElementeFuns(element,_T("Bq"));
    LinkElementeFuns(element,_T("r/s"));
    LinkElementeFuns(element,_T("min"));
    LinkElementeFuns(element,_T("h"));
    LinkElementeFuns(element,_T("d"));
    LinkElementeFuns(element,_T("a"));
    LinkElementeFuns(element,_T("m/s"));
    LinkElementeFuns(element,_T("Pa.s"));
    LinkElementeFuns(element,_T("mPa.s"));
    LinkElementeFuns(element,_T("N.s/m^2"));
    LinkElementeFuns(element,_T("%"));
    LinkElementeFuns(element,_T("NAPI"));
    LinkElementeFuns(element,_T("inch"));
    LinkElementeFuns(element,_T("API"));
    LinkElementeFuns(element,_T("V"));
    LinkElementeFuns(element,_T("度"));
    LinkElementeFuns(element,_T("uS/m"));
    LinkElementeFuns(element,_T("ppm"));
    LinkElementeFuns(element,_T("I"));

	doc.LinkEndChild( element );
	////
	char * pFileName = FromUNICODEToANSI(strFile);
	doc.SaveFile(pFileName);

	delete []pFileName;
	pFileName = NULL;
	return 0;
}
void CDMoniterApp::LinkElementeFuns(TiXmlElement * element,CString str)
{
	TiXmlElement* msgs = new TiXmlElement( "Unit" ); 
	element->LinkEndChild( msgs );
	TiXmlElement* msg = new TiXmlElement( "Label" ); 
	////********/////transfer//////********//////
	const int maxBufferSize = 64;
	unsigned short UnicodeStr[maxBufferSize];
	unsigned short utf8StrLen;
	DWORD dwLength;//转换后的UTF－8编码的长度in BYTEs
	char utf8Str[64];
	memset(utf8Str,0,maxBufferSize*sizeof(char));
	memset(UnicodeStr,0,maxBufferSize*sizeof(unsigned short));
	short UnicodeStrLen=2*str.GetLength();
	memcpy(UnicodeStr,str,UnicodeStrLen);
	utf8StrLen=6*UnicodeStrLen;
	memset(utf8Str,0,maxBufferSize*sizeof(char));
	dwLength=theApp.FromUnicodeToUTF8( utf8Str, utf8StrLen, UnicodeStr, UnicodeStrLen);//Unicode to UTF-8
	//////////********///////////
	msg->LinkEndChild( new TiXmlText( utf8Str )); 
	msgs->LinkEndChild( msg ); 
}

/**************************************************************************/
/***  specifications;              ***/
/***  NAME   = FromUNICODEToANSI;       ***/
/***  FUNCTION  = UNICODE转换为ASCII码   ***/
/***  DATE   = 2008/11/18;           ***/
/***  AUTHOR  = wuhaoyong;              ***/
/***  INPUT   = *pData-UNICODE字符串,*nwDataLen-UNICODE字符串有效长度,*pDataLen-转换为ASCII的长度;               ***/
/***  OUTPUT  = *pBuffer-ASCII字符串;               ***/
/***  END OF SPECIFICATIONS;            ***/
/**************************************************************************/
char *CDMoniterApp::FromUNICODEToANSI(CString str)
{
    UINT nCodePage = CP_ACP; //ASCII
	int strLen = str.GetLength();
    int len = WideCharToMultiByte(nCodePage,0,str,strLen,NULL,0,NULL,NULL);
    char * pFileName = new char[len+1];   //以字节为单位
	memset(pFileName,0,len+1);
	//宽字节编码转换成多字节编码
    WideCharToMultiByte(CP_ACP,0,str,str.GetLength(),pFileName,len,NULL,NULL);
    return pFileName;
}

/*===========================================================================
   Function :Utf8 to Unicode
   Param    :   utf8Str        --UTF8 dest code
                    utf8strlen     --max utf8 length
                    unStr          -- Unicode Str Source
                    unMaxlen     --Unicode 最大个数 
   return   :  --实际转化的长度
 
   Author   : 
   Data     : 2002-10-24
===========================================================================*/
short CDMoniterApp::FromUnicodeToUTF8 (LPSTR utf8Str, short utf8StrLen, WORD * unStr, unsigned short unMaxLen)
{
    //short len_dest=0;
    short unlen = 0;            //转化的unicode 长度
    short utflen = 0;           //转化的utf8 长度

    WORD *src;
    src = unStr;
    for (; (unlen <= unMaxLen - 1) && (*src != 0x00) && (utflen <= utf8StrLen);)
    {                           //按照长度、0x00结束
        if (((*src) & 0xff80) == 0) //1byte
        {
            *utf8Str = (char) (*src);
            utflen += 1;
        }
        else if (((*src) & 0xf800) == 0) //2bytes
        {
            *utf8Str = (char) ((((*src) >> 6) & 0x1f) | 0xc0);
            utf8Str++;
            *utf8Str = (char) (((*src) & 0x003f) | 0x80);
            utflen += 2;
        }
        else                    //3bytes
        {
            *utf8Str = (char) ((((*src) >> 12) & 0x000f) | 0xe0);
            utf8Str++;
            *utf8Str = (char) ((((*src) >> 6) & 0x3f) | 0x80);
            utf8Str++;
            *utf8Str = (char) (((*src) & 0x003f) | 0x80);
            utflen += 3;
        }
        unlen++;                
        src++;
        utf8Str++;
    }
    *utf8Str = 0x00;
    return utflen;

}
/*===========================================================================
    Function :Unicode to UTF8
    Param : utf8Str     --UTF8 dest code
    utf8strlen    --max utf8 length
    unStr     -- Unicode Str Source
    unMaxlen  --Unicode 最大个数 
    return :  --实际转化的长度
  
    Author : 
    Data  : 2002-10-24
===========================================================================*/
short CDMoniterApp::FromUTF8ToUnicode (unsigned char *utf8Str, short utf8StrLen, WORD * unStr, unsigned short unMaxLen)
{

    short zen_han, len_dest;
    unsigned char *p_src;
    unsigned char utf8_len = 0;
    len_dest = 0;
    p_src = (unsigned char *) (utf8Str);

    /* limit the total bytes of the *mstr */
    if (utf8StrLen <= 0)
    {
        return (0);
    }

    /* converting at here utf8_len <= utf8StrLen 改为 utf8_len < utf8StrLen*/
    for (; (*p_src != 0x00) && (len_dest <= unMaxLen - 1) && (utf8_len < utf8StrLen);)
    {
        zen_han = Utf8TextBytes ((const unsigned char *) p_src);
        if (zen_han == 1)       //ASCII, just add 0x00 at beginning
        {
            (*unStr) = *(p_src);
            unStr++;
            p_src++;
            utf8_len++;
            len_dest += 1;
        }
        else if (zen_han == 2)
        {
            *unStr = (((((*p_src) >> 2) & (unsigned char) 0x07)) & 0x00ff) << 8;
            *unStr |= ((((*p_src) << 6) | ((*(p_src + 1)) & (unsigned char) 0x3f))) & 0x00ff;
            unStr++;
            p_src += 2;
            utf8_len += 2;
            len_dest += 1;

        }
        else if (zen_han == 3)
        {
            *(unStr) = ((((*(p_src)) << 4) | (((*(p_src + 1)) >> 2) & 0x0f)) & 0x00ff) << 8;

            *unStr |= ((((*(p_src + 1)) << 6) | ((*(p_src + 2)) & (unsigned char) 0x3f))) & 0x00ff;
            unStr++;
            p_src += 3;
            utf8_len += 3;
            len_dest += 1;
        }
        else if (zen_han == 4)  //
        {
            *unStr = (*(p_src)) & 0x7;
            for (int i=1; i<4;i++)
            {
                *unStr <<= 6; // 左移6位后与后续字节的有效位值"位或"赋值
                *unStr = *unStr | ((*(p_src + i)) & 0x3f);//先与后或
            }
            unStr++;
            p_src += 4;
            utf8_len += 4;
            len_dest += 1;
        }
        else if (zen_han == 5)  //
        {
            *unStr = (*(p_src)) & 0x3;
            for (int i=1; i<5;i++)
            {
                *unStr <<= 6; // 左移6位后与后续字节的有效位值"位或"赋值
                *unStr = *unStr | ((*(p_src + i)) & 0x3f);//先与后或
            }
            unStr++;
            p_src += 5;
            utf8_len += 5;
            len_dest += 1;
        }
        else if (zen_han == 6)  //
        {
            *unStr = (*(p_src)) & 0x1;
            for (int i=1; i<6;i++)
            {
                *unStr <<= 6; // 左移6位后与后续字节的有效位值"位或"赋值
                *unStr = *unStr | ((*(p_src + i)) & 0x3f);//先与后或
            }
            unStr++;
            p_src += 6;
            utf8_len += 6;
            len_dest += 1;
        }
        else                    //treated as illegal character, search the next character
        {
            p_src++;
            utf8_len++;
        }
    }
    *(unStr) = 0x0000;
    return (len_dest);

}

/* ===============================================
  Function:  Returns the number of bytes used by the first character of the
 
  string 'mstr'.  For ASCII text this will always return 1.
  当mstr指向0时，或*mstr的第一个字符编码不是有效的UTF-8编码时，返回0
   The table below summarizes the format of these different octet types.
   The letter x indicates bits available for encoding bits of the UCS-4
   character value.(get this table from rfc2279)
 UCS-4 range (hex.)    UTF-8 octet sequence (binary)
 0000 0000-0000 007F   0xxxxxxx
 0000 0080-0000 07FF   110xxxxx 10xxxxxx
 0000 0800-0000 FFFF   1110xxxx 10xxxxxx 10xxxxxx
 0001 0000-001F FFFF   11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
 0020 0000-03FF FFFF   111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
 0400 0000-7FFF FFFF   1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
 
 非法UTF-8初始序列(get this table from internet,this is right?)
 UTF-8序列   非法的原因 
 10xxxxxx   作为字符的起始字节非法(80..BF) 
 1100000x   非法，过长(C0 80..BF) 
 11100000 100xxxxx 非法，过长(E0 80..9F) 
 11110000 1000xxxx 非法，过长(F0 80..8F) 
 11111000 10000xxx 非法，过长(F8 80..87) 
 11111100 100000xx 非法，过长(FC 80..83) 
 1111111x   非法；为规格说明所禁止 
====================================================== */

short CDMoniterApp::Utf8TextBytes (const unsigned char *mstr)
{
    short textbytes = 0;
    if (mstr == 0)
    {                           //Returns 0 if mstr contains a null string or if there is
        return 0;               //no valid character in mstr.
    }
    /* code checking.
       because all unicode used now is lower than 0xffff, only 1~3 bytes UTF-8 has means, 
       the other length will not be dealed with in other functions */
    if (((*mstr) & 0x80) == 0)
    {
        textbytes = 1;          //0xxxxxxx, normal ASCII code
    }
    else if ((((*mstr) & 0xe0) == 0xc0) && (((*(mstr + 1)) & 0xc0) == 0x80))
    {
        if (((*mstr) & 0xfe) == 0xc0) //1100,000x is illegal data,
        {
            textbytes = 0;
        }
        else
        {
            textbytes = 2;      //110xxxxx 10xxxxxx
        }
    }
    else if ((((*mstr) & 0xf0) == 0xe0) && (((*(mstr + 1)) & 0xc0) == 0x80) && (((*(mstr + 2)) & 0xc0) == 0x80))
    {
        if ((*mstr == (char) 0xe0) && (((*(mstr + 1)) & 0xe0) == 0x80)) //1110,0000,100x,xxxx is illegal data
        {
            textbytes = 0;
        }
        else
        {
            textbytes = 3;      //1110xxxx 10xxxxxx 10xxxxxx
        }
    }
    else if ((((*mstr) & 0xf8) == 0xf0) && (((*(mstr + 1)) & 0xc0) == 0x80) && (((*(mstr + 2)) & 0xc0) == 0x80)
             && (((*(mstr + 3)) & 0xc0) == 0x80))
    {
        if (((*mstr) == (char) 0xf0) && (((*(mstr + 1)) & 0xf0) == 0x80)) // 1111,0000,1000,xxxx is illegal data
        {
            textbytes = 0;
        }
        else
        {
            textbytes = 4;      // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        }
    }
    else if ((((*mstr) & 0xfc) == 0xf8) && (((*(mstr + 1)) & 0xc0) == 0x80) &&
             (((*(mstr + 2)) & 0xc0) == 0x80) && (((*(mstr + 3)) & 0xc0) == 0x80) && (((*(mstr + 4)) & 0xc0) == 0x80))
    {
        if ((*mstr == (char) 0xf8) && (((*(mstr + 1)) & 0xf8) == 0x80)) //1111,1000,1000,0xxx is illegal data
        {
            textbytes = 0;
        }
        else
        {
            textbytes = 5;      //111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
        }
    }
    else if ((((*mstr) & 0xfe) == 0xfc) && (((*(mstr + 1)) & 0xc0) == 0x80) &&
             (((*(mstr + 2)) & 0xc0) == 0x80) && (((*(mstr + 3)) & 0xc0) == 0x80) && (((*(mstr + 4)) & 0xc0) == 0x80) &&
             (((*(mstr + 5)) & 0xc0) == 0x80))
    {
        if ((*mstr == (char) 0xfc) && (((*(mstr + 1)) & 0xfc) == 0x80)) //1111,1100,1000,00xx is illegal data
        {
            textbytes = 0;
        }
        else
        {
            textbytes = 6;      //1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
        }
    }
    else
    {
        textbytes = 0;          //illegal formal, return 0
    }

    return textbytes;
}
int CDMoniterApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}
