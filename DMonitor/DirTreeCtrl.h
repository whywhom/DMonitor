#pragma once
#pragma warning(disable : 4996)
#include "afxcmn.h"
class CDirTreeCtrl :
	public CTreeCtrl
{
public:
	CDirTreeCtrl();
public:
	BOOL SetSelPath( LPCTSTR strPath );
	CString GetFullPath( HTREEITEM hItem );
	LPCTSTR GetSubPath( LPCTSTR strPath );
	BOOL DisplayTree( LPCTSTR strRoot, BOOL bFiles = FALSE );
	BOOL FindSubDir( LPCTSTR strPath );
	HTREEITEM AddItem( HTREEITEM hParent, LPCTSTR strPath );
	virtual ~CDirTreeCtrl();
protected:
	BOOL IsValidPath( LPCTSTR strPath );
	void ExpandItem( HTREEITEM hItem, UINT nCode );
	HTREEITEM SearchSiblingItem( HTREEITEM hItem, LPCTSTR strText );
	//BOOL FindSubDir( LPCTSTR strPath );
	//HTREEITEM AddItem( HTREEITEM hParent, LPCTSTR strPath );
	void DisplayPath( HTREEITEM hParent, LPCTSTR strPath );
	BOOL DisplayDrives();
	BOOL m_bFiles;
	CString m_strError;
	BOOL GetSysImgList();
	CImageList m_imgList;
	CString m_strRoot;
	//{{AFX_MSG(CDirTreeCtrl)
	afx_msg void OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

