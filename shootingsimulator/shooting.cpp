#include "shooting.h"

shooting::shooting(double si, int sp, int ra, int t, int a, s3d::Color c,Sound s)
{
	size = si;
	speed = sp;
	rate = ra;
	type = t;
	alpha = a;
	color = c;
	se = s;
}

shooting::~shooting()
{
}

void shooting::shoot()
{
	if (Input::MouseL.clicked && !shoted)
	{
		switch (type)
		{
		case normal:
			//bullets.emplace_back(Mouse::Pos,size, speed);
			shoted = true;
			bulletpoint = Mouse::Pos();
			Bsize = size;
			Bspeed = speed;
			se.playMulti(0.4);

			break;
		default:
			break;
		}
	}
}

void shooting::bullet()
{
	if (shoted)
	{
		//for (const auto& bullet : bullets) {

			makebullet().draw(color);
			bulletpoint.y += (double)(0.1 * (50 - Bspeed) - 2.0);
			Bsize -= Bspeed / 33.0; //’e‘¬“x
			Bspeed--;
			if (Bspeed <=0)
			{
				shoted = false;
				hit = true;
			}

			//shotnormal(alpha);
			//sizedown();

		//}

	}

}

bool shooting::gethit()
{
	return hit;
}

void shooting::unhit()
{
	hit = false;
}

Circle shooting::makebullet()
{
	return Circle(bulletpoint, Bsize);
}

Point shooting::ammopos()
{
	return Point(bulletpoint);
}

//void shooting::shotnormal(/*Vec4 name,*/ int a)
//{
//		name.y += (double)(0.1 * (50 - name.z) - 2.0);
//		name.z -= name.w / 33.0; //’e‘¬“x
//
//}

//void shooting::sizedown(/*Vec4 name*/)
//{
//	name.w--;
//}



