#include <iostream>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <stack>
#include <set>

#include "pattern.h"

using namespace std;

class qmap
{
private:
    vector<vector<char> > mapRoom;
    vector<vector<char> > mapPaths;
    vector<vector<char> > mainMap;
    int minCntRoom = 7, maxCntRoom = 15;
    int sqrtCntRoom = 4; // Кол-во комнат в высоты и/или в ширину.
    int roomHieght = 8, roomWidth = 8; // Высота и ширина комнат.
    int mapHieght = roomHieght * sqrtCntRoom * 2 - roomHieght;
    int mapWidth = roomWidth * sqrtCntRoom * 2 - roomWidth;
    int percentageOfPaths = 20; // Шанс удаления коридора, при условии, что кол-во доступных комнат не изменится.
    pair<int, int> Spawn = pair<int, int>(-1, -1);

    //////////// Удалить случайные коридоры. ////////////
    void RandCorridors()
    {
        int cnt = cntRelatedRooms();
        char rez;
        for (int i = 0; i < sqrtCntRoom * 2 - 1; i++)
        {
            for (int j = 0; j < sqrtCntRoom * 2 - 1; j++)
            {
                if ((mapPaths[i][j] == '-' || mapPaths[i][j] == '|'))
                {
                    rez = mapPaths[i][j];
                    mapPaths[i][j] = ' ';
                    if (cntRelatedRooms() == cnt)
                    {
                        mapPaths[i][j] = (rand() % 100 > percentageOfPaths ? rez : ' ');
                    }
                    else
                        mapPaths[i][j] = rez;
                }
            }
        }
    }

    //////////// Посчитать кол-во комнат ////////////
    int RoomCounter()
    {
        int countRoom = 0;
        for (int i = 0; i < sqrtCntRoom; i++)
            for (int j = 0; j < sqrtCntRoom; j++)
                if (mapRoom[i][j] == 'r')
                    countRoom++;
        return countRoom;
    }

    //////////// Удалить комнаты, которые не являются соседними со спавном. ////////////
    void BFSandClear()
    {
        stack<pair<int, int>> Paths;
        Paths.push(Spawn);

        vector<vector<char> > RoomColour(sqrtCntRoom, vector<char>(sqrtCntRoom, ' '));
        RoomColour[Spawn.first][Spawn.second] = '.';
        while (!Paths.empty())
        {
            int x = Paths.top().first;
            int y = Paths.top().second;
            Paths.pop();
            if (x > 0)
            {
                if (mapRoom[x - 1][y] == 'r' && RoomColour[x - 1][y] != '.')
                {
                    Paths.push(pair<int, int>(x - 1, y));
                    RoomColour[x - 1][y] = '.';
                }
            }
            if (x < sqrtCntRoom - 1)
            {
                if (mapRoom[x + 1][y] == 'r' && RoomColour[x + 1][y] != '.')
                {
                    Paths.push(pair<int, int>(x + 1, y));
                    RoomColour[x + 1][y] = '.';
                }
            }

            if (y > 0)
            {
                if (mapRoom[x][y - 1] == 'r' && RoomColour[x][y - 1] != '.')
                {
                    Paths.push(pair<int, int>(x, y - 1));
                    RoomColour[x][y - 1] = '.';
                }
            }

            if (y < sqrtCntRoom - 1)
            {
                if (mapRoom[x][y + 1] == 'r' && RoomColour[x][y + 1] != '.')
                {
                    Paths.push(pair<int, int>(x, y + 1));
                    RoomColour[x][y + 1] = '.';
                }
            }
        }

        for (int i = 0; i < sqrtCntRoom; i++)
            for (int j = 0; j < sqrtCntRoom; j++)
                mapRoom[i][j] = ' ';

        for (int i = 0; i < sqrtCntRoom; i++)
            for (int j = 0; j < sqrtCntRoom; j++)
            {
                if (RoomColour[i][j] == '.')
                {
                    mapRoom[i][j] = 'r';
                    if (i == Spawn.first && j == Spawn.second)
                        mapRoom[i][j] = 's';
                }
            }
    }

