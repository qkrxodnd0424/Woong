using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SpawnEnemy : MonoBehaviour {
    public GameObject[] enemy;
    public GameObject boss;
    public GameObject warning;
    public Transform[] position;
    public Transform[] position1;
    public Transform[] position2;
    public static bool spawn;
    public static int maxScore = 10000;
	void Start () {
        spawn = true; 
        StartCoroutine(EnemySpawn());
        StartCoroutine(SpawnEnemy2());
        StartCoroutine(SpawnEnemy3());
    }
    public IEnumerator EnemySpawn()
    {
        while (spawn)
        {
            yield return new WaitForSeconds(3.5f);
            if (GameObject.FindWithTag("Player") == null)
            {
                spawn = true;
                Enemy.Score = 0;
                MoveBG.Speed = 0.28f;
                SpawnEnemy.maxScore = 10000;
                Enemy.Speed = 230.0f;
                Enemy.MaxScore = 1000;
                Enemy.MaxScore1 = 1000;
                Enemy.itemScore = 3000;
                Enemy.HP1 = 80;
                Missile.level = 0;
                Player.HP = 5;
                Player.Speed = 200.0f;
                SceneManager.LoadScene("Start");
            }
                foreach (var t in position)
                    Instantiate(enemy[Random.Range(0, 2)], t.position, t.rotation);

            if (Enemy.Score > maxScore)
            {
               spawn = false;
               if (GameObject.FindWithTag("Boss") == null)
               {
                    yield return new WaitForSeconds(1.5f);
                    Instantiate(warning, new Vector3(0, 1.5f, 0), transform.rotation);
                    yield return new WaitForSeconds(3.5f);
                    Instantiate(boss, new Vector3(6.7f, 158.6f, 0), transform.rotation);
               }
            }      
        }
    }
    IEnumerator SpawnEnemy2()
    {
        while(spawn)
        {
            yield return new WaitForSeconds(15.5f);
            foreach (var t in position1)
                Instantiate(enemy[Random.Range(0, 2)], t.position, t.rotation);
        }
    }
    IEnumerator SpawnEnemy3()
    {
        while(spawn)
        {
            yield return new WaitForSeconds(4.5f);
            foreach (var t in position2)
                Instantiate(enemy[Random.Range(0, 2)], t.position, t.rotation);
        }
    }
}
