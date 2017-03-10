#include "shooting.h"

shooting::shooting(int si, int sp, int ra, int t, int a, s3d::Color c)
{
	size = si;
	speed = sp;
	rate = ra;
	type = t;
	alpha = a;
	color = c;
}

shooting::~shooting()
{
}

void shooting::shoot()
{
	const Sound scanonn(L"resource/canonn.mp3");
	const Sound slaser(L"resource/laser.mp3");
	const Sound smissile(L"resource/missile.mp3");
	const Sound hit(L"resource/hit.mp3");


	if(Input::MouseL.clicked&&Input::MouseL.released >=rate){
		switch (type)
	{
	case normal:
		bullets.emplace_back(Mouse::Pos,size, speed);
		scanonn.playMulti(0.4);

		break;
	default:
		break;
	}

	}

}

void shooting::bullet()
{
	switch (type)
	{
	case normal:
		for (const auto& bullet : bullets) {
			Circle(bullet.x,bullet.y).draw(color);
			shotnormal(bullet,alpha);
			sizedown(bullet);

		}
			

		break;
	default:
		break;
	}

}

void shooting::shotnormal(Vec4 name, int a)
{
		name.y += (double)(0.1 * (50 - name.z) - 2.0);
		name.z -= name.w / 33.0; //’e‘¬“x

}

void shooting::sizedown(Vec4 name)
{
	name.w--;
}


