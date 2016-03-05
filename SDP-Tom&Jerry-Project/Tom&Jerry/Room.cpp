#include "Room.h"
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

Room::Room()
{
    this->pathSaver=NULL;
    this->shortestRoads=NULL;
    this->numberOfShortestRoads=0;
    this->shortestPathSize=1000000;
    this->jerryCow=0;
    this->jerryRow=0;
    this->tomCow=1;
    this->tomRow=1;
    this->roomCows=3;
    this->roomRows=3;
    room=new char*[3];
    for(int i=0; i<3; i++)
    {
        this->room[i]=new char[3];
        strncpy(this->room[i],"   ",3);
    }
}

Room::~Room()
{
    this->deleteRoom();
    delete[] this->pathSaver;
    this->deleteShortestRoads();

}

void Room::deleteShortestRoads()
{
    for(int i=0; i<this->numberOfShortestRoads; i++)
    {
        delete[] this->shortestRoads[i];
    }
    delete[] this->shortestRoads;
}

void Room::readRoomFromFile(const char* path)
{
    this->deleteRoom();
    string line;
    ifstream myfile(path);
    if (myfile.is_open())
    {
        int m,n,k,l;
        myfile>>n>>m;
        this->roomCows=n;
        this->roomRows=m;
        this->room=new char*[n];
        for(int i=0; i<n; i++)
        {
            this->room[i]=new char[m];
            for(int j=0; j<m; j++)
            {
                this->room[i][j]=' ';
            }
        }
        myfile>>this->jerryCow>>this->jerryRow;
        myfile>>this->tomCow>>this->tomRow;
        myfile>>k>>l;
        for(int i=0; i<k; i++)
        {
            int r,rcpy,c;
            myfile>>c>>r;
            getline(myfile,line);
            rcpy=r;
            while(getline(myfile,line))
            {
                if(line=="===") break;
                for(int j=0; j<line.length(); j++)
                {
                    this->room[c][rcpy]=line[j];
                    rcpy++;
                }
                c++;
                rcpy=r;
            }
        }
        for(int i=0; i<l; i++)
        {
            int a,b;
            myfile>>a>>b;
            this->room[a][b]='p';
        }
        myfile.close();
        this->pathSaver=new char[this->roomCows*this->roomRows];
        this->shortestPaths();
    }
    else cout << "Unable to open file";
}

void Room::printRoom()
{
    for(int i=0; i<this->roomCows; i++)
    {
        for(int j=0; j<this->roomRows; j++)
        {
            if(i==this->tomCow && j==this->tomRow)
                cout<<"T";
            else if(i==this->jerryCow && j==this->jerryRow)
                cout<<"J";
            else
            {
                if(this->room[i][j]==' ')
                    cout<<"_";
                else
                    cout<<this->room[i][j];
            }
        }
        cout<<endl;
    }
}

void Room::deleteRoom()
{
    for(int i=0; i<this->roomCows; i++)
    {
        delete[] this->room[i];
    }
    delete[] this->room;

}

void Room::findShortestPathSize(int cow,int row,int result,char dirrection)
{
    if(cow>=this->roomCows || cow<0 || row>=this->roomRows || row<0)
    {
        return;
    }
    if(this->room[cow][row]=='*' || this->room[cow][row]=='1' || this->room[cow][row]=='P')
    {
        return;
    }
    if(cow==this->jerryCow && row==this->jerryRow)
    {
        if(result<=this->shortestPathSize)
        {
            this->shortestPathSize=result;
        }
        return;
    }
    if(this->room[cow][row]=='p')
        this->room[cow][row]='P';
    else
        this->room[cow][row]='*';
    this->pathSaver[result]=dirrection;
    //this->printRoom();
    //system("pause");

    findShortestPathSize(cow-1,row,result+1, 'U');
    findShortestPathSize(cow,row-1,result+1, 'L');
    findShortestPathSize(cow+1,row,result+1, 'D');
    findShortestPathSize(cow,row+1,result+1, 'R');

    if(this->room[cow][row]=='P')
        this->room[cow][row]='p';
    else
        this->room[cow][row]=' ';
}

void Room::findShortestPathsHelper(int cow,int row,int result,char dirrection)
{
    if(cow>=this->roomCows || cow<0 || row>=this->roomRows || row<0)
    {
        return;
    }
    if(this->room[cow][row]=='*' || this->room[cow][row]=='1' || this->room[cow][row]=='P')
    {
        return;
    }
    if(cow==this->jerryCow && row==this->jerryRow)
    {
        if(result==this->shortestPathSize)
        {
            char* roadCpy=new char[result+2];
            for(int i=0; i<result; i++)
            {
                roadCpy[i]=this->pathSaver[i];
            }
            roadCpy[result]=dirrection;
            roadCpy[result+1]='\0';
            this->addShortestRoad(roadCpy);
            delete[] roadCpy;
        }
        return;
    }
    if(this->room[cow][row]=='p')
        this->room[cow][row]='P';
    else
        this->room[cow][row]='*';
    this->pathSaver[result]=dirrection;
    //this->printRoom();
    //system("pause");

    findShortestPathsHelper(cow-1,row,result+1, 'U');
    findShortestPathsHelper(cow,row-1,result+1, 'L');
    findShortestPathsHelper(cow+1,row,result+1, 'D');
    findShortestPathsHelper(cow,row+1,result+1, 'R');

    if(this->room[cow][row]=='P')
        this->room[cow][row]='p';
    else
        this->room[cow][row]=' ';
}

void Room::shortestPaths()
{
    this->findShortestPathSize(this->tomCow,this->tomRow,0,'T');
    this->findShortestPathsHelper(this->tomCow,this->tomRow,0,'T');
}

void Room::addShortestRoad(char* road)
{
    this->numberOfShortestRoads++;
    char** roadsCpy=new char*[this->numberOfShortestRoads];
    for(int i=0; i<this->numberOfShortestRoads-1; i++)
    {
        roadsCpy[i]=new char[strlen(this->shortestRoads[i])+1];
        strncpy(roadsCpy[i],this->shortestRoads[i],strlen(this->shortestRoads[i]));
        roadsCpy[i][strlen(this->shortestRoads[i])]='\0';
    }
    roadsCpy[this->numberOfShortestRoads-1]=new char[strlen(road)+1];
    strncpy(roadsCpy[this->numberOfShortestRoads-1],road,strlen(road)+1);
    roadsCpy[this->numberOfShortestRoads-1][strlen(road)+1]='\0';

    for(int i=0; i<this->numberOfShortestRoads-1; i++)
    {
        delete[] this->shortestRoads[i];
    }
    delete[] this->shortestRoads;

    this->shortestRoads=roadsCpy;
}

void Room::printShortestPaths()
{
    for(int i=0; i<=this->numberOfShortestRoads-1; i++)
    {
        cout<<"Path "<<i<<": "<<this->shortestRoads[i]<<endl;
    }
}

char** Room::getShortestRoads()
{
    return this->shortestRoads;
}

int Room::getNumberOfShortestRoads()
{
    return this->numberOfShortestRoads;
}

int Room::getShortestPathSize()
{
    return this->shortestPathSize;
}

int Room::getJerryCow()
{
    return this->jerryCow;
}

int Room::getJerryRow()
{
    return this->jerryRow;
}

int Room::getTomCow()
{
    return this->tomCow;
}

int Room::getTomRow()
{
    return this->tomRow;
}

char** Room::getRoom(){
    return this->room;
}

int Room::getRoomCows(){
    return this->roomCows;
}
int Room::getRoomRows(){
    return  this->roomRows;
}
