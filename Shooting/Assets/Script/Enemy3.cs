using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy3 : MonoBehaviour {
    public float Speed;
    public GameObject missile;
    private int Num;
    private void Start()
    {
        StartCoroutine(ShootMissile());
    }
    void Update()
    {
        transform.position += transform.rotation * Vector3.left * Time.deltaTime * Speed;
        if (transform.position.x < -100)
        {
            Destroy(gameObject);
        }
    }
    IEnumerator ShootMissile()
    {
        while(true)
        {
            Num = Random.Range(1, 4);
            yield return new WaitForSeconds(0.7f);
            if (Num == 1)
            {
                Instantiate(missile, transform.position, Quaternion.identity);
            }
            if(Num == 2)
            {
                Instantiate(missile, transform.position, Quaternion.Euler(0, 0, 35));
                Instantiate(missile, transform.position, Quaternion.identity);
                Instantiate(missile, transform.position, Quaternion.Euler(0, 0, -35));
            }
            if(Num==3)
            {
                for (int i = 0; i < 361; i += 15)
                {
                    Instantiate(missile, transform.position, Quaternion.Euler(0, 0, i));
                    yield return new WaitForSeconds(0.01f);
                }
            }
        }
    }
}
