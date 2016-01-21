using System;
using System.IO;
using System.IO.Ports;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace EraYaN.Serial
{
    public class SerialInterface : ISerial, IDisposable
    {
        const int blockLimit = 256;
        Action kickoffRead = null;
        string port;
        int baudrate;
        SerialPort serialPort;
        public string lastError = "";
        public event EventHandler<SerialDataEventArgs> SerialDataEvent;
        public bool IsOpen
        {
            get
            {
                return serialPort.IsOpen;
            }
        }
        public int BytesInTBuffer
        {
            get
            {
                return serialPort.BytesToWrite;
            }
        }
        public int BytesInRBuffer
        {
            get
            {
                return serialPort.BytesToRead;
            }
        }
        public SerialInterface(string _port, int _baudrate)
        {
            port = _port;
            baudrate = _baudrate;
            serialPort = new SerialPort();
            serialPort.PortName = port;
            serialPort.BaudRate = baudrate;
            serialPort.Parity = Parity.None;
            serialPort.DataBits = 8;
            serialPort.StopBits = StopBits.One;
            serialPort.Handshake = Handshake.None;
            serialPort.ReceivedBytesThreshold = 1;
            serialPort.ReadTimeout = 500;
            serialPort.WriteTimeout = 500;
            //serialPort.DataReceived += serialPort_DataReceived;
            serialPort.ErrorReceived += serialPort_ErrorReceived;
            serialPort.PinChanged += serialPort_PinChanged;
            
        }
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
                if (serialPort != null)
                {
                    serialPort.Close();
                    serialPort.Dispose();
                }
            }            
        }

        public int OpenPort()
        {
            try
            {
                serialPort.Open();
                byte[] buffer = new byte[blockLimit];                
                kickoffRead = delegate {
                    serialPort.BaseStream.BeginRead(buffer, 0, buffer.Length, delegate (IAsyncResult ar) {
                        try
                        {
                            int actualLength = serialPort.BaseStream.EndRead(ar);
                            byte[] received = new byte[actualLength];
                            Buffer.BlockCopy(buffer, 0, received, 0, actualLength);
                            handleSerialData(received);
                        }
                        catch (IOException exc)
                        {
                            //handleAppSerialError(exc);
                        }
                        kickoffRead();
                    }, null);
                };
                kickoffRead();
                return 0;
            }
            catch (IOException e)
            {
                //MessageBox.Show("SerialInterface Error:\n" + e.Message, "SerialInterface Error", MessageBoxButton.OK, MessageBoxImage.Error);
                lastError = e.Message;
                return -1;
            }
            catch (ArgumentException e)
            {
                //MessageBox.Show("SerialInterface Error:\n" + e.Message, "SerialInterface Error", MessageBoxButton.OK, MessageBoxImage.Error);
                lastError = e.Message;
                return -2;
            }
            catch (InvalidOperationException e)
            {
                //MessageBox.Show("SerialInterface Error:\n" + e.Message, "SerialInterface Error", MessageBoxButton.OK, MessageBoxImage.Error);
                lastError = e.Message;
                return -3;
            }
            catch (UnauthorizedAccessException e)
            {
                //MessageBox.Show("SerialInterface Error:\n" + e.Message, "SerialInterface Error", MessageBoxButton.OK, MessageBoxImage.Error);
                lastError = e.Message;
                return -4;
            }
            catch (Exception e)
            {
                //MessageBox.Show("SerialInterface Error:\n" + e.Message, "SerialInterface Error", MessageBoxButton.OK, MessageBoxImage.Error);
                lastError = e.Message;
                return 1;
            }
        }
        public void SendString(string data)
        {
            serialPort.WriteLine(data);
        }
        public void SendByteArray(byte[] data)
        {
            serialPort.Write(data, 0, data.Length);
        }
        public void SendByte(byte data)
        {
            byte[] buf = {data};
            serialPort.Write(buf,0,1);
        }
        void serialPort_PinChanged(object sender, SerialPinChangedEventArgs e)
        {
            serialPort.Close();
            serialPort.Open();
        }

        void serialPort_ErrorReceived(object sender, SerialErrorReceivedEventArgs e)
        {            
            //MessageBox.Show();
            throw new NotImplementedException();
        }

        /*void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            int input = serialPort.ReadByte();
            DataSerial((byte)input, e);           
        }*/

        void handleSerialData(byte[] data)
        {
            foreach (byte b in data)
            {
                DataSerial(b);
            }
        }
    
        void DataSerial(byte b)
        {
            OnSerialDataChanged(new SerialDataEventArgs(b));
        }

        protected virtual void OnSerialDataChanged(SerialDataEventArgs e)
        {
            if (SerialDataEvent != null)
            {
                SerialDataEvent(this, e);
            }
        }
    }
}
