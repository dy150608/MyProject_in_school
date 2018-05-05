#ifndef GREEDYSNAKE_H_INCLUDED
#define GREEDYSNAKE_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

const int maxsize = 20;

typedef struct node
{
    char status;
    int  order;
}S;// snake

class Data
{
private:
    int Game;
    int  head_x,head_y;
    int  move_x,move_y;
    int food_flag;// it's to mark have or not eaten the food
    friend class Snake;
    friend class Food;
};
class Map
{
    friend class Snake;
public:
    void _map_1();
    void _map_2();
    void _map_3();
};
class Food
{
private:
    int food_x,food_y;
    friend class Snake;
public:
    bool createfood(void);
    bool food(void);
};
class Snake
{
private:
    char move_instruct;
    int  snake_len;
    Data _data;
    Food _food;
    Map  _map;
public:
    void printboard(void);
    void intialize(void);
    void head_space(int,int);
    void head_food(int,int);
    void head_body(int,int);
    void head_edge(void);
    void head_move(void);
    void body_move(void);
    void snakemove(void);

    void printscore(void);
    void gamecontinue(void);
};

#endif // GREEDYSNAKE_H_INCLUDED
