#ifndef IDFUNCTIONS_H
#define IDFUNCTIONS_H

namespace IDFunctions{
  typedef void (*sfunc)( void* );
  typedef void (*gfunc)( void* );
    
  static void S_ONBOARD_LED(void *val);
  static void G_ONBOARD_LED(void *val);
  
  static void S_LED_BLUE_FRONT(void *val);
  static void G_LED_BLUE_FRONT(void *val);

  static void S_RELAY_TL1(void *val);
  static void G_RELAY_TL1(void *val);

  static void S_RELAY_TL1(void *val);
  static void G_RELAY_TL1(void *val);
  
  static void S_DHT_TEMPERATURE(void *val);
  static void G_DHT_TEMPERATURE(void *val);
  
  static void S_DHT_HUMIDITY(void *val);
  static void G_DHT_HUMIDITY(void *val);
  
  static void S_DS18B20_TEMPERATURE(void *val);
  static void G_DS18B20_TEMPERATURE(void *val);

  static void S_PROBE_PH(void *val);
  static void G_PROBE_PH(void *val);

  //static processfunc ProcessFunctions[] = { Process01, Process02 };
}

#endif
