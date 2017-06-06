#pragma once
#include <Siv3D.hpp>
#include "shooting.h"

class target
{
public:
	enum TYPE
	{
		circle,
		box,
		moved_box,
	};
	target(TYPE t, double s, double s2, double sp, double ti,s3d::Color c);
	~target();
	void addtarget(Point p);
	void drawtarget();
	void movextarget(Vec3 &v);
	void hittarget(Bullet b,Sound se);
	void boomtarget(Bullet b, Sound se);
	void reset();
	bool checkvoid();
	int score;
	Stopwatch fade,cool;
private:

	double size, size2, speed, time;
	TYPE type;
	s3d::Color color;
	Array<Point> targets;
	Array<Vec3> movetargets;
};