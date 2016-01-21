using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EraYaN.FTMS.PCController
{
    public static class ComVars
    {
        public const byte ONBOARD_LED = 1;
        public const byte RELAY_TL1 = 2;
        public const byte RELAY_TL2 = 3;
        //Int16s
        public const byte LED_BLUE_FRONT = 40;
        //Int32s
        //const byte ONBOARD_LED = 3;
        //Floats
        public const byte DHT_TEMPERATURE = 60;
        public const byte DHT_HUMIDITY = 61;
        public const byte DS18B20_TEMPERATURE = 62;
        public const byte PROBE_PH = 63;
    }
}
