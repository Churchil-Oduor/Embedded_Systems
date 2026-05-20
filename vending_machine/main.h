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

extern LiquidCrystal_I2C lcd;
extern HardwareSerial sim800;
extern Keypad keypad;
String inputCode();
String inputPhone();
String generateCode();
void receivePayment(String *paymentStatement, bool *msgSignal);
void sendMsgCode(paymentInfo paymentInfo, bool *msgSentToClient);
void parsePayment(String mpesaStatement, paymentInfo *paymentInfo, bool *responseStatus);
String extractAmt(String mpesaStatement, bool *responseStatus);
String extractClientName(String mpesaStatement, bool *responseStatus);
String extractPhoneNo(String mpesaStatement, bool *responseStatus);

bool verifyClient(paymentInfo paymentInfo);

  
#endif 
