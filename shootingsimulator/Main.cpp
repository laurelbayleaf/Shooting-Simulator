
# include <Siv3D.hpp>
# include <HamFramework.hpp>
# include "shooting.h"
# include "target.h"

//void hittargetsystem(shooting);

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

	//const Sound s1(L"resource/bassdrum.mp3");
	//const Sound s2(L"resource/snare.mp3");
	//const Sound s3(L"resource/hat.mp3");
	//const Sound s4(L"resource/dum.mp3");
	//const Sound sdo(L"resource/belldo.mp3");
	//const Sound sfa(L"resource/bellfa.mp3");
	//const Sound sso(L"resource/bellso.mp3");
	//const Sound sra(L"resource/bellra.mp3");

	const Sound stageclear(L"resource/clear.mp3");
	const Sound gameover(L"resource/gameover.mp3");
	const Sound ranking(L"resource/ranking.mp3");

	const Font font(20);
	const Font title(25, Typeface::Medium);
	const Font clear(30, Typeface::Medium);
	const Font coment(15);

	//int stage = 1, stagescore = 300, 
	int score = 0;
		//, roll = 0;
	//double radian = Radians(roll);
	int gamemode = 0;

	//int scores[6] = { 0,0,0,0,0,0 };
	//std::string name[6] = { "A","B","C","D","E","F" };
	//String str;
	//int command = 0; //隠しコマンド用フラグ
	//String commando;

	EventTimer eventTimer;
	eventTimer.addEvent(L"3", 0.0s);
	eventTimer.addEvent(L"2", 1.0s);
	eventTimer.addEvent(L"1", 2.0s);
	eventTimer.addEvent(L"GO!", 3.0s);
	eventTimer.addEvent(L"start", 4.0s);
	String count,equipedname;
