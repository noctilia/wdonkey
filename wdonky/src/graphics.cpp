#include "SFML/graphics.hpp"
#include "graphics.hpp"
#include <format>

Graphics::Graphics(sf::RenderWindow* window, sf::RenderTexture* buffer,
  int scaleX, int scaleY, int scaleW, int scaleH, sf::Font* font, sf::Font* fontScore)
{
  grid_allocated = false;

  this->font = font;
  this->fontScore = fontScore;
  this->scaleH = scaleH;
  this->scaleW = scaleW;
  this->scaleX = scaleX;
  this->scaleY = scaleY;
  this->buffer = buffer;
  this->window = window;

  sf::Image icon;
  icon.loadFromFile("assets/img/icon.png");
  window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

  const std::vector<std::string> staticBitmapsPaths = {
    "assets/img/tiles/scala.png",
    "assets/img/tiles/ground.png",
    "assets/img/hammer.png",
    "assets/img/barrel/barrel_standing.png",
    "assets/img/peach/peach0.png",
    "assets/img/enemy/oilcan.png"
  };

  for (auto& path : staticBitmapsPaths)
  {
    sf::Texture* texture = new sf::Texture;
    texture->loadFromFile(path);
    staticBitmaps.push_back(texture);
  }
}

Graphics::~Graphics()
{
  deleteGrid();

  for (auto& bitmap : staticBitmaps)
    delete bitmap;
}

void Graphics::deleteGrid()
{
  if (grid_allocated)
  {
    for (int i = 0; i < x; i++)
      delete grid[i];
    delete[] grid;
  }
}

void Graphics::assignGrid(int level)
{
  // TODO: use std::vector instead of raw pointers
  deleteGrid();

  std::ifstream fileinput;

  fileinput.open(std::format("assets/maps/level{}.txt", level));
  if (!fileinput.is_open())
    std::cout << "could not initialize level " << level << std::endl;

  fileinput >> x >> y;
  grid = new int* [x];

  // TODO: use std::vector instead of raw pointers
  for (int i = 0; i < x; i++) {
    grid[i] = new int[y];
  }

  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      fileinput >> grid[i][j];
    }
  }

  fileinput.close();
  grid_allocated = true;
}

void Graphics::DrawMap(bool cutScene)
{
  //al_set_target_bitmap(buffer);
  //al_clear_to_color(al_map_rgb(0, 0, 0));
  buffer->clear(sf::Color::Black);

  for (int i = 0; i < x; i++)
  {
    for (int j = 0; j < y; j++)
    {
      switch (grid[i][j])
      {
      case 1: {
        // TODO: use sprite instead of bitmap
        sf::Sprite sprite(*staticBitmaps[0]);
        sprite.setPosition(j * 20, i * 20);
        //display->draw(sprite);
        buffer->draw(sprite);
        //al_draw_bitmap(staticBitmaps[0], j * 20, i * 20, 0);
        break;
      }

      case 2: {
        // TODO: use sprite instead of bitmap in vector class
        sf::Sprite sprite(*staticBitmaps[1]);
        sprite.setPosition(j * 20, i * 20);
        //display->draw(sprite);
        buffer->draw(sprite);
        //al_draw_bitmap(staticBitmaps[1], j * 20, i * 20, 0);
        break;
      }
      }
    }
  }
  if (cutScene == false) {

    sf::Sprite sprite(*staticBitmaps[5]);
    sprite.setPosition(40, 520);
    buffer->draw(sprite);
    //al_draw_bitmap(staticBitmaps[5], 40, 520, 0);             //barile incendiato
  }

  // TODO: draw to render texture instead of backbuffer???
  sf::Sprite sprite(buffer->getTexture());
  sprite.setScale(scaleX, scaleY);
  window->draw(sprite);

  //al_set_target_backbuffer(display);
  //al_clear_to_color(al_map_rgb(0, 0, 0));
  //al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);
}


void Graphics::DrawMenu(short unsigned n)
{
  //al_set_target_bitmap(buffer);
  //al_clear_to_color(al_map_rgb(0, 0, 0));

  buffer->clear(sf::Color::Black);

  sf::Texture texture;
  switch (n)
  {
  case 0:
    // TODO: use texture cache?
    texture.loadFromFile("assets/img/menu/Menu0.png");
    //bitmap = al_load_bitmap("../Assets/Bitmaps/Menu/Menu0.png");
    break;
  case 1:
    texture.loadFromFile("assets/img/menu/Menu1.png");
    //bitmap = al_load_bitmap("../Assets/Bitmaps/Menu/Menu1.png");
    break;
  case 2:
    texture.loadFromFile("assets/img/menu/Menu2.png");
    //bitmap = al_load_bitmap("../Assets/Bitmaps/Menu/Menu2.png");
    break;
  case 3:
    texture.loadFromFile("assets/img/menu/Menu3.png");  
    //bitmap = al_load_bitmap("../Assets/Bitmaps/Menu/Menu3.png");
    break;
  }

  // TODO: fix me
  {
    sf::Sprite sprite(texture);
    buffer->draw(sprite);
  }
  //al_draw_bitmap(bitmap, 0, 0, 0);
  //al_destroy_bitmap(bitmap);
 
  //al_set_target_backbuffer(display);
  //al_clear_to_color(al_map_rgb(0, 0, 0));
  //al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);

  window->clear(sf::Color::Black);

  sf::Sprite sprite(buffer->getTexture());
  sprite.setScale(scaleX, scaleY);
  window->draw(sprite);
}

