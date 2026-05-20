#include "main.h"

String inputCode(){
  String code = "";
  char key;

  lcd.setCursor(0,0);
  lcd.print("Enter Code");
  
   while(true) {

    lcd.setCursor(0, 1);
    key = keypad.getKey();

    if (key != NO_KEY) {

     if (key == '*') {
      code = "";
      lcd.setCursor(0,0);
      lcd.print("Enter Code");
      lcd.setCursor(0, 1);
      }
      
     else if (key == '#')
     {
       break;
     }
     else {
      code += key;
      lcd.setCursor(0, 0);
      lcd.print("Enter Code");
      lcd.setCursor(0, 1);
      lcd.print(code);
      }
     }
    
    }

    
  return code;
  }
  
String inputPhone(){
  char key;
  String input;
  
  input = "+254";
  
  lcd.setCursor(0,0);
  lcd.print("Enter Phone");
  lcd.setCursor(0, 1);
  lcd.print(input);
  
  while(true) {

    lcd.setCursor(0, 1);
    key = keypad.getKey();

    if (key != NO_KEY) {


       if (key == '*') {
      input = "+254";
      lcd.setCursor(0,0);
      lcd.print("Enter Phone");
      lcd.setCursor(0, 1);
      lcd.print(input);
      }
      
     else if (key == '#')
     {

        if (input.length() == 13)
        {
          break;
        } else {
          lcd.clear();
          lcd.print("Incomplete Number!");
          delay(2000);
          lcd.clear();
          lcd.print(input);
          }
     }
     else {
      input += key;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter Phone");
      lcd.setCursor(0, 1);
      lcd.print(input);
      }
   
      }
    
  }
    
  return  input;
  }
  
bool verifyClient(paymentInfo paymentInfo)
{
  char key;
  bool check;
  String phone;
  String code;

  phone = inputPhone();

  lcd.clear();
  code = inputCode();
  
  if (paymentInfo.phoneNo == phone && paymentInfo.code == code)
      return true;
      
  return false;
}
