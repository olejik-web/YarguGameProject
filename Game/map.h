#include <iostream>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <stack>
#include <set>

#include "object.h"
#include "pattern.h"

using namespace std;

int HEIGHT_MAP = 128;//������ ����� ������
int WIDTH_MAP = 128;//������ ����� ������ 

class qmap
{
private:
    vector<vector<char> > mapRoom;
    vector<vector<char> > mapPaths;
    vector<vector<int> > mainMap;
    vector<vector<int> > MapWithObject;
    int minCntRoom = 7, maxCntRoom = 16;
    int sqrtCntRoom = 4; // ���-�� ������ � ������ �/��� � ������.
    int roomHieght = 16, roomWidth = 16; // ������ � ������ ������.
    int mapHieght = roomHieght * sqrtCntRoom * 2 - roomHieght;
    int mapWidth = roomWidth * sqrtCntRoom * 2 - roomWidth;
    int percentageOfPaths = 20; // ���� �������� ��������, ��� �������, ��� ���-�� ��������� ������ �� ���������.
    pair<int, int> Spawn = pair<int, int>(-1, -1);

    bool vision_barrier = false;

    //////////// ������� ��������� ��������. ////////////
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

    //////////// ��������� ���-�� ������ ////////////
    int RoomCounter()
    {
        int countRoom = 0;
        for (int i = 0; i < sqrtCntRoom; i++)
            for (int j = 0; j < sqrtCntRoom; j++)
                if (mapRoom[i][j] == 'r')
                    countRoom++;
        return countRoom;
    }

    //////////// ������� �������, ������� �� �������� ��������� �� �������. ////////////
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

