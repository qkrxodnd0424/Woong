using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Missile : MonoBehaviour {
    public GameObject[] missile;
    public float fps = 1;
    [HideInInspector]
    public static int level = 0;
    public static int damage = 25;
	// Use this for initialization
	void Start () {
        StartCoroutine(FireMissile());
        SoundManager.instance.mSound();
    }
    IEnumerator FireMissile()
    {
        while(true)
        {
            Instantiate(missile[level], new Vector3(transform.position.x,transform.position.y+20), Quaternion.identity);
            SoundManager.instance.mSound();
            yield return new WaitForSeconds(1 / fps);
        }
    }
}
