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
 * 
 */
