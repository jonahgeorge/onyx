#include <SFML/Graphics.hpp>
#include <SFML/Window/Input.hpp>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <sstream>
#include <iomanip>
#include <vector>

#include "Player.h"

using namespace std;

const int WindowWidth = 1366, WindowHeight = 768; //Window Size
const int GameWidth = 100000, GameHeight = 100000; //World Size

const float pi = 3.1415926535897932364;

Player::Player(sf::RenderWindow &window, bool SW, int PCH, int PMH, int PCE, int PME, float PCF, float PMF, int PL, float PCEX, float PMEX, float PS, int PH, int PR, int PD, float PA, int PC):

            ShieldsWork(SW),
           PlayerCurrentHealth(PCH),
           PlayerMaxHealth(PMH),
           PlayerCurrentEnergy(PCE),
           PlayerMaxEnergy(PME),
           PlayerCurrentFuel(PCF),
           PlayerMaxFuel(PMF),
           PlayerLevel(PL),
           PlayerCurrentExp(PCEX),
           PlayerMaxExp(PMEX),
           PlayerSpeed(PS),
           PlayerHeading(PH),
           PlayerRange(PR),
           PlayerDamage(PD),
           PlayerArmor(PA),
           PlayerCurrency(PC),
           Window(window)
{}

void Player::WayPointCalc(int ViewX, int ViewY)
{
    RenderWayPoint1X = GlobalWayPoint1X;// - ViewX;
    RenderWayPoint1Y = GlobalWayPoint1Y;// - ViewY;

    RenderWayPoint2X = GlobalWayPoint2X;// - ViewX;
    RenderWayPoint2Y = GlobalWayPoint2Y;// - ViewY;

    RenderWayPoint3X = GlobalWayPoint3X;// - ViewX;
    RenderWayPoint3Y = GlobalWayPoint3Y;// - ViewY;
}

void Player::ScreenWrap(int ViewX, int ViewY) //Window Shift
{
        if (GlobalPlayerX > GameWidth) {GlobalPlayerX = 0;}
        if (GlobalPlayerY > GameHeight) {GlobalPlayerY = 0 + 5;}
        if (GlobalPlayerX < 0) {GlobalPlayerX = GameWidth - 5;}
        if (GlobalPlayerY < 0) {GlobalPlayerY = GameHeight - 5;}

}

void Player::RenderCalc(int ViewX, int ViewY)
{
    RenderPlayerX = GlobalPlayerX - ViewX;
    RenderPlayerY = GlobalPlayerY - ViewY;
}

void Player::Regulations(int ViewX, int ViewY)
{
        if (PlayerCurrentEnergy == 0) {ShieldsWork = false;}

        if (ShieldsOn == true && ShieldsWork == true)
        {
            PlayerArmor = 999999999999999999;
            PlayerCurrentEnergy -= 2;
        }
        else if(ShieldsOn == false && ShieldsWork == true)
        {
            PlayerArmor = 1;
            PlayerCurrentEnergy += 2;
        }

        if (PlayerCurrentHealth < 0) {PlayerCurrentHealth = 0;}
        else if (PlayerCurrentHealth > PlayerMaxHealth) {PlayerCurrentHealth = PlayerMaxHealth;}

        if (PlayerCurrentEnergy < 0) {PlayerCurrentEnergy = 0;}
        else if (PlayerCurrentEnergy > PlayerMaxEnergy) {PlayerCurrentEnergy = PlayerMaxEnergy;}

        if (PlayerCurrentFuel < 0) {PlayerCurrentFuel = 0;}
        else if (PlayerCurrentFuel > PlayerMaxFuel) {PlayerCurrentFuel = PlayerMaxFuel;}

        if (PlayerCurrentExp < 0) {PlayerCurrentExp = 0;}
        else if (PlayerCurrentExp >= PlayerMaxExp)
            {
                PlayerLevel += 1;
                PlayerCurrentExp = 0;
                PlayerMaxExp = PlayerMaxExp * 1.5;
                cout <<"Player Level: " << PlayerLevel << endl;
            }

        RenderCalc(ViewX, ViewY);
}

void Player::WayPoint1(int ViewX, int ViewY)
{
//    const sf::Input& Input = Window.GetInput();
//    sf::Vector2f MousePos = Window.ConvertCoords(Window.GetInput().GetMouseX(), Window.GetInput().GetMouseY());
//
//    GlobalWayPoint1X = MousePos.x;
//    GlobalWayPoint1Y = MousePos.y;
}

void Player::WayPoint2(int ViewX, int ViewY)
{
//    const sf::Input& Input = Window.GetInput();
//
//    GlobalWayPoint2X = Input.GetMouseX() + ViewX;
//    GlobalWayPoint2Y = Input.GetMouseY() + ViewY;
}

