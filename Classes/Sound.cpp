//
//  Sound.cpp
//  PopoHit
//
//  Created by Pham Thanh on 4/12/16.
//
//

#include "Sound.hpp"

Sound* Sound::_instance = nullptr;

Sound* Sound::getInstance()
{
    if (!_instance)
    {
        _instance = new Sound;
    }
    return _instance;
}

void Sound::init()
{
    preloadBackgroundMusic("sound/sd_bg_play.mp3");
    preloadBackgroundMusic("sound/sd_menu_bg.mp3");
    preloadBackgroundMusic("sound/game_music.mp3");
    preloadBackgroundMusic("sound/game_pass.mp3");
    preloadBackgroundMusic("sound/no_hit.mp3");
    preloadBackgroundMusic("sound/over_music.mp3");
}

void Sound::playMenuBackground()
{
    if (readBoolXML(MUSIC))
    {
        if (isBackground())
        {
            stopBackground();
        }
        playBackgroundMusic("sound/game_music.mp3",true);
    }
}

void Sound::playGameBackground()
{
    if (readBoolXML(MUSIC))
    {
        if (isBackground())
        {
            stopBackground();
        }
        playBackgroundMusic("sound/game_music.mp3", true);
    }
}

void Sound::playAttack()
{
    if (readBoolXML(MUSIC))
    {
        playEffect("sound/no_hit.mp3");
    }
}

void Sound::playBtn()
{

    if (readBoolXML(MUSIC))
    {
        playEffect("sound/second_music.mp3");
    }
}

void Sound::playDead()
{
    if (readBoolXML(MUSIC))
    {
        playEffect("sound/no_hit.mp3");
    }
}


bool Sound::isBackground()
{
    return SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying();
}

void Sound::stopBackground()
{
    if (isBackground())
    {
        SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    }
}
void Sound::playGamePass() {
    if (readBoolXML(MUSIC))
    {
        playEffect("sound/game_pass.mp3");
    }
}
void Sound::playGameOver() {
    if (readBoolXML(MUSIC))
    {
        playEffect("sound/over_music.mp3");
    }
}
void Sound::UnInit()
{
    unloadEffect("sound/sd_menu_bg.mp3");
    unloadEffect("sound/game_music.mp3");
    unloadEffect("sound/game_pass.mp3");
    unloadEffect("sound/no_hit.mp3");
    unloadEffect("sound/over_music.mp3");
    unloadEffect("sound/sd_bg_play.mp3");
}

