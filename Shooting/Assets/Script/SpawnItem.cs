using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnItem : MonoBehaviour {
    public GameObject item;
    private void ItemSpawn()
    {
        float x = Random.Range(-74, 79);
        Instantiate(item, new Vector3(x, 330, 0), Quaternion.identity);
    }
	void Start () {
        InvokeRepeating("ItemSpawn", 20, Random.Range(15, 28));
	}
}
