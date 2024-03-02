#include "game.hpp"

#include "SFML/Graphics.hpp"
#include <stdio.h>
#include <string>

void must_init(bool test, std::string description)
{
  if (test)
    return;

  std::cout << "coud not initialize " << description;
  exit(1);
}


int main(int argv, char** argc)
{
  srand(time(0));

  sf::Font font;
  font.loadFromFile("assets/fnt/slkscr.ttf");

  sf::Font fontpunteggio;
  fontpunteggio.loadFromFile("assets/fnt/slkscr.ttf");


  sf::RenderWindow window(sf::VideoMode(l, h), "Donkey Kong");
  window.setFramerateLimit(60);

  sf::RenderTexture buffer;
  buffer.create(window.getSize().x, window.getSize().y);

  int windowHeight = window.getSize().x;
  int windowWidth = window.getSize().y;
  
  float sx = windowWidth / float(h);
  float sy = windowHeight / float(l);
  
  int scale = std::min(sx, sy);

  int scaleW = l * scale;
  int scaleH = h * scale;
  int scaleX = (windowWidth - scaleW) / 2;
  int scaleY = (windowHeight - scaleH) / 2;

  // todo:: use smart pointers
  Graphics* GraphicManager = new Graphics(&window, &buffer, scaleX, scaleY, scaleW, scaleH, &font, &fontpunteggio);
  Sounds* SoundManager = new Sounds;
  Game GameManager(GraphicManager, SoundManager);

  int scelta = -1;
  int vite = 3;
  int livello = 1;
  int score = 0;

  // TODO: use sf::Keyboard::isKeyPressed() for input
  auto flushEventQueue = [&window]()
    {
    sf::Event event;
    while (window.pollEvent(event));
  };  
    
  while (scelta != 0)
  {
    flushEventQueue();
    //al_flush_event_queue(queue);

    // TODO: use event manager
    scelta = GameManager.runMenu();
    switch (scelta)
    {
    case 0:
      break;
    case 1:
      flushEventQueue();
      //al_flush_event_queue(queue);

      vite = 3;
      livello = 1;
      score = 0;
      while (vite != 0)
      {
        if (livello == 5)
          break;
        if (GameManager.runGame(vite, livello, score) == true)
        {
          flushEventQueue();
          //al_flush_event_queue(queue);

          if (livello == 4)
            GameManager.runCut(14);        //cutscene
          else
            GameManager.runCut(0);        //cutscene
          livello++;
        }
      }
      if (livello == 5)
        GameManager.runStatic(1);
      else
        GameManager.runStatic(2);
      break;
    case 2:
      flushEventQueue();
      //al_flush_event_queue(queue);
      GameManager.runOptions();
      break;
    case 3:
      flushEventQueue();
      //al_flush_event_queue(queue);
      GameManager.runStatic(0);
      break;
    }
  }

#if 0
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    window.clear(sf::Color::Black);
    //window.draw(shape);
    window.display();
  }
#endif

#if 0
  must_init(al_init(), "allegro");
  must_init(al_install_keyboard(), "keyboard");

  must_init(al_install_audio(), "sound");
  must_init(al_init_acodec_addon(), "Codec");

  must_init(al_init_font_addon(), "font");
  must_init(al_init_ttf_addon(), "ttf");
  ALLEGRO_FONT* font = al_create_builtin_font();
  must_init(font, "fonts");
  ALLEGRO_FONT* fontpunteggio = al_load_ttf_font("../Assets/Fonts/slkscr.ttf", 30, 0);
  must_init(fontpunteggio, "fontpunteggio");
#endif

#if 0
  ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
  must_init(timer, "timer");

  ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
  must_init(queue, "queue");

  al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
  ALLEGRO_BITMAP* buffer = al_create_bitmap(l, h);
  ALLEGRO_DISPLAY* display = al_create_display(l, h);
  must_init(display, "display");
  int windowHeight = al_get_display_height(display);
  int windowWidth = al_get_display_width(display);
  float sx = windowWidth / float(h);
  float sy = windowHeight / float(l);
  int scale = min(sx, sy);
  int scaleW = l * scale;
  int scaleH = h * scale;
  int scaleX = (windowWidth - scaleW) / 2;
  int scaleY = (windowHeight - scaleH) / 2;

  must_init(al_init_image_addon(), "image addon");
  must_init(buffer, "buffer");

  if (!al_hide_mouse_cursor(display))
    cout << "couldn't hide mouse cursor";
  
  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_display_event_source(display));
  al_register_event_source(queue, al_get_timer_event_source(timer));
  
  Graphics* GraphicManager = new Graphics(display, buffer, scaleX, scaleY, scaleW, scaleH, font, fontpunteggio);
  Sounds* SoundManager = new Sounds;
  Game GameManager(GraphicManager, SoundManager);
#endif

#if 0
  int scelta = -1;
  int vite = 3;
  int livello = 1;
  int score = 0;
  while (scelta != 0)
  {
    al_flush_event_queue(queue);
    scelta = GameManager.runMenu(timer, queue);
    switch (scelta)
    {
    case 0:
      break;
    case 1:
      al_flush_event_queue(queue);
      vite = 3;
      livello = 1;
      score = 0;
      while (vite != 0)
      {
        if (livello == 5)
          break;
        if (GameManager.runGame(timer, queue, vite, livello, score) == true)
        {
          al_flush_event_queue(queue);
          if (livello == 4)
            GameManager.runCut(queue, timer, 14);        //cutscene
          else
            GameManager.runCut(queue, timer, 0);        //cutscene
          livello++;
        }
      }
      if (livello == 5)
        GameManager.runStatic(queue, 1);
      else
        GameManager.runStatic(queue, 2);
      break;
    case 2:
      al_flush_event_queue(queue);
      GameManager.runOptions(timer, queue);
      break;
    case 3:
      al_flush_event_queue(queue);
      GameManager.runStatic(queue, 0);
      break;
    }
  }




  al_destroy_font(font);
  al_destroy_display(display);
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);
  delete GraphicManager;
  delete SoundManager;

#endif


  return 0;
}
