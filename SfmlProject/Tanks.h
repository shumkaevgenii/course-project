#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

const int HEIGHT_MAP = 15;
const int WIDTH_MAP = 19;


sf::String TileMap[HEIGHT_MAP] = {
	"0000000000000000000",
	"0                 0",
	"0                 0",
	"0    1        1   0",
	"0    1        1   0",
	"0    1        1   0",
	"0    1        1   0",
	"0        1        0",
	"0        1        0",
	"0        1        0",
	"0    1        1   0",
	"0    1        1   0",
	"0    1        1   0",
	"0                 0",
	"0000000000000000000"
};

class Panzer {
	int Score;
public:
	float w, h, dx, dy, speed;
	float x, y;
	int dir;
	bool life;
	sf::String File;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	Panzer(sf::String F, float X, float Y, float W, float H)
	{
		Score = dx = dy = speed = dir = 0;
		File = F; life = true;
		w = W; h = H;
		image.loadFromFile("image/" + File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(sf::IntRect(84, 0, W, H));
	}

	void interaction(int H, int W) {
		for (int i = y / 40; i < (y + H) / 40; i++)
			for (int j = x / 40; j < (x + W) / 40; j++)

				if (TileMap[i][j] == '0' || TileMap[i][j] == '1' || TileMap[i][j] == '2')
				{
					if (dy > 0)	y = i * 40 - H;

					if (dy < 0)	y = i * 40 + 40;

					if (dx > 0)	x = j * 40 - W;

					if (dx < 0)	x = j * 40 + 40;
				}


	}

	void update(float time)
	{
		switch (dir)
		{
		case 0: dx = speed; dy = 0; break;
		case 1: dx = -speed; dy = 0; break;
		case 2: dx = 0; dy = speed; break;
		case 3: dx = 0; dy = -speed; break;
		}

		x += dx * time;
		y += dy * time;

		speed = 0;
		interaction(h, w);
		sprite.setPosition(x, y);
	}

	float getTankcoordinateX() {
		return this->x;
	}
	float getTankcoordinateY() {
		return this->y;
	}
	int getScore() { return this->Score; }
	void IncreaseScore() { this->Score++; }
};

class Bullet {
public:
	float dx, dy, speed;
	float x, y;
	bool life;
	int dir;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;

	Bullet() {
		x = y = dx = dy = 0;
		speed = 0.9;
		life = false;
		image.loadFromFile("image/3.png");
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(245, 200, -10, 10));
	}

	void interaction(int H, int W) {
		for (int i = y / 40; i < (y + H) / 40; i++)
			for (int j = x / 40; j < (x + W) / 40; j++)
				if (TileMap[i][j] == '0' || TileMap[i][j] == '1') {
					life = false; x = -100;
				}
	}

	void ShotBullet(float time) {

		switch (dir)
		{
		case 0: dx = speed; dy = 0; break;
		case 1: dx = -speed; dy = 0; break;
		case 2: dx = 0; dy = speed; break;
		case 3: dx = 0; dy = -speed; break;
		}
		x += dx * time;
		y += dy * time;
		interaction(5, 5);
		sprite.setPosition(x + 14, y + 14);

	}

	int getBulletX() { return x; }
	int getBulletY() { return y; }

};


