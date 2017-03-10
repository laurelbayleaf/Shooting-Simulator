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
	int size,speed,rate,type,alpha;
	s3d::Color color;
	Array<Vec4> bullets; 

public:
	shooting(int si, int sp, int ra, int t, int a, s3d::Color c);
	~shooting();
	void shoot();
	void bullet();
	void shotnormal(Vec4 name,int a);
	void sizedown(Vec4 name);
};

