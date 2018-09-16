using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class Enemy : MonoBehaviour
{
    public static float Speed = 230.0f;
    public static int HP1 = 70;
    public int HP = 150;
    public static int MaxScore = 1000;
    public static int MaxScore1 = 1000;
    public static int itemScore = 3000;
    public GameObject mItem;
    [HideInInspector]
    public static int Score = 0;
    public static int Gold = 50000;

    void Start()
    {
        HP = HP1;
        Debug.Log(HP);   
    }

    void Update()
    {
        Move();
        MissileUp();
        Check();
        DestroyEnemy();       
    }

    private void OnTriggerEnter2D(Collider2D col)
    {
        if (col.CompareTag("PlayerMissile"))
        {
            HP -= Missile.damage;
            Debug.Log(HP);
        }
    }
    private void DestroyEnemy()
    {
        if (HP <= 0)
        {
            SoundManager.instance.die1();
            Destroy(gameObject);
            Gold += Random.Range(40, 60);
            Score += Random.Range(1500, 4000);
        }
    }
    private void Move()
    {
        transform.position += transform.rotation * Vector3.down * Time.deltaTime * Speed;
        if (transform.position.y <= -250)
            Destroy(gameObject);
    }

    private void Check()
    {
        if (Score > MaxScore1)
        {          
            HP1 += Random.Range(40, 60);
            Speed += 15.0f;
            MaxScore1 += 1000;
        }     
    }
    void MissileUp()
    {
        if(Score > MaxScore)
        {
            if (Missile.level < 7)
            {
                float x = Random.Range(-74, 79);
                Instantiate(mItem, new Vector3(x, 330, 0), Quaternion.identity);
                MaxScore += 1300;
            }
        }
    }
}
