using UnityEngine;
using System.Collections;

public class Egg : MonoBehaviour {

    public int id;

    public GameObject cube;
    private int teamId;

    private string team;

    public float lifeTime = 5.0f;
    public float moveTime = 1.0f;
    public bool moving = false;

    private bool moisie = false;

    void Start ()
    {
      this.transform.Find("model2").gameObject.renderer.enabled = false;
      this.transform.Find("model3").gameObject.renderer.enabled = false;
    }

    // Update is called once per frame
    void Update ()
    {
      float distance = Vector3.Distance(Camera.main.transform.position, this.transform.position);
      this.transform.Find("model").gameObject.renderer.material.SetFloat("_Outline", 0.015f / distance);
      this.transform.Find("model2").gameObject.renderer.material.SetFloat("_Outline", 0.015f / distance);
      this.transform.Find("model3").gameObject.renderer.material.SetFloat("_Outline", 0.015f / distance);

      if (moisie)
      {
        lifeTime -= Time.deltaTime;
        if (lifeTime <= 0.0f)
        {
          moving = true;
        }
        if (moving)
        {
          moveTime -= Time.deltaTime;
          this.transform.Translate(new Vector3(0, -0.25f * Time.deltaTime, 0));
          if (moveTime <= 0.0f)
          {
            cube.GetComponent<CubeMap>().playerExit(this.gameObject);
            Destroy(this.gameObject);
          }
        }
      }

    }

    public void setColor(int nbr)
    {
      this.teamId = nbr;
      //texture color
      if (nbr % 8 == 0)
      {
        this.transform.Find("model").gameObject.renderer.material.SetColor("_Color", new Color(1, 0.65f, 0.65f, 1));
        this.transform.Find("model2").gameObject.renderer.material.SetColor("_Color", new Color(1, 0.65f, 0.65f, 1));
        this.transform.Find("model3").gameObject.renderer.material.SetColor("_Color", new Color(1, 0.65f, 0.65f, 1));
      }
      else if (nbr % 8 == 1)
      {
        this.transform.Find("model").gameObject.renderer.material.SetColor("_Color", new Color(1, 0.1f, 0.9f, 1));
        this.transform.Find("model2").gameObject.renderer.material.SetColor("_Color", new Color(1, 0.1f, 0.9f, 1));
        this.transform.Find("model3").gameObject.renderer.material.SetColor("_Color", new Color(1, 0.1f, 0.9f, 1));
      }
      else if (nbr % 8 == 2)
      {
        this.transform.Find("model").gameObject.renderer.material.SetColor("_Color", new Color(0.15f, 0.85f, 0.15f, 1));
        this.transform.Find("model2").gameObject.renderer.material.SetColor("_Color", new Color(0.15f, 0.85f, 0.15f, 1));
        this.transform.Find("model3").gameObject.renderer.material.SetColor("_Color", new Color(0.15f, 0.85f, 0.15f, 1));
      }
      else if (nbr % 8 == 3)
      {
        this.transform.Find("model").gameObject.renderer.material.SetColor("_Color", new Color(0.95f, 0.7f, 0.2f, 1));
        this.transform.Find("model2").gameObject.renderer.material.SetColor("_Color", new Color(0.95f, 0.7f, 0.2f, 1));
        this.transform.Find("model3").gameObject.renderer.material.SetColor("_Color", new Color(0.95f, 0.7f, 0.2f, 1));
      }
      else if (nbr % 8 == 4)
      {
        this.transform.Find("model").gameObject.renderer.material.SetColor("_Color", new Color(0.3f, 0.9f, 1, 1));
        this.transform.Find("model2").gameObject.renderer.material.SetColor("_Color", new Color(0.3f, 0.9f, 1, 1));
        this.transform.Find("model3").gameObject.renderer.material.SetColor("_Color", new Color(0.3f, 0.9f, 1, 1));
      }
      else if (nbr % 8 == 5)
      {
        this.transform.Find("model").gameObject.renderer.material.SetColor("_Color", new Color(0.8f, 0.7f, 1, 1));
        this.transform.Find("model2").gameObject.renderer.material.SetColor("_Color", new Color(0.8f, 0.7f, 1, 1));
        this.transform.Find("model3").gameObject.renderer.material.SetColor("_Color", new Color(0.8f, 0.7f, 1, 1));
      }
      else if (nbr % 8 == 6)
      {
        this.transform.Find("model").gameObject.renderer.material.SetColor("_Color", new Color(1f, 0.95f, 0.9f, 1));
        this.transform.Find("model2").gameObject.renderer.material.SetColor("_Color", new Color(1f, 0.95f, 0.9f, 1));
        this.transform.Find("model3").gameObject.renderer.material.SetColor("_Color", new Color(1f, 0.95f, 0.9f, 1));
      }
      else if (nbr % 8 == 7)
      {
        this.transform.Find("model").gameObject.renderer.material.SetColor("_Color", new Color(0.1f, 0.1f, 0.1f, 1));
        this.transform.Find("model2").gameObject.renderer.material.SetColor("_Color", new Color(0.1f, 0.1f, 0.1f, 1));
        this.transform.Find("model3").gameObject.renderer.material.SetColor("_Color", new Color(0.1f, 0.1f, 0.1f, 1));
      }
    }

    public void select()
    {
      this.transform.Find("model").gameObject.renderer.material.SetColor("_OutlineColor", new Color(0.1F, 0.9F, 0.0F, 1F));
      this.transform.Find("model2").gameObject.renderer.material.SetColor("_OutlineColor", new Color(0.1F, 0.9F, 0.0F, 1F));
      this.transform.Find("model3").gameObject.renderer.material.SetColor("_OutlineColor", new Color(0.1F, 0.9F, 0.0F, 1F));
    }

    public void unselect()
    {
      this.transform.Find("model").gameObject.renderer.material.SetColor("_OutlineColor", new Color(0F, 0F, 0F, 1F));
      this.transform.Find("model2").gameObject.renderer.material.SetColor("_OutlineColor", new Color(0F, 0F, 0F, 1F));
      this.transform.Find("model3").gameObject.renderer.material.SetColor("_OutlineColor", new Color(0F, 0F, 0F, 1F));
    }

    public void setId(int val)
    {
      this.id = val;
    }

    public int getId()
    {
      return this.id;
    }

    public void setCube(GameObject cb)
    {
      this.cube = cb;
    }

    public GameObject getCube()
    {
      return this.cube;
    }

    public int getTeamId()
    {
      return this.teamId;
    }

    public void setTeam(string name)
    {
      this.team = name;
    }

    public string getTeam()
    {
      return this.team;
    }

    public void eclore()
    {
      this.transform.Find("model").gameObject.renderer.enabled = false;
      this.transform.Find("model2").gameObject.renderer.enabled = true;
      this.transform.Find("model3").gameObject.renderer.enabled = true;
    }

    public void moisir()
    {
      this.transform.Find("model2").gameObject.renderer.material.SetColor("_Color", Color.grey);
      this.transform.Find("model3").gameObject.renderer.material.SetColor("_Color", Color.grey);
      this.moisie = true;
    }
}
