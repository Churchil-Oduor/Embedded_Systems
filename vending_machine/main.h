#ifndef MAIN_H
#define MAIN_H


#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>



typedef struct paymentInfo {
  String clientName;
  String phoneNo;
  String amt;
  } paymentInfo;

extern HardwareSerial sim800;
void receivePayment(char *paymentStatement, int msgLength, bool *msgSignal);
void sendConfirmationPin();
void parsePayment(String mpesaStatement, paymentInfo *paymentInfo);
String extractAmt(String mpesaStatement);
String extractClientName(String mpesaStatement);
String extractPhoneNo(String mpesaStatement);

  
#endif 
