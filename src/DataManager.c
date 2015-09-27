#include <pebble.h>
#include <string.h>
#include "DataManager.h"
#define DATA_KEY 7

  void setHeart(int heart)
  {
    am.heart= heart;
    persist_write_data( DATA_KEY, &am , sizeof(struct Amigo));
  }
  int getheart()
  {
    return am.heart;
  }

void setThirstExpire(time_t thirstExpire)
  {
    am.thirstExpire = thirstExpire;
    persist_write_data( DATA_KEY, &am , sizeof(struct Amigo));
  
  }
  time_t getthirstExpire()
  {
    return am.thirstExpire;
  }

void setFunExpire(time_t funExpire)
  {
    am.funExpire = funExpire;
    persist_write_data( DATA_KEY, &am , sizeof(struct Amigo));
  
  }
  time_t getfunExpire()
  {
    return am.funExpire;
  }

void setHungryExpire(time_t hungryExpire)
  {
    am.hungryExpire = hungryExpire;
    persist_write_data( DATA_KEY, &am , sizeof(struct Amigo));
  
  }
  time_t gethungryExpire()
  {
    return am.hungryExpire;
  }

void setPlayExpire(time_t playExpire)
  {
    am.playExpire = playExpire;
    persist_write_data( DATA_KEY, &am , sizeof(struct Amigo));
  
  }
  time_t getplayExpire()
  {
    return am.playExpire;
  }


void dataInit()
  {
    if(persist_exists(DATA_KEY))
    {
       persist_read_data(DATA_KEY, &am, sizeof(struct Amigo));
    }
    else
      {
      char* john = "John";
      strcpy(am.name, john);
      setHeart(MAX_HEARTS);
      setThirstExpire(THRIST_EXPIRE + time(NULL));
      setFunExpire(FUN_EXPIRE + time(NULL));
      setHungryExpire(HUNGRY_EXPIRE + time(NULL));
      setPlayExpire(PLAY_EXPIRE + time(NULL));
      
      
      }
      
  }
/*
subtractHeart will take in the amount of hearts lost and subtract by how much the current hearts the amigo has
then it will update the expired time, and send  the new expired interval
*/
void subtractHeart(int heartLost)
  {
  am.heart -= heartLost; /* reduces the number of hearts from the heartlost  */
  
   time_t currentTime = time(NULL);
    
    int d = currentTime- am.thirstExpire;
    int l = am.thirstExpire;
    am.thirstExpire += ( d/l + (d % l == 0 ? 0 :1 )) * l; /* this will update thristExpire */
    
     d = currentTime - am.funExpire;
     l = am.funExpire;
    am.funExpire += ( d/l + (d % l == 0 ? 0 :1 )) * l; /* this will update funExpire */
    
    
     d = currentTime - am.hungryExpire;
     l = am.hungryExpire;
    am.hungryExpire += ( d/l + (d % l == 0 ? 0 :1 )) * l; /* this will update hungryExpire */
    
    
     d = currentTime - am.playExpire;
     l = am.playExpire;
    am.playExpire += ( d/l + (d % l == 0 ? 0 :1 )) * l; /* this will update playExpire */
    
   
} 
  

/*
heartLost will return how many hearts the amigo lost in the application
*/

int heartLost(time_t* thrirstExpire,time_t* funExpire,time_t* hungryExpire)
  {
    int heartLost = 0;
    time_t currentTime = time(NULL);
    heartLost += timesExpired(&currentTime, &am.thirstExpire, THRIST_EXPIRE);
    heartLost += timesExpired(&currentTime, &am.funExpire, FUN_EXPIRE);
    heartLost += timesExpired(&currentTime, &am.hungryExpire, HUNGRY_EXPIRE);
    heartLost += timesExpired(&currentTime, &am.playExpire, PLAY_EXPIRE);
    
  return heartLost;
  }

/*
timesExpired will return the an int for the amount of times the amigo expired for a given metrix
if it didn't expire then it wuill return 0
*/
int timesExpired(time_t* currentTime, time_t* expireTime, int length) 
  {
    if(*currentTime > *expireTime)
      {
        return (*expireTime - *currentTime) / length + 1;
      }
    else
      {
        return 0;
      }
  }