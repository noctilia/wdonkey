#include "game.hpp"
#include "graphics.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
Game::Game(Graphics* g, Sounds* s)
  : SoundManager(s)
  , GraphicManager(g)
  , difficulty(1.0)
  , muted(false)
{}

int Game::runMenu()
{
  SoundManager->stopSamples();
  if (!muted)
    SoundManager->playMenu();

  int state = 0;
  bool done = false;
  bool redraw = true;

  while (1)
  {
    sf::Event event;
    // TODO: use event manager instead of GraphicManager->getEvent
    while (GraphicManager->getEvent(event))
    {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) and state != 0)
      {
        state--;
        if (!muted)
          SoundManager->playPress();
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) and state != 3)
      {
        state++;
        if (!muted)
          SoundManager->playPress();
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) and state == 0)
        return 1;

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) and state == 1)
        return 2;

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) and state == 2)
        return 3;

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) and state == 3)
        done = true;

      // todo: return app close event
      if (sf::Event::Closed == event.type)
        done = true;

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        done = true;

      //if (eGraphicManager->getKey() == ALLEGRO_KEY_ENTER and state == 0)
      //  return 1;

      //if (GraphicManager->getKey() == ALLEGRO_KEY_ENTER and state == 1)
      //  return 2;
      //
      //if (GraphicManager->getKey() == ALLEGRO_KEY_ENTER and state == 2)
      //  return 3;
      //
      //if (GraphicManager->getKey() == ALLEGRO_KEY_ENTER and state == 3)
      //  done = true;
      //
      ////if (event.type == sf::Event::Closed)
      ////  window.close();

      //if (event.k GraphicManager->getKey() == ALLEGRO_KEY_ESCAPE)
      //  done = true;
    }

    if (done)
      break;

    GraphicManager->DrawMenu(state);
    GraphicManager->flipDisplay();
    redraw = false;

    /* if (redraw and GraphicManager->isEventQueueEmpty())
     {
       GraphicManager->DrawMenu(state);
       GraphicManager->flipDisplay();
       redraw = false;
     }*/
  }
  SoundManager->stopSamples();
  return 0;

}

