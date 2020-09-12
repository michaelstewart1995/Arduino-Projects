// The Botler v0.3 - EEE527: Embedded Systems 28.11.17
// Aimee McCart - B00658830
// Michael Stewart - B00661765

#include <WiFi101.h> 
#include <SPI.h>  
#include <TelegramBot.h>  
 
// Initialize Wifi connection to the router  
char ssid[] = "MY WIFI 6539";             // network SSID (name)  
char pass[] = "";                         // network password is blank
// Initialize Telegram BOT  
const char* BotToken = "478849574:AAFc20JHakmfEIHNoVNd_cI-um5w9IOi3No";    // bot token to prevent unauthorised access
WiFiSSLClient client;
TelegramBot bot(BotToken,client);  
TelegramKeyboard botlerKeyboard;
const int ledPin = 6;  // the number of the LED pin  

void setup() 
{  //start of setup
 Serial.begin(115200);  
 while (!Serial) {}  //start running when the serial is open 
 delay(3000);  
 Serial.print("Connecting Wifi: ");  // attempt to connect to wifi network
 Serial.println(ssid);               // print ssid to serial monitor
 
 while (WiFi.begin(ssid) != WL_CONNECTED) //wait for wifi connection
 {  
   Serial.print(".");  
   delay(500);  
 }
 
 Serial.println("\nWiFi connected"); 
 
 // define your rows
 const char* row_one[] = {"Lights On", "Lights Off"};
 const char* row_two[] = {"Help", "Temperature"};

 // assing a row to one or more keyboards
 // second argument is the length of the row
 botlerKeyboard.addRow(row_one, 2);
 botlerKeyboard.addRow(row_two, 2); 
 bot.begin();  //begin bot
 pinMode(ledPin, OUTPUT); // configure pins
 pinMode(0, INPUT);

 analogReference(AR_DEFAULT); // set analog reference for temp sensor
 analogReadResolution(8);     // configure ADC to 8 bit
} // end of setup  

void loop() 
{
 int Qlevel; //initialise variables for temperature sensor
 float volt, temperature; //initialise voltage and temp variables

 Qlevel = analogRead(A0); //read quantiser level from pin A0
 volt = (Qlevel*3.3)/255; //convert quantiser level to voltage
 temperature = (volt-0.5)/0.01; //convert voltage to temperature
 String tempString = String(temperature); //convert temp float to string for bot api compatibility
 
 //Bot Interaction
 message m = bot.getUpdates();       // read new messages

 if (m.text.equals("Lights On"))     // lights on
  {  
   Serial.print("Message Received: ");  // print message to serial monitor
   Serial.println(m.text);
   digitalWrite(ledPin, HIGH);  
   bot.sendMessage(m.chat_id, "The lights are now ON"); 
  }  
 else if (m.text.equals("Lights Off")) // lights off
  {   
   Serial.print("Message Received: ");  
   Serial.println(m.text);
   digitalWrite(ledPin, LOW); 
   bot.sendMessage(m.chat_id, "The lights are now OFF");  
  }  
 else if (m.text.equals("Temperature")) //temperature
  {  
  Serial.print("Message Received: ");  // print message to serial monitor
  Serial.println(m.text);
  Serial.print("Voltage: "); // print measured voltage to serial
  Serial.print(volt);
  Serial.print("  Quantisation Level: "); //print measured q level to serial
  Serial.print(Qlevel);
  Serial.print("  Temperature: "); // print measured temperature to serial
  Serial.println(temperature);
  bot.sendMessage(m.chat_id, "The temperature is: ");  //send temperature to user
  bot.sendMessage(m.chat_id, tempString);
  } 
 else if (m.text.equals("Help")) // help function
  {
   Serial.print("Message Received: ");  // print message to serial monitor
   Serial.println(m.text);
   bot.sendMessage(m.chat_id, "Available Functions:");
   bot.sendMessage(m.chat_id, "Lights On: Turn the lights on \nLights Off: Turn the lights off \nTemperature: Display current room temperature");
  }
 else if (m.text.equals("Keyboard")) // help function
  {
   Serial.print("Message Received: ");  // print message to serial monitor
   Serial.println(m.text);
   bot.sendMessage(m.chat_id, "Please choose a command:", botlerKeyboard);  // Reply to the same chat with the same text
  }
  else 
  {
   Serial.print("Awaiting Message...");  // print message to serial monitor
   Serial.println(m.text);
   bot.sendMessage(m.chat_id, "Please choose a command:", botlerKeyboard);  // Reply to the same chat with the same text
  }
}


////Function Definitions
//
//void on(){
// 
//  }
//
//void off(){
//
//  }
//
//void help(){
//
//  }
//
//void tempGet(){
//  int temp();
//  }
