#include "StdAfx.h"
#include "Clickomaniaboard.h"
#include "ClickomaniaView.h"
#include <mmsystem.h>
#include <windows.h>
#include "resource.h"

Clickomaniaboard::Clickomaniaboard(void) : m_arrboard(NULL), m_cols(15), m_rows(15), m_height(35), m_width(35), m_remaining(0), m_colors(3)
{
	m_color[0] = RGB(0, 0, 0);
	m_color[1] = RGB(255, 0, 0);
	m_color[2] = RGB(0, 255, 0);
	m_color[3] = RGB(0, 0, 255);
	m_color[4] = RGB(160, 160, 160);
	m_color[5] = RGB(255, 128, 0);
	m_color[6] = RGB(127, 0, 255);
	m_color[7] = RGB(255, 255, 0);
}

void Clickomaniaboard::operator=(const Clickomaniaboard& a) {
	m_cols = a.m_cols;
	m_rows = a.m_rows;
	m_height = a.m_height;
	m_width = a.m_width;
	m_remaining = a.m_remaining;
	m_colors = a.m_colors;
	for (int i = 0; i < 8; i++)
		m_color[i] = a.m_color[i];
	m_arrboard = NULL;
	CreateBoard();
	for (int row = 0; row < m_rows; row++)
		for (int col = 0; col < m_cols; col++)
			m_arrboard[row][col] = a.m_arrboard[row][col];
}

Clickomaniaboard::~Clickomaniaboard(void)
{
	DeleteBoard();
}

void Clickomaniaboard::SetColors(int num) {
	m_colors = num;
	SetupBoard();
}

void Clickomaniaboard::SetBlockWidth(int num) {
	m_width = num;
}
void Clickomaniaboard::SetBlockHeight(int num) {
	m_height = num;
}
void Clickomaniaboard::SetBlockRow(int num) {
	m_rows = num;
}
void Clickomaniaboard::SetBlockColumn(int num) {
	m_cols = num;
}

void Clickomaniaboard::SetupBoard() {
	if (m_arrboard == NULL)
		CreateBoard();
	for (int i = 0; i < m_rows; ++i)//i=row, j = col
		for (int j = 0; j < m_cols; ++j)
			m_arrboard[i][j] = (rand() % m_colors) + 1;
	m_remaining = m_rows * m_cols;
	State = FALSE;
}

COLORREF Clickomaniaboard::GetBoardSpace(int row, int col) {
	if (row < 0 || row >= m_rows || col < 0 || col >= m_cols)
		return m_color[0];
	return m_color[m_arrboard[row][col]];
}

void Clickomaniaboard::DeleteBoard() {
	if (m_arrboard != NULL)
	{
		for (int i = 0; i < m_rows; ++i)//i=row
			if (m_arrboard[i] != NULL)
			{
				delete[] m_arrboard[i];
				m_arrboard[i] = NULL;
			}
		delete[] m_arrboard;
		m_arrboard = NULL;
	}
}

void Clickomaniaboard::CreateBoard() {
	if (m_arrboard != NULL)
		DeleteBoard();
	m_arrboard = new int*[m_rows];//i=row, j = col
	for (int i = 0; i < m_rows; ++i)
		m_arrboard[i] = new int[m_cols];
	for (int i = 0; i < m_rows; ++i)
		for (int j = 0; j < m_cols; ++j)
			m_arrboard[i][j] = 0;
}

int Clickomaniaboard::DeleteBlocks(int row, int col) {
	int deleted_block = 0;
	if (row < 0 || row >= m_rows || col < 0 || col >= m_cols)
		return 0;
	int color = m_arrboard[row][col];
	far_right = -1;
	far_left = m_cols;
	if (color != 0)
		deleted_block = DeleteNeighbour(row, col, color);
	if (deleted_block <= 1)
	{
		m_arrboard[row][col] = color;
		PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_ASYNC | SND_RESOURCE);
		return 0;
	}
	PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_ASYNC | SND_RESOURCE);
	update_board();
	m_remaining -= deleted_block;
	State = TRUE;
	return deleted_block;
}

int Clickomaniaboard::DeleteNeighbour(int row, int col, int color) {
	if (row < 0 || row >= m_rows || col < 0 || col >= m_cols)
		return 0;
	if (color != m_arrboard[row][col])
		return 0;
	else
	{
		m_arrboard[row][col] = 0;
		if (far_left > col)
			far_left = col;
		if (far_right < col)
			far_right = col;
		return 1 + DeleteNeighbour(row - 1, col, color)
			+ DeleteNeighbour(row + 1, col, color)
			+ DeleteNeighbour(row, col - 1, color)
			+ DeleteNeighbour(row, col + 1, color);
	}
}
void Clickomaniaboard::update_board() {
	for (int i = far_right; i >= far_left; --i)
		for (int j = m_rows - 1; j >= 0; --j)
		{
			if (m_arrboard[j][i] == 0)
			{
				int k;
				for (k = j; k >= 0; --k)
				{
					if (m_arrboard[k][i] != 0)
						m_arrboard[j--][i] = m_arrboard[k][i];
				}
				while (j >= 0)
					m_arrboard[j--][i] = 0;
			}
		}
	int nNextEmptyCol = 0;
	int nNextOccupiedCol = nNextEmptyCol;
	while (nNextEmptyCol < m_cols && nNextOccupiedCol < m_cols)
	{
		while (nNextEmptyCol < m_cols &&
			m_arrboard[m_rows - 1][nNextEmptyCol] != 0)
			nNextEmptyCol++;
		if (nNextEmptyCol < m_cols)
		{
			nNextOccupiedCol = nNextEmptyCol + 1;
			while (nNextOccupiedCol < m_cols &&
				m_arrboard[m_rows - 1][nNextOccupiedCol] == 0)
				nNextOccupiedCol++;
			if (nNextOccupiedCol < m_cols)
			{
				for (int row = 0; row < m_rows; row++)
				{
					m_arrboard[row][nNextEmptyCol] =
						m_arrboard[row][nNextOccupiedCol];
					m_arrboard[row][nNextOccupiedCol] = 0;
				}
			}
		}
	}
}
bool Clickomaniaboard::IsGameOver(void) {
	for (int col = 0; col < m_cols; col++)
	{
		for (int row = m_rows - 1; row >= 0; row--)
		{
			int nColor = m_arrboard[row][col];
			if (nColor == 0)
				break;
			else
			{
				if (row - 1 >= 0 &&
					m_arrboard[row - 1][col] == nColor)
					return false;
				else if (col + 1 < m_cols &&
					m_arrboard[row][col + 1] == nColor)
					return false;
			}
		}
	}
	return true;
}