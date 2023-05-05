#include "head.h";

#include "View.h";
#include "Player.h";
#include "map.h";
#include "object.h"
#include "objects.h"



using namespace sf;
using namespace std;

int SCREENX = 1000;
int SCREENY = 600;

vector<vector<int> > TileMap;
vector<vector<int> > ObjectMap;

void GenerateMap(Sprite& m_map, Sprite& o_map, RenderWindow& window, Player& play, float& time) {
    for (int i = 0; i < HEIGHT_MAP; i++)
        for (int j = 0; j < WIDTH_MAP; j++)
        {
            // Рисует тайлы по карте индексов. Карта - Map, индексы -  room_item_id.
            m_map.setTextureRect(IntRect(room_item_id[TileMap[i][j]].getImageCoord().first, room_item_id[TileMap[i][j]].getImageCoord().second, room_item_id[TileMap[i][j]].getTileHeight(), room_item_id[TileMap[i][j]].getTileWidth()));
            m_map.setPosition(j * 32, i * 32); // Задаёт координаты для тайлов.
            window.draw(m_map); // Отрисовывает изображение.
        }
    for (int i = 0; i < HEIGHT_MAP; i++)
        for (int j = 0; j < WIDTH_MAP; j++)
        {
            if (ObjectMap[i][j] == 68)
                continue;
            // Рисует тайлы по карте индексов. Карта - Map, индексы -  room_item_id.
            o_map.setTextureRect(IntRect(room_item_id[ObjectMap[i][j]].getImageCoord().first, room_item_id[ObjectMap[i][j]].getImageCoord().second, room_item_id[ObjectMap[i][j]].getTileHeight(), room_item_id[ObjectMap[i][j]].getTileWidth()));
            o_map.setPosition(j * 32, i * 32); // Задаёт координаты для тайлов.
            window.draw(o_map); // Отрисовывает изображение.
        }

}

int main()
{
    std::srand(std::time(nullptr));
    qmap Map;
    Map.initMap();
    Map.initMainMap();
    Map.addDoor();
    //Map.printMap();

    TileMap = Map.getMainMap();
    ObjectMap = Map.getMapWithObject();

    sf::RenderWindow window(sf::VideoMode(SCREENX, SCREENY), "GameProject");
    view.reset(FloatRect(0, 0, SCREENX, SCREENY));

    Font font;
    font.loadFromFile("KarmaFuture.ttf");
    Text textCoord("", font, 16);
    Text textSpawnPoint("", font, 16);

    Image map_image;//объект изображения для карты
    map_image.loadFromFile("Tileset.png");//загружаем файл для карты
    Texture tmap;//текстура карты
    tmap.loadFromImage(map_image);//заряжаем текстуру картинкой
    Sprite m_map;//создаём спрайт для карты
    m_map.setTexture(tmap);//заливаем текстуру спрайтом

    Sprite o_map;
    o_map.setTexture(tmap);

    sf::Clock clock;
    sf::Clock Working_hours;
    int X = Map.getSpawn().first;
    int Y = Map.getSpawn().second;
    //Player player("Assets/AnimationSheet_Character.png", 50, 50, 32, 32);
    Player player("Assets/AnimationSheet_Character.png",
        Map.getSpawn(), Map.getRoomWidth(), Map.getRoomHieght(), 32, 32);

    
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        cout << time << '\n';
        clock.restart();
        time /= 3000;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::G) && Working_hours.getElapsedTime().asSeconds() > 2)
        {
            Map.SwitchTheBarrier();
            ObjectMap = Map.getMapWithObject();
            Working_hours.restart();
        }

        window.setView(view); // обновление камеры

        std::ostringstream playerCoordX;
        playerCoordX << player.getPlayerCoordinateX();
        std::ostringstream playerCoordY;
        playerCoordY << player.getPlayerCoordinateY();

        std::ostringstream SpawnPointX;
        SpawnPointX << Map.getSpawn().first;
        std::ostringstream SpawnPointY;
        SpawnPointY << Map.getSpawn().second;

        textCoord.setString("Score " + playerCoordX.str() + " " + playerCoordY.str());
        textCoord.setPosition(view.getCenter().x - SCREENX / 2, view.getCenter().y - SCREENY / 2);
        textSpawnPoint.setString("Spawn coord: " + SpawnPointX.str() + " " + SpawnPointY.str());
        textSpawnPoint.setPosition(view.getCenter().x - SCREENX / 2, view.getCenter().y - SCREENY / 2 + 32);

        window.clear(Color(128, 106, 89));
        GenerateMap(m_map, o_map, window, player, time); // Генерация карты
        player.update(time, TileMap, view);

        window.draw(player.sprite);
        window.draw(textCoord);
        window.draw(textSpawnPoint);

        window.display();
    }
    return 0;
}
