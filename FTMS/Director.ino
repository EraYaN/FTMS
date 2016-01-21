#include "Director.h"
#include "IDFunctions.h"

//Function Declarations for Director
/// <summary>
///	Constructor of the Director class.
/// </summary>
/// <param name="pid">ID of the program to run.</param>
Director::Director()
  : s_DHT11("Kast", ST_DHT11, DHT11_PIN),
    s_DS18B20("Water", 0, &oneWire),
    s_pHProbe()
{

}
/// <summary>
///	Constructor of the Director class. Run default program.
/// </summary>
/*Director::Director() {
  Director(0);
  }*/
void Director::Init() {
  //contruct
  s_pHProbe.Init();
  s_DHT11.Init();
  s_DS18B20.Init();
  //set Pin Modes
  for (int pin = 0; pin < pincount; pin++) {
    pinMode(pins[pin][0], pins[pin][1]);
    if (pins[pin][1] == OUTPUT) {
      if (digitalPinHasPWM(pins[pin][1])) {
        analogWrite(pins[pin][0], pins[pin][2]);
      } else {
        digitalWrite(pins[pin][0], pins[pin][2]);
      }
    }
  }
}
void Director::Tick() {
  //runs every "loop()"
  //Update Time
  //doTimeWork();
}
int Director::SpecialRoutine() {
  //Pause all and execute task. Like calibrating the pH-probe.
  return 0;
}

void Director::ProcessBoolean(bool setter, byte id, bool *val) {
  if (!setter) {
    val = new bool;
  }
  switch (id) {
    case ComVars::ONBOARD_LED:
      setter ? IDFunctions::S_ONBOARD_LED(val) : IDFunctions::G_ONBOARD_LED(val);
      break;
    default:
      return;
  }
  if (!setter) {
    com.SetBoolean(id, *val);
  }
}
void Director::ProcessInteger16(bool setter, byte id, int *val) {
  if (!setter) {
    val = new int;
  }
  switch (id) {
    case ComVars::LED_BLUE_FRONT:
      setter ? IDFunctions::S_LED_BLUE_FRONT(val) : IDFunctions::G_LED_BLUE_FRONT(val);
      break;
    default:
      return;
  }
  if (!setter) {
    com.SetInteger16(id, *val);
  }
}
void Director::ProcessInteger32(bool setter, byte id, long *val) {
  if (!setter) {
    val = new long;
  }
  switch (id) {
    /*case ComVars::LED_BLUE_FRONT:
      setter ? IDFunctions::S_ONBOARD_LED(val) : IDFunctions::G_ONBOARD_LED(val);
      break;*/
    default:
      return;
  }
  if (!setter) {
    com.SetInteger32(id, *val);
  }
}
void Director::ProcessFloat(bool setter, byte id, double *val) {
  if (!setter) {
    val = new double;
  }
  switch (id) {
    case ComVars::DHT_TEMPERATURE:
      setter ? IDFunctions::S_DHT_TEMPERATURE(val) : IDFunctions::G_DHT_TEMPERATURE(val);
      break;
    case ComVars::DHT_HUMIDITY:
      setter ? IDFunctions::S_DHT_HUMIDITY(val) : IDFunctions::G_DHT_HUMIDITY(val);
      break;
    case ComVars::DS18B20_TEMPERATURE:
      setter ? IDFunctions::S_DS18B20_TEMPERATURE(val) : IDFunctions::G_DS18B20_TEMPERATURE(val);
      break;
      case ComVars::PROBE_PH:
      setter ? IDFunctions::S_PROBE_PH(val) : IDFunctions::G_PROBE_PH(val);
      break;
    default:
      return;
  }
  if (!setter) {    
    com.SetFloat(id, *val);
  }
}
void Director::ProcessString(bool setter, byte id, String *val) {
  //TODO verify whenever necessary
  if (!setter) {
    val = new String;
  }
  switch (id) {
    /*case ComVars::LED_BLUE_FRONT:
      setter ? IDFunctions::S_ONBOARD_LED(val) : IDFunctions::G_ONBOARD_LED(val);
      break;*/
    default:
      return;
  }
  if (!setter) {
    com.SetString(id, *val);
  }
}

void Director::StartProgram() {
  //start the program.
  int errCode = 0;
  //update all sensor values
  //unsigned long t1 = millis();
  if ((errCode = s_DHT11.updateValue()) != 0) com.DebugMessage("E: DHT11 update error 0" + errCode);
  //unsigned long t2 = millis();
  if ((errCode = s_DS18B20.updateValue()) != 0) com.DebugMessage("E: DS18B20 update error 0" + errCode);
  // unsigned long t3 = millis();
  if ((errCode = s_pHProbe.updateValue(s_DS18B20.getTemperature())) != 0) com.DebugMessage("E: pHProbe update error 0" + errCode);
  //unsigned long t4 = millis();
  //draw screen
  frame();
  //Send sensor stuff to PC
  //com.SetInteger32(12, millis());
  //com.SetFloat(13, s_DHT11.getTemperature());
  //com.SetFloat(14, s_DS18B20.getTemperature());
  /*unsigned long t5 = millis();
    Serial.println("Sensors");
    Serial.println(t2-t1);
    Serial.println(t3-t2);
    Serial.println(t4-t3);
    Serial.println("Screen");
    Serial.println(t5-t4);
    Serial.println("Total");
    Serial.println(t5-t1);*/
}


