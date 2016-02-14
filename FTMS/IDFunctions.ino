#include "IDFunctions.h"

namespace IDFunctions {

void S_ONBOARD_LED(void *val) {
  digitalWrite(LED_ONBOARD, *reinterpret_cast<bool*>(val));
}
void G_ONBOARD_LED(void *val) {
  *reinterpret_cast<bool*>(val) = digitalRead(LED_ONBOARD);
}
void S_RELAY_TL1(void *val) {
  digitalWrite(RELAY_TL1, (*reinterpret_cast<bool*>(val)));
}
void G_RELAY_TL1(void *val) {
  *reinterpret_cast<bool*>(val) = digitalRead(RELAY_TL1);
}
void S_RELAY_TL2(void *val) {
  digitalWrite(RELAY_TL2, (*reinterpret_cast<bool*>(val)));
}
void G_RELAY_TL2(void *val) {
  *reinterpret_cast<bool*>(val) = digitalRead(RELAY_TL2);
}
void S_RELAY_TL3(void *val) {
  digitalWrite(RELAY_TL3, (*reinterpret_cast<bool*>(val)));
}
void G_RELAY_TL3(void *val) {
  *reinterpret_cast<bool*>(val) = digitalRead(RELAY_TL3);
}
void S_RELAY_TL4(void *val) {
  digitalWrite(RELAY_TL4, (*reinterpret_cast<bool*>(val)));
}
void G_RELAY_TL4(void *val) {
  *reinterpret_cast<bool*>(val) = digitalRead(RELAY_TL4);
}
void S_RELAY_TL5(void *val) {
  digitalWrite(RELAY_TL5, (*reinterpret_cast<bool*>(val)));
}
void G_RELAY_TL5(void *val) {
  *reinterpret_cast<bool*>(val) = digitalRead(RELAY_TL5);
}
void S_RELAY_FLORAMATE(void *val) {
  digitalWrite(RELAY_FLORAMATE, (*reinterpret_cast<bool*>(val)));
}
void G_RELAY_FLORAMATE(void *val) {
  *reinterpret_cast<bool*>(val) = digitalRead(RELAY_FLORAMATE);
}
void S_RELAY_PUMP_MAIN1(void *val) {
  digitalWrite(RELAY_PUMP_MAIN1, (*reinterpret_cast<bool*>(val)));
}
void G_RELAY_PUMP_MAIN1(void *val) {
  *reinterpret_cast<bool*>(val) = digitalRead(RELAY_PUMP_MAIN1);
}
void S_RELAY_PUMP_MAIN2(void *val) {
  digitalWrite(RELAY_PUMP_MAIN2, (*reinterpret_cast<bool*>(val)));
}
void G_RELAY_PUMP_MAIN2(void *val) {
  *reinterpret_cast<bool*>(val) = digitalRead(RELAY_PUMP_MAIN2);
}
void S_RELAY_CO2(void *val) {
  digitalWrite(RELAY_CO2, (*reinterpret_cast<bool*>(val)));
}
void G_RELAY_CO2(void *val) {
  *reinterpret_cast<bool*>(val) = digitalRead(RELAY_CO2);
}
void S_RELAY_PUMP_CO2(void *val) {
  digitalWrite(RELAY_PUMP_CO2, (*reinterpret_cast<bool*>(val)));
}
void G_RELAY_PUMP_CO2(void *val) {
  *reinterpret_cast<bool*>(val) = digitalRead(RELAY_PUMP_CO2);
}
void S_RELAY_AIRPUMP(void *val) {
  digitalWrite(RELAY_AIRPUMP, (*reinterpret_cast<bool*>(val)));
}
void G_RELAY_AIRPUMP(void *val) {
  *reinterpret_cast<bool*>(val) = digitalRead(RELAY_AIRPUMP);
}
void S_RELAY_TERRA_LIGHT(void *val) {
  digitalWrite(RELAY_TERRA_LIGHT, (*reinterpret_cast<bool*>(val)));
}
void G_RELAY_TERRA_LIGHT(void *val) {
  *reinterpret_cast<bool*>(val) = digitalRead(RELAY_TERRA_LIGHT);
}
void S_RELAY_TERRA_HEAT(void *val) {
  digitalWrite(RELAY_TERRA_HEAT, (*reinterpret_cast<bool*>(val)));
}
void G_RELAY_TERRA_HEAT(void *val) {
  *reinterpret_cast<bool*>(val) = digitalRead(RELAY_TERRA_HEAT);
}
void S_RELAY_RESERVE1(void *val) {
  digitalWrite(RELAY_RESERVE1, (*reinterpret_cast<bool*>(val)));
}
void G_RELAY_RESERVE1(void *val) {
  *reinterpret_cast<bool*>(val) = digitalRead(RELAY_RESERVE1);
}
void S_RELAY_RESERVE2(void *val) {
  digitalWrite(RELAY_RESERVE2, (*reinterpret_cast<bool*>(val)));
}
void G_RELAY_RESERVE2(void *val) {
  *reinterpret_cast<bool*>(val) = digitalRead(RELAY_RESERVE2);
}
void S_RELAY_RESERVE3(void *val) {
  digitalWrite(RELAY_RESERVE1, (*reinterpret_cast<bool*>(val)));
}
void G_RELAY_RESERVE3(void *val) {
  *reinterpret_cast<bool*>(val) = digitalRead(RELAY_RESERVE3);
}

void S_LED_WHITE_FRONT(void *val) {  
  analogWrite(LED_WHITE_FRONT, *reinterpret_cast<int*>(val));
}
void G_LED_WHITE_FRONT(void *val) {
  com.Forbidden(ComVars::LED_WHITE_FRONT);
}
void S_LED_WHITE_REAR(void *val) {  
  analogWrite(LED_WHITE_REAR, *reinterpret_cast<int*>(val));
}
void G_LED_WHITE_REAR(void *val) {
  com.Forbidden(ComVars::LED_WHITE_REAR);
}
void S_LED_RED_FRONT(void *val) {  
  analogWrite(LED_RED_FRONT, *reinterpret_cast<int*>(val));
}
void G_LED_RED_FRONT(void *val) {
  com.Forbidden(ComVars::LED_RED_FRONT);
}
void S_LED_RED_REAR(void *val) {  
  analogWrite(LED_RED_REAR, *reinterpret_cast<int*>(val));
}
void G_LED_RED_REAR(void *val) {
  com.Forbidden(ComVars::LED_RED_REAR);
}
void S_LED_BLUE_FRONT(void *val) {  
  analogWrite(LED_BLUE_FRONT, *reinterpret_cast<int*>(val));
}
void G_LED_BLUE_FRONT(void *val) {
  com.Forbidden(ComVars::LED_BLUE_FRONT);
}
void S_LED_BLUE_REAR(void *val) {  
  analogWrite(LED_BLUE_REAR, *reinterpret_cast<int*>(val));
}
void G_LED_BLUE_REAR(void *val) {
  com.Forbidden(ComVars::LED_BLUE_REAR);
}
void S_FAN_SPEED(void *val) {  
  analogWrite(FAN_SPEED, *reinterpret_cast<int*>(val));
}
void G_FAN_SPEED(void *val) {
  com.Forbidden(ComVars::FAN_SPEED);
}


void S_DHT_TEMPERATURE(void *val) {
  com.Forbidden(ComVars::DHT_TEMPERATURE);
}
void G_DHT_TEMPERATURE(void *val) {
  *reinterpret_cast<double*>(val) = drctr.s_DHT11.getTemperature();
}

void S_DHT_HUMIDITY(void *val) {
  com.Forbidden(ComVars::DHT_HUMIDITY);
}
void G_DHT_HUMIDITY(void *val) {
  *reinterpret_cast<double*>(val) = drctr.s_DHT11.getHumidity();
}

void S_DS18B20_TEMPERATURE(void *val) {
  com.Forbidden(ComVars::DS18B20_TEMPERATURE);
}
void G_DS18B20_TEMPERATURE(void *val) {
  *reinterpret_cast<double*>(val) = drctr.s_DS18B20.getTemperature();
}

void S_PROBE_PH(void *val) {
  com.Forbidden(ComVars::PROBE_PH);
}
void G_PROBE_PH(void *val) {
  *reinterpret_cast<double*>(val) = drctr.s_pHProbe.getpH(); 
}

}