void Graphics::DrawOptions(int n, float difficulty)
{
  //al_set_target_bitmap(buffer);
  //al_clear_to_color(al_map_rgb(0, 0, 0));

  buffer->clear(sf::Color::Black);

  sf::Texture texture;

  // TODO: fix me
  if (n == 1)
    texture.loadFromFile("assets/img/menu/options3.png");
  else if (n == 0 and difficulty == 1)
    texture.loadFromFile("assets/img/menu/options0.png");
  else if (n == 0 and difficulty == 0.5)
    texture.loadFromFile("assets/img/menu/options2.png");
  else if (n == 0 and difficulty == 1.5)
    texture.loadFromFile("assets/img/menu/options1.png");

  // TODO: fix me
  {
    sf::Sprite sprite(texture);
    buffer->draw(sprite);
  }

  window->clear(sf::Color::Black);

  sf::Sprite sprite(buffer->getTexture());
  sprite.setScale(scaleX, scaleY);
  window->draw(sprite);

  //al_draw_bitmap(bitmap, 0, 0, 0);
  //al_destroy_bitmap(bitmap);
  //al_set_target_backbuffer(display);
  //al_clear_to_color(al_map_rgb(0, 0, 0));
  //al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);
}

void Graphics::DrawImage(int a)
{
  //al_set_target_bitmap(buffer);
  //al_clear_to_color(al_map_rgb(0, 0, 0));
  buffer->clear(sf::Color::Black);

  sf::Texture texture;

  if (a == 0)
    texture.loadFromFile("assets/img/menu/credits.png");
  if (a == 1)
    texture.loadFromFile("assets/img/victory.png");
  if (a == 2)
    texture.loadFromFile("assets/img/death.png");

  // TODO: fix me
  {
    sf::Sprite sprite(texture);
    buffer->draw(sprite);
  }

  window->clear(sf::Color::Black);

  sf::Sprite sprite(buffer->getTexture());
  sprite.setScale(scaleX, scaleY);
  window->draw(sprite);

  //al_draw_bitmap(bitmap, 0, 0, 0);
  //al_destroy_bitmap(bitmap);
  //al_set_target_backbuffer(display);
  //al_clear_to_color(al_map_rgb(0, 0, 0));
  //al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);
}

void Graphics::DrawPeach(Entity* Peach)
{
  //al_set_target_bitmap(buffer);
  /*al_draw_bitmap(staticBitmaps[4], Peach->getY(), Peach->getX(), 0);
  al_set_target_backbuffer(display);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);*/


  {
    sf::Sprite sprite(*staticBitmaps[4]);
    sprite.setPosition(Peach->getY(), Peach->getX()); 
    buffer->draw(sprite);
  }
}

void Graphics::DrawStaticBarrels()
{
  //al_set_target_bitmap(buffer);
  //al_draw_bitmap(staticBitmaps[3], 33, 99, 0);
  //al_draw_bitmap(staticBitmaps[3], 33, 120, 0);
  //al_draw_bitmap(staticBitmaps[3], 10, 99, 0);
  //al_draw_bitmap(staticBitmaps[3], 10, 120, 0);
  //al_set_target_backbuffer(display);
  //al_clear_to_color(al_map_rgb(0, 0, 0));
  //al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);


  {
    sf::Sprite sprite(*staticBitmaps[3]);
    //sprite.setScale(scaleX, scaleY);
    sprite.setPosition(33, 99);
    buffer->draw(sprite);

    sprite.setPosition(33, 120);
    buffer->draw(sprite);

    sprite.setPosition(10, 99);
    buffer->draw(sprite);

    sprite.setPosition(10, 120);
    buffer->draw(sprite);
  }
}

void Graphics::DrawKong(Kong* Wukong)
{
  //al_set_target_bitmap(buffer);
  // TODO: use sprite animation class
  if (Wukong->getFrame() > 0 and Wukong->getFrame() <= Wukong->getDifficolta() * 20)
    bitmap.loadFromFile("assets/img/kong/kong1.png");
  else if (Wukong->getFrame() > Wukong->getDifficolta() * 20 and Wukong->getFrame() <= Wukong->getDifficolta() * 40)
    bitmap.loadFromFile("assets/img/kong/kong2.png");
  else if (Wukong->getFrame() > Wukong->getDifficolta() * 40 and Wukong->getFrame() <= Wukong->getDifficolta() * 60)
    bitmap.loadFromFile("assets/img/kong/kong3.png");
  else if (Wukong->getFrame() > Wukong->getDifficolta() * 60 and Wukong->getFrame() <= Wukong->getDifficolta() * 80)
    bitmap.loadFromFile("assets/img/kong/kong4.png");
  else
    bitmap.loadFromFile("assets/img/kong/kong5.png");

  /*al_draw_bitmap(bitmap, Wukong->getY(), Wukong->getX(), 0);
  al_destroy_bitmap(bitmap);

  al_set_target_backbuffer(display);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);*/
  
  sf::Sprite sprite(bitmap);
  //sprite.setScale(scaleX, scaleY);
  sprite.setPosition(Wukong->getY(), Wukong->getX());
  buffer->draw(sprite);

  Wukong->nextFrame();
}

