using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EraYaN.FTMS.PCController
{
    public static class ComVars
    {
		//Booleans
        public const byte ONBOARD_LED = 1;
        public const byte RELAY_TL1 = 2;
        public const byte RELAY_TL2 = 3;
		public const byte RELAY_TL3 = 4; // White  (Philips 840)   4000K,    All-day.
		public const byte RELAY_TL4 = 5; // W-White (Philips 830)    3000K,    All-day.
		public const byte RELAY_TL5 = 6; // White,    Mid-day peak.
		public const byte RELAY_FLORAMATE = 7;
		public const byte RELAY_PUMP_MAIN1 = 8;
		public const byte RELAY_PUMP_MAIN2 = 9;
		public const byte RELAY_CO2 = 10;
		public const byte RELAY_PUMP_CO2 = 11;
		public const byte RELAY_AIRPUMP = 12;
		public const byte RELAY_TERRA_LIGHT = 13;
		public const byte RELAY_TERRA_HEAT = 14;
		public const byte RELAY_RESERVE1 = 15;
		public const byte RELAY_RESERVE2 = 16;
		public const byte RELAY_RESERVE3 = 17;
		//Int16s
		public const byte LED_WHITE_FRONT = 40; //LEDPWM1
		public const byte LED_WHITE_REAR = 41; //LEDPWM2
		public const byte LED_RED_FRONT = 42; //LEDPWM3
		public const byte LED_RED_REAR = 43; //LEDPWM4
		public const byte LED_BLUE_FRONT = 44; //LEDPWM5
		public const byte LED_BLUE_REAR = 45; //LEDPWM6
		public const byte FAN_SPEED = 46;
		//Int32s
		//const byte ONBOARD_LED = 3;
		//Floats
		public const byte DHT_TEMPERATURE = 60;
		public const byte DHT_HUMIDITY = 61;
		public const byte DS18B20_TEMPERATURE = 62;
		public const byte PROBE_PH = 63;        
    }
}
