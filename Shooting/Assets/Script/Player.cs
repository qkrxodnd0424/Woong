using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Player : MonoBehaviour {
    public GameObject effect;
    public GameObject missile;
    public static float Speed = 200.0f;
    public static int HP = 20;
    public static float pos;

	void Start () {
	}
	void Update () {
        Move();
        MoveClamp();
        if (HP <= 0)
        {
            Instantiate(effect, transform.position, transform.rotation);
            SoundManager.instance.Boom();
            Destroy(gameObject);
        }
    }
   
    private void Move()
    {
        if (Input.GetKey(KeyCode.RightArrow))
            transform.Translate(Vector3.right * Speed * Time.deltaTime);
        if (Input.GetKey(KeyCode.LeftArrow))
            transform.Translate(Vector3.left * Speed * Time.deltaTime);
        if (Input.GetKey(KeyCode.UpArrow))
            transform.Translate(Vector3.up * Speed * Time.deltaTime);
        if (Input.GetKey(KeyCode.DownArrow))
            transform.Translate(Vector3.down * Speed * Time.deltaTime);
        pos = transform.position.x;
    }
    private void MoveClamp()
    {
        Vector3 left = Camera.main.ViewportToScreenPoint(new Vector3(0, 0));
        Vector3 right = Camera.main.ViewportToScreenPoint(new Vector3(1, 1));
        Vector3 player = transform.position;

        player.x = Mathf.Clamp(player.x, left.x - 100, right.x - 1820);
        player.y = Mathf.Clamp(player.y, left.y - 220, right.y - 700);

        transform.position = player;
    }
    private void OnTriggerEnter2D(Collider2D col)
    {
        if (col.CompareTag("Enemy"))
            HP--;
        if (col.CompareTag("Meteo"))
            HP--;
        if (col.CompareTag("Missile"))
            HP--;
        if (col.CompareTag("Item"))
        {
            if (HP <= 5)
                HP++;
        }
        if (col.CompareTag("Item1"))
        {
            if (Missile.level < 12)
            {
                Missile.level += 1;
                Missile.damage += Random.Range(14, 18);
            }
        } 
    }
    IEnumerator SpeedUp()
    {
        Speed += 30.0f;
        yield return new WaitForSeconds(5.0f);
        Speed -= 30.0f;
    }
    IEnumerator Scene()
    {
        yield return new WaitForSeconds(3.0f);
        SceneManager.LoadScene("Start");
    }
}
