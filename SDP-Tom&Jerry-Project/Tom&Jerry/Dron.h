#ifndef DRON_H_INCLUDED
#define DRON_H_INCLUDED
#include "MyTree.cpp"

class Dron{
private:
    int tomCow,tomRow;
    int JerryCow,JerryRow;
    int pathsNumber;
    int roomCows,roomRows;
    char** paths;
    char** room;
    Tree* treePaths;

    void buildTree();
    void addPathInTree(int,MyNode*,char*);
public:
    ~Dron();
    Dron(char**,int,int,char**,int,int,int,int,int);
    int getNumberOfTurns(int);
    int getDistance(int);
    int getPaintAmount(int);
};

#endif // DRON_H_INCLUDED
