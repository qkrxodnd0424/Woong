using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class GoldManager : MonoBehaviour {
    public Text goldText;

	void Update () {
        goldText.text = Enemy.Gold.ToString();
	}
}
