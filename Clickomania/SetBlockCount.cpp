// SetBlockCount.cpp : implementation file
//

#include "stdafx.h"
#include "Clickomania.h"
#include "SetBlockCount.h"
#include "afxdialogex.h"
#include "ClickomaniaDoc.h"


// CSetBlockCount dialog

IMPLEMENT_DYNAMIC(CSetBlockCount, CDialog )

CSetBlockCount::CSetBlockCount(CWnd* pParent /*=NULL*/)
	: CDialog(CSetBlockCount::IDD, pParent)
	, c_value1(0)
	, c_value2(0)
	, iscount(TRUE)
{

}

CSetBlockCount::~CSetBlockCount()
{
}

void CSetBlockCount::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, c_value1);
	DDV_MinMaxInt(pDX, c_value1, 10, 10000);
	DDX_Text(pDX, IDC_EDIT2, c_value2);
	DDV_MinMaxInt(pDX, c_value2, 10, 10000);
	DDX_Control(pDX, IDC_TEXT1, c_name1);
	DDX_Control(pDX, IDC_TEXT2, c_name2);
}


BEGIN_MESSAGE_MAP(CSetBlockCount, CDialog)
	ON_BN_CLICKED(IDC_OK, &CSetBlockCount::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CANCEL, &CSetBlockCount::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_DEFAULTS, &CSetBlockCount::OnBnClickedDefaults)
END_MESSAGE_MAP()


// CSetBlockCount message handlers

BOOL CSetBlockCount::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	 if(iscount)
  {
    SetWindowText(_T("Update Block Count"));
    c_name1.SetWindowText(_T("Rows"));
    c_name2.SetWindowText(_T("Columns"));
  }
  else
  {
    SetWindowText(_T("Update Block Size"));
    c_name1.SetWindowText(_T("Block Width"));
    c_name2.SetWindowText(_T("Block Height"));
  }

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CSetBlockCount::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	 CDialog::OnOK();
}


void CSetBlockCount::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	 CDialog::OnCancel();
}


void CSetBlockCount::OnBnClickedDefaults()
{
	// TODO: Add your control notification handler code here
	if(iscount)
		c_value1 = c_value2 = 15;
	else
		c_value1 = c_value2 = 35;
	UpdateData(FALSE);
}
