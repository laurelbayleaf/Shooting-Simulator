//
//
//if (Input::KeyUp.clicked && equiped != GUN::null)
//{
//	equiped++;
//}
//if (Input::KeyDown.clicked && equiped != GUN::normalcanonn)
//{
//	equiped--;
//}
//
//Circle shot(ammopos, size); //’e
//
//if (Input::MouseL.clicked && !shoot)
//{
//	shoot = 1; //’e”­ŽË
//	switch (equiped)
//	{
//	case normalcanonn:
//		scanonn.playMulti(0.4);
//		size = 40;
//		time = 50;
//		break;
//	case laser:
//		slaser.playMulti();
//		size = 50;
//		time = 30;
//		break;
//	case missile:
//		smissile.playMulti();
//		size = 50;
//		time = 50;
//	default:
//		break;
//	}
//}
//
//if (shoot)
//{
//	switch (equiped)
//	{
//	case normalcanonn:
//		shot.draw();
//		font(time).draw();
//
//		break;
//	case laser:
//		size -= size * 0.15;
//		time--;
//		shot.draw(Palette::Aqua);
//		break;
//	case missile:
//		size--;
//		ammopos.x -= 0.1*(ammopos.x - Mouse::Pos().x);
//		ammopos.y -= 0.1*(ammopos.y - Mouse::Pos().y);
//		time--;
//		font(shot.x, L" ", shot.y).draw();
//		font(Mouse::Pos()).draw(0, 40);
//		shot.draw(Palette::Brown);
//		break;
//	default:
//		break;
//	}
//
//	if (time <= 0)
//	{
//		Hit = 1;
//		shoot = 0;
//		size = 0;
//	}
//}
//else {
//	ammopos = Mouse::Pos(); //ˆÊ’u“¯Šú
//}
//if (Hit) {
//	c1 = o1.intersects(shot);
//	Hit = 0;
//	Erase_if(targets, [&](const Vec2& t) {
//		if (t.distanceFrom(ammopos) < 15.0) {
//			hit.playMulti();
//			Circle(shot.x, shot.y, 30).draw(Palette::Red);//”š•—
//			return true;
//
//		}
//		else
//		{
//			return false;
//		}
//	});
//}
//if (c1) {
//	hit.playMulti();
//	Circle(shot.x, shot.y, 30).draw(Palette::Red);//”š•—
//	c1 = 0;
//}
