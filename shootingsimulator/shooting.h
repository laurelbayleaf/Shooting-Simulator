#pragma once
#include <Siv3D.hpp>
#include "Bullet.h"
class shooting
{
public:
	enum TYPE
	{
		normal,
		straight,
		guided,
	};
	shooting(double si, int sp, int ra, int	b, TYPE t, double a, s3d::Color c, Sound s);
	~shooting();
	void shoot();
	void bullet();
	Array<Bullet>bullets;

private:
	int speed, rate, boom, charge = 0;
	double alpha, size;
	bool hit = false;
	TYPE type;
	Sound se;
	s3d::Color color;

};

