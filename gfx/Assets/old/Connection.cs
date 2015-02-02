using System.Net;
using System.Net.Sockets;
using System.Threading;
using System;
using System.Text;
using UnityEngine;
using System.Collections;
using System.IO;

public class Connection : MonoBehaviour
{

    private Thread WorkerThread;
    private bool running = false;

    public void Start()
    {
        WorkerThread = new Thread(ThreadListener);
        WorkerThread.Start();
    }

    public void Stop()
    {
        running = false;
        WorkerThread.Join();
        WorkerThread = null;
    }

    private void ThreadListener()
    {
        TcpClient client = new TcpClient();
        NetworkStream ns = null;
        int port = 4242;

        try
        {

            client.Connect(new IPEndPoint(IPAddress.Parse("127.0.0.1"), port));

            ns = client.GetStream();
            StreamReader sr= new StreamReader(ns, Encoding.UTF8);
            StreamWriter sw = new StreamWriter(ns, Encoding.UTF8);


            /*// Wait for the data to arrive, sleep thread continuously until it does
            // But don't wait forever, or thread might deadlock
            int waitCounter = 0;
            while (!ns.DataAvailable && waitCounter < 1000)
            {
                Thread.Sleep(10);
                waitCounter++;
            }

            // Done waiting. Did we exit because data is available, or did we exit because of a timeout?
            if (waitCounter == 1000)
            {
                // 10053 is the Windows Socket error code for when software causes a connection abort, possibly due to a time-out, which is exactly
                // what has happened if the waitCounter reaches 1000
                throw new SocketException(10053);
            }*/

            running = true;
            // Incoming complete. Enter read loop.

            //byte[] myWriteBuffer = Encoding.ASCII.GetBytes("GRAPHICS\n");

            if (ns.CanWrite)
            {
              sw.WriteLine("GRAPHICS\n");

            }
            else{
                 Debug.Log("Sorry.  You cannot write to this NetworkStream.");
            }

            while (running)
            {
                String line = sr.ReadLine();
                Debug.Log("read");
                Debug.Log(line);

                // Then parse values out of your data chunk typically using static methods
                // in the BitConverter class
                //int example = BitConverter.ToInt32(data, 0); // Makes an integer out of the first 4 bytes read

            }
        }
        catch (InvalidOperationException InvOpEx)
        {
            Debug.Log("TCP exception: " + InvOpEx.Message);
        }
        catch (SocketException SockEx)
        {
            Debug.Log("Socket exception: " + SockEx.Message);
        }
        finally
        {
            if(ns != null)
                ns.Close();
            client.Close();
        }
    }
}
