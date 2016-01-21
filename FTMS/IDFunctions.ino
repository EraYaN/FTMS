#include "IDFunctions.h"

namespace IDFunctions {

void S_ONBOARD_LED(void *val) {
  digitalWrite(LED_ONBOARD, *reinterpret_cast<bool*>(val));
}
void G_ONBOARD_LED(void *val) {
  *reinterpret_cast<bool*>(val) = digitalRead(LED_ONBOARD);
}

void S_LED_BLUE_FRONT(void *val) {  
  analogWrite(LED_BLUE_FRONT, *reinterpret_cast<int*>(val));
}
void G_LED_BLUE_FRONT(void *val) {
  com.Forbidden(ComVars::ONBOARD_LED);
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
  bool tmp = digitalRead(RELAY_TL2);
  val = &tmp;
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