bool Game::runGame(int& lifes, int& level, int& score)
{
  SoundManager->stopMenu();
  if (level == 3)                     //nel level 3 ci sono piu' barili
    difficulty -= 0.3;

  GraphicManager->assignGrid(level);
  bool complete = false;
  unsigned hammerTime = 0;

  srand(time(0));
  SoundManager->stopSamples();
  if (!muted)
    SoundManager->startNewGame();

  std::list <Barrel> Barili;
  Barrel Bar(GraphicManager->grid);
  int addpunteggiomartello = 0;
  int addpunteggiobarile = 0;
  std::pair <int, int> segnaCancellazione;

  segnaCancellazione.first = 0;
  segnaCancellazione.second = 0;
  int frameExpl = 0;

#define KEY_SEEN     1
#define KEY_RELEASED 2

  // TODO: keybuffer
  //unsigned char key[ALLEGRO_KEY_MAX];
  //memset(key, 0, sizeof(key));

  auto window = GraphicManager->getWindow();

  // TODO: remove me
  auto flushEventQueue = [&window]()
    {
      sf::Event event;
      while (window->pollEvent(event));
    };

  while (lifes != 0)
  {
#define KEY_SEEN     1
#define KEY_RELEASED 2
    // TODO: keybuffer
    //unsigned char key[ALLEGRO_KEY_MAX];
    //memset(key, 0, sizeof(key));


    // TODO: remove me, use input manager
    //al_flush_event_queue(queue);
    flushEventQueue();

    hammerTime = 0;
    Player* Play = new Player(GraphicManager->grid);
    Kong* Wukong = new Kong(GraphicManager->grid, difficulty);
    Entity* Peach = new Entity(60, 220, GraphicManager->grid);
    auto temp = Barili.begin();
    bool done = false;
    bool redraw = true;

    //ALLEGRO_EVENT event;
    sf::Event event;

    //al_start_timer(timer);

    while (1)
    {
      //al_wait_for_event(queue, &event);

      while (GraphicManager->getEvent(event))
      {
        if (sf::Event::Closed == event.type) {
          done = true;
          lifes = 1;
        }

        if (event.type == sf::Event::KeyPressed) {
          if (event.key.code == sf::Keyboard::Up)
          {
            Play->MoveUp();
          }
          if (event.key.code == sf::Keyboard::Down)
          {
            Play->MoveDown();
          }
          if (event.key.code == sf::Keyboard::Left)
          {
            Play->MoveLeft();
            if (!muted)
              SoundManager->playWalking();
          }
          if (event.key.code == sf::Keyboard::Right)
          {
            Play->MoveRight();
            if (!muted)
              SoundManager->playWalking();
          }

          if (event.key.code == sf::Keyboard::Space)
          {
            Play->Jump();
            if (!muted)
              SoundManager->playJump();
          }

          if (event.key.code == sf::Keyboard::Escape)
          {
            done = true;
            lifes = 1;
          }
          
          if (event.key.code == sf::Keyboard::Tab)
          {
            complete = true;          //LEVEL SKIPPER CHEAT
            done = true;
          }

          if (event.key.code == sf::Keyboard::LShift and Play->getHammer())
          {
            Play->setHammered(true);
            hTime++;
            if (!muted)
              SoundManager->playHammer();
          }
        }
      }
#if 0
      switch (event.type)
      {
      case ALLEGRO_EVENT_TIMER:
        if (key[ALLEGRO_KEY_UP])
        {
          Play->MoveUp();
        }
        if (key[ALLEGRO_KEY_DOWN])
        {
          Play->MoveDown();
        }
        if (key[ALLEGRO_KEY_LEFT])
        {
          Play->MoveLeft();
          if (!muted)
            SoundManager->playWalking();
        }
        if (key[ALLEGRO_KEY_RIGHT])
        {
          Play->MoveRight();
          if (!muted)
            SoundManager->playWalking();
        }
        if (key[ALLEGRO_KEY_SPACE])
        {
          Play->Jump();
          if (!muted)
            SoundManager->playJump();
        }
        if (key[ALLEGRO_KEY_ESCAPE])
        {
          done = true;
          lifes = 1;
        }
        if (key[ALLEGRO_KEY_TAB])
        {
          complete = true;          //LEVEL SKIPPER CHEAT
          done = true;
        }
        if (key[ALLEGRO_KEY_LSHIFT] and Play->getHammer())
        {
          Play->setHammered(true);
          hTime++;
          if (!muted)
            SoundManager->playHammer();
        }
        for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
          key[i] &= KEY_SEEN;


        Play->HandleGravity();
        if (Play->getX() / 20 == 21 and Play->getY() / 20 == 17 and Play->getHammer() == false and hammerTime == 0)//prende il martello.
          Play->setHammer(true);
        if (hTime < 30)
          hTime++;
        else
        {
          hTime = 0;
          Play->setHammered(false);
        }

        if (Play->getHammer())
          hammerTime++;
        if (hammerTime > 325 and Play->getHammer())
          Play->setHammer(false);
        if (Wukong->getLancia() == Wukong->getFrame())
        {
          Barili.push_back(Bar);
          Wukong->nextFrame();
        }
        for (auto i = Barili.begin(); i != Barili.end(); i++)
        {

          i->roll();
          i->HandleGravity();
          if (Play->getX() / 20 == i->getX() / 20 and Play->getY() / 20 == i->getY() / 20)
          {
            SoundManager->stopSamples();
            if (!muted)
              SoundManager->playDeath();
            Play->setMorto(true);
            al_rest(4);
            done = true;
          }

          if ((Play->getX() / 20 == (i->getX() / 20) - 1 or Play->getX() / 20 == (i->getX() / 20) - 2) and Play->getY() / 20 == i->getY() / 20
            and i->getJumped() == false and Play->getLadderstate() == false and (Play->getJump() or Play->isFalling()))
          {
            score += 100;
            addpunteggiobarile += 4;
            i->setJumped(true);
          }

          if (i->getStop())
          {
            temp = i;
            i++;
            Barili.erase(temp);

          }
          if (
            Play->getHammered() and Play->getDirection() == LEFT and (Play->getY() / 20) - 1 == i->getY() / 20 and Play->getX() / 20 == i->getX() / 20
            or
            Play->getHammered() and Play->getDirection() == RIGHT and (Play->getY() / 20) + 1 == i->getY() / 20 and Play->getX() / 20 == i->getX() / 20)
          {
            temp = i;
            segnaCancellazione.first = i->getX();
            segnaCancellazione.second = i->getY();
            i++;
            Barili.erase(temp);
            score += 300;
            addpunteggiomartello += 5;
          }

        }
        if (Play->getX() / 20 == Peach->getX() / 20 and Play->getY() / 20 == Peach->getY() / 20 and level != 4)  //completa il level
        {
          complete = true;
          done = true;
        }
        if (Play->getX() / 20 == 6 and Play->getY() / 20 == 1 and level == 4)  //completa il gioco
        {
          complete = true;
          done = true;
        }
        redraw = true;
        break;

      case ALLEGRO_EVENT_KEY_DOWN:
        key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
        break;
      case ALLEGRO_EVENT_KEY_UP:
        key[event.keyboard.keycode] &= KEY_RELEASED;
        break;

      case ALLEGRO_EVENT_DISPLAY_CLOSE:
        done = true;
        lifes = 1;
        break;

        }
#endif
      if (done)
        break;

      /**************************************************************************************/
      /* logic loop */
      /**************************************************************************************/

      // this needs timer events... oder move to logic loop
      Play->HandleGravity();
      //takes the hammer
      if (Play->getX() / 20 == 21 and Play->getY() / 20 == 17 and Play->getHammer() == false and hammerTime == 0)
        Play->setHammer(true);
      if (hTime < 30)
        hTime++;
      else
      {
        hTime = 0;
        Play->setHammered(false);
      }

      if (Play->getHammer())
        hammerTime++;

      if (hammerTime > 325 and Play->getHammer())
        Play->setHammer(false);

      if (Wukong->getThrowBarrel() == Wukong->getFrame())
      {
        Barili.push_back(Bar);
        Wukong->nextFrame();
      }

      for (auto i = Barili.begin(); i != Barili.end(); i++)
      {

        i->roll();
        i->HandleGravity();
        if (Play->getX() / 20 == i->getX() / 20 and Play->getY() / 20 == i->getY() / 20)
        {
          SoundManager->stopSamples();
          if (!muted)
            SoundManager->playDeath();
          Play->setDead(true);
          
          //al_rest(4);
          done = true;
        }

        if ((Play->getX() / 20 == (i->getX() / 20) - 1 or Play->getX() / 20 == (i->getX() / 20) - 2) and Play->getY() / 20 == i->getY() / 20
          and i->getJumped() == false and Play->getLadderstate() == false and (Play->getJump() or Play->isFalling()))
        {
          score += 100;
          addpunteggiobarile += 4;
          i->setJumped(true);
        }

        if (i->getStop())
        {
          temp = i;
          i++;
          Barili.erase(temp);

        }
        if (
          Play->getHammered() and Play->getDirection() == LEFT and (Play->getY() / 20) - 1 == i->getY() / 20 and Play->getX() / 20 == i->getX() / 20
          or
          Play->getHammered() and Play->getDirection() == RIGHT and (Play->getY() / 20) + 1 == i->getY() / 20 and Play->getX() / 20 == i->getX() / 20)
        {
          temp = i;
          segnaCancellazione.first = i->getX();
          segnaCancellazione.second = i->getY();
          i++;
          Barili.erase(temp);
          score += 300;
          addpunteggiomartello += 5;
        }

      }
      if (Play->getX() / 20 == Peach->getX() / 20 and Play->getY() / 20 == Peach->getY() / 20 and level != 4)  //completa il level
      {
        complete = true;
        done = true;
      }
      if (Play->getX() / 20 == 6 and Play->getY() / 20 == 1 and level == 4)  //completa il gioco
      {
        complete = true;
        done = true;
      }
      /************************************************************************************************************/
      //if (redraw and al_is_event_queue_empty(queue))
      {
        GraphicManager->DrawMap(false);

        GraphicManager->DrawPeach(Peach);

        GraphicManager->DrawStaticBarrels();
        GraphicManager->DrawKong(Wukong);
        GraphicManager->DrawExplosive(frameExpl);

        if (Play->getHammer() and Play->getFrame() <= 30)
          GraphicManager->DrawPlayerHammer(Play);
        else
          GraphicManager->DrawPlayer(Play);

        for (auto i = Barili.begin(); i != Barili.end(); i++)
          GraphicManager->DrawBarrel(*i);

        if (Play->getHammer() == false and hammerTime < 200)
          GraphicManager->DrawHammer();

        GraphicManager->DrawScore(score);

        if (addpunteggiomartello > 0)
        {
          GraphicManager->DrawInstantScore(1, Play->getX() - 9, Play->getY());
          addpunteggiomartello--;
        }

        if (addpunteggiobarile > 0)
        {
          GraphicManager->DrawInstantScore(2, Play->getX() - 9, Play->getY());
          addpunteggiobarile--;
        }

        GraphicManager->DrawDelete(segnaCancellazione.first, segnaCancellazione.second);
        GraphicManager->DrawLives(lifes);

        GraphicManager->flipDisplay();
        redraw = false;
      }
      }
    delete Play;
    delete Wukong;
    delete Peach;
    Barili.clear();
    if (complete)
      break;
    lifes--;
    }
  if (level == 3)                 //difficoltà torna normale
    difficulty += 0.3;
  SoundManager->stopSamples();
  return complete;
  }

