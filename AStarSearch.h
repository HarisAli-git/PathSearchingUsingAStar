#pragma once
#include <set>
#include <stack>
#include <iterator>
#include "grid.h"
#include "AStarHead.h"

typedef pair<double, pair<int, int>> p;

class AStarSearch {

	int ai;
	int bj;
	int r;
	int c;
	bool fd;
	double m;
	double gn;
	double hn;
	double fn;
	bool **v_list;
	AStarHead*** a;
	set<p> f;
	p p1;

public:

	AStarSearch(grid_input g)
	{
		c = g.get_col();
		r = g.get_row();

		a = new AStarHead **[r];
		v_list = new bool *[r];

		fd = false;

		m = LONG_MAX;

		ai = 0;
		bj = 0;

		gn = 0.0;
		hn = 0.0;
		fn = 0.0;

		for (int l = 0; l < r; l++)
		{
			v_list[l] = new bool[c];
			a[l] = new AStarHead *[c];

			for (int k = 0; k < c; k++)
			{
				v_list[l][k] = false;
				a[l][k] = new AStarHead(-1, -1, -1, -1, -1);
			}
		}
	}

	AStarSearch()
	{
		a = NULL;
		v_list = NULL;
	}

	// code modified from geeksforgeeks.org
	// href https://www.geeksforgeeks.org/a-search-algorithm/
	void TracingPath(grid g)
	{

		cout << "The destination cell is found\n";
		cout << "The Path is:\n";

		int r1 = g.get_d_first();
		int c1 = g.get_d_sec();

		stack<sd> Path;

		while (!(a[r1][c1]->get_a() == r1 && a[r1][c1]->get_b() == c1))
		{
			sd temp;
			temp.x = r1;
			temp.y = c1;
			Path.push(temp);

			int temp_r = a[r1][c1]->get_a();
			c1 = a[r1][c1]->get_b();
			r1 = temp_r;
		}

		sd temp;
		temp.x = r1;
		temp.y = c1;
		Path.push(temp);

		int i = 0;

		while (!Path.empty())
		{
			sd ptop = Path.top();
			Path.pop();

			g.draw_coordinates(ptop.y, ptop.x, 45, 0, 0, 100, 10, 10);

			if (ptop.x == g.get_d_first() && ptop.y == g.get_d_sec())
				g.draw_coordinates(ptop.y, ptop.x, 0, 0, 0, 0, 255, 0);

			Sleep(80);
			cout << "-> (" << ptop.x << "," << ptop.y << ") ";
			i++;
			if (i == 5)
			{
				i = 0;
				cout << endl;
			}
		}

		return;
	}


	double cal_huv(int x, int y, int a, int b)
	{
		double x_huv = (double)sqrt((x - a) * (x - a));
		double y_huv = (double)sqrt((y - b) * (y - b));

		return x_huv + y_huv;
	}

	bool proceed(int a, int b, grid g)
	{
		if (v_list[a][b])
			return false;
		else
			return g.is_clear(a, b);
	}

	// code modified from geeksforgeeks.org
	// href https://www.geeksforgeeks.org/a-search-algorithm/
	void dis_each_el(grid g)
	{
		m = (*f.begin()).first;
		p1 = *f.begin();

		for (auto it = f.begin(); it != f.end(); ++it)
		{
			if ((*it).first < m)
				p1 = *it;
		}

		g.draw_coordinates(p1.second.second, p1.second.first, 45, 45, 45, 33, 139, 139);
		Sleep(25);
		f.erase(p1);
	}

	bool checkHUV(int i, int j)
	{
		if (a[i][j]->get_x() == -1 || a[i][j]->get_x() > fn)
			return true;
		else
			return false;
	}

	// code modified from geeksforgeeks.org
	// href https://www.geeksforgeeks.org/a-search-algorithm/
	void success(int i, int j, grid g)
	{
		if (g.is_in_range(i, j) == true)
		{
			if (g.is_dest_reached(i, j) == true)
			{
				a[i][j]->SetInt(ai, bj);
				fd = true;
			}

			else if (proceed(i, j, g))
			{
				gn = a[i][j]->get_y() + 1.0;
				hn = cal_huv(i, j, g.get_d_first(), g.get_d_sec());
				fn = gn + hn;

				if (checkHUV(i, j))
				{
					f.insert(make_pair(fn, make_pair(i, j)));
					a[i][j]->SetValues(ai, bj, fn, gn, hn);
				}
			}
		}
	}

	void set_ij(int &a, int &b, const int &a1, const int &b1)
	{
		a = a1;
		b = b1;
	}

	// code modified from geeksforgeeks.org
	// href https://www.geeksforgeeks.org/a-search-algorithm/
	void Search(grid g)
	{
		Sleep(500);

		int i = 0, j = 0;

		set_ij(i, j, g.get_s_first(), g.get_s_sec());

		double in_f = 0.0;

		a[i][j]->SetValues(i, j, in_f, in_f, in_f);

		f.insert(make_pair(in_f, make_pair(i, j)));

		while (!f.empty() && !fd)
		{

			dis_each_el(g);

			set_ij(i, j, p1.second.first, p1.second.second);

			v_list[i][j] = true;

			ai = i;
			bj = j;

			if (!fd)
				success(i, j - 1, g);
			if (!fd)
				success(i - 1, j, g);
			if (!fd)
				success(i + 1, j, g);
			if (!fd)
				success(i, j + 1, g);
			if (!fd)
				success(i - 1, j + 1, g);
			if (!fd)
				success(i - 1, j - 1, g);
			if (!fd)
				success(i + 1, j + 1, g);
			if (!fd)
				success(i + 1, j - 1, g);
		}

		if (!fd)
			cout << "The Destination Cell has failed to reach!" << endl;
		else
			TracingPath(g);

	}

	~AStarSearch()
	{
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				delete a[i][j];
				a[i][j] = NULL;
			}

			delete[] a[i];
			a[i] = NULL;
		}

		delete[] a;
		a = NULL;

		for (int i = 0; i < r; i++)
		{
			delete[] v_list[i];
			v_list[i] = NULL;
		}

		delete[] v_list;
		v_list = NULL;
	}

};