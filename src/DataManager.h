#pragma once
#include <pebble.h>
#include <time.h>
  
#define THRIST_EXPIRE 60
#define FUN_EXPIRE 120
#define PLAY_EXPIRE 180
#define HUNGRY_EXPIRE 240


  /*
  The Amigo struct is to define the characteristics of the Amigo, in the pebble application
  Encluding heart, thirstExpire,funExpire, hungryExpire, and user_NameInput
  */
  struct Amigo 
 {
    int heart;
    time_t thirstExpire;
    time_t funExpire;
    time_t hungryExpire;
    time_t playExpire;
    char name[50];
 };

struct Amigo am;


/*
timesExpired will return the an int for the amount of times the amigo expired
if it didn't expire then it wuill return 0
*/

int timesExpired(time_t* currrentTime, time_t* expireTime, int length); 
  
/*
heartLost will return how many hearts the amigo lost in the application
*/

int heartLost(time_t* thrirstExpire,time_t* funExpire,time_t* hungryExpire);

/*
subtractHeart will take in the amount of hearts lost and subtract by how much the current hearts the amigo has
then it will update the expired time, and send  the new expired interval
*/
void subtractHeart(int heartLost);


