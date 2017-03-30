#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::Bullet(double si, int sp,int b, double a)
{
	size = si;
	speed = sp;
	boom = b;
	alpha = a;
	bulletpoint = Mouse::Pos();
}

Bullet::~Bullet()
{
}
