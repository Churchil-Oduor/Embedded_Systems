#include "main.h"

/**
 * receivePayment: Receives Payment information.
 * Return: Nothing
 */
 
void receivePayment(char *paymentStatement, int msgLength, int *msgSignal) {
  
  int index = 0;
  
  while(sim800.available()) {
    
    char c = sim800.read();
    *msgSignal = 1;

    index = sim800.readBytes(paymentStatement, msgLength - 1);
    //paymentStatement[index++] = c;
    
    if (index >= msgLength - 1)
        break;
    }
    paymentStatement[index] = '\0';
}


/**
 * parsePayment: receives payment and parses info to extract,
 * name of client, client contact, and transaction detail.
 * @msg: mpesaMsg received
 * Return: Details struct having the name of client,,
 * amount paid..
 * 
 */
 
clientInfo *parsePayment(String mpesaStatement) {
 
  String clientName;
  String phoneNo;
  String amt;
  clientInfo *paymentInfo;
  int startIndex;
  int endIndex;


  startIndex = 0;
  endIndex = 0;

  paymentInfo = new clientInfo;

   clientName = extractClientName(mpesaStatement);
   phoneNo = extractPhoneNo(mpesaStatement);
   amt = extractAmt(mpesaStatement);
   
   paymentInfo -> phoneNo = phoneNo;
   paymentInfo -> clientName = clientName;
   paymentInfo -> amt = amt;

   return paymentInfo;  
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
  String clientName;
  int startIndex;
  int endIndex;

  startIndex = 0;
  endIndex = 0;

  startIndex = mpesaStatement.indexOf("from ");
  endIndex = mpesaStatement.indexOf("254", mpesaStatement.indexOf("254") + 1);

  if (endIndex == -1)
     endIndex = mpesaStatement.indexOf("254");

  clientName = mpesaStatement.substring(startIndex + 5, endIndex);

  return clientName;
  
}


String extractPhoneNo(String mpesaStatement) {
  String phoneNo;
  int startIndex;
  int endIndex;

  startIndex = 0;
  endIndex = 0;

  startIndex = mpesaStatement.indexOf("254", mpesaStatement.indexOf("254") + 1) == -1 ? mpesaStatement.indexOf("254"): 
  mpesaStatement.indexOf("254", mpesaStatement.indexOf("254") + 1);


  endIndex = mpesaStatement.indexOf(" on ");
  phoneNo = mpesaStatement.substring(startIndex, endIndex);

  return phoneNo;
  
  }

/**
 * sendConfirmationPin: sends the confirmation pin upon receiving the payment message. 
 * Return:
 * 
 */
 
void sendConfirmationPin() {
  
  
}
