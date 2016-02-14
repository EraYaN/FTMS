#ifndef IDFUNCTIONS_H
#define IDFUNCTIONS_H

namespace IDFunctions {
//typedef void (*sfunc)( void* );
//typedef void (*gfunc)( void* );

static void S_ONBOARD_LED(void *val);
static void G_ONBOARD_LED(void *val);
static void S_RELAY_TL1(void *val);
static void G_RELAY_TL1(void *val);
static void S_RELAY_TL2(void *val);
static void G_RELAY_TL2(void *val);
static void S_RELAY_TL3(void *val);
static void G_RELAY_TL3(void *val);
static void S_RELAY_TL4(void *val);
static void G_RELAY_TL4(void *val);
static void S_RELAY_TL5(void *val);
static void G_RELAY_TL5(void *val);
static void S_RELAY_FLORAMATE(void *val);
static void G_RELAY_FLORAMATE(void *val);
static void S_RELAY_PUMP_MAIN1(void *val);
static void G_RELAY_PUMP_MAIN1(void *val);
static void S_RELAY_PUMP_MAIN2(void *val);
static void G_RELAY_PUMP_MAIN2(void *val);
static void S_RELAY_CO2(void *val);
static void G_RELAY_CO2(void *val);
static void S_RELAY_PUMP_CO2(void *val);
static void G_RELAY_PUMP_CO2(void *val);
static void S_RELAY_AIRPUMP(void *val);
static void G_RELAY_AIRPUMP(void *val);
static void S_RELAY_TERRA_LIGHT(void *val);
static void G_RELAY_TERRA_LIGHT(void *val);
static void S_RELAY_TERRA_HEAT(void *val);
static void G_RELAY_TERRA_HEAT(void *val);
static void S_RELAY_RESERVE1(void *val);
static void G_RELAY_RESERVE1(void *val);
static void S_RELAY_RESERVE2(void *val);
static void G_RELAY_RESERVE2(void *val);
static void S_RELAY_RESERVE3(void *val);
static void G_RELAY_RESERVE3(void *val);

static void S_LED_WHITE_FRONT(void *val);
static void G_LED_WHITE_FRONT(void *val);
static void S_LED_WHITE_REAR(void *val);
static void G_LED_WHITE_REAR(void *val);
static void S_LED_RED_FRONT(void *val);
static void G_LED_RED_FRONT(void *val);
static void S_LED_RED_REAR(void *val);
static void G_LED_RED_REAR(void *val);
static void S_LED_BLUE_FRONT(void *val);
static void G_LED_BLUE_FRONT(void *val);
static void S_LED_BLUE_REAR(void *val);
static void G_LED_BLUE_REAR(void *val);
static void S_FAN_SPEED(void *val);
static void G_FAN_SPEED(void *val);

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
