#include "main.h"

/**
 * receivePayment: Receives Payment information and reads the information.
 * Return: Nothing
 */
 
void receivePayment(char *paymentStatement, int msgLength, bool *msgSignal) {

  int index;

  index = 0;
  
  if (sim800.available()) {
    
    *msgSignal = true;
    
    while(index <= msgLength - 1) {
      index = sim800.readBytes(paymentStatement, msgLength - 1);
      if (index >= msgLength - 1) {
          paymentStatement[index] = '\0';
          break;
      }
     }  
  }
}


/**
 * parsePayment: receives payment and parses info to extract,
 * name of client, client contact, and transaction detail.
 * @msg: mpesaMsg received
 * Return: Details struct having the name of client,,
 * amount paid..
 * 
 */
 
void parsePayment(String mpesaStatement, paymentInfo *paymentInfo) {
 
  String clientName;
  String phoneNo;
  String amt;


  
   clientName = extractClientName(mpesaStatement);
   phoneNo = extractPhoneNo(mpesaStatement);
   amt = extractAmt(mpesaStatement);
   
   paymentInfo -> phoneNo = phoneNo;
   paymentInfo -> clientName = clientName;
   paymentInfo -> amt = amt;

}

/**
 * 
 */

String extractAmt(String mpesaStatement) {
  int startIndex;
  int endIndex;
  String amt;

  startIndex = 0;
  endIndex = 0;
  
  startIndex = mpesaStatement.indexOf("Received Ksh ");
  endIndex = mpesaStatement.indexOf(" from");

  if (startIndex != -1) {
    startIndex += 13;
    amt = mpesaStatement.substring(startIndex, endIndex);
    }
    else {
      amt = "Not Found";
    }
   return amt;
  }


String extractClientName(String mpesaStatement) {
  int startIndex;
  int endIndex;

  startIndex = 0;
  endIndex = 0;

  startIndex = mpesaStatement.indexOf(" from ");
  int start254 = mpesaStatement.indexOf(" 254");
  int second254 = mpesaStatement.indexOf(" 254", startIndex);

  endIndex  = second254 == -1 ? start254 : second254;

  return mpesaStatement.substring(startIndex + 6, endIndex);
  
}


String extractPhoneNo(String mpesaStatement) {
  int startIndex;
  int endIndex;


  startIndex = 0;
  endIndex = 0;

  int first254 = mpesaStatement.indexOf(" 254");
  int next254 = mpesaStatement.indexOf(" 254", first254 + 12);

  startIndex = (next254 == -1)? first254: next254;
  endIndex = mpesaStatement.indexOf(" on ");

  
  return mpesaStatement.substring(startIndex, endIndex);
  }

/**
 * sendConfirmationPin: sends the confirmation pin upon receiving the payment message. 
 * Return:
 * 
 */
 
void sendConfirmationPin() {
  
  
}
