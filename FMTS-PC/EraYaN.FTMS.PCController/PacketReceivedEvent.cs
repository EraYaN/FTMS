using System;
using System.IO.Ports;

namespace EraYaN.FTMS.PCController
{
    public class PacketReceivedEventArgs : EventArgs
    {
        public readonly Packet ReceivedPacket;
        public PacketReceivedEventArgs(Packet _ReceivedPacket)
        {
            ReceivedPacket = _ReceivedPacket;
        }
    }
}