    //////////// Создать пути между комнатами. ////////////
    void makePaths()
    {
        // Очищаем вектор, иначе комнаты будут наслаиваться с предыдущего цыкла.
        for (int i = 0; i < sqrtCntRoom * 2 - 1; i++)
            for (int j = 0; j < sqrtCntRoom * 2 - 1; j++)
                mapPaths[i][j] = ' ';

        for (int i = 0; i < sqrtCntRoom; i++)
        {
            for (int j = 0; j < sqrtCntRoom; j++)
            {
                if (mapRoom[i][j] == 'r' || mapRoom[i][j] == 's')
                {
                    mapPaths[i * 2][j * 2] = mapRoom[i][j];
                    if (i > 0 && (mapRoom[i - 1][j] == 'r' || mapRoom[i - 1][j] == 's'))
                    {
                        mapPaths[i * 2 - 1][j * 2] = '|';
                    }
                    if (i < sqrtCntRoom - 1 && (mapRoom[i + 1][j] == 'r' || mapRoom[i + 1][j] == 's'))
                    {
                        mapPaths[i * 2 + 1][j * 2] = '|';
                    }
                    if (j > 0 && (mapRoom[i][j - 1] == 'r' || mapRoom[i][j - 1] == 's'))
                    {
                        mapPaths[i * 2][j * 2 - 1] = '-';
                    }
                    if (j < sqrtCntRoom - 1 && (mapRoom[i][j + 1] == 'r' || mapRoom[i][j + 1] == 's'))
                    {
                        mapPaths[i * 2][j * 2 + 1] = '-';
                    }
                }
            }
        }
    }

    //////////// Посчитать кол-во комнат, в которые из спавна можно попасть по коридорам. ////////////
    int cntRelatedRooms()
    {
        stack<pair<int, int>> Paths;
        Paths.push(pair<int, int>(Spawn.first * 2, Spawn.second * 2));

        vector<vector<char> > RoomColour(sqrtCntRoom * 2 - 1, vector<char>(sqrtCntRoom * 2 - 1, ' '));
        RoomColour[Spawn.first * 2][Spawn.second * 2] = '.';
        while (!Paths.empty())
        {
            int x = Paths.top().first;
            int y = Paths.top().second;
            Paths.pop();
            if (x > 0)
            {
                if (mapPaths[x - 1][y] == '|' && RoomColour[x - 2][y] != '.')
                {
                    Paths.push(pair<int, int>(x - 2, y));
                    RoomColour[x - 2][y] = '.';
                }
            }
            if (x < sqrtCntRoom * 2 - 2)
            {
                if (mapPaths[x + 1][y] == '|' && RoomColour[x + 2][y] != '.')
                {
                    Paths.push(pair<int, int>(x + 2, y));
                    RoomColour[x + 2][y] = '.';
                }
            }

            if (y > 0)
            {
                if (mapPaths[x][y - 1] == '-' && RoomColour[x][y - 2] != '.')
                {
                    Paths.push(pair<int, int>(x, y - 2));
                    RoomColour[x][y - 2] = '.';
                }
            }

            if (y < sqrtCntRoom * 2 - 2)
            {
                if (mapPaths[x][y + 1] == '-' && RoomColour[x][y + 2] != '.')
                {
                    Paths.push(pair<int, int>(x, y + 2));
                    RoomColour[x][y + 2] = '.';
                }
            }
        }


        int cnt = 0;
        for (int i = 0; i < sqrtCntRoom * 2 - 1; i++)
        {
            for (int j = 0; j < sqrtCntRoom * 2 - 1; j++)
            {
                //cout << RoomColour[i][j];
                if (RoomColour[i][j] == '.')
                {
                    cnt++;
                }
            }
            //cout << endl;
        }

        return cnt;
    }

    //////////// Сделать одну из комнат спавном ////////////
    void makeSpawn()
    {
        while (Spawn.first == -1 && Spawn.second == -1)
        {
            bool flag = true;
            for (int i = 0; i < sqrtCntRoom && flag; i++)
                for (int j = 0; j < sqrtCntRoom && flag; j++)
                {
                    mapRoom[i][j] = (mapRoom[i][j] == 'r' ? (rand() % 100 == 5 ? 's' : 'r') : ' ');
                    if (mapRoom[i][j] == 's')
                    {
                        flag = !flag;
                        Spawn = pair<int, int>(i, j);
                        return;
                    }
                }
        }
    }

    pair<int, int> getSpawn()
    {
        if (Spawn.first == -1 && Spawn.second == -1)
            makeSpawn();
        return Spawn;
    }

    //////////// Случайно сгенерировать комнаты ////////////
    void randomRoom()
    {
        for (int i = 0; i < sqrtCntRoom; i++)
            for (int j = 0; j < sqrtCntRoom; j++)
                mapRoom[i][j] = (rand() % 2 == 0 ? ' ' : 'r');
    }

public:

    qmap()
    {
        mapRoom = vector<vector<char> >(sqrtCntRoom, vector<char>(sqrtCntRoom, ' '));
        mapPaths = vector<vector<char> >(sqrtCntRoom * 2 - 1, vector<char>(sqrtCntRoom * 2 - 1, ' '));
        mainMap = vector<vector<char> >(mapHieght, vector<char>(mapWidth, ' '));
    }

