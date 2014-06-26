using UnityEngine;
using System.Collections;

public class Tomb : MonoBehaviour {

	// Use this for initialization

  public float lifeTime = 2.0f;
  public float moveTime = 1.0f;
  public GameObject cube;
  public bool moving = false;

	void Start ()
  {
    moving = false;
	}

	// Update is called once per frame
	void Update ()
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

  public void setCube(GameObject cb)
  {
    this.cube = cb;
  }

}
