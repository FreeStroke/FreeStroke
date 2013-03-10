/*!
 * \file KController.cs
 * \author Sylvain Fay-Châtelard & Adrien Madouasse
 * \brief The controller, entrance of the application, initialize GUI
 * \date 2013-03-07
 */
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.IO;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace KController
{
    /*!
     * \class KController
     * \brief Entrance of the application
     */
    public partial class KController : Form
    {
        /*!< The default name of the KController */
        private const String defaultName = "KController";
        /*!< The default UDP port */
        private const ushort defaultUdpPort = 47371;
        /*!< The default TCP port */
        private const ushort defaultTcpPort = 47371;
        /*!< The Kinect sensor */
        private Kinect kinect;
        /*!< The TCP server */
        private TCPServer tcpServer;
        /*!< The UDP server */
        private UDPServer udpServer;

        /*!
         * \brief enum for the state of the Kinect and TCP connection
         */
        public enum KinectState {
            DISCONNECTED,
            WAITING,
            CONNECTED
        };

        /*!
         * \brief The constructor
         */
        public KController()
        {
            InitializeComponent();

            String name;
            ushort udpPort;
            ushort tcpPort;

            // The folder path
            String pathLocalApp = System.Environment.GetFolderPath(System.Environment.SpecialFolder.LocalApplicationData)
                + @"\FreeSoft\KController\config.txt";
            try
            {
                // Load the configuration
                StreamReader reader = new StreamReader(pathLocalApp);
                name = reader.ReadLine();
                udpPort = System.UInt16.Parse(reader.ReadLine());
                tcpPort = System.UInt16.Parse(reader.ReadLine());
                reader.Close();
            }
            catch (System.IO.DirectoryNotFoundException e)
            {
                Console.Write("System.IO.DirectoryNotFoundException" + e.Message);
                name = defaultName;
                udpPort = defaultUdpPort;
                tcpPort = defaultTcpPort;
            }
            catch (System.IO.FileNotFoundException e)
            {
                Console.Write("System.IO.DirectoryNotFoundException" + e.Message);
                name = defaultName;
                udpPort = defaultUdpPort;
                tcpPort = defaultTcpPort;
            }

            // Put values in text fields
            txtBoxName.Text = name;
            txtBoxUDP.Text = udpPort.ToString();
            txtBoxTCP.Text = tcpPort.ToString();

            // Initiliaze servers and kinect
            udpServer = new UDPServer(name, udpPort, tcpPort);
            tcpServer = new TCPServer(this, udpServer, tcpPort);
            kinect = new Kinect(this, tcpServer);

            // Start Kinect and servers
            if (kinect.start())
            {
                this.changeState(KinectState.WAITING);
            }
            tcpServer.start();
            udpServer.start();
        }

        /*!
         * \brief Change the state of the Kinect, update the picture in the GUI
         * \param state The new state
         */
        public void changeState(KinectState state)
        {
            switch (state)
            {
                case KinectState.DISCONNECTED:
                    picState.Image = global::KController.Properties.Resources.state_red;
                    break;
                case KinectState.WAITING:
                    picState.Image = global::KController.Properties.Resources.state_orange;
                    break;
                case KinectState.CONNECTED:
                    picState.Image = global::KController.Properties.Resources.state_green;
                    break;
            }
        }

        /*!
         * \brief Manage closing of the application, close the UDP server, TCP server and the kinect
         * \param sender Which send the message
         * \param e The event
         */
        private void KController_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (udpServer != null)
            {
                udpServer.stop();
            }
            if (tcpServer != null)
            {
                tcpServer.stop();
            }
            if (kinect != null)
            {
                kinect.stop();
            }
        }

        /*!
         * \brief Intercept the click on the 'Apply' button, update the name, the UDP port and the TCP port
         * \param sender Which send the message
         * \param e The event
         */
        private void btnApply_Click(object sender, EventArgs e)
        {
            if (txtBoxName.Text != "")
            {
                udpServer.setName(txtBoxName.Text);
            }
            else
            {
                txtBoxName.Text = defaultName;
            }

            if (txtBoxTCP.Text != "")
            {
                ushort tcp = System.UInt16.Parse(txtBoxTCP.Text);
                if (tcp != tcpServer.getPort())
                {
                    tcpServer.setPort(tcp);
                    udpServer.setTCPPort(tcp);
                }
            }
            else
            {
                txtBoxTCP.Text = defaultTcpPort.ToString();
            }

            if (txtBoxUDP.Text != "")
            {
                ushort udp = System.UInt16.Parse(txtBoxUDP.Text);
                if (udp != udpServer.getPort())
                {
                    udpServer.setPort(udp, tcpServer.getPort());
                }
            }
            else
            {
                txtBoxUDP.Text = defaultUdpPort.ToString();
            }

            // The folder path
            String pathLocalApp = System.Environment.GetFolderPath(System.Environment.SpecialFolder.LocalApplicationData)
                + @"\FreeSoft\KController";

            // Create directory if not exists
            System.IO.Directory.CreateDirectory(pathLocalApp);

            // Write in the configuration file
            StreamWriter sw = new StreamWriter(pathLocalApp + @"\config.txt");
            sw.WriteLine(txtBoxName.Text);
            sw.WriteLine(txtBoxUDP.Text);
            sw.WriteLine(txtBoxTCP.Text);
            sw.Close();
        }
    }
}
