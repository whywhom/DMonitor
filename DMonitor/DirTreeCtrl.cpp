#include "stdafx.h"
#include "DirTreeCtrl.h"
#include "SortStringArray.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
CDirTreeCtrl::CDirTreeCtrl()
{
	m_strRoot = "";      // 对根目录赋初值
}
CDirTreeCtrl::~CDirTreeCtrl()
{
	m_imgList.Detach();// 释放图标资源
}
BEGIN_MESSAGE_MAP(CDirTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CDirTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemexpanded)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
BOOL CDirTreeCtrl::DisplayTree(LPCTSTR strRoot, BOOL bFiles)
{
	DWORD dwStyle = GetStyle();   //读取树型控件样式
	if ( dwStyle & TVS_EDITLABELS ) 
	{
		// 不允许编辑
		ModifyStyle( TVS_EDITLABELS , 0 );
	}	
	// 显示根目录如C:\ 如果参数 Rootname == NULL就显示所有的盘符
	DeleteAllItems();
	if ( !GetSysImgList() ) //得到系统图标
		return FALSE;
	m_bFiles = bFiles;  //是否显示文件 TRUE显示 FALSE不显示 
	if ( strRoot == NULL || strRoot[0] == '\0' )
	{
		if ( !DisplayDrives() )
			return FALSE;
		m_strRoot = "";
	}
	else
	{
		m_strRoot = strRoot;
		if ( m_strRoot.Right(1) != '\\' )
			m_strRoot += "\\";
		HTREEITEM hParent = AddItem( TVI_ROOT, m_strRoot );
		DisplayPath( hParent, strRoot );
	}
	return TRUE;	
}
BOOL CDirTreeCtrl::GetSysImgList()//得到系统图标
{
	SHFILEINFO shFinfo;
	HIMAGELIST hImgList = NULL;
	if ( GetImageList( TVSIL_NORMAL ) )
		m_imgList.Detach();	
	hImgList = (HIMAGELIST)SHGetFileInfo( _T("C:\\"), 0, &shFinfo, sizeof( shFinfo ), SHGFI_SYSICONINDEX | SHGFI_SMALLICON );
	if ( !hImgList )
	{
		m_strError = "Cannot retrieve the Handle of SystemImageList!";
		return FALSE;
	}
	m_imgList.m_hImageList = hImgList;       
	SetImageList( &m_imgList, TVSIL_NORMAL );
	return TRUE;   // OK
}
BOOL CDirTreeCtrl::DisplayDrives()//显示所有可用的盘符
{	
	DeleteAllItems();
	TCHAR  szDrives[128];
	TCHAR* pDrive;
	if ( !GetLogicalDriveStrings( sizeof(szDrives), szDrives ) )
	{
		m_strError = "Error Getting Logical DriveStrings!";
		return FALSE;
	}
	pDrive = szDrives;
	while( *pDrive )
	{
		HTREEITEM hParent = AddItem( TVI_ROOT, pDrive );
		if ( FindSubDir( pDrive ) )
			InsertItem(_T( ""), 0, 0, hParent );
		pDrive += lstrlen( pDrive ) + 1;
	}
	return TRUE;
}
void CDirTreeCtrl::DisplayPath(HTREEITEM hParent, LPCTSTR strPath) //显示路径
{
	CFileFind find;
	CString   strPathFiles = strPath;
	BOOL      bFind;
	CSortStringArray strDirArray;
	CSortStringArray strFileArray;	
	if ( strPathFiles.Right(1) != "\\" )
		strPathFiles += "\\";
	strPathFiles += "*.tools";
	bFind = find.FindFile( strPathFiles );
	while ( bFind )
	{
		bFind = find.FindNextFile();
		if ( find.IsDirectory() && !find.IsDots() )
		{		
			strDirArray.Add( find.GetFilePath() );
		}
		if ( !find.IsDirectory() && m_bFiles )
			strFileArray.Add( find.GetFilePath() );
	}    
	strDirArray.Sort();
	SetRedraw( FALSE );
	CWaitCursor wait;
	int i;
	for (  i = 0; i < strDirArray.GetSize(); i++ )
	{
		HTREEITEM hItem = AddItem( hParent, strDirArray.GetAt(i) );
		if ( FindSubDir( strDirArray.GetAt(i) ) )
			InsertItem(_T( ""), 0, 0, hItem );
	}
	if ( m_bFiles )
	{
		strFileArray.Sort();
		for ( i = 0; i < strFileArray.GetSize(); i++ )
		{
			HTREEITEM hItem = AddItem( hParent, strFileArray.GetAt(i) );			
		}
	}    
	SetRedraw( TRUE );	
}
HTREEITEM CDirTreeCtrl::AddItem(HTREEITEM hParent, LPCTSTR strPath) //添加Item到树型控件
{	
	SHFILEINFO shFinfo;
	int iIcon, iIconSel;
	CString    strTemp = strPath;    
	if ( strTemp.Right(1) != '\\' )
		strTemp += "\\";
	if ( !SHGetFileInfo( strTemp,0,&shFinfo,sizeof( shFinfo ),SHGFI_ICON |SHGFI_SMALLICON ) )
	{	m_strError = "Error Gettting SystemFileInfo!";
	return NULL;
	}
	iIcon = shFinfo.iIcon; //得到图标
	DestroyIcon( shFinfo.hIcon );
	if ( !SHGetFileInfo( strTemp,0,&shFinfo,sizeof( shFinfo ),SHGFI_ICON | SHGFI_OPENICON |SHGFI_SMALLICON ) )
	{		m_strError = "Error Gettting SystemFileInfo!";
	return NULL;
	}
	iIconSel = shFinfo.iIcon; //得到选中图标
	DestroyIcon( shFinfo.hIcon ); 
	if ( strTemp.Right(1) == "\\" )
		strTemp.SetAt( strTemp.GetLength() - 1, '\0' );	
	if ( hParent == TVI_ROOT )
		return InsertItem( strTemp, iIcon, iIconSel, hParent );	
	return InsertItem( GetSubPath( strTemp ), iIcon, iIconSel, hParent );
}
LPCTSTR CDirTreeCtrl::GetSubPath(LPCTSTR strPath) //得到子目录如：C:\temp\readme.txt 则返回result = readme.txt
{	 
	static CString strTemp;
	int     iPos;
	strTemp = strPath;
	if ( strTemp.Right(1) == '\\' )
		strTemp.SetAt( strTemp.GetLength() - 1, '\0' );
	iPos = strTemp.ReverseFind( '\\' );
	if ( iPos != -1 )
		strTemp = strTemp.Mid( iPos + 1);
	return (LPCTSTR)strTemp;
}
BOOL CDirTreeCtrl::FindSubDir( LPCTSTR strPath) //发现子目录
{
	CFileFind find;
	CString   strTemp = strPath;
	BOOL      bFind;
	if ( strTemp[strTemp.GetLength()-1] == '\\' )
		strTemp += "*.*";
	else
		strTemp += "\\*.*";		
	bFind = find.FindFile( strTemp );	
	while ( bFind )
	{
		bFind = find.FindNextFile();
		if ( find.IsDirectory() && !find.IsDots() )
		{
			return TRUE;
		}
		if ( !find.IsDirectory() && m_bFiles && !find.IsHidden() )
			return TRUE;		
	}
	return FALSE;
}
void CDirTreeCtrl::OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	CString strPath;	 
	if ( pNMTreeView->itemNew.state & TVIS_EXPANDED )
	{
		ExpandItem( pNMTreeView->itemNew.hItem, TVE_EXPAND );	    
	}
	else
	{		
		HTREEITEM hChild = GetChildItem( pNMTreeView->itemNew.hItem );			
		while ( hChild ) 
		{
			DeleteItem( hChild );
			hChild = GetChildItem( pNMTreeView->itemNew.hItem );
		}
		InsertItem( _T(""), pNMTreeView->itemNew.hItem );
	}
	*pResult = 0;
}
CString CDirTreeCtrl::GetFullPath(HTREEITEM hItem)
{
	CString strReturn;
	CString strTemp;
	HTREEITEM hParent = hItem;
	strReturn = "";
	while ( hParent )
	{		
		strTemp  = GetItemText( hParent );
		strTemp += "\\";
		strReturn = strTemp + strReturn;
		hParent = GetParentItem( hParent );
	}    
	strReturn.TrimRight( '\\' );
	return strReturn;
}
BOOL CDirTreeCtrl::SetSelPath(LPCTSTR strPath)
{
	HTREEITEM hParent  = TVI_ROOT;
	int       iLen    = lstrlen(strPath) + 2;
	char*     pszPath = new char[iLen];
	char*     pPath   = pszPath;
	BOOL      bRet    = FALSE;    
	if ( !IsValidPath( strPath ) )
	{
		delete [] pszPath; // this must be added 29.03.99
		return FALSE;
	}		
	strcpy( pszPath, (char*)strPath );
	strupr( pszPath );	
	if ( pszPath[strlen(pszPath)-1] != '\\' )
		lstrcat((LPWSTR) pszPath, _T("\\") );    
	int iLen2 = strlen( pszPath );	
	for (WORD i = 0; i < iLen2; i++ )
	{
		if ( pszPath[i] == '\\' )
		{
			SetRedraw( FALSE );
			pszPath[i] = '\0';
			hParent = SearchSiblingItem( hParent, (LPCTSTR)pPath );
			if ( !hParent ) 
				break;
			else
			{	
				UINT uState;
				uState = GetItemState( hParent, TVIS_EXPANDEDONCE );
				if ( uState )
				{
					Expand( hParent, TVE_EXPAND );
					Expand( hParent, TVE_COLLAPSE | TVE_COLLAPSERESET );
					InsertItem(_T(""), hParent ); 
					Expand( hParent, TVE_EXPAND ); 
				}
				else
					Expand( hParent, TVE_EXPAND );
			}
			pPath += strlen(pPath) + 1;
		}
	}
	delete [] pszPath;	
	if ( hParent ) 
	{		
		SelectItem( hParent ); 
		bRet = TRUE;
	}
	else
	{
		bRet = FALSE;
	}	
	SetRedraw( TRUE );
	return bRet;
}
HTREEITEM CDirTreeCtrl::SearchSiblingItem( HTREEITEM hItem, LPCTSTR strText)
{
	HTREEITEM hFound = GetChildItem( hItem );
	CString   strTemp;
	while ( hFound )
	{
		strTemp = GetItemText( hFound );
		strTemp.MakeUpper();
		if ( strTemp == strText )
			return hFound;
		hFound = GetNextItem( hFound, TVGN_NEXT );
	}
	return NULL;
}

