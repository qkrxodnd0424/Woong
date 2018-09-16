using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MoveBG : MonoBehaviour {
    public GameObject Bg;
    public static float Speed = 0.28f;
    private float BgY = 0.0f;

	void Start () {
        StartCoroutine(BgSpeed());
        SoundManager.instance.Bgm();
    }
    private void Update()
    {
        BgY += Time.deltaTime * Speed;
        Bg.GetComponent<Renderer>().material.mainTextureOffset = new Vector2(0, BgY);
        if(Enemy.Score > 17000)
        {
            StartCoroutine(End());
        }
    }
    IEnumerator BgSpeed()
    {
        while(true)
        {
            yield return new WaitForSeconds(9.0f);
            Speed += 0.025f;
        }
    }
    IEnumerator End()
    {
        yield return new WaitForSeconds(2.0f);
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
        SceneManager.LoadScene("Start");
    }
}
