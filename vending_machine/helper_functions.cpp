#include "main.h"


/**
 * generateCode: generates a 5 digit code for the client.
 * @Return: returns the 5 digit code
 */

String generateCode() {

	int i;
	String code;
  const int codeLength = 4;

	String codes = "ABCD0123456789";
  code = "";
  
	for (i = 0; i < codeLength; i++)
	{
		int index = random(0, codes.length());
		code += codes[index];
	}
	return code;
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
