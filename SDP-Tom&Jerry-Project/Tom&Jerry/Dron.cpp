#include<iostream>
#include<cstring>
#include "Dron.h"
#include<stdio.h>

using namespace std;

Dron::Dron(char** room,int roomCows,int roomRows,char** paths,int pSize,int tC,int tR,int jC,int jR){
    this->paths=new char*[pSize];
    for(int i=0;i<pSize;i++){
        this->paths[i]=new char[strlen(paths[i])+2];
        strncpy(this->paths[i],paths[i],strlen(paths[i]));
        this->paths[i][strlen(paths[i])]='1'+i;
        this->paths[i][strlen(paths[i])+1]='\0';
    }
    this->room=new char*[roomRows];
    for(int i=0;i<roomRows;i++){
        this->room[i]=new char[strlen(room[i])+1];
        strncpy(this->room[i],room[i],strlen(room[i]));
        this->room[i][strlen(room[i])]='\0';
    }
    this->tomCow=tC;
    this->tomRow=tR;
    this->JerryCow=jC;
    this->JerryRow=jR;
    this->pathsNumber=pSize;
    this->roomRows=roomRows;
    this->roomCows=roomCows;

    this->buildTree();
}

Dron::~Dron(){
    for(int i=0;i<this->roomRows;i++){
        delete[] this->room[i];
    }
    delete[] this->room;

    for(int i=0;i<this->pathsNumber;i++){
        delete[] this->paths[i];
    }
    delete[] this->paths;
}

void Dron::addPathInTree(int index,MyNode* t,char* path){
    if(index >= strlen(path)) return;

    if(t->one!=NULL && t->one->data==path[index])
        this->addPathInTree(index+1,t->one,path);
    else if(t->two!=NULL && t->two->data==path[index])
        this->addPathInTree(index+1,t->two,path);
    else if(t->three!=NULL && t->three->data==path[index])
        this->addPathInTree(index+1,t->three,path);
    else if(t->four!=NULL && t->four->data==path[index])
        this->addPathInTree(index+1,t->four,path);
    else{
        if(t->one==NULL){
            t->one=new MyNode(path[index]);
            this->addPathInTree(index+1,(t->one),path);
        }
        else if(t->two==NULL){
            t->two=new MyNode(path[index]);
            this->addPathInTree(index+1,(t->two),path);
        }
        else if(t->three==NULL){
            t->three=new MyNode(path[index]);
            this->addPathInTree(index+1,(t->three),path);
        }
        else if(t->one==NULL){
            t->four=new MyNode(path[index]);
            this->addPathInTree(index+1,(t->four),path);
        }
    }

}

void Dron::buildTree(){
    this->treePaths=new Tree('T');

    for(int i=0;i<this->pathsNumber;i++){
        this->addPathInTree(1,this->treePaths->root(),this->paths[i]);
    }

    this->treePaths->Print(this->treePaths->root());
}

int Dron::getNumberOfTurns(int index){
    index--;
    if(index>=this->pathsNumber) return -1;
    int len=strlen(this->paths[index])-1;
    int result=0;
    char curr;
    if(len>1) curr=this->paths[index][1];
    for(int i=2;i<len;i++){
        if(curr!=this->paths[index][i]){
            result++;
            curr=this->paths[index][i];
        }
    }

    return result;
}
int Dron::getDistance(int index){
    index--;
    if(index>=this->pathsNumber) return -1;
    return strlen(this->paths[index])-1;
}
int Dron::getPaintAmount(int index){
    index--;
    if(index>=this->pathsNumber) return -1;
    int currRow=this->tomCow;
    int currCow=this->tomRow;
    int len=strlen(this->paths[index])-1;
    int result=0;

    for(int i=1;i<len;i++){
        if(this->paths[index][i]=='U') currRow--;
        if(this->paths[index][i]=='D') currRow++;
        if(this->paths[index][i]=='L') currCow--;
        if(this->paths[index][i]=='R') currCow++;

        if(this->room[currRow][currCow]=='p') result++;
    }

    return result;
}