void Game::runOptions()
{
  int state = 0;
  bool done = false;
  bool redraw = true;
  //al_start_timer(timer);
  while (1)
  {
    sf::Event event;
    // TODO: use event manager instead of GraphicManager->getEvent
    while (GraphicManager->getEvent(event))
    {
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Right and state != 1 and difficulty >= 1)
        {
          difficulty -= 0.5;
          if (!muted)
            SoundManager->playPress();
        }
        if (event.key.code == sf::Keyboard::Left and state != 1 and difficulty <= 1)
        {
          difficulty += 0.5;
          if (!muted)
            SoundManager->playPress();
        }
        if (event.key.code == sf::Keyboard::Up and state != 0)
        {
          state--;
          if (!muted)
            SoundManager->playPress();
        }
        if (event.key.code == sf::Keyboard::Down and state != 1)
        {
          state++;
          if (!muted)
            SoundManager->playPress();
        }
        if (event.key.code == sf::Keyboard::Enter and state == 1
          or event.key.code == sf::Keyboard::Escape
          or event.type == sf::Event::Closed)
        {
          done = true;
          if (!muted)
            SoundManager->playBack();
          sf::sleep(sf::milliseconds(300));
        }
        if (event.key.code == sf::Keyboard::M)
        {
          SoundManager->playPress();
          if (muted)
          {
            muted = false;
            SoundManager->playMenu();
          }
          else
          {
            muted = true;
            SoundManager->stopMenu();
          }
        }
      }
    }


    if (done)
      break;

    GraphicManager->DrawOptions(state, difficulty);
    GraphicManager->flipDisplay();
    redraw = false;
  }
}

