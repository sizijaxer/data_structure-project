#include <bits/stdc++.h>
#include <windows.h>///for debug tools Sleep
using namespace std;
/////////////map/////////////
int Width;
int Height;
char *Map;
string blocks[18];
void game_process();
void show_map(char* Map);
void show_true_map(char* Map);
int decide_blocks(string block_name);
bool isfit(int nblock,int posX,int posY);
void initial_blocks();
fstream input;
fstream output;
int main()
{   
    input.open("Tetris.data",ios::in);
    output.open("Tetris.final",ios::out);
    input >> Height >> Width;
    Width += 2;
    Height += 5;
    //Height = 8+1+4;
    Map = new char[Height*Width];
    for(int i=0;i<Height;i++){
        for(int j=0;j<Width;j++){
            Map[i*Width+j] = (j == 0 || j == Width - 1 || i == Height - 1) ? '#' : '0';
            
        }
    }
    //show_map(Map);
    game_process();
    show_true_map(Map);
    return 0;
}
void game_process()
{
    bool game_over = false;
    while(!game_over){
        initial_blocks();
        string block_name;
        int current_x;
        input>>block_name;
        int id = decide_blocks(block_name);
        if(id==-1)
        {
            //cout<<"no such block"<<endl;
            return;
        }
        //cout<<block_name<<" id:"<<id<<endl;
        if(block_name=="END")break;
        input>>current_x;
        int current_y = 0;
        ///game_logic
        /// only_go_down
        ///test if block can go down
        while(1){
            char sub_Map[Width*Height];
            for(int i=0;i<Width*Height;i++)sub_Map[i] = Map[i];
            //cout <<"id:"<<id<<endl;
            if(isfit(id,current_x,current_y+1))
            {
                //cout<<"GOGO ";
                current_y+=1;
                for(int i=0;i<Width*Height;i++)sub_Map[i] = Map[i];
                for(int px=0;px<4;px++)
                    for(int py=0;py<4;py++)
                    {
                        if(blocks[id][py * 4 + px] != '.')
                        {   //cout<<"put!!";
                            sub_Map[(current_y + py) * Width + (current_x + px)] = '1';
                        }
                    }
                //show_map(sub_Map);
            }
            else
            {   
                for(int px=0;px<4;px++)
                    for(int py=0;py<4;py++)
                    {
                        if(blocks[id][py * 4 + px] != '.')
                        {   //cout<<"put!!";
                            Map[(current_y + py) * Width + (current_x + px)] = '1';
                        }
                    }
                ////檢查line
                int index;
                int number_of_line=0;
                for(int py=3;py>=0;py--)
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
                            if((current_y+py)<4)
                            {
                                show_true_map(Map);
                                exit(1);
                            }
                        }
                        //show_map(Map);
                        for(int px=1;px<Width-1;px++)
                        {
                            ////make it to "0000"
                            Map[(current_y+py)*Width+px] = '0';
                        }
                        number_of_line++;
                        //cout<<"lines="<<number_of_line<<endl;
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
                        py=4;
                    }
                }  
                //show_map(Map);
                break;
            }
        }
        //show_map(Map);
        for(int i=0;i<4*Width;i++)if(Map[i]=='1')game_over=true;
    }
    //cout<<"game_over";
}
bool isfit(int id,int current_x,int current_y)///nposx=0;///nposy=1
{
    for(int px=0;px<4;px++)
    {
        for(int py=0;py<4;py++)
        {   //cout<<"det.. ";
            int map_pos = (current_y+py)*Width+(current_x+px);
            if(current_y+py >= 0 && current_y+py < Height)
			{
				if (blocks[id][py*4+px] == 'X' && Map[map_pos] != '0' )
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
void show_true_map(char* Map)
{
    for(int i=4;i<Height-1;i++){
        for(int j=1;j<Width-1;j++){
            output<<Map[i*Width+j];
        }
        output<<endl;
    }
    //cout<<"=========Next==========="<<endl;
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
    else if(block_name=="S1")return 12;
    else if(block_name=="S2")return 13;
    else if(block_name=="Z1")return 14;
    else if(block_name=="Z2")return 15;
    else if(block_name=="I1")return 16;
    else if(block_name=="I2")return 17;
    else if(block_name=="O")return 18;
    else return -1;
}
void initial_blocks()
{
    blocks[0].append("....");
    blocks[0].append("....");
    blocks[0].append("XXX.");
    blocks[0].append(".X..");///T1

    blocks[1].append("....");
    blocks[1].append(".X..");
    blocks[1].append("XX..");
    blocks[1].append(".X..");///T2

    blocks[2].append("....");
    blocks[2].append("....");
    blocks[2].append(".X..");
    blocks[2].append("XXX.");///T3

    blocks[3].append("....");
    blocks[3].append("X...");
    blocks[3].append("XX..");
    blocks[3].append("X...");///T4

    blocks[4].append("....");
    blocks[4].append("X...");
    blocks[4].append("X...");
    blocks[4].append("XX..");///L1

    blocks[5].append("....");
    blocks[5].append("....");
    blocks[5].append("XXX.");
    blocks[5].append("X...");///L2

    blocks[6].append("....");
    blocks[6].append("XX..");
    blocks[6].append(".X..");
    blocks[6].append(".X..");;///L3

    blocks[7].append("....");
    blocks[7].append("....");
    blocks[7].append("..X.");
    blocks[7].append("XXX.");///L4

    blocks[8].append("....");
    blocks[8].append(".X..");
    blocks[8].append(".X..");
    blocks[8].append("XX..");///J1

    blocks[9].append("....");
    blocks[9].append("....");
    blocks[9].append("X...");
    blocks[9].append("XXX.");///J2

    blocks[10].append("....");
    blocks[10].append("XX..");
    blocks[10].append("X...");
    blocks[10].append("X...");///J3

    blocks[11].append("....");
    blocks[11].append("....");
    blocks[11].append("XXX.");
    blocks[11].append("..X.");///J4

    blocks[12].append("....");
    blocks[12].append("....");
    blocks[12].append(".XX.");
    blocks[12].append("XX..");///S1

    blocks[13].append("....");
    blocks[13].append("X...");
    blocks[13].append("XX..");
    blocks[13].append(".X..");///S2

    blocks[14].append("....");
    blocks[14].append("....");
    blocks[14].append("XX..");
    blocks[14].append(".XX.");///Z1

    blocks[15].append("....");
    blocks[15].append(".X..");
    blocks[15].append("XX..");
    blocks[15].append("X...");///Z2

    blocks[16].append("X...");
    blocks[16].append("X...");
    blocks[16].append("X...");
    blocks[16].append("X...");///I1

    blocks[17].append("....");
    blocks[17].append("....");
    blocks[17].append("....");
    blocks[17].append("XXXX");///I2

    blocks[18].append("....");
    blocks[18].append("....");
    blocks[18].append("XX..");
    blocks[18].append("XX..");///O
    return;
}