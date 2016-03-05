#include <iostream>
#include <map>
#include <fstream>
#include <windows.h>
#include <string>
using namespace std;

void readFromFile(string fileName,map<string,pair<double,string>>& facultyReg){
    string line;
    ifstream file(fileName);
    while(getline(file,line)){
        string id,comment;
        int grade=0,spaces=0,oldI=0;
        for(int i=0;spaces<2;i++){
            if(line[i]==' ') {
                if(spaces==0)
                    id=line.substr(oldI,i-oldI);
                else{
                    grade=(int)line[i-1]-(int)'0';
                    comment=line.substr(i+1,line.length()-i-1);
                }
                spaces++;
                oldI=i;
            }
        }
        map<string,pair<double,string>>::iterator it;
        it=facultyReg.find(id);
        if(it==facultyReg.end())
            facultyReg.insert(pair<string,pair<double,string> >(id,pair<double,string>(grade,comment)));
        else{
            it->second.first=(it->second.first+grade)/2;
            if(it->second.second.length()<comment.length())
                it->second.second=comment;
        }
    }
    file.close();
}

void printToBinaryFile(string fileName,map<string,pair<double,string>>& facultyReg){
    ofstream of(fileName, ios::binary|ios::out|ios::trunc);
    for(auto& x:facultyReg){
        of.write((char*)&x.first,sizeof(char)*10);
        of.write((char*)&x.second.first,sizeof(double));
        of.write((char*)&x.second.second,sizeof(char)*1000);
    }
    of.close();
}
/*
int main() {

    map<string,pair<double,string>> facultyReg;
    readFromFile("kiko.txt",facultyReg);
    printToBinaryFile("kiko.bin",facultyReg);

    ifstream of("kiko.bin", ios::binary|ios::in);
    while(of.eof()){
        char* id=new char[100];
        char* comment=new char[1000];
        double grade;
        of.read(id,sizeof(char)*10);
        of.read((char*)&grade,sizeof(double));
        of.read(comment,sizeof(char)*1000);
        cout<<id<<" "<<grade<<" "<<comment<<endl;
        system("pause");
        delete id;
        delete comment;
    }
    of.close();
	return 0;
}
*/
