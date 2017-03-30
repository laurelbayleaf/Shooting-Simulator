#pragma once
#include <Siv3D.hpp>
class Bullet
{
public:
	Bullet();
	Bullet(double si, int sp,int b, double a);
	~Bullet();
	int speed, boom;
	double alpha, size = 0;
	Point bulletpoint, bulletvelocity;
	bool hit = false;

private:

};
