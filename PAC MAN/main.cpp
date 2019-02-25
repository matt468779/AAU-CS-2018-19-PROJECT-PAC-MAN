#include <GL/glut.h>
#include <math.h>
#include <windows.h>
#include <iostream>
#include <stdio.h>

enum in_game_state{PAUSE, PLAY, STOP_IN};
in_game_state in_state=PLAY;
enum out_game_state{START,  STOP, ENDGAME};
out_game_state out_state=START;
enum pacDirectionX {RIGHT=0, LEFT, STOPX};
enum pacDirectionY {UP=3, DOWN, STOPY};
enum pacDirection {right=6, left, up, down, stop};
pacDirectionY PdirectionY;
pacDirectionX PdirectionX= LEFT;
pacDirection Pdirection= left;
bool chaseGBR = true, chaseGP=true, chaseGB=true, chaseGO=true;
float posx_ui=0, posy_ui=0;
int chase_counter=1,score=0;
int opener=1,opener_counter=0;
int rBR=1, gBR=1, bBR=1, wBR=0,
    rO=1, gO=1, bO=1, wO=0,
    rB=1, gB=1, bB=1, wB=0,
    chaseX_GBR, chaseY_GBR, chaseX_GP, chaseY_GP,
    chaseX_GO, chaseY_GO,
    chaseX_GB,chaseY_GB;

int a,b,c,d,e,f,life_count=3;
int tempcounter=77;
int counter=1,counterP=0, counterO=0, counterB=0, tempcounterP=77, tempcounterO=77, tempcounterB=77, pellet_counter=0;
int rP=1, gP=1, bP=1, wP=0;
float k=0;
float angle;
float radius=1.2;
int posx=-2, posy=-13, posxGP=-2 ,posyGP=1, posxGB=-4 ,posyGB=1, posxGBR=-2 ,posyGBR=7, posxGO=0 ,posyGO=1;
int initial_posxGP=-12 ,initial_posyGP=17, initial_posxGB=16 ,initial_posyGB=-19, initial_posxGBR=8 ,initial_posyGBR=17, initial_posxGO=-20 ,initial_posyGO=-19;
void display();
void reshape(int, int);
void draw_wall();
void draw_sprite();
void draw_ghost();
void logic();
void game_text();
void timer(int);
void keyboard(unsigned char c,int x,int y);
void keyboard_callback(int key, int, int);
const int BOARD_X=41, BOARD_Y=53;
const int SPRITE_X=41, SPRITE_Y=53;
int hi_score=5000;

void renderBitmapString(float x, float y, void *font, char *string)
{
  char *c;
  glRasterPos2f(x,y);

  for (c=string; *c != '\0'; c++)
  	  {
    glutBitmapCharacter(font, *c);
  }
}
void Write(char *string){
    while(*string)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string++);
}

void print(char *string){
    while(*string)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string++);
}

int board_array[BOARD_Y][BOARD_X] =
        //1,2,3,4,5,6,7,,8,9,                                       // c
        {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},//1
         {0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0},//2
         {0,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,0,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,0},//3
         {0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0},//4
         {0,2,1,2,0,0,0,0,0,2,1,2,0,0,0,0,0,2,1,2,0,2,1,2,0,0,0,0,0,2,1,2,0,0,0,0,0,2,1,2,0},//5
         {0,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,0},//6
         {0,2,3,2,0,2,2,2,0,2,1,2,0,2,2,2,0,2,1,2,0,2,1,2,0,2,2,2,0,2,1,2,0,2,2,2,0,2,3,2,0},//7
         {0,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,0},//8
         {0,2,1,2,0,0,0,0,0,2,1,2,0,0,0,0,0,2,1,2,0,2,1,2,0,0,0,0,0,2,1,2,0,0,0,0,0,2,1,2,0},//9
         {0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0},//10
         {0,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,0},//11
         {0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0},//12
         {0,2,1,2,0,0,0,0,0,2,1,2,0,2,1,2,0,0,0,0,0,0,0,0,0,2,1,2,0,2,1,2,0,0,0,0,0,2,1,2,0},//13
         {0,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,2,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,0},//14
         {0,2,1,2,0,0,0,0,0,2,1,2,0,2,1,2,0,0,0,0,0,0,0,0,0,2,1,2,0,2,1,2,0,0,0,0,0,2,1,2,0},//15
         {0,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,0},//16
         {0,2,1,2,1,2,1,2,1,2,1,2,0,2,1,2,1,2,1,2,0,2,1,2,1,2,1,2,0,2,1,2,1,2,1,2,1,2,1,2,0},//17
         {0,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,0},//18
         {0,0,0,0,0,0,0,0,0,2,1,2,0,0,0,0,0,2,2,2,0,2,2,2,0,0,0,0,0,2,1,2,0,0,0,0,0,0,0,0,0},//19
         {2,2,2,2,2,2,2,2,0,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,0,2,2,2,2,2,2,2,2},//20
         {2,2,2,2,2,2,2,2,0,2,1,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,1,2,0,2,2,2,2,2,2,2,2},//21
         {2,2,2,2,2,2,2,2,0,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,0,2,2,2,2,2,2,2,2},//22
         {2,2,2,2,2,2,2,2,0,2,1,2,0,2,2,2,0,0,0,5,5,5,0,0,0,2,2,2,0,2,1,2,0,2,2,2,2,2,2,2,2},//23
         {2,2,2,2,2,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,2,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,2,2,2,2,2},//24
         {0,0,0,0,0,0,0,0,0,2,1,2,0,2,2,2,0,2,2,2,2,2,2,2,0,2,2,2,0,2,1,2,0,0,0,0,0,0,0,0,0},//25
         {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},//26
         {2,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,0,2,2,2,2,2,2,2,0,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2},//27
         {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},//28
         {0,0,0,0,0,0,0,0,0,2,1,2,0,2,2,2,0,0,0,0,0,0,0,0,0,2,2,2,0,2,1,2,0,0,0,0,0,0,0,0,0},//29
         {2,2,2,2,2,2,2,2,0,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,0,2,2,2,2,2,2,2,2},//30
         {2,2,2,2,2,2,2,2,0,2,1,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,1,2,0,2,2,2,2,2,2,2,2},//31
         {2,2,2,2,2,2,2,2,0,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,0,2,2,2,2,2,2,2,2},//32
         {2,2,2,2,2,2,2,2,0,2,1,2,0,2,2,2,0,0,0,0,0,0,0,0,0,2,2,2,0,2,1,2,0,2,2,2,2,2,2,2,2},//33
         {2,2,2,2,2,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,2,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,2,2,2,2,2},//34
         {0,0,0,0,0,0,0,0,0,2,1,2,0,2,2,2,0,0,0,0,0,0,0,0,0,2,2,2,0,2,1,2,0,0,0,0,0,0,0,0,0},//35
         {0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0},//36
         {0,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,0,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,0},//37
         {0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0},//38
         {0,2,1,2,0,0,0,0,0,2,1,2,0,0,0,0,0,2,1,2,0,2,1,2,0,0,0,0,0,2,1,2,0,0,0,0,0,2,1,2,0},//39
         {0,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,0},//40
         {0,2,3,2,1,2,1,2,0,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,0,2,1,2,1,2,3,2,0},//41
         {0,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,0},//42
         {0,0,0,0,0,2,1,2,0,2,1,2,0,2,1,2,0,0,0,0,0,0,0,0,0,2,1,2,0,2,1,2,0,2,1,2,0,0,0,0,0},//43
         {0,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,2,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,0},//44
         {0,0,0,0,0,2,1,2,0,2,1,2,0,2,1,2,0,0,0,0,0,0,0,0,0,2,1,2,0,2,1,2,0,2,1,2,0,0,0,0,0},//45
         {0,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,0},//46
         {0,2,1,2,1,2,1,2,1,2,1,2,0,2,1,2,1,2,1,2,0,2,1,2,1,2,1,2,0,2,1,2,1,2,1,2,1,2,1,2,0},//47
         {0,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,0},//48
         {0,2,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,2,0,2,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,2,0},//49
         {0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0},//50
         {0,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,0},//51
         {0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0},//52
         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};//53

