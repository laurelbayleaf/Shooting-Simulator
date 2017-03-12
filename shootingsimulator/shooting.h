#pragma once
# include <Siv3D.hpp>



class shooting
{
private:
	enum TYPE
	{
		normal,
		straight,
		guided,
	};
	int speed, rate, type, time;
	double alpha,size, Bsize = 0;
	bool shoted = false, hit = false;
	Point bulletpoint,bulletvelocity;
	Sound se;
	s3d::Color color;
	//Array<Vec4> bullets; 

public:
	shooting(double si, int sp, int ra, int t, double a, s3d::Color c,Sound s);
	~shooting();
	void shoot();
	void bullet();
	bool gethit();
	void unhit();
	Circle makebullet();
	Point ammopos();
};

