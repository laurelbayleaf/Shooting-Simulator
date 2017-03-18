#include "shooting.h"

shooting::shooting(double si, int sp, int ra, int b, TYPE t, double a, s3d::Color c,Sound s)
{
	size = si;
	speed = sp;
	rate = ra;
	boom = b;
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
		shoted = true;
		bulletpoint = Mouse::Pos();
		Bsize = size;
		time = speed;
		se.playMulti(0.4);
	}
}

void shooting::bullet()
{
	if (shoted)
	{
		makebullet().draw(color);

		switch (type)
		{
		case normal:
			bulletpoint.y += (double)(0.1 * (50 - time) - 2.0);
			Bsize -= time / 33.0; //’e‘¬“x
			break;
		case straight:
			Bsize -= Bsize * 0.15;
			break;
		case guided:
			Bsize--;
			if (0.1*(bulletpoint.x - Mouse::Pos().x) >= 5) {
				bulletvelocity.x = 5;
			}
			else
			{
				bulletvelocity.x = 0.1*(bulletpoint.x - Mouse::Pos().x);
			}
			if (0.1*(bulletpoint.y - Mouse::Pos().y) >= 5) {
				bulletvelocity.y = 5;
			}
			else
			{
				bulletvelocity.y = 0.1*(bulletpoint.y - Mouse::Pos().y);
			}

			bulletpoint -= bulletvelocity;
			break;
		default:
			break;
		}

		time--;
		if (time <= 0)
		{
			shoted = false;
			hit = true;
		}


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

int shooting::boomrange()
{
	return boom;
}


