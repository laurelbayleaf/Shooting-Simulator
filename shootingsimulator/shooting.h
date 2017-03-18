#pragma once
# include <Siv3D.hpp>



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
	bool gethit();
	void unhit();
	Circle makebullet();
	Point ammopos();
	int boomrange();
private:
	int speed, rate, time, boom;
	double alpha,size, Bsize = 0;
	bool shoted = false, hit = false;
	Point bulletpoint,bulletvelocity;
	TYPE type;
	Sound se;
	s3d::Color color;
};

