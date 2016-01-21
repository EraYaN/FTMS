using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace EraYaN.FTMS.PCController
{
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window
	{
        Communication com;
		public MainWindow()
		{
			InitializeComponent();
            com = new Communication("COM4", 115200);
            com.PacketReceivedEvent += Com_PacketReceivedEvent;            
        }

        private void Com_PacketReceivedEvent(object sender, PacketReceivedEventArgs e)
        {
            if (e.ReceivedPacket.Validate())
            {
               
                if (e.ReceivedPacket.Command == Command.Debug)
                {
                    Dispatcher.Invoke((Action)delegate ()
                    {
                        ConsoleTextBox.AppendText("Debug: ");
                        ConsoleTextBox.AppendText(Encoding.ASCII.GetString(e.ReceivedPacket.Data));
                        ConsoleTextBox.AppendText("\n");
                        ConsoleTextBox.ScrollToEnd();
                    });
                }
                else {
                    System.Diagnostics.Debug.WriteLine("Got well formed packet.");
                    Dispatcher.Invoke((Action)delegate ()
                    {
                        ConsoleTextBox.AppendText(e.ReceivedPacket.ToString());
                        ConsoleTextBox.AppendText("\n");
                        ConsoleTextBox.ScrollToEnd();
                    });
                    
                }
            }
            else {
                System.Diagnostics.Debug.WriteLine("Got bad packet.");
            }            
        }

        private void TestButton_Click(object sender, RoutedEventArgs e)
        {
            com.SetBoolean(ComVars.ONBOARD_LED, true);
        }

        private void TestButtonFalse_Click(object sender, RoutedEventArgs e)
        {
            com.SetBoolean(ComVars.ONBOARD_LED, false);
        }

        private void TestButtonInt16_Click(object sender, RoutedEventArgs e)
        {
            com.SetInteger16(ComVars.LED_BLUE_FRONT, (short)Math.Round(BlueLEDFrontSlider.Value));            
        }

        private void GetFloatTestButton_Click(object sender, RoutedEventArgs e)
        {
            com.GetFloat(ComVars.DHT_TEMPERATURE);
        }
    }
}
