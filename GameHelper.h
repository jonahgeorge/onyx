#ifndef GAMEHELPER_H_INCLUDED
#define GAMEHELPER_H_INCLUDED

class GameHelper
{
    public:
    GameHelper (sf::RenderWindow &window, int PC = 4, int SC = 5000, int RC = 50, int AS = 250, int YC = 100, bool DB = false, bool MS = false);

    int BulletCount;

    int StarCount;
    int PlanetCount;

    int AsteroidCount;

    int RedCount;
    int GreenCount;
    int YellowCount;

    int ViewX, ViewY;

    int ScreenX, ScreenY;

    bool Debug;
    bool Music;

    void RenderView();

    private:
    sf::RenderWindow &Window;
};

GameHelper::GameHelper(sf::RenderWindow &window, int PC, int SC, int RC, int AS, int YC, bool DB, bool MS):
    PlanetCount(PC),
    StarCount(SC),
    RedCount(RC),
    AsteroidCount(AS),
    YellowCount(YC),
    Debug(DB),
    Music(MS),
    Window(window)

{}

void GameHelper::RenderView()
{
//    ScreenX = ViewX + ScreenX;
//    ScreenY = ViewY + ScreenY;
}




#endif // GAMEHELPER_H_INCLUDED