// Credits
void Game::runStatic(int a)
{
  //al_flush_event_queue(queue);

  // todo: drawing laoding
  GraphicManager->DrawImage(a);
  if (a == 2 and !muted)
    SoundManager->playMammaMia();

  //al_flip_display();
  GraphicManager->flipDisplay();

  while (1)
  {
    sf::Event event;
    while (GraphicManager->getEvent(event))
    {
      if (event.type == sf::Event::KeyPressed or event.type == sf::Event::Closed) {
        if (!muted)
        {
          SoundManager->playBack();
          sf::sleep(sf::milliseconds(300));
        }
        return;
      }
    }

    GraphicManager->DrawImage(a);
    GraphicManager->flipDisplay();
  }
}

void Game::runCut(int frame)
{
  SoundManager->stopSamples();
  GraphicManager->assignGrid(0);
  //ALLEGRO_EVENT event;
  //al_start_timer(timer);

  bool done = false;
  bool redraw = true;
  float rests[19] = { 1.3,0.5,1.0,0.5,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.7,0.8,1.6,1.2,2.0 };
  while (1)
  {
    sf::Event event;
    while (GraphicManager->getEvent(event))
    {
      if (event.type == sf::Event::KeyPressed or event.type == sf::Event::Closed) {
        done = true;
        break;
      }
    }

    if (done)
      break;

    //if (redraw and al_is_event_queue_empty(queue))
    {
      GraphicManager->DrawCut(frame);
      GraphicManager->flipDisplay();

      //al_flip_display();
      redraw = false;

      sf::sleep(sf::milliseconds(rests[frame] * 1000));
      //al_rest(rests[frame]);
      frame++;
      if (frame == 14 or frame == 19)
        done = true;
    }
  }
}

