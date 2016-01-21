using System;
using System.IO.Ports;

namespace EraYaN.Serial
{
    public class SerialDataEventArgs : EventArgs
    {
        public readonly byte Data;
        public SerialDataEventArgs(byte data)
        {
            Data = data;  
        }
    }
}
