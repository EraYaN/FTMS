using System;
using System.IO.Ports;

namespace EraYaN.Serial
{
    interface ISerial
    {
        event EventHandler<SerialDataEventArgs> SerialDataEvent;       
    }
}