#if 0
Game::Game(Graphics* g, Sounds* s) :SoundManager(s), GraphicManager(g), difficulty(1.0), muted(false) {}

int Game::runMenu(ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* queue)
{
  al_flush_event_queue(queue);
  SoundManager->stopSamples();
  if (!muted)
    SoundManager->playMenu();
  int state = 0;
  bool done = false;
  bool redraw = true;
  ALLEGRO_EVENT event;
  al_start_timer(timer);
  while (1)
  {
    al_wait_for_event(queue, &event);
    switch (event.type)
    {
    case ALLEGRO_EVENT_TIMER:
      redraw = true;
      break;
    case ALLEGRO_EVENT_KEY_CHAR:
      if (event.keyboard.keycode == ALLEGRO_KEY_UP and state != 0)
      {
        state--;
        if (!muted)
          SoundManager->playPress();
      }
      if (event.keyboard.keycode == ALLEGRO_KEY_DOWN and state != 3)
      {
        state++;
        if (!muted)
          SoundManager->playPress();
      }
      if (event.keyboard.keycode == ALLEGRO_KEY_ENTER and state == 0)
        return 1;
      if (event.keyboard.keycode == ALLEGRO_KEY_ENTER and state == 1)
        return 2;
      if (event.keyboard.keycode == ALLEGRO_KEY_ENTER and state == 2)
        return 3;
      if (event.keyboard.keycode == ALLEGRO_KEY_ENTER and state == 3)
        done = true;
      if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
        done = true;
      break;
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      done = true;
      break;
    }

    if (done)
      break;

    if (redraw and al_is_event_queue_empty(queue))
    {
      GraphicManager->DrawMenu(state);
      al_flip_display();
      redraw = false;
    }
  }
  SoundManager->stopSamples();
  return 0;
}




