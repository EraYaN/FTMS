using EraYaN.Serial;
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

namespace FMTS_PC_Controller
{
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window
	{
		SerialInterface com = new SerialInterface("COM3",115200);
		public MainWindow()
		{
			InitializeComponent();
			com.SerialDataEvent += com_SerialDataEvent;
		}

		void com_SerialDataEvent(object sender, SerialDataEventArgs e)
		{
			System.Diagnostics.Debug.WriteLine(e.DataByte);
		}
	}
}
