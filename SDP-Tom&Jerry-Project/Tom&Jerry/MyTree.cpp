#include <iostream>
#include <stdio.h>
using namespace std;

struct MyNode
{
    char data;
    MyNode *one, *two ,*three ,*four;

    MyNode(char const& _data = char(),
           MyNode* _one = NULL,
           MyNode* _two = NULL,
           MyNode* _three = NULL,
           MyNode* _four = NULL)
        : data(_data), one(_one), two(_two) ,three(_three) ,four(_four) {}
} ;

class Tree
{
private:
    MyNode* r;
    char* depth;
    int di;

    MyNode* copyNode(MyNode* n)
    {
        if (n == NULL)
            return n;
        //cerr << "Copying tree" << endl;
        return new MyNode(n->data, copyNode(n->one),
                          copyNode(n->two),
                          copyNode(n->three),
                          copyNode(n->four));
    }

    void eraseNode(MyNode* n)
    {
        if (n != NULL)
        {
            eraseNode(n->one);
            eraseNode(n->two);
            eraseNode(n->three);
            eraseNode(n->four);
            delete n;
        }
    }

    void Push( char c )
    {
        depth[ di++ ] = ' ';
        depth[ di++ ] = c;
        depth[ di++ ] = ' ';
        depth[ di++ ] = ' ';
        depth[ di ] = '\0';
    }

    void Pop( )
    {
        depth[ di -= 4 ] = '\0';
    }

public:
    Tree(MyNode* p) : r(copyNode(p)) {}



    Tree() : r(NULL) {}
    Tree(char const& x)
        : r(new MyNode(x)),depth(new char[200]),di(0) {
        this->depth[0]='\0';
        }


    Tree(Tree const& bt) : r(copyNode(bt.r))
    {
    }

    Tree& operator=(Tree const& bt)
    {
        if (this != &bt)
        {
            eraseNode(r);
            r = copyNode(bt.r);
        }
        return *this;
    }

    ~Tree()
    {
        eraseNode(r);
    }

    void setOneTree(char c)
    {
        if(this->r->one==NULL) return;
        this->r->one=new MyNode(c);
    }

    void setTwoTree(char c)
    {
        if(this->r->two==NULL) return;
        this->r->two=new MyNode(c);
    }

    void setThreeTree(char c)
    {
        if(this->r->three==NULL) return;
        this->r->three=new MyNode(c);
    }

    void setFourTree(char c)
    {
        if(this->r->four==NULL) return;
        this->r->four=new MyNode(c);
    }

    MyNode* root()
    {
        return r;
    }

    MyNode* oneTree()
    {
        return this->r->one;
    }

    MyNode* twoTree() const
    {
        return this->r->two;
    }

    MyNode* threeTree() const
    {
        return this->r->three;
    }

    MyNode* fourTree() const
    {
        return this->r->four;
    }

    bool empty() const
    {
        return r == NULL;
    }




    void printTree(MyNode* n,int level)
    {
        if(n==NULL) return;
        if(n->data!='T' && n->data!='U' && n->data!='D' && n->data!='L' && n->data!='R')
            cout<<"------->"<<(int)(n->data)-'1';
        else cout<<n->data;

        this->printTree(n->one,level+1);
        if(n->two!=NULL)
            cout<<endl;
        for(int i=0; i<level; i++) cout<<" ";
        this->printTree(n->two,level+1);
        if(n->three!=NULL)
            cout<<endl;
        for(int i=0; i<level; i++) cout<<" ";
        this->printTree(n->three,level+1);
        if(n->four!=NULL)
            cout<<endl;
        for(int i=0; i<level; i++) cout<<" ";
        this->printTree(n->four,level+1);
        //cout<<endl;
    }

    void Print(MyNode* tree)
    {
        if(tree->data!='T' && tree->data!='U' && tree->data!='D' && tree->data!='L' && tree->data!='R')
            printf( "---(%d)\n", tree->data-(int)'1'+1);
        else
            printf( "(%c)\n", tree->data);

        if(tree->one){
            printf( "%s `--", depth );
            Push( tree->two ? '|' : ' ' );
            Print( tree->one );
            Pop( );
        }
        if(tree->two){
            printf( "%s `--", depth );
            Push( tree->three ? '|' : ' ' );
            Print( tree->two );
            Pop( );
        }
        if(tree->three){
            printf( "%s `--", depth );
            Push( tree->four ? '|' : ' ' );
            Print( tree->three );
            Pop( );
        }
        if(tree->four){
            printf( "%s `--", depth );
            Push( ' ' );
            Print( tree->four );
            Pop( );
        }
    }
};

