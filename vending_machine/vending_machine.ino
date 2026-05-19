HardwareSerial sim800(2);

#include "main.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int SDA_PIN = 18;
const int SCL_PIN = 19;

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte colPins[COLS]= {23, 5, 13, 12};
byte rowPins[ROWS]  = {14, 27, 16, 17};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String input = "";


void setup() {

  pinMode(12, OUTPUT);
  Serial.begin(9600);
  sim800.begin(9600, SERIAL_8N1, 25, 26);
  
  Wire.begin(SDA_PIN, SCL_PIN);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("sim800 booting...");


  //attention
  sim800.println("AT");
  Serial.println(sim800.readString());
  delay(1000);


  //sim card status check
  sim800.println("AT+CPIN?");
  Serial.println(sim800.readString());
  delay(1000);


  //network registration status.
  sim800.println("AT+CREG?");
  Serial.println(sim800.readString());
  delay(1000);


  //signal strength check
  sim800.println("AT+CSQ");
  Serial.println(sim800.readString());
  delay(1000);

  
  //setting mode to sms
  sim800.println("AT+CMGF=1");
 // Serial.println(sim800.readString());
  delay(500);


  
  sim800.println("AT+CNMI=1,2,0,0,0");
 // Serial.println(sim800.readString());
  delay(500);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Ready..");
  delay(500);
}



void loop()
{
  bool msgSignal = false;
  bool msgSentToClient = false;
  bool responseStatus = true;
  paymentInfo paymentInfo;
  String message;
  


   if (sim800.available())
      digitalWrite(12, HIGH);
    else
      digitalWrite(12, LOW);
  
  receivePayment(&message, sizeof(message), &msgSignal);

  if (msgSignal == true)
  {  
   
    parsePayment(String(message), &paymentInfo, &responseStatus);

   

    if (responseStatus == true) {
          Serial.println("Name: "+ paymentInfo.clientName);
          Serial.println("Phone: " + paymentInfo.phoneNo);
          Serial.println("Amount: " +  paymentInfo.amt);
	        Serial.println("Code:" + paymentInfo.code);
          lcd.clear();
          lcd.print(paymentInfo.clientName);
          sendMsgCode(paymentInfo, &msgSentToClient);
      } else 
      {
        Serial.println("");
        }
  }

  if (msgSentToClient) {
    
    }
  delay(1000);
  
}



/*void loop() {

  char key = keypad.getKey();

  if (key) {

    Serial.print(key);

    if (key == '*') {
      input = "";
      lcd.clear();
      lcd.print("Enter:");
    }

    else if (key == '#') {
      lcd.clear();
      lcd.print("Sending...");

      sendSMS(input, "Hello Nelson, Water Vendor says Hi!");

      delay(2000);

      input = "";
      lcd.clear();
      lcd.print("Enter:");
    }

    else {
      input += key;

      lcd.setCursor(0,1);
      lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.print(input);
    }
  }
}*/
