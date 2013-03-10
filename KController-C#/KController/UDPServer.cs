/*!
 * \file UDPServer.cs
 * \author Sylvain Fay-Châtelard & Adrien Madouasse
 * \brief UDP communication with a FreeStroke to answer to the discover request
 * \date 2013-03-07
 */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Net.Sockets;

namespace KController
{
    /*!
     * \class UDPServer
     * \brief The UDP server to manage the Controller discover
     */
    class UDPServer
    {
        /*!< The multicast address */
        private System.Net.IPAddress multicastAddress = System.Net.IPAddress.Parse("224.11.2.13");
        /*!< The UDP socket */
        private UdpClient socket = null;
        /*!< The KController name sent to FreeStroke */
        private String name;
        /*!< The UDP port, default value = 47371 */
        private ushort udpPort;
        /*!< The TCP port, default value = 47371 */
        private ushort tcpPort;
        /*!< The state of the thread loop */
        private bool run = false;
        /*!< The thread for the UDP server */
        private Thread thread;

        /*!
         * \brief The constructor
         * \param name The name of the KController
         * \param port The UDP port on which the server listen
         * \param tcpPort The TCP port on which the server listen
         */
        public UDPServer(String name, ushort port, ushort tcpPort)
        {
            this.name = name;
            this.udpPort = port;
            this.tcpPort = tcpPort;
        }

        /*!
         * \brief Return if the UDP Server is currently started
         */
        public bool isRunning()
        {
            return run;
        }

        /*!
         * \brief Return the current UDP port
         */
        public ushort getPort()
        {
            return udpPort;
        }

        /*!
         * \brief Start the UDP server in a thread and restart it when there is an exception
         */
        public void setPort(ushort udpPort, ushort tcpPort)
        {
            this.udpPort = udpPort;
            this.tcpPort = tcpPort;
            if (run)
            {
                this.stop();
                this.start();
            }
        }

        /*!
         * \brief Change only TCP port to send to the client
         */
        public void setTCPPort(ushort tcpPort)
        {
            this.tcpPort = tcpPort;
        }

        /*!
         * \brief Change the name of the Controller
         */
        public void setName(string name)
        {
            this.name = name;
        }

        /*!
         * \brief Start the thread and the UDP server
         */
        public void start()
        {
            // Run the thread
            thread = new Thread(this.private_start);
            thread.Start();
        }

        /*!
         * \brief Start the UDP server
         */
        private void private_start()
        {
            try
            {
                run = true;
                socket = new UdpClient(udpPort);
                if (multicastAddress == null)
                {
                    return;
                }
                socket.JoinMulticastGroup(multicastAddress);
                System.Net.IPEndPoint from = new System.Net.IPEndPoint(System.Net.IPAddress.Any, 0);

                // Listening
                while (run)
                {
                    // Read
                    byte[] data = socket.Receive(ref from);
                    if (data.Length != 1 && data[0] != 0)
                    {
                        continue;
                    }

                    // Prepare the response
                    byte[] response = new byte[3 + name.Length + 1];
                    response[0] = 1;
                    response[1] = (byte)(tcpPort >> 8);
                    response[2] = (byte)tcpPort;
                    for (int i = 0; i < name.Length; i++)
                    {
                        response[i + 3] = (byte)name.ToCharArray()[i];
                    }
                    response[3 + name.Length] = 0;
                    socket.Send(response, 3 + name.Length  + 1, from);
                }
            }
            catch (System.Net.Sockets.SocketException e)
            {
                Console.WriteLine("UDP : System.Net.Sockets.SocketException " + e.Message);

                // Stop the UDP server
                stop();
            }
        }

        /*!
         * \brief Stop the UDP server
         */
        public void stop()
        {
            try
            {
                run = false;
                if (multicastAddress == null)
                {
                    socket.Close();
                    return;
                }
                socket.DropMulticastGroup(multicastAddress);
                socket.Close();
                thread.Abort();
            }
            catch (System.ObjectDisposedException e)
            {
                Console.WriteLine("UDP : System.ObjectDisposedException : " + e.Message);
            }
            catch (System.Net.Sockets.SocketException e)
            {
                Console.WriteLine("UDP : System.Net.Sockets.SocketException : " + e.Message);
            }
            catch (System.NullReferenceException e)
            {
                Console.WriteLine("UDP : System.NullReferenceException : " + e.Message);
            }
        }
    }
}
