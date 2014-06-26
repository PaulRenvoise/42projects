using UnityEngine;
using System;
using System.Threading;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.IO;
using System.Net.Sockets;
using System.Text;

public class ClientNetwork : MonoBehaviour {

    private static byte[] recievebuffer = new byte[4096];

    private static Queue<string> RecieveQueue = new Queue<string>();
    private static readonly object RecieveQueueLocker = new object();
    private static readonly object RecieveBufferLocker = new object();
    private static readonly object RecieveThreadLocker = new object();
    public MapGeneration mapgen;
    public ClientController clientCont;
    public Selection selection;
    private static bool RecieveThreadFree = true;
    private bool socketReady = false;
    public string ip = "127.0.0.1";
    public string port = "4242";

    private static Socket mySocket;

    private bool menu;
    private Rect menuRect;

    public string winner;

    void Start()
    {
      winner = "";
      menu = false;

      this.menuRect.width = Screen.width / 2;
      this.menuRect.height = Screen.height / 4;

      this.menuRect.x = (Screen.width / 2) - (this.menuRect.width / 2);
      this.menuRect.y = (Screen.height / 2) - (this.menuRect.height / 2);
    }

    void CheckRecieve()
    {
       string msg = string.Empty;
       lock(RecieveQueueLocker)
       {
         if (RecieveThreadFree && RecieveQueue.Count > 0)
         {
           msg = RecieveQueue.Dequeue();
         }
       }
       if (!string.IsNullOrEmpty(msg))
       {
         if (msg.Length >= 2)
         {
          //Debug.Log ("Message: " + msg);
          readData(msg);
         }
       }
    }

    void Update()
    {
       if (socketReady)
       {
         if (Connected())
           CheckRecieve();
          else
          {
            closeSocket();
            Application.LoadLevel(0);
          }

       }
       if (Input.GetKeyDown(KeyCode.Escape))
         menu = !menu;
    }

    void OnApplicationQuit()
    {
       closeSocket();
    }

    public bool setupSocket(string Host, int Port)
    {
       try
       {
         mySocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
         mySocket.Connect(Host, Port);
         Debug.Log ("Connected.");
         mySocket.BeginReceive(recievebuffer, 0, recievebuffer.Length, SocketFlags.None, new AsyncCallback(ReaderThread), mySocket);
         Debug.Log("test4");
         Debug.Log ("Reader Thread Started.");
         socketReady = true;
         WriteString("GRAPHIC\n");
         return true;
       }
       catch (Exception e)
       {
         Debug.Log("Connection error");
       }
       return false;
    }

    public bool Connected()
    {
       try
       {
         if (mySocket.Connected)
         {
          return true;
         } else
         {
          return false;
         }
       }
       catch (Exception e)
       {
         Debug.Log ("Socket Error on Connection Check: " + e);
         return false;
       }
    }

    private static void ReaderThread (IAsyncResult AR)
    {
       try
       {
         Socket socket = (Socket)AR.AsyncState;
         //Socket socket = mySocket;
         int recieved = socket.EndReceive(AR);
         byte[] dataBuf = new byte[recieved];
         Array.Copy(recievebuffer, dataBuf, recieved);
         string text = Encoding.ASCII.GetString(dataBuf);
         lock(RecieveQueueLocker)
         {
          RecieveQueue.Enqueue(text);
         }
         try
         {
          mySocket.BeginReceive(recievebuffer, 0, recievebuffer.Length, SocketFlags.None, new AsyncCallback(ReaderThread), mySocket);
         }
         catch (Exception e)
         {
          Debug.Log("(Reader Thread: Start Next) Socket error: " + e);
         }
       }
       catch (Exception e)
       {
         Debug.Log("(Reader Thread: Begin) Socket error: " + e);
       }
    }

    private static void WriterThread (IAsyncResult AR)
    {
       Socket socket = (Socket)AR.AsyncState;
       socket.EndSend(AR);
    }

    public void WriteString(string theLine)
    {
       byte[] data = Encoding.ASCII.GetBytes(theLine);
       try
       {
         mySocket.BeginSend(data, 0, data.Length, SocketFlags.None, new AsyncCallback(WriterThread), mySocket);
         Debug.Log("Sent: " + theLine);
       }
       catch (Exception e)
       {
         Debug.Log("(Network: WriteString) Socket error: " + e);

       }
    }

    public void closeSocket()
    {
       if (!socketReady)
         return;
       try
       {
         mySocket.Close();
       }
       catch (Exception e)
       {
         Debug.Log("Close Socket Failed: " + e);
       }
       socketReady = false;
    }