void Graphics::DrawExplosive(int& frame)
{
  // TODO: use sprite animation class
  //al_set_target_bitmap(buffer);
  if (frame >= 0 and frame < 4)
    bitmap.loadFromFile("assets/img/enemy/fire0.png");
  else if (frame >= 4 and frame < 8)
    bitmap.loadFromFile("assets/img/enemy/fire1.png");
  else if (frame >= 8 and frame < 12)
    bitmap.loadFromFile("assets/img/enemy/fire2.png");
  else if (frame >= 12 and frame < 16)
    bitmap.loadFromFile("assets/img/enemy/fire3.png");

  if (frame >= 15)
    frame = 0;
  else
    frame++;

  //al_draw_bitmap(bitmap, 40, 500, 0);
  //al_destroy_bitmap(bitmap);
  //al_set_target_backbuffer(display);
  //al_clear_to_color(al_map_rgb(0, 0, 0));
  //al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);

  sf::Sprite sprite(bitmap);
  sprite.setPosition(40, 500);
  buffer->draw(sprite);
}


void Graphics::DrawCut(int frame)
{
  DrawMap(true);
  //al_set_target_bitmap(buffer);

  auto drawBitmap = [this](const std::string& path, int x, int y) {
    sf::Texture texture;
    texture.loadFromFile(path);
    sf::Sprite sprite(texture);
    sprite.setPosition(x, y);
    buffer->draw(sprite);
  };

  auto drawStaticBitmap = [this](int index, int x, int y) {
    sf::Sprite sprite(*staticBitmaps[index]);
    sprite.setPosition(x, y);
    buffer->draw(sprite);
  };

  switch (frame)
  {
  case 0:
    //bitmap = al_load_bitmap("../Assets/Bitmaps/Cutscene/kong_standing.png");
    //al_draw_bitmap(bitmap, 60, 80, 0);
    //al_draw_bitmap(staticBitmaps[4], 280, 60, 0);

    drawBitmap("assets/img/cutscene/kong_standing.png", 60, 80);   
    drawStaticBitmap(4, 280, 60);

    break;
  case 1:
    //bitmap = al_load_bitmap("assets/img/Cutscene/kong_standing.png");
    //al_draw_bitmap(bitmap, 200, 20, 0);
    //al_draw_bitmap(staticBitmaps[4], 280, 60, 0);

    drawBitmap("assets/img/cutscene/kong_standing.png", 200, 20); 
    drawStaticBitmap(4, 280, 60); 

    break;
  case 2:
    //bitmap = al_load_bitmap("assets/img/Cutscene/kong_standing.png");
    //al_draw_bitmap(bitmap, 220, 20, 0);
    //al_draw_bitmap(staticBitmaps[4], 280, 60, 0);

    drawBitmap("assets/img/cutscene/kong_standing.png", 220, 20); 
    drawStaticBitmap(4, 280, 60);
    break;
  case 3:
    //bitmap = al_load_bitmap("assets/img/Cutscene/kong_climbing_left0.png");
    //al_draw_bitmap(bitmap, 140, 60, 0);

    drawBitmap("assets/img/cutscene/kong_climbing_left0.png", 140, 60); 
    break;
  case 4:
    //bitmap = al_load_bitmap("assets/img/Cutscene/kong_climbing_right0.png");
    //al_draw_bitmap(bitmap, 140, 55, 0);

    drawBitmap("assets/img/cutscene/kong_climbing_right0.png", 140, 55);
    break;
  case 5:
    //bitmap = al_load_bitmap("assets/img/Cutscene/kong_climbing_left0.png");
    //al_draw_bitmap(bitmap, 140, 50, 0);

    drawBitmap("assets/img/cutscene/kong_climbing_left0.png", 140, 50); 
    break;
  case 6:
    //bitmap = al_load_bitmap("assets/img/Cutscene/kong_climbing_right0.png");
    //al_draw_bitmap(bitmap, 140, 45, 0);

    drawBitmap("assets/img/cutscene/kong_climbing_right0.png", 140, 45);  
    break;
  case 7:
    //bitmap = al_load_bitmap("assets/img/Cutscene/kong_climbing_left0.png");
    //al_draw_bitmap(bitmap, 140, 40, 0);

    drawBitmap("assets/img/cutscene/kong_climbing_left0.png", 140, 40);
    break;
  case 8:
    //bitmap = al_load_bitmap("assets/img/Cutscene/kong_climbing_right0.png");
    //al_draw_bitmap(bitmap, 140, 35, 0);

    drawBitmap("assets/img/cutscene/kong_climbing_right0.png", 140, 35);  
    break;
  case 9:
    //bitmap = al_load_bitmap("assets/img/Cutscene/kong_climbing_left0.png");
    //al_draw_bitmap(bitmap, 140, 25, 0);
    
    drawBitmap("assets/img/cutscene/kong_climbing_left0.png", 140, 25); 
    break;
  case 10:
    //bitmap = al_load_bitmap("assets/img/Cutscene/kong_climbing_right0.png");
    //al_draw_bitmap(bitmap, 140, 20, 0);

    drawBitmap("assets/img/cutscene/kong_climbing_right0.png", 140, 20);  
    break;
  case 11:
    //bitmap = al_load_bitmap("assets/img/Cutscene/kong_climbing_left0.png");
    //al_draw_bitmap(bitmap, 140, 15, 0);

    drawBitmap  ("assets/img/cutscene/kong_climbing_left0.png", 140, 15);   
    break;
  case 12:
    //bitmap = al_load_bitmap("assets/img/Cutscene/kong_climbing_right0.png");
    //al_draw_bitmap(bitmap, 140, 10, 0);

    drawBitmap("assets/img/cutscene/kong_climbing_right0.png", 140, 10);  
    break;
  case 13:
    //bitmap = al_load_bitmap("assets/img/Cutscene/kong_climbing_left0.png");
    //al_draw_bitmap(bitmap, 140, 5, 0);

    drawBitmap("assets/img/cutscene/kong_climbing_left0.png", 140, 5);  
    break;
  case 14:
    //bitmap = al_load_bitmap("assets/img/Cutscene/kong_standing.png");
    //al_draw_bitmap(bitmap, 60, 80, 0);
    //al_destroy_bitmap(bitmap);

    drawBitmap("assets/img/cutscene/kong_standing.png", 60, 80);  

    //bitmap = al_load_bitmap("assets/img/Player/right1.png");
    //al_draw_bitmap(bitmap, 20, 120, 0);
    drawBitmap("assets/img/player/right1.png", 20, 120);  

    //al_draw_bitmap(staticBitmaps[4], 280, 60, 0);
    drawStaticBitmap(4, 280, 60); 
    break;
  case 15:
    //bitmap = al_load_bitmap("assets/img/Cutscene/kong_onhead.png");
    //al_draw_bitmap(bitmap, 60, 80, 0);
    //al_destroy_bitmap(bitmap);

    drawBitmap("assets/img/cutscene/kong_onhead.png", 60, 80);  

    //bitmap = al_load_bitmap("assets/img/Player/Hammer4R.png");
    //al_draw_bitmap(bitmap, 37, 120, 0);
    drawBitmap("assets/img/player/hammer4r.png", 37, 120);    

    //al_draw_bitmap(staticBitmaps[4], 280, 60, 0);
    drawStaticBitmap(4, 280, 60); 
    break;
  case 16:
    //bitmap = al_load_bitmap("assets/img/Cutscene/kong_knockedout.png");
    //al_draw_bitmap(bitmap, 60, 80, 0);
    //al_destroy_bitmap(bitmap);
    drawBitmap("assets/img/cutscene/kong_knockedout.png", 60, 80);  
    
    //bitmap = al_load_bitmap("assets/img/Player/Hammer4R.png");
    //al_draw_bitmap(bitmap, 37, 120, 0);
    drawBitmap("assets/img/player/hammer4r.png", 37, 120);  

    //al_draw_bitmap(staticBitmaps[4], 280, 60, 0);
    drawStaticBitmap(4, 280, 60);
    break;
  case 17:
    //al_draw_bitmap(staticBitmaps[4], 280, 60, 0);
    drawStaticBitmap(4, 280, 60); 

    //bitmap = al_load_bitmap("assets/img/Player/right1.png");
    //al_draw_bitmap(bitmap, 245, 60, 0);
    drawBitmap("assets/img/player/right1.png", 245, 60);  
    break;
  case 18:
    //al_draw_bitmap(staticBitmaps[4], 280, 60, 1);
    drawStaticBitmap(4, 280, 60);

    //bitmap = al_load_bitmap("assets/img/Player/right1.png");
    //al_draw_bitmap(bitmap, 260, 60, 0);
    //al_destroy_bitmap(bitmap);

    drawBitmap("assets/img/player/right1.png", 260, 60);  

    //bitmap = al_load_bitmap("assets/img/Cutscene/heart.png");
    //al_draw_bitmap(bitmap, 270, 47, 0);
    drawBitmap("assets/img/cutscene/heart.png", 270, 47); 
    break;
  }

 /* al_destroy_bitmap(bitmap);
  al_set_target_backbuffer(display);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);*/

  
}



