#include "AStarSearch.h"
#include <vector>

struct it {
	int p;
	int dx;
	int dy;
};

it inBegin(int &row, char f[])
{
	ifstream fin(f);
	vector<it> v;
	it node;

	if (fin)
	{
		int s = 0;
		fin >> s;

		for (int i = 0; i < s; i++)
		{
			it a;
			fin >> a.dx;
			fin >> a.dy;
			fin >> a.p;

			v.push_back(a);
		}

		for (int i = 0; i < s; i++)
		{
			if (v[i].p == 0)
			{
				node.dx = v[i].dx;
				node.dy = v[i].dy;
			}
		}

		cout << "\nWelcome to the Optimal Path scheduling simulation Assignment by using A*. ";

		fin.close();
		return node;
	}
	else
	{
		cout << "\nFile Not opened!\nHence Program will not terminate!";
		exit(0);
		return node;
	}
}

int get_r(char f[])
{
	ifstream fin(f);
	if (fin)
	{
		int r = 0;
		fin >> r;
		return r;
		fin.close();
	}
	else
	{
		cout << "\nFile Not opened!\nHence Program will not terminate!";
		return -1;
	}
}

int main()
{
	COORD scr_buff_s{ 1920, 1080 };
	HANDLE ch(GetStdHandle(STD_OUTPUT_HANDLE));
	HWND cw = GetConsoleWindow();
	SetConsoleScreenBufferSize(ch, scr_buff_s);
	ShowWindow(cw, SW_MAXIMIZE);

	int row = 0;

	char f21[] = "crd.txt";

	it node = inBegin(row, f21);

	cout << "\nRescue 1122 starting x-coordinate: " << 0;
	cout << "\tRescue 1122 starting y-coordinate: " << 0;
	cout << "\nRescue 1122 destination x-coordinate: " << node.dx;
	cout << "\tRescue 1122 destination y-coordinate: " << node.dy;

	cout << "\nCoordinates Set!";
	system("pause");

	char f1[] = "grid.txt", f1_size[] = "grid_size.txt";

	int r = get_r(f1_size);
	if (r == -1)
		return 0;

	grid gr(f1, f1_size, 15, 39, 39, node.dx, node.dy);


	system("cls");
	gr.draw_grid();

	COORD c;
	c.X = 0;
	c.Y = r;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

	AStarSearch a(gr.get_grid_input());
	a.Search(gr);
	int ret = _getch();

	cout << endl;
	return 0;
}