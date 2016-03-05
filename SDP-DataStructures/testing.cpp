#include<iostream>
#include<fstream>
#include<cstring>
#include<map>
#include<set>
using namespace std;

struct Tweet{
    string ID;
    string text;
};



/*void creadMentions(string filename="tweets.bin"){
    map<string,set<string>> mentions;
    Tweet t1;
    ifstream f;
    f.open(filename,ios::binary | ios::in);
    while(!f.eof()){
        f.read((char*)&t1,sizeof(t1));
        //cout<<t1.ID<<" "<<t1.text<<endl;
        map<string,set<string>>::iterator it=mentions.find(t1.ID);
        if(it==mentions.end()){
            mentions
        }
        else{

        }
    }
    f.close();
}*/

/*int main()
{
    Tweet t;
    t.ID="kiro";
    t.text="nqkakuv text";
    Tweet t2;
    t2.ID="misho";
    t2.text="nqkakuv text 2";

    ofstream of("text.bin", ios::binary | ios::out | ios::trunc);
    of.write((char*)&t,sizeof(t));
    of.write((char*)&t2,sizeof(t2));
    //of.flush();
    of.close();


    Tweet t1;
    ifstream f;
    f.open("text.bin",ios::binary | ios::in);
    while(!f.eof()){
        f.read((char*)&t1,sizeof(t1));
        cout<<t1.ID<<" "<<t1.text<<endl;
    }
    f.close();
   // delete t1;
    return 0;
}*/
