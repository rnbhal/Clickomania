
// ClickomaniaView.h : interface of the CClickomaniaView class
//

#pragma once
#include "ClickomaniaDoc.h"

class CClickomaniaView : public CView
{
protected: // create from serialization only
	CClickomaniaView();
	DECLARE_DYNCREATE(CClickomaniaView)

	// Attributes
public:
	CClickomaniaDoc* GetDocument() const;
	// Operations
public:
	void ResizeWindow();
	// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

	// Implementation
public:
	virtual ~CClickomaniaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEditUndo();
	afx_msg void OnLevelLevel3();
	afx_msg void OnUpdateLevelLevel3(CCmdUI *pCmdUI);
	afx_msg void OnLevelLevel4();
	afx_msg void OnUpdateLevelLevel4(CCmdUI *pCmdUI);
	afx_msg void OnLevelLevel5();
	afx_msg void OnUpdateLevelLevel5(CCmdUI *pCmdUI);
	afx_msg void OnLevelLevel6();
	afx_msg void OnUpdateLevelLevel6(CCmdUI *pCmdUI);
	afx_msg void OnLevelLevel7();
	afx_msg void OnUpdateLevelLevel7(CCmdUI *pCmdUI);
	afx_msg void OnSetupBlockcount();
	afx_msg void OnSetupBlocksize();
	afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in ClickomaniaView.cpp
inline CClickomaniaDoc* CClickomaniaView::GetDocument() const
{ return reinterpret_cast<CClickomaniaDoc*>(m_pDocument); }
#endif

