//  EEE305 - Microcontroller Systems
//  
//  Coursework 3 - C Programming Project
//
//  Michael Stewart & Aimee McCart
//
//  Temperature sensor based alarm with servo mapped analog display
//
//  This program will read the ambient room temperature using a temperature sensor
//  It will then take this temperature and map it to a servo motor to display on a temperature dial
//  If the temperature exceeds 30 degrees C the system will sound an alarm and light an LED


#include <Servo.h> //initiating servo library
#include <LiquidCrystal.h> //initiating Liquid Crystal library
Servo myServo; //initiating servo motor
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //defining lcd pins for library

const int sensorPin = A1; //setting temperature sensor input to A1
const int baselineTemp = 20.0; //setting baseline room temperature
int const potPin = A0; //setting potentiometer pin to A0

//Potentiometer can be interchanged with temperature sensor for quick testing of servo setup

int potVal; //initiating potVal variable
int angle; //initiating angle variable


void setup() {
  // put your setup code here, to run once:

myServo.attach(9); //attaching servo to digital pin 9
Serial.begin(9600); //begin serial monitor
lcd.begin(16, 2); //begin lcd output

lcd.clear();
delay(200);
lcd.print("Temp Sensor");
lcd.setCursor(0, 1);
lcd.print("EEE305 Project");
delay(2000);

lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Aimee McCart");
lcd.setCursor(0, 1);
lcd.print("Michael Stewart");
delay(2000);
lcd.clear();
delay(200);
}

void loop() {

int sensorVal = analogRead(sensorPin); //reading the temperature sensor value between 0 and 1024

Serial.print("Sensor Value: "); //printing raw sensor value
Serial.print(sensorVal);

float voltage = (sensorVal/1024.0) * 5.0; //converting sensor value to voltage and printing to serial
Serial.print(", Volts: ");
Serial.print(voltage);

float temperature = (voltage - .5) *100; //converting voltage to temperature and printing to serial monitor
Serial.print(", degrees C: "); 
Serial.print(temperature);


potVal = analogRead(potPin); //setting potVal to potentiometer value
Serial.print(" potVal: "); //printing potentiometer value to serial monitor
Serial.print(potVal);

  angle = map(sensorVal, 120, 170, 0, 177); //mapping potentiometer value to servo angle
  Serial.print(" Angle: "); //printing servo angle to serial monitor
  Serial.println(angle);

myServo.write(angle); //sending servo angle to servo using servo library

lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Temperature:");

lcd.setCursor(0, 1);
lcd.print(temperature);
lcd.print(" degrees C");

delay(200);
}
