
# include <Siv3D.hpp>
# include <HamFramework.hpp>
# include "shooting.h"
# include "target.h"

void swp(int *a, int *b) {
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
void swap(std::string *a, std::string *b) {
	std::string tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void sorter(int sort[6], std::string names[6])
{
	int i, j;
	for (i = 0; i<6; i++) {
		for (j = i + 1; j<6; j++) {
			if (sort[i]<sort[j]) {
				swp(&sort[i], &sort[j]);
				swap(&names[i], &names[j]);
			}
		}
	}
}


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
	const Sound sdo2(L"resource/belldo2.mp3");
	const Sound sfa(L"resource/bellfa.mp3");
	//const Sound sso(L"resource/bellso.mp3");
	//const Sound sra(L"resource/bellra.mp3");

	const Sound stageclear(L"resource/clear.mp3");
	const Sound gameover(L"resource/gameover.mp3");
	const Sound ranking(L"resource/ranking.mp3");

	const Font font(20);
	const Font title(25, Typeface::Medium);
	const Font clear(30, Typeface::Medium);
	const Font coment(15);
	const Font timeup(70, Typeface::Heavy, FontStyle::Outline);
	timeup.changeOutlineStyle(TextOutlineStyle(Palette::Yellow, Palette::Whitesmoke, 2.0));
	
	int score;
	int gamemode = 0;

	int scores[6] = { 0,0,0,0,0,0 };
	std::string name[6] = { "A","B","C","D","E","F" };
	String str;

	EventTimer eventTimer;
	eventTimer.addEvent(L"3", 0.0s);
	eventTimer.addEvent(L"2", 1.0s);
	eventTimer.addEvent(L"1", 2.0s);
	eventTimer.addEvent(L"GO!", 3.0s);
	eventTimer.addEvent(L"start", 4.0s);
	bool startswitch = false;
	String count,equipedname;

	Stopwatch countdown;
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

	shooting gun_normalcannon(40, 50, 50, 30, shooting::TYPE::normal, -1, 10, Palette::White, scannon);
	shooting gun_laser(50, 30, 15, 30, shooting::TYPE::straight, -1, 30, Palette::Aqua, slaser);
	shooting gun_missile(50, 50, 120, 60, shooting::TYPE::guided, 0.1, 100, Palette::Brown, smissile);



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
			font(L"クリックで次へ").drawCenter(400);
			if (Input::MouseL.clicked)
			{
				scene = GUIDANCE1;
				next.playMulti();
			}
			break;
		case GUIDANCE1:
			font(L"一分以内で的を狙って弾を当てよう！\n発射する度に、\n弾丸のコストでスコアが下がるよ！").draw(10,20);
			font(L"照準はマウス操作\n左クリックで発射！\n左右キーで武器変更\n\tクリックで次へ").draw(300, 250);
			if (Input::MouseL.clicked)
			{
				scene = GUIDANCE2;
				next.playMulti();
			}
			break;
		case GUIDANCE2:
			font(L"SCORE\t:現在のスコア\n残り時間\t:現在の残り時間").draw(10,10);
			font(L"\n\n\n\tクリックで次へ").draw(300, 300);
			if (Input::MouseL.clicked)
			{
				gamemode = 1;
				scene = MODE;
				mode.playMulti();
			}

			break;
		case MODE:
			font(L"モードを選んでね").draw();
			font(L"ぽやしみ～\t：かんたん。寝てても出来る\n難しくNASA\t：ふつう。最初はこれでしょ\nむずいンゴ!?\t：むずかしい。上級者向け\nオワタ\t\t：オワタ式。ミス即終了\n無理\t\t\t：無理").draw(50, 50);
			font(L"クリックで決定してゲームスタート！").draw(10, 400);
			if (Input::KeyUp.clicked && gamemode != 0)
			{
				gamemode--;
			}
			if (Input::KeyDown.clicked && gamemode != 4)
			{
				gamemode++;
			}
			Line(10, (gamemode + 1) * 40 + 30, 40, (gamemode + 1) * 40 + 30).drawArrow(1, { 40, 30 }, Palette::White);

			if (Input::MouseL.clicked)
			{
				scene = PRECEDE;
				titlebgm.stop();

				//初期化
				eventTimer.start();
				startswitch = false;
				small_box.score = 0;
				small_circle.score = 0;
				small_moved_box.score = 0;
				gun_normalcannon.tortalcost = 0;
				gun_laser.tortalcost = 0;
				gun_missile.tortalcost = 0;
				eventTimer.restart();
				countdown.reset();
				small_box.reset();
				small_circle.reset();
				small_moved_box.reset();
			}
			break;
		case PRECEDE: {
			const auto elapsed = eventTimer.update();
			if (eventTimer.onTriggered(L"3")) {
				count = L"3";
				if (!startswitch) {
					startswitch = true;
					sfa.playMulti();
				}
			}

			if (eventTimer.onTriggered(L"2")) {
				count = L"2";
				if (startswitch) {
					startswitch = false;
					sfa.playMulti();
				}
			}
			if (eventTimer.onTriggered(L"1")) {
				count = L"1";
				if (!startswitch) {
					startswitch = true;
					sfa.playMulti();
				}
			}
			if (eventTimer.onTriggered(L"GO!")) {
				count = L"GO!";
				if (startswitch) {
					startswitch = false;
					sdo2.playMulti();
				}
			}
			clear(count).drawCenter(140);
			if (eventTimer.onTriggered(L"start")) {
				countdown.start();
				scene = GAME;
			}
			break;
		}
		case GAME: {
			score = small_box.score + small_circle.score + small_moved_box.score - (gun_normalcannon.tortalcost + gun_laser.tortalcost + gun_missile.tortalcost);
			camera.update();
			{
				const auto t1 = camera.createTransformer();

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
					random.x = Random(30, 540);
					random.y = Random(30, 430);
					small_moved_box.addtarget(random);
				}

				//的描画

				small_box.drawtarget();
				small_circle.drawtarget();
				small_moved_box.drawtarget();


				////  発射機構  ////


				//武器選択
				if (Input::KeyRight.clicked && equiped != GUN::null)
				{
					equiped++;
				}
				if (Input::KeyLeft.clicked && equiped != GUN::normalcannon)
				{
					equiped--;
				}

				//武器毎の発射処理
				if (countdown.s() < 60)
				{
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
						small_box.boomtarget(b,hit);
						small_circle.boomtarget(b,hit);
						small_moved_box.boomtarget(b,hit);
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

			}
			camera.draw(Palette::Orange);

			////  画面表示  ////
			
			switch (equiped)
			{
			case normalcannon:
				font(L"EQUIPED:normalcannon").draw(10, 440);
				Rect(10, 400, (gun_normalcannon.rate - gun_normalcannon.charge)*(200/ gun_normalcannon.rate), 40).draw(Palette::Yellow);
				break;
			case laser:
				font(L"EQUIPED:laser").draw(10, 440);
				Rect(10, 400, (gun_laser.rate - gun_laser.charge)*(200/ gun_laser.rate), 40).draw(Palette::Yellow);
				break;
			case missile:
				font(L"EQUIPED:missile").draw(10, 440);
				Rect(10, 400, (gun_missile.rate - gun_missile.charge)*((double)200/ gun_missile.rate), 40).draw(Palette::Yellow);
				break;
			default:
				break;
			}
			if (countdown.s() < 60)
			{
			font(L"残り", 60 - countdown.s(), L"秒").draw();
			font(L"SCORE:", score).draw(0, 40);
			}

			//ポーズ

			font(L"PAUSE:P").draw(450, 20);
			if (Input::KeyP.clicked) {
				scene = PAUSE;
				countdown.pause();
				sp.playMulti();
			}
			if (countdown.s() >= 60)
			{
				if (!startswitch)
				{
					startswitch = true;
					start.play();
				}
				timeup(L"TIME UP!").drawCenter(120);
				if (countdown.s() >= 63) {
					scene = GAMEOVER;
					gameover.play();
					gameover.setVolume(0.4);
				}
			}

			break;
		}
		case PAUSE:
			title(L"P A U S E").drawCenter(100);
			font(L"続けるにはＰキー").drawCenter(200);
			if (Input::KeyP.clicked) {
				scene = GAME;
				countdown.start();
				ep.playMulti();
			}
			break;
		case GAMEOVER: {
			font(L"終了！お疲れ様でした").drawCenter(50);
			font(L"あなたのスコア：", score).drawCenter(80);
			font(L"Enterキーを押して次へ").drawCenter(400);
			coment(L"素材提供：魔王魂").draw(450, 350);
			if (score > scores[4]) {
				Input::GetCharsHelper(str);
				name[5] = str.narrow();
				scores[5] = score;
				font(L"おめでとう！ハイスコア！").drawCenter(170, Palette::Yellow);
				font(L"あなたの名前を残しませんか?\n\n↑ここで入力してね").drawCenter(210, Palette::Yellow);
				font(L"名前：").draw(100, 250);
				font(str).drawCenter(250);

			}
			if (Input::KeyEnter.clicked)
			{
				scene = RANKING;
				gameover.stop();
				sorter(scores, name);
				str = L"";
			}
			break;
		}
		case RANKING: {
			ranking.play();
			clear(L"ランキング").drawCenter(50);
			font(L"1位\t" + CharacterSet::Widen(name[0])).draw(150, 120);
			font(L"2位\t" + CharacterSet::Widen(name[1])).draw(150, 160);
			font(L"3位\t" + CharacterSet::Widen(name[2])).draw(150, 200);
			font(L"4位\t" + CharacterSet::Widen(name[3])).draw(150, 240);
			font(L"5位\t" + CharacterSet::Widen(name[4])).draw(150, 280);
			font(scores[0]).draw(450, 120);
			font(scores[1]).draw(450, 160);
			font(scores[2]).draw(450, 200);
			font(scores[3]).draw(450, 240);
			font(scores[4]).draw(450, 280);
			font(L"タイトルに戻るにはクリック").drawCenter(400);
			if (Input::MouseL.clicked)
			{
				scene = TITLE;
				ranking.pause();
			}
			break;
		}
		default:
			break;
		}
	}
}