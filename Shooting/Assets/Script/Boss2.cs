using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Boss2 : MonoBehaviour
{
    private int patternNum; //패턴 넘버 어떤패턴을 쓸까
    private int HP = 7000;  //HP
    private float Speed = 35.0f; //보스 이동 스피드
    private float Speed1 = 15.0f; //보스이동 시피트 2
    float lastShootTime; //마지막으로 패턴이 써진시간
    public Transform[] point; //미사일이 날라갈 장소
    public GameObject missile1; //미사일 1
    public GameObject missile2; //미사일 2
    public GameObject missile3; //미사일 3

    void Update()
    {
        Move();
        MoveClamp();
        Pattern();
        End();
        if (HP < 0)
        {//보스피가 0보다 적어지면
            StartCoroutine(End1());
        }
    }

    void Pattern()
    {
        if (Time.time > lastShootTime + 1.5f) //일정시간이 지나면 패턴실행
        {
            lastShootTime = Time.time;
            patternNum = 1;
            StartCoroutine(attack(patternNum)); //코루틴을 실행한다.
        }
    }

    IEnumerator attack(int p) //코루틴
    {
        if (p == 1 || p == 6) // 1번
        {
            for (int j = 0; j < 3; j++)
            {
                for (int i = 175; i < 200; i += 5)
                {
                    Instantiate(missile1, point[0].transform.position, Quaternion.Euler(0, 0, i));
                    Instantiate(missile1, point[2].transform.position, Quaternion.Euler(0, 0, i));
                    yield return new WaitForSeconds(2f);
                }
            }
        }
        if (p == 2 || p == 7) //2번
        {
            for (int a = 0; a < 5; a++)
            {
                for (int i = 180; i < 240; i += 5)
                {
                    Instantiate(missile2, point[1].transform.position, Quaternion.Euler(0, 0, i));


                    yield return new WaitForSeconds(1f);
                }
            }
        }
        if (p == 3 || p == 8)  //3번
        {
            for (int i = 0; i < 3; i++)
            {
                //Instantiate(missile3, point[1].transform.position, point[1].transform.rotation);
                Instantiate(missile3, point[0].transform.position, Quaternion.Euler(0, 0, 200));
                Instantiate(missile3, point[1].transform.position, Quaternion.Euler(0, 0, 180));
                Instantiate(missile3, point[2].transform.position, Quaternion.Euler(0, 0, 160));
                yield return new WaitForSeconds(0.35f);
            }
        }
        if (p == 4 || p == 9) //4번
        {
            for (int b = 90; b < 240; b += 10)
            {
                for (int i = 0; i < 1; i++)
                {
                    Instantiate(missile1, point[1].transform.position, Quaternion.Euler(0, 0, b));
                    yield return new WaitForSeconds(0.2f);
                }
            }
        }
        if (p == 5 || p == 10) // 5번
        {
            for (int j = 0; j < 3; j++)
            {
                for (int i = 0; i < 3; i++)
                {
                    Instantiate(missile2, point[0].transform.position, Quaternion.Euler(0, 0, 180));
                    Instantiate(missile2, point[2].transform.position, Quaternion.Euler(0, 0, 180));
                    Instantiate(missile2, point[1].transform.position, Quaternion.Euler(0, 0, 180));
                    yield return new WaitForSeconds(0.5f);
                }
            }
        }
        if (p == 11 || p == 12) //6번
        {
            for (int r = 0; r < 3; r++)
                for (int z = 90; z < 280; z += 10)
                {
                    Instantiate(missile1, point[1].transform.position, Quaternion.Euler(0, 0, z));
                    yield return new WaitForSeconds(0.2f);
                }
        }
    }

    private void OnTriggerEnter2D(Collider2D col)
    {
        if (col.CompareTag("PlayerMissile"))
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
        if (Input.GetKey(KeyCode.UpArrow))
            transform.Translate(Vector3.up * Speed1 * Time.deltaTime);
        if (Input.GetKey(KeyCode.DownArrow))
            transform.Translate(Vector3.down * (Speed1 - 4.0f) * Time.deltaTime);

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
            Player.HP = 1;
            Player.Speed = 200.0f;
            SceneManager.LoadScene("Start");
        }
    }
    IEnumerator End1()
    {
        yield return new WaitForSeconds(3.0f);
        Destroy(gameObject);
        SceneManager.LoadScene("Start");
    }
}