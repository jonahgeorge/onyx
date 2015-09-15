#include <SFML/Graphics.hpp>
#include <SFML/Window/Input.hpp>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <sstream>
#include <iomanip>
#include <vector>

#include "Asteroid.h"

const int WindowWidth = 1366, WindowHeight = 768; //Window Size
const int GameWidth = 10000, GameHeight = 10000; //World Size

using namespace std;

Asteroid::Asteroid(sf::RenderWindow &window, float AS, int AR, int AA, int AMH):

           AsteroidSpeed(AS),
           AsteroidRange(AR),
           AsteroidAttack(AA),
           AsteroidMaxHealth(AMH),
           Window (window)
{}

void Asteroid::CheckDead(int c)
{
    if (AsteroidCurrentHealth[c] <= 0)
    {
        IsDead[c] = true;
    }
}

void Asteroid::Dead(int c, sf::Sprite* exploAsterSprite, bool Debug, int PlayerCurrency)
{
    if (IsDead[c] == true)
    {
        exploAsterSprite[c].SetPosition(RenderAsteroidX[c], RenderAsteroidY[c]);
        Window.Draw(exploAsterSprite[c]);

        AsteroidCurrentHealth[c] = AsteroidMaxHealth;

        if (Debug == true) {cout << "Asteroid #" << c << " || Terminated\n";}

        GlobalAsteroidX[c] = rand()%GameWidth + 1;
        GlobalAsteroidY[c] = rand()%GameHeight + 1;

        PlayerCurrency += 5;
    }
}

void Asteroid::CheckDraw(int c, int ViewX, int ViewY)
{
    if ((GlobalAsteroidY[c] - ViewY >= WindowHeight * -1 && GlobalAsteroidY[c] <= ViewY) || (GlobalAsteroidY[c] - ViewY <= WindowHeight && GlobalAsteroidY[c] >= ViewY))
    {
        if ((GlobalAsteroidX[c] - ViewX >= WindowWidth * -1 && GlobalAsteroidX[c] <= ViewX) || (GlobalAsteroidX[c] - ViewX <= WindowWidth && GlobalAsteroidX[c] >= ViewX))
        {
            IsDrawable[c] = true;
        }
    }

}

void Asteroid::Draw(int c, int AsteroidCount, sf::Sprite* asteroidSprite)
{
    if (IsDrawable[c] == true)
    {
        if (IsSelect[c] == true)
        {
            Window.Draw(sf::Shape::Circle(RenderAsteroidX[c], RenderAsteroidY[c], 20.f, sf::Color(125,255,0,100), 1.f, sf::Color::Green));
        }

        asteroidSprite[c].SetPosition(RenderAsteroidX[c],RenderAsteroidY[c]);
        asteroidSprite[c].Rotate(1);
        Window.Draw(asteroidSprite[c]);

//        Window.Draw(sf::Shape::Circle(RenderAsteroidX[c], RenderAsteroidY[c], 5.f, sf::Color::Magenta));
    }
}

void Asteroid::CheckSelect(int c, int GlobalSelectBox1X, int GlobalSelectBox1Y, int GlobalSelectBox2X, int GlobalSelectBox2Y)
{
    if ((GlobalAsteroidY[c] >= GlobalSelectBox1Y && GlobalAsteroidY[c] <= GlobalSelectBox2Y) || (GlobalAsteroidY[c] >= GlobalSelectBox2Y && GlobalAsteroidY[c] <= GlobalSelectBox1Y))
    {
        if ((GlobalAsteroidX[c] >= GlobalSelectBox1X && GlobalAsteroidX[c] <= GlobalSelectBox2X) || (GlobalAsteroidX[c] >= GlobalSelectBox2X && GlobalAsteroidX[c] <= GlobalSelectBox1X))
        {
            IsSelect[c] = true;
        }
    }
}

void Asteroid::RenderCalc(int AsteroidCount, int ViewX, int ViewY)
{
    for (int c = 0; c < AsteroidCount; c++)
    {
        RenderAsteroidX[c] = GlobalAsteroidX[c] - ViewX;
        RenderAsteroidY[c] = GlobalAsteroidY[c] - ViewY;
    }
}

void Asteroid::Initialize(int AsteroidCount) //randomly generates the X,Y and Heading of asteroids
{
    for (unsigned int cycle = 0; cycle < AsteroidCount; ++cycle)
    {
        GlobalAsteroidX.push_back((rand()%GameWidth) + 1);
        GlobalAsteroidY.push_back((rand()%GameHeight) + 1);

        RenderAsteroidX.push_back(NULL);
        RenderAsteroidY.push_back(NULL);

        AsteroidHeading.push_back((rand()%360) + 1);
        AsteroidCurrentHealth.push_back(100);

        IsDrawable.push_back(false);
        IsSelect.push_back(false);
        IsDead.push_back(false);
    }
}

void Asteroid::Drift(int AsteroidCount)//random drift
{
    for (int c = 0; c < AsteroidCount; c++)
    {
        GlobalAsteroidX[c] = (AsteroidSpeed * cos(0.017453277777 * AsteroidHeading[c])) + GlobalAsteroidX[c];
        GlobalAsteroidY[c] = (AsteroidSpeed * sin(0.017453277777 * AsteroidHeading[c])) + GlobalAsteroidY[c];

//        if (AsteroidX[c] > WindowWidth)
//            AsteroidX[c] = 0;
//        if (AsteroidX[c] < 0)
//            AsteroidX[c] = WindowWidth; //wraps asteroids around the screen
//        if (AsteroidY[c] > WindowHeight)
//            AsteroidY[c] = 0;
//        if (AsteroidY[c] < 0)
//            AsteroidY[c] = WindowHeight;
    }

//        if (PlayerX > EnemyX)
//            EnemyX = EnemyX + EnemySpeed;
////            * App.GetFrameTime();
//        if (PlayerX < EnemyX)
//            EnemyX = EnemyX - EnemySpeed;
////            * App.GetFrameTime();
//        if (PlayerY > EnemyY)
//            EnemyY = EnemyY + EnemySpeed;
////              * App.GetFrameTime();
//        if (PlayerY < EnemyY)
//            EnemyY = EnemyY - EnemySpeed;
////              * App.GetFrameTime();
}

void Asteroid::InRange(int c, float GlobalPlayerX, float GlobalPlayerY, float PlayerArmor, int& PlayerCurrentHealth, int AsteroidCount, bool Debug)
{
        if ((GlobalAsteroidY[c] - GlobalPlayerY >= AsteroidRange * -1 && GlobalAsteroidY[c] <= GlobalPlayerY)
            || (GlobalAsteroidY[c] - GlobalPlayerY <= AsteroidRange && GlobalAsteroidY[c] >= GlobalPlayerY))
        {
            if ((GlobalAsteroidX[c] - GlobalPlayerX >= AsteroidRange * -1 && GlobalAsteroidX[c] <= GlobalPlayerX)
                || (GlobalAsteroidX[c] - GlobalPlayerX <= AsteroidRange && GlobalAsteroidX[c] >= GlobalPlayerX))
            {
                PlayerCurrentHealth -= AsteroidAttack / PlayerArmor;

                if(Debug == true)
                {
                    cout << "Asteroid #" << c <<" (Hit) || Player Health: " << PlayerCurrentHealth << endl;
                }
            }
        }
        else
        {
            //cout << "Asteroid #" << c << " || Not In Range\n";

        }
}
