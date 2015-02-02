using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class ClientController : MonoBehaviour {

  public GameObject client;
  public GameObject eggPrefab;
  private List<GameObject> clients = new List<GameObject>();
  private List<GameObject> eggs = new List<GameObject>();
  private List<string> teams = new List<string>();
  public MapGeneration mapGen;

  public bool displayTeamInfo = false;
  public Vector2 scrollPosition;

  public int speed = 10;

  public ClientNetwork cn;

	// Use this for initialization
	void Start () {

	}

	// Update is called once per frame
	void Update ()
  {
	}

  public void addTeam(string name)
  {
    teams.Add(name);
  }

  private int findTeamNumber(string team)
  {
    for (int i = 0; i < teams.Count; i++)
    {
      if (team == teams[i])
        return i;
    }
    return 0;
  }

  public void newClient(int id, int x, int y, int or, int lvl, string team)
  {

    int team_nbr = findTeamNumber(team);
    Vector3 pos = mapGen.getCaseAt(x, y).getAvailablePosition();

    GameObject c = Instantiate(client, new Vector3(pos.x, 0.6f, pos.z), Quaternion.identity) as GameObject;
    c.GetComponent<Client>().setId(id);
    c.GetComponent<Client>().setTeam(team);
    c.GetComponent<Client>().setLevel(lvl);
    c.GetComponent<Client>().setTexture(team_nbr);
    mapGen.getCaseAt(x, y).playerEnter(c);

    c.GetComponent<Client>().setCube(mapGen.getCubeAt(x, y));
    c.GetComponent<Client>().setOrientation(or);

    c.GetComponent<Client>().modifySpeed(speed);

    clients.Add(c);
  }

  public void incantation(int[] ids)
  {
    for(int i = 0 ; i < ids.Length; i++)
    {
      getClientById(ids[i]).GetComponent<Client>().incantation();
    }
  }

  public void newEgg(int idEgg, int idClient, int x, int y)
  {
    GameObject client = getClientById(idClient);
    if (client != null)
    {
      int team_nbr = client.GetComponent<Client>().getTeamId();

      Vector3 pos = mapGen.getCaseAt(x, y).getAvailablePosition();

      GameObject egg = Instantiate(eggPrefab, new Vector3(pos.x, 0.71f, pos.z), Quaternion.identity) as GameObject;
      egg.GetComponent<Egg>().setId(idEgg);
      egg.GetComponent<Egg>().setTeam(client.GetComponent<Client>().getTeam());
      egg.GetComponent<Egg>().setColor(team_nbr);

      mapGen.getCaseAt(x, y).playerEnter(egg);

      egg.GetComponent<Egg>().setCube(mapGen.getCubeAt(x, y));

      eggs.Add(egg);
    }
  }

  public void eclotEgg(int id)
  {
    GameObject egg = null;
    for (int i = 0; i < eggs.Count; i++)
    {
      if (eggs[i].GetComponent<Egg>().getId() == id)
      {
        egg = eggs[i];
        break ;
      }
    }
    if (egg)
    {
      egg.GetComponent<Egg>().eclore();
    }
  }

  public void moisieEgg(int id)
  {
    GameObject egg = null;
    for (int i = 0; i < eggs.Count; i++)
    {
      if (eggs[i].GetComponent<Egg>().getId() == id)
      {
        egg = eggs[i];
        break ;
      }
    }
    if (egg)
    {
      egg.GetComponent<Egg>().moisir();
    }
  }

  public void connectionEgg(int id)
  {
    GameObject egg = null;
    for (int i = 0; i < eggs.Count; i++)
    {
      if (eggs[i].GetComponent<Egg>().getId() == id)
      {
        egg = eggs[i];
        break ;
      }
    }
    if (egg)
    {
      egg.GetComponent<Egg>().getCube().GetComponent<CubeMap>().playerExit(egg);
      eggs.Remove(egg);
      Destroy(egg);
    }
  }

  public void deadClient(int id)
  {
    GameObject client = getClientById(id);
    if (client != null)
    {
      clients.Remove(client);
      client.GetComponent<Client>().die();
    }
  }

  public GameObject getClientById(int id)
  {
    GameObject client = null;
    for (int i = 0; i < clients.Count; i++)
    {
      if (clients[i].GetComponent<Client>().getId() == id)
      {
        client = clients[i];
        break ;
      }
    }
    return client;
  }

  public void updateClientInventory(int id, int[] inv)
  {
    GameObject client = getClientById(id);
    if (client != null)
      client.GetComponent<Client>().setInventory(inv);
  }

  public void levelUpClient(int id, int lvl)
  {
    GameObject client = getClientById(id);
    if (client != null)
    {
      client.GetComponent<Client>().levelUp();
    }
  }

  public void moveClient(int id, int x, int y, int or)
  {
    GameObject client = getClientById(id);
    if (client != null)
    {
      if (client.GetComponent<Client>().getCube().GetComponent<CubeMap>().getX() != x || client.GetComponent<Client>().getCube().GetComponent<CubeMap>().getY() != y)
      {
        CubeMap cm = client.GetComponent<Client>().getCube().GetComponent<CubeMap>();
        if (cm.getY() == 0 && y == mapGen.getHeight() -1)
        {
          client.GetComponent<Client>().setTp(cm.getTpSouth());
          client.GetComponent<Client>().setTpOut(mapGen.getCaseAt(x, y).getTpNorth());
        }
        else if (cm.getX() == 0 && x == mapGen.getWidth() - 1)
        {
          client.GetComponent<Client>().setTp(cm.getTpWest());
          client.GetComponent<Client>().setTpOut(mapGen.getCaseAt(x, y).getTpEast());
        }
        else if (cm.getX() == mapGen.getWidth() - 1 && x == 0)
        {
          client.GetComponent<Client>().setTp(cm.getTpEast());
          client.GetComponent<Client>().setTpOut(mapGen.getCaseAt(x, y).getTpWest());
        }
        else if (cm.getY() == mapGen.getHeight() - 1 && y == 0)
        {
          client.GetComponent<Client>().setTp(cm.getTpNorth());
          client.GetComponent<Client>().setTpOut(mapGen.getCaseAt(x, y).getTpSouth());
        }
        cm.playerExit(client);
        client.GetComponent<Client>().setTarget(mapGen.getCaseAt(x, y).getAvailablePosition());
        mapGen.getCaseAt(x, y).playerEnter(client);
        client.GetComponent<Client>().setCube(mapGen.getCubeAt(x, y));
      }
      else
      {
        client.GetComponent<Client>().rotate(or);
      }
    }
  }

  public void messageClient(int id, string msg)
  {
    GameObject client = getClientById(id);
    if (client != null)
    {
      client.GetComponent<Client>().sendMessage(msg);
    }
  }

  public void expulse(int id)
  {
    GameObject client = getClientById(id);
    if (client != null)
    {
      client.GetComponent<Client>().expulse();
    }
  }

  public void clientTakeRessource(int id, int rc)
  {
    GameObject client = getClientById(id);
    if (client != null)
    {
      client.GetComponent<Client>().takeRessource();
    }
  }

  void OnGUI()
  {
    if (cn.isConnected() == true)
    {
        GUI.color = Color.black;
        GUI.Label(new Rect(0, 25, 100, 25), "Speed : " + this.speed);
        GUI.color = Color.white;
        if (GUI.Button(new Rect(0, 45, 50, 35), "-") && speed > 1)
        {
          this.speed -= 1;
          cn.WriteString("sst "+ this.speed +"\n");
        }

        if (GUI.Button(new Rect(55, 45, 50, 35), "+"))
        {
          this.speed += 1;
          cn.WriteString("sst "+ this.speed +"\n");
        }

        if (GUI.Button(new Rect(0, 85, 50, 35), " - 10") && speed > 10)
        {
          this.speed -= 10;
          cn.WriteString("sst "+ this.speed +"\n");
        }

        if (GUI.Button(new Rect(55, 85, 50, 35), "+ 10"))
        {
          this.speed += 10;
          cn.WriteString("sst "+ this.speed +"\n");
        }

        if (GUI.Button(new Rect(0, 125, 50, 35), " - 100") && speed > 100)
        {
          this.speed -= 100;
          cn.WriteString("sst "+ this.speed +"\n");
        }

        if (GUI.Button(new Rect(55, 125, 50, 35), "+ 100"))
        {
          this.speed += 100;
          cn.WriteString("sst "+ this.speed +"\n");
        }


        if (displayTeamInfo)
        {

          if (GUI.Button(new Rect(0, 0, Screen.width / 10, 20), "Hide teams info"))
            displayTeamInfo = false;

          for (int i = 0 ; i < teams.Count; i++)
          {
            int numClient = getClientFromTeam(i).Count;
            if (numClient > 0)
            {
              Rect teamBox = new Rect();
              teamBox.x = (Screen.width / teams.Count) * i;
              teamBox.y = Screen.height - ((numClient + 1) * 20) - 10;

              teamBox.width = Screen.width / teams.Count;
              teamBox.height = ((numClient + 1) * 20) + 10;

              if (i % 8 == 0)
                GUI.color = new Color(1, 0.8f, 0.65f, 1);
              else if (i % 8 == 1)
                GUI.color = new Color(1, 0.1f, 0.9f, 1);
              else if (i % 8 == 2)
                GUI.color = new Color(0.1f, 0.9f, 0.15f, 1);
              else if (i % 8 == 3)
                GUI.color = new Color(0.95f, 0.7f, 0.2f, 1);
              else if (i % 8 == 4)
                GUI.color = new Color(0.3f, 0.9f, 1, 1);
              else if (i % 8 == 5)
                GUI.color = new Color(0.8f, 0.7f, 1, 1);
              else if (i % 8 == 6)
                GUI.color = new Color(1f, 0.95f, 0.9f, 1);
              else if (i % 8 == 7)
                GUI.color = new Color(0.5f, 0.5f, 0.5f, 1);


              GUI.Window(i, teamBox, displayTeam, teams[i]);
            }
          }
        }
        else
        {
            if (GUI.Button(new Rect(0, 0, Screen.width / 10, 20), "Show teams info"))
              displayTeamInfo = true;
        }
    }
  }

  public void modifySpeed(int sp)
  {
    this.speed = sp;
    for(int i = 0 ; i < clients.Count ; i++)
    {
      clients[i].GetComponent<Client>().modifySpeed(sp);
    }
  }

  List<Client> getClientFromTeam(int id)
  {
    List<Client> lst = new List<Client>();

    for(int i = 0 ; i < clients.Count ; i++)
    {
      if (clients[i].GetComponent<Client>().getTeamId() == id)
        lst.Add(clients[i].GetComponent<Client>());
    }
    return lst;
  }

  void displayTeam(int winId)
  {
    List<Client> lst = getClientFromTeam(winId);
    if (winId % 8 == 0)
      GUI.color = new Color(1, 0.65f, 0.65f, 1);
    else if (winId % 8 == 1)
      GUI.color = new Color(1, 0.1f, 0.9f, 1);
    else if (winId % 8 == 2)
      GUI.color = new Color(0.1f, 0.9f, 0.15f, 1);
    else if (winId % 8 == 3)
      GUI.color = new Color(0.95f, 0.7f, 0.2f, 1);
    else if (winId % 8 == 4)
      GUI.color = new Color(0.3f, 0.9f, 1, 1);
    else if (winId % 8 == 5)
      GUI.color = new Color(0.8f, 0.7f, 1, 1);
    else if (winId % 8 == 6)
      GUI.color = new Color(1f, 0.95f, 0.9f, 1);
    else if (winId % 8 == 7)
      GUI.color = new Color(0.1f, 0.1f, 0.1f, 1);

    for (int i = 0 ; i < lst.Count ; i++)
    {
      GUI.Label(new Rect(10, 20 * (i + 1) , 135, 20 * (i + 1)),  "Client #" +lst[i].getId()+" : "+lst[i].getLevel() + " nr : " + lst[i].getNourriture());
    }
  }
}
