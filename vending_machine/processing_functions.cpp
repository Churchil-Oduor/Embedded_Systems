#include "main.h"

/**
 * receivePayment: Receives Payment information and reads the information.
 * @msgLength: maximum number of characters in the mpesa statement information
 * @msgSignal: check to see if there is information being received.
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
 * @mpesaStatement: mpesa statement to be parsed.
 * @responseStatus: alert switch incase message is corrupted.
 * Return: Details struct having the name of client,,
 * amount paid.
 * 
 */
 
void parsePayment(String mpesaStatement, paymentInfo *paymentInfo, bool *responseStatus) {
 
  String clientName;
  String phoneNo;
  String amt;


  
   clientName = extractClientName(mpesaStatement, responseStatus);
   phoneNo = extractPhoneNo(mpesaStatement, responseStatus);
   amt = extractAmt(mpesaStatement, responseStatus);
   
   paymentInfo -> phoneNo = phoneNo;
   paymentInfo -> clientName = clientName;
   paymentInfo -> amt = amt;
   paymentInfo -> code = generateCode();

}

/**
 * extractAmt: from the mpesaStatement, retrieves the amount paid by client.
 * 
 * @mpesaStatement: received mpesastatement to be parsed.
 * @responseStatus: alert switch incase message is corrupted.
 * Return: Amount paid.
 */

String extractAmt(String mpesaStatement, bool *responseStatus) {
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
      *responseStatus = false;
    }
   return amt;
  }



/**
 * extractClientName: retrieves client's name from mpesa statement.
 * @mpesaStatement: mpesa statement containing client information.
 * @responseStatus: alert switch incase message is corrupted.
 * Return: Client's name
 */
String extractClientName(String mpesaStatement, bool *responseStatus) {
  int startIndex;
  int endIndex;

  startIndex = 0;
  endIndex = 0;

  startIndex = mpesaStatement.indexOf(" from ");
  int start254 = mpesaStatement.indexOf(" 254");
  int second254 = mpesaStatement.indexOf(" 254", startIndex);

  endIndex  = second254 == -1 ? start254 : second254;

  if (startIndex == -1 || endIndex == -1) {
    return "Error Occured";
    *responseStatus = false;
    }
  return mpesaStatement.substring(startIndex + 6, endIndex);
  
}


/**
 * extractPhoneNo: retrieves clients phone number.
 * @mpesaStatement: mpesa statement containing clients information.
 * @responseStatus: alert switch incase message is corrupted.
 * Return: clients phone number.
 */
String extractPhoneNo(String mpesaStatement, bool *responseStatus) {
  int startIndex;
  int endIndex;
  String phoneNo;


  startIndex = 0;
  endIndex = 0;

  int first254 = mpesaStatement.indexOf(" 254");
  int next254 = mpesaStatement.indexOf(" 254", first254 + 12);

  startIndex = (next254 == -1)? first254 + 1: next254 + 1;
  endIndex = mpesaStatement.indexOf(" on ");
  
    if (startIndex == -1 || endIndex == -1) {
      return "Error Occured";
      *responseStatus = false;
    }

    phoneNo = "+" + mpesaStatement.substring(startIndex, endIndex);
    phoneNo.replace(" ", "");
    
  return phoneNo;
  }



/**
 * sendConfirmationPin: sends the confirmation pin upon receiving the payment message.
 * @paymentInfo: clients info for message sending.
 * @msgSentClient: a check to ascertain message has been sent.
 * 
 */
 
void sendMsgCode(paymentInfo paymentInfo, bool *msgSentToClient)
{
  
    String message = "Karibu " + paymentInfo.clientName + " to Water Vendor.\n Use the code " + paymentInfo.code + " for dispensing.\n Water balance " + "3-Litres";

    sim800.print("AT+CMGS=\"");
    sim800.print(paymentInfo.phoneNo);
    sim800.println("\"");
  
    delay(1000);
    sim800.print(message);
    sim800.write(26);

    Serial.write(sim800.read());
    delay(1000);
  
    *msgSentToClient = true;
}
