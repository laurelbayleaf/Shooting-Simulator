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
		null,
	};
	int speed, rate, type, alpha, Bspeed;
	double size, Bsize = 0;
	bool shoted = false, hit = false;
	Point bulletpoint;
	Sound se;
	s3d::Color color;
	//Array<Vec4> bullets; 

public:
	shooting(double si, int sp, int ra, int t, int a, s3d::Color c,Sound s);
	~shooting();
	void shoot();
	void bullet();
	bool gethit();
	void unhit();
	Circle makebullet();
	Point ammopos();
	//void shotnormal(Vec4 name,int a);
	//void sizedown(Vec4 name);
};

