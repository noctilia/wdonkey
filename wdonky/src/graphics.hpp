#pragma once  

#include "SFML/Graphics.hpp"

#include <fstream>
#include <vector>  
#include <iostream>

#include "entities.hpp"

class Graphics
{
public:
    int** grid = NULL;
    Graphics (sf::RenderWindow* display,
      sf::RenderTexture* buffer,
      int scaleX, 
      int scaleY,
      int scaleW,
      int scaleH,
      sf::Font* font,
      sf::Font* fontScore);

    ~Graphics();

public:

    void assignGrid(int level);
    void DrawMap (bool cutScene);
    void DrawHammer();
    void DrawPlayerHammer(Player* Play);
    void DrawPlayer(Player* Play);
    void DrawKong(Kong* Wukong);
    void DrawStaticBarrels();
    void DrawExplosive(int& frame);
    void DrawBarrel(Barrel& Bar);
    void DrawPeach(Entity* Peach);
    void DrawMenu(short unsigned n);
    void DrawInstantScore(int opt,int x,int y);
    void DrawDelete(int& x,int& y);
    void DrawScore (int score);
    void DrawLives(int lifes);
    void DrawOptions(int n,float difficulty);
    void DrawImage(int a);
    void DrawCut(int frame);
    
    // TODO: remove me
    bool getEvent(sf::Event& event) {
      return window->pollEvent(event);
    }
    
    sf::RenderWindow* getWindow() { return window; }

    void flipDisplay() {
      buffer->display();
      window->draw(sf::Sprite(buffer->getTexture()));
      window->display();
    }

private:

  void deleteGrid();

  int scaleW;
  int scaleH;
  int scaleX;
  int scaleY;

  sf::RenderWindow* window = nullptr;
  sf::RenderTexture* buffer = nullptr;

  sf::Texture bitmap; // this is used by kong render

  // AnimatitedSprite enemyFire;
  sf::Texture fireTexture;

  sf::Font* font;
  sf::Font* fontScore;

  std::vector <sf::Texture*> staticBitmaps;
  int x = 0;
  int y = 0;
  bool grid_allocated = false;
  int l = 0;
};
