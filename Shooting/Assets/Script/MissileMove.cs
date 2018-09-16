using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MissileMove : MonoBehaviour {
    public float Speed;
    public float DestroyY;
	
	void Update () {
        transform.position += transform.rotation * Vector3.up * Time.deltaTime * Speed;
        if (transform.position.y > DestroyY)
            Destroy(gameObject);
	}

    private void OnTriggerEnter2D(Collider2D col)
    {
        if (col.CompareTag("Enemy"))
            Destroy(gameObject);
        if (col.CompareTag("Boss"))
            Destroy(gameObject);
    }

}
