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
void parsePayment(String mpesaStatement, paymentInfo *paymentInfo, bool *responseStatus);
String extractAmt(String mpesaStatement, bool *responseStatus);
String extractClientName(String mpesaStatement, bool *responseStatus);
String extractPhoneNo(String mpesaStatement, bool *responseStatus);

  
#endif 
