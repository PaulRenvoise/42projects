using UnityEngine;
using System.Collections;

public class Client : MonoBehaviour {

	// Use this for initialization

  public int level;
  public int id;
  public int[] inventory = {-1, -1, -1, -1, -1, -1, -1};

  public Vector3 target;
  public Vector3 tp;
  public Vector3 tp_out;
  public bool hasTarget;
  public bool hasTp;

  public GameObject cube;

  public int orientation;

  public float msgDisplayTime = 10.0f;
  public float expulseDisplayTime = 2.0f;
  private float expulseTime;
  private float msgTime = 0f;
  private bool displayMsg = false;
  private bool displayExpulse = false;

  public GameObject bulle;
  public GameObject bulle2;
  public TextMesh frontText;
  public TextMesh frontText2;

  private float speed = 1.5f;
  private float speedRotation = 1.5f;
  public float baseSpeed = 1.4f;
  public float baseSpeedRotation = 1.5f;

  public bool taking = false;
  public float takingDisplayTime = 1.4f;
  public float takingTime;

  public float rotationDisplayTime = 1.4f;
  public float rotationTime;

  private int rotationDir = 0;

  private bool rotating = false;

  public Transform basin;

  public GameObject tomb;

  public Texture text1;
  public Texture text2;
  public Texture text3;
  public Texture text4;
  public Texture text5;
  public Texture text6;
  public Texture text7;
  public Texture text8;

  private Texture[] textures;

  private int teamId;

  private string team;

  private bool incantating;

  void Awake()
  {
    this.textures = new Texture[8];
    this.textures[0] = text1;
    this.textures[1] = text2;
    this.textures[2] = text3;
    this.textures[3] = text4;
    this.textures[4] = text5;
    this.textures[5] = text6;
    this.textures[6] = text7;
    this.textures[7] = text8;

	   this.transform.localScale = new Vector3(0.4f, 0.4f, 0.4f);
     this.level = 1;
     this.hasTarget = false;
     this.hasTp = false;
     this.displayMsg = false;
     this.displayExpulse= false;

     this.frontText.renderer.enabled  = false;
     this.bulle.renderer.enabled  = false;

     this.frontText2.renderer.enabled  = false;
     this.bulle2.renderer.enabled  = false;

     //animation["run"].speed = 2;
	}

  public void modifySpeed(int sp)
  {
    this.speed = (baseSpeed * sp) / 10.0f;
    this.speedRotation = (baseSpeedRotation * sp) / 10.0f;
    animation["run"].speed = (baseSpeed * sp) / 10.0f;
  }

	// Update is called once per frame
	void Update ()
  {
    float distance = Vector3.Distance(Camera.main.transform.position, this.transform.position);
    this.transform.Find("model").gameObject.renderer.material.SetFloat("_Outline", 0.015f / distance);

    if (this.hasTp)
    {
      if (this.transform.position != tp)
      {
        this.transform.position = Vector3.MoveTowards(this.transform.position, tp, speed * Time.deltaTime);
      }
      else if (this.hasTp)
      {
        this.hasTp = false;
        this.transform.position = tp_out;
      }
    }
    else if (this.hasTarget)
    {
      if (this.transform.position != target)
      {
        this.transform.position = Vector3.MoveTowards(this.transform.position, target, speed * Time.deltaTime);
      }
      else if (this.hasTarget)
      {
        this.hasTarget = false;
        animation.Play("idle");
      }
    }

    if (this.displayMsg)
    {
      if (msgTime > 0.0f)
      {
        msgTime -= Time.deltaTime * speed;
        if (msgTime <= 0.0f)
        {
          this.displayMsg = false;

          this.frontText.renderer.enabled  = false;
          this.bulle.renderer.enabled  = false;
        }
      }
    }

    if (this.displayExpulse)
    {
      if (expulseTime > 0.0f)
      {
        expulseTime -= Time.deltaTime * speed;
        if (expulseTime <= 0.0f)
        {
          this.displayExpulse = false;

          this.frontText2.renderer.enabled  = false;
          this.bulle2.renderer.enabled  = false;
        }
      }
    }

    if (taking)
    {
      takingTime -= Time.deltaTime * speed;
      if (takingTime > takingDisplayTime / 2)
      {
        this.basin.Rotate(new Vector3(0, 0, - 150 * Time.deltaTime * speed));
      }
      else if (takingTime > 0)
      {
        this.basin.Rotate(new Vector3(0, 0, 150 * Time.deltaTime * speed));
      }
      else
      {
        takingTime = 0;
        taking = false;
        animation.enabled = true;
      }
    }


    if (this.rotating)
    {
      if (rotationTime > 0.0f)
      {
        rotationTime -= Time.deltaTime * speed;

        this.transform.Rotate(new Vector3(0, rotationDir * speedRotation, 0));

        if (rotationTime <= 0.0f)
        {
          this.rotating = false;
          setOrientation(this.orientation);
        }
      }
    }

    if (this.incantating)
    {
      this.transform.Rotate(new Vector3(0, 1 * Time.deltaTime * 600, 0));
    }
	}

