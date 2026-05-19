#ifndef MAIN_H
#define MAIN_H


#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <random>


typedef struct paymentInfo {
  String clientName;
  String phoneNo;
  String amt;
  String code;
  } paymentInfo;

extern HardwareSerial sim800;
String generateCode();
void receivePayment(String *paymentStatement, int msgLength, bool *msgSignal);
void sendMsgCode(paymentInfo paymentInfo, bool *msgSentToClient);
void parsePayment(String mpesaStatement, paymentInfo *paymentInfo, bool *responseStatus);
String extractAmt(String mpesaStatement, bool *responseStatus);
String extractClientName(String mpesaStatement, bool *responseStatus);
String extractPhoneNo(String mpesaStatement, bool *responseStatus);

  
#endif 
