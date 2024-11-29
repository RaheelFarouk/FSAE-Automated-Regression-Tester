// Receive all incoming CAN_BUS Coms through mcp 2515 chipset
#include <SPI.h>              //Library for using SPI Communication 
#include <mcp2515.h>          //Library for using CAN Communication (https://github.com/autowp/arduino-mcp2515/)

#include <FastLED.h>
#define NUM_LEDS 1
#define DATA_PIN 29
#define CLOCK_PIN 13
CRGB leds[NUM_LEDS];

struct can_frame canMsg;
 
MCP2515 mcp2515(53);                 // SPI CS Pin 53
 
 
void setup()
{
    //start debug LED
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  //Turn off LED
  setDebugColour(CRGB::Black);

  Serial.begin(9600);                //Begins Serial Communication at 115200 baudrate
  Serial.flush();
  SPI.begin();                       //Begins SPI communication
  Serial.println("CANBUS OUTPUT: ");
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS, MCP_8MHZ); //Sets CAN at speed 1000BPS and Clock 8MHz
  mcp2515.setNormalMode();                  //Sets CAN at normal mode
  Serial.println("ID   DlC   DATA");
  setDebugColour(CRGB::Purple);
  delay(3000);

  // setup pinmodes here
  setupOutputs();
  
  setDebugColour(CRGB::Green);
  FastLED.setBrightness(20);
  delay(500);
  }
 
void loop()
{
  recieveCANCommand();
  // recieveMessage();
}

void recieveMessage(){
  // Serial.println(mcp2515.readMessage(&canMsg));
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) // To receive data (Poll Read)
  {
    Serial.print(canMsg.can_id);
    Serial.print("     ");
    Serial.print(canMsg.can_dlc);
    Serial.print("   ");
    for(int i = 0; i<canMsg.can_dlc; i++){ //go through all the data points using the dlc(length output recieved on line 30) to print out all the data points
      Serial.print(canMsg.data[i]);
      Serial.print("  ");
    }
    // Serial.println();
  }
  return;
}

void recieveCANCommand()
{
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) // To receive data (Poll Read)
  {
    // Serial.print(canMsg.can_id);
    // Serial.print("     ");
    // Serial.print(canMsg.can_dlc);
    // Serial.print("   ");
    if(canMsg.can_id == 0x001)
    {
      setDebugColour(CRGB::Green);
      Serial.print("Got Mux ID: "); Serial.println(canMsg.data[0]);
      if(canMsg.data[0] == 0x00)
      {
        setOutput(2, canMsg.data[1]);
        setOutput(3, canMsg.data[2]);
        setOutput(4, canMsg.data[3]);
        setOutput(5, canMsg.data[4]);
        setOutput(6, canMsg.data[5]);
        setOutput(7, canMsg.data[6]);
      }
      else if(canMsg.data[0] == 0x01)
      {
        setOutput(8, canMsg.data[1]);
        setOutput(9, canMsg.data[2]);
        setOutput(10, canMsg.data[3]);
        setOutput(11, canMsg.data[4]);
        setOutput(12, canMsg.data[5]);
        setOutput(13, canMsg.data[6]);
      }
      else if(canMsg.data[0] == 0x02)
      {
        setOutput(44, canMsg.data[1]);
        setOutput(45, canMsg.data[2]);
        setOutput(46, canMsg.data[3]);
      }
      setDebugColour(CRGB::Black);
    }
    Serial.println();
  }
  else if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_FAIL)
  {
    setDebugColour(CRGB::Red);
  }
  else if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_ALLTXBUSY)
  {
    setDebugColour(CRGB::Pink);
  }
  else if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_FAILINIT)
  {
    setDebugColour(CRGB::MediumVioletRed);
  }
  else if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_FAILTX)
  {
    setDebugColour(CRGB::Orange);
  }
  else if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_NOMSG)
  {
    setDebugColour(CRGB::Olive);
  }
  
  return;
}

void setOutput(int pin, int value)
{
  analogWrite(pin, value);
  Serial.print("Requested Output for Pin");
  Serial.print(pin);
  Serial.print(": ");
  Serial.println(value);
}

void setupOutputs()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(45, OUTPUT);
  pinMode(46, OUTPUT);
}

void setDebugColour(CRGB::HTMLColorCode code)
{
  leds[0] = code;
  FastLED.show();
}