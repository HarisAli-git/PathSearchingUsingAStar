#pragma once
#include "grid_input.h"
using namespace std;

struct sd {
	int x;
	int y;
};

class grid {
	COORD scr_buff_s;
	HANDLE ch;
	HWND cw;
	grid_input g;
	sd s, d;

public:

	grid()
	{

	}

	int get_s_first()
	{
		return s.x;
	}

	int get_d_first()
	{
		return d.x;
	}

	int get_s_sec()
	{
		return s.y;
	}

	int get_d_sec()
	{
		return d.y;
	}

	grid_input get_grid_input()
	{
		return g;
	}

	void draw_coordinates(const int& a, const int& b, const int& r1, const int& g1, const int& b1, const int& rb, const int& gb, const int& bb)
	{
		g.draw_hurdle(a * g.get_width(), b * g.get_width(), a * g.get_width() + g.get_width(), b * g.get_width() + g.get_width(), r1, g1, b1, rb, gb, bb);
	}

	bool is_dest_reached(const int& r, const int& c)
	{
		if (r == d.x && c == d.y)
			return true;
		else
			return false;
	}

	bool is_clear(const int &r, const int &c)
	{
		return g.is_clear(r, c);
	}

	bool is_in_range(const int &r, const int &c) // prints true if curr_row & curr_col are >= than 0 and < max value
	{
		if (r >= 0 && c >= 0)
		{
			if (r < g.get_row() && c < g.get_col())
				return true;
			else
				return false;
		}
		else
			return false;
	}

	void draw_grid()
	{
		g.draw_grid(s.x, s.y, d.x, d.y);
	}

	grid(char* f1, char* f1_size, const int& wide, const int &sx, const int &sy, const int &dx, const int &dy) : g(f1, f1_size, wide), scr_buff_s{ 1920, 1080 }, ch(GetStdHandle(STD_OUTPUT_HANDLE)), cw(GetConsoleWindow())
	{
		s.x = sx;
		s.y = sy;
		d.x = dx;
		d.y = dy;

		if ((is_in_range(s.x, s.y)) && (is_in_range(d.x, d.y)))
		{
			if ((is_clear(s.x, s.y)) && (is_clear(d.x, d.y)))
			{
				if (!is_dest_reached(s.x, s.y))
				{
					SetConsoleScreenBufferSize(ch, scr_buff_s);
					ShowWindow(cw, SW_MAXIMIZE);
				}
				else
				{
					cout << "\nWe are already at the Destination!" << endl;
					exit(0);
				}
			}
			else
			{
				cout << "\nWe are blocked at the Source Destination!" << endl;
				exit(0);
			}
		}
		else
		{
			cout << "\nSource Destination are out of range!" << endl;
			exit(0);
		}
	}

	~grid()
	{

	}
};