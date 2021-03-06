#ifndef COMMUNICATION_H
#define COMMUNICATION_H
/*Define shit here*/

enum Command : byte
{
  //Control codes
  OK = 0xF0,
  Reset = 0xF1,
  Refresh = 0xF2,
  Forbidden = 0xF3,
  NotFound = 0xF4,
  TypeMismatch = 0xF5,
  VersionUnsupported = 0xFE,
  Unsupported = 0xFF,
  //Int16 commands
  SetInteger16 = 0x13,
  GetInteger16 = 0x15,
  //Int32 commands
  SetInteger32 = 0x23,
  GetInteger32 = 0x25,
  //Boolean commands
  SetBoolean = 0x33,
  GetBoolean = 0x35,
  //Float commands
  SetFloat = 0x43,
  GetFloat = 0x45,
  //String commands
  SetString = 0x53,
  GetString = 0x55,
  //Function commands
  DisplayString = 0xE5,
  Debug = 0xE6
};

namespace ComVars
{
//Booleans
const byte ONBOARD_LED = 1;
const byte RELAY_TL1 = 2;
const byte RELAY_TL2 = 3;
const byte RELAY_TL3 = 4; // White  (Philips 840)   4000K,    All-day.
const byte RELAY_TL4 = 5; // W-White (Philips 830)    3000K,    All-day.
const byte RELAY_TL5 = 6; // White,    Mid-day peak.
const byte RELAY_FLORAMATE = 7;
const byte RELAY_PUMP_MAIN1 = 8;
const byte RELAY_PUMP_MAIN2 = 9;
const byte RELAY_CO2 = 10;
const byte RELAY_PUMP_CO2 = 11;
const byte RELAY_AIRPUMP = 12;
const byte RELAY_TERRA_LIGHT = 13;
const byte RELAY_TERRA_HEAT = 14;
const byte RELAY_RESERVE1 = 15;
const byte RELAY_RESERVE2 = 16;
const byte RELAY_RESERVE3 = 17;
//Int16s
const byte LED_WHITE_FRONT = 40; //LEDPWM1
const byte LED_WHITE_REAR = 41; //LEDPWM2
const byte LED_RED_FRONT = 42; //LEDPWM3
const byte LED_RED_REAR = 43; //LEDPWM4
const byte LED_BLUE_FRONT = 44; //LEDPWM5
const byte LED_BLUE_REAR = 45; //LEDPWM6
const byte FAN_SPEED = 46;
//Int32s
//const byte ONBOARD_LED = 3;
//Floats
const byte DHT_TEMPERATURE = 60;
const byte DHT_HUMIDITY = 61;
const byte DS18B20_TEMPERATURE = 62;
const byte PROBE_PH = 63;
}


/// <summary>
///  Class that will handle all communication
/// </summary>
class Communication {
    //Class discription
    bool isReceivingPacket = false;
    int currentPacketByte = 0;
    int expectedPacketLength = 4;
    byte version;
    Command cmd;
    byte ID;
    byte* data;
    int datalen;
    byte temp;
    int iterations = 0;
  public:
    const byte PROTOCOL_VERSION = 1;
    const int MAX_ITERATIONS = 100;
    Communication();
    void Init();
    void CheckForData();
    //Protocol Methods
    void OK();
    void Reset();
    void Refresh();
    void Forbidden(byte id);
    void NotFound(byte id);
    void TypeMismatch(byte id);
    void VersionUnsupported();
    void Unsupported();
    void SetBoolean(byte id, bool val);
    void SetInteger16(byte id, int val);
    void SetInteger32(byte id, long val);
    void SetFloat(byte id, double val);
    void SetString(byte id, String val);
    void GetBoolean(byte id);
    void GetInteger16(byte id);
    void GetInteger32(byte id);
    void GetFloat(byte id);
    void GetString(byte id);
    void DebugMessage(String msg);
    void DebugMessage(const char* format, ...);
    
  private:
    int BasePacketLength(Command cmd);
    bool HasNData(Command cmd);
    void HandlePacket();
    void ResetCurrentPacket();
};

#endif
