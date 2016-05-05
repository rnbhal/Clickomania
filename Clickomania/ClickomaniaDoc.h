
// ClickomaniaDoc.h : interface of the CClickomaniaDoc class
//


#pragma once
#include "Clickomaniaboard.h"

class CClickomaniaDoc : public CDocument
{
protected: // create from serialization only
	CClickomaniaDoc();
	DECLARE_DYNCREATE(CClickomaniaDoc)

protected:
	Clickomaniaboard m_board;
	Clickomaniaboard previous_board;
	// Operations
public:
	COLORREF GetBoardSpace(int row, int col) {return m_board.GetBoardSpace(row, col); }
	void SetupBoard(void)   { m_board.SetupBoard(); }
	int GetWidth(void)      { return m_board.GetWidth(); }
	int GetHeight(void)     { return m_board.GetHeight(); }
	int GetColumns(void)    { return m_board.GetColumn(); }
	int GetRows(void)       { return m_board.GetRow(); }
	int GetColors(void)     { return m_board.GetColors(); }
	void SetColors(int num) {m_board.SetColors(num);}
	void SetBlockHeight(int num) {m_board.SetBlockHeight(num);}
	void SetBlockWidth(int num) {m_board.SetBlockWidth(num);}
	void SetBlockRow(int num) {m_board.SetBlockRow(num);}
	void SetBlockColumn(int num) {m_board.SetBlockColumn(num);}
	void DeleteBoard(void)  { m_board.DeleteBoard(); }
	bool IsGameOver()	    {return m_board.IsGameOver();}
	int DeleteBlocks(int row,int col){return m_board.DeleteBlocks(row,col);}
	int GetRemainingCount() {return m_board.GetRemainingCount();}
	void copy() {previous_board = m_board;}
	void undo() {m_board = previous_board;}
	bool GetState() {return m_board.GetState();}
	void SetState(bool a) {m_board.SetState(a);}
	// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// Implementation
public:
	virtual ~CClickomaniaDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