#if 0
Graphics(sf::RenderWindow* display,
  sf::RenderTexture* buffer,
  int scaleX,
  int scaleY,
  int scaleW,
  int scaleH,
  sf::Font* font,
  sf::Font* fontScore)
{
  allocated = false;
  this->font = font;
  this->fontScore = fontScore;
  this->scaleH = scaleH;
  this->scaleW = scaleW;
  this->scaleX = scaleX;
  this->scaleY = scaleY;
  this->buffer = buffer;
  this->display = display;
  ALLEGRO_BITMAP* icon = al_load_bitmap("../Assets/Bitmaps/icon.png");
  staticBitmaps.push_back(al_load_bitmap("../Assets/Bitmaps/Tiles/scala.png"));
  staticBitmaps.push_back(al_load_bitmap("../Assets/Bitmaps/Tiles/ground.png"));
  staticBitmaps.push_back(al_load_bitmap("../Assets/Bitmaps/hammer.png"));
  staticBitmaps.push_back(al_load_bitmap("../Assets/Bitmaps/Barrel/barrel_standing.png"));
  staticBitmaps.push_back(al_load_bitmap("../Assets/Bitmaps/Peach/peach0.png"));
  staticBitmaps.push_back(al_load_bitmap("../Assets/Bitmaps/Other/oilcan.png"));
  al_set_display_icon(display, icon);
  al_destroy_bitmap(icon);
}
#endif

