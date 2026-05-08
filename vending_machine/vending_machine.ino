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

  Wire.begin(SDA_PIN, SCL_PIN);
  lcd.begin();
  lcd.backlight();

  Serial.begin(9600);
  sim800.begin(9600, SERIAL_8N1, 25, 26);

  lcd.setCursor(0,0);
  lcd.print("Enter:");

  sim800.println("AT+CMGF=1");
  delay(500);
  sim800.println("AT+CNMI=1,2,0,0,0");
  delay(500);
}


bool messageSent = false;
void loop()
{
  int msgSignal = 0;

  clientInfo *info;
  char message[100];

  receivePayment(message, sizeof(message), &msgSignal);
  
  if (msgSignal == 1)
  {  
    //Serial.println(message);
    info = parsePayment(String(message));
    Serial.print("\nName: "+info->clientName+ "\nPhone #: " +info->phoneNo + "\nAmt " + info->amt + "\n");
    messageSent = true;
    
    delete info;
  }

  delay(500);
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
