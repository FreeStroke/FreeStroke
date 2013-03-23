/*
 * Projet de fin d'études LastProject de
 * Adrien Broussolle
 * Camille Darcy
 * Guillaume Demurger
 * Sylvain Fay-Chatelard
 * Anthony Fourneau
 * Aurèle Lenfant
 * Adrien Madouasse
 *
 * Copyright (C) 2013 Université Paris-Est Marne-la-Vallée 
 *
 * FreeStroke is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
 *
 */

/*!
 * \file TCPServer.cs
 * \author Sylvain Fay-Châtelard & Adrien Madouasse
 * \brief TCP communication with a FreeStroke to send Kinect data
 * \date 2013-03-07
 */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Net.Sockets;
using System.IO;
using System.Windows.Forms;
using AESDH;

namespace KController
{
    /*!
     * \class TCPServer
     * \brief The TCP server to send data from Kinect
     */
    class TCPServer
    {
        /*!< The controller, entrance of the application */
        private KController controller = null;
        /*!< The TCP server socket */
        private TcpListener socket = null;
        /*!< The TCP client socket */
        private TcpClient client = null;
        /*!< The TCP port */
        private ushort port;
        /*!< The stream in which the write to send data to the client */
        private NetworkStream stream = null;
        /*!< The state of the thread loop */
        private bool run = false;
        /*!< The state of the diffie hellman keys */
        private bool exchangeEnded = false;
        /*!< The max buffer size */
        private int BUFFER_SIZE = 2048;
        /*!< The AES algorithm */
        private AES aes;
        /*!< The thread in which the TCP server is launched */
        private Thread thread;

        /*!
         * \brief The constructor
         * \param controller The controller, entrance of the application
         * \param udp The UDP server
         * \param port The TCP port
         */
        public TCPServer(KController controller, ushort port)
        {
            this.controller = controller;
            this.port = port;
        }

        /*!
         * \brief Return if the TCP Server is currently started
         */
        public bool isRunning()
        {
            return run;
        }

        /*!
         * \brief Return if the diffie hellman exchange is ended
         */
        public bool isDiffieEnded()
        {
            return exchangeEnded;
        }

        /*!
         * \brief Start the TCP server in a thread
         */
        public void start()
        {
            if (thread == null && !run)
            {
                thread = new Thread(this.private_start);
                thread.Name = "TCP Thread";
                thread.Start();
            }
        }

        /*!
         * \brief Return the TCP port
         */
        public ushort getPort()
        {
            return port;
        }

        /*!
         * \brief Update the TCP port
         * \param port The TCP port
         */
        public void setPort(ushort port)
        {
            // Send port change request
            byte[] newPort = new byte[4];
            newPort[0] = 0;
            newPort[1] = 1;
            newPort[2] = (byte)(port >> 8);
            newPort[3] = (byte)port;
            this.sendRawData(newPort);

            // Restart TCP server
            this.stop();
            this.port = port;
            this.start();
        }

        /*!
         * \brief Start the TCP server
         */
        private void private_start()
        {
            run = true;

            try
            {
                socket = new TcpListener(System.Net.IPAddress.Any, port);
                socket.Start();
            }
            catch (System.Net.Sockets.SocketException e)
            {
                MessageBox.Show("TCP port is already used");
                Application.Exit();
            }

            // Accept loop
            while (run)
            {
                try
                {
                    // Accept a client
                    exchangeEnded = false;
                    client = socket.AcceptTcpClient();
                    controller.changeState(KController.KinectState.CONNECTED);
                    stream = client.GetStream();

                    // Secure the connection
                    diffieHellmanExchange();
                    exchangeEnded = true;

                    // Loop to send no data to detect when the communication is dead
                    while (run && client.Connected)
                    {
                        // Wait a little to not overload network
                        System.Threading.Thread.Sleep(100);
                    }
                    
                    // Close the connection
                    if (client.Connected)
                    {
                        client.Close();
                    }
                    controller.changeState(KController.KinectState.WAITING);
                }
                catch (System.IO.IOException e)
                {
                    client = null;
                    controller.changeState(KController.KinectState.WAITING);
                    Console.WriteLine("TCP : System.IO.IOException " + e.Message);
                }
                catch (System.InvalidOperationException e)
                {
                    this.stop();
                    client = null;
                    controller.changeState(KController.KinectState.WAITING);
                    Console.WriteLine("TCP : System.InvalidOperationException " + e.Message);
                }
                catch (System.Net.Sockets.SocketException e)
                {
                    client = null;
                    Console.WriteLine("TCP : System.Net.Sockets.SocketException " + e.Message);
                    return;
                }
            }
        }

