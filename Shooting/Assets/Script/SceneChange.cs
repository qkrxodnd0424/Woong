using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
public class SceneChange : MonoBehaviour {
    public void goStore()
    {
        SceneManager.LoadScene("Store");
    }
    public void goMain()
    {
        SceneManager.LoadScene("Start");
    }
    public void goStage1()
    {
        SceneManager.LoadScene("Stage1");
    }
    public void goStage2()
    {
        SceneManager.LoadScene("Stage2");
    }
}
