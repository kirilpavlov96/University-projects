#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

class Room{
private:
    int jerryCow,jerryRow,tomCow,tomRow;
    int roomCows,roomRows,shortestPathSize,numberOfShortestRoads;
    char** room;
    char** shortestRoads;
    char* pathSaver;
    void findShortestPathSize(int,int,int,char);
    void findShortestPathsHelper(int,int,int,char);
    void addShortestRoad(char*);
    void shortestPaths();
    void deleteRoom();
    void deleteShortestRoads();
public:
    Room();
    ~Room();
    void printRoom();
    void readRoomFromFile(const char*);
    void printShortestPaths();
    char** getShortestRoads();
    char** getRoom();
    int getRoomCows();
    int getRoomRows();
    int getNumberOfShortestRoads();
    int getShortestPathSize();
    int getJerryCow();
    int getJerryRow();
    int getTomCow();
    int getTomRow();
    int** getPlacesToPaint();
    int getPlacesToPaintNumber();
};

#endif // ROOM_H_INCLUDED