//////////////////////////////////////////////////////////////////////
	enum SCENE {
		TITLE,
		GUIDANCE1,
		GUIDANCE2,
		MODE,
		PRECEDE,
		GAME,
		PAUSE,
		CLEAR,
		GAMEOVER,
		RANKING
	};
	SCENE scene = TITLE;

	//使用可能武器

	enum GUN
	{
		normalcannon,
		laser,
		missile,
		null,
	};
	int equiped = normalcannon;

	const Sound scannon(L"resource/cannon.mp3");
	const Sound slaser(L"resource/laser.mp3");
	const Sound smissile(L"resource/missile.mp3");
	const Sound hit(L"resource/hit.mp3");

	//武器種

	shooting gun_normalcannon(40, 50, 50, 30, shooting::TYPE::normal, -1, Palette::White,scannon);
	shooting gun_laser(50, 30, 15, 30, shooting::TYPE::straight, -1, Palette::Aqua,slaser);
	shooting gun_missile(50, 50, 120, 50, shooting::TYPE::guided, 0.1, Palette::Brown,smissile);



	//的種

	target small_circle(target::TYPE::circle, 15,-1, -1, Palette::Limegreen);
	target small_box(target::TYPE::box, 30, -1,-1, Palette::Aquamarine);
	target small_moved_box(target::TYPE::moved_box,100,50,5,Palette::Blue);

	while (System::Update())
	{
		switch (scene)
		{
		case TITLE:
			titlebgm.play();
			title(L"Shooting Simulator").drawCenter(100);
			font(L"スペースキーを押してね").drawCenter(400);
			if (Input::KeySpace.clicked)
			{
				scene = GUIDANCE1;
				next.playMulti();
			}
			break;
		case GUIDANCE1:
			font(L" 的をよく狙おう！").draw(0,20);
			font(L"照準はマウスで\n左クリックで発射！\n\n\tZキーで次へ").draw(300, 300);
			if (Input::KeyZ.clicked)
			{
				scene = MODE;
				next.playMulti();
			}
			break;
		case GUIDANCE2:
			font(L"\n STAGE\t\t\t:現在のステージ\n SCORE\t\t\t:現在のスコア\n STAGESCORE\t:そのステージの持ち点\n\t\t\t\t ミスすると減点\n\t\t\t\t これがなくなると\n\t\t\t\t ゲームオーバー!").draw();
			font(L"\n\n\n\tZキーで次へ").draw(300, 300);
			if (Input::KeyZ.clicked)
			{
				gamemode = 1;
				scene = MODE;
				mode.playMulti();
			}

			break;
		case MODE:
			font(L"モードを選んでね").draw();
			font(L"ぽやしみ～\t：かんたん。寝てても出来る\n難しくNASA\t：ふつう。最初はこれでしょ\nむずいンゴ!?\t：むずかしい。上級者向け\nオワタ\t\t：オワタ式。ミス即終了\n無理\t\t\t：無理").draw(50, 50);
			font(L"Zキーで決定してゲームスタート！").draw(10, 400);
			if (Input::KeyUp.clicked && gamemode != 0)
			{
				gamemode--;
			}
			if (Input::KeyDown.clicked && gamemode != 4)
			{
				gamemode++;
			}
			Line(10, (gamemode + 1) * 40 + 30, 40, (gamemode + 1) * 40 + 30).drawArrow(1, { 40, 30 }, Palette::White);

			if (Input::KeyZ.clicked)
			{
				scene = PRECEDE;
				titlebgm.stop();
				//start.play();
				eventTimer.start();
			}
			break;
		case PRECEDE: {
			const auto elapsed = eventTimer.update();
			if (eventTimer.onTriggered(L"3"))
				count = L"3";
			if (eventTimer.onTriggered(L"2"))
				count = L"2";
			if (eventTimer.onTriggered(L"1"))
				count = L"1";
			if (eventTimer.onTriggered(L"GO!"))
				count = L"GO!";
			clear(count).drawCenter(140);
			if (eventTimer.onTriggered(L"start"))
					scene = GAME;
			break;
		}
		case GAME: {
			//if (Input::KeyShift.pressed) {
			//	s3d::Transformer2D trans(s3d::Mat3x2::Scale(rate));
			//}
			score = small_box.score + small_circle.score + small_moved_box.score;
			camera.update();
			{

				const auto t1 = camera.createTransformer();
				switch (equiped)
				{
				case normalcannon:
				font(L"EQUIPED:normalcannon").draw(20, 400);
					break;
				case laser:
				font(L"EQUIPED:laser").draw(20, 400);
					break;
				case missile:
				font(L"EQUIPED:missile").draw(20, 400);
					break;
				default:
					break;
				}
				font(L"\n\nカメラ").draw();
				font(L"SCORE:",score).draw(20, 440);

				////  的関連  ////


				//的追加
				if (Input::KeyT.clicked) {
					Point random;
					random.x = Random(30, 640);
					random.y = Random(30, 480);
					small_box.addtarget(random);
				}
				if (Input::KeyY.clicked) {
					Point random;
					random.x = Random(30, 590);
					random.y = Random(30, 430);
					small_circle.addtarget(random);
				}
				if (Input::KeyU.clicked) {
					Point random;
					random.x = Random(30,540);
					random.y = Random(30,430);
					small_moved_box.addtarget(random);
				}

				//的描画

				small_box.drawtarget();
				small_circle.drawtarget();
				small_moved_box.drawtarget();


				////  発射機構  ////


				//武器選択
				if (Input::KeyUp.clicked && equiped != GUN::null)
				{
					equiped++;
				}
				if (Input::KeyDown.clicked && equiped != GUN::normalcannon)
				{
					equiped--;
				}

				//武器毎の発射処理
				switch (equiped)
				{
				case normalcannon:
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

				for (auto& b : gun_normalcannon.bullets)
					if (b.hit)
					{
						b.Delete = true;
						small_box.hittarget(b, hit);
						small_circle.hittarget(b, hit);
						small_moved_box.hittarget(b, hit);
					}
				for (auto& b : gun_laser.bullets)
					if (b.hit)
					{
						b.Delete = true;
						small_box.hittarget(b, hit);
						small_circle.hittarget(b, hit);
						small_moved_box.hittarget(b, hit);
					}
				for (auto& b : gun_missile.bullets)
					if (b.hit)
					{
						b.Delete = true;
						small_box.hittarget(b, hit);
						small_circle.hittarget(b, hit);
						small_moved_box.hittarget(b, hit);
					}

				//弾の消去

				gun_normalcannon.bulletdelete();
				gun_laser.bulletdelete();
				gun_missile.bulletdelete();

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