#include "main.h"

/**
 * receivePayment: Receives Payment information and reads the information.
 * @msgSignal: check to see if there is information being received.
 * Return: Nothing
 */
 
void receivePayment(String *paymentStatement, bool *msgSignal) {

  if (sim800.available()) {
    *paymentStatement = sim800.readString();
    *msgSignal = true;
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
    delay(1000);
  
    *msgSentToClient = true;
}



/**
 * verifyCode: verifies code shared by client.
 * @clientsCode: Code entered by client.
 * @code: systems assigned code to client.
 * Return: is code is correct return true else false.
 */

bool verifyCode(String code, String clientCode) {

  if (code == clientCode)
    return true;

  return false;
}









  
