using EraYaN.Serial;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EraYaN.FTMS.PCController
{

    public class Communication : IDisposable
    {
        public static readonly byte PROTOCOL_VERSION = 1;
        SerialInterface serial;
        string serialPort;
        int baudRate;
        public event EventHandler<PacketReceivedEventArgs> PacketReceivedEvent;

        bool isReceivingPacket = false;
        List<byte> packetBuffer;
        int expectedPacketLength = 4;

        public Communication(string SerialPort, int BaudRate)
        {
            serialPort = SerialPort;
            baudRate = BaudRate;
            serial = new SerialInterface(SerialPort, BaudRate);
            serial.SerialDataEvent += com_SerialDataEvent;
            if (serial.OpenPort() != 0)
            {
                System.Diagnostics.Debug.WriteLine(serial.lastError);
            }
        }

        void com_SerialDataEvent(object sender, SerialDataEventArgs e)
        {
            if (isReceivingPacket == false)
            {
                packetBuffer = new List<byte>();
                isReceivingPacket = true;
                expectedPacketLength = 4;
                if (e.Data == 0xF0)
                {
                    packetBuffer.Add(e.Data);
                }
                else {
                    isReceivingPacket = false;
                }
            }
            else {
                packetBuffer.Add(e.Data);
                if (packetBuffer.Count == 3)
                {
                    //command received
                    expectedPacketLength = ((Command)packetBuffer[2]).BasePacketLength();
                }
                if (packetBuffer.Count == 6)
                {

                    if (((Command)packetBuffer[2]).HasNData())
                    {
                        int datlen = (short)((packetBuffer[5] << 8) + packetBuffer[4]);
                        expectedPacketLength = 6 + datlen;
                    }
                }
            }

            if (isReceivingPacket)
            {
                if (packetBuffer.Count >= expectedPacketLength)
                {
                    try
                    {
                        PacketReceived(new Packet(packetBuffer.ToArray()));
                    }
                    catch (ArgumentException ex)
                    {
                        //Bad Packet, Discard
                        System.Diagnostics.Debug.WriteLine(ex);
                    }
                    isReceivingPacket = false;
                    packetBuffer.Clear();
                }

            }

        }

        public void SendPacket(Packet p)
        {
            if (serial.IsOpen && p.Validate())
            {
                serial.SendByteArray(p.ToByteArray());
            }
        }

        #region Protocol Methods
        public void OK()
        {
            Packet p = new Packet();
            p.Command = Command.OK;
            p.ID = 0;
            p.DataLength = 0;
            p.Data = new byte[0] { };
            SendPacket(p);
        }
        public void Reset()
        {
            Packet p = new Packet();
            p.Command = Command.Reset;
            p.ID = 0;
            p.DataLength = 0;
            p.Data = new byte[0] { };
            SendPacket(p);
        }
        public void Refresh()
        {
            Packet p = new Packet();
            p.Command = Command.Refresh;
            p.ID = 0;
            p.DataLength = 0;
            p.Data = new byte[0] { };
            SendPacket(p);
        }
        public void Forbidden(byte id)
        {
            Packet p = new Packet();
            p.Command = Command.Forbidden;
            p.ID = id;
            p.DataLength = 0;
            p.Data = new byte[0] { };
            SendPacket(p);
        }
        public void NotFound(byte id)
        {
            Packet p = new Packet();
            p.Command = Command.NotFound;
            p.ID = id;
            p.DataLength = 0;
            p.Data = new byte[0] { };
            SendPacket(p);
        }
        public void TypeMismatch(byte id)
        {
            Packet p = new Packet();
            p.Command = Command.TypeMismatch;
            p.ID = id;
            p.DataLength = 0;
            p.Data = new byte[0] { };
            SendPacket(p);
        }
        public void VersionUnsupported()
        {
            Packet p = new Packet();
            p.Command = Command.VersionUnsupported;
            p.ID = 0;
            p.DataLength = 1;
            p.Data = new byte[1] { PROTOCOL_VERSION };
            SendPacket(p);
        }
        public void Unsupported()
        {
            Packet p = new Packet();
            p.Command = Command.Unsupported;
            p.ID = 0;
            p.DataLength = 0;
            p.Data = new byte[0] { };
            SendPacket(p);
        }
        public void SetBoolean(byte id, bool val)
        {
            Packet p = new Packet();
            p.Command = Command.SetBoolean;
            p.ID = id;
            p.DataLength = sizeof(byte);
            p.Data = new byte[1] { (val ? (byte)1 : (byte)0) };
            SendPacket(p);

        }
        public void SetInteger16(byte id, short val)
        {
            Packet p = new Packet();
            p.Command = Command.SetInteger16;
            p.ID = id;
            p.DataLength = sizeof(short);
            p.Data = BitConverter.GetBytes(val);
            SendPacket(p);
        }
        public void SetInteger32(byte id, int val)
        {
            Packet p = new Packet();
            p.Command = Command.SetInteger32;
            p.ID = id;
            p.DataLength = sizeof(int);
            p.Data = BitConverter.GetBytes(val);
            SendPacket(p);
        }
        public void SetFloat(byte id, float val)
        {
            Packet p = new Packet();
            p.Command = Command.SetFloat;
            p.ID = id;
            p.DataLength = sizeof(float);
            p.Data = BitConverter.GetBytes(val);
            SendPacket(p);
        }
        public void SetString(byte id, string val)
        {
            byte[] str_b = Encoding.ASCII.GetBytes(val);
            Packet p = new Packet();
            p.Command = Command.SetString;
            p.ID = id;
            p.DataLength = (short)str_b.Length;
            p.Data = str_b;
            SendPacket(p);
        }
        public void GetBoolean(byte id)
        {
            Packet p = new Packet();
            p.Command = Command.GetBoolean;
            p.ID = id;
            p.DataLength = 0;
            p.Data = new byte[0] { };
            SendPacket(p);
        }
        public void GetInteger16(byte id)
        {
            Packet p = new Packet();
            p.Command = Command.GetInteger16;
            p.ID = id;
            p.DataLength = 0;
            p.Data = new byte[0] { };
            SendPacket(p);
        }
        public void GetInteger32(byte id)
        {
            Packet p = new Packet();
            p.Command = Command.GetInteger32;
            p.ID = id;
            p.DataLength = 0;
            p.Data = new byte[0] { };
            SendPacket(p);
        }
        public void GetFloat(byte id)
        {
            Packet p = new Packet();
            p.Command = Command.GetFloat;
            p.ID = id;
            p.DataLength = 0;
            p.Data = new byte[0] { };
            SendPacket(p);
        }
        public void GetString(byte id)
        {
            Packet p = new Packet();
            p.Command = Command.GetString;
            p.ID = id;
            p.DataLength = 0;
            p.Data = new byte[0] { };
            SendPacket(p);
        }
        public void DisplayString(byte id)
        {
            //TODO put duration in data.
            Packet p = new Packet();
            p.Command = Command.DisplayString;
            p.ID = id;
            p.DataLength = 0;
            p.Data = new byte[0] { };
            SendPacket(p);
        }
        public void Debug(string val)
        {
            byte[] str_b = Encoding.ASCII.GetBytes(val);
            Packet p = new Packet();
            p.Command = Command.Debug;
            p.ID = 0;
            p.DataLength = (short)str_b.Length;
            p.Data = str_b;
            SendPacket(p);
        }
        #endregion

        #region IDisposable members
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                // free managed resources
                if (serial != null)
                {
                    serial.Dispose();
                }
            }
        }
        #endregion

        #region Event members
        void PacketReceived(Packet p)
        {
            OnPacketReceived(new PacketReceivedEventArgs(p));
        }

        protected virtual void OnPacketReceived(PacketReceivedEventArgs e)
        {
            if (PacketReceivedEvent != null)
            {
                PacketReceivedEvent(this, e);
            }
        }
        #endregion
    }

}
