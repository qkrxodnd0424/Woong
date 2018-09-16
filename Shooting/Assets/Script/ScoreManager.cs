using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScoreManager : MonoBehaviour {
    public Text scoreText;

	void Update () {
        scoreText.text = Enemy.Score.ToString();
	}
}