bool Game::runGame(ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* queue, int& lifes, int& level, int& score)
{
  SoundManager->stopMenu();
  if (level == 3)                     //nel level 3 ci sono piu' barili
    difficulty -= 0.3;
  GraphicManager->assignGrid(level);
  bool complete = false;
  unsigned hammerTime = 0;
  srand(time(0));
  SoundManager->stopSamples();
  if (!muted)
    SoundManager->startNewGame();
  list <Barrel> Barili;
  Barrel Bar(GraphicManager->grid);
  int addpunteggiomartello = 0;
  int addpunteggiobarile = 0;
  pair <int, int> segnaCancellazione;
  segnaCancellazione.first = 0;
  segnaCancellazione.second = 0;
  int frameExpl = 0;
#define KEY_SEEN     1
#define KEY_RELEASED 2
  unsigned char key[ALLEGRO_KEY_MAX];
  memset(key, 0, sizeof(key));
  while (lifes != 0)
  {
#define KEY_SEEN     1
#define KEY_RELEASED 2
    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));
    al_flush_event_queue(queue);
    hammerTime = 0;
    Player* Play = new Player(GraphicManager->grid);
    Kong* Wukong = new Kong(GraphicManager->grid, difficulty);
    Entity* Peach = new Entity(60, 220, GraphicManager->grid);
    auto temp = Barili.begin();
    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;



    al_start_timer(timer);
    while (1)
    {
      al_wait_for_event(queue, &event);
      switch (event.type)
      {
      case ALLEGRO_EVENT_TIMER:
        if (key[ALLEGRO_KEY_UP])
        {
          Play->MoveUp();
        }
        if (key[ALLEGRO_KEY_DOWN])
        {
          Play->MoveDown();
        }
        if (key[ALLEGRO_KEY_LEFT])
        {
          Play->MoveLeft();
          if (!muted)
            SoundManager->playWalking();
        }
        if (key[ALLEGRO_KEY_RIGHT])
        {
          Play->MoveRight();
          if (!muted)
            SoundManager->playWalking();
        }
        if (key[ALLEGRO_KEY_SPACE])
        {
          Play->Jump();
          if (!muted)
            SoundManager->playJump();
        }
        if (key[ALLEGRO_KEY_ESCAPE])
        {
          done = true;
          lifes = 1;
        }
        if (key[ALLEGRO_KEY_TAB])
        {
          complete = true;          //LEVEL SKIPPER CHEAT
          done = true;
        }
        if (key[ALLEGRO_KEY_LSHIFT] and Play->getHammer())
        {
          Play->setHammered(true);
          hTime++;
          if (!muted)
            SoundManager->playHammer();
        }
        for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
          key[i] &= KEY_SEEN;


        Play->HandleGravity();
        if (Play->getX() / 20 == 21 and Play->getY() / 20 == 17 and Play->getHammer() == false and hammerTime == 0)//prende il martello.
          Play->setHammer(true);
        if (hTime < 30)
          hTime++;
        else
        {
          hTime = 0;
          Play->setHammered(false);
        }

        if (Play->getHammer())
          hammerTime++;
        if (hammerTime > 325 and Play->getHammer())
          Play->setHammer(false);
        if (Wukong->getLancia() == Wukong->getFrame())
        {
          Barili.push_back(Bar);
          Wukong->nextFrame();
        }
        for (auto i = Barili.begin(); i != Barili.end(); i++)
        {

          i->roll();
          i->HandleGravity();
          if (Play->getX() / 20 == i->getX() / 20 and Play->getY() / 20 == i->getY() / 20)
          {
            SoundManager->stopSamples();
            if (!muted)
              SoundManager->playDeath();
            Play->setMorto(true);
            al_rest(4);
            done = true;
          }

          if ((Play->getX() / 20 == (i->getX() / 20) - 1 or Play->getX() / 20 == (i->getX() / 20) - 2) and Play->getY() / 20 == i->getY() / 20
            and i->getJumped() == false and Play->getLadderstate() == false and (Play->getJump() or Play->isFalling()))
          {
            score += 100;
            addpunteggiobarile += 4;
            i->setJumped(true);
          }

          if (i->getStop())
          {
            temp = i;
            i++;
            Barili.erase(temp);

          }
          if (
            Play->getHammered() and Play->getDirection() == LEFT and (Play->getY() / 20) - 1 == i->getY() / 20 and Play->getX() / 20 == i->getX() / 20
            or
            Play->getHammered() and Play->getDirection() == RIGHT and (Play->getY() / 20) + 1 == i->getY() / 20 and Play->getX() / 20 == i->getX() / 20)
          {
            temp = i;
            segnaCancellazione.first = i->getX();
            segnaCancellazione.second = i->getY();
            i++;
            Barili.erase(temp);
            score += 300;
            addpunteggiomartello += 5;
          }

        }
        if (Play->getX() / 20 == Peach->getX() / 20 and Play->getY() / 20 == Peach->getY() / 20 and level != 4)  //completa il level
        {
          complete = true;
          done = true;
        }
        if (Play->getX() / 20 == 6 and Play->getY() / 20 == 1 and level == 4)  //completa il gioco
        {
          complete = true;
          done = true;
        }
        redraw = true;
        break;

      case ALLEGRO_EVENT_KEY_DOWN:
        key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
        break;
      case ALLEGRO_EVENT_KEY_UP:
        key[event.keyboard.keycode] &= KEY_RELEASED;
        break;

      case ALLEGRO_EVENT_DISPLAY_CLOSE:
        done = true;
        lifes = 1;
        break;

      }

      if (done)
        break;

      if (redraw and al_is_event_queue_empty(queue))
      {
        GraphicManager->DrawMap(false);
        GraphicManager->DrawPeach(Peach);
        GraphicManager->DrawStaticBarrels();
        GraphicManager->DrawKong(Wukong);
        GraphicManager->DrawExplosive(frameExpl);
        if (Play->getHammer() and Play->getFrame() <= 30)
          GraphicManager->DrawPlayerHammer(Play);
        else
          GraphicManager->DrawPlayer(Play);

        for (auto i = Barili.begin(); i != Barili.end(); i++)
          GraphicManager->DrawBarrel(*i);
        if (Play->getHammer() == false and hammerTime < 200)
          GraphicManager->DrawHammer();
        GraphicManager->DrawScore(score);
        if (addpunteggiomartello > 0)
        {
          GraphicManager->DrawInstantScore(1, Play->getX() - 9, Play->getY());
          addpunteggiomartello--;
        }
        if (addpunteggiobarile > 0)
        {
          GraphicManager->DrawInstantScore(2, Play->getX() - 9, Play->getY());
          addpunteggiobarile--;
        }
        GraphicManager->DrawDelete(segnaCancellazione.first, segnaCancellazione.second);
        GraphicManager->DrawLives(lifes);
        al_flip_display();
        redraw = false;
      }
    }
    delete Play;    delete Wukong;    delete Peach;   Barili.clear();
    if (complete)
      break;
    lifes--;
  }
  if (level == 3)                 //difficoltà torna normale
    difficulty += 0.3;
  SoundManager->stopSamples();
  return complete;
}
void Game::runOptions(ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* queue)
{
  int state = 0;
  bool done = false;
  bool redraw = true;
  ALLEGRO_EVENT event;
  al_start_timer(timer);
  while (1)
  {
    al_wait_for_event(queue, &event);
    switch (event.type)
    {
    case ALLEGRO_EVENT_TIMER:
      redraw = true;
      break;
    case ALLEGRO_EVENT_KEY_CHAR:
      if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT and state != 1 and difficulty >= 1)
      {
        difficulty -= 0.5;
        if (!muted)
          SoundManager->playPress();
      }
      if (event.keyboard.keycode == ALLEGRO_KEY_LEFT and state != 1 and difficulty <= 1)
      {
        difficulty += 0.5;
        if (!muted)
          SoundManager->playPress();
      }
      if (event.keyboard.keycode == ALLEGRO_KEY_UP and state != 0)
      {
        state--;
        if (!muted)
          SoundManager->playPress();
      }
      if (event.keyboard.keycode == ALLEGRO_KEY_DOWN and state != 1)
      {
        state++;
        if (!muted)
          SoundManager->playPress();
      }
      if (event.keyboard.keycode == ALLEGRO_KEY_ENTER and state == 1 or event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
      {
        done = true;
        if (!muted)
          SoundManager->playBack();
        al_rest(0.3);
        }
      if (event.keyboard.keycode == ALLEGRO_KEY_M)
      {
        SoundManager->playPress();
        if (muted)
        {
          muted = false;
          SoundManager->playMenu();
        }
        else
        {
          muted = true;
          SoundManager->stopMenu();
        }
      }
      break;
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      done = true;
      break;
      }

    if (done)
      break;

    if (redraw and al_is_event_queue_empty(queue))
    {
      GraphicManager->DrawOptions(state, difficulty);
      al_flip_display();
      redraw = false;
    }
    }
  }
