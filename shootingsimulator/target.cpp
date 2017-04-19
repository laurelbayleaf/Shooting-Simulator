#include "target.h"
#include "shooting.h"


target::target(TYPE t, double s, double s2, double sp, s3d::Color c)
{
	type = t;
	size = s;
	size2 = s2;
	speed = sp;
	color = c;
}

target::~target()
{
}

void target::addtarget(Point p)
{
	if (type ==moved_box)
	{
	movetargets.emplace_back(p.x,p.y,speed);
	}
	else
	{
	targets.emplace_back(p.x,p.y);
	}
}

void target::drawtarget()
{
	switch (type)
	{
	case circle:
		for (const auto& target : targets)
			Circle(target,size).draw(color);
		break;
	case box:
		for (const auto& target : targets)
			Rect((int)size).setCenter(target).draw(color);
		break;
	case moved_box:
		for (auto& target : movetargets) {
			movextarget(target);
			Rect((int)size,(int)size2).setCenter((int)target.x,(int)target.y).draw(color);
		}
	default:
		break;
	}
}

void target::movextarget(Vec3 &v)
{
	v.x += v.z;
	if ((v.x < (size / 2) && v.z < 0) || (Window::Width() - (size / 2) < v.x && v.z > 0))
	{
		v.z *= -1; //”½ŽË
		if (v.z > 0) {
			v.x = size / 2;
		}
		else {
			v.x = Window::Width() - size / 2;
		}
	}
}

void target::hittarget(Bullet b, Sound se)
{
	if (type == moved_box)
	{
		Erase_if(movetargets, [&](Vec3 t) {
			if (Rect((int)size, (int)size2).setCenter((int)t.x, (int)t.y).intersects(b.bulletpoint)) {
				se.playMulti();
				Circle(b.bulletpoint, b.boom).draw(Palette::Red);//”š•—
				b.Delete = true;
				score += 300;
				return true;
			}
			else
			{
				return false;
			}
		});
	}
	else
	{
		Erase_if(targets, [&](const Point& t) {
			if (type == circle) {
				if (Circle(t, size).intersects(b.bulletpoint)) {
					se.playMulti();
					Circle(b.bulletpoint, b.boom).draw(Palette::Red);//”š•—
					b.Delete = true;
					score += 100;
					return true;
				}
				else
				{
					return false;
				}

			}
			else
			{
				if (Rect((int)size).setCenter(t).intersects(b.bulletpoint)) {
					se.playMulti();
					Circle(b.bulletpoint, b.boom).draw(Palette::Red);//”š•—
					b.Delete = true;
					score += 100;
					return true;
				}
				else
				{
					return false;
				}

			}
		});
	}
}

