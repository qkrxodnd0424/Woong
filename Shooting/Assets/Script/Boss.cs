using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Boss : MonoBehaviour {
    private int patternNum;
    private int HP = 12000;
    private float Speed = 35.0f;
    private float Speed1 = 15.0f;
    float lastShootTime;
    public GameObject boss2;
    public GameObject Warning;
    public Transform[] point;
    public GameObject missile1;
    public GameObject missile2;
    public GameObject missile3;

    void Update () {
        Move();
        MoveClamp();
        Pattern();
        End();
        if (HP < 0)
        {
            Enemy.Score += 15000;
            Destroy(gameObject);
        }
	}

    void Pattern()
    {
        if(Time.time > lastShootTime + 0.7f)
        {
            lastShootTime = Time.time;
            patternNum = Random.Range(1, 13);
            StartCoroutine(attack(patternNum));
        }
    }
    
    IEnumerator attack(int p)
    {
        if (p == 1 || p == 6)
        {
            for (int j = 0; j < 5; j++)
            {
                for (int i = 0; i < 361; i += 10)
                {
                    /*Instantiate(missile1, point[0].transform.position, point[0].transform.rotation);
                    Instantiate(missile1, point[0].transform.position, Quaternion.Euler(0, 0, 35));
                    Instantiate(missile1, point[0].transform.position, Quaternion.Euler(0, 0, -35));
                    Instantiate(missile1, point[2].transform.position, point[2].transform.rotation);
                    Instantiate(missile1, point[2].transform.position, Quaternion.Euler(0, 0, 35));
                    Instantiate(missile1, point[2].transform.position, Quaternion.Euler(0, 0, -35));*/
                    Instantiate(missile1, point[0].transform.position, Quaternion.Euler(0, 0, i));
                    Instantiate(missile2, point[2].transform.position, Quaternion.Euler(0, 0, i));
                    yield return new WaitForSeconds(0.05f);
                }
            }
        }
        if (p == 2 || p == 7)
        {    
            for (int i = 0; i < 5; i++)
            {
                Instantiate(missile2, point[0].transform.position, point[0].transform.rotation);
                Instantiate(missile2, point[0].transform.position, Quaternion.Euler(0, 0, 35));
                Instantiate(missile2, point[0].transform.position, Quaternion.Euler(0, 0, -35));
                Instantiate(missile2, point[2].transform.position, point[1].transform.rotation);
                Instantiate(missile2, point[2].transform.position, Quaternion.Euler(0, 0, 35));
                Instantiate(missile2, point[2].transform.position, Quaternion.Euler(0, 0, -35));
                yield return new WaitForSeconds(0.35f);
            }
        }
        if (p == 3 || p == 8)
        {
            for (int i = 0; i < 5; i++)
            {
                Instantiate(missile3, point[1].transform.position, point[1].transform.rotation);
                Instantiate(missile3, point[1].transform.position, Quaternion.Euler(0, 0, 35));
                Instantiate(missile3, point[1].transform.position, Quaternion.Euler(0, 0, -35));
                yield return new WaitForSeconds(0.35f);
            }
        }
        if (p == 4 || p == 9)
        {
            for (int i = 0; i < 5; i++)
            {
                Instantiate(missile1, point[1].transform.position, point[1].transform.rotation);
                Instantiate(missile2, point[1].transform.position, Quaternion.Euler(0, 0, 35));
                Instantiate(missile3, point[1].transform.position, Quaternion.Euler(0, 0, -35));
                Instantiate(missile1, point[2].transform.position, Quaternion.Euler(0, 0, -90));
                Instantiate(missile2, point[0].transform.position, Quaternion.Euler(0, 0, 90));
                yield return new WaitForSeconds(0.35f);
            }
        }
        if (p == 5 || p == 10)
        {
            for (int j = 0; j < 3; j++)
            {
                for (int i = 0; i < 5; i++)
                {
                    Instantiate(missile1, point[j].transform.position, point[j].transform.rotation);
                    Instantiate(missile1, point[j].transform.position, Quaternion.Euler(0, 0, 45));
                    Instantiate(missile1, point[j].transform.position, Quaternion.Euler(0, 0, -45));
                    Instantiate(missile1, point[j].transform.position, Quaternion.Euler(0, 0, 225));
                    Instantiate(missile1, point[j].transform.position, Quaternion.Euler(0, 0, -225));
                    yield return new WaitForSeconds(0.35f);
                }
            }
        }
        if (p == 11 || p == 12)
        {
            for (int i = 0; i < 361; i += 6)
            {
                Instantiate(missile1, point[1].transform.position, Quaternion.Euler(0, 0, i));
                yield return new WaitForSeconds(0.03f);
            }
        }
    }

    private void OnTriggerEnter2D(Collider2D col)
    {
        if(col.CompareTag("PlayerMissile"))
        {
            HP -= Missile.damage;
        }
    }
    private void Move()
    {
        if (Input.GetKey(KeyCode.RightArrow))
            transform.Translate(Vector3.left * Speed * Time.deltaTime);
        if (Input.GetKey(KeyCode.LeftArrow))
            transform.Translate(Vector3.right * Speed * Time.deltaTime);
 
    }
    private void MoveClamp()
    {
        Vector3 left = Camera.main.ViewportToScreenPoint(new Vector3(0, 0));
        Vector3 right = Camera.main.ViewportToScreenPoint(new Vector3(1, 1));
        Vector3 player = transform.position;

        player.x = Mathf.Clamp(player.x, left.x - 50, right.x - 1860);
        player.y = Mathf.Clamp(player.y, left.y - 220, right.y - 700);

        transform.position = player;
    }
    private void End()
    {
        if (GameObject.FindWithTag("Player") == null)
        {
            SpawnEnemy.spawn = true;
            Enemy.Score = 0;
            MoveBG.Speed = 0.28f;
            SpawnEnemy.maxScore = 10000;
            Enemy.Speed = 230.0f;
            Enemy.MaxScore = 1000;
            Enemy.MaxScore1 = 1000;
            Enemy.itemScore = 3000;
            Enemy.HP1 = 70;
            Missile.level = 0;
            Player.HP = 5;
            Player.Speed = 200.0f;
            SceneManager.LoadScene("Start");
        }
    }
}
