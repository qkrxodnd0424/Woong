using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnMeteo : MonoBehaviour {
    public GameObject meteo;
    public GameObject line;
    public GameObject line1;
    public GameObject laser;
    private void MeteoSpawn()
    {
        float x = Random.Range(-70, 70);
        float x1 = Random.Range(-70, 70);
        float x2 = Random.Range(-70, 70);
        StartCoroutine(meteo1(x, x1, x2));
    }
	void Start () {
        InvokeRepeating("MeteoSpawn", 5, 13);
	}
    IEnumerator meteo1(float x, float x1, float x2)
    {
        float random = Random.Range(1, 3);
        if (random == 1)
        {
            Instantiate(line, new Vector3(x, 330, 0), Quaternion.identity);
            yield return new WaitForSeconds(1.5f);
            SoundManager.instance.Laser();
            Instantiate(laser, new Vector3(x, 330, 0), Quaternion.identity);
        }
        else
        {
            float rand = Random.Range(1, 3);
            if (rand == 1)
            {
                Instantiate(line1, new Vector3(x, 330, 0), Quaternion.identity);
                yield return new WaitForSeconds(0.5f);
                Instantiate(line1, new Vector3(x1, 330, 0), Quaternion.identity);
                yield return new WaitForSeconds(0.5f);
                Instantiate(line1, new Vector3(x2, 330, 0), Quaternion.identity);
                Instantiate(meteo, new Vector3(x, 330, 0), Quaternion.identity);
                yield return new WaitForSeconds(0.5f);
                Instantiate(meteo, new Vector3(x1, 330, 0), Quaternion.identity);
                yield return new WaitForSeconds(0.5f);
                Instantiate(meteo, new Vector3(x2, 330, 0), Quaternion.identity);
            }
            else
            {
                Instantiate(line1, new Vector3(x, 330, 0), Quaternion.identity);
                yield return new WaitForSeconds(1.5f);
                Instantiate(meteo, new Vector3(x, 330, 0), Quaternion.identity);
            }
        }
    }
}
