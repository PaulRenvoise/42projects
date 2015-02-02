using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class MapGeneration : MonoBehaviour {

  public GameObject cubeMap;
  public Transform center;
  public int width = 10;
  public int height = 10;
  private List<List<GameObject>> cubes = new List<List<GameObject>>();

	// Use this for initialization

	public void generate(int w, int h)
  {
      this.width = w;
      this.height = h;

      center.Translate(new Vector3(width/2, 0, height / 2));

      for(int i = 0; i < height ; i++)
      {
        List<GameObject> line = new List<GameObject>();
        this.cubes.Add(line);
        for(int j = 0; j < width ; j++)
        {
          GameObject cube = Instantiate(cubeMap, new Vector3(j, 0, i), Quaternion.identity) as GameObject;
          line.Add(cube);
          cube.GetComponent<CubeMap>().setX(j);
          cube.GetComponent<CubeMap>().setY(i);
        }
      }
      StartCoroutine(annimeCubes());
	}

  IEnumerator annimeCubes()
  {
    for(int i = 0; i < height ; i++)
    {
      for(int j = 0; j < width ; j++)
      {
        cubes[i][j].GetComponent<CubeMap>().moveUp();
        yield return StartCoroutine(MyDelayMethod(0.005f));
      }
    }
  }

  IEnumerator MyDelayMethod(float delay)
  {
      yield return new WaitForSeconds(delay);
  }

	// Update is called once per frame
	void Update () {

	}

  public void startIncantation(int x, int y, int lvl)
  {
    cubes[y][x].GetComponent<CubeMap>().startIncantation(lvl);
  }

  public void stopIncantation(int x, int y)
  {
    cubes[y][x].GetComponent<CubeMap>().stopIncantation();
  }

  public void updateRessources(int x, int y, int[] ressources)
  {
    cubes[y][x].GetComponent<CubeMap>().updateRessources(ressources);
  }

  public CubeMap getCaseAt(int x, int y)
  {
    return cubes[y][x].GetComponent<CubeMap>();
  }

  public GameObject getCubeAt(int x, int y)
  {
    return cubes[y][x];
  }

  public int getWidth()
  {
    return this.width;
  }

  public int getHeight()
  {
    return this.height;
  }


}
