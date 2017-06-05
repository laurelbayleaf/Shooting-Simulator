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
	shooting(double si, int sp, int ra, int	b, TYPE t, double a,int co, s3d::Color c, Sound s);
	~shooting();
	void shoot();
	void bullet();
	void bulletdelete();
	Array<Bullet>bullets;
	int tortalcost = 0, charge = 0, rate;

private:
	int speed, boom, cost;
	void addcost();
	double alpha, size;
	bool hit = false;
	TYPE type;
	Sound se;
	s3d::Color color;

};