    void readData (string data)
    {
      string[] lines = data.Split('\n');
      foreach (string line in lines)
      {
        string[] part = line.Split(' ');
        Debug.Log(line);
        if (part[0] == "msz")
        {
          mapgen.generate(int.Parse(part[1]), int.Parse(part[2]));
        }
        else if (part[0] == "bct")
        {
          Debug.Log("update rcs");
          int[] ressources = {int.Parse(part[3]), int.Parse(part[4]), int.Parse(part[5]),
                              int.Parse(part[6]), int.Parse(part[7]), int.Parse(part[8]), int.Parse(part[9])};
          mapgen.updateRessources(int.Parse(part[1]), int.Parse(part[2]), ressources);
        }
        else if (part[0] == "pnw")
        {
          clientCont.newClient(int.Parse(part[1].Substring(1, part[1].Length - 1)),
                              int.Parse(part[2]), int.Parse(part[3]), int.Parse(part[4]), int.Parse(part[5]), part[6]);
        }
        else if (part[0] == "tna")
        {
          clientCont.addTeam(part[1]);
        }
        else if (part[0] == "sgt")
        {
          clientCont.modifySpeed(int.Parse(part[1]));
        }
        else if (part[0] == "pdi")
        {
          clientCont.deadClient(int.Parse(part[1].Substring(1, part[1].Length - 1)));
        }
        else if (part[0] == "pin")
        {
          int[] inv = {int.Parse(part[4]), int.Parse(part[5]), int.Parse(part[6]),
                      int.Parse(part[7]), int.Parse(part[8]), int.Parse(part[9]), int.Parse(part[10])};
          clientCont.updateClientInventory(int.Parse(part[1].Substring(1, part[1].Length - 1)), inv);
        }
        else if (part[0] == "ppo")
        {
          clientCont.moveClient(int.Parse(part[1].Substring(1, part[1].Length - 1)),
                                int.Parse(part[2]), int.Parse(part[3]), int.Parse(part[4]));
        }
        else if (part[0] == "pic")
        {
          mapgen.startIncantation(int.Parse(part[1]), int.Parse(part[2]), int.Parse(part[3]));

          int[] players = new int[part.Length - 4];

          for(int j = 0; j < part.Length - 4 ; j++)
          {
            players[j] = int.Parse(part[4 + j].Substring(1, part[4 + j].Length - 1));
          }

          clientCont.incantation(players);
        }
        else if (part[0] == "pie")
        {
          mapgen.stopIncantation(int.Parse(part[1]), int.Parse(part[2]));
        }
        else if (part[0] == "plv")
        {
          clientCont.levelUpClient(int.Parse(part[1].Substring(1, part[1].Length - 1)), int.Parse(part[2]));
        }
        else if (part[0] == "pbc")
        {
          clientCont.messageClient(int.Parse(part[1].Substring(1, part[1].Length - 1)), part[2]);
        }
        else if (part[0] == "pgt" || part[0] == "pdr")
        {
          clientCont.clientTakeRessource(int.Parse(part[1].Substring(1, part[1].Length - 1)), int.Parse(part[2]));
        }
        else if (part[0] == "pex")
        {
          clientCont.expulse(int.Parse(part[1].Substring(1, part[1].Length - 1)));
        }
        else if (part[0] == "enw")
        {
          clientCont.newEgg(int.Parse(part[1].Substring(1, part[1].Length - 1)),
                                         int.Parse(part[2].Substring(1, part[2].Length - 1)),
                                         int.Parse(part[3]), int.Parse(part[4])
                                        );
        }
        else if (part[0] == "eht")
        {
          clientCont.eclotEgg(int.Parse(part[1].Substring(1, part[1].Length - 1)));
        }
        else if (part[0] == "edi")
        {
          clientCont.moisieEgg(int.Parse(part[1].Substring(1, part[1].Length - 1)));
        }
        else if (part[0] == "ebo")
        {
          clientCont.connectionEgg(int.Parse(part[1].Substring(1, part[1].Length - 1)));
        }
        else if (part[0] == "seg")
        {
          this.winner = part[1];
        }
      }
    }

    void OnGUI()
    {
      if (!socketReady)
      {
        ip = GUI.TextField(new Rect((Screen.width / 2) - (Screen.width / 8), Screen.height / 2 - 20, Screen.width / 4, 20), ip, 25);
        port = GUI.TextField(new Rect((Screen.width / 2) - (Screen.width / 8), Screen.height / 2 + 20, Screen.width / 8, 20), port, 4);

        if (GUI.Button(new Rect((Screen.width / 1.95f), Screen.height / 2 + 20, Screen.width / 9, 20), "Connect"))
            this.setupSocket(ip, int.Parse(port));
      }

      if (menu)
      {
        GUI.Window(99, menuRect, displayMenu, "Menu");
      }

      if (winner != "")
      {
        GUI.color = Color.red;
        GUI.Label(new Rect(200, 0, 200, 30), "Team : " + this.winner + " won.");
        GUI.color = Color.white;
      }

    }

  public bool isConnected()
  {
    return this.socketReady;
  }

  void displayMenu(int winId)
  {
    if (GUI.Button(new Rect(this.menuRect.width / 4, this.menuRect.height / 10, this.menuRect.width / 2, this.menuRect.height / 5), "Quit"))
    {
      closeSocket();
      Application.Quit();
    }
    if (GUI.Button(new Rect(this.menuRect.width / 4, this.menuRect.height / 3, this.menuRect.width / 2, this.menuRect.height / 5), "Resum"))
        menu = false;
    if (GUI.Button(new Rect(this.menuRect.width / 4, this.menuRect.height / 1.75f, this.menuRect.width / 2, this.menuRect.height / 5), "Disconnect"))
    {
      closeSocket();
      Application.LoadLevel(0);
    }
  }

}
