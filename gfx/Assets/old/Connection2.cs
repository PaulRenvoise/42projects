using UnityEngine;
using System.Collections;
using System.Threading;
using System.Net.Sockets;
using System.Text;
using System.Net;
using System;

public class Connection2 : MonoBehaviour {

	// Use this for initialization

  private Socket sock;
  private bool connected = false;
  private Thread WorkerThread;
  public MapGeneration mapgen;
  public string ip = "127.0.0.1";
  public string port = "4242";

  /*void Connect()
  {
      WorkerThread = new Thread(ThreadListener);
      WorkerThread.Start();
  }*/

	void Connect()
  {
	  sock = new Socket
    (
      AddressFamily.InterNetwork,
      SocketType.Stream,
      ProtocolType.Tcp
    );

    IPEndPoint iep = new IPEndPoint(IPAddress.Parse("127.0.0.1"), int.Parse(port));

    try
    {
      sock.Connect(iep);
      connected = true;

      byte[] buffer = Encoding.ASCII.GetBytes("GRAPHIC\n");
      sock.Send(buffer, 0, buffer.Length, SocketFlags.None);

      //while (connected)
      //{
        int bytesCount;
        string res = "";
        byte[] buffer2 ;
        do
        {
            buffer2 = new byte[1];
            bytesCount = sock.Receive(buffer2, 0, buffer2.Length, SocketFlags.None);
            res = res + Encoding.Default.GetString(buffer2, 0, bytesCount);
        }
        while (Encoding.Default.GetString(buffer2, 0, bytesCount) != "\n");
        //Debug.Log(res);
          readData(res);
    //  }
    }
    /*catch (InvalidOperationException InvOpEx)
    {
        Debug.Log("TCP exception: " + InvOpEx.Message);
    }*/
    catch (SocketException SockEx)
    {
        Debug.Log("Socket exception: " + SockEx.Message);
    }
    finally
    {
        if(sock != null)
            sock.Close();
    }
	}

	void readData (string data)
  {
    string[] lines = data.Split('\n');
    foreach (string line in lines)
  	{
  	  string[] part = line.Split(' ');
      Debug.Log("part :" + part[0]);
      if (part[0] == "msz")
      {
        Debug.Log("gen");
        mapgen.generate(int.Parse(part[1]), int.Parse(part[2]));
      }
  	}
	}

  void OnGUI()
  {
    if (!connected)
    {
      ip = GUI.TextField(new Rect((Screen.width / 2) - (Screen.width / 4), 10, Screen.width / 4, 20), ip, 25);
      port = GUI.TextField(new Rect((Screen.width / 2) - (Screen.width / 4), 40, Screen.width / 8, 20), port, 4);

      if (GUI.Button(new Rect((Screen.width / 2) - (Screen.width / 9), 40, Screen.width / 9, 20), "Connect"))
          this.Connect();
    }
  }
}
