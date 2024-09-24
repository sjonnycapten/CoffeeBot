#ifndef SET
#define SET
#include "Setup.h"
#endif

#define READY "001"
#define NOTREADY "002"
#define RECEIVED "04"




#define SIGNAL_NEW_COFFEE_REQUEST "11"

#define DESTINATION_INDEX 0

void SendCoffeeState();
void ChangeCoffeeState();
void HandleIncommingData(char * data);

char * AddDestToData(char *data,char *dest);
void IncreaseCoffeeCount();
void HandlePayload(uint8_t destination,uint8_t command);
void sendData(uint8_t command,uint8_t destination,char * toppic);
