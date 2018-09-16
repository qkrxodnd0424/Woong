using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class HpManager : MonoBehaviour {
    public Text hpText;

    void Update()
    {
        hpText.text = "HP : " + Player.HP.ToString();

    }
}
