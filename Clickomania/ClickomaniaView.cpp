
// ClickomaniaView.cpp : implementation of the CClickomaniaView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Clickomania.h"
#endif

#include "ClickomaniaDoc.h"
#include "ClickomaniaView.h"
#include "SetBlockCount.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClickomaniaView

IMPLEMENT_DYNCREATE(CClickomaniaView, CView)

BEGIN_MESSAGE_MAP(CClickomaniaView, CView)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_EDIT_UNDO, &CClickomaniaView::OnEditUndo)
	ON_COMMAND(ID_LEVEL_LEVEL3, &CClickomaniaView::OnLevelLevel3)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_LEVEL3, &CClickomaniaView::OnUpdateLevelLevel3)
	ON_COMMAND(ID_LEVEL_LEVEL4, &CClickomaniaView::OnLevelLevel4)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_LEVEL4, &CClickomaniaView::OnUpdateLevelLevel4)
	ON_COMMAND(ID_LEVEL_LEVEL5, &CClickomaniaView::OnLevelLevel5)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_LEVEL5, &CClickomaniaView::OnUpdateLevelLevel5)
	ON_COMMAND(ID_LEVEL_LEVEL6, &CClickomaniaView::OnLevelLevel6)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_LEVEL6, &CClickomaniaView::OnUpdateLevelLevel6)
	ON_COMMAND(ID_LEVEL_LEVEL7, &CClickomaniaView::OnLevelLevel7)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_LEVEL7, &CClickomaniaView::OnUpdateLevelLevel7)
	ON_COMMAND(ID_SETUP_BLOCKCOUNT, &CClickomaniaView::OnSetupBlockcount)
	ON_COMMAND(ID_SETUP_BLOCKSIZE, &CClickomaniaView::OnSetupBlocksize)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CClickomaniaView::OnUpdateEditUndo)
END_MESSAGE_MAP()

	// CClickomaniaView construction/destruction

CClickomaniaView::CClickomaniaView()
	{
		// TODO: add construction code here

	}

CClickomaniaView::~CClickomaniaView()
	{
	}

BOOL CClickomaniaView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: Modify the Window class or styles here by modifying
		//  the CREATESTRUCT cs
		return CView::PreCreateWindow(cs);
	}

	// CClickomaniaView drawing
void CClickomaniaView::ResizeWindow() {
  CClickomaniaDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if(!pDoc)
    return;
  CRect rcClient, rcWindow;
  GetClientRect(&rcClient);
  ClientToScreen(&rcClient.TopLeft());
  ClientToScreen(&rcClient.BottomRight());
  GetParentFrame()->GetWindowRect(&rcWindow);
  int WidthDiff = rcWindow.Width() - rcClient.Width();
  int HeightDiff = rcWindow.Height() - rcClient.Height();
  rcWindow.right = rcWindow.left +
    pDoc->GetWidth() * pDoc->GetColumns() + WidthDiff;
  rcWindow.bottom = rcWindow.top +
    (pDoc->GetHeight() * pDoc->GetRows()) + HeightDiff;
  GetParentFrame()->MoveWindow(&rcWindow);
}

void CClickomaniaView::OnDraw(CDC* pDC)
	{
		CClickomaniaDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		// TODO: add draw code for native data here
		int nDCSave = pDC->SaveDC();
		CRect rcClient;
		GetClientRect(&rcClient);
		COLORREF clr = pDoc->GetBoardSpace(-1, -1);
		pDC->FillSolidRect(&rcClient, clr);
		CBrush br;
		br.CreateStockObject(HOLLOW_BRUSH);
		CBrush* pbrOld = pDC->SelectObject(&br);
		for(int i = 0; i < pDoc->GetRows(); i++)//i=row, j = col
		{
			for(int j = 0; j < pDoc->GetColumns(); j++)
			{
				clr = pDoc->GetBoardSpace(i, j);
				CRect rcBlock;
				rcBlock.top = i * pDoc->GetHeight();
				rcBlock.left = j * pDoc->GetWidth();
				rcBlock.right = rcBlock.left + pDoc->GetWidth();
				rcBlock.bottom = rcBlock.top + pDoc->GetHeight();
				pDC->FillSolidRect(&rcBlock, clr);
				//  Draw the block outline
				pDC->Rectangle(&rcBlock);
			}
		}
		//  Restore the device context settings
		pDC->RestoreDC(nDCSave);
		br.DeleteObject();
	}


// CClickomaniaView diagnostics

#ifdef _DEBUG
	void CClickomaniaView::AssertValid() const
	{
		CView::AssertValid();
	}

	void CClickomaniaView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CClickomaniaDoc* CClickomaniaView::GetDocument() const // non-debug version is inline
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClickomaniaDoc)));
		return (CClickomaniaDoc*)m_pDocument;
	}
