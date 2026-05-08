#ifndef MAIN_H
#define MAIN_H


#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>


extern HardwareSerial sim800;
void receivePayment(char *paymentStatement, int msgLength, int *msgSignal);
void sendConfirmationPin();

typedef struct clientInfo {
  char *clientName;
  int phoneNo;
  char *transactionID;
  } clientInfo;
  
#endif 
