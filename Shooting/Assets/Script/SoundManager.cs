using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundManager : MonoBehaviour {
    public AudioClip missileSound;
    public AudioClip bgm;
    public AudioClip laser;
    public AudioClip boom;
    public AudioClip die;
    AudioSource mAudio;
    AudioSource bgmAudio;
    AudioSource laserAudio;
    AudioSource boomAudio;
    AudioSource dieAudio;

    public static SoundManager instance;
    private void Awake()
    {
        if (SoundManager.instance == null)
            SoundManager.instance = this;
    }
    private void Start()
    {
      
    }
    public void mSound()
    {
        mAudio = GetComponent<AudioSource>();
        mAudio.PlayOneShot(missileSound);
    }
    public void Bgm()
    {
        bgmAudio = GetComponent<AudioSource>();
        bgmAudio.volume = 0.1f;
        bgmAudio.PlayOneShot(bgm);
    }
    public void Laser()
    {
        laserAudio = GetComponent<AudioSource>();
        laserAudio.volume = 0.1f;
        laserAudio.PlayOneShot(laser);
    }
    public void Boom()
    {
        boomAudio = GetComponent<AudioSource>();
        boomAudio.volume = 0.1f;
        boomAudio.PlayOneShot(boom);
    }
    public void die1()
    {
        dieAudio = GetComponent<AudioSource>();
        dieAudio.PlayOneShot(die);
    }
}
