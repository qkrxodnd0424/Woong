using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Meteo : MonoBehaviour {
    public float Speed;

    void Update()
    {
        transform.position += transform.rotation * Vector3.down * Time.deltaTime * Speed;
        if (transform.position.y <= -250)
        {
            Destroy(gameObject);
        }
    }
}