void CDirTreeCtrl::ExpandItem(HTREEITEM hItem, UINT nCode)
{	
	CString strPath;

	if ( nCode == TVE_EXPAND )
	{
		HTREEITEM hChild = GetChildItem( hItem );
		while ( hChild )
		{
			DeleteItem( hChild );
			hChild = GetChildItem( hItem );
		}        
		strPath = GetFullPath( hItem );
		DisplayPath( hItem, strPath );
	}
}
BOOL CDirTreeCtrl::IsValidPath(LPCTSTR strPath)
{
	// This function check the Pathname

	HTREEITEM hChild;
	CString   strItem;
	CString   strTempPath = strPath;
	BOOL      bFound = FALSE;
	CFileFind find;
	hChild = GetChildItem( TVI_ROOT );
	strTempPath.MakeUpper();
	strTempPath.TrimRight('\\');
	while ( hChild )
	{
		strItem = GetItemText( hChild );
		strItem.MakeUpper();
		if ( strItem == strTempPath.Mid( 0, strItem.GetLength() ) )
		{
			bFound = TRUE;
			break;
		}
		hChild = GetNextItem( hChild, TVGN_NEXT );
	}    
	if ( !bFound )
		return FALSE;
	strTempPath += "\\nul";
	if ( find.FindFile( strTempPath ) )
		return TRUE;     
	return FALSE;
}
