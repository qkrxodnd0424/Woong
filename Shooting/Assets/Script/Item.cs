using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Item : MonoBehaviour {
    private float Speed = 180.0f;

	void Update () {
        transform.position += transform.rotation * Vector3.down * Time.deltaTime * Speed;
        if (transform.position.y < -250)
            Destroy(gameObject);
	}

    private void OnTriggerEnter2D(Collider2D col)
    {
        if (col.CompareTag("Player"))
            Destroy(gameObject);
    }
}