void Player::WayPoint3(int ViewX, int ViewY)
{
//    const sf::Input& Input = Window.GetInput();
//
//    GlobalWayPoint3X = Input.GetMouseX() + ViewX;
//    GlobalWayPoint3Y = Input.GetMouseY() + ViewY;
}

void Player::WayPointDraw()
{
    Window.Draw(sf::Shape::Line(RenderPlayerX, RenderPlayerY, RenderWayPoint1X, RenderWayPoint1Y, 1.f, sf::Color::Green));
    Window.Draw(sf::Shape::Circle(RenderWayPoint1X, RenderWayPoint1Y, 2.f, sf::Color::Green));
    Window.Draw(sf::Shape::Line(RenderWayPoint1X, RenderWayPoint1Y, RenderWayPoint2X, RenderWayPoint2Y, 1.f, sf::Color::Green));
    Window.Draw(sf::Shape::Circle(RenderWayPoint2X, RenderWayPoint2Y, 2.f, sf::Color::Green));
    Window.Draw(sf::Shape::Line(RenderWayPoint2X, RenderWayPoint2Y, RenderWayPoint3X, RenderWayPoint3Y, 1.f, sf::Color::Green));
    Window.Draw(sf::Shape::Circle(RenderWayPoint3X, RenderWayPoint3Y, 2.f, sf::Color::Green));
}

void Player::WMove()
{
//    PlayerX = (PlayerSpeed * cos(0.017453277777 * PlayerHeading)) + PlayerX;
//    PlayerY = (PlayerSpeed * sin(0.017453277777 * PlayerHeading)) + PlayerY; //0.017453277777 *
//    cout << PlayerX << " , " << PlayerY << endl;
    if (PlayerCurrentFuel > 1)
    {
        VPlayerX += (cos(0.017453277777 * PlayerHeading)) * PlayerSpeed;
        VPlayerY += (sin(0.017453277777 * PlayerHeading)) * PlayerSpeed;
        PlayerCurrentFuel -= .01;

    }
}

void Player::SMove()
{
        VPlayerX += (cos(0.017453277777 * PlayerHeading)) * (PlayerSpeed * -1);
        VPlayerY += (sin(0.017453277777 * PlayerHeading)) * (PlayerSpeed * -1);
}

void Player::AMove()
{
    PlayerHeading -= 15;
    if (PlayerHeading < 0)
    {
        PlayerHeading = 360;
    }
}

void Player::DMove()
{
    PlayerHeading += 15;
    if (PlayerHeading > 360)
    {
        PlayerHeading = 0;
    }
}

void Player::Move()
{
    if (GlobalPlayerY != GlobalWayPoint1Y && GlobalPlayerY != GlobalWayPoint1Y)
    {
        PlayerHeading = atan2(GlobalWayPoint1Y - GlobalPlayerY, GlobalWayPoint1X - GlobalPlayerX) * 180 / pi;

        GlobalPlayerX += cos(PlayerHeading * pi / 180) * PlayerSpeed;
        GlobalPlayerY += sin(PlayerHeading * pi / 180) * PlayerSpeed;

        if ((GlobalPlayerY - GlobalWayPoint1Y >= 5 * -1 && GlobalPlayerY <= GlobalWayPoint1Y) || (GlobalPlayerY - GlobalWayPoint1Y <= 5 && GlobalPlayerY >= GlobalWayPoint1Y))
        {
            if ((GlobalPlayerX - GlobalWayPoint1X >= 5 * -1 && GlobalPlayerX <= GlobalWayPoint1X) || (GlobalPlayerX - GlobalWayPoint1X <= 5 && GlobalPlayerX >= GlobalWayPoint1X))
            {
                GlobalWayPoint1X = GlobalWayPoint2X;
                GlobalWayPoint1Y = GlobalWayPoint2Y;

                GlobalWayPoint2X = GlobalWayPoint3X;
                GlobalWayPoint2Y = GlobalWayPoint3Y;
            }
        }
    }
}


void Player::Thrust()
{
    if (PlayerCurrentEnergy >= 25)
    {
    PlayerCurrentEnergy -= 25;

    cout << "Warping...\n" << GlobalPlayerX << ", " << GlobalPlayerY << endl;

    GlobalPlayerX = GlobalWayPoint1X;
    GlobalPlayerY = GlobalWayPoint1Y;

    cout << "Exiting SlipStream...\n" << GlobalPlayerX << ", " << GlobalPlayerY << endl;
    }
    else if (PlayerCurrentEnergy < 25)
    {
    cout << "Insufficient Energy\n";
    }

        PlayerCurrentFuel -= 5;
}