#endif //_DEBUG

// CClickomaniaView message handlers
void CClickomaniaView::OnInitialUpdate()
{
	//ResizeWindow();
	CView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
	ResizeWindow();
}


void CClickomaniaView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
  CClickomaniaDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if(!pDoc)
    return;
  int row = point.y / pDoc->GetHeight();
  int col = point.x / pDoc->GetWidth();
  pDoc->copy();
  int count = pDoc->DeleteBlocks(row, col);
  if(count > 0)
  {

    Invalidate();
    UpdateWindow();
    if(pDoc->IsGameOver())
    {
      int remaining = pDoc->GetRemainingCount();
      CString message;
      message.Format(_T("No more moves left\nBlocks remaining: %d"),
        remaining);
      MessageBox(message, _T("Game Over"), MB_OK | MB_ICONINFORMATION);
	  pDoc->DeleteBoard();
	  pDoc->SetupBoard();
	  Invalidate();
      UpdateWindow();
    }
  }
	CView::OnLButtonDown(nFlags, point);
}


void CClickomaniaView::OnEditUndo()
{
	// TODO: Add your command handler code here
	CClickomaniaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(!pDoc)
		return;
	pDoc->undo();
	pDoc->SetState(FALSE);
	Invalidate();
    UpdateWindow();
}


void CClickomaniaView::OnLevelLevel3()
{
	// TODO: Add your command handler code here
	CClickomaniaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(!pDoc)
	  return;
	pDoc->SetColors(3);
	Invalidate();
    UpdateWindow();
}


void CClickomaniaView::OnUpdateLevelLevel3(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CClickomaniaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(!pDoc)
	  return;
	pCmdUI->Enable(!(pDoc->GetColors() == 3));
}


void CClickomaniaView::OnLevelLevel4()
{
	// TODO: Add your command handler code here
	CClickomaniaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(!pDoc)
	  return;
	pDoc->SetColors(4);
	Invalidate();
    UpdateWindow();
}


void CClickomaniaView::OnUpdateLevelLevel4(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CClickomaniaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(!pDoc)
	  return;
	pCmdUI->Enable(!(pDoc->GetColors() == 4));
}


void CClickomaniaView::OnLevelLevel5()
{
	// TODO: Add your command handler code here
	CClickomaniaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(!pDoc)
	  return;
	pDoc->SetColors(5);
	Invalidate();
    UpdateWindow();
}


void CClickomaniaView::OnUpdateLevelLevel5(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CClickomaniaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(!pDoc)
	  return;
	pCmdUI->Enable(!(pDoc->GetColors() == 5));
}


void CClickomaniaView::OnLevelLevel6()
{
	// TODO: Add your command handler code here
	CClickomaniaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(!pDoc)
	  return;
	pDoc->SetColors(6);
	Invalidate();
    UpdateWindow();
}


void CClickomaniaView::OnUpdateLevelLevel6(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CClickomaniaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(!pDoc)
	  return;
	pCmdUI->Enable(!(pDoc->GetColors() == 6));
}


void CClickomaniaView::OnLevelLevel7()
{
	// TODO: Add your command handler code here
	CClickomaniaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(!pDoc)
	  return;
	pDoc->SetColors(7);
	Invalidate();
    UpdateWindow();
}


void CClickomaniaView::OnUpdateLevelLevel7(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CClickomaniaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(!pDoc)
	  return;
	pCmdUI->Enable(!(pDoc->GetColors() == 7));
}



void CClickomaniaView::OnSetupBlockcount()
{
	// TODO: Add your command handler code here
	CClickomaniaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(!pDoc)
	  return;
	CSetBlockCount box;
	box.iscount = true;
	box.c_value1 = pDoc->GetRows();
	box.c_value2 = pDoc->GetColumns();
	if(box.DoModal()==IDOK)
	{
		pDoc->DeleteBoard();
		pDoc->SetBlockRow(box.c_value1);
		pDoc->SetBlockColumn(box.c_value2);
		pDoc->SetupBoard();
		ResizeWindow();
	}
}


void CClickomaniaView::OnSetupBlocksize()
{
	// TODO: Add your command handler code here
	CClickomaniaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(!pDoc)
	  return;
	CSetBlockCount box(this);
	box.iscount = false;
	box.c_value1 = pDoc->GetHeight();
	box.c_value2 = pDoc->GetWidth();
	if(box.DoModal()==IDOK)
	{
		pDoc->DeleteBoard();
		pDoc->SetBlockHeight(box.c_value1);
		pDoc->SetBlockWidth(box.c_value2);
		pDoc->SetupBoard();
		ResizeWindow();
	}
}


void CClickomaniaView::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CClickomaniaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(!pDoc)
	  return;
    pCmdUI->Enable(pDoc->GetState());
}
