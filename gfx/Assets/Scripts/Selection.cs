using UnityEngine;
using System.Collections;

public class Selection : MonoBehaviour {

	// Use this for initialization
  public GameObject caseSelected;
  public GameObject playerSelected;
  public GameObject eggSelected;
  public ClientNetwork cn;
  private Rect selectionBox;
  private Rect selectionBoxClient;
  private Rect selectionBoxEgg;
	void Start ()
  {
    caseSelected = null;
    playerSelected = null;
    eggSelected = null;

    this.selectionBox.width = Screen.width / 8;
    this.selectionBox.height = 170;

    this.selectionBox.x = (Screen.width) - (this.selectionBox.width);
    this.selectionBox.y = 0;

    this.selectionBoxClient.width = Screen.width / 8;
    this.selectionBoxClient.height = 220;

    this.selectionBoxClient.x = (Screen.width) - (this.selectionBoxClient.width);
    this.selectionBoxClient.y = 170;

    this.selectionBoxEgg.width = Screen.width / 8;
    this.selectionBoxEgg.height = 50;

    this.selectionBoxEgg.x = (Screen.width) - (this.selectionBoxEgg.width);
    this.selectionBoxEgg.y = 390;
	}

	// Update is called once per frame
	void Update ()
  {
    if (Input.GetMouseButtonDown(0))
    {
      Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
      RaycastHit hit;
      if (Physics.Raycast(ray, out hit, 100))
      {
        if (hit.collider.gameObject.tag == "case" && caseSelected != hit.collider.gameObject)
        {
          if (caseSelected != null)
          {
            caseSelected.GetComponent<CubeMap>().unselect();
          }
          hit.collider.gameObject.GetComponent<CubeMap>().select();
          caseSelected = hit.collider.gameObject;
        }
        else if (caseSelected == hit.collider.gameObject)
        {
          caseSelected.GetComponent<CubeMap>().unselect();
          caseSelected.GetComponent<CubeMap>().over();
          caseSelected = null;
        }
        else if (caseSelected != null && hit.collider.gameObject.tag == "case")
        {
          caseSelected.GetComponent<CubeMap>().unselect();
          caseSelected = null;
        }
        else if (hit.collider.gameObject.tag == "client" && playerSelected != hit.collider.gameObject)
        {
          if (playerSelected != null)
          {
            playerSelected.GetComponent<Client>().unselect();
          }
          hit.collider.gameObject.GetComponent<Client>().select();
          playerSelected = hit.collider.gameObject;
          this.cn.WriteString("pin #" + playerSelected.GetComponent<Client>().getId() + "\n");
        }
        else if (playerSelected == hit.collider.gameObject)
        {
          playerSelected.GetComponent<Client>().unselect();
          playerSelected = null;
        }
        else if (hit.collider.gameObject.tag == "egg" && eggSelected != hit.collider.gameObject)
        {
          if (eggSelected != null)
          {
            eggSelected.GetComponent<Egg>().unselect();
          }
          hit.collider.gameObject.GetComponent<Egg>().select();
          eggSelected = hit.collider.gameObject;
        }
        else if (playerSelected == hit.collider.gameObject)
        {
          eggSelected.GetComponent<Egg>().unselect();
          eggSelected = null;
        }
      }
      else
      {
        if (caseSelected != null)
        {
          caseSelected.GetComponent<CubeMap>().unselect();
          caseSelected = null;
        }

        if (playerSelected != null)
        {
          playerSelected.GetComponent<Client>().unselect();
          playerSelected = null;
        }

        if (eggSelected != null)
        {
          eggSelected.GetComponent<Egg>().unselect();
          eggSelected = null;
        }
      }
    }
	}

  void OnGUI()
  {
    if (caseSelected != null)
    {
      GUI.Window(100, selectionBox, displayCaseContent, "Case "
                 + caseSelected.GetComponent<CubeMap>().getX() + " "
                 + caseSelected.GetComponent<CubeMap>().getY() );
    }

    if (playerSelected != null)
    {
      GUI.Window(101, selectionBoxClient, displayClientInventory, "Client #" + playerSelected.GetComponent<Client>().getId());
    }

    if (eggSelected != null)
    {
      GUI.Window(102, selectionBoxEgg, displayEgg, "Egg #" + eggSelected.GetComponent<Egg>().getId());
    }
  }

  void displayCaseContent(int winId)
  {
     int[] rcs = caseSelected.GetComponent<CubeMap>().getRessources();
     GUI.Label(new Rect(10, 20, 100, 20),  "Food : " + rcs[0]);
     GUI.Label(new Rect(10, 40, 100, 20),  "Linemate : " + rcs[1]);
     GUI.Label(new Rect(10, 60, 100, 20),  "Deraumere : " + rcs[2]);
     GUI.Label(new Rect(10, 80, 100, 20),  "Sibur : " + rcs[3]);
     GUI.Label(new Rect(10, 100, 100, 20), "Mendiane : " + rcs[4]);
     GUI.Label(new Rect(10, 120, 100, 20), "Phiras : " + rcs[5]);
     GUI.Label(new Rect(10, 140, 100, 20), "Thystame : " + rcs[6]);
  }

  void displayClientInventory(int winId)
  {
     int[] inventory = playerSelected.GetComponent<Client>().getInventory();
     GUI.Label(new Rect(10, 20, 100, 20),  "Level : " + playerSelected.GetComponent<Client>().getLevel());
     GUI.Label(new Rect(10, 40, 100, 20),  "team : " + playerSelected.GetComponent<Client>().getTeam());
     GUI.Label(new Rect(10, 55, 100, 20),  "------");
     GUI.Label(new Rect(10, 70, 100, 20),  "Food : " + inventory[0]);
     GUI.Label(new Rect(10, 90, 100, 20),  "Linemate : " + inventory[1]);
     GUI.Label(new Rect(10, 110, 100, 20),  "Deraumere : " + inventory[2]);
     GUI.Label(new Rect(10, 130, 100, 20),  "Sibur : " + inventory[3]);
     GUI.Label(new Rect(10, 150, 100, 20), "Mendiane : " + inventory[4]);
     GUI.Label(new Rect(10, 170, 100, 20), "Phiras : " + inventory[5]);
     GUI.Label(new Rect(10, 190, 100, 20), "Thystame : " + inventory[6]);
  }

  void displayEgg(int winId)
  {
     GUI.Label(new Rect(10, 20, 100, 20),  "team : " + eggSelected.GetComponent<Egg>().getTeam());
  }
}
