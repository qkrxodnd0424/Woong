using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RandomEnemy : MonoBehaviour {
    public GameObject Enemy;
    public GameObject enemy;
    private void EnemySpawn()
    {
        float y = Random.Range(110, 160);
            Instantiate(Enemy, new Vector3(100, y, 0), Quaternion.identity);
    }
    private void EnemySpawn1()
    {
        float y = Random.Range(110, 160);
        Instantiate(enemy, new Vector3(-100, y, 0), Quaternion.identity);
    }
    void Start()
    {
        InvokeRepeating("EnemySpawn", 13, Random.Range(15, 28));
        InvokeRepeating("EnemySpawn1", 7, Random.Range(10, 18));
    }
}
