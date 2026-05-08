#ifndef MAIN_H
#define MAIN_H


#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>



typedef struct clientInfo {
  String clientName;
  String phoneNo;
  String amt;
  } clientInfo;

extern HardwareSerial sim800;
void receivePayment(char *paymentStatement, int msgLength, int *msgSignal);
void sendConfirmationPin();
clientInfo *parsePayment(String mpesaStatement);
String extractAmt(String mpesaStatement);
String extractClientName(String mpesaStatement);
String extractPhoneNo(String mpesaStatement);

  
#endif 
