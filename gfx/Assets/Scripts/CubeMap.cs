using UnityEngine;
using System.Collections;

public class CubeMap : MonoBehaviour {

	// Use this for initialization
  public int[] ressources = {0, 0, 0, 0, 0, 0, 0};

  public Transform[] positions;

  public bool movingUp = false;
  public GameObject apple;
  public GameObject linemate;
  public GameObject deraumetre;
  public GameObject sibur;
  public GameObject mendiane;
  public GameObject phiras;
  public GameObject thysame;
  private bool selected = false;

  public int pos1 = 0;
  public GameObject pos2;
  public GameObject pos3;
  public GameObject pos4;
  public GameObject pos5;
  public GameObject pos6;
  public GameObject pos7;
  public GameObject pos8;
  public GameObject pos9;

  public ParticleSystem ps1;
  public ParticleSystem ps2;

  public Transform tp_north;
  public Transform tp_south;
  public Transform tp_west;
  public Transform tp_east;

  private int x;
  private int y;

  private int lvlIncantation = 1;

  public GameObject deraumerePart;
  public GameObject linematePart;
  public GameObject mendianePart;
  public GameObject phyrasPart;
  public GameObject siburPart;
  public GameObject thysamePart;

	void Awake ()
  {
	   this.transform.Translate(Vector3.down * 2);
     this.transform.Find("plane").gameObject.renderer.enabled = false;
     this.positions = new Transform[9];
     positions[0] = this.transform.Find("pos1");
     positions[1] = this.transform.Find("pos2");
     positions[2] = this.transform.Find("pos3");
     positions[3] = this.transform.Find("pos4");
     positions[4] = this.transform.Find("pos5");
     positions[5] = this.transform.Find("pos6");
     positions[6] = this.transform.Find("pos7");
     positions[7] = this.transform.Find("pos8");
     positions[8] = this.transform.Find("pos9");

     pos1 = 0;

     pos2 = null;
     pos3 = null;
     pos4 = null;
     pos5 = null;
     pos6 = null;
     pos7 = null;
     pos8 = null;
     pos9 = null;

     ps1.enableEmission = false;
     ps2.enableEmission = false;
	}

	// Update is called once per frame
	void Update ()
  {
    if (this.transform.position.y < 0 && movingUp)
    {
      this.transform.Translate(Vector3.up * Time.deltaTime * 3);
      if (this.transform.position.y >= 0)
      {
        this.transform.position = new Vector3(this.transform.position.x, 0, this.transform.position.z);
        movingUp = false;
      }
    }
	}

  public void updateRessouce(int id, int value)
  {
    this.ressources[id] = value;
    if (this.ressources[id] <= 0)
    {
      if (id == 0)
      {
       apple.transform.Find("apple").gameObject.renderer.enabled = false;
       apple.transform.Find("stem").gameObject.renderer.enabled = false;
      }
      else if (id == 1)
       linemate.renderer.enabled = false;
      else if (id == 2)
        deraumetre.renderer.enabled = false;
      else if (id == 3)
        sibur.renderer.enabled = false;
      else if (id == 4)
        mendiane.renderer.enabled = false;
      else if (id == 5)
        phiras.renderer.enabled = false;
      else if (id == 6)
        thysame.renderer.enabled = false;
    }
    else
    {
      if (id == 0)
      {
       apple.transform.Find("apple").gameObject.renderer.enabled = true;
       apple.transform.Find("stem").gameObject.renderer.enabled = true;
      }
      else if (id == 1)
       linemate.renderer.enabled = true;
      else if (id == 2)
        deraumetre.renderer.enabled = true;
      else if (id == 3)
        sibur.renderer.enabled = true;
      else if (id == 4)
        mendiane.renderer.enabled = true;
      else if (id == 5)
        phiras.renderer.enabled = true;
      else if (id == 6)
        thysame.renderer.enabled = true;
    }
  }

  public void updateRessources(int[] rcs)
  {
    this.ressources = rcs;
    this.updateRessouce(0, this.ressources[0]);
    this.updateRessouce(1, this.ressources[1]);
    this.updateRessouce(2, this.ressources[2]);
    this.updateRessouce(3, this.ressources[3]);
    this.updateRessouce(4, this.ressources[4]);
    this.updateRessouce(5, this.ressources[5]);
    this.updateRessouce(6, this.ressources[6]);
  }

  public void moveUp()
  {
    movingUp = true;
  }

  void OnMouseEnter()
  {
    if (!selected)
    {
      this.over();
    }
  }

  public void over()
  {
    this.transform.Find("grid").gameObject.renderer.material.SetFloat("_LineWidth", 0.02f);
    this.transform.Find("plane").gameObject.renderer.enabled = true;
    this.transform.Find("grid").gameObject.renderer.material.SetColor("_GridColor", new Color(1F, 1F, 1F, 0.0F));
    this.transform.Find("grid").gameObject.renderer.material.SetColor("_LineColor", new Color(0F, 0F, 0.0F, 1F));
  }

  public void select()
  {
    this.transform.Find("grid").gameObject.renderer.material.SetFloat("_LineWidth", 0.02f);
    this.transform.Find("plane").gameObject.renderer.enabled = true;
    this.transform.Find("grid").gameObject.renderer.material.SetColor("_GridColor", new Color(1F, 1F, 1F, 0.0F));
    this.transform.Find("grid").gameObject.renderer.material.SetColor("_LineColor", new Color(0.1F, 0.9F, 0.0F, 1F));
    selected = true;
  }

