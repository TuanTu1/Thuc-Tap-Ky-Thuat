#pragma once 
#include "SDL_mixer.h"
#include <string>
#include <map>
#include "Singleton.h"

class Sound : public CSingleton<Sound>
{
public:
    Sound();
    ~Sound();

    bool Init();
    void PlaySound(const std::string& name);
    void PauseSound();
    void ResumeSound();
    void StopSound();
    void LoadSound(const std::string& name);
    void LoadSfx(const std::string& name);
    void PlaySfx(const std::string& name, int repeat = 0);
    void CleanUp();

    // Getters
    bool IsSfxEnabled() const { return m_sfxEnabled; }
    bool IsMusicEnabled() const { return m_musicEnabled; }

    // Setters
    void SetSfxEnabled(bool enabled) { m_sfxEnabled = enabled; }
    void SetMusicEnabled(bool enabled) { m_musicEnabled = enabled; }

private:
    std::string m_PathMusic;
    // Mix_Music* m_Music = NULL; // Uncomment if needed
    std::map<std::string, Mix_Chunk*> m_Sfxs;
    std::map<std::string, Mix_Music*> m_Sounds;

    bool m_sfxEnabled = true;
    bool m_musicEnabled = true;
};
