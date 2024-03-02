#pragma once  

#include "sounds.hpp"
#include "graphics.hpp"
#include <ctime>


class Game
{
private:
    Sounds* SoundManager = nullptr;
    Graphics* GraphicManager = nullptr;
    float difficulty;
    int hTime = 0;
    bool muted;

public:
    Game(Graphics* g, Sounds* s);

    int runMenu();
    bool runGame(int& lifes,int& level,int &score); 
    void runOptions();
    void runStatic(int a);
    void runCut(int frame);
};