  public void unselect()
  {
    selected = false;
    this.transform.Find("plane").gameObject.renderer.enabled = false;
    this.transform.Find("grid").gameObject.renderer.material.SetFloat("_LineWidth", 0.02f);
    this.transform.Find("grid").gameObject.renderer.material.SetColor("_GridColor", new Color(0F, 0F, 0F, 0.0F));
    this.transform.Find("grid").gameObject.renderer.material.SetColor("_LineColor", new Color(0F, 0F, 0F, 1F));
  }


  void OnMouseExit()
  {
    if (!selected)
    {
      this.transform.Find("plane").gameObject.renderer.enabled = false;
      this.transform.Find("grid").gameObject.renderer.material.SetFloat("_LineWidth", 0.02f);
      this.transform.Find("grid").gameObject.renderer.material.SetColor("_GridColor", new Color(0F, 0F, 0F, 0F));
      this.transform.Find("grid").gameObject.renderer.material.SetColor("_LineColor", new Color(0F, 0F, 0F, 1F));
    }
  }

  public int[] getRessources()
  {
    return this.ressources;
  }

  public void setX(int val)
  {
    this.x = val;
  }

  public void setY(int val)
  {
    this.y = val;
  }

  public int getX()
  {
    return this.x;
  }

  public int getY()
  {
    return this.y;
  }

  public Vector3 getAvailablePosition()
  {
    if (pos1 == 0)
      return positions[0].position;
    else if (pos2 == null)
      return positions[1].position;
    else if (pos3 == null)
      return positions[2].position;
    else if (pos4 == null)
      return positions[3].position;
    else if (pos5 == null)
      return positions[4].position;
    else if (pos6 == null)
      return positions[5].position;
    else if (pos7 == null)
      return positions[6].position;
    else if (pos8 == null)
      return positions[7].position;
    else if (pos9 == null)
      return positions[8].position;
    else
      return positions[0].position;
  }

  public void playerEnter(GameObject player)
  {
    if (pos1 == 0)
      pos1 = 1;
    else if (pos2 == null)
      pos2 = player;
    else if (pos3 == null)
      pos3 = player;
    else if (pos4 == null)
      pos4 = player;
    else if (pos5 == null)
      pos5 = player;
    else if (pos6 == null)
      pos6 = player;
    else if (pos7 == null)
      pos7 = player;
    else if (pos8 == null)
      pos8 = player;
    else if (pos9 == null)
      pos9 = player;
    else
      pos1++;
  }

  public void playerExit(GameObject player)
  {
    if (pos2 == player)
      pos2 = null;
    else if (pos3 == player)
      pos3 = null;
    else if (pos4 == player)
      pos4 = null;
    else if (pos5 == player)
      pos5 = null;
    else if (pos6 == player)
      pos6 = null;
    else if (pos7 == player)
      pos7 = null;
    else if (pos8 == player)
      pos8 = null;
    else if (pos9 == player)
      pos9 = null;
    else
      pos1--;
  }

  public void startIncantation(int lvl)
  {
    this.lvlIncantation = lvl;
    ps1.enableEmission = true;
    ps2.enableEmission = true;
  }

  public void stopIncantation()
  {
    ps1.enableEmission = false;
    ps2.enableEmission = false;

    Debug.Log("Incantation end lvl : " + this.lvlIncantation);

    if (this.lvlIncantation == 1)
    {
      Instantiate(linematePart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);
    }
    else if (this.lvlIncantation == 2)
    {
      Instantiate(linematePart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);

      Instantiate(deraumerePart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);

      Instantiate(siburPart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);
    }
    else if (this.lvlIncantation == 3)
    {
      Instantiate(linematePart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);
      Instantiate(linematePart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);

      Instantiate(siburPart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);

      Instantiate(phyrasPart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);
      Instantiate(phyrasPart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);
    }
    else if (this.lvlIncantation == 4)
    {
      Instantiate(linematePart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);

      Instantiate(deraumerePart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);

      Instantiate(siburPart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);
      Instantiate(siburPart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);

      Instantiate(phyrasPart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);
    }
    else if (this.lvlIncantation == 5)
    {
      Instantiate(linematePart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);

      Instantiate(deraumerePart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);
      Instantiate(deraumerePart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);

      Instantiate(siburPart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);

      Instantiate(mendianePart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);
      Instantiate(mendianePart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);
      Instantiate(mendianePart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);
    }
    else if (this.lvlIncantation == 6)
    {
      Instantiate(linematePart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);

      Instantiate(deraumerePart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);
      Instantiate(deraumerePart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);

      Instantiate(siburPart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);
      Instantiate(siburPart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);
      Instantiate(siburPart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);

      Instantiate(phyrasPart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);
    }
    else if (this.lvlIncantation == 7)
    {
      Instantiate(linematePart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);
      Instantiate(linematePart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);

      Instantiate(deraumerePart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);
      Instantiate(deraumerePart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);

      Instantiate(siburPart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);
      Instantiate(siburPart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);

      Instantiate(mendianePart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);
      Instantiate(mendianePart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);

      Instantiate(phyrasPart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);
      Instantiate(phyrasPart, new Vector3(this.transform.position.x, 0.6f, this.transform.position.z), Quaternion.identity);
    }
  }

  public Vector3 getTpNorth()
  {
    return this.tp_north.position;
  }

  public Vector3 getTpSouth()
  {
    return this.tp_south.position;
  }

  public Vector3 getTpWest()
  {
    return this.tp_west.position;
  }

  public Vector3 getTpEast()
  {
    return this.tp_east.position;
  }
}
