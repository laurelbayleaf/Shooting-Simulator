#include "shooting.h"
#include "Bullet.h"
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
	if (Input::MouseL.clicked && (charge <= 0))
	{
		bullets.emplace_back(size, speed, boom, alpha);
		se.playMulti(0.4);
		charge += rate;
	}
	else if (charge != 0)
	{
		charge--;
	}
}

void shooting::bullet()
{
	for (auto& b : bullets) {
		Circle(b.bulletpoint, b.size).draw(color);

		switch (type)
		{
		case normal:
			b.bulletpoint.y += (double)(0.1 * (50 - b.speed) - 2.0);
			b.size -= b.speed / 33.0; //’e‘¬“x
			break;
		case straight:
			b.size -= b.size * 0.15;
			break;
		case guided:
			b.size--;
			if (0.1*(b.bulletpoint.x - Mouse::Pos().x) >= 5)b.bulletvelocity.x = 5;
			else b.bulletvelocity.x = 0.1*(b.bulletpoint.x - Mouse::Pos().x);
			if (0.1*(b.bulletpoint.y - Mouse::Pos().y) >= 5)b.bulletvelocity.y = 5;
			else b.bulletvelocity.y = 0.1*(b.bulletpoint.y - Mouse::Pos().y);
			b.bulletpoint -= b.bulletvelocity;
			break;
		default:
			break;
		}

		b.speed--;
		if (b.speed <= 0)
		{
			b.hit = true;
		}
	}
}

void shooting::bulletdelete()
{
	Erase_if(bullets, [&](Bullet b)
	{
		if (b.Delete)
		{
			return true;
		}
		else
		{
			return false;
		}
	});
}