#if 0
void Graphics::assignGrid(int level)
{
  if (allocated)
  {
    for (int i = 0; i < x; i++)
      delete grid[i];
    delete[] grid;
  }
  ifstream fileinput;
  fileinput.open(string("../Assets/Maps/level" + to_string(level) + ".txt"));
  if (!fileinput)
    cout << "could not initialize level " << level << endl;
  fileinput >> x >> y;
  grid = new int* [x];
  for (int i = 0; i < x; i++)
    grid[i] = new int[y];
  for (int i = 0; i < x; i++)
    for (int j = 0; j < y; j++)
      fileinput >> grid[i][j];
  fileinput.close();
  allocated = true;
}
#endif

#if 0
void Graphics::DrawMap(bool cutScene)
{
  al_set_target_bitmap(buffer);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  for (int i = 0; i < x; i++)
  {
    for (int j = 0; j < y; j++)
    {
      switch (grid[i][j])
      {
      case 1:
        al_draw_bitmap(staticBitmaps[0], j * 20, i * 20, 0);
        break;
      case 2:
        al_draw_bitmap(staticBitmaps[1], j * 20, i * 20, 0);
        break;
      }
    }
  }
  if (cutScene == false)
    al_draw_bitmap(staticBitmaps[5], 40, 520, 0);             //barile incendiato
  al_set_target_backbuffer(display);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);
}
#endif

#if 0
void Graphics::DrawHammer()
{
  al_set_target_bitmap(buffer);
  al_draw_bitmap(staticBitmaps[2], 18 * 20, 21 * 20, 0);
  al_set_target_backbuffer(display);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);
}


void Graphics::DrawPlayerHammer(Player* Play)
{
  al_set_target_bitmap(buffer);
  bool decenter = false;
  if (Play->getFrame() >= 0 && Play->getFrame() <= 15 && Play->getHammered())
    bitmap = al_load_bitmap("../Assets/Bitmaps/Player/Hammer4.png");
  else if (Play->getFrame() >= 16 && Play->getFrame() <= 33 && Play->getHammered())
    bitmap = al_load_bitmap("../Assets/Bitmaps/Player/Hammer4.png");

  else if (Play->getFrame() >= 0 and Play->getFrame() <= 5)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Player/Hammer1R.png");
  else if (Play->getFrame() >= 6 and Play->getFrame() <= 10)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Player/Hammer3R.png");
  else if (Play->getFrame() >= 11 and Play->getFrame() <= 15)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Player/Hammer5R.png");
  else if (Play->getFrame() >= 16 and Play->getFrame() <= 20)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Player/Hammer1.png");
  else if (Play->getFrame() >= 21 and Play->getFrame() <= 25)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Player/Hammer3.png");
  else if (Play->getFrame() >= 26 and Play->getFrame() <= 30)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Player/Hammer5.png");
  if (!Play->getHammered())
    al_draw_bitmap(bitmap, Play->getY(), Play->getX(), 0);
  else
    if (Play->getDirection() == LEFT)
      al_draw_bitmap(bitmap, Play->getY(), Play->getX(), 0);
    else
      al_draw_bitmap(bitmap, Play->getY(), Play->getX(), 1);
  al_destroy_bitmap(bitmap);
  al_set_target_backbuffer(display);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);
}

void Graphics::DrawPlayer(Player* Play)
{

  al_set_target_bitmap(buffer);
  if (Play->getFrame() >= 0 and Play->getFrame() <= 5)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Player/right1.png");
  else if (Play->getFrame() >= 6 and Play->getFrame() <= 10)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Player/right2.png");
  else if (Play->getFrame() >= 11 and Play->getFrame() <= 15)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Player/right3.png");
  else if (Play->getFrame() >= 16 and Play->getFrame() <= 20)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Player/left1.png");
  else if (Play->getFrame() >= 21 and Play->getFrame() <= 25)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Player/left2.png");
  else if (Play->getFrame() >= 26 and Play->getFrame() <= 30)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Player/left3.png");
  else if (Play->getFrame() >= 31 and Play->getFrame() <= 33)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Player/climb1.png");
  else if (Play->getFrame() >= 34 and Play->getFrame() <= 36)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Player/climb2.png");
  else if (Play->getFrame() == 37)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Player/jumpr.png");
  else if (Play->getFrame() == 38)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Player/jumpl.png");
  else if (Play->getFrame() == 39)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Player/rightfall.png");
  else if (Play->getFrame() == 40)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Player/leftfall.png");
  al_draw_bitmap(bitmap, Play->getY(), Play->getX(), 0);
  al_destroy_bitmap(bitmap);
  al_set_target_backbuffer(display);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);
}


