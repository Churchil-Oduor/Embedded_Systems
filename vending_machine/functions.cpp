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
 * Return: Details struct having the name of client, transaction ID,
 * amount paid and transaction ID.
 * 
 */
 
/**clientInfo *parsePayment(String mpesaStatement) {

  
}**/


/**
 * sendConfirmationPin: sends the confirmation pin upon receiving the payment message. 
 * Return:
 * 
 */
 
void sendConfirmationPin() {
  
  
}
