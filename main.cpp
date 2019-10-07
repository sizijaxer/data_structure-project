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
wstring blocks[19];
void game_process();
void show_map(char* Map);
int decide_blocks(string block_name);
bool isfit(int nblock,int posX,int posY);
void det_line(char* sub_Map,int current_y,int current_x);
int get_boom();
int main()
{
    blocks[16].append(L"X...");///[id]
    blocks[16].append(L"X...");
    blocks[16].append(L"X...");
    blocks[16].append(L"X...");

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
            det_line(sub_Map,current_y,current_x);
            if(isfit(id,current_x,current_y+1))
            {
                //cout<<"GOGO ";
                current_y+=1;
                /////過程若出現一條線就要銷
                //char sub_Map[Width*Height];
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
                Sleep(300);
                ////判斷是否有要銷格，有消一行，則往下一個
                //det_line(sub_Map,current_y-1,current_x);
                /*int lines = 0;
                bool have_line = false; 
                int line_row;
                int map_pos;
                for(int py=0;py<4;py++)
                {   
                    have_line = true; 
                    for (int px = 1; px < Width - 1; px++)///掃整列
					{
                        map_pos = (current_y-1 + py) * Width + (current_x + px);
                        if(sub_Map[map_pos]=='0')have_line = false;
                    }
                    if(have_line)
                    {
                        line_row = (current_y-1 + py) * Width + (current_x + 1)+1;
                        break;
                    }
                }
                if(have_line)///消除
                {
                    for(int px = 1;px<Width-1;px++) sub_Map[px+line_row] = '=';
                    Sleep(300);
                    show_map(sub_Map);
                    cout<<"=========Next(boom)==========="<<endl;
                    for(int px = 1;px<Width-1;px++) sub_Map[px+line_row] = '0';
                    for(int i=0;i<Width*Height;i++)Map[i] = sub_Map[i];
                }*/
                //////////////////////////////////////
                Sleep(1000);
                show_map(sub_Map);
                cout<<"=========Next==========="<<endl;
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
void det_line(char* sub_Map,int current_y,int current_x)
{
    ////判斷是否有要銷格，有消一行，則往下一個
    int lines = 0;
    bool have_line = false; 
    int line_row;
    int map_pos;
    for(int py=0;py<4;py++)
    {   
        have_line = true; 
        for (int px = 1; px < Width - 1; px++)///掃整列
	    {
            map_pos = (current_y + py) * Width + (current_x + px);
            if(sub_Map[map_pos]=='0')have_line = false;
        }
        if(have_line)
        {
            line_row = (current_y + py) * Width + (current_x + 1)+1;
            break;
        }
    }
    if(have_line)///消除
    {
        for(int px = 1;px<Width-1;px++) sub_Map[px+line_row] = '=';
        Sleep(300);
        show_map(sub_Map);
        cout<<"=========Next(boom)==========="<<endl;
        for(int px = 1;px<Width-1;px++) sub_Map[px+line_row] = '0';
        for(int i=0;i<Width*Height;i++)Map[i] = sub_Map[i];
        return;
    }       //////////////////////////////////////
}
void show_map(char* Map)
{
    for(int i=0;i<Height;i++){
        for(int j=0;j<Width;j++){
            cout<<Map[i*Width+j];
        }
        cout<<endl;
    }
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