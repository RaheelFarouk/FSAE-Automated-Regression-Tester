// Receive all incoming CAN_BUS Coms through mcp 2515 chipset
#include <SPI.h>              //Library for using SPI Communication 
#include <mcp2515.h>          //Library for using CAN Communication (https://github.com/autowp/arduino-mcp2515/)

struct can_frame canMsg;
 
MCP2515 mcp2515(10);                 // SPI CS Pin 10
 
 
void setup()
{
  Serial.begin(115200);                //Begins Serial Communication at 115200 baudrate
  Serial.flush();
  SPI.begin();                       //Begins SPI communication
  Serial.println("CANBUS OUTPUT: ");
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS, MCP_8MHZ); //Sets CAN at speed 1000BPS and Clock 8MHz
  mcp2515.setNormalMode();                  //Sets CAN at normal mode
  Serial.println("ID   DlC   DATA");
  delay(3000);


  // setup pinmodes here
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(8, HIGH);
  }
 
void loop()
{
  recieveCANCommand();
  recieveMessage();
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
    Serial.println();
  }
  return;
}

void recieveCANCommand()
{
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) // To receive data (Poll Read)
  {
    Serial.print(canMsg.can_id);
    Serial.print("     ");
    Serial.print(canMsg.can_dlc);
    Serial.print("   ");
    if(canMsg.can_id == 0x001)
    {
      if(canMsg.data[0] = 0x00)
      {
        //set the pwm digital output to this value
        analogWrite(7, canMsg.data[1]);
        Serial.print("Requested Output for Channel 7: ");
        Serial.println(canMsg.data[1]);

        //set the pwm digital output to this value
        analogWrite(7, canMsg.data[2]);
        Serial.print("Requested Output for Channel 7: ");
        Serial.println(canMsg.data[2]);

        
      }
      

    }
    Serial.println();
  }
  return;
}
