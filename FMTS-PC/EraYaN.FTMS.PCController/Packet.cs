using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EraYaN.FTMS.PCController
{
    public class Packet
    {
        public byte Version;
        public Command Command;
        public byte ID;
        public short DataLength;
        public byte[] Data;
        public byte[] ToByteArray()
        {
            byte[] packed;
            if (DataLength == 0)
            {
                packed = new byte[4];
            }
            else {
                if (Command.HasNData())
                {
                    packed = new byte[6 + DataLength];
                }
                else {
                    packed = new byte[4 + DataLength];
                }
            }

            packed[0] = 0xF0;
            packed[1] = Version;
            packed[2] = (byte)Command;
            packed[3] = ID;

            if (DataLength > 0)
            {
                if (Command.HasNData())
                {
                    packed[4] = (byte)(0x00FF & DataLength);
                    packed[5] = (byte)((0xFF00 & DataLength) >> 4);
                    Buffer.BlockCopy(Data, 0, packed, 6, DataLength);
                }
                else {
                    Buffer.BlockCopy(Data, 0, packed, 4, DataLength);
                }
            }

            return packed;
        }

        public Packet()
        {
            Version = Communication.PROTOCOL_VERSION;
        }

        public Packet(byte[] PacketData)
        {
            //implement
            if (PacketData.Length < 4)
            {
                throw new ArgumentException("The data needs to be at least 4 bytes long, see the protocol specifications.", "data");
            }
            if (PacketData[0] != 0xF0)
            {
                throw new ArgumentException("Invalid data, start byte not found.", "data");
            }
            if (PacketData[1] > Communication.PROTOCOL_VERSION)
            {
                throw new ArgumentException("Invalid data, received protocol version unsupported.", "data");
            }
            Command = (Command)PacketData[2];
            ID = PacketData[3];
            if (Command.HasNData())
            {
                if (PacketData.Length == 5)
                {
                    throw new ArgumentException("Invalid data, invalid data length (5).", "data");
                }
                if (PacketData.Length == 6 && (PacketData[4] != 0 && PacketData[5] != 0))
                {
                    throw new ArgumentException("Invalid data, invalid data length, data was truncated.", "data");
                }
                if (PacketData.Length > 4)
                {
                    DataLength = (short)((PacketData[5] << 8) + PacketData[4]);
                    if (PacketData.Length < 6 + DataLength)
                    {
                        throw new ArgumentException("Invalid data, invalid data length, data was truncated.", "data");
                    }
                    if (PacketData.Length > 6 + DataLength)
                    {
                        throw new ArgumentException("Invalid data, invalid data length, data was too long, unsafe.", "data");
                    }
                    Data = new byte[DataLength];
                    Buffer.BlockCopy(PacketData, 6, Data, 0, DataLength);
                }
            }
            else {
                DataLength = (short)(Command.BasePacketLength() - 4);
                Data = new byte[DataLength];
                Buffer.BlockCopy(PacketData, 4, Data, 0, DataLength);
            }
        }

        public bool Validate()
        {
            switch (Command)
            {
                case Command.OK:
                case Command.Reset:
                case Command.Refresh:
                case Command.Unsupported:
                    //no data, no id
                    if (DataLength != 0 || ID != 0)
                    {
                        return false;
                    }
                    break;
                case Command.Forbidden:
                case Command.NotFound:
                case Command.TypeMismatch:
                case Command.DisplayString:
                case Command.GetInteger16:
                case Command.GetInteger32:
                case Command.GetBoolean:
                case Command.GetFloat:
                case Command.GetString:
                    //no data, id
                    if (DataLength != 0 || ID == 0)
                    {
                        return false;
                    }
                    break;
                case Command.VersionUnsupported:
                    //1 byte data, id
                    if (DataLength != 1 || ID == 0)
                    {
                        return false;
                    }
                    break;
                case Command.SetInteger16:
                    //2 byte int data, id
                    if (DataLength != 2 || ID == 0)
                    {
                        return false;
                    }
                    break;
                case Command.SetInteger32:
                    //4 byte int data, id
                    if (DataLength != 4 || ID == 0)
                    {
                        return false;
                    }
                    break;
                case Command.SetBoolean:
                    //1 byte boolean data, id
                    if (DataLength != 1 || ID == 0 || (Data[0] != 0 && Data[0] != 1))
                    {
                        return false;
                    }
                    break;
                case Command.SetFloat:
                    //4 byte int data, id
                    if (DataLength != 4 || ID == 0)
                    {
                        return false;
                    }
                    break;
                case Command.SetString:
                    //n byte string data, id
                    if (DataLength == 0 || ID == 0 || Data.Length != DataLength)
                    {
                        return false;
                    }
                    break;
                case Command.Debug:
                    //n byte string data, no id
                    if (DataLength == 0 || ID != 0 || Data.Length != DataLength)
                    {
                        return false;
                    }
                    break;
                default:
                    return false;
            }
            return true;
        }
        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendFormat("Packet v{0}: {1}\n", Version, Command.ToString());
            sb.AppendFormat("ID: {0}\n", ID);
            switch (Command)
            {
                case Command.OK:
                case Command.Reset:
                case Command.Refresh:
                case Command.Unsupported:
                case Command.Forbidden:
                case Command.NotFound:
                case Command.TypeMismatch:
                case Command.DisplayString:
                case Command.GetInteger16:
                case Command.GetInteger32:
                case Command.GetBoolean:
                case Command.GetFloat:
                case Command.GetString:
                    sb.Append("No Data\n");
                    break;
                case Command.VersionUnsupported:
                    sb.AppendFormat("Last version supported: {0}\n", Data[0]);
                    break;
                case Command.SetBoolean:
                    sb.AppendFormat("Boolean: {0}\n", BitConverter.ToBoolean(Data, 0));
                    break;
                case Command.SetInteger16:
                    sb.AppendFormat("Integer16: {0}\n", BitConverter.ToInt16(Data, 0));
                    break;
                case Command.SetInteger32:
                    sb.AppendFormat("Integer32: {0}\n", BitConverter.ToInt32(Data, 0));
                    break;
                case Command.SetFloat:
                    sb.AppendFormat("Float: {0}\n", BitConverter.ToSingle(Data, 0));
                    break;
                case Command.SetString:
                case Command.Debug:
                    sb.AppendFormat("Data Length: {0}\n", DataLength);
                    sb.AppendFormat("Data: {0}\n", Encoding.ASCII.GetString(Data));
                    break;
                default:
                    sb.Append("Unknown Command\n");
                    break;
            }
            return sb.ToString();
        }
    }
}
