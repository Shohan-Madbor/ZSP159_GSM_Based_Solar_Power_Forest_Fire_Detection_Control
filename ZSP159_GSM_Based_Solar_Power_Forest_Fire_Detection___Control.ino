#include <dht.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27 , 16,2);
//LiquidCrystal_I2C lcd(0x3F , 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
#include <SoftwareSerial.h>
SoftwareSerial mySerial (2,3);
char msg;
char call;
String message;

int FLAME =4;
int buzzer = 5;
int motor = 6;

dht DHT;
#define DHT11_PIN A0
int chk = 0;
int fire= 0;
int smoke1=0;
long duration;

int distance;
void setup() {
  pinMode(buzzer, OUTPUT);
    pinMode(motor, OUTPUT);

 pinMode(FLAME, INPUT);       
Serial.begin(9600);
 mySerial.begin(9600);   // Setting the baud rate of GSM Module  
lcd.init();
lcd.backlight();
 lcd.begin(16,2);
  lcd.clear();
  
   mySerial.println("AT+CNMI=\"+88019********\"\r"); // Replace x with mobile number
     delay(1000);     
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
  
}
void loop() {
int chk = DHT.read11(DHT11_PIN);
 Serial.println(DHT.temperature); // AT Command to receive a live SMS

delay(1000);

   lcd.clear();

lcd.setCursor(8,0);
lcd.print("Temp");
lcd.setCursor(8,1);
lcd.print(DHT.temperature);          
lcd.setCursor(1,0);
lcd.print("Fire");
lcd.setCursor(1,1);
lcd.print("N.D" );
if( DHT.temperature > 38)
  {
          lcd.clear();
lcd.setCursor(0,0);
    lcd.print(".Temperature is.");
    lcd.setCursor(0,1);
    lcd.print("..Danger Zone..");
      SendMessage("Temperature is Danger Zone");

    digitalWrite(buzzer,HIGH);// set the buzzer ON
       delay(5000);
       digitalWrite(buzzer,LOW);// set the buzzer ON

  }
    if( DHT.temperature < 38)
  {
    digitalWrite(buzzer,LOW); // Set the buzzer OFF
  }
  
      int fire = digitalRead(FLAME);// read FLAME sensor

  if( fire ==LOW)
  {
          lcd.clear();
lcd.setCursor(0,0);
    lcd.print("Fire Detected");
      SendMessage("Fire Detected");
    digitalWrite(motor,HIGH);// set the buzzer ON
    digitalWrite(buzzer,HIGH);// set the buzzer ON
       delay(5000);
       digitalWrite(buzzer,LOW);// set the buzzer ON
       digitalWrite(motor,LOW);// set the buzzer ON

  }
    if( fire ==HIGH)
  {
           digitalWrite(motor,LOW);// set the buzzer O
    digitalWrite(buzzer,LOW); // Set the buzzer OFF
    Serial.println("Peace");
  }
 

  if (Serial.available()>0)
   switch(Serial.read())
  {
  
  }

}


void SendMessage(String thisIsAString )
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+88019*********\"\r"); // Replace x with mobile number
  delay(2000);
  mySerial.println(thisIsAString);// The SMS text you want to send
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  lcd.clear();



}
