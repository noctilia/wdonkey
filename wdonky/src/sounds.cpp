#include "sounds.hpp"

Sounds::Sounds()
{
  newgame.loadFromFile("assets/snd/newgame.wav");
  death.loadFromFile("assets/snd/morte.wav");
  mammamia.loadFromFile("assets/snd/MammaMiaPizzeria.wav");
  walking.loadFromFile("assets/snd/walking.wav");
  jump.loadFromFile("assets/snd/jump.wav");
  menu.loadFromFile("assets/snd/menu.wav");
  hammer.loadFromFile("assets/snd/hammer.wav");
  press.loadFromFile("assets/snd/press.wav");
  back.loadFromFile("assets/snd/back.wav");

}

void Sounds::startNewGame()
{
  //al_play_sample(newgame, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
  menuInstance.setBuffer(newgame);  
  menuInstance.play();
}

void Sounds::playHammer()
{
  /*if (!al_get_sample_instance_playing(hammerInstance))
    al_play_sample_instance(hammerInstance);*/
  hammerInstance.setBuffer(hammer);
  hammerInstance.play();  
}

void Sounds::playDeath()
{
 /* al_play_sample(death, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);*/
}

void Sounds::playMammaMia()
{
  /*al_play_sample(mammamia, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);*/
}

void Sounds::playWalking()
{
  /*if (!al_get_sample_instance_playing(walkingInstance) 
    and !al_get_sample_instance_playing(jumpInstance) 
    and !al_get_sample_instance_playing(hammerInstance))
    al_play_sample_instance(walkingInstance);*/
}

void Sounds::playJump()
{
  /*if (!al_get_sample_instance_playing(jumpInstance))
    al_play_sample_instance(jumpInstance);*/
}

void Sounds::playMenu()
{
  /*if (!al_get_sample_instance_playing(menuInstance))
  {
    al_play_sample_instance(menuInstance);
    al_set_sample_instance_playmode(menuInstance, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_gain(menuInstance, 0.6);
  }*/
}

void Sounds::stopSamples() {
  //al_stop_samples();
}

void Sounds::stopMenu()
{
  /*if (al_get_sample_instance_playing(menuInstance))
    al_stop_sample_instance(menuInstance);*/
}

void Sounds::playPress()
{
  menuInstance.setBuffer(press);
  menuInstance.play();  
  /*l_play_sample(press, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);*/
}

void Sounds::playBack()
{
  /*al_play_sample(back, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);*/
}

Sounds::~Sounds()
{
  /*al_destroy_sample(newgame);
  al_destroy_sample(death);
  al_destroy_sample(mammamia);
  al_destroy_sample_instance(walkingInstance);
  al_destroy_sample(walking);
  al_destroy_sample_instance(jumpInstance);
  al_destroy_sample(jump);
  al_destroy_sample(menu);
  al_destroy_sample_instance(hammerInstance);
  al_destroy_sample(hammer);
  al_destroy_sample(press);
  al_destroy_sample(back);
  al_uninstall_audio();*/
}