  public void setTexture(int nbr)
  {
    this.teamId = nbr;
    this.transform.Find("model").gameObject.renderer.material.SetTexture("_MainTex", textures[(nbr % 8)]);
  }

  public void levelUp()
  {
    this.incantating = false;
    setOrientation(this.orientation);
    this.level++;
    this.transform.localScale = new Vector3(this.transform.localScale.x + 0.05f,
                                            this.transform.localScale.y + 0.05f,
                                            this.transform.localScale.z + 0.05f );
  }

  public void setLevel(int lvl)
  {

    this.level = lvl;
    this.transform.localScale = new Vector3(this.transform.localScale.x + ((0.05f) * (lvl - 1)),
                                            this.transform.localScale.y + ((0.05f) * (lvl - 1)),
                                            this.transform.localScale.z + ((0.05f) * (lvl - 1)) );
  }

  public void setTarget(Vector3 t)
  {
    t = new Vector3(t.x , this.transform.position.y, t.z);
    this.target = t;
    this.hasTarget = true;
    animation.Play("run");
  }

  public void setTp(Vector3 t)
  {
    t = new Vector3(t.x, this.transform.position.y, t.z);
    this.tp = t;
    this.hasTp = true;
    animation.Play("run");
  }

  public void setTpOut(Vector3 t)
  {
    t = new Vector3(t.x, this.transform.position.y, t.z);
    this.tp_out = t;
  }

  public void setTeam(string name)
  {
    this.team = name;
  }

  public string getTeam()
  {
    return this.team;
  }

  public void select()
  {
    this.transform.Find("model").gameObject.renderer.material.SetColor("_OutlineColor", new Color(0.1F, 0.9F, 0.0F, 1F));
  }

  public void unselect()
  {
    this.transform.Find("model").gameObject.renderer.material.SetColor("_OutlineColor", new Color(0F, 0F, 0F, 1F));
  }

  public void setId(int val)
  {
    this.id = val;
  }

  public int getId()
  {
    return this.id;
  }

  public int getLevel()
  {
    return this.level;
  }

  public void setInventory(int[] inv)
  {
    this.inventory = inv;
  }

  public int[] getInventory()
  {
    return this.inventory;
  }

  public int getNourriture()
  {
    return this.inventory[0];
  }

  public void setCube(GameObject cb)
  {
    this.cube = cb;
  }

  public GameObject getCube()
  {
    return this.cube;
  }

  public void setOrientation(int or)
  {
    this.transform.rotation = Quaternion.identity;
    if (or == 2)
      this.transform.Rotate(new Vector3(0, 90, 0));
    else if (or == 3)
      this.transform.Rotate(new Vector3(0, 180, 0));
    else if (or == 4)
      this.transform.Rotate(new Vector3(0, 270, 0));
    this.orientation = or;
  }

  public void rotate(int or)
  {

    if (this.orientation == 1 && or == 2)
    {
      rotationDir = 1;
    }
    else if (this.orientation == 1 && or == 4)
    {
      rotationDir = -1;
    }
    else if (this.orientation == 2 && or == 1)
    {
      rotationDir = -1;
    }
    else if (this.orientation == 2 && or == 3)
    {
      rotationDir = 1;
    }
    else if (this.orientation == 3 && or == 2)
    {
      rotationDir = -1;
    }
    else if (this.orientation == 3 && or == 4)
    {
      rotationDir = 1;
    }
    else if (this.orientation == 4 && or == 3)
    {
      rotationDir = -1;
    }
    else if (this.orientation == 4 && or == 1)
    {
      rotationDir = 1;
    }


    rotationTime = rotationDisplayTime;
    this.rotating = true;
    this.orientation = or;
  }

  public int getOrientation()
  {
    return this.orientation;
  }

  public void sendMessage(string msg)
  {
    if (msg.Length > 11)
      msg = msg.Substring(0, 10) + "...";
    this.msgTime = this.msgDisplayTime;
    this.displayMsg = true;
    this.frontText.text = msg;
    this.frontText.renderer.enabled = true;
    this.bulle.renderer.enabled  = true;
  }

  public void takeRessource()
  {
    this.taking = true;
    takingTime = takingDisplayTime;
    animation.enabled = false;
  }

  public void die()
  {
    GameObject t;
    if (!hasTarget)
      t = Instantiate(tomb, this.transform.position, this.transform.rotation) as GameObject;
    else
      t = Instantiate(tomb, this.target, this.transform.rotation) as GameObject;

    cube.GetComponent<CubeMap>().playerExit(this.gameObject);
    cube.GetComponent<CubeMap>().playerEnter(t);
    t.GetComponent<Tomb>().setCube(cube);
    Destroy(this.gameObject);
  }

  public int getTeamId()
  {
    return this.teamId;
  }

  public void incantation()
  {
    this.incantating = true;
  }

  public void expulse()
  {
    this.expulseTime = this.expulseDisplayTime;
    this.displayExpulse = true;
    this.frontText2.renderer.enabled  = true;
    this.bulle2.renderer.enabled  = true;
  }

}
