#include <cmath>
#include "Room.h"
#include "Dron.h"
#include<windows.h>

int main() {
    /*Room r;
    r.readRoomFromFile("data/room2.in");
    r.printRoom();
    r.printShortestPaths();
    Dron d(r.getRoom(),
           r.getRoomRows(),
           r.getRoomCows(),
           r.getShortestRoads(),
           r.getNumberOfShortestRoads(),
           r.getTomCow(),
           r.getTomRow(),
           r.getJerryCow(),
           r.getJerryRow());

    int choice=0;
    cout<<"Please choose path index!"<<endl;
    cin>>choice;
    cout<<"Distance: "<<d.getDistance(choice)<<endl;
    cout<<"Number of turns: "<<d.getNumberOfTurns(choice)<<endl;
    cout<<"The amount spilled paint: "<<d.getPaintAmount(choice)<<endl;*/
    string a;
    getline(cin,a);
    cout<<a<<endl;
	return 0;
}
