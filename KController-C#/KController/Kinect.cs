/*!
 * \file Kinect.cs
 * \author Sylvain Fay-Châtelard & Adrien Madouasse
 * \brief Communication with the Kinect to retrieve skeleton data
 * \date 2013-03-07
 */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using Microsoft.Kinect;
using System.Threading;

namespace KController
{
    /*!
     * \class Kinect
     * \brief Manage the Kinect sensor
     */
    class Kinect
    {
        /*!< The Kinect sensor */
        private KinectSensor kinect = null;
        /*!< Array of skeleton */
        private Skeleton[] skeletonData = null;
        /*!< Check if it is the first skeleton */
        private bool isFirstSkeleton = false;
        /*!< The thread in which the object is used */
        private Thread thread;
        /*!< The reference to the GUI */
        private KController controller = null;
        /*!< The TCP sever */
        private TCPServer tcpServer = null;
        /*!< Limit the number of empty frame */
        private const int limit = 100;
        /*!< Limit the number of empty frame */
        private int counter = -1;

        /*!< Skeleton joints */
        private Dictionary<int, string> NamesToJoints = new Dictionary<int, string>() {
				{0, "ShoulderCenter"},
				{1, "Head"},
				{2, "ShoulderRight"},
				{6, "ShoulderLeft"},
				{3, "ElbowRight"},
				{7, "ElbowLeft"},
				{4, "WristRight"},
				{18, "HipCenter"}, //right-pelvis
				{19, "Spine"}, //left-pelvis
				{8, "WristLeft"},
				{5, "HandRight"},
				{10, "HipRight"},
				{14, "HipLeft"},
				{9, "HandLeft"},
				{11, "KneeRight"},
				{15, "KneeLeft"},
				{12, "AnkleRight"},
				{13, "FootRight"},
				{16, "AnkleLeft"},
				{17, "FootLeft"}
			};

        /*!
         * \brief The constructor
         * \param controller The reference to GUI
         * \param tcpServer The TCP server
         */
        public Kinect(KController controller, TCPServer tcpServer)
        {
            this.counter = limit;
            this.controller = controller;
            this.tcpServer = tcpServer;
        }

        /*!
         * \brief Start the Kinect sensor
         * \return true if the initialization id OK
         */
        public bool start()
        {
            // Get first Kinect Sensor
            kinect = KinectSensor.KinectSensors.FirstOrDefault(s => s.Status == KinectStatus.Connected);
            if (kinect == null)
            {
                return false;
            }
            KinectSensor.KinectSensors.StatusChanged += kinect_StatusChanged;
            thread = new Thread(this.private_start);
            thread.Start();
            return true;
        }

        /*!
         * \brief Uninitialize the Kinect and stop the thread
         */
        public void stop()
        {
            this.uninitialize();
            if (thread != null)
            {
                thread.Abort();
            }
        }

        /*!
         * \brief Start the Kinect
         */
        private void private_start()
        {
            kinect.SkeletonStream.TrackingMode = SkeletonTrackingMode.Default;
            kinect.SkeletonStream.Enable(); // Enable skeletal tracking
            skeletonData = new Skeleton[kinect.SkeletonStream.FrameSkeletonArrayLength]; // Allocate ST data
            kinect.SkeletonFrameReady += new EventHandler<SkeletonFrameReadyEventArgs>(kinect_SkeletonFrameReady); // Get Ready for Skeleton Ready Events
            kinect.Start(); // Start Kinect sensor
        }

        /*!
         * \brief Uninitialize and stop the Kinect
         */
        private void uninitialize()
        {
            if (kinect != null)
            {
                kinect.Stop();
                kinect.Dispose();
            }
        }

        /*!
         * \brief A callback to know when the status of the Kinect changed (plugged / unplugged)
         * \param sender Which send the message
         * \param e The event
         */
        private void kinect_StatusChanged(object sender, StatusChangedEventArgs e)
        {
            switch (e.Status)
            {
                case KinectStatus.Connected:
                    controller.changeState(KController.KinectState.WAITING);
                    break;
                case KinectStatus.Disconnected:
                case KinectStatus.NotReady:
                case KinectStatus.NotPowered:
                default:
                    controller.changeState(KController.KinectState.DISCONNECTED);
                    break;
            }
        }

        /*!
         * \brief A callback to know when a skeleton is ready
         * \param sender Which send the message
         * \param eventArgs The event
         */
        private void kinect_SkeletonFrameReady(object sender, SkeletonFrameReadyEventArgs eventArgs)
        {
            if (!tcpServer.isDiffieEnded())
            {
                return;
            }
            // Open the Skeleton frame
            using (SkeletonFrame skeletonFrame = eventArgs.OpenSkeletonFrame())
            {
                // Check that a frame is available
                if (skeletonFrame != null && this.skeletonData != null)
                {
                    if (isFirstSkeleton == false)
                    {
                        Console.WriteLine("Skeleton OK");
                        isFirstSkeleton = true;
                    }
                    // Get the skeletal information in this frame
                    skeletonFrame.CopySkeletonDataTo(this.skeletonData);
                    foreach (Skeleton skeleton in this.skeletonData)
                    {
                        if (skeleton.TrackingState == SkeletonTrackingState.Tracked)
                        {
                            Dictionary<string, float[]> joints = new Dictionary<string, float[]>();
                            string str = "";
                            str += DateTime.Now.ToString("yyyyMMddHHmmssffff") + " ";

                            foreach (Joint joint in skeleton.Joints)
                            {
                                float[] pos = new float[3];
                                pos[0] = joint.Position.X;
                                pos[1] = joint.Position.Y;
                                pos[2] = joint.Position.Z;
                                joints.Add(joint.JointType.ToString(), pos);
                            }

                            for (int i = 0; i < joints.Count; i++)
                            {
                                float[] res;
                                string jointName;
                                NamesToJoints.TryGetValue(i, out jointName);
                                joints.TryGetValue(jointName, out res);
                                str += res[0] + " " + res[1] + " " + res[2] + " ";
                            }

                            str += "\n";
                            try
                            {
                                tcpServer.send(System.Text.Encoding.ASCII.GetBytes(str));
                            }
                            catch (System.IO.IOException e)
                            {
                                Console.WriteLine("System.IO.IOException : " + e.Message);
                            }
                        }
                        else
                        {
                            counter--;
                            if (counter <= 0)
                            {
                                try
                                {
                                    byte[] b = { 0, 0 };
                                    tcpServer.sendRawData(b);
                                }
                                catch (System.IO.IOException e)
                                {
                                    Console.WriteLine("System.IO.IOException : " + e.Message);
                                }
                                counter = limit;
                            }
                        }
                    }
                }
            }
        }
    }
}
