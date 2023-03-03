#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <sstream>
#include <vector>
#include <stack>
#if defined _WIN32 || defined _WIN64

#include <Windows.h>

int SCREENX = GetSystemMetrics(SM_CXSCREEN);
int SCREENY = GetSystemMetrics(SM_CYSCREEN);

#endif

using namespace std;

float TIME;

class FPS
{
public:
    sf::Font font;
    sf::Text text;
	FPS() : mFrame(0), mFps(0) {
        font.loadFromFile("DoomFont.ttf");
        text.setFont(font);
        text.setCharacterSize(34);
        text.setFillColor(sf::Color::Red);
        text.setPosition(SCREENX - 120, 30.f);
	}
	const unsigned int getFPS() const { return mFps; }

private:
	unsigned int mFrame;
	unsigned int mFps;
	sf::Clock mClock;

public:
	void update()
	{
		if(mClock.getElapsedTime().asSeconds() >= 1.f)
		{
			mFps = mFrame;
			mFrame = 0;
			mClock.restart();
		}
		++mFrame;
        ostringstream out_fps;
		out_fps << this->getFPS();
        this->text.setString("FPS: " + out_fps.str());
	}
};

class Player {
    public:
    float x, y, w, h, dx, dy, speed; //���������� ������ � � �, ������ ������, ��������� (�� � � �� �), ���� ��������
	vector<bool>dirs; //����������� (direction) �������� ������
	sf::String File; //���� � �����������
	sf::Image image;//���� �����������
	sf::Texture texture;//���� ��������
	sf::Sprite sprite;//���� ������
	sf::Vector2f vec;
	Player(sf::String F, float X, float Y, float W, float H){  //����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������
	    speed = 0.8f;
		File = F;//��� �����+����������
		w = W; h = H;//������ � ������
		image.loadFromFile(File);
		texture.loadFromImage(image);//���������� ���� ����������� � ��������
		sprite.setTexture(texture);//�������� ������ ���������
		x = X; y = Y;//���������� ��������� �������
		sprite.setTextureRect(sf::IntRect(0, 0, w, h));  //IntRect - ���������� �����
		sf::Vector2f scale = sprite.getScale();
        sprite.setScale(scale.x * SCREENX * 0.005, scale.y * SCREENY * 0.0065);
        vec.x = 0;
        vec.y = 0;
        dirs = vector<bool>(4, false);
	}
	void update(float time) // ������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.
	{
        if (dirs[0] != dirs[1]) {
            if (dirs[0]) {vec.x = -speed;}
            if (dirs[1]) {vec.x = speed;}
        }
        if (dirs[2] != dirs[3]) {
            if (dirs[2]) {vec.y = -speed;}
            if (dirs[3]) {vec.y = speed;}
        }
        sprite.move(vec);
        vec.x = 0;
        vec.y = 0;
        dirs = vector<bool>(4, false);
	}
};

FPS GameFPS;

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREENX, SCREENY), "GameProject");
    Player player("../Assets/BlueWitch/run.png", 10.0f, 10.0f, 31.0f, 32.0f);
    while (window.isOpen())
    {
        sf::Clock clock;
        TIME = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        stack<char>st;
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))) {
            player.dirs[0] = true;
            st.push('l');
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))) {
            player.dirs[1] = true;
            st.push('r');
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))) {
            player.dirs[2] = true;
            st.push('u');
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))) { //���� ������ ������� ������� ����� ��� ���� ����� �
            player.dirs[3] = true;
            st.push('d');
		}
		// cout << player.dirs[0] << " " << player.dirs[1] << " " << player.dirs[2] << " " << player.dirs[3] << "\n";
        /* while (!st.empty()) {
            cout << st.top() << " ";
            st.pop();
        }
        cout << "\n";*/
        player.update(TIME);
        GameFPS.update();
        window.clear();
        window.draw(player.sprite);
        window.draw(GameFPS.text);
        window.display();
    }
    return 0;
}
