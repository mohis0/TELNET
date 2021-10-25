#include <Arduino.h>
#include <RemoteDebug.h>
#include <ESP8266WiFi.h>

String SSID = "mohsen" , PASS = "m1111111";
RemoteDebug Debug;

void telnetSetup()
{
    Debug.begin("TELNET");
    Debug.showColors(true);
    Debug.setResetCmdEnabled(true);
    Debug.setSerialEnabled(true);
    Debug.getTelnetClient();
    Debug.showTime(true);
    Debug.showDebugLevel(true);
}
void telnetCommands() //you can define commands and callback functions here for Telnet console
{
  if(Debug.getLastCommand()== "test") // "test" is a command //if we type test in Telnet and press enter , this if will excute
  {
    delay(2000);
    Debug.println("connection is valid");
    Debug.clearLastCommand(); //you must put this line in every callback function , if you dont that callback function will run until you send a new command
  }
}

void wifiConnect()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID.c_str(), PASS.c_str()); //start connecting to wifi
  Serial.println();
  Serial.print("connecting to wifi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("connected successfuly");
  return;
}

void setup() {
  // put your setup code here, to run once:
  wifiConnect();
  telnetSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  telnetCommands();
  Debug.handle();
}