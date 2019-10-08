#include <iostream>
#include <string>
#include <unistd.h>
#include <windows.h>
using namespace std;
/////////////map/////////////
int Width;
int Height;
char *Map;
/////////////////////////////
////////////shape/////////
////////////////////////
wstring blocks[20];
void game_process();
void show_map(char* Map);
int decide_blocks(string block_name);
bool isfit(int nblock,int posX,int posY);
bool det_line(char* sub_Map,int current_y,int current_x,int id);
int get_boom();
void initial_blocks();
int main()
{
    ///initial blocks
    /*cin>>Height;
    Height +=1;
    cin>>Width;
    Width +=2;*/
    Width = 5+2;
    Height = 10+2;
    Map = new char[Height*Width];
    for(int i=0;i<Height;i++){
        for(int j=0;j<Width;j++){
            Map[i*Width+j] = (j == 0 || j == Width - 1 || i == Height - 1) ? '#' : '0';
        }
    }
    show_map(Map);
    game_process();
    return 0;
}
void game_process()
{
    bool game_over = false;
    while(!game_over){
        initial_blocks();
        string block_name;
        int current_x;
        cin>>block_name;
        int id = decide_blocks(block_name);
        if(id==-1)
        {
            cout<<"no such block"<<endl;
            return;
        }
        cout<<block_name<<" id:"<<id<<endl;
        if(block_name=="END")return;
        cin>>current_x;
        int current_y = 0;
        ///game_logic
        /// only_go_down
        ///test if block can go down
        while(1){
            char sub_Map[Width*Height];
            for(int i=0;i<Width*Height;i++)sub_Map[i] = Map[i];
            cout <<"id:"<<id<<endl;
            if(isfit(id,current_x,current_y+1))
            {
                //cout<<"GOGO ";
                current_y+=1;
                for(int i=0;i<Width*Height;i++)sub_Map[i] = Map[i];
                for(int px=0;px<4;px++)
                    for(int py=0;py<4;py++)
                    {
                        if(blocks[id][py * 4 + px] != L'.')
                        {   //cout<<"put!!";
                            sub_Map[(current_y + py) * Width + (current_x + px)] = '1';
                        }
                    }
                show_map(sub_Map);
            }
            else /// stop the block and put it on map
            {   
                for(int px=0;px<4;px++)
                    for(int py=0;py<4;py++)
                    {
                        if(blocks[id][py * 4 + px] != L'.')
                        {   //cout<<"put!!";
                            Map[(current_y + py) * Width + (current_x + px)] = '1';
                        }
                    }
                ////檢查line
                int lines[Height];
                int index;
                int number_of_line=0;
                for(int py=0;py<4;py++)
                {
                    bool have_line=true;
                    if(current_y+py<Height-1)
                    {
                        for(int px=1;px<Width-1;px++)
                        {
                            if(Map[(current_y+py)*Width+px]=='0') have_line=false;
                        }
                    }
                    if(have_line)
                    {
                        for(int px=1;px<Width-1;px++)
                        {
                            ////make it to "===="
                            Map[(current_y+py)*Width+px] = '=';
                        }
                        show_map(Map);
                        ////make i to "00000"
                        for(int px=1;px<Width-1;px++)
                        {
                            ////make it to "0000"
                            Map[(current_y+py)*Width+px] = '0';
                        }
                        number_of_line++;
                        cout<<"lines="<<number_of_line<<endl;
                        ////全部往下number_of_lines列
                        for(int i=0;i<Width*Height;i++) sub_Map[i] = Map[i];
                        for(int sub_py=current_y+py;sub_py>0;sub_py--)
                        {
                            for(int px=1;px<Width-1;px++)
                            {
                                Map[(sub_py)*Width+px] = sub_Map[(sub_py-1)*Width+px];
                            }
                        }
                        for(int px=1;px<Width-1;px++)Map[px]='0';
                    }
                }  
                show_map(Map);
                break;
            }
        }

    }
}
bool isfit(int id,int nPosX,int nPosY)///nposx=0;///nposy=1
{
    for(int px=0;px<4;px++)
    {
        for(int py=0;py<4;py++)
        {   //cout<<"det.. ";
            int map_pos = (nPosY + py) * Width + (nPosX + px);
            if(nPosY + py >= 0 && nPosY + py < Height)
			{
				// In Bounds so do collision check
				if (blocks[id][py * 4 + px] != L'.' && Map[map_pos] != '0' )
                {
                    //cout<<"NOT OK! ";
                    return false;
                }
			}
        }
    }
    return true;
}
void show_map(char* Map)
{
    for(int i=0;i<Height;i++){
        for(int j=0;j<Width;j++){
            cout<<Map[i*Width+j];
        }
        cout<<endl;
    }
    Sleep(300);
    cout<<"=========Next==========="<<endl;
    return;
}
int decide_blocks(string block_name)
{
    if(block_name=="T1")return 0;
    else if(block_name=="T2")return 1;
    else if(block_name=="T3")return 2;
    else if(block_name=="T4")return 3;
    else if(block_name=="L1")return 4;
    else if(block_name=="L2")return 5;
    else if(block_name=="L3")return 6;
    else if(block_name=="L4")return 7;
    else if(block_name=="J1")return 8;
    else if(block_name=="J2")return 9;
    else if(block_name=="J3")return 10;
    else if(block_name=="J4")return 11;
    else if(block_name=="Z1")return 12;
    else if(block_name=="Z2")return 13;
    else if(block_name=="Z3")return 14;
    else if(block_name=="Z4")return 15;
    else if(block_name=="I1")return 16;
    else if(block_name=="I2")return 17;
    else if(block_name=="O")return 18;
    else return -1;
}
void initial_blocks()
{
    blocks[0].append(L"....");
    blocks[0].append(L"....");
    blocks[0].append(L"XXX.");
    blocks[0].append(L".X..");///T1

    blocks[1].append(L"....");
    blocks[1].append(L".X..");
    blocks[1].append(L"XX..");
    blocks[1].append(L".X..");///T2

    blocks[2].append(L"....");
    blocks[2].append(L"....");
    blocks[2].append(L".X..");
    blocks[2].append(L"XXX.");///T3

    blocks[3].append(L"....");
    blocks[3].append(L"X...");
    blocks[3].append(L"XX..");
    blocks[3].append(L"X...");///T4

    blocks[4].append(L"....");
    blocks[4].append(L"X...");
    blocks[4].append(L"X...");
    blocks[4].append(L"XX..");///L1

    blocks[5].append(L"....");
    blocks[5].append(L"....");
    blocks[5].append(L"X...");
    blocks[5].append(L"XXX.");///L2

    blocks[6].append(L"....");
    blocks[6].append(L"XX..");
    blocks[6].append(L".X..");
    blocks[6].append(L".X..");;///L3

    blocks[7].append(L"....");
    blocks[7].append(L"....");
    blocks[7].append(L"..X.");
    blocks[7].append(L"XXX.");///L4

    blocks[8].append(L"....");
    blocks[8].append(L".X..");
    blocks[8].append(L".X..");
    blocks[8].append(L"XX..");///J1

    blocks[9].append(L"....");
    blocks[9].append(L"....");
    blocks[9].append(L"X...");
    blocks[9].append(L"XXX.");///J2

    blocks[10].append(L"....");
    blocks[10].append(L"XX..");
    blocks[10].append(L"X...");
    blocks[10].append(L"X...");///J3

    blocks[11].append(L"....");
    blocks[11].append(L"....");
    blocks[11].append(L"XXX.");
    blocks[11].append(L"..X.");///J4

    blocks[12].append(L"....");
    blocks[12].append(L"....");
    blocks[12].append(L".XX.");
    blocks[12].append(L"XX..");///S1

    blocks[13].append(L"....");
    blocks[13].append(L"X...");
    blocks[13].append(L"XX..");
    blocks[13].append(L".X..");///S2

    blocks[14].append(L"....");
    blocks[14].append(L"....");
    blocks[14].append(L"XX..");
    blocks[14].append(L".XX.");///Z1

    blocks[15].append(L"....");
    blocks[15].append(L".X..");
    blocks[15].append(L"XX..");
    blocks[15].append(L"X...");///Z2

    blocks[16].append(L"X...");
    blocks[16].append(L"X...");
    blocks[16].append(L"X...");
    blocks[16].append(L"X...");///Z2

    blocks[17].append(L"....");
    blocks[17].append(L"....");
    blocks[17].append(L"....");
    blocks[17].append(L"XXXX");///I2

    blocks[18].append(L"XX..");
    blocks[18].append(L"XX..");
    blocks[18].append(L"....");
    blocks[18].append(L"....");///O

    return;
}