void Game()
{
	sf::Font font;
	font.loadFromFile("CyrilicOld.ttf");
	sf::Text text("", font, 20);
	text.setStyle(sf::Text::Bold);

	sf::Image map_image;
	map_image.loadFromFile("image/MA2P.png");
	sf::Texture map;
	map.loadFromImage(map_image);
	sf::Sprite s_map;
	s_map.setTexture(map);

	Bullet BulletOfFirstTank;
	Bullet BulletOfSecondTank;
	Panzer FirstTank("3.png", 50, 50, 40, 40);
	Panzer SecondTank("3.png", 680, 520, 40, 40);

	float Frame = 0;
	float BangTimeCounter = 0;
	int GameTime = 0;

	sf::Clock TankMovementTime;
	sf::Clock PlayTime;
	sf::Clock EndPlayTime;
	sf::Clock TankDetonationTime;

	int Up = 310;
	int Down = 344;
	int Right = 305;
	int Left = 340;

	bool HitFirst = false;
	bool HitSecond = false;

	bool isNewGame = false;

	bool isDrawTank1 = true;
	bool isDrawTank2 = true;


	sf::RenderWindow window(sf::VideoMode(760, 600), "Game by Zhenya");

	sf::Event event;
	window.pollEvent(event); // (*Window) - указатель на переменную "window", где хранитс€ окно sfml

	while (window.isOpen())
	{

		float time = TankMovementTime.getElapsedTime().asMicroseconds();
		TankMovementTime.restart(); time /= 800;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::P)
					window.close();

				if ((event.key.code == sf::Keyboard::Space) && (FirstTank.life && SecondTank.life)) {
					BulletOfFirstTank.life = true; BulletOfFirstTank.x = FirstTank.getTankcoordinateX(), BulletOfFirstTank.y = FirstTank.getTankcoordinateY(); BulletOfFirstTank.dir = FirstTank.dir;
				}

				if ((event.key.code == sf::Keyboard::RShift) && (FirstTank.life && SecondTank.life)) {
					BulletOfSecondTank.life = true; BulletOfSecondTank.x = SecondTank.getTankcoordinateX(), BulletOfSecondTank.y = SecondTank.getTankcoordinateY(); BulletOfSecondTank.dir = SecondTank.dir;
				}
			}
		}


		////////////////////////Tanks control////////////////////////////////////////////
		if (FirstTank.life) {


			//////////First tank control////////////
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				FirstTank.dir = 1; FirstTank.speed = 0.15;
				Frame += 0.005*time;
				if (Frame > 7) { Frame -= 7; Left = 340; }
				FirstTank.sprite.setTextureRect(sf::IntRect(525, Left - int(Frame) * 43, -40, -40));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				FirstTank.dir = 0; FirstTank.speed = 0.15;
				Frame += 0.005*time;
				if (Frame > 7) { Frame -= 7; Right = 305; }
				FirstTank.sprite.setTextureRect(sf::IntRect(485, Right - int(Frame) * 43, 40, 40));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				FirstTank.dir = 3; FirstTank.speed = 0.15;
				Frame += 0.005*time;
				if (Frame > 7) {
					Up = 310;  Frame -= 7;
				}
				FirstTank.sprite.setTextureRect(sf::IntRect(Up - int(Frame) * 43, 97, 40, 40));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				FirstTank.dir = 2; FirstTank.speed = 0.15;
				Frame += 0.005*time;
				if (Frame > 7) {
					Down = 344; Frame -= 7;
				}
				FirstTank.sprite.setTextureRect(sf::IntRect(Down - int(Frame) * 43, 138, -40, -40));
			}
		}
		if (SecondTank.life) {

			//////////////Second tank control/////////////////
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				SecondTank.dir = 1; SecondTank.speed = 0.15;
				Frame += 0.005*time;
				if (Frame > 7) { Frame -= 7; Left = 340; }
				SecondTank.sprite.setTextureRect(sf::IntRect(525, Left - int(Frame) * 43, -40, -40));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				SecondTank.dir = 0; SecondTank.speed = 0.15;
				Frame += 0.005*time;
				if (Frame > 7) { Frame -= 7; Right = 305; }
				SecondTank.sprite.setTextureRect(sf::IntRect(485, Right - int(Frame) * 43, 40, 40));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				SecondTank.dir = 3; SecondTank.speed = 0.15;
				Frame += 0.005*time;
				if (Frame > 7) {
					Up = 310;  Frame -= 7;
				}
				SecondTank.sprite.setTextureRect(sf::IntRect(Up - int(Frame) * 43, 97, 40, 40));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				SecondTank.dir = 2; SecondTank.speed = 0.15;
				Frame += 0.005*time;
				if (Frame > 7) {
					Down = 344; Frame -= 7;
				}
				SecondTank.sprite.setTextureRect(sf::IntRect(Down - int(Frame) * 43, 138, -40, -40));
			}

		}


		FirstTank.update(time);
		SecondTank.update(time);


		if (BulletOfFirstTank.life)  BulletOfFirstTank.ShotBullet(time);
		if (BulletOfSecondTank.life) BulletOfSecondTank.ShotBullet(time);


		//////////////////////////////Hit of First tank/////////////////////////////////////////
		if ((BulletOfFirstTank.getBulletX() >= SecondTank.getTankcoordinateX() - 20 && BulletOfFirstTank.getBulletX() <= SecondTank.getTankcoordinateX() + 25)
			&& ((BulletOfFirstTank.getBulletY() >= SecondTank.getTankcoordinateY() - 20 && BulletOfFirstTank.getBulletY() <= SecondTank.getTankcoordinateY() + 25))) {
			HitFirst = true; BulletOfFirstTank.x = -100; BulletOfFirstTank.y = -100;
			SecondTank.life = false; FirstTank.IncreaseScore();
			TankDetonationTime.restart();
		}
		if (HitFirst)
		{
			BangTimeCounter = TankDetonationTime.getElapsedTime().asMicroseconds() / 1000;
			SecondTank.sprite.setTextureRect(sf::IntRect(56, 193, 25, 25));
			if ((int)BangTimeCounter > (int)200)
				SecondTank.sprite.setTextureRect(sf::IntRect(95, 189, 36, 36));
			if ((int)BangTimeCounter > (int)400)
				SecondTank.sprite.setTextureRect(sf::IntRect(136, 186, 43, 38));
			if (int(BangTimeCounter) > (int)900) {
				isDrawTank2 = false; TankDetonationTime.restart();
				isNewGame = true;
				if (FirstTank.getScore() > 100 || SecondTank.getScore() > 100)
				{
					break;
				}
			}
		}

		///////////////////////////Hit of second tank//////////////////////////////////
		if ((BulletOfSecondTank.getBulletX() >= FirstTank.getTankcoordinateX() - 20 && BulletOfSecondTank.getBulletX() <= FirstTank.getTankcoordinateX() + 25)
			&& ((BulletOfSecondTank.getBulletY() >= FirstTank.getTankcoordinateY() - 20 && BulletOfSecondTank.getBulletY() <= FirstTank.getTankcoordinateY() + 25))) {
			HitSecond = true; BulletOfSecondTank.x = -100; BulletOfSecondTank.y = -100;
			FirstTank.life = false; SecondTank.IncreaseScore();
			TankDetonationTime.restart();
		}
		if (HitSecond)
		{
			BangTimeCounter = TankDetonationTime.getElapsedTime().asMicroseconds() / 1000;
			FirstTank.sprite.setTextureRect(sf::IntRect(56, 193, 25, 25));
			if ((int)BangTimeCounter > (int)200)
				FirstTank.sprite.setTextureRect(sf::IntRect(95, 189, 36, 36));
			if ((int)BangTimeCounter > (int)400)
				FirstTank.sprite.setTextureRect(sf::IntRect(136, 186, 43, 38));
			if (int(BangTimeCounter) > (int)900) {
				isDrawTank1 = false; TankDetonationTime.restart();
				isNewGame = true;
				if (FirstTank.getScore() > 2 || SecondTank.getScore() > 2)
				{
					break;
				}
			}
		}

		window.clear();

		////////////////////DrawMap///////////////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(sf::IntRect(0, 0, 40, 40));
				if (TileMap[i][j] == '0') s_map.setTextureRect(sf::IntRect(0, 120, 40, 40));
				if (TileMap[i][j] == '1')s_map.setTextureRect(sf::IntRect(238, 121, 40, 40));

				s_map.setPosition(j * 40, i * 40);

				window.draw(s_map);
			}


		////////////////////////Show play time and scores of tanks/////////////////////////////////////
		GameTime = PlayTime.getElapsedTime().asSeconds();
		std::ostringstream TIME, SCORE1, SCORE2;
		TIME << GameTime; SCORE1 << FirstTank.getScore(); SCORE2 << SecondTank.getScore();
		text.setString("¬рем€ игры:" + TIME.str() + "           —чет  " + SCORE1.str() + '-' + SCORE2.str());
		text.setPosition(20, 5);
		window.draw(text);

		/////////////////////Draw images of tanks//////////////////////////////////////
		if (isDrawTank1)window.draw(FirstTank.sprite);
		if (isDrawTank2)window.draw(SecondTank.sprite);

		/////////////////////Draw images of bullets//////////////////////////////////////
		if (BulletOfFirstTank.life) window.draw(BulletOfFirstTank.sprite);
		if (BulletOfSecondTank.life) window.draw(BulletOfSecondTank.sprite);

		/////////////////////////To begin game again////////////////////////////
		if (isNewGame) {
			int Delay = EndPlayTime.getElapsedTime().asSeconds();
			if (Delay > 0) {
				isNewGame = false;
				isNewGame = false;
				HitSecond = HitFirst = false;
				isDrawTank1 = isDrawTank2 = true;
				FirstTank.life = SecondTank.life = true;
				FirstTank.y = FirstTank.x = 50; SecondTank.x = 680; SecondTank.y = 520;
				FirstTank.sprite.setTextureRect(sf::IntRect(Up - int(Frame) * 43, 97, 40, 40));
				SecondTank.sprite.setTextureRect(sf::IntRect(Up - int(Frame) * 43, 97, 40, 40));
				BulletOfFirstTank.x = -100; BulletOfSecondTank.x = -100;
			}
		}
		else EndPlayTime.restart();

		window.display();
	}
	return;
}