void Graphics::DrawKong(Kong* Wukong)
{
  al_set_target_bitmap(buffer);
  if (Wukong->getFrame() > 0 and Wukong->getFrame() <= Wukong->getDifficolta() * 20)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Kong/kong1.png");
  else if (Wukong->getFrame() > Wukong->getDifficolta() * 20 and Wukong->getFrame() <= Wukong->getDifficolta() * 40)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Kong/kong2.png");
  else if (Wukong->getFrame() > Wukong->getDifficolta() * 40 and Wukong->getFrame() <= Wukong->getDifficolta() * 60)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Kong/kong3.png");
  else if (Wukong->getFrame() > Wukong->getDifficolta() * 60 and Wukong->getFrame() <= Wukong->getDifficolta() * 80)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Kong/kong4.png");
  else
    bitmap = al_load_bitmap("../Assets/Bitmaps/Kong/kong5.png");
  al_draw_bitmap(bitmap, Wukong->getY(), Wukong->getX(), 0);
  al_destroy_bitmap(bitmap);
  al_set_target_backbuffer(display);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);
  Wukong->nextFrame();
}


void Graphics::DrawStaticBarrels()
{
  al_set_target_bitmap(buffer);
  al_draw_bitmap(staticBitmaps[3], 33, 99, 0);
  al_draw_bitmap(staticBitmaps[3], 33, 120, 0);
  al_draw_bitmap(staticBitmaps[3], 10, 99, 0);
  al_draw_bitmap(staticBitmaps[3], 10, 120, 0);
  al_set_target_backbuffer(display);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);
}

void Graphics::DrawExplosive(int& frame)
{
  al_set_target_bitmap(buffer);
  if (frame >= 0 and frame < 4)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Other/fire0.png");
  else if (frame >= 4 and frame < 8)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Other/fire1.png");
  else if (frame >= 8 and frame < 12)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Other/fire2.png");
  else if (frame >= 12 and frame < 16)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Other/fire3.png");
  if (frame >= 15)
    frame = 0;
  else
    frame++;
  al_draw_bitmap(bitmap, 40, 500, 0);
  al_destroy_bitmap(bitmap);
  al_set_target_backbuffer(display);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);
}

void Graphics::DrawBarrel(Barrel& Bar)
{
  al_set_target_bitmap(buffer);
  if (Bar.isFalling())
  {
    if (Bar.getFrame() >= 0 and Bar.getFrame() < 5)
      bitmap = al_load_bitmap("../Assets/Bitmaps/Barrel/barrelfallingN1.png");
    else if (Bar.getFrame() >= 5 and Bar.getFrame() <= 7)
      bitmap = al_load_bitmap("../Assets/Bitmaps/Barrel/barrelfallingN2.png");
    if (Bar.getFrame() >= 7)
      Bar.setFrame(0);
    else
      Bar.nextFrame();
    al_draw_bitmap(bitmap, Bar.getY(), Bar.getX(), 0);
    al_destroy_bitmap(bitmap);
    al_set_target_backbuffer(display);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);
  }
  else
  {
    if (Bar.getFrame() == 0)
      bitmap = al_load_bitmap("../Assets/Bitmaps/Barrel/barrel1.png");
    if (Bar.getFrame() == 1)
      bitmap = al_load_bitmap("../Assets/Bitmaps/Barrel/barrel2.png");
    if (Bar.getFrame() == 2)
      bitmap = al_load_bitmap("../Assets/Bitmaps/Barrel/barrel3.png");
    if (Bar.getFrame() == 3)
      bitmap = al_load_bitmap("../Assets/Bitmaps/Barrel/barrel4.png");
    if (Bar.getFrame() == 4)
      bitmap = al_load_bitmap("../Assets/Bitmaps/Barrel/barrel5.png");
    if (Bar.getFrame() == 5)
      bitmap = al_load_bitmap("../Assets/Bitmaps/Barrel/barrel6.png");
    if (Bar.getFrame() == 6)
      bitmap = al_load_bitmap("../Assets/Bitmaps/Barrel/barrel7.png");
    if (Bar.getFrame() == 7)
      bitmap = al_load_bitmap("../Assets/Bitmaps/Barrel/barrel8.png");
    if (Bar.getFrame() >= 7)
      Bar.setFrame(0);
    else
      Bar.nextFrame();

    if (Bar.getDirection() == RIGHT)
      al_draw_bitmap(bitmap, Bar.getY(), Bar.getX(), 0);
    else
      al_draw_bitmap(bitmap, Bar.getY(), Bar.getX(), 1);
    al_destroy_bitmap(bitmap);
    al_set_target_backbuffer(display);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);
  }

}