const int MOVEMENT_Y=BOARD_Y, MOVEMENT_X=BOARD_X;
int movement_array[MOVEMENT_Y][MOVEMENT_X] =       //c
        {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},//1
         {0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0},//2
         {0,2,12,4,4,4,4,4,4,4,6,4,4,4,4,4,4,4,13,2,0,2,12,4,4,4,4,4,4,4,6,4,4,4,4,4,4,4,13,2,0},//3
         {0,2,5,2,2,2,2,2,2,2,5,2,2,2,2,2,2,2,5,2,0,2,5,2,2,2,2,2,2,2,5,2,2,2,2,2,2,2,5,2,0},//4
         {0,2,5,2,0,0,0,0,0,2,5,2,0,0,0,0,0,2,5,2,0,2,5,2,0,0,0,0,0,2,5,2,0,0,0,0,0,2,5,2,0},//5
         {0,2,5,2,0,2,2,2,0,2,5,2,0,2,2,2,0,2,5,2,0,2,5,2,0,2,2,2,0,2,5,2,0,2,2,2,0,2,5,2,0},//6
         {0,2,5,2,0,2,2,2,0,2,5,2,0,2,2,2,0,2,5,2,0,2,5,2,0,2,2,2,0,2,5,2,0,2,2,2,0,2,5,2,0},//7
         {0,2,5,2,0,2,2,2,0,2,5,2,0,2,2,2,0,2,5,2,0,2,5,2,0,2,2,2,0,2,5,2,0,2,2,2,0,2,5,2,0},//8
         {0,2,5,2,0,0,0,0,0,2,5,2,0,0,0,0,0,2,5,2,0,2,5,2,0,0,0,0,0,2,5,2,0,0,0,0,0,2,5,2,0},//9
         {0,2,5,2,2,2,2,2,2,2,5,2,2,2,2,2,2,2,5,2,2,2,5,2,2,2,2,2,2,2,5,2,2,2,2,2,2,2,5,2,0},//10
         {0,2,8,4,4,4,4,4,4,4,14,4,4,4,6,4,4,4,7,4,4,4,7,4,4,4,6,4,4,4,14,4,4,4,4,4,4,4,9,2,0},//11
         {0,2,5,2,2,2,2,2,2,2,5,2,2,2,5,2,2,2,2,2,2,2,2,2,2,2,5,2,2,2,5,2,2,2,2,2,2,2,5,2,0},//12
         {0,2,5,2,0,0,0,0,0,2,5,2,0,2,5,2,0,0,0,0,0,0,0,0,0,2,5,2,0,2,5,2,0,0,0,0,0,2,5,2,0},//13
         {0,2,5,2,0,2,2,2,0,2,5,2,0,2,5,2,0,2,2,2,2,2,2,2,0,2,5,2,0,2,5,2,0,2,2,2,0,2,5,2,0},//14
         {0,2,5,2,0,0,0,0,0,2,5,2,0,2,5,2,0,0,0,0,0,0,0,0,0,2,5,2,0,2,5,2,0,0,0,0,0,2,5,2,0},//15
         {0,2,5,2,2,2,2,2,2,2,5,2,0,2,5,2,2,2,2,2,0,2,2,2,2,2,5,2,0,2,5,2,2,2,2,2,2,2,5,2,0},//16
         {0,2,10,4,4,4,4,4,4,4,9,2,0,2,10,4,4,4,13,2,0,2,12,4,4,4,11,2,0,2,8,4,4,4,4,4,4,4,11,2,0},//17
         {0,2,2,2,2,2,2,2,2,2,5,2,0,2,5,2,2,2,5,2,0,2,5,2,2,2,5,2,0,2,5,2,2,2,2,2,2,2,2,2,0},//18
         {0,0,0,0,0,0,0,0,0,2,5,2,0,0,5,0,0,2,5,2,0,2,5,2,0,0,5,0,0,2,5,2,0,0,0,0,0,0,0,0,0},//19
         {2,2,2,2,2,2,2,2,0,2,5,2,0,2,5,2,2,2,5,2,2,2,5,2,2,2,5,2,0,2,5,2,0,2,2,2,2,2,2,2,2},//20
         {2,2,2,2,2,2,2,2,0,2,5,2,0,2,12,4,4,4,7,4,4,4,7,4,4,4,13,2,0,2,5,2,0,2,2,2,2,2,2,2,2},//21
         {2,2,2,2,2,2,2,2,0,2,5,2,0,2,5,2,2,2,2,2,2,2,2,2,2,2,5,2,0,2,5,2,0,2,2,2,2,2,2,2,2},//22
         {2,2,2,2,2,2,2,2,0,2,5,2,0,2,5,2,0,0,0,-1,-1,-1,0,0,0,2,5,2,0,2,5,2,0,2,2,2,2,2,2,2,2},//23
         {2,2,2,2,2,2,2,2,0,2,5,2,0,2,5,2,0,2,2,2,2,2,2,2,0,2,5,2,0,2,5,2,0,2,2,2,2,2,2,2,2},//24
         {0,0,0,0,0,0,0,0,0,2,5,2,0,2,5,2,0,2,2,2,2,2,2,2,0,2,5,2,0,2,5,2,0,0,0,0,0,0,0,0,0},//25
         {2,2,2,2,2,2,2,2,2,2,5,2,2,2,5,2,0,2,2,2,2,2,2,2,0,2,5,2,2,2,5,2,2,2,2,2,2,2,2,2,2},//26
         {15,4,4,4,4,4,4,4,4,4,14,4,4,4,9,2,0,2,2,2,2,2,2,2,0,2,8,4,4,4,14,4,4,4,4,4,4,4,4,4,16},//27
         {2,2,2,2,2,2,2,2,2,2,5,2,2,2,5,2,0,2,2,2,2,2,2,2,0,2,5,2,2,2,5,2,2,2,2,2,2,2,2,2,2},//28
         {0,0,0,0,0,0,0,0,0,2,5,2,0,2,5,2,0,0,0,0,0,0,0,0,0,2,5,2,0,2,5,2,0,0,0,0,0,0,0,0,0},//29
         {2,2,2,2,2,2,2,2,0,2,5,2,0,2,5,2,2,2,2,2,2,2,2,2,2,2,5,2,0,2,5,2,0,2,2,2,2,2,2,2,2},//30
         {2,2,2,2,2,2,2,2,0,2,5,2,0,2,8,4,4,4,4,4,4,4,4,4,4,4,9,2,0,2,5,2,0,2,2,2,2,2,2,2,2},//31
         {2,2,2,2,2,2,2,2,0,2,5,2,0,2,5,2,2,2,2,2,2,2,2,2,2,2,5,2,0,2,5,2,0,2,2,2,2,2,2,2,2},//32
         {2,2,2,2,2,2,2,2,0,2,5,2,0,2,5,2,0,0,0,0,0,0,0,0,0,2,5,2,0,2,5,2,0,2,2,2,2,2,2,2,2},//33
         {2,2,2,2,2,2,2,2,0,2,5,2,0,2,5,2,0,2,2,2,2,2,2,2,0,2,5,2,0,2,5,2,0,2,2,2,2,2,2,2,2},//34
         {0,0,0,0,0,0,0,0,0,2,5,2,0,2,5,2,0,0,0,0,0,0,0,0,0,2,5,2,0,2,5,2,0,0,0,0,0,0,0,0,0},//35
         {0,2,2,2,2,2,2,2,2,2,5,2,2,2,5,2,2,2,2,2,0,2,2,2,2,2,5,2,2,2,5,2,2,2,2,2,2,2,2,2,0},//36
      {0,2,12,4,4,4,4,4,4,4,14,4,4,4,7,4,4,4,13,2,0,2,12,4,4,4,7,4,4,4,14,4,4,4,4,4,4,4,13,2,0},//37
         {0,2,5,2,2,2,2,2,2,2,5,2,2,2,2,2,2,2,5,2,0,2,5,2,2,2,2,2,2,2,5,2,2,2,2,2,2,2,5,2,0},//38
         {0,2,5,2,0,0,0,0,0,2,5,2,0,0,0,0,0,2,5,2,0,2,5,2,0,0,0,0,0,2,5,2,0,0,0,0,0,2,5,2,0},//39
         {0,2,5,2,2,2,2,2,0,2,5,2,2,2,2,2,2,2,5,2,2,2,5,2,2,2,2,2,2,2,5,2,0,2,2,2,2,2,5,2,0},//40
       {0,2,10,4,4,4,13,2,0,2,8,4,4,4,6,4,4,4,7,4,4,4,7,4,4,4,6,4,4,4,9,2,0,2,12,4,4,4,11,2,0},//41 start
         {0,2,2,2,2,2,5,2,0,2,5,2,2,2,5,2,2,2,2,2,2,2,2,2,2,2,5,2,2,2,5,2,0,2,5,2,2,2,2,2,0},//42
         {0,0,0,0,0,2,5,2,0,2,5,2,0,2,5,2,0,0,0,0,0,0,0,0,0,2,5,2,0,2,5,2,0,2,5,2,0,0,0,0,0},//43
         {0,2,2,2,0,2,5,2,0,2,5,2,0,2,5,2,0,2,2,2,2,2,2,2,0,2,5,2,0,2,5,2,0,2,5,2,0,2,2,2,0},//44
         {0,0,0,0,0,2,5,2,0,2,5,2,0,2,5,2,0,0,0,0,0,0,0,0,0,2,5,2,0,2,5,2,0,2,5,2,0,0,0,0,0},//45
         {0,2,2,2,2,2,5,2,2,2,5,2,0,2,5,2,2,2,2,2,0,2,2,2,2,2,5,2,0,2,5,2,2,2,5,2,2,2,2,2,0},//46
     {0,2,12,4,4,4,7,4,4,4,11,4,4,4,10,4,4,4,13,2,0,2,12,4,4,4,11,2,0,2,10,4,4,4,7,4,4,4,13,2,0},//47
         {0,2,5,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,5,2,0,2,5,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,5,2,0},//48
         {0,2,5,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,5,2,0,2,5,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,5,2,0},//49
         {0,2,5,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5,2,2,2,5,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5,2,0},//50
        {0,2,10,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,4,4,4,7,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,11,2,0},//51
         {0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0},//52
         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};//53
