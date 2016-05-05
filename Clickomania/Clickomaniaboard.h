#pragma once
class Clickomaniaboard
{
public:
	Clickomaniaboard(void);
	~Clickomaniaboard(void);
	void SetupBoard();
	COLORREF GetBoardSpace(int row, int col);
	int GetWidth(){ return m_width;}
	int GetHeight(){return m_height;}
	int GetRow(){return m_rows;}
	int GetColumn(){return m_cols;}
	int GetColors(){return m_colors;}
	void SetColors(int num);
	void SetBlockHeight(int num);
	void SetBlockWidth(int num);
	void SetBlockRow(int num);
	void SetBlockColumn(int num);
	void DeleteBoard();
	int DeleteNeighbour(int row,int col, int color);
	bool IsGameOver();
	bool GetState() {return State;}
	void SetState(bool a) {State =a;}
	void update_board();
	int DeleteBlocks(int row,int col);
	int GetRemainingCount() {return m_remaining;}
	void Clickomaniaboard::operator=( const Clickomaniaboard& other );
private:
	bool State;
	int m_rows;
	int m_cols;
	int m_height;
	int m_width;
	int m_remaining;
	int far_left;
	int far_right;
	int m_colors;
	COLORREF m_color[8];
	void CreateBoard();
	int** m_arrboard;
};