    //////////// ������� ���� ����� ���������. ////////////
    void makePaths()
    {
        // ������� ������, ����� ������� ����� ������������ � ����������� �����.
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

    //////////// ��������� ���-�� ������, � ������� �� ������ ����� ������� �� ���������. ////////////
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

    //////////// ������� ���� �� ������ ������� ////////////
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

    //////////// �������� ������������� ������� ////////////
    void randomRoom()
    {
        for (int i = 0; i < sqrtCntRoom; i++)
            for (int j = 0; j < sqrtCntRoom; j++)
                mapRoom[i][j] = (rand() % 2 == 0 ? ' ' : 'r');
    }

public:

    pair<int, int> getSpawn()
    {
        if (Spawn.first == -1 && Spawn.second == -1)
            makeSpawn();
        return Spawn;
    }

    qmap()
    {
        mapRoom = vector<vector<char> >(sqrtCntRoom, vector<char>(sqrtCntRoom + 1, ' '));
        mapPaths = vector<vector<char> >(sqrtCntRoom * 2 - 1, vector<char>(sqrtCntRoom * 2, ' '));
        mainMap = vector<vector<int> >(mapHieght, vector<int>(mapWidth + 1, 14));
        MapWithObject = vector<vector<int> >(mapHieght, vector<int>(mapWidth + 1, 68));
    }

    int getMaxCntRoom() { return maxCntRoom; }
    int getMinCntRoom() { return minCntRoom; }
    int getSqrtCntRoom() { return sqrtCntRoom; }
    int getRoomHieght() { return roomHieght; }
    int getRoomWidth() { return roomWidth; }
    int getMapHieght() { return mapHieght; }
    int getMapWidth() { return mapWidth; }
    vector<vector<int> > getMainMap() { return mainMap; }
    vector<vector<int> > getMapWithObject() { return MapWithObject; }

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

    //////////// � ������, ���� ����� �������� �����, ����� ������� ����������. ////////////
    void initMap()
    {
        HEIGHT_MAP = mapHieght;//������ ����� ������
        WIDTH_MAP = mapWidth;//������ ����� ������ 
        while (true)
        {
            randomRoom(); // ������� ������� � ��������� ������.
            makeSpawn(); // ������� ��������� ������� �������.
            BFSandClear(); // ������� �������, � ������� ���������� ������� �� ������.
            makePaths(); // ������� ���� ����� ��������� ���������.
            RandCorridors(); // ������� ��������� ��������.
            int cntRoom = RoomCounter();
            int cntRelRoom = cntRelatedRooms();
            if (getMinCntRoom() <= cntRoom && cntRoom <= getMaxCntRoom())
                break;
        }
    }

    //////////// ������� ����� � ������� ////////////
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

    //////////// ������� ����� ����� �� ������� ////////////
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

    //////////// �������� �������� ����� ////////////
    void initMainMap()
    {
        for (int i = 0; i < sqrtCntRoom * 2 - 1; i++)
        {
            for (int j = 0; j < sqrtCntRoom * 2 - 1; j++)
            {
                if (mapPaths[i][j] == 'r')
                {
                    int num = rand() % Rooms.size();
                    vector<vector<int> >& RandRoom = Rooms[num];
                    for (int i1 = 0; i1 < roomHieght; i1++)
                    {
                        for (int j1 = 0; j1 < roomWidth; j1++)
                        {
                            //mainMap[i * roomHieght + i1][j * roomWidth + j1] = 0;
                            mainMap[i * roomHieght + i1][j * roomWidth + j1] = RandRoom[i1][j1];
                        }
                    }
                }

                if (mapPaths[i][j] == 's')
                {
                    int num = rand() % Rooms.size();
                    vector<vector<int> >& RandRoom = Rooms[num];
                    for (int i1 = 0; i1 < roomHieght; i1++)
                    {
                        for (int j1 = 0; j1 < roomWidth; j1++)
                        {
                            //mainMap[i * roomHieght + i1][j * roomWidth + j1] = 0;
                            mainMap[i * roomHieght + i1][j * roomWidth + j1] = RandRoom[i1][j1];
                        }
                    }

                    mainMap[i * roomHieght + roomHieght / 2][j * roomWidth + roomWidth / 2] = 20;
                }

                if (mapPaths[i][j] == '-')
                {
                    int num = rand() % CorG.size();
                    vector<vector<int> >& RandRoom = CorG[num];
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
                    int num = rand() % CorV.size();
                    vector<vector<int> >& RandRoom = CorV[num];
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

    // �������� ��������� ������ ��������������� ������.
    void addDoor()
    {
        for (int i = 0; i < sqrtCntRoom * 2 - 1; i++)
        {
            for (int j = 0; j < sqrtCntRoom * 2 - 1; j++)
            {
                if (mapPaths[i][j] == '-')
                {
                    mainMap[i * roomHieght + roomHieght / 2 - 1][j * roomWidth - 1] = 45;
                    mainMap[i * roomHieght + roomHieght / 2][j * roomWidth - 1] = 53;

                    // ���������� ����� � ��������� �����.
                    MapWithObject[i * roomHieght + roomHieght / 2 - 2][j * roomWidth - 1] = 71;
                    MapWithObject[i * roomHieght + roomHieght / 2 - 1][j * roomWidth - 1] = 71;
                    MapWithObject[i * roomHieght + roomHieght / 2][j * roomWidth - 1] = 71;

                    mainMap[i * roomHieght + roomHieght / 2 - 2][j * roomWidth - 1] = 3;
                    mainMap[i * roomHieght + roomHieght / 2 + 1][j * roomWidth - 1] = 12;

                    mainMap[i * roomHieght + roomHieght / 2 - 1][j * roomWidth - 2] = 31;
                    mainMap[i * roomHieght + roomHieght / 2][j * roomWidth - 2] = 32;

                    mainMap[i * roomHieght + roomHieght / 2 - 1][(j + 1) * roomWidth] = 45;
                    mainMap[i * roomHieght + roomHieght / 2][(j + 1) * roomWidth] = 53;

                    // ���������� ����� � ��������� ������.
                    MapWithObject[i * roomHieght + roomHieght / 2 - 2][(j + 1) * roomWidth] = 72;
                    MapWithObject[i * roomHieght + roomHieght / 2 - 1][(j + 1) * roomWidth] = 72;
                    MapWithObject[i * roomHieght + roomHieght / 2][(j + 1) * roomWidth] = 72;

                    mainMap[i * roomHieght + roomHieght / 2 - 2][(j + 1) * roomWidth] = 3;
                    mainMap[i * roomHieght + roomHieght / 2 + 1][(j + 1) * roomWidth] = 10;

                    mainMap[i * roomHieght + roomHieght / 2 - 1][(j + 1) * roomWidth + 1] = 31;
                    mainMap[i * roomHieght + roomHieght / 2][(j + 1) * roomWidth + 1] = 32;
                }
                if (mapPaths[i][j] == '|')
                {
                    mainMap[i * roomHieght - 1][j * roomWidth + roomWidth / 2] = 44;
                    mainMap[i * roomHieght - 1][j * roomWidth + roomWidth / 2 - 1] = 51;

                    // ���������� ����� � ��������� ����� ������.
                    MapWithObject[i * roomHieght - 1][j * roomWidth + roomWidth / 2] = 2;
                    MapWithObject[i * roomHieght - 1][j * roomWidth + roomWidth / 2 - 1] = 1;

                    mainMap[i * roomHieght - 1][j * roomWidth + roomWidth / 2 + 1] = 12;
                    mainMap[i * roomHieght - 1][j * roomWidth + roomWidth / 2 - 2] = 10;

                    mainMap[i * roomHieght - 2][j * roomWidth + roomWidth / 2] = 28;
                    mainMap[i * roomHieght - 2][j * roomWidth + roomWidth / 2 - 1] = 29;

                    mainMap[(i + 1) * roomHieght][j * roomWidth + roomWidth / 2] = 44;
                    mainMap[(i + 1) * roomHieght][j * roomWidth + roomWidth / 2 - 1] = 51;

                    // ���������� ����� � ��������� ����� ������.
                    MapWithObject[(i + 1) * roomHieght - 1][j * roomWidth + roomWidth / 2] = 70;
                    MapWithObject[(i + 1) * roomHieght - 1][j * roomWidth + roomWidth / 2 - 1] = 70;
                    MapWithObject[(i + 1) * roomHieght][j * roomWidth + roomWidth / 2] = 1;
                    MapWithObject[(i + 1) * roomHieght][j * roomWidth + roomWidth / 2 - 1] = 2;

                    mainMap[(i + 1) * roomHieght][j * roomWidth + roomWidth / 2 + 1] = 2;
                    mainMap[(i + 1) * roomHieght][j * roomWidth + roomWidth / 2 - 2] = 3;

                    mainMap[(i + 1) * roomHieght + 1][j * roomWidth + roomWidth / 2] = 30;
                    mainMap[(i + 1) * roomHieght + 1][j * roomWidth + roomWidth / 2 - 1] = 31;
                }
            }
        }
    }

    void SwitchTheBarrier()
    {
        vision_barrier = !vision_barrier;
        for (int i = 0; i < sqrtCntRoom * 2 - 1; i++)
        {
            for (int j = 0; j < sqrtCntRoom * 2 - 1; j++)
            {
                if (mapPaths[i][j] == '-')
                {
                    // ���������� ����� � ��������� �����.
                    MapWithObject[i * roomHieght + roomHieght / 2 - 2][j * roomWidth - 1] = (vision_barrier ? 71 : 68);
                    MapWithObject[i * roomHieght + roomHieght / 2 - 1][j * roomWidth - 1] = (vision_barrier ? 71 : 68);
                    MapWithObject[i * roomHieght + roomHieght / 2][j * roomWidth - 1] = (vision_barrier ? 71 : 68);

                    // ���������� ����� � ��������� ������.
                    MapWithObject[i * roomHieght + roomHieght / 2 - 2][(j + 1) * roomWidth] = (vision_barrier ? 72 : 68);
                    MapWithObject[i * roomHieght + roomHieght / 2 - 1][(j + 1) * roomWidth] = (vision_barrier ? 72 : 68);
                    MapWithObject[i * roomHieght + roomHieght / 2][(j + 1) * roomWidth] = (vision_barrier ? 72 : 68);
                }
                if (mapPaths[i][j] == '|')
                {
                    // ���������� ����� � ��������� ����� ������.
                    MapWithObject[i * roomHieght - 1][j * roomWidth + roomWidth / 2] = (vision_barrier ? 2 : 68);
                    MapWithObject[i * roomHieght - 1][j * roomWidth + roomWidth / 2 - 1] = (vision_barrier ? 2 : 68);

                    // ���������� ����� � ��������� ����� ������.
                    MapWithObject[(i + 1) * roomHieght - 1][j * roomWidth + roomWidth / 2] = (vision_barrier ? 70 : 68);
                    MapWithObject[(i + 1) * roomHieght - 1][j * roomWidth + roomWidth / 2 - 1] = (vision_barrier ? 70 : 68);
                    MapWithObject[(i + 1) * roomHieght][j * roomWidth + roomWidth / 2] = (vision_barrier ? 1 : 68);
                    MapWithObject[(i + 1) * roomHieght][j * roomWidth + roomWidth / 2 - 1] = (vision_barrier ? 2 : 68);
                }
            }
        }
    }

    ////////// ������� ������� �������, � ������� ��������� ��������. //////////
    pair<pair<int, int>, pair<int, int> > coordinatesOfTheRoomByPlayer(int coordPlayerX, int coordPlayerY, int TileSize)
    {
        int numRoomX = coordPlayerX / (TileSize * roomWidth * 2);
        int numRoomY = coordPlayerY / (TileSize * roomHieght * 2);
        
        pair<pair<int, int>, pair<int, int> > rez;
        rez.first.first = numRoomX * (TileSize * roomWidth * 2);
        rez.first.second = numRoomY * (TileSize * roomHieght * 2);
        rez.second.first = numRoomX * (TileSize * roomWidth * 2);
        rez.second.second = numRoomY * (TileSize * roomHieght * 2);

        return rez;
    }

    ////////// ������� ����� ����� �� ������� ////////////
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

//////////// ��������� ������ ���������, ��������� ����� � ��������� � � ������� ////////////
//int main()
//{
//    std::srand(std::time(nullptr));
//    qmap qmap;
//    qmap.initMap();
//    qmap.printPaths();
//    qmap.initMainMap();
//    qmap.printMap();
//}