    int getMaxCntRoom() { return maxCntRoom; }
    int getMinCntRoom() { return minCntRoom; }
    int getSqrtCntRoom() { return sqrtCntRoom; }
    int getRoomHieght() { return roomHieght; }
    int getRoomWidth() { return roomWidth; }
    int getMapHieght() { return mapHieght; }
    int getMapWidth() { return mapWidth; }
    vector<vector<char> > getMainMap() { return mainMap; }

    void setMaxCntRoom(int value) { maxCntRoom = value; }
    void setMinCntRoom(int value) { minCntRoom = value; }
    void setSqrtCntRoom(int value)
    {
        sqrtCntRoom = value;
        mapHieght = roomHieght * sqrtCntRoom - roomHieght;
        mapWidth = roomWidth * sqrtCntRoom - roomWidth;
    }
    void setRoomHieght(int value)
    {
        roomHieght = value;
        mapHieght = roomHieght * sqrtCntRoom - roomHieght;
    }
    void setRoomWidth(int value)
    {
        roomWidth = value;
        mapWidth = roomWidth * sqrtCntRoom - roomWidth;
    }
    void setPercentageOfPaths(int value) { percentageOfPaths = value; }

    //////////// В случае, если нужно обновить карту, после задание параметров. ////////////
    void initMap()
    {
        while (true)
        {
            randomRoom(); // Создать комнаты в случайных местах.
            makeSpawn(); // Сделать случайную комнату спавном.
            BFSandClear(); // Удалить комнаты, в которые невозможно попасть от спавна.
            makePaths(); // Сделать пути между соседними комнатами.
            RandCorridors(); // Удалить случайные коридоры.
            int cntRoom = RoomCounter();
            int cntRelRoom = cntRelatedRooms();
            if (getMinCntRoom() <= cntRoom && cntRoom <= getMaxCntRoom())
                break;
        }
    }

    //////////// Вывести карту в консоль ////////////
    void printRoom()
    {
        for (int i = 0; i < mapRoom.size(); i++)
        {
            for (int j = 0; j < mapRoom.size(); j++)
            {
                cout << mapRoom[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }

    //////////// Вывести карту путей на консоль ////////////
    void printPaths()
    {
        for (int i = 0; i < mapPaths.size(); i++)
        {
            for (int j = 0; j < mapPaths.size(); j++)
            {
                cout << mapPaths[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }

    //////////// Создание основной карты ////////////
    void initMainMap()
    {
        for (int i = 0; i < sqrtCntRoom * 2 - 1; i++)
        {
            for (int j = 0; j < sqrtCntRoom * 2 - 1; j++)
            {
                if (mapPaths[i][j] == 'r' || mapPaths[i][j] == 's')
                {
                    int num = rand() % rooms.size();
                    vector<string>& RandRoom = rooms[num];
                    for (int i1 = 0; i1 < roomHieght; i1++)
                    {
                        for (int j1 = 0; j1 < roomWidth; j1++)
                        {
                            mainMap[i * roomHieght + i1][j * roomWidth + j1] = RandRoom[i1][j1];
                        }
                    }
                }
                if (mapPaths[i][j] == '-')
                {
                    int num = rand() % corG.size();
                    vector<string>& RandRoom = corG[num];
                    for (int i1 = 0; i1 < roomHieght; i1++)
                    {
                        for (int j1 = 0; j1 < roomWidth; j1++)
                        {
                            mainMap[i * roomHieght + i1][j * roomWidth + j1] = RandRoom[i1][j1];
                        }
                    }
                }
                if (mapPaths[i][j] == '|')
                {
                    int num = rand() % corV.size();
                    vector<string>& RandRoom = corV[num];
                    for (int i1 = 0; i1 < roomHieght; i1++)
                    {
                        for (int j1 = 0; j1 < roomWidth; j1++)
                        {
                            mainMap[i * roomHieght + i1][j * roomWidth + j1] = RandRoom[i1][j1];
                        }
                    }
                }
            }
        }
    }

    //////////// Вывести карту путей на консоль ////////////
    void printMap()
    {
        for (int i = 0; i < mapHieght; i++)
        {
            for (int j = 0; j < mapWidth; j++)
            {
                cout << mainMap[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }
};

//////////// Небольшой пример программы, создающий карту и выводящий её в консоль ////////////
//int main()
//{
//    std::srand(std::time(nullptr));
//    qmap qmap;
//    qmap.initMap();
//    qmap.printPaths();
//    qmap.initMainMap();
//    qmap.printMap();
//}