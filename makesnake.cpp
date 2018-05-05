/* this file is definite with all class */
#include "greedysnake.h"

using std::cout;
using std::cin;

S board[maxsize][maxsize];

bool Food::createfood()
{
    food_x = rand() % maxsize;
    food_y = rand() % maxsize;
    if(board[food_x][food_y].status == ' ')
    {
        board[food_x][food_y].status = '@';
        return true;
    }
    else
        return false;
}
bool Food::food()
{
    bool su = false;
    while(su == false)
    {
        su = createfood();
    }
    return su;
}
void Map::_map_1()
{
    for(int i = 0;i < maxsize;i ++)
    {
        board[i][0].status = '#';
        board[i][maxsize-1].status = '#';
        board[0][i].status = '#';
        board[maxsize-1][i].status = '#';
    }
}
void Map::_map_2()
{
    for(int i = 0;i < maxsize;i ++)
    {
        board[i][0].status = '#';
        board[i][maxsize-1].status = '#';
        board[0][i].status = '#';
        board[maxsize-1][i].status = '#';
    }
    for(int i = 3;i < 8;i ++)
    {
        board[i][5].status    = '#';
        board[i+9][5].status  = '#';
        board[i][14].status   = '#';
        board[i+9][14].status = '#';

        board[5][i].status    = '#';
        board[5][i+9].status  = '#';
        board[14][i].status   = '#';
        board[14][i+9].status = '#';
    }
}
void Map::_map_3()
{
    for(int i = 0;i < maxsize;i ++)
    {
        board[i][0].status = '#';
        board[i][maxsize-1].status = '#';
        board[0][i].status = '#';
        board[maxsize-1][i].status = '#';
    }
    for(int i = 3;i < 8;i ++)
    {
        board[i][3].status = '#';
        board[i][15].status = '#';
        board[i+8][3].status = '#';
        board[i+8][15].status = '#';

        board[3][i].status = '#';
        board[15][i].status = '#';
        board[3][i+8].status = '#';
        board[15][i+8].status = '#';
    }
}
void Snake::printboard()
{
    system("cls");
    for(int i = 0;i < maxsize;i ++,cout<<"\n")
        for(int j =0;j < maxsize;j ++)
            cout<<board[i][j].status;
}
void Snake::intialize()
{
    system("cls");
    snake_len = 5;
    _data.Game = 1;
    move_instruct = 'a';

    for(int i = 0;i < maxsize;i ++)
        for(int j = 0;j < maxsize;j ++)
        {
            board[i][j].status = ' ';
            board[i][j].order  = 0;
        }

    // initial map
    int _map_o;
    cout<<"please input a integer for map option:\n";
    cout<<"1:the first\n2:the second\n3:the third\n";
    cin>>_map_o;
    while(!( (_map_o == 1) || (_map_o == 2) || (_map_o == 3) ))
    {
        cout<<"illegal input, please input legal option...\n";
        cin>>_map_o;
    }
    switch(_map_o)
    {
    case 1:
        _map._map_1();
        break;
    case 2:
        _map._map_2();
        break;
    case 3:
        _map._map_3();
        break;
    }

    // initialize snake
    _data.head_x = _data.head_y = 10;
    board[_data.head_x][_data.head_y].status= '&';
    for(int i = 1;i < 5;i ++)
    {
        board[_data.head_x][_data.head_y+i].status = '*';
        board[_data.head_x][_data.head_y+i].order  = i;
    }
    _food.food();
    printboard();
}
void Snake::head_space(int i,int j)
{
    switch(move_instruct)
    {
    case 'w':
        board[i-1][j].status = '&';
        board[i][j].status   = ' ';
        _data.head_x = i-1;
        break;
    case 's':
        board[i+1][j].status = '&';
        board[i][j].status   = ' ';
        _data.head_x = i+1;
        break;
    case 'a':
        board[i][j-1].status = '&';
        board[i][j].status   = ' ';
        _data.head_y = j-1;
        break;
    case 'd':
        board[i][j+1].status = '&';
        board[i][j].status   = ' ';
        _data.head_y = j+1;
        break;
    }
    _data.move_x = i;
    _data.move_y = j;
}
void Snake::head_food(int i,int j)
{
    switch(move_instruct)
    {
    case 'w':
        board[i-1][j].status = '&';
        board[i][j].status   = ' ';
        _data.head_x = i-1;
        break;
    case 's':
        board[i+1][j].status = '&';
        board[i][j].status   = ' ';
        _data.head_x = i+1;
        break;
    case 'a':
        board[i][j-1].status = '&';
        board[i][j].status   = ' ';
        _data.head_y = j-1;
        break;
    case 'd':
        board[i][j+1].status = '&';
        board[i][j].status   = ' ';
        _data.head_y = j+1;
        break;
    }
    snake_len += 1;
    _data.food_flag = 1;
    _food.food();
    _data.move_x = i;
    _data.move_y = j;
}
void Snake::head_body(int i,int j)
{
    _data.Game = 0;
    printboard();
    return;
}
void Snake::head_edge()
{
    _data.Game = 0;
    printboard();
    return;
}
void Snake::head_move()
{
    int i,j;
    i = _data.head_x;
    j = _data.head_y;
    switch(move_instruct)
    {
    case 'w':
        if(board[i-1][j].status == ' ')
            head_space(i,j);
        else if(board[i-1][j].status == '@')
            head_food(i,j);
        else if(board[i-1][j].status == '#')
            head_edge();
        else if(board[i-1][j].status == '*')
            head_body(i-1,j);
        break;
    case 's':
        if(board[i+1][j].status == ' ')
            head_space(i,j);
        else if(board[i+1][j].status == '@')
            head_food(i,j);
        else if(board[i+1][j].status == '#')
            head_edge();
        else if(board[i+1][j].status == '*')
            head_body(i+1,j);
        break;
    case 'a':
        if(board[i][j-1].status == ' ')
            head_space(i,j);
        else if(board[i][j-1].status == '@')
            head_food(i,j);
        else if(board[i][j-1].status == '#')
            head_edge();
        else if(board[i][j-1].status == '*')
            head_body(i,j-1);
        break;
    case 'd':
        if(board[i][j+1].status == ' ')
            head_space(i,j);
        else if(board[i][j+1].status == '@')
            head_food(i,j);
        else if(board[i][j+1].status == '#')
            head_edge();
        else if(board[i][j+1].status == '*')
            head_body(i,j+1);
        break;
    }
}
void Snake::body_move()
{
    if(_data.Game == 0)
        return;
    int x,y;
    int num = 0;
    for(int k = 1;k < snake_len;k ++)
    {
        if(k == snake_len-1 && _data.food_flag == 1)
        {
            board[_data.move_x][_data.move_y].status = '*';
            board[_data.move_x][_data.move_y].order  = k;
            _data.food_flag = 0;
            return;
        }
        if(num+1 == board[_data.move_x-1][_data.move_y].order)
        {
            num = board[_data.move_x-1][_data.move_y].order;
            x = _data.move_x-1;
            y = _data.move_y;
        }
        if(num+1 == board[_data.move_x+1][_data.move_y].order)
        {
            num = board[_data.move_x+1][_data.move_y].order;
            x = _data.move_x+1;
            y = _data.move_y;
        }
        if(num+1 == board[_data.move_x][_data.move_y-1].order)
        {
            num = board[_data.move_x][_data.move_y-1].order;
            x = _data.move_x;
            y = _data.move_y-1;
        }
        if(num+1 == board[_data.move_x][_data.move_y+1].order)
        {
            num = board[_data.move_x][_data.move_y+1].order;
            x = _data.move_x;
            y = _data.move_y+1;
        }
        board[_data.move_x][_data.move_y].status = board[x][y].status;// break_point
        board[_data.move_x][_data.move_y].order  = board[x][y].order;
        //last_number     = S[x][y].number;
        board[x][y].status = ' ';
        board[x][y].order  = 0;
        _data.move_x = x;
        _data.move_y = y;
    }
}
void Snake::snakemove()
{
    head_move();
    body_move();
    if(kbhit())// break_point
    {
        move_instruct = getch();
    }
    printboard();
}
void Snake::printscore()
{
    if(snake_len < (maxsize-1)*(maxsize-1))
        cout<<"your score is:"<<snake_len<<"\n";
    else
        cout<<"congratulation!"<<"\n";
}
void Snake::gamecontinue()
{
    while(_data.Game == 1)
    {
        Sleep(200);
        snakemove();
    }
}