void Graphics::DrawPeach(Entity* Peach)
{
  al_set_target_bitmap(buffer);
  al_draw_bitmap(staticBitmaps[4], Peach->getY(), Peach->getX(), 0);
  al_set_target_backbuffer(display);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);
}
void Graphics::DrawMenu(short unsigned n)
{
  al_set_target_bitmap(buffer);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  switch (n)
  {
  case 0:
    bitmap = al_load_bitmap("../Assets/Bitmaps/Menu/Menu0.png");
    break;
  case 1:
    bitmap = al_load_bitmap("../Assets/Bitmaps/Menu/Menu1.png");
    break;
  case 2:
    bitmap = al_load_bitmap("../Assets/Bitmaps/Menu/Menu2.png");
    break;
  case 3:
    bitmap = al_load_bitmap("../Assets/Bitmaps/Menu/Menu3.png");
    break;
  }
  al_draw_bitmap(bitmap, 0, 0, 0);
  al_destroy_bitmap(bitmap);
  al_set_target_backbuffer(display);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);
}
void Graphics::DrawInstantScore(int opt, int x, int y)
{
  al_set_target_bitmap(buffer);
  if (opt == 1)
  {
    al_draw_text(font, al_map_rgb(255, 255, 255), y, x, 0, "300");
  }
  else
  {
    al_draw_text(font, al_map_rgb(255, 255, 255), y, x, 0, "100");
  }
  al_set_target_backbuffer(display);
  al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);
}
void Graphics::DrawDelete(int& x, int& y)
{
  if (x == 0 and y == 0)
    return;
  al_set_target_bitmap(buffer);
  bitmap = al_load_bitmap("../Assets/Bitmaps/Barrel/deletebarrel.png");
  al_draw_bitmap(bitmap, y, x, 0);
  al_destroy_bitmap(bitmap);
  al_set_target_backbuffer(display);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);
  x = 0;
  y = 0;
}
void Graphics::DrawScore(int score)
{
  al_set_target_bitmap(buffer);
  al_draw_textf(fontScore, al_map_rgb(255, 255, 255), 315, 50, 0, " SCORE");
  al_draw_textf(fontScore, al_map_rgb(255, 0, 0), 329, 75, 0, "%d", score);
  al_set_target_backbuffer(display);
  al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);
}
void Graphics::DrawLives(int lifes)
{
  al_set_target_bitmap(buffer);
  bitmap = al_load_bitmap("../Assets/Bitmaps/life.png");
  for (int c = 0; c < lifes; c++)
  {
    al_draw_bitmap(bitmap, 335 + (c * 22), 32, 0);
  }
  al_destroy_bitmap(bitmap);
  al_set_target_backbuffer(display);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);
}
void Graphics::DrawOptions(int n, float difficulty)
{
  al_set_target_bitmap(buffer);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  if (n == 1)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Menu/Options3.png");
  else if (n == 0 and difficulty == 1)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Menu/Options0.png");
  else if (n == 0 and difficulty == 0.5)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Menu/Options2.png");
  else if (n == 0 and difficulty == 1.5)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Menu/Options1.png");
  al_draw_bitmap(bitmap, 0, 0, 0);
  al_destroy_bitmap(bitmap);
  al_set_target_backbuffer(display);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);
}
void Graphics::DrawImage(int a)
{
  al_set_target_bitmap(buffer);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  if (a == 0)
    bitmap = al_load_bitmap("../Assets/Bitmaps/Menu/Credits.png");
  if (a == 1)
    bitmap = al_load_bitmap("../Assets/Bitmaps/victory.png");
  if (a == 2)
    bitmap = al_load_bitmap("../Assets/Bitmaps/death.png");
  al_draw_bitmap(bitmap, 0, 0, 0);
  al_destroy_bitmap(bitmap);
  al_set_target_backbuffer(display);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);
}
void Graphics::DrawCut(int frame)
{
  DrawMap(true);
  al_set_target_bitmap(buffer);
  switch (frame)
  {
  case 0:
    bitmap = al_load_bitmap("../Assets/Bitmaps/Cutscene/kong_standing.png");
    al_draw_bitmap(bitmap, 60, 80, 0);
    al_draw_bitmap(staticBitmaps[4], 280, 60, 0);
    break;
  case 1:
    bitmap = al_load_bitmap("../Assets/Bitmaps/Cutscene/kong_standing.png");
    al_draw_bitmap(bitmap, 200, 20, 0);
    al_draw_bitmap(staticBitmaps[4], 280, 60, 0);
    break;
  case 2:
    bitmap = al_load_bitmap("../Assets/Bitmaps/Cutscene/kong_standing.png");
    al_draw_bitmap(bitmap, 220, 20, 0);
    al_draw_bitmap(staticBitmaps[4], 280, 60, 0);
    break;
  case 3:
    bitmap = al_load_bitmap("../Assets/Bitmaps/Cutscene/kong_climbing_left0.png");
    al_draw_bitmap(bitmap, 140, 60, 0);
    break;
  case 4:
    bitmap = al_load_bitmap("../Assets/Bitmaps/Cutscene/kong_climbing_right0.png");
    al_draw_bitmap(bitmap, 140, 55, 0);
    break;
  case 5:
    bitmap = al_load_bitmap("../Assets/Bitmaps/Cutscene/kong_climbing_left0.png");
    al_draw_bitmap(bitmap, 140, 50, 0);
    break;
  case 6:
    bitmap = al_load_bitmap("../Assets/Bitmaps/Cutscene/kong_climbing_right0.png");
    al_draw_bitmap(bitmap, 140, 45, 0);
    break;
  case 7:
    bitmap = al_load_bitmap("../Assets/Bitmaps/Cutscene/kong_climbing_left0.png");
    al_draw_bitmap(bitmap, 140, 40, 0);
    break;
  case 8:
    bitmap = al_load_bitmap("../Assets/Bitmaps/Cutscene/kong_climbing_right0.png");
    al_draw_bitmap(bitmap, 140, 35, 0);
    break;
  case 9:
    bitmap = al_load_bitmap("../Assets/Bitmaps/Cutscene/kong_climbing_left0.png");
    al_draw_bitmap(bitmap, 140, 25, 0);
    break;
  case 10:
    bitmap = al_load_bitmap("../Assets/Bitmaps/Cutscene/kong_climbing_right0.png");
    al_draw_bitmap(bitmap, 140, 20, 0);
    break;
  case 11:
    bitmap = al_load_bitmap("../Assets/Bitmaps/Cutscene/kong_climbing_left0.png");
    al_draw_bitmap(bitmap, 140, 15, 0);
    break;
  case 12:
    bitmap = al_load_bitmap("../Assets/Bitmaps/Cutscene/kong_climbing_right0.png");
    al_draw_bitmap(bitmap, 140, 10, 0);
    break;
  case 13:
    bitmap = al_load_bitmap("../Assets/Bitmaps/Cutscene/kong_climbing_left0.png");
    al_draw_bitmap(bitmap, 140, 5, 0);
    break;
  case 14:
    bitmap = al_load_bitmap("../Assets/Bitmaps/Cutscene/kong_standing.png");
    al_draw_bitmap(bitmap, 60, 80, 0);
    al_destroy_bitmap(bitmap);
    bitmap = al_load_bitmap("../Assets/Bitmaps/Player/right1.png");
    al_draw_bitmap(bitmap, 20, 120, 0);
    al_draw_bitmap(staticBitmaps[4], 280, 60, 0);
    break;
  case 15:
    bitmap = al_load_bitmap("../Assets/Bitmaps/Cutscene/kong_onhead.png");
    al_draw_bitmap(bitmap, 60, 80, 0);
    al_destroy_bitmap(bitmap);
    bitmap = al_load_bitmap("../Assets/Bitmaps/Player/Hammer4R.png");
    al_draw_bitmap(bitmap, 37, 120, 0);
    al_draw_bitmap(staticBitmaps[4], 280, 60, 0);
    break;
  case 16:
    bitmap = al_load_bitmap("../Assets/Bitmaps/Cutscene/kong_knockedout.png");
    al_draw_bitmap(bitmap, 60, 80, 0);
    al_destroy_bitmap(bitmap);
    bitmap = al_load_bitmap("../Assets/Bitmaps/Player/Hammer4R.png");
    al_draw_bitmap(bitmap, 37, 120, 0);
    al_draw_bitmap(staticBitmaps[4], 280, 60, 0);
    break;
  case 17:
    al_draw_bitmap(staticBitmaps[4], 280, 60, 0);
    bitmap = al_load_bitmap("../Assets/Bitmaps/Player/right1.png");
    al_draw_bitmap(bitmap, 245, 60, 0);
    break;
  case 18:
    al_draw_bitmap(staticBitmaps[4], 280, 60, 1);
    bitmap = al_load_bitmap("../Assets/Bitmaps/Player/right1.png");
    al_draw_bitmap(bitmap, 260, 60, 0);
    al_destroy_bitmap(bitmap);
    bitmap = al_load_bitmap("../Assets/Bitmaps/Cutscene/heart.png");
    al_draw_bitmap(bitmap, 270, 47, 0);
    break;
  }
  al_destroy_bitmap(bitmap);
  al_set_target_backbuffer(display);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_scaled_bitmap(buffer, 0, 0, l, h, scaleX, scaleY, scaleW, scaleH, 0);
}

Graphics::Graphics(sf::RenderWindow* display, sf::Texture* buffer, int scaleX, int scaleY, int scaleW, int scaleH, sf::Font* font, sf::Font* fontScore)
{
}
Graphics::~Graphics()
{
  if (allocated)
  {
    for (int i = 0; i < x; i++)
      delete grid[i];
    delete[] grid;
  }
  al_destroy_bitmap(buffer);
  for (int i = 0; i < staticBitmaps.size(); i++)
    al_destroy_bitmap(staticBitmaps[i]);
}

#endif