void Game::runStatic(ALLEGRO_EVENT_QUEUE* queue, int a)
{
  al_flush_event_queue(queue);
  GraphicManager->DrawImage(a);
  if (a == 2 and !muted)
    SoundManager->playMammaMia();
  al_flip_display();
  ALLEGRO_EVENT event;
  while (1)
  {
    al_wait_for_event(queue, &event);
    if (event.type == ALLEGRO_EVENT_KEY_DOWN)
    {
      if (!muted)
      {
        SoundManager->playBack();
        al_rest(0.3);
      }
      return;
    }
  }
}
void Game::runCut(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer, int frame)
{
  SoundManager->stopSamples();
  GraphicManager->assignGrid(0);
  ALLEGRO_EVENT event;
  al_start_timer(timer);
  bool done = false;
  bool redraw = true;
  float rests[19] = { 1.3,0.5,1.0,0.5,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.7,0.8,1.6,1.2,2.0 };
  while (1)
  {
    al_wait_for_event(queue, &event);
    switch (event.type)
    {
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      done = true;
      break;
    case ALLEGRO_KEY_DOWN:
      done = true;
      break;
    case ALLEGRO_EVENT_TIMER:
      redraw = true;
      break;
    }
    if (done)
      break;
    if (redraw and al_is_event_queue_empty(queue))
    {
      GraphicManager->DrawCut(frame);
      al_flip_display();
      redraw = false;
      al_rest(rests[frame]);
      frame++;
      if (frame == 14 or frame == 19)
        done = true;
    }
  }
}

#endif