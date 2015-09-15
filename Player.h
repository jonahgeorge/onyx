#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <vector>

using namespace std;

class Player
{
public:
    Player(sf::RenderWindow &window, bool SW = true, int PCH = 100, int PMH = 100, int PCE = 100, int PME = 100, float PCF = 100.f, float PMF = 100.f,
            int PL = 0, float PCEX = 0, float PMEX = 100, float PS = 0.3f, int PH = 0, int PR = 100, int PD = 2, float PA = 1, int PC = 0);

    void ScreenWrap(int, int);
    void Regulations(int, int);
    void RenderCalc(int, int);

    void WayPointCalc(int, int);
    void WayPointDraw();

    void Move();

    void Shoot();
    void Thrust();

    void WMove();
    void AMove();
    void SMove();
    void DMove();

    bool ShieldsOn;
    bool ShieldsWork;

    int PlayerCurrentHealth, PlayerMaxHealth;
    int PlayerCurrentEnergy, PlayerMaxEnergy;
    float PlayerCurrentFuel, PlayerMaxFuel;

    float VPlayerX, VPlayerY;

    int PlayerLevel;
    float PlayerCurrentExp, PlayerMaxExp;

    float GlobalPlayerX, GlobalPlayerY;
    float RenderPlayerX, RenderPlayerY;

    void WayPoint1(int, int);
    void WayPoint2(int, int);
    void WayPoint3(int, int);

    float RenderWayPoint1X, RenderWayPoint1Y;
    float RenderWayPoint2X, RenderWayPoint2Y;
    float RenderWayPoint3X, RenderWayPoint3Y;

    float GlobalWayPoint1X, GlobalWayPoint1Y;
    float GlobalWayPoint2X, GlobalWayPoint2Y;
    float GlobalWayPoint3X, GlobalWayPoint3Y;

    float PlayerSpeed;
    int PlayerHeading;
    int PlayerRange;
    int PlayerDamage;
    float PlayerArmor;
    int PlayerCurrency;

    float MouseX, MouseY;

private:
    sf::RenderWindow &Window;
};

#endif // PlAYER_H_INCLUDED