int temp_board_array[MOVEMENT_Y][MOVEMENT_X];
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glClear(GL_COLOR_BUFFER_BIT);
    glutInitWindowSize(1360,720);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("PAC-MAN");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);
    glutSpecialFunc(keyboard_callback);
    glutReshapeFunc(reshape);
    glutMainLoop();

}
void keyboard(unsigned char game, int ,int){
    if(game==32){
        in_state=PLAY;
        out_state=STOP;
    }
    else if(game==27)
        in_state=PAUSE;
    else if (out_state == ENDGAME && (game == 89 || game == 121))
        out_state= START;
    else if (out_state == ENDGAME && (game == 78 || game == 110))
        exit(0);

}
float r_text=0, b_text=0, g_text=0;
void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    char tmp_str[40];
        if (r_text<1)
            r_text=r_text+0.01;
        else r_text=0;
        if (g_text<1)
            g_text+=0.02;
        else g_text=0;
        if (b_text<1)
            b_text+=0.03;
        else b_text=0;
        posx_ui+=0.5;
        if(posx_ui==46)
            posx_ui=-46;
    if (out_state == START){
        score=0;
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_POLYGON);
        for (int i=0.1; i<360; i++){
            angle = 3.142/180 * i;
            glVertex2f(posx_ui + 10*cos(angle), posy_ui + 10*sin(angle));
        }
        glEnd();
        glColor3f(0.0,0.0,0.0);
        glBegin(GL_TRIANGLES);
        glVertex2f((posx_ui - 2 ),(posy_ui ));
        glVertex2f((posx_ui + 10), (posy_ui + 10));
        glVertex2f((posx_ui + 10) , (posy_ui - 10));
        glEnd();
        glColor3f(1, 1.0, 0.3);
        glRasterPos2f(-4, 20);
        sprintf(tmp_str, "PAC MAN");
        print(tmp_str);


        glColor3f(0.0+r_text, 0.0+g_text, 0.0+b_text);
        glRasterPos2f(-12, -20);
        sprintf(tmp_str, "PRESS SPACEBAR TO START!!!");
        print(tmp_str);

        for(int i=0; i<MOVEMENT_Y; i++){
            for(int j=0; j<MOVEMENT_X; j++){
                temp_board_array[i][j]=board_array[i][j];
            }
        }
    }
    else if(in_state == PLAY){
        game_text();
        draw_wall();
        draw_sprite();
        draw_ghost();
        logic();
    }
    else if(in_state==PAUSE){
        glColor3f(0.0+r_text, 0.0+g_text, 0.0+b_text);
        glRasterPos2f(-15, 0);
        sprintf(tmp_str, "             GAME PAUSED");
        print(tmp_str);
        glColor3f(0.0+r_text, 0.0+g_text, 0.0+b_text);
        glRasterPos2f(-15, -4);
        sprintf(tmp_str, "PRESS SPACEBAR TO CONTINUE");
        print(tmp_str);
    }
    else if (out_state == ENDGAME){
        glColor3f(0.0+r_text, 0.0+g_text, 0.0+b_text);
        glRasterPos2f(-10, 6);
        sprintf(tmp_str, "DO YOU WISH TO CONTINUE");
        print(tmp_str);
        glColor3f(0.0+r_text, 0.0+g_text, 0.0+b_text);
        glRasterPos2f(-10, 2);
        sprintf(tmp_str, "yes(y)            no(n)");
        print(tmp_str);
        glColor3f(0.0+r_text, 0.0+g_text, 0.0+b_text);
        glRasterPos2f(-10, 10);
        sprintf(tmp_str, "score : %d",score);
        print(tmp_str);

    }
    glutSwapBuffers();
    glFlush();
}
void game_text(){
    char tmp_str[40];
    glColor3f(1, 0.3, 0.3);
    glRasterPos2f(20, 20);
	sprintf(tmp_str, "HI-SCORE: ");
    print(tmp_str);

    glColor3f(1, 1, 1);
    glRasterPos2f(20, 18);
	sprintf(tmp_str, "%d", hi_score);
    print(tmp_str);

    glColor3f(1, 0.3, 0.3);
    glRasterPos2f(20, 14);
	sprintf(tmp_str, "SCORE: ");
    Write(tmp_str);

    glColor3f(1, 1, 1);
    glRasterPos2f(20, 12);
	sprintf(tmp_str, "%d", score);
    Write(tmp_str);

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(-40, 20);
	sprintf(tmp_str, "press esc to pause");
    print(tmp_str);

    if (score > hi_score)
        hi_score=score;

}
void draw_wall(){
        //DRAW THE WALLS
    glColor3f(0.0,0.0,1.0);
    glPointSize(19.5);
    glBegin(GL_POINTS);
    for(int i=0; i<BOARD_Y; i++){
        for(int j=0; j<BOARD_X; j++){
            if(board_array[i][j]==0){
                glVertex2f(-22+j,27-i);
            }
        }
    }
    glEnd();
    //DRAW THE PELLETS
    glColor3f(1.0,1.0,0.0);
    glPointSize(5);
    glBegin(GL_POINTS);
    int k=0;
        for(int i=0; i<BOARD_Y; i++){
            for(int j=0; j<BOARD_X; j++){
                if(board_array[i][j]==1){
                    glVertex2f(-22+j,27-i);
                    if (posx==-22+j && posy==27-i){
                        board_array[i][j]=2;
                        score+=10;
                        pellet_counter++;
                    }
                }
            }
        }
    glEnd();
    //DRAW THE POWER-UPS
    glPointSize(15);
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_POINTS);
    for(int i=0; i<BOARD_Y; i++){
        for(int j=0; j<BOARD_X; j++){
            if (board_array[i][j]==3){
                glVertex2f(-22+j,27-i);
                if (posx==-22+j && posy==27-i){
                    board_array[i][j]=2;
                    chaseGP=false;
                    chaseGB=false;
                    chaseGO=false;
                    chaseGBR=false;
                    chase_counter=0;
                    score+=200;
                    pellet_counter++;
                }
            }
        }
    }
    glEnd();


}
void reshape(int w, int h){
    glViewport(0,0,(GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-45.5, 45.5, -27, 27);
    glMatrixMode(GL_MODELVIEW);
}
void draw_sprite(){

     //MOVEMENT LOGIC FOR THE SPRITE
    for(int i=0; i<MOVEMENT_Y; i++){
        for(int j=0; j<MOVEMENT_X; j++){
            if(movement_array[i][j]==4){
                if (posx==-22+j && posy==27-i){
                    if(PdirectionX==RIGHT)
                        posx=posx+1;
                    else if(PdirectionX==LEFT)
                        posx=posx-1;
                    PdirectionY=STOPY;
                    break;
                }
            }
            else if(movement_array[i][j]==6){
                if (posx==-22+j && posy==27-i){
                    if(PdirectionY==DOWN){
                        posy=posy-1;
                        PdirectionX=STOPX;
                    }
                    else if(PdirectionX==LEFT)
                        posx=posx-1;
                    else if(PdirectionX==RIGHT)
                        posx=posx+1;
                    break;
                }
            }
            else if(movement_array[i][j]==7){
                if (posx==-22+j && posy==27-i){
                    if(PdirectionY==UP){
                        posy=posy+1;
                        PdirectionX=STOPX;
                    }
                    else if(PdirectionX==RIGHT)
                        posx=posx+1;
                    else if(PdirectionX==LEFT)
                        posx=posx-1;
                    break;
                }
            }
            else if(movement_array[i][j]==8){
                if (posx==-22+j && posy==27-i){
                    if(PdirectionX==RIGHT){
                        posx=posx+1;
                        PdirectionY=STOPY;
                    }
                    else if(PdirectionY==DOWN)
                        posy=posy-1;
                    else if(PdirectionY==UP)
                        posy=posy+1;
                    break;
                }
            }
            else if(movement_array[i][j]==9){
                if (posx==-22+j && posy==27-i){
                    if(PdirectionX==LEFT){
                        posx=posx-1;
                        PdirectionY=STOPY;
                    }
                    else if(PdirectionY==UP)
                        posy=posy+1;
                    else if(PdirectionY==DOWN)
                        posy=posy-1;
                    break;
                }
            }
            else if(movement_array[i][j]==10){
                if (posx==-22+j && posy==27-i){
                    if(PdirectionY==UP){
                        posy=posy+1;
                        PdirectionX=STOPX;
                    }
                    else if(PdirectionX==RIGHT){
                        posx=posx+1;
                        PdirectionY=STOPY;
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==11){
                if (posx==-22+j && posy==27-i){
                    if(PdirectionX==LEFT){
                        posx=posx-1;
                        PdirectionY=STOPY;
                    }
                    else if(PdirectionY==UP){
                        posy=posy+1;
                        PdirectionX=STOPX;
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==12){
              if (posx==-22+j && posy==27-i){
                    if(PdirectionY==DOWN){
                        posy=posy-1;
                        PdirectionX=STOPX;
                    }
                    else if(PdirectionX==RIGHT){
                        posx=posx+1;
                        PdirectionY=STOPY;
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==13){
                if (posx==-22+j && posy==27-i){
                    if(PdirectionX==LEFT){
                        posx=posx-1;
                        PdirectionY=STOPY;
                    }
                    else if(PdirectionY==DOWN){
                        posy=posy-1;
                        PdirectionX=STOPX;
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==14){
                if (posx==-22+j && posy==27-i){
                    if(Pdirection==down){
                        posy=posy-1;
                        PdirectionY=DOWN;
                    }
                    else if(Pdirection==left){
                        posx=posx-1;
                        PdirectionX=LEFT;
                    }
                    else if(Pdirection==up){
                        posy=posy+1;
                        PdirectionY=UP;
                    }
                    else if(Pdirection==right){
                        posx=posx+1;
                        PdirectionX=RIGHT;
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==15){
                if (posx==-22+j && posy==27-i){
                    posx=17 ;
                    posy=1;
                    break;
                }
            }
            else if(movement_array[i][j]==16){
                if (posx==-22+j && posy==27-i){
                    posx=-21 ;
                    posy=1 ;
                    break;
                }
            }
            else if(movement_array[i][j]==5){
                if (posx==-22+j && posy==27-i){
                    if(PdirectionY==UP){
                        posy=posy+1.0;
                        PdirectionX=STOPX;
                    }
                    if(PdirectionY==DOWN){
                        posy--;
                        PdirectionX=STOPX;
                        goto label;
                    }
                    break;
                }
            }
        }
    }
    label:;

    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    for (int i=0.1; i<360; i++){
        angle = 3.142/180 * i;
        glVertex2f(posx + radius*cos(angle), posy + radius*sin(angle));
    }
    glEnd();

    glColor3f(0.0,0.0,0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(opener*(posx + 0.25 * a),opener* (posy + 0.25 *b));
    glVertex2f(opener*(posx - 1.2 * c), opener*(posy - 1.2 *d));
    glVertex2f(opener*(posx - 1.2 *e) , opener*(posy + 1.2 * f));
    glEnd();

    if (PdirectionX==LEFT){
        a=1; b=0; c=1; d=1; e=1; f=1;
    }
    else if (PdirectionX==RIGHT){
        a=-1; b=0; c=-1; d=1; e=-1; f=1;
    }
    if (PdirectionY==UP){
        a=0; b=-1; c=-1; d=-1; e=1; f=1;
    }
    else if (PdirectionY==DOWN){
        a=0; b=1; c=1; d=1; e=-1; f=-1;
    }

    opener_counter++;


    if(opener_counter<2){
        opener=0;
    }
    if(opener_counter>2 && opener_counter<5){
        opener=1;
    }
    if (opener_counter>4)
        opener_counter=0;

    std::cout<<opener_counter<<std::endl;

    for (int j=0; j<life_count; j++){
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_POLYGON);
        for (int i=0.1; i<360; i++){
            angle = 3.142/180 * i;
            glVertex2f(23 + 3*j + radius*cos(angle), -20 + radius*sin(angle));
        }
        glEnd();

        glColor3f(0.0,0.0,0.0);
        glBegin(GL_TRIANGLES);
        glVertex2f((23 + 0.25 + 3*j), (-20 + 0.25 ));
        glVertex2f((23 - 1.2 + j*3), (-20 - 1.2 ));
        glVertex2f((23 - 1.2 + j*3), (-20 + 1.2 ));
        glEnd();
    }

}
void draw_ghost(){
    //PINK
    glColor3f(1.0*rP, 0.8*gP, 0.8*bP+wP);
    glBegin(GL_POLYGON);
    for (int i=10; i<170; i++){
        angle = 3.142/180 * i;
        glVertex2f(posxGP + radius*cos(angle), posyGP + radius*sin(angle));
    }
    glVertex2f(posxGP-1.2,posyGP-1.2);
    glVertex2f(posxGP+1.2,posyGP-1.2);

    glEnd();
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(posxGP-0.5,posyGP-0.5);
    glVertex2f(posxGP-1.2,posyGP-1.2);
    glVertex2f(posxGP,posyGP-1.2);

    glVertex2f(posxGP+0.6,posyGP-0.5);
    glVertex2f(posxGP,posyGP-1.2);
    glVertex2f(posxGP+1.2,posyGP-1.2);
    glEnd();
    glPointSize(9);
    glColor3f(1.0,1.0,1.0);

    glBegin(GL_POINTS);
    glVertex2f(posxGP-0.6,posyGP+0.5);
    glVertex2f(posxGP+0.6,posyGP+0.5);
    glEnd();
    glPointSize(3.5);
    glColor3f(0.0+ wP, 0.0+wP,0.0+wP);

    glBegin(GL_POINTS);
    glVertex2f(posxGP-0.6,posyGP+0.5);
    glVertex2f(posxGP+0.6,posyGP+0.5);
    glEnd();

    //BLUE
    glColor3f(0.7*rB, 0.9*gB, 1.0*bB+wB);
    glBegin(GL_POLYGON);
    for (int i=10; i<170; i++){
        angle = 3.142/180 * i;
        glVertex2f(posxGB + radius*cos(angle), posyGB + radius*sin(angle));
    }
    glVertex2f(posxGB-1.2,posyGB-1.2);
    glVertex2f(posxGB+1.2,posyGB-1.2);

    glEnd();
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(posxGB-0.5,posyGB-0.5);
    glVertex2f(posxGB-1.2,posyGB-1.2);
    glVertex2f(posxGB,posyGB-1.2);

    glVertex2f(posxGB+0.6,posyGB-0.5);
    glVertex2f(posxGB,posyGB-1.2);
    glVertex2f(posxGB+1.2,posyGB-1.2);
    glEnd();
    glPointSize(9);
    glColor3f(1.0,1.0,1.0);

    glBegin(GL_POINTS);
    glVertex2f(posxGB-0.6,posyGB+0.5);
    glVertex2f(posxGB+0.6,posyGB+0.5);
    glEnd();
    glPointSize(3.5);
    glColor3f(0.0+wP,0.0+wP,0.0+wP);

    glBegin(GL_POINTS);
    glVertex2f(posxGB-0.6,posyGB+0.5);
    glVertex2f(posxGB+0.6,posyGB+0.5);
    glEnd();
    //BROWN
    glColor3f(0.8*rBR, 0.1*gBR, 0.1*bBR+wBR);
    glBegin(GL_POLYGON);
    for (int i=10; i<170; i++){
        angle = 3.142/180 * i;
        glVertex2f(posxGBR + radius*cos(angle), posyGBR + radius*sin(angle));
    }
    glVertex2f(posxGBR-1.2,posyGBR-1.2);
    glVertex2f(posxGBR+1.2,posyGBR-1.2);

    glEnd();
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(posxGBR-0.5,posyGBR-0.5);
    glVertex2f(posxGBR-1.2,posyGBR-1.2);
    glVertex2f(posxGBR,posyGBR-1.2);

    glVertex2f(posxGBR+0.6,posyGBR-0.5);
    glVertex2f(posxGBR,posyGBR-1.2);
    glVertex2f(posxGBR+1.2,posyGBR-1.2);
    glEnd();
    glPointSize(9);
    glColor3f(1.0,1.0,1.0);

    glBegin(GL_POINTS);
    glVertex2f(posxGBR-0.6,posyGBR+0.5);
    glVertex2f(posxGBR+0.6,posyGBR+0.5);
    glEnd();
    glPointSize(3.5);
    glColor3f(0.0+wBR,0.0+wBR,0.0+wBR);

    glBegin(GL_POINTS);
    glVertex2f(posxGBR-0.6,posyGBR+0.5);
    glVertex2f(posxGBR+0.6,posyGBR+0.5);
    glEnd();

    //ORANGE
    glColor3f(0.8*rO, 0.4*gO, 0.0*bO+wO);
    glBegin(GL_POLYGON);
    for (int i=10; i<170; i++){
        angle = 3.142/180 * i;
        glVertex2f(posxGO + radius*cos(angle), posyGO + radius*sin(angle));
    }
    glVertex2f(posxGO-1.2,posyGO-1.2);
    glVertex2f(posxGO+1.2,posyGO-1.2);

    glEnd();
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(posxGO-0.5,posyGO-0.5);
    glVertex2f(posxGO-1.2,posyGO-1.2);
    glVertex2f(posxGO,posyGO-1.2);

    glVertex2f(posxGO+0.6,posyGO-0.5);
    glVertex2f(posxGO,posyGO-1.2);
    glVertex2f(posxGO+1.2,posyGO-1.2);
    glEnd();
    glPointSize(9);
    glColor3f(1.0,1.0,1.0);

    glBegin(GL_POINTS);
    glVertex2f(posxGO-0.6,posyGO+0.5);
    glVertex2f(posxGO+0.6,posyGO+0.5);
    glEnd();
    glPointSize(3.5);
    glColor3f(0.0+wO,0.0+wO,0.0+wO);

    glBegin(GL_POINTS);
    glVertex2f(posxGO-0.6,posyGO+0.5);
    glVertex2f(posxGO+0.6,posyGO+0.5);

    glEnd();



    for(int i=0; i<MOVEMENT_Y; i++){
        for(int j=0; j<MOVEMENT_X; j++){
            if(movement_array[i][j]==4){
                if(posxGBR==-22+j && posyGBR==27-i){
                    if(posxGBR<chaseX_GBR){
                        if (chaseGBR==true)
                            posxGBR++;
                        else
                            posxGBR--;
                    }
                    else if(posxGBR>chaseX_GBR){
                        if (chaseGBR==true)
                            posxGBR--;
                        else
                            posxGBR++;
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==5){
                if (posxGBR==-22+j && posyGBR==27-i){
                    if(posyGBR>chaseY_GBR){
                        if (chaseGBR==true)
                            posyGBR--;
                        else
                            posyGBR++;
                    }
                    else if(posyGBR<chaseY_GBR){
                        if (chaseGBR==true)
                            posyGBR++;
                        else
                            posyGBR--;
                    }
                    goto another;
                }
            }
            else if(movement_array[i][j]==6){
                if (posxGBR==-22+j && posyGBR==27-i){
                    if(posxGBR<chaseX_GBR){
                        if (chaseGBR==true)
                            posxGBR++;
                        else
                            posxGBR--;
                    }
                    else if(posxGBR>chaseX_GBR){
                        if (chaseGBR==true)
                            posxGBR--;
                        else
                            posxGBR++;
                    }
                    else if(posyGBR>chaseY_GBR){
                        if (chaseGBR==true)
                            posyGBR--;
                        break;
                    }
                }
            }
            else if(movement_array[i][j]==7){
                if (posxGBR==-22+j && posyGBR==27-i){
                    if(posxGBR<chaseX_GBR){
                        if (chaseGBR==true)
                            posxGBR++;
                        else
                            posxGBR--;
                    }
                    else if(posyGBR<chaseY_GBR){
                        if (chaseGBR==true)
                            posyGBR++;
                    }
                    else if(posxGBR>chaseX_GBR){
                        if (chaseGBR==true)
                            posxGBR--;
                        else
                            posxGBR++;
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==8){
                if (posxGBR==-22+j && posyGBR==27-i){
                    if(posyGBR>chaseY_GBR){
                        if (chaseGBR==true)
                            posyGBR--;
                        else
                            posyGBR++;
                    }
                    else if(posyGBR<chaseY_GBR){
                        if (chaseGBR==true)
                            posyGBR++;
                        else
                            posyGBR--;
                    }
                    else if(posxGBR<chaseX_GBR){
                        if (chaseGBR==true){
                            posxGBR++;
                        }
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==9){
                if (posxGBR==-22+j && posyGBR==27-i){
                    if(posxGBR>chaseX_GBR){
                        if (chaseGBR==true)
                            posxGBR--;
                    }
                    else if(posyGBR<chaseY_GBR){
                        if (chaseGBR==true)
                            posyGBR++;
                        else
                            posyGBR--;
                    }
                    else if(posyGBR>chaseY_GBR){
                        if (chaseGBR==true)
                            posyGBR--;
                        else
                            posyGBR++;
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==10){
                if (posxGBR==-22+j && posyGBR==27-i){
                    if(posxGBR<chaseX_GBR){
                        if (chaseGBR==true)
                            posxGBR++;
                    }
                    else if(posyGBR<chaseY_GBR){
                        if (chaseGBR==true)
                            posyGBR++;
                    }
                        if (chaseX_GBR<=posxGBR && chaseY_GBR<=posyGBR){
                            tempcounter=0;
                            chaseX_GBR=40;
                            chaseY_GBR=-25;
                        }
                        break;
                }
            }
            else if(movement_array[i][j]==11){
                if (posxGBR==-22+j && posyGBR==27-i){
                    if(posyGBR<chaseY_GBR){
                        if (chaseGBR==true)
                            posyGBR++;
                    }
                    else if(posxGBR>chaseX_GBR){
                        if (chaseGBR==true)
                            posxGBR--;
                    }
                    if (chaseX_GBR>=posxGBR && chaseY_GBR<=posyGBR){
                        tempcounter=0;
                        chaseX_GBR=-20;
                        chaseY_GBR=-23;
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==12){
                if (posxGBR==-22+j && posyGBR==27-i){
                    if(posyGBR>chaseY_GBR){
                        if (chaseGBR==true)
                            posyGBR--;
                    }
                    else if(posxGBR<chaseX_GBR){
                        if (chaseGBR==true)
                            posxGBR++;
                    }
                    if (chaseX_GBR<=posxGBR && chaseY_GBR>=posyGBR){
                        tempcounter=0;
                        chaseX_GBR=-20;
                        chaseY_GBR=-23;
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==13){
                if (posxGBR==-22+j && posyGBR==27-i){
                    if(posyGBR>chaseY_GBR){
                        if (chaseGBR==true)
                            posyGBR--;
                    }
                    else if(posxGBR>chaseX_GBR){
                        if (chaseGBR==true)
                            posxGBR--;
                    }
                    if (chaseX_GBR>=posxGBR && chaseY_GBR>=posyGBR){
                        tempcounter=0;
                        chaseX_GBR=40;
                        chaseY_GBR=-25;
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==14){
                if (posxGBR==-22+j && posyGBR==27-i){
                    if(posyGBR>chaseY_GBR){
                        if (chaseGBR==true)
                            posyGBR--;
                        else
                            posyGBR++;
                        break;
                    }
                    else if(posxGBR<chaseX_GBR){
                        if (chaseGBR==true)
                            posxGBR++;
                        else
                            posxGBR--;
                        break;
                    }
                    else if(posyGBR<chaseY_GBR){
                        if (chaseGBR==true)
                            posyGBR++;
                        else
                            posyGBR--;
                        break;
                    }
                    else if(posxGBR>chaseX_GBR){
                        if (chaseGBR==true)
                            posxGBR--;
                        else
                            posxGBR++;
                        break;
                    }
                }
            }
            else if(movement_array[i][j]==15){
                if (posxGBR==-22+j && posyGBR==27-i){
                    posxGBR=17 ;
                    posyGBR=1;
                    break;
                }
            }
            else if(movement_array[i][j]==16){
                if (posxGBR==-22+j && posyGBR==27-i){
                    posxGBR=-21 ;
                    posyGBR=1 ;
                    break;
                }
            }
        }
    }
    another:;

 for(int i=0; i<MOVEMENT_Y; i++){
        for(int j=0; j<MOVEMENT_X; j++){
            if(movement_array[i][j]==4){
                if(posxGP==-22+j && posyGP==27-i){
                    if(posxGP<chaseX_GP){
                        if (chaseGP==true)
                            posxGP++;
                        else
                            posxGP--;
                    }
                    else if(posxGP>chaseX_GP){
                        if (chaseGP==true)
                            posxGP--;
                        else
                            posxGP++;
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==5){
                if (posxGP==-22+j && posyGP==27-i){
                    if(posyGP>chaseY_GP){
                        if (chaseGP==true)
                            posyGP--;
                        else
                            posyGP++;
                    }
                    else if(posyGP<chaseY_GP){
                        if (chaseGP==true)
                            posyGP++;
                        else
                            posyGP--;
                    }
                    goto anotherP;
                }
            }
            else if(movement_array[i][j]==6){
                if (posxGP==-22+j && posyGP==27-i){
                    if(posxGP<chaseX_GP){
                        if (chaseGP==true)
                            posxGP++;
                        else
                            posxGP--;
                    }
                    else if(posxGP>chaseX_GP){
                        if (chaseGP==true)
                            posxGP--;
                        else
                            posxGP++;
                    }
                    else if(posyGP>chaseY_GP){
                        if (chaseGP==true)
                            posyGP--;
                        break;
                    }
                }
            }
            else if(movement_array[i][j]==7){
                if (posxGP==-22+j && posyGP==27-i){
                    if(posyGP<chaseY_GP){
                        if (chaseGP==true)
                            posyGP++;
                    }
                    else if(posxGP<chaseX_GP){
                        if (chaseGP==true)
                            posxGP++;
                        else
                            posxGP--;
                    }
                    else if(posxGP>chaseX_GP){
                        if (chaseGP==true)
                            posxGP--;
                        else
                            posxGP++;
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==8){
                if (posxGP==-22+j && posyGP==27-i){
                    if(posyGP>chaseY_GP){
                        if (chaseGP==true)
                            posyGP--;
                        else
                            posyGP++;
                    }
                    else if(posyGP<chaseY_GP){
                        if (chaseGP==true)
                            posyGP++;
                        else
                            posyGP--;
                    }
                    else if(posxGP<chaseX_GP){
                        if (chaseGP==true){
                            posxGP++;
                        }
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==9){
                if (posxGP==-22+j && posyGP==27-i){
                    if(posxGP>chaseX_GP){
                        if (chaseGP==true)
                            posxGP--;
                    }
                    else if(posyGP<chaseY_GP){
                        if (chaseGP==true)
                            posyGP++;
                        else
                            posyGP--;
                    }
                    else if(posyGP>chaseY_GP){
                        if (chaseGP==true)
                            posyGP--;
                        else
                            posyGP++;
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==10){
                if (posxGP==-22+j && posyGP==27-i){
                    if(posxGP<chaseX_GP){
                        if (chaseGP==true)
                            posxGP++;
                    }
                    else if(posyGP<chaseY_GP){
                        if (chaseGP==true)
                            posyGP++;
                        if (chaseX_GP<=posxGP && chaseY_GP<=posyGP ){
                            tempcounterP=0;
                            chaseX_GP=40;
                            chaseY_GP=-25;
                        }
                        break;
                    }
                }
            }
            else if(movement_array[i][j]==11){
                if (posxGP==-22+j && posyGP==27-i){
                    if(posyGP<chaseY_GP){
                        if (chaseGP==true)
                            posyGP++;
                    }
                    else if(posxGP>chaseX_GP){
                        if (chaseGP==true)
                            posxGP--;
                    }
                    if (chaseX_GP>=posxGP  && chaseY_GP<=posyGP ){
                        tempcounterP=0;
                        chaseX_GP=-20;
                        chaseY_GP=-23;
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==12){
                if (posxGP==-22+j && posyGP==27-i){
                    if(posyGP>chaseY_GP){
                        if (chaseGP==true)
                            posyGP--;
                    }
                    else if(posxGP<chaseX_GP){
                        if (chaseGP==true)
                            posxGP++;
                    }
                    if (chaseX_GP<=posxGP  && chaseY_GP>=posyGP ){
                        tempcounterP=0;
                        chaseX_GP=-20;
                        chaseY_GP=-23;
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==13){
                if (posxGP==-22+j && posyGP==27-i){
                    if(posxGP>chaseX_GP){
                        if (chaseGP==true)
                            posxGP--;

                    }
                    else if(posyGP>chaseY_GP){
                        if (chaseGP==true)
                            posyGP--;
                    }
                    if (chaseX_GP>=posxGP  && chaseY_GP>=posyGP ){
                        tempcounterP=0;
                        chaseX_GP=40;
                        chaseY_GP=-25;
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==14){
                if (posxGP==-22+j && posyGP==27-i){
                    if(posyGP>chaseY_GP){
                        if (chaseGP==true)
                            posyGP--;
                        else
                            posyGP++;
                        break;
                    }
                    else if(posxGP<chaseX_GP){
                        if (chaseGP==true)
                            posxGP++;
                        else
                            posxGP--;
                        break;
                    }
                    else if(posyGP<chaseY_GP){
                        if (chaseGP==true)
                            posyGP++;
                        else
                            posyGP--;
                        break;
                    }
                    else if(posxGP>chaseX_GP){
                        if (chaseGP==true)
                            posxGP--;
                        else
                            posxGP++;
                        break;
                    }
                }
            }
            else if(movement_array[i][j]==15){
                if (posxGP==-22+j && posyGP==27-i){
                    posxGP=17 ;
                    posyGP=1;
                    break;
                }
            }
            else if(movement_array[i][j]==16){
                if (posxGP==-22+j && posyGP==27-i){
                    posxGP=-21 ;
                    posyGP=1 ;
                    break;
                }
            }
        }
    }
    anotherP:;

    for(int i=0; i<MOVEMENT_Y; i++){
        for(int j=0; j<MOVEMENT_X; j++){
            if(movement_array[i][j]==4){
                if(posxGO==-22+j && posyGO==27-i){
                    if(posxGO<chaseX_GO){
                        if (chaseGO==true)
                            posxGO++;
                        else
                            posxGO--;
                    }
                    else if(posxGO>chaseX_GO){
                        if (chaseGO==true)
                            posxGO--;
                        else
                            posxGO++;
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==5){
                if (posxGO==-22+j && posyGO==27-i){
                    if(posyGO>chaseY_GO){
                        if (chaseGO==true)
                            posyGO--;
                        else
                            posyGO++;
                    }
                    else if(posyGO<chaseY_GO){
                        if (chaseGO==true)
                            posyGO++;
                        else
                            posyGO--;
                    }
                    goto anotherO;
                }
            }
            else if(movement_array[i][j]==6){
                if (posxGO==-22+j && posyGO==27-i){
                    if(posxGO<chaseX_GO){
                        if (chaseGO==true)
                            posxGO++;
                        else
                            posxGO--;
                    }
                    else if(posxGO>chaseX_GO){
                        if (chaseGO==true)
                            posxGO--;
                        else
                            posxGO++;
                    }
                    else if(posyGO>chaseY_GO){
                        if (chaseGO==true)
                            posyGO--;
                        break;
                    }
                }
            }
            else if(movement_array[i][j]==7){
                if (posxGO==-22+j && posyGO==27-i){
                    if(posyGO<chaseY_GO){
                        if (chaseGO==true)
                            posyGO++;
                    }
                    else if(posxGO<chaseX_GO){
                        if (chaseGO==true)
                            posxGO++;
                        else
                            posxGO--;
                    }
                    else if(posxGO>chaseX_GO){
                        if (chaseGO==true)
                            posxGO--;
                        else
                            posxGO++;
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==8){
                if (posxGO==-22+j && posyGO==27-i){
                    if(posyGO>chaseY_GO){
                        if (chaseGO==true)
                            posyGO--;
                        else
                            posyGO++;
                    }
                    else if(posyGO<chaseY_GO){
                        if (chaseGO==true)
                            posyGO++;
                        else
                            posyGO--;
                    }
                    else if(posxGO<chaseX_GO){
                        if (chaseGO==true){
                            posxGO++;
                        }
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==9){
                if (posxGO==-22+j && posyGO==27-i){
                    if(posxGO>chaseX_GO){
                        if (chaseGO==true)
                            posxGO--;
                    }
                    else if(posyGO<chaseY_GO){
                        if (chaseGO==true)
                            posyGO++;
                        else
                            posyGO--;
                    }
                    else if(posyGO>chaseY_GO){
                        if (chaseGO==true)
                            posyGO--;
                        else
                            posyGO++;
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==10){
                if (posxGO==-22+j && posyGO==27-i){
                    if(posxGO<chaseX_GO){
                        if (chaseGO==true)
                            posxGO++;
                    }
                    else if(posyGO<chaseY_GO){
                        if (chaseGO==true)
                            posyGO++;
                        if (chaseX_GO<=posxGO && chaseY_GO<=posyGO ){
                            tempcounterO=0;
                            chaseX_GO=40;
                            chaseY_GO=-25;
                        }
                        break;
                    }
                }
            }
            else if(movement_array[i][j]==11){
                if (posxGO==-22+j && posyGO==27-i){
                    if(posyGO<chaseY_GO){
                        if (chaseGO==true)
                            posyGO++;
                    }
                    else if(posxGO>chaseX_GO){
                        if (chaseGO==true)
                            posxGO--;
                    }
                    if (chaseX_GO>=posxGO  && chaseY_GO<=posyGO ){
                        tempcounterO=0;
                        chaseX_GO=-20;
                        chaseY_GO=-23;
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==12){
                if (posxGO==-22+j && posyGO==27-i){
                    if(posyGO>chaseY_GO){
                        if (chaseGO==true)
                            posyGO--;
                    }
                    else if(posxGO<chaseX_GO){
                        if (chaseGO==true)
                            posxGO++;
                    }
                    if (chaseX_GO<posxGO  && chaseY_GO>=posyGO ){
                        tempcounterO=0;
                        chaseX_GO=-20;
                        chaseY_GO=-23;
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==13){
                if (posxGO==-22+j && posyGO==27-i){
                    if(posxGO>chaseX_GO){
                        if (chaseGO==true)
                            posxGO--;

                    }
                    else if(posyGO>chaseY_GO){
                        if (chaseGO==true)
                            posyGO--;
                    }
                    if (chaseX_GO>=posxGO  && chaseY_GO>=posyGO ){
                        tempcounterO=0;
                        chaseX_GO=40;
                        chaseY_GO=-25;
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==14){
                if (posxGO==-22+j && posyGO==27-i){
                    if(posyGO>chaseY_GO){
                        if (chaseGO==true)
                            posyGO--;
                        else
                            posyGO++;
                        break;
                    }
                    else if(posxGO<chaseX_GO){
                        if (chaseGO==true)
                            posxGO++;
                        else
                            posxGO--;
                        break;
                    }
                    else if(posyGO<chaseY_GO){
                        if (chaseGO==true)
                            posyGO++;
                        else
                            posyGO--;
                        break;
                    }
                    else if(posxGO>chaseX_GO){
                        if (chaseGO==true)
                            posxGO--;
                        else
                            posxGO++;
                        break;
                    }
                }
            }
            else if(movement_array[i][j]==15){
                if (posxGO==-22+j && posyGO==27-i){
                    posxGO=17 ;
                    posyGO=1;
                    break;
                }
            }
            else if(movement_array[i][j]==16){
                if (posxGO==-22+j && posyGO==27-i){
                    posxGO=-21 ;
                    posyGO=1 ;
                    break;
                }
            }
        }
    }
    anotherO:;

    for(int i=0; i<MOVEMENT_Y; i++){
        for(int j=0; j<MOVEMENT_X; j++){
            if(movement_array[i][j]==4){
                if(posxGB==-22+j && posyGB==27-i){
                    if(posxGB<chaseX_GB){
                        if (chaseGB==true)
                            posxGB++;
                        else
                            posxGB--;
                    }
                    else if(posxGB>chaseX_GB){
                        if (chaseGB==true)
                            posxGB--;
                        else
                            posxGB++;
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==5){
                if (posxGB==-22+j && posyGB==27-i){
                    if(posyGB>chaseY_GB){
                        if (chaseGB==true)
                            posyGB--;
                        else
                            posyGB++;
                    }
                    else if(posyGB<chaseY_GB){
                        if (chaseGB==true)
                            posyGB++;
                        else
                            posyGB--;
                    }
                    goto anotherB;
                }
            }
            else if(movement_array[i][j]==6){
                if (posxGB==-22+j && posyGB==27-i){
                    if(posxGB<chaseX_GB){
                        if (chaseGB==true)
                            posxGB++;
                        else
                            posxGB--;
                    }
                    else if(posxGB>chaseX_GB){
                        if (chaseGB==true)
                            posxGB--;
                        else
                            posxGB++;
                    }
                    else if(posyGB>chaseY_GB){
                        if (chaseGB==true)
                            posyGB--;
                        break;
                    }
                }
            }
            else if(movement_array[i][j]==7){
                if (posxGB==-22+j && posyGB==27-i){
                    if(posyGB<chaseY_GB){
                        if (chaseGB==true)
                            posyGB++;
                    }
                    else if(posxGB<chaseX_GB){
                        if (chaseGB==true)
                            posxGB++;
                        else
                            posxGB--;
                    }
                    else if(posxGB>chaseX_GB){
                        if (chaseGB==true)
                            posxGB--;
                        else
                            posxGB++;
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==8){
                if (posxGB==-22+j && posyGB==27-i){
                    if(posyGB>chaseY_GB){
                        if (chaseGB==true)
                            posyGB--;
                        else
                            posyGB++;
                    }
                    else if(posyGB<chaseY_GB){
                        if (chaseGB==true)
                            posyGB++;
                        else
                            posyGB--;
                    }
                    else if(posxGB<chaseX_GB){
                        if (chaseGB==true){
                            posxGB++;
                        }
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==9){
                if (posxGB==-22+j && posyGB==27-i){
                    if(posxGB>chaseX_GB){
                        if (chaseGB==true)
                            posxGB--;
                    }
                    else if(posyGB<chaseY_GB){
                        if (chaseGB==true)
                            posyGB++;
                        else
                            posyGB--;
                    }
                    else if(posyGB>chaseY_GB){
                        if (chaseGB==true)
                            posyGB--;
                        else
                            posyGB++;
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==10){
                if (posxGB==-22+j && posyGB==27-i){
                    if(posxGB<chaseX_GB){
                        if (chaseGB==true)
                            posxGB++;
                    }
                    else if(posyGB<chaseY_GB){
                        if (chaseGB==true)
                            posyGB++;
                        if (chaseX_GB<=posxGB && chaseY_GB<=posyGB ){
                            tempcounterB=0;
                            chaseX_GB=40;
                            chaseY_GB=-25;
                        }
                        break;
                    }
                }
            }
            else if(movement_array[i][j]==11){
                if (posxGB==-22+j && posyGB==27-i){
                    if(posyGB<chaseY_GB){
                        if (chaseGB==true)
                            posyGB++;
                    }
                    else if(posxGB>chaseX_GB){
                        if (chaseGB==true)
                            posxGB--;
                    }
                    if (chaseX_GB>=posxGB  && chaseY_GB<=posyGB ){
                        tempcounterB=0;
                        chaseX_GB=-20;
                        chaseY_GB=-23;
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==12){
                if (posxGB==-22+j && posyGB==27-i){
                    if(posyGB>chaseY_GB){
                        if (chaseGB==true)
                            posyGB--;
                    }
                    else if(posxGB<chaseX_GB){
                        if (chaseGB==true)
                            posxGB++;
                    }
                    if (chaseX_GB<=posxGB  && chaseY_GB>=posyGB ){
                        tempcounterB=0;
                        chaseX_GB=-20;
                        chaseY_GB=-23;
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==13){
                if (posxGB==-22+j && posyGB==27-i){
                    if(posxGB>chaseX_GB){
                        if (chaseGB==true)
                            posxGB--;

                    }
                    else if(posyGB>chaseY_GB){
                        if (chaseGB==true)
                            posyGB--;
                    }
                    if (chaseX_GB>=posxGB  && chaseY_GB>=posyGB ){
                        tempcounterB=0;
                        chaseX_GB=40;
                        chaseY_GB=-25;
                    }
                    break;
                }
            }
            else if(movement_array[i][j]==14){
                if (posxGB==-22+j && posyGB==27-i){
                    if(posyGB>chaseY_GB){
                        if (chaseGB==true)
                            posyGB--;
                        else
                            posyGB++;
                        break;
                    }
                    else if(posxGB<chaseX_GB){
                        if (chaseGB==true)
                            posxGB++;
                        else
                            posxGB--;
                        break;
                    }
                    else if(posyGB<chaseY_GB){
                        if (chaseGB==true)
                            posyGB++;
                        else
                            posyGB--;
                        break;
                    }
                    else if(posxGB>chaseX_GB){
                        if (chaseGB==true)
                            posxGB--;
                        else
                            posxGB++;
                        break;
                    }
                }
            }
            else if(movement_array[i][j]==15){
                if (posxGB==-22+j && posyGB==27-i){
                    posxGB=17 ;
                    posyGB=1;
                    break;
                }
            }
            else if(movement_array[i][j]==16){
                if (posxGB==-22+j && posyGB==27-i){
                    posxGB=-21 ;
                    posyGB=1 ;
                    break;
                }
            }
        }
    }
    anotherB:;

}

void logic(){


    chase_counter++;
    counter++;
    counterB++;
    counterO++;
    counterP++;

    if (chaseGBR==false){
        rBR=0;
        gBR=0;
        bBR=0;
        wBR=1;
    }
    if (chaseGP==false){
        rP=0;
        gP=0;
        bP=0;
        wP=1;
    }
    if (chaseGO==false){
        rO=0;
        gO=0;
        bO=0;
        wO=1;
    }
    if (chaseGO==false){
        rB=0;
        gB=0;
        bB=0;
        wB=1;
    }
    if (chase_counter >= 55){
        chaseGBR = true;
        chaseGB = true;
        chaseGO = true;
        chaseGP = true;
        rBR=1;  rP=1;   rO=1;   rB=1;
        gBR=1;  gP=1;   gO=1;   gB=1;
        bBR=1;  bP=1;   bO=1;   bB=1;
        wBR=0;  wP=0;   wO=0;   wB=0;
    }
    if (chaseGP==true){
        rP=1;
        gP=1;
        bP=1;
        wP=0;
    }
    if (chaseGBR==true){
        rBR=1;
        gBR=1;
        bBR=1;
        wBR=0;
    }
    if (chaseGO==true){
        rO=1;
        gO=1;
        bO=1;
        wO=0;
    }
    if (chaseGB==true){
        rB=1;
        gB=1;
        bB=1;
        wB=0;
    }


    if(chaseGBR==false && posx==posxGBR && posy==posyGBR){
        Sleep(1000);
        posxGBR=-2;
        posyGBR=7;
        chaseGBR=true;
        counter=0;
    }
    if(chaseGP==false && posx==posxGP && posy==posyGP){
        Sleep(1000);
        posxGP=-2;
        posyGP=7;
        chaseGP=true;
        counterP=55;
    }
    if(chaseGO==false && posx==posxGO && posy==posyGO){
        Sleep(1000);
        posxGO=-2;
        posyGO=7;
        chaseGO=true;
        counterO=165;
    }
    if(chaseGB==false && posx==posxGB && posy==posyGB){
        Sleep(1000);
        posxGB=-2;
        posyGB=7;
        chaseGB=true;
        counterB=210;
    }
    if (tempcounter<13){
        tempcounter++;
        goto jumper;
    }

    if(counter<55){
        chaseX_GBR=initial_posxGBR;
        chaseY_GBR=initial_posyGBR;

        if (posxGBR==8 && posyGBR==17){
            initial_posxGBR= 16;
        }
        else if (posxGBR==16 && posyGBR==17){
            initial_posyGBR= 25;
        }
        else if (posxGBR==16  && posyGBR==25){
            initial_posxGBR =8;
        }
        else if (posxGBR==8 && posyGBR==25){
            initial_posyGBR =17;
        }
    }
    else if (counter>55){
        chaseX_GBR=posx;
        chaseY_GBR=posy;
        if (counter>165)
            counter=0;

        initial_posxGBR= 8;
        initial_posyGBR= 17;
    }
    jumper:






    if (tempcounterP<9){
        tempcounterP++;
        goto jumperP;
    }
    if (counterP==54){
        posxGP=-2;
        posyGP=7;
    }
    if(counter>55 && counter<110){
        chaseX_GP=initial_posxGP;
        chaseY_GP=initial_posyGP;

        if (posxGP==-12 && posyGP==17){
            initial_posxGP= -20;
        }
        else if (posxGP==-20 && posyGP==17){
            initial_posyGP= 25;
        }
        else if (posxGP==-20  && posyGP==25){
            initial_posxGP =-12;
        }
        else if (posxGP==-12 && posyGP==25){
            initial_posyGP =17;
        }
    }
    else if (counterP>110){
        if(posy>posyGP)
            chaseY_GP=posy;
        if(posy<posyGP)
            chaseY_GP=posy;
        if(posx-8>posxGP)
            chaseX_GP=posx - 8;
        if(posx+8<posxGP)
            chaseX_GP=posx - 8;

        if (counterP>=220)
            counterP=55;

        initial_posxGP= -12;
        initial_posyGP= 17;
    }



    jumperP:;



    if (tempcounterO<9){
        tempcounterO++;
        goto jumperO;
    }
    if (counterO==54){
        posxGO=-2;
        posyGO=7;
    }
    if(counterO>165 && counterO<220){
        chaseX_GO=initial_posxGO;
        chaseY_GO=initial_posyGO;

        if (posxGO==-20 && posyGO==-19){
            initial_posyGO= -23;
        }
        else if (posxGO==-20 && posyGO==-23){
            initial_posxGO=-4;
        }
        else if (posxGO==-4 && posyGO==-23){
            initial_posyGO =-19;
        }
        else if (posxGO==-4  && posyGO==-19){
            initial_posxGO =-8;
        }
        else if (posxGO==-8 && posyGO==-19){
            initial_posyGO =-13;
        }
        else if (posxGO==-8 && posyGO==-13){
            initial_posxGO =-12;
        }
        else if (posxGO==-12 && posyGO==-13){
            initial_posyGO =-19;
        }
        else if (posxGO==-12 && posyGO==-19){
            initial_posxGO =-20;
//            initial_posxGO= -20;
//            initial_posyGO= -19;
        }
    }
    else if (counterO>220){
        chaseX_GO=posx;
        chaseY_GO=posy;
        if(posy>posyGO){
            if (posyGO + 16 > posy)
                counterO=165;
        }
        else if(posy<posyGO){
            if (posyGO - 16 < posy)
                counterO=165;
        }
        else if(posx>posxGO){
            if (posxGO + 16 > posx)
                counterO=165;
        }
        else if(posx<posxGO){
            if (posxGO - 16 < posx)
                counterO=165;
        }
    }
    else if (counterO>=330 || counterO==165){
        counterO=165;
        initial_posxGO= -20;
        initial_posyGO= -19;
    }


    jumperO:;



    if (tempcounterB<9){
        tempcounterB++;
        goto jumperB;
    }
    if (counterB==210){
        posxGB=-2;
        posyGB=7;
    }
    if(counterB>210 && counterB<275){
        chaseX_GB=initial_posxGB;
        chaseY_GB=initial_posyGB;

        if (posxGB==16 && posyGB==-19){
            initial_posyGB= -23;
        }
        else if (posxGB==16 && posyGB==-23){
            initial_posxGB=0;
        }
        else if (posxGB==0 && posyGB==-23){
            initial_posyGB =-19;
        }
        else if (posxGB==0  && posyGB==-19){
            initial_posxGB =4;
        }
        else if (posxGB==4 && posyGB==-19){
            initial_posyGB =-13;
        }
        else if (posxGB==4 && posyGB==-13){
            initial_posxGB =8;
        }
        else if (posxGB==8 && posyGB==-13){
            initial_posyGB =-19;
        }
        else if (posxGB==8 && posyGB==-19){
            initial_posxGB =16;
        }
    }
    else if (counterB>275){
        chaseX_GB=posxGBR + 8;
        chaseY_GB=posyGBR + 8;
        if(posyGBR-8>posyGB)
            chaseY_GB=posyGBR+8;
        if(posyGBR+8<posyGB)
            chaseY_GB=posyGBR-8;
        if(posxGBR-8>posxGB)
            chaseX_GB=posxGBR + 8;
        if(posxGBR+8<posxGB)
            chaseX_GB=posxGBR - 8;

    }
    else if (counterB>=375 || counterB==210){
        counterB=211;
        initial_posxGB= 16;
        initial_posyGB= -19;
    }

    jumperB:;

    if((posyGP==posy && posxGP==posx && chaseGP==true) || (posyGBR==posy && posxGBR==posx && chaseGBR==true) || (posyGO==posy && posxGO==posx && chaseGO==true) || (posyGB==posy && posxGB==posx && chaseGB==true)){
        Sleep(2000);
        posx=-2;
        posy=-13;
        posxGP=-2;
        posyGP=1;
        posxGBR=-2;
        posyGBR=7;
        posxGO=0;
        posyGO=1;
        posxGB=-4;
        posyGB=1;
        counter=0;
        counterP=0;
        counterO=0;
        counterB=0;
        PdirectionX=LEFT;
        life_count--;
    }
    if (life_count==0 || pellet_counter==193){
        for(int i=0; i<MOVEMENT_Y; i++){
            for(int j=0; j<MOVEMENT_X; j++){
                board_array[i][j]=temp_board_array[i][j];
            }
        }
        life_count=3;
        pellet_counter=0;
        posx=-2;
        posy=-13;
        posxGP=-2;
        posyGP=1;
        posxGB=-4;
        posyGB=1;
        posxGBR=-2;
        posyGBR=7;
        posxGO=0;
        posyGO=1;
        out_state=ENDGAME;
        in_state=STOP_IN;

    }
}

void timer(int){
    glutPostRedisplay();
    glutTimerFunc(1000/9.5, timer, 0);

}
void keyboard_callback(int key, int, int){
    switch (key){
    case GLUT_KEY_UP:
        PdirectionY = UP;
        Pdirection = up;
        break;
    case GLUT_KEY_DOWN:
        PdirectionY = DOWN;
        Pdirection = down;
        break;
    case GLUT_KEY_RIGHT:
        PdirectionX = RIGHT;
        Pdirection = right;
        break;
    case GLUT_KEY_LEFT:
        PdirectionX = LEFT;
        Pdirection = left;
        break;
     }
}