        /*!
         * \brief Stop the TCP server
         */
        public void stop()
        {
            try
            {
                run = false;
                aes = null;
                if (client != null)
                {
                    client.Close();
                    client = null;
                }
                if (socket != null)
                {
                    socket.Stop();
                    socket = null;
                }
                if (thread != null)
                {
                    thread.Abort();
                    thread = null;
                }
            }
            catch (System.Net.Sockets.SocketException e)
            {
                Console.WriteLine("TCP : System.Net.Sockets.SocketException : " + e.Message);
            }
            catch (System.NullReferenceException e)
            {
                Console.WriteLine("TCP : System.NullReferenceException : " + e.Message);
            }
        }

        /*!
         * \brief Prepare a secure connection : make a Diffie-Hellman exchange
         *          to exchange a symetric key for AES algorithm
         */
        public void diffieHellmanExchange()
        {
            // Diffie-Hellman exchange
            byte[] data = new byte[sizeof(long) * 3];
            stream.Read(data, 0, sizeof(long) * 3);
            long g = loadBinaryLong(data, 0);
            long m = loadBinaryLong(data, sizeof(long));
            long A = loadBinaryLong(data, sizeof(long)*2);

            DiffieHellman diffie = new DiffieHellman();
            long B = diffie.createRecipientInterKey(g, m);
            long K = diffie.createRecipientEncryptionKey(A);
            byte[] response = new byte[sizeof(long)];
            saveBinaryLong(response, B);
            stream.Write(response, 0, sizeof(long));

            // AES initialization
            aes = new AES();
            byte[] cryptedKey = new byte[32];
            byte[] key = new byte[32];
            byte[] keyRow = new byte[sizeof(long)];
            saveBinaryLong(keyRow, K);
            Random rand = new Random((int)K);
            uint r = (uint)rand.Next();
            for (int i = 0; i < 32; i++)
            {
                key[i] = (byte)((r << 16) ^ (uint)rand.Next());
                cryptedKey[i] = (byte)(keyRow[4 + i % 4] ^ key[i]);
            }

            // Send the AES key to the FreeStroke client, crypted with a XOR
            stream.Write(cryptedKey, 0, 32);

            // To give pointer to the DLL
            // It's OK
            unsafe
            {
                fixed (byte* keyPtr = key)
                {
                    aes.makeKey(keyPtr);
                }
            }
        }

        /*!
         * \brief Send data to client without crypted it
         * \param data Data to send
         */
        public void sendRawData(byte[] data)
        {
            if (stream == null)
            {
                return;
            }
            stream.Write(data, 0, data.Length);
        }

        /*!
         * \brief Crypt and send data to the FreeStroke client
         * \param data Data to send
         */
        public void send(byte[] data)
        {
            if (socket == null || client == null || !client.Connected || aes == null)
            {
                return;
            }
            ushort length = (ushort)data.Length;
            uint sizeModulo = (uint)(length + ((16 - (length % 16)) % 16));

            // Write data in a buffer to crypted it
            byte[] bufferI = new byte[BUFFER_SIZE];
            byte[] bufferO = new byte[BUFFER_SIZE];
            for (int i = 0; i < length; i++)
            {
                bufferI[i] = (byte)data.ElementAt(i);
            }
            for (int i = length + 1; i < sizeModulo + 2; i++)
            {
                bufferI[i] = 0;
            }

            // Crypt data with AES
            // It's OK
            unsafe
            {
                fixed (byte* buffI = bufferI)
                {
                    fixed (byte* buffO = bufferO)
                    {
                        // Encrypt data and send
                        aes.encrypt(buffI, buffO, sizeModulo);
                        byte[] final = new byte[sizeModulo + 2];
                        final[0] = (byte)(length >> 8);
                        final[1] = (byte)length;
                        for (int i = 0; i < sizeModulo; i++)
                        {
                            final[i + 2] = buffO[i];
                        }
                        stream.Write(final, 0, (int)(sizeModulo + 2));
                    }
                }
            }
        }

        /*!
         * \brief Make a long from an array of bytes
         * \param data The binary long
         * \param offset Where the reading start in the array
         * \return The built long
         */
        long loadBinaryLong(byte[] data, int offset)
        {
	        long ret = 0;
	        for (int i = 0; i < sizeof(long); i++)
	        {
		        ret <<= 8;
                ret += data[i + offset];
	        }
	        return ret;
        }

        /*!
         * \brief Put a long in an array of bytes
         * \param data The array of bytes in which it puts the long
         * \param value The long to translate
         */
        void saveBinaryLong(byte[] data, long value)
        {
            for (int i = 0; i < sizeof(long); i++)
            {
                data[7 - i] = (byte)(value >> (8 * i));
            }
        }
    }
}
