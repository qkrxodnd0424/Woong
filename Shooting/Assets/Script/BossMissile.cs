﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BossMissile : MonoBehaviour
{
    public float Speed;

    void Update()
    {
        transform.position += transform.rotation * Vector3.up * Time.deltaTime * Speed;
        if (transform.position.y > 210)
            Destroy(gameObject);
        if (transform.position.y < -210)
            Destroy(gameObject);
        if (transform.position.x > 106)
            Destroy(gameObject);
        if (transform.position.x < -106)
            Destroy(gameObject);
    }

    private void OnTriggerEnter2D(Collider2D col)
    {
        if (col.CompareTag("Player"))
            Destroy(gameObject);
    }
}
