#pragma once

class AStarHead {

	int a;
	int b;
	double x;
	double y;
	double z;

public:

	AStarHead()
	{

	}

	AStarHead(const int &a, const int& b, const double& x, const double& y, const double& z)
	{
		this->a = a;
		this->b = b;
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void SetValues(const int& a, const int& b, const double& x, const double& y, const double& z)
	{
		this->a = a;
		this->b = b;
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void SetInt(const int& a, const int& b)
	{
		this->a = a;
		this->b = b;
	}

	int get_a()
	{
		return a;
	}

	int get_b()
	{
		return b;
	}

	double get_x()
	{
		return x;
	}

	double get_y()
	{
		return y;
	}

	double get_z()
	{
		return z;
	}

	void set_a(const int& a)
	{
		this->a = a;
	}

	void set_b(const int& b)
	{
		this->b = b;
	}

	void set_x(const double& x)
	{
		this->x = x;
	}

	void set_y(const double& y)
	{
		this->y = y;
	}

	void set_z(const double& z)
	{
		this->z = z;
	}

	~AStarHead()
	{

	}
};