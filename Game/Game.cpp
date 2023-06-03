#include "head.h";

#include "View.h";
#include "Player.h";
#include "map.h";
#include "object.h"
#include "objects.h"



using namespace sf;
using namespace std;

int SCREENX = 2000;
int SCREENY = 1200;

vector<vector<int> > TileMap;
vector<vector<int> > ObjectMap;

void GenerateMap(Sprite& m_map, RenderWindow& window, Player& play, float& time, int radius) {
    int x = play.getPlayerCoordinateY() / 32;
    int y = play.getPlayerCoordinateX() / 32;
    for (int i = max(0, x - radius); i < min(HEIGHT_MAP, x + radius); i++)
        for (int j = max(0, y - radius); j < min(WIDTH_MAP, y + radius); j++)
        {
            // Рисует тайлы по карте индексов. Карта - Map, индексы -  room_item_id.
            m_map.setTextureRect(IntRect(room_item_id[TileMap[i][j]].getImageCoord().first, room_item_id[TileMap[i][j]].getImageCoord().second, room_item_id[TileMap[i][j]].getTileHeight(), room_item_id[TileMap[i][j]].getTileWidth()));
            m_map.setPosition(j * 32, i * 32); // Задаёт координаты для тайлов.
            m_map.setScale(1.001, 1.01);
            window.draw(m_map); // Отрисовывает изображение.
        }
    for (int i = max(0, x - radius); i < min(HEIGHT_MAP, x + radius); i++)
        for (int j = max(0, y - radius); j < min(WIDTH_MAP, y + radius); j++)
        {
            if (ObjectMap[i][j] == 68)
                continue;
            // Рисует тайлы по карте индексов. Карта - Map, индексы -  room_item_id.
            m_map.setTextureRect(IntRect(room_item_id[ObjectMap[i][j]].getImageCoord().first, room_item_id[ObjectMap[i][j]].getImageCoord().second, room_item_id[ObjectMap[i][j]].getTileHeight(), room_item_id[ObjectMap[i][j]].getTileWidth()));
            m_map.setPosition(j * 32, i * 32); // Задаёт координаты для тайлов.
            m_map.setScale(1.001, 1.01);
            window.draw(m_map); // Отрисовывает изображение.
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
    //sf::RenderWindow window(sf::VideoMode(), "GameProject", sf::Style::Fullscreen);
    view.reset(FloatRect(0, 0, SCREENX, SCREENY));

    Font font;
    font.loadFromFile("KarmaFuture.ttf");
    Text textCoord("", font, 48);
    Text textSpawnPoint("", font, 48);

    Image map_image;//объект изображения для карты
    map_image.loadFromFile("Tileset.png");//загружаем файл для карты
    Texture tmap;//текстура карты
    tmap.loadFromImage(map_image);//заряжаем текстуру картинкой
    Sprite m_map;//создаём спрайт для карты
    m_map.setTexture(tmap);//заливаем текстуру спрайтом

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
        GenerateMap(m_map, window, player, time, 50); // Генерация карты
        player.update(time, TileMap, ObjectMap, view);
        Map.coordinatesOfTheRoomByPlayer(player.getPlayerCoordinateX(), player.getPlayerCoordinateY(), 32);



        window.draw(player.sprite);
        window.draw(textCoord);
        window.draw(textSpawnPoint);

        window.display();
    }
    return 0;
}
