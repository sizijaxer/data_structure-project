#include <iostream>
#include <string>
#include <blocks.cpp>
using namespace std;
/////////////map/////////////
int Wildth;
int Height;
char **Map;
/////////////////////////////
////////////shape/////////
class create_shapes{
public:
    wstring blocks;
};
class shapes_I1:public create_shapes{
public:
    shapes_I1(){
        blocks.append(L"1...");
        blocks.append(L"1...");
        blocks.append(L"1...");
        blocks.append(L"1...");
    }
private:
    string name = "I1";
};
////////////////////////
int main()
{
    cin>>Height;
    Height +=1;
    cin>>Wildth;
    Wildth +=2;
    Map = new char*[Height];
    for(int i=0;i<Height;i++) Map[i] = new char[Wildth];
    for(int i=0;i<Height;i++){
        for(int j=0;j<Wildth;j++){
            Map[i][j] = (j==0 || j==Wildth-1 || i==Height-1)? '#':'0';
        }
    }
    for(int i=0;i<Height;i++){
        for(int j=0;j<Wildth;j++){
            cout<<Map[i][j];
        }
        cout<<endl;
    }
    return 0;
}