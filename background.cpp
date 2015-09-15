#include <SFML/Graphics.hpp>
#include <SFML/Window/Input.hpp>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <sstream>
#include <iomanip>
#include <vector>

#include "Background.h"

const int WindowWidth = 1366, WindowHeight = 768; //Window Size
const int GameWidth = 100000, GameHeight = 100000; //World Size

using namespace std;

Star::Star(sf::RenderWindow &window):
Window(window)
{}

void Star::Initialize(int StarCount)
{
    for (unsigned int cycle = 0; cycle < StarCount; ++cycle)
    {
        GlobalStarX.push_back((rand()%GameWidth) + 1);
        GlobalStarY.push_back((rand()%GameHeight) + 1);

        RenderStarX.push_back(NULL);
        RenderStarY.push_back(NULL);

//        StarPos

        IsDrawable.push_back(false);
        StarRad.push_back((rand()%3) + 1);
    }
}

void Star::Draw(int StarCount, int ViewX, int ViewY, int ScreenX, int ScreenY)
{
//        for (int c = 0; c < StarCount; c++)
//        {
////        if ((GlobalStarY[c] - ViewY >= ScreenY * -1 && GlobalStarY[c] <= ViewY) || (GlobalStarY[c] - ViewY <= ScreenY && GlobalStarY[c] >= ViewY))
////            {
////                if ((GlobalStarX[c] - ViewX >= ScreenX * -1 && GlobalStarX[c] <= ViewX) || (GlobalStarX[c] - ViewX <= ScreenX && GlobalStarX[c] >= ViewX))
////                {
////                    IsDrawable[c] = true;
////                    RenderStarX[c] = GlobalStarX[c] - ViewX;//(ScreenX/2);
////                    RenderStarY[c] = GlobalStarY[c] - ViewY;//(ScreenY/2);
//
//                    StarPos[c] = Window.ConvertCoords(GlobalStarX[c], GlobalStarY[c]);
////        Cursor.SetPosition(CursorPos);
////        App.Draw(Cursor);
//
//                    Window.Draw(sf::Shape::Circle(GlobalStarX[c], GlobalStarY[c], StarRad[c], sf::Color(255,255,255,150)));
//                }
//            }
////        }


        for (int c = 0; c < StarCount; c++)
        {
//        if ((GlobalStarY[c] - ViewY >= WindowHeight * -1 && GlobalStarY[c] <= ViewY) || (GlobalStarY[c] - ViewY <= ScreenY && GlobalStarY[c] >= WindowHeight))
//            {
//                if ((GlobalStarX[c] - ViewX >= WindowWidth * -1 && GlobalStarX[c] <= ViewX) || (GlobalStarX[c] - ViewX <= WindowWidth && GlobalStarX[c] >= ViewX))
//                {
                    IsDrawable[c] = true;
                    RenderStarX[c] = GlobalStarX[c] - ViewX;//(ScreenX/2);
                    RenderStarY[c] = GlobalStarY[c] - ViewY;//(ScreenY/2);

//                    Window.Draw(sf::Shape::Circle(RenderStarX[c], RenderStarY[c], StarRad[c], sf::Color(255,255,255,150)));
//                }
//            }
        }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Planet::Planet(sf::RenderWindow &window):
    Window(window)
    {}

void Planet::Initialize(int PlanetCount)
{
    for (unsigned int cycle = 0; cycle < PlanetCount; ++cycle)
    {
        GlobalPlanetX.push_back((rand()%GameWidth) + 1);
        GlobalPlanetY.push_back((rand()%GameHeight) + 1);

        RenderPlanetX.push_back(NULL);
        RenderPlanetY.push_back(NULL);

        PlanetRand.push_back((rand()%4) + 1);
        PlanetSize.push_back((rand()%30) + 1);
        IsDrawable.push_back(false);
    }
}

void Planet::CheckDraw(int PlanetCount, int ViewX, int ViewY)
{
    for (int c = 0; c < PlanetCount; c++)
    {
//        if ((GlobalPlanetY[c] - ViewY >= ((WindowHeight + PlanetSize[c] * 10) * -1) && GlobalPlanetY[c] <= ViewY) || (GlobalPlanetY[c] - ViewY <= (WindowHeight + PlanetSize[c] * 10) && GlobalPlanetY[c] >= ViewY))
//            {
//                if ((GlobalPlanetX[c] - ViewX >= ((WindowWidth + PlanetSize[c] * 10) * -1) && GlobalPlanetX[c] <= ViewX) || (GlobalPlanetX[c] - ViewX <= (WindowWidth + PlanetSize[c] * 10) && GlobalPlanetX[c] >= ViewX))
//                {
                    RenderPlanetX[c] = GlobalPlanetX[c] - ViewX;
                    RenderPlanetY[c] = GlobalPlanetY[c] - ViewY;

                    IsDrawable[c] = true;
//                }
//            }
    }
}


void Planet::Draw(int PlanetCount, sf::Sprite* World1, sf::Sprite* World2, sf::Sprite* World3, sf::Sprite* World4)
{
        for (int c = 0; c < PlanetCount; c++)
        {
            if (IsDrawable[c] == true)
            {
                if (PlanetRand[c] == 1)
                {
                World1[c].SetPosition(RenderPlanetX[c], RenderPlanetY[c]);
                World1[c].SetScale(PlanetSize[c], PlanetSize[c]);
                Window.Draw(World1[c]);

//                    Window.Draw(sf::Shape::Circle(RenderPlanetX[c],RenderPlanetY[c], PlanetSize[c] * 10, sf::Color(0,0,205,200), 2.f, sf::Color(0,0,205)));
                }
                else if (PlanetRand[c] == 2)
                {
                World2[c].SetPosition(RenderPlanetX[c], RenderPlanetY[c]);
                World2[c].SetScale(PlanetSize[c], PlanetSize[c]);
                Window.Draw(World2[c]);

//                    Window.Draw(sf::Shape::Circle(RenderPlanetX[c],RenderPlanetY[c], PlanetSize[c] * 10, sf::Color(255,0,0,200), 2.f, sf::Color(255,0,0)));
                }
                else if (PlanetRand[c] == 3)
                {
                World3[c].SetPosition(RenderPlanetX[c], RenderPlanetY[c]);
                World3[c].SetScale(PlanetSize[c], PlanetSize[c]);
                Window.Draw(World3[c]);

//                    Window.Draw(sf::Shape::Circle(RenderPlanetX[c],RenderPlanetY[c], PlanetSize[c] * 10, sf::Color(255,165,0,200), 2.f, sf::Color(255,165,0)));
                }
                else if (PlanetRand[c] == 4)
                {
                World4[c].SetPosition(RenderPlanetX[c], RenderPlanetY[c]);
                World4[c].SetScale(PlanetSize[c], PlanetSize[c]);
                Window.Draw(World4[c]);

//                    Window.Draw(sf::Shape::Circle(RenderPlanetX[c],RenderPlanetY[c], PlanetSize[c] * 10, sf::Color(0,75,0,200), 2.f, sf::Color::Green));
                }
            }
        }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Moon::Moon(sf::RenderWindow &window):
Window(window)
{}


void Moon::Initialize()
{
    for (unsigned int cycle = 0; cycle < 8; ++cycle)
    {
        GlobalMoonX.push_back((rand()%GameWidth) + 1);
        GlobalMoonY.push_back((rand()%GameHeight) + 1);

        RenderMoonX.push_back(NULL);
        RenderMoonY.push_back(NULL);

        IsDrawable.push_back(false);
//        StationRad.push_back((rand()%3) + 1);
    }
}

void Moon::CheckDraw(int c, int ViewX, int ViewY)
{
//    if ((GlobalMoonY[c] - ViewY >= WindowHeight * -1 && GlobalMoonY[c] <= ViewY) || (GlobalMoonY[c] - ViewY <= WindowHeight && GlobalMoonY[c] >= ViewY))
//    {
//        if ((GlobalMoonX[c] - ViewX >= WindowWidth * -1 && GlobalMoonX[c] <= ViewX) || (GlobalMoonX[c] - ViewX <= WindowWidth && GlobalMoonX[c] >= ViewX))
//        {
            IsDrawable[c] = true;
//        }
//    }
}

void Moon::Draw(int c, int ViewX, int ViewY, sf::Sprite* moonSprite)
{
    if(IsDrawable[c] == true)
    {
            RenderMoonX[c] = GlobalMoonX[c] - ViewX;
            RenderMoonY[c] = GlobalMoonY[c] - ViewY;

                moonSprite[c].SetPosition(RenderMoonX[c], RenderMoonY[c]);
//                moonSprite[c].SetScale(PlanetSize[c] / 10, PlanetSize[c] / 10);
                Window.Draw(moonSprite[c]);

//            Window.Draw(sf::Shape::Circle(RenderMoonX[c], RenderMoonY[c], 50, sf::Color::White));

//            spacestationSprite[c].SetPosition(RenderStationX[c], RenderStationY[c]);
//            spacestationSprite[c].Rotate(0.5);
//            Window.Draw(spacestationSprite[c]);
    }
}

void Moon::Move(int c, vector<float> PlanetSize, vector<float> GlobalPlanetX, vector<float> GlobalPlanetY, sf::Sprite* moonSprite)
{

    GlobalMoonX[c] = ((PlanetSize[c] * 10 + 150) * sin(theta)) + GlobalPlanetX[c];
    GlobalMoonY[c] = ((PlanetSize[c] * 10 + 150) * cos(theta)) + GlobalPlanetY[c];

    moonSprite[c].Rotate(2);

    theta = theta + .0005;
    if (theta >= 360) {theta = 0;}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Spacestation::Spacestation(sf::RenderWindow &window):
Window(window)
{}


void Spacestation::Initialize()
{
    for (unsigned int cycle = 0; cycle < 8; ++cycle)
    {
        GlobalStationX.push_back((rand()%GameWidth) + 1);
        GlobalStationY.push_back((rand()%GameHeight) + 1);

        RenderStationX.push_back(NULL);
        RenderStationY.push_back(NULL);

        IsDrawable.push_back(false);
        StationRad.push_back((rand()%3) + 1);
    }
}

void Spacestation::CheckDraw(int c, int ViewX, int ViewY)
{
//    if ((GlobalStationY[c] - ViewY >= WindowHeight * -1 && GlobalStationY[c] <= ViewY) || (GlobalStationY[c] - ViewY <= WindowHeight && GlobalStationY[c] >= ViewY))
//    {
//        if ((GlobalStationX[c] - ViewX >= WindowWidth * -1 && GlobalStationX[c] <= ViewX) || (GlobalStationX[c] - ViewX <= WindowWidth && GlobalStationX[c] >= ViewX))
//        {
            IsDrawable[c] = true;
//        }
//    }
}

void Spacestation::Draw(int c, int ViewX, int ViewY, sf::Sprite* spacestationSprite)
{
    if(IsDrawable[c] == true)
    {
            RenderStationX[c] = GlobalStationX[c] - ViewX;
            RenderStationY[c] = GlobalStationY[c] - ViewY;

            spacestationSprite[c].SetPosition(RenderStationX[c], RenderStationY[c]);
            spacestationSprite[c].Rotate(0.5);
            Window.Draw(spacestationSprite[c]);
    }
}

void Spacestation::Move(int c, vector<float> GlobalMoonX, vector<float> GlobalMoonY)
{

    GlobalStationX[c] = ((100 + 50) * sin(theta)) + GlobalMoonX[c];
    GlobalStationY[c] = ((100 + 50) * cos(theta)) + GlobalMoonY[c];

    theta = theta + .005;
    if (theta >= 360) {theta = 0;}
}
