
# include <Siv3D.hpp>
# include <HamFramework.hpp>
# include "shooting.h"

void Main()
{
	Camera2D camera;
	const std::array<s3d::Key, 6> keyConfig =
	{
		s3d::Input::KeyW, s3d::Input::KeyA, s3d::Input::KeyS, s3d::Input::KeyD,
		s3d::Input::KeyShift, s3d::Input::KeyControl
	};
	camera.setKeyConfig(keyConfig);
	const Sound titlebgm(L"resource/titleBGM.mp3");
	const Sound titlesound(L"resource/title.mp3");
	const Sound next(L"resource/next.mp3");
	const Sound mode(L"resource/mode.mp3");
	const Sound start(L"resource/start.mp3");
	const Sound sp(L"resource/startpause.mp3");
	const Sound ep(L"resource/endpause.mp3");
	const Sound comando(L"resource/comando.mp3");
	const Sound huge(L"resource/huge.mp3");
	const Sound cannon(L"resource/cannnon.mp3");
	const Sound heal(L"resource/heal.mp3");

	const Sound s1(L"resource/bassdrum.mp3");
	const Sound s2(L"resource/snare.mp3");
	const Sound s3(L"resource/hat.mp3");
	const Sound s4(L"resource/dum.mp3");
	const Sound sdo(L"resource/belldo.mp3");
	const Sound sfa(L"resource/bellfa.mp3");
	const Sound sso(L"resource/bellso.mp3");
	const Sound sra(L"resource/bellra.mp3");

	const Sound stageclear(L"resource/clear.mp3");
	const Sound gameover(L"resource/gameover.mp3");
	const Sound ranking(L"resource/ranking.mp3");

	const Font font(20);
	const Font title(25, Typeface::Medium);
	const Font clear(30, Typeface::Medium);
	const Font coment(15);

	//int stage = 1, stagescore = 300, score = 0, roll = 0;
	int gamestage = 100;
	//double radian = Radians(roll);


	//int scores[6] = { 0,0,0,0,0,0 };
	//std::string name[6] = { "A","B","C","D","E","F" };
	//String str;
	//int command = 0; //隠しコマンド用フラグ
	//String commando;


	//////////////////////////////////////////////////////////////////////
	enum SCENE {
		TITLE,
		GUIDANCE1,
		GUIDANCE2,
		MODE,
		GAME,
		PAUSE,
		CLEAR,
		GAMEOVER,
		RANKING
	};
	SCENE scene = GAME;

	enum GUN
	{
		normalcanonn,
		laser,
		missile,
		null,
	};

	const Sound scanonn(L"resource/canonn.mp3");
	const Sound slaser(L"resource/laser.mp3");
	const Sound smissile(L"resource/missile.mp3");
	const Sound hit(L"resource/hit.mp3");

	Rect o1(0, 200, 100, 50);
	int posx = 5;
	o1.x = (Window::Width() - 200) / 2;
	int equiped = normalcanonn;
	Array<Vec2> bullets0, bullets1, bullet2, targets;
				//normal,straight,guided

	//武器種

	shooting gun_normalcannon(40, 50, 60, 0, -1, Palette::White,scanonn);
	shooting gun_laser(50, 30, 15, 1, -1, Palette::Aqua,slaser);
	shooting gun_missile(50, 50, 120, 2, 0.1, Palette::Brown,smissile);

	while (System::Update())
	{
		switch (scene)
		{
		case TITLE:
			break;
		case GUIDANCE1:
			break;
		case GUIDANCE2:
			break;
		case MODE:
			break;
		case GAME: {
			//if (Input::KeyShift.pressed) {
			//	s3d::Transformer2D trans(s3d::Mat3x2::Scale(rate));
			//}
			camera.update();
			{

				const auto t1 = camera.createTransformer();

				font(L"\n\nカメラ").draw();

				// target
				if (Input::KeyT.clicked)
					targets.emplace_back(Random(30,640),Random(30,480));

				for (const auto& target : targets)
					RectF(30, 30).setCenter(target).draw(Palette::Limegreen);

				 

				o1.moveBy(posx, 0);
				if ((o1.x < 0 && posx < 0) || (Window::Width() - gamestage < o1.x && posx > 0))
				{

					posx *= -1; //反射
					if (posx > 0) {
						o1.x = 0;
					}
					else {
						o1.x = Window::Width() - gamestage;
					}

					s1.playMulti();
				}
				o1.draw(Palette::Blue);


				//発射機構


				//武器選択
				if (Input::KeyUp.clicked && equiped != GUN::null)
				{
					equiped++;
				}
				if (Input::KeyDown.clicked && equiped != GUN::normalcanonn)
				{
					equiped--;
				}

				//武器毎の発射処理
				switch (equiped)
				{
				case normalcanonn:
					gun_normalcannon.shoot();
					break;
				case laser:
					gun_laser.shoot();
					break;
				case missile:
					gun_missile.shoot();
					break;
				default:
					break;
				}


				//弾丸更新
				gun_normalcannon.bullet();
				gun_laser.bullet();
				gun_missile.bullet();


				//命中判定
				if (gun_normalcannon.gethit())
				{
					gun_normalcannon.unhit();
					if (o1.intersects(gun_normalcannon.makebullet())) {
						hit.playMulti();
						Circle(gun_normalcannon.ammopos(), 30).draw(Palette::Red);//爆風
					}

					Erase_if(targets, [&](const Vec2& t) {
						if (t.distanceFrom(gun_normalcannon.ammopos()) < 15.0) {
							hit.playMulti();
							Circle(gun_normalcannon.ammopos(), 30).draw(Palette::Red);//爆風
							return true;
						}
						else
						{
							return false;
						}
					});

				}
				if (gun_laser.gethit())
				{
					gun_laser.unhit();
					if (o1.intersects(gun_laser.makebullet())) {
						hit.playMulti();
						Circle(gun_laser.ammopos(), 30).draw(Palette::Red);//爆風
					}

					Erase_if(targets, [&](const Vec2& t) {
						if (t.distanceFrom(gun_laser.ammopos()) < 15.0) {
							hit.playMulti();
							Circle(gun_laser.ammopos(), 30).draw(Palette::Red);//爆風
							return true;
						}
						else
						{
							return false;
						}
					});

				}
				if (gun_missile.gethit())
				{
					gun_missile.unhit();
					if (o1.intersects(gun_missile.makebullet())) {
						hit.playMulti();
						Circle(gun_missile.ammopos(), 50).draw(Palette::Red);//爆風
					}

					Erase_if(targets, [&](const Vec2& t) {
						if (t.distanceFrom(gun_missile.ammopos()) < 15.0) {
							hit.playMulti();
							Circle(gun_missile.ammopos(), 50).draw(Palette::Red);//爆風
							return true;
						}
						else
						{
							return false;
						}
					});

				}


				//照準
				Line(Mouse::Pos().x - 50, Mouse::Pos().y, Mouse::Pos().x + 50, Mouse::Pos().y).draw();
				Line(Mouse::Pos().x, Mouse::Pos().y - 50, Mouse::Pos().x, Mouse::Pos().y + 50).draw();
				Circle sightframe(Mouse::Pos(), 50);
				sightframe.drawFrame(3, 0);
				//sightframe.drawFrame(0, 2000,Palette::Black);

			}
			camera.draw(Palette::Orange);
			//ポーズ
			font(L"PAUSE:P").draw(450, 20);
			if (Input::KeyP.clicked) {
				scene = PAUSE;
				sp.playMulti();
			}
			break;
		}
		case PAUSE:
			title(L"P A U S E").drawCenter(100);
			font(L"続けるにはＰキー").drawCenter(200);
			if (Input::KeyP.clicked) {
				scene = GAME;
				ep.playMulti();
			}
			break;
		case CLEAR:
			break;
		case GAMEOVER:
			break;
		case RANKING:
			break;
		default:
			break;
		}
	}
}
