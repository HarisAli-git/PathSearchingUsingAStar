#pragma once
#include <iostream>
#include <conio.h>
#include "windows.h"
#include <fstream>
using namespace std;

class grid_input {
	int w;
	int row;
	int col;
	int sx;
	int sy;
	int dx;
	int dy;
	int **grid;

public:
	grid_input()
	{
		grid = NULL;
	}

	grid_input(const grid_input& g)
	{
		this->w = g.w;
		this->row = g.row;
		this->col = g.col;
		this->sx = g.sx;
		this->dx = g.dx;
		this->dy = g.dy;

		this->grid = new int*[row];

		for (int i = 0; i < row; i++)
		{
			this->grid[i] = new int[col];

			for (int j = 0; j < col; j++)
			{
				this->grid[i][j] = g.grid[i][j];
			}
		}

	}

	int get_width()
	{
		return w;
	}

	int get_row()
	{
		return row;
	}

	int get_col()
	{
		return col;
	}

	bool is_clear(const int &r, const int &c)
	{
		bool flag = (grid[r][c] == 1);
		return flag;
	}

	void del_obj_draw_hurdle(HPEN p, HBRUSH b)
	{
		DeleteObject(p);
		DeleteObject(b);
	}

	void SetWindow(HWND &cw, HDC &dc)
	{
		cw = GetConsoleWindow();
		dc = GetDC(cw);
	}

	HBRUSH draw_with_brush(const int& r, const int& g, const int& b, const HDC dc)
	{
		HBRUSH brush = ::CreateSolidBrush(RGB(r, g, b));
		SelectObject(dc, brush);
		return brush;
	}

	HPEN draw_with_pen(const int &px, const int& r, const int& g, const int& b, const HDC dc)
	{
		HPEN p = CreatePen(PS_SOLID, px, RGB(r, g, b));
		SelectObject(dc, p);
		return p;
	}

	void draw_hurdle(const int& a, const int& b, const int& x, const int& y, const int& R, const int& G, const int& B, const int& r1, const int& g1, const int& b1)
	{
		HWND cw = GetConsoleWindow();
		HDC dc = GetDC(cw);

		SetWindow(cw, dc);

		HPEN p = draw_with_pen(1, R, G, B, dc);
		HBRUSH d = draw_with_brush(r1, g1, b1, dc);

		Rectangle(dc, a, b, x, y);
		ReleaseDC(cw, dc);

		del_obj_draw_hurdle(p, d);

	}

	void draw_coordinates(const int& a, const int& b, const int& r1, const int& g1, const int& b1, const int& rb, const int& gb, const int& bb)
	{
		draw_hurdle(a * w, b * w, a * w + w, b * w + w, r1, g1, b1, rb, gb, bb);
	}

	void draw_grid_with_hurdles(const int& i, const int& j, const int& a, const int& b)
	{
		if (grid[i][j] == 1)
			draw_coordinates(a, b, 0, 0, 0, 200, 200, 200);
		else if (grid[i][j] == 0)
			draw_coordinates(a, b, 255, 255, 255, 75, 158, 86);
		else if (grid[i][j] == 2)
			draw_coordinates(a, b, 255, 255, 255, 2, 2, 122);
		else if (grid[i][j] == 3)
			draw_coordinates(a, b, 255, 255, 255, 141, 70, 172);
		else if (grid[i][j] == 4)
			draw_coordinates(a, b, 255, 255, 255, 105, 84, 35);
	}

	void draw_grid(const int &x1, const int& x2, const int& y1, const int& y2)
	{
		int a, b;
		a = b = 0;

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				draw_coordinates(a, b, 255, 255, 255, 75, 158, 86);
				draw_grid_with_hurdles(i, j, a, b);

				if (i == y1 && j == y2)
					draw_coordinates(a, b, 0, 0, 0, 255, 25, 30);
				else if (i == x1 && j == x2)
					draw_coordinates(a, b, 0, 0, 0, 0, 255, 0);

				a++;
			}
			a = 0;
			b++;
		}

	}

	bool FileRead(string gri, string size)
	{
		fstream fin(gri);
		fstream fin1(size);
		if (fin && fin1)
		{
			fin1 >> row;
			fin1 >> col;
			grid = new int*[row];
			for (int i = 0; i < row; i++)
			{
				grid[i] = new int[col];
				for (int j = 0; j < col; j++)
				{
					fin >> grid[i][j];
				}
			}

			fin.close();
			fin1.close();
			return true;
		}
		else
		{
			cout << "\nFile Not Opened! Hence, program will terminate now!\n" << endl;
			return false;
		}
	}

	grid_input(char* f1, char* f1_size, const int &wide)
	{
		ifstream fin(f1);
		ifstream fin_size(f1_size);

		if (!FileRead(f1, f1_size))
			exit(0);

		w = wide;
	}

	~grid_input()
	{
		for (int i = 0; i < row; i++)
		{
			delete[] grid[i];
			grid[i] = NULL;
		}
		delete[] grid;
		grid = NULL;
	}
};