#pragma once
#include "resource.h"
#include "afxwin.h"

// CSetBlockCount dialog

class CSetBlockCount : public CDialog
{
	DECLARE_DYNAMIC(CSetBlockCount)

public:
	CSetBlockCount(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetBlockCount();

// Dialog Data
	enum { IDD = IDD_SETBLOCKCOUNT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int c_value1;
	int c_value2;
	bool iscount;
public:
	virtual BOOL OnInitDialog();
	CStatic c_name1;
	CStatic c_name2;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedDefaults();
};
