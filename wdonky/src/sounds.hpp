#include <SFML/Audio.hpp> 

class Sounds
{
public:

public:
  Sounds();
  void startNewGame();
  void playHammer();
  void playDeath();
  void playMammaMia();
  void playWalking();
  void playJump();
  void playMenu();
  void stopSamples();
  void stopMenu();
  void playPress();
  void playBack();
  ~Sounds();

private:
  sf::SoundBuffer newgame;
  sf::SoundBuffer death;
  sf::SoundBuffer mammamia;
  sf::SoundBuffer walking;
  sf::SoundBuffer jump;
  sf::SoundBuffer menu;
  sf::SoundBuffer hammer;
  sf::SoundBuffer press;
  sf::SoundBuffer back;

  sf::Sound walkingInstance;
  sf::Sound jumpInstance;
  sf::Sound hammerInstance;
  sf::Sound menuInstance;
};

#if 0

#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
using namespace std;
class Sounds
{
    private:
        ALLEGRO_SAMPLE* newgame;
        ALLEGRO_SAMPLE* death;
        ALLEGRO_SAMPLE* mammamia;
        ALLEGRO_SAMPLE* walking;
        ALLEGRO_SAMPLE* jump;
        ALLEGRO_SAMPLE* menu;
        ALLEGRO_SAMPLE* hammer;
        ALLEGRO_SAMPLE* press;
        ALLEGRO_SAMPLE* back;
        ALLEGRO_SAMPLE_INSTANCE* walkingInstance;
        ALLEGRO_SAMPLE_INSTANCE* jumpInstance;
        ALLEGRO_SAMPLE_INSTANCE* hammerInstance;
        ALLEGRO_SAMPLE_INSTANCE* menuInstance;

};

#endif
