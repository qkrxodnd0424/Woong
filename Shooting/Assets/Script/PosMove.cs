using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PosMove : MonoBehaviour {
    private float Speed = 35.0f;
	// Use this for initialization
	void Start () {
        if (Input.GetKey(KeyCode.RightArrow))
            transform.Translate(Vector3.right * Speed * Time.deltaTime);
        if (Input.GetKey(KeyCode.LeftArrow))
            transform.Translate(Vector3.left * Speed * Time.deltaTime);
    }
	
	// Update is called once per frame
	void Update () {
		
	}
}
