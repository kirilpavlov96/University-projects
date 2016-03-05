#include<iostream>
#include<fstream>
#include<list>
using namespace std;
struct Hotel{
    char name[10];
    int age;
};

istream& operator>>(istream& is,Hotel& h){
    is.get(h.name,10);
    is>>h.age;
    return is;
}

ostream& operator<<(ostream& os,Hotel& h){
    os<<h.name<<" "<<h.age<<endl;
}

int main()
{
    list<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);

    for(list<int>::reverse_iterator it=l.rbegin();it!=l.rend();it++){
        cout<<*it<<endl;
    }
    return 0;
}
