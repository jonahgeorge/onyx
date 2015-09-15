/// Onyx [Alpha Build] -- V.20
/// Jonah George

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Input.hpp>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;
const float pi = 3.1415926535897932364;

const int WindowWidth = 1024, WindowHeight = 768; //Window Size
const int GameWidth = 100000, GameHeight = 100000; //World Size

const int ConstBulletCount = 100;
const int TurretCount = 1;
const int AsteroidCount = 1000;
const int RedCount = 100, YellowCount = 100, GreenCount = 100;
const int PlanetCount = 4, StarCount = 5000, MoonCount = 8;

#include "GameHelper.h"
#include "Background.h" //Star, Planets, Spacestation
#include "Player.h"
#include "Red.h"
#include "Yellow.h"
#include "Green.h"
#include "Asteroid.h"
#include "Turret.h"
#include "Bullet.h"

sf::Sprite* Title; sf::Sprite* Web; sf::Sprite* Background; sf::Sprite* Logo;
sf::Sprite* Easy; sf::Sprite* Med; sf::Sprite* Hard; sf::Sprite* Custom;
sf::Sprite* Von; sf::Sprite* Voff; sf::Sprite* Don; sf::Sprite* Doff;
bool* MouseLeftDown;
sf::Music* MenuMusic;
//
//int LoadMedia();
//int Menu();//sf::Sprite*, sf::Sprite*, sf::Sprite*, sf::Sprite*, sf::Sprite*, sf::Sprite*, sf::Sprite*, sf::Sprite*, sf::Sprite*, sf::Sprite*, sf::Sprite*, sf::Sprite*, bool, sf::Music*);
//int Game(sf::Sprite*, sf::Sprite*, sf::String*, sf::String*, sf::String*, sf::String*, sf::Music*, sf::Sprite*, sf::Sprite*, sf::Sprite*, sf::Sprite*, sf::Sprite*, sf::Sprite*, sf::Sprite*, sf::Sprite*, sf::Sprite*, sf::Sprite*, sf::Sprite*, sf::Sprite*, sf::Sprite*, sf::Sprite*, sf::Sprite*, sf::Sprite*, sf::Sprite*, sf::Sprite*);

int LoadMedia(){
    //------------------------------------------------ Picture Data --------------------------------------------------
    sf::Image* ITitle = new sf::Image();
    if(!ITitle->LoadFromFile("media/images/UI/title.png")) {return EXIT_FAILURE;}

    Title = new sf::Sprite(*ITitle);
    Title->SetCenter(221,51.5);

    sf::Image* difficultyImage = new sf::Image();
    if(!difficultyImage->LoadFromFile("media/images/UI/difficulty.png")) {return EXIT_FAILURE;}

    Easy = new sf::Sprite(*difficultyImage);               //Easy
    Easy->SetSubRect(sf::IntRect(0,0,200,50));
    Easy->SetCenter(100,25);

    Med = new sf::Sprite(*difficultyImage);                //Medium
    Med->SetSubRect(sf::IntRect(0,50,200,100));
    Med->SetCenter(100,25);

    Hard = new sf::Sprite(*difficultyImage);               //Hard
    Hard->SetSubRect(sf::IntRect(0,100,200,150));
    Hard->SetCenter(100,25);

    Custom = new sf::Sprite(*difficultyImage);             //Custom
    Custom->SetSubRect(sf::IntRect(0,150,200,200));
    Custom->SetCenter(100,25);

    sf::Image* sidemenuImage = new sf::Image();
    if(!sidemenuImage->LoadFromFile("media/images/UI/sidemenu.png")) {return EXIT_FAILURE;}

    Don = new sf::Sprite(*sidemenuImage);                  //Debug On
    Don->SetSubRect(sf::IntRect(0,0,178,23));

    Doff = new sf::Sprite(*sidemenuImage);                 //Debug Off
    Doff->SetSubRect(sf::IntRect(0,23,178,46));

    Von = new sf::Sprite(*sidemenuImage);                  //Volume On
    Von->SetSubRect(sf::IntRect(0,46,178,69));

    Voff = new sf::Sprite(*sidemenuImage);                 //Volume Off
    Voff->SetSubRect(sf::IntRect(0,69,178,92));

    Web = new sf::Sprite(*sidemenuImage);                  //Link to Website --> Does not work in fullscreen mode
    Web->SetSubRect(sf::IntRect(0,92,178,115));

    sf::Image* IBack = new sf::Image();
    if(!IBack->LoadFromFile("media/images/UI/SciFiSpace.jpg")) {return EXIT_FAILURE;}

    Background = new sf::Sprite(*IBack);
    Background->SetPosition(0,0);

    sf::Image* ILogo = new sf::Image();
    if(!ILogo->LoadFromFile("media/images/UI/Logo.png")) {return EXIT_FAILURE;}

    Logo = new sf::Sprite(*ILogo);

    sf::Image starImage;
    if(!starImage.LoadFromFile("media/images/star.png")) {}

    sf::Sprite starField[StarCount];
    for (int x = 0; x < StarCount; x++) {
        sf::Sprite TempStar(starImage);
//        TempSYExplo.SetSubRect(sf::IntRect(0,0,80,77));
        TempStar.SetCenter(2.5,2.5);
//        TempStar.SetScale(.5,.5);
        starField[x] = TempStar;
    }
//        starField.SetScale(10,10);
//        starField.SetPosition(-5000,-5000);

    //------------------------------------------------------------------------------------------

    sf::Image explosionImage;
    if(!explosionImage.LoadFromFile("media/images/explosion.png")) {return EXIT_FAILURE;}

    sf::Sprite exploYellowSprite[YellowCount];              //Yellow explosion
    for (int x = 0; x < YellowCount; x++) {
        sf::Sprite TempSYExplo(explosionImage);
        TempSYExplo.SetSubRect(sf::IntRect(0,0,80,77));
        TempSYExplo.SetCenter(40,38);
        TempSYExplo.SetScale(.5,.5);
        exploYellowSprite[x] = TempSYExplo;
    }

    sf::Sprite exploAsterSprite[AsteroidCount];             //Asteroid explosion
    for (int x = 0; x < AsteroidCount; x++) {
        sf::Sprite TempSExplo(explosionImage);
        TempSExplo.SetSubRect(sf::IntRect(160,0,240,71));
        TempSExplo.SetCenter(41,31.5);
        TempSExplo.SetScale(.5,.5);
        exploAsterSprite[x] = TempSExplo;
    }

    sf::Sprite exploRedSprite[RedCount];                    //Red explosion
    for (int x = 0; x < RedCount; x ++) {
        sf::Sprite TempSAExplo(explosionImage);
        TempSAExplo.SetSubRect(sf::IntRect(80,0,160,77));
        TempSAExplo.SetCenter(40,38);
        TempSAExplo.SetScale(.6,.6);
        exploRedSprite[x] = TempSAExplo;
    }

    sf::Image planetsImage;
    if (!planetsImage.LoadFromFile("media/images/planetsImage.png")) {return EXIT_FAILURE;}

    sf::Sprite World1[PlanetCount];
    for (int x = 0; x < PlanetCount; x++) {
        sf::Sprite TempSWorld1(planetsImage);
//       TempSWorld1.SetScale(.5,.5);
        TempSWorld1.SetSubRect(sf::IntRect(0,0,131,131));   //"Ice" World
        TempSWorld1.SetCenter(65.5,65.5);
        World1[x] = TempSWorld1;
    }

    sf::Sprite World2[PlanetCount];
    for (int x = 0; x < PlanetCount; x++) {
        sf::Sprite TempSWorld2(planetsImage);
//       TempSWorld2.SetScale(.5,.5);
        TempSWorld2.SetSubRect(sf::IntRect(131,0,265,129)); //"Earth" World
        TempSWorld2.SetCenter(67,64.5);
        World2[x] = TempSWorld2;
    }

    sf::Sprite World3[PlanetCount];
    for (int x = 0; x < PlanetCount; x++) {
        sf::Sprite TempSWorld3(planetsImage);
//       TempSWorld3.SetScale(.5,.5);
        TempSWorld3.SetSubRect(sf::IntRect(0,131,134,265)); //"Purple" World
        TempSWorld3.SetCenter(67,67);
        World3[x] = TempSWorld3;
    }

    sf::Sprite World4[PlanetCount];
    for (int x = 0; x < PlanetCount; x++) {
        sf::Sprite TempSWorld4(planetsImage);
//       TempSWorld4.SetScale(.5,.5);
        TempSWorld4.SetSubRect(sf::IntRect(133,130,265,265));   //"Green" World
        TempSWorld4.SetCenter(66,67.5);
        World4[x] = TempSWorld4;
    }

    sf::Image moonImage;
    if (!moonImage.LoadFromFile("media/images/moonImage.png")) {return EXIT_FAILURE;}

    sf::Sprite moonSprite[MoonCount];
    for (int x = 0; x < MoonCount; x++) {
        sf::Sprite TempMoonSprite(moonImage);
        TempMoonSprite.SetCenter(28,28);
        TempMoonSprite.SetScale(1.3,1.3);
        moonSprite[x] = TempMoonSprite;
    }

    sf::Image spacestationImage;
    if(!spacestationImage.LoadFromFile("media/images/spacestation.png")) {return EXIT_FAILURE;}

    sf::Sprite spacestationSprite[10];
    for (int x = 0; x < 10; x++) {
        sf::Sprite TempSExplo(spacestationImage);
        TempSExplo.SetCenter(62,62);
        TempSExplo.SetScale(.5,.5);
        spacestationSprite[x] = TempSExplo;
    }

    sf::Image playerImage;
    if(!playerImage.LoadFromFile("media/images/greyshipW.png")) {return EXIT_FAILURE;}

    sf::Sprite playerSprite(playerImage);
//    //SShip.SetSubRect(sf::IntRect(10,10,20,20));
    playerSprite.SetCenter(60, 22);
//    playerSprite.SetScale(.8,.8);
//    SShip.SetBlendMode(sf::Blend::None);

    sf::Image IShipW;
    if(!IShipW.LoadFromFile("media/images/PlayerShipW.png")) {return EXIT_FAILURE;}

    sf::Sprite SShipW(IShipW);
    SShipW.SetCenter(30.5,24);
    SShipW.SetScale(.6,.6);

    sf::Image IShield;
    if(!IShield.LoadFromFile("media/images/shields.png")) {return EXIT_FAILURE;}

    sf::Sprite SShield(IShield);
    SShield.SetCenter(54.5,25);

    sf::Image IGreen;
    if(!IGreen.LoadFromFile("media/images/greenship.png")) {return EXIT_FAILURE;}

    sf::Sprite SGreen[GreenCount];
    for (int x = 0; x < GreenCount; x++) {
        sf::Sprite TempSGreen(IGreen);
        TempSGreen.SetCenter(0,0);
        TempSGreen.SetScale(1,1);
        SGreen[x] = TempSGreen;
    }

    sf::Image yellowImage;
    if(!yellowImage.LoadFromFile("media/images/yellowship.png")) {return EXIT_FAILURE;}

    sf::Sprite yellowSprite[YellowCount];
    for (int x = 0; x < YellowCount; x++) {
        sf::Sprite TempSYellow(yellowImage);
        TempSYellow.SetCenter(12, 10);
        TempSYellow.SetScale(.6,.6);
        yellowSprite[x] = TempSYellow;
    }

    sf::Image redImage;
    if(!redImage.LoadFromFile("media/images/redship.png")) {return EXIT_FAILURE;}
    sf::Sprite redSprite[RedCount];

    for (int x = 0; x < RedCount; x++) {
        sf::Sprite TempSRed(redImage);
        TempSRed.SetCenter(12, 22.5);
        TempSRed.SetScale(.7,.7);
        redSprite[x] = TempSRed;
    }

    sf::Image asteroidImage;
    if(!asteroidImage.LoadFromFile("media/images/asteroid.png")) {return EXIT_FAILURE;}

    sf::Sprite asteroidSprite[AsteroidCount];
    for (int x = 0; x < AsteroidCount; x++) {
        sf::Sprite TempSAster(asteroidImage);
        TempSAster.SetCenter(17, 15);
        TempSAster.SetScale(.4,.4);
        asteroidSprite[x] = TempSAster;
    }

    sf::Image IYellowW;
    if(!IYellowW.LoadFromFile("media/images/yellowshipW.png")) {return EXIT_FAILURE;}

    sf::Sprite SYellowW[YellowCount];
    for (int x = 0; x < YellowCount; x++) {
        sf::Sprite TempSYellowW(IYellowW);
        TempSYellowW.SetCenter(12, 10);
        TempSYellowW.SetScale(.6,.6);
        SYellowW[x] = TempSYellowW;
    }

    sf::Image IRTurret;
    if(!IRTurret.LoadFromFile("media/images/turret.png")) {return EXIT_FAILURE;}

    sf::Sprite SRTurret[TurretCount];
    for (int x = 0; x < TurretCount; x++) {
        sf::Sprite TempSRTurret(IRTurret);
        TempSRTurret.SetCenter(5,6);
        SRTurret[x] = TempSRTurret;
    }

    sf::Image IHealth;
    if(!IHealth.LoadFromFile("media/images/UI/H-E-F.png")) {return EXIT_FAILURE;}

    sf::Sprite SHealth(IHealth);
    //SHealth.SetScale(.9,.9);


    sf::Image ITempTop;
    if(!ITempTop.LoadFromFile("media/images/UI/C-C.png")) {return EXIT_FAILURE;}

    sf::Sprite STempTop(ITempTop);
    //SHealth.SetScale(.9,.9);

//--------------------------------------------------- Music Data -----------------------------------------------------------------

    sf::Music* MenuMusic = new sf::Music();
    if(!MenuMusic->OpenFromFile("media/music/The Son of Flynn.ogg")) {return EXIT_FAILURE;}

    sf::Music GameMusic;
    if(!GameMusic.OpenFromFile("media/music/Separate Ways.ogg")) {return EXIT_FAILURE;}

//--------------------------------------------------- Text Data -----------------------------------------------------------------

    sf::Font MyFont;
    if (!MyFont.LoadFromFile("media/Bedizen.ttf", 25)) {return EXIT_FAILURE;}

    sf::String HealthText;
    HealthText.SetFont(MyFont);
    HealthText.SetColor(sf::Color::Black);
    HealthText.SetSize(20);

    sf::String EnergyText;
    EnergyText.SetFont(MyFont);
    EnergyText.SetColor(sf::Color::Black);
    EnergyText.SetSize(20);

    sf::String FuelText;
    FuelText.SetFont(MyFont);
    FuelText.SetColor(sf::Color::Black);
    FuelText.SetSize(20);

    sf::String CurrencyText;
    CurrencyText.SetFont(MyFont);
    CurrencyText.SetColor(sf::Color::Black);
    CurrencyText.SetSize(20);
}

int Menu() {//sf::Sprite* Title, sf::Sprite* Easy, sf::Sprite* Med, sf::Sprite* Hard, sf::Sprite* Custom, sf::Sprite* Von, sf::Sprite* Voff, sf::Sprite* Don, sf::Sprite* Doff, sf::Sprite* Web, sf::Sprite* Background, bool MouseLeftDown, sf::Music MenuMusic) {

//    MenuMusic->Play();

    sf::RenderWindow Menu;
    Menu.Create(sf::VideoMode::GetDesktopMode(), "Onyx [Alpha]", sf::Style::Fullscreen);

    Title->SetPosition(Menu.GetWidth()/2,100);
    Easy->SetPosition(Menu.GetWidth()/2,340);
    Med->SetPosition(Menu.GetWidth()/2, 400);
    Hard->SetPosition(Menu.GetWidth()/2,460);
    Custom->SetPosition(Menu.GetWidth()/2,520);

    Logo->SetPosition(Menu.GetWidth()-150,Menu.GetHeight()-91);

    Von->SetPosition(0,60);
    Voff->SetPosition(0,60);
    Don->SetPosition(0,10);
    Doff->SetPosition(0,10);
    Web->SetPosition(0,110);

    GameHelper gl(Menu);

    while (Menu.IsOpened()) {

    Menu.Draw(*Background);
    Menu.Draw(*Title);

    Menu.Draw(*Easy);
    Menu.Draw(*Med);
    Menu.Draw(*Hard);
    Menu.Draw(*Custom);
    Menu.Draw(*Web);

    if (gl.Music == true) {Menu.Draw(*Von);}
    else if (gl.Music == false) {Menu.Draw(*Voff);}

    if (gl.Debug == true) {Menu.Draw(*Don);}
    else if (gl.Debug == false) {Menu.Draw(*Doff);}

    Easy->SetColor(sf::Color::White);
    Med->SetColor(sf::Color::White);
    Hard->SetColor(sf::Color::White);
    Custom->SetColor(sf::Color::White);
    Web->SetColor(sf::Color::White);
    Von->SetColor(sf::Color::White);
    Voff->SetColor(sf::Color::White);
    Don->SetColor(sf::Color::White);
    Doff->SetColor(sf::Color::White);

    const sf::Input &Input = Menu.GetInput();

    float MouseX = Input.GetMouseX();
    float MouseY = Input.GetMouseY();

    sf::Event Event;

        while (Menu.GetEvent (Event)) {
            if (Event.Type == sf::Event::Closed) {Menu.Close(); return EXIT_SUCCESS;}
            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape)) {Menu.Close(); return EXIT_SUCCESS;}
        }

         if((MouseX > (Menu.GetWidth()/2) - 100  && MouseX < (Menu.GetWidth()/2) + 100)  && (MouseY > 315 && MouseY < 365)) {Easy->SetColor(sf::Color(160,160,160));}
    else if((MouseX > (Menu.GetWidth()/2) - 100  && MouseX < (Menu.GetWidth()/2) + 100)  && (MouseY > 375 && MouseY < 425)) {Med->SetColor(sf::Color(160,160,160));}
    else if((MouseX > (Menu.GetWidth()/2) - 100  && MouseX < (Menu.GetWidth()/2) + 100)  && (MouseY > 435 && MouseY < 485)) {Hard->SetColor(sf::Color(160,160,160));}
    else if((MouseX > (Menu.GetWidth()/2) - 100  && MouseX < (Menu.GetWidth()/2) + 100)  && (MouseY > 495 && MouseY < 545)) {Custom->SetColor(sf::Color(160,160,160));}

    else if ((MouseX > 0 && MouseX < 100) && (MouseY > 0 && MouseY < 25))   {Don->SetColor(sf::Color(160,160,160)); Doff->SetColor(sf::Color(160,160,160));}
    else if ((MouseX > 0 && MouseX < 100) && (MouseY > 50 && MouseY < 75))  {Von->SetColor(sf::Color(160,160,160)); Voff->SetColor(sf::Color(160,160,160));}
    else if ((MouseX > 0 && MouseX < 100) && (MouseY > 100 && MouseY < 125)){Web->SetColor(sf::Color(160,160,160));}

            if ((Event.Type == sf::Event::MouseButtonPressed) && (Event.Key.Code == sf::Mouse::Left)) {*MouseLeftDown = true;}
            if ((Event.Type == sf::Event::MouseButtonReleased) && (Event.Key.Code == sf::Mouse::Left)) {
                if (*MouseLeftDown == true) {

                    if((MouseX > (Menu.GetWidth()/2) - 100 && MouseX < (Menu.GetWidth()/2) + 100) && (MouseY > 315 && MouseY < 365)) {
                    //EASY
                        Menu.Close();
                        gl.RedCount = 10;
                        gl.AsteroidCount = 350;
                        gl.YellowCount = 10;
                        gl.GreenCount = 1;

                    }
                    else if ((MouseX > (Menu.GetWidth()/2) - 100 && MouseX < (Menu.GetWidth()/2) + 100) && (MouseY > 375 && MouseY < 425)) {
                    //MED
                        gl.RedCount = 20;
                        gl.AsteroidCount = 350;
                        gl.YellowCount = 25;
                        gl.GreenCount = 2;
                        Menu.Close();
                    }
                    else if ((MouseX > (Menu.GetWidth()/2) - 100 && MouseX < (Menu.GetWidth()/2) + 100) && (MouseY > 435 && MouseY < 485)) {
                    //HARD
                        gl.RedCount = 25;
                        gl.AsteroidCount = 500;
                        gl.YellowCount = 35;
                        gl.GreenCount = 3;
                        Menu.Close();
                    }

                    else if ((MouseX > 0 && MouseX < 100) && (MouseY > 0 && MouseY < 25)) {
                        if (gl.Debug == true) {gl.Debug = false;}           //Debug printout On/Off Toggle
                        else if (gl.Debug == false) {gl.Debug = true;}      //
                    }
                    else if ((MouseX > 0 && MouseX < 100) && (MouseY > 50 && MouseY < 75)) {
                        if (gl.Music == true) {gl.Music = false;}           // Music On/Off Toggle
                        else if (gl.Music == false) {gl.Music = true;}      //
                    }
                    else if ((MouseX > 0 && MouseX < 100) && (MouseY > 100 && MouseY < 125)) {system("firefox http://devgeo.wordpress.com");}
                }

                MouseLeftDown = false;
            }

        Menu.Display();

    }

//    MenuMusic->Stop();
}

//int Game(sf::Sprite* STempTop, sf::Sprite* SHealth, sf::String* CurrencyText, sf::String* FuelText, sf::String* EnergyText, sf::Music* GameMusic, sf::Sprite* moonSprite, sf::Sprite* SRTurret, sf::Sprite* exploRedSprite, sf::Sprite* exploYellowSprite, sf::Sprite* exploAsterSprite, sf::Sprite* playerSprite, sf::Sprite* starField, sf::Sprite* World1, sf::Sprite* World2, sf::Sprite* World3, sf::Sprite* World4, sf::Sprite* spacestationSprite, sf::Sprite* moonSprite, sf::Sprite* asteroidSprite, sf::Sprite* redSprite, sf::Sprite* yellowSprite) {
//    bool Firing = false;
//
//    bool MouseLeftDown = false;
//    bool MouseRightDown = false;
//
//    bool PlayerWMove = false;
//    bool PlayerAMove = false;
//    bool PlayerSMove = false;
//    bool PlayerDMove = false;
//
//    bool LControlDown = false;
//    bool LShiftDown = false;
//
//    bool ShieldPress = false;
//    bool SpaceDown = false;
//    bool ShipFiring = false;
//    bool Num9Down = false;
//    bool QDown = false;
//    bool NDown = false;
//    bool MDown = false;
//
//    bool MapMode = false;
//    bool PlayerThrustCheck = false;
//
//    int GlobalSelectBox1X, GlobalSelectBox1Y;
//    int GlobalSelectBox2X, GlobalSelectBox2Y;
//
//    int RenderSelectBox1X, RenderSelectBox1Y;
//    int RenderSelectBox2X, RenderSelectBox2Y;
//
//    srand(time(NULL));
//                sf::Clock ThrusterImgClock;
//
////--------------------------------------------------- Game Window ----------------------------------------------------------------
//    int BulletCounter;
//    BulletCounter = 1;
//
//    float TempMX[100], TempMY[100];
//
////    gl.ScreenX = 1024;
////    gl.ScreenY = 768;
//
//    sf::RenderWindow App;//(sf::VideoMode(500,500,32), "Onyx [Alpha]");
//    App.Create(sf::VideoMode::GetDesktopMode(), "Onyx [Alpha]", sf::Style::Fullscreen);
//
//    Player pl(App);
//    Star st(App);
//    Red rd(App);
//    Yellow yl(App);
//    Green gr(App);
//    Bullet bl(App);
//    Turret tr(App);
//    Asteroid as(App);
//    Planet planet(App);
//    Moon mn(App);
//    Spacestation stat(App);
//    GameHelper global(App);
//
//    as.Initialize(global.AsteroidCount);
//    rd.Initialize(global.RedCount);
//    yl.Initialize(global.YellowCount);
//
//    stat.Initialize();
//    planet.Initialize(global.PlanetCount);
//    st.Initialize(global.StarCount);
//    mn.Initialize();
//
//    rd.Spawn(global.RedCount);
//    yl.Spawn(global.YellowCount);
//
//    sf::Vector2f Center(50000, 50000);
//    sf::Vector2f HalfSize(App.GetWidth()/2, App.GetHeight()/2);
//    sf::View View(Center, HalfSize);
//
//    STempTop.SetPosition(App.GetWidth() - 275,0);
//    SHealth.SetPosition(0,App.GetHeight() - 50);
//
//    CurrencyText.SetPosition(App.GetWidth() - 99,10);
//    FuelText.SetPosition(240, App.GetHeight() - 40);
//    EnergyText.SetPosition(140, App.GetHeight() - 40);
//    HealthText.SetPosition(40, App.GetHeight() - 40);
//
//    global.ScreenX = 1024;
//    global.ScreenY = 768;
////
//    global.ViewX = 5000 - (global.ScreenX/2);
//    global.ViewY = 5000 - (global.ScreenY/2);
//
//    if (global.Music == true) {GameMusic.Play();} //Play Music
//
//    while (App.IsOpened())
//    {
//        const sf::Input &Input = App.GetInput();
//        App.SetFramerateLimit(30); // Limits  per second
//
//        App.Clear(sf::Color::Black); //Refreshes the screen
//
//        sf::Vector2f MousePos = App.ConvertCoords(App.GetInput().GetMouseX(), App.GetInput().GetMouseY());
//
//        float MouseX = MousePos.x;
//        float MouseY = MousePos.y;
//
//        sf::Event Event;
//
//        while (App.GetEvent (Event)) {
//            if (Event.Type == sf::Event::Closed) {App.Close();}
//            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape)) {App.Close();}
//
//        if (App.GetInput().IsKeyDown(sf::Key::Add))      View.Zoom(1.1f);
//        if (App.GetInput().IsKeyDown(sf::Key::Subtract)) View.Zoom(0.9f);
//
//        App.SetView(View);
//
//            if ((Event.Type == sf::Event::MouseWheelMoved) && (Event.Key.Code == sf::Mouse::Middle))
//
//            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Numpad9)) {Num9Down = true;}
//            if ((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::Numpad9)) {if (Num9Down == true) {global.ViewX = pl.GlobalPlayerX - (WindowWidth / 2); global.ViewY = pl.GlobalPlayerY - (WindowHeight / 2);}}
//
//            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Space)) {ShipFiring = true;}
//            if ((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::Space)) {ShipFiring = false; View.SetHalfSize(100,100);}
//
//    //////////////////////////////////  WASD Movement ///////////////////////////////////////////////////////////////////////
//
//            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::W)) {PlayerWMove = true;}
//            if ((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::W)) {PlayerWMove = false;}
//
//            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::A)) {PlayerAMove = true;}
//            if ((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::A)) {PlayerAMove = false;}
//
//            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::S)) {PlayerSMove = true;}
//            if ((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::S)) {PlayerSMove = false;}
//
//            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::D)) {PlayerDMove = true;}
//            if ((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::D)) {PlayerDMove = false;}
//
//    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//            if ((Event.Type == sf::Event::MouseButtonPressed) && (Event.Key.Code == sf::Mouse::Left)) {
//                for (int c = 0; c < global.YellowCount; c++) {yl.IsSelect[c] = false;}
//                for (int c = 0; c < global.RedCount; c++) {rd.IsSelect[c] = false;}
//                for (int c = 0; c < global.AsteroidCount; c++) {as.IsSelect[c] = false;}
//
//                MouseLeftDown = true;
//                GlobalSelectBox1X = MouseX + global.ViewX;
//                GlobalSelectBox1Y = MouseY + global.ViewY;
//            }
//            if ((Event.Type == sf::Event::MouseButtonReleased) && (Event.Key.Code == sf::Mouse::Left)) {
//                if (MouseLeftDown == true) {MouseLeftDown = false;}
//
//                GlobalSelectBox2X = MouseX + global.ViewX;
//                GlobalSelectBox2Y = MouseY + global.ViewY;
//            }
//
//            if (LShiftDown == true && MouseLeftDown == true) {
//                for (int c = 0; c < YellowCount; c++) {
//                    if ((yl.GlobalYellowY[c] - MouseY >= 25 * -1 && yl.GlobalYellowY[c] <= MouseY) || (yl.GlobalYellowY[c] - MouseY <= 25 && yl.GlobalYellowY[c] >= MouseY)) {
//                        if ((yl.GlobalYellowX[c] - MouseX >= 25 * -1 && yl.GlobalYellowX[c] <= MouseX) || (yl.GlobalYellowX[c] - MouseX <= 25 && yl.GlobalYellowX[c] >= MouseX)) {
//                            if (yl.IsSelect[c] == true) {yl.IsDead[c] = true;}
//                        }
//                    }
//                }
//            }
//
//            if ((Event.Type == sf::Event::MouseButtonPressed) && (Event.Key.Code == sf::Mouse::Right)) {MouseRightDown = true;}
//            if ((Event.Type == sf::Event::MouseButtonReleased) && (Event.Key.Code == sf::Mouse::Right)) {
//                if (LShiftDown == true) {pl.GlobalWayPoint2X = MousePos.x; pl.GlobalWayPoint2Y = MousePos.y;}
//                else if (LControlDown == true) {pl.GlobalWayPoint3X = MousePos.x; pl.GlobalWayPoint3Y = MousePos.y;}
//                else {pl.GlobalWayPoint1X = MousePos.x; pl.GlobalWayPoint1Y = MousePos.y;}
//            }
//
//            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::LControl)) {LControlDown = true;}
//            if ((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::LControl)) {LControlDown = false;}
//
//            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::LShift)) {LShiftDown = true;}
//            if ((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::LShift)) {LShiftDown = false;}
//
//            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Q)) {QDown = true;}
//            if ((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::Q)) {if (QDown == true) {pl.Thrust();}}
//
//            //if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::N)) {NDown = true;}
//            if (Input.IsKeyDown(sf::Key::N)) //&& (Event.Key.Code == sf::Key::N)) {if (NDown == true)
//            {
//                global.ScreenX += 50; global.ScreenY += 50;}
//
//            //if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::M)) {MDown = true;}
//            if (Input.IsKeyDown(sf::Key::M)) //&& (Event.Key.Code == sf::Key::M))
//            {//if (MDown == true) {
//                global.ScreenX -= 50; global.ScreenY -= 50;}
//        }
//
//            float Offset = 200.f * App.GetFrameTime();
//
////        if (MouseX >= WindowWidth - 75) {View.Move( Offset,  0);}
////        else if (MouseX <= 75) {View.Move(-Offset,  0);}
////
////        if (MouseY >= WindowHeight - 75) {View.Move( 0,       Offset);}
////        else if (MouseY <= 75) {View.Move( 0,       -Offset);}
//
//        pl.WayPointCalc(global.ViewX, global.ViewY);
////        pl.Move();
//
//        if (PlayerThrustCheck == true) {pl.Thrust();}
//
//    View.SetCenter(pl.RenderPlayerX, pl.RenderPlayerY);
//
//        RenderSelectBox1X = GlobalSelectBox1X - global.ViewX;
//        RenderSelectBox1Y = GlobalSelectBox1Y - global.ViewY;
//
//        pl.GlobalPlayerX += pl.VPlayerX;
//        pl.GlobalPlayerY += pl.VPlayerY;
//
//        if (PlayerWMove == true) {pl.WMove();}
//        else {
//            pl.VPlayerX *= .999;
//            pl.VPlayerY *= .999;}
//        if (PlayerAMove == true) {pl.AMove();}
//        if (PlayerSMove == true) {pl.SMove();}
//        if (PlayerDMove == true) {pl.DMove();}
//
//    //------------------------------------------------------------------------
//
//        global.RenderView();
//
//        yl.RenderCalc(global.YellowCount, global.ViewX, global.ViewY);  ////
//        rd.RenderCalc(global.RedCount, global.ViewX, global.ViewY);     //// Calculates Render Coordinates
//        as.RenderCalc(global.AsteroidCount, global.ViewX, global.ViewY);////
//
//        pl.ScreenWrap(global.ViewX, global.ViewY);  //Screen Wrapping
//
//        as.Drift(global.AsteroidCount);             //Asteroid Drift
//
//        planet.CheckDraw(global.PlanetCount, global.ViewX, global.ViewY);
//
//        for(int c = 0; c < 8; c++) {
//            stat.CheckDraw(c, global.ViewX, global.ViewY);
//            stat.Move(c, mn.GlobalMoonX, mn.GlobalMoonY);
//        }
//
//        for(int c = 0; c < 8; c++) {
//            mn.CheckDraw(c, global.ViewX, global.ViewY);
//            mn.Move(c, planet.PlanetSize, planet.GlobalPlanetX, planet.GlobalPlanetY, moonSprite);
//        }
//
//        pl.Regulations(global.ViewX, global.ViewY); //Player/Enemy Regulations
//
//        string HealthString;
//        stringstream HealthStream;
//        HealthStream << pl.PlayerCurrentHealth;
//        HealthString = HealthStream.str();
//        HealthText.SetText(HealthString + "%");
//
//        string EnergyString;
//        stringstream EnergyStream;
//        EnergyStream << pl.PlayerCurrentEnergy;
//        EnergyString = EnergyStream.str();
//        EnergyText.SetText(EnergyString + "%");
//
//        string FuelString;
//        stringstream FuelStream;
//        FuelStream << setprecision(3) << pl.PlayerCurrentFuel / pl.PlayerMaxFuel * 100;
//        FuelString = FuelStream.str();
//        FuelText.SetText(FuelString + "%");
//
//        string CurrencyString;
//        stringstream CurrencyStream;
//        CurrencyStream << pl.PlayerCurrency;
//        CurrencyString = CurrencyStream.str();
//        CurrencyText.SetText(CurrencyString + "c");
//
//    // ------------------------ Turret Code -----------------------------
//
//    tr.OnTarget(pl.RenderPlayerX,pl.RenderPlayerY,pl.PlayerHeading, SRTurret); //Calc Turret Pos and Point Towards Mouse
//
//    // ------------------------------- Red Code ---------------------------------
//
//    for (int c = 0; c < global.RedCount; c++) {
//        rd.CheckSelect(c, GlobalSelectBox1X, GlobalSelectBox1Y, GlobalSelectBox2X, GlobalSelectBox2Y);
//        rd.CheckDraw(pl.GlobalPlayerX, pl.GlobalPlayerY, c);
//
//        rd.InRange(c, pl.GlobalPlayerX, pl.GlobalPlayerY, pl.RenderPlayerX, pl.RenderPlayerY, pl.PlayerArmor, pl.PlayerCurrentHealth, global.RedCount);
//
//        rd.CheckDead(c);
//        rd.Dead(c, global.Debug, pl.PlayerCurrency, exploRedSprite);
//    }
//
//    // ------------------------------- Yellow Code ---------------------------------
//
//    for (int c = 0; c < global.YellowCount; c++) {
//        yl.CheckSelect(c, GlobalSelectBox1X, GlobalSelectBox1Y, GlobalSelectBox2X, GlobalSelectBox2Y);
//        yl.CheckDraw(global.YellowCount, pl.GlobalPlayerX, pl.GlobalPlayerY, c);
//
//        yl.InRange(c, pl.GlobalPlayerX, pl.GlobalPlayerY, pl.RenderPlayerX, pl.RenderPlayerY, pl.PlayerArmor, pl.PlayerCurrentHealth, global.YellowCount);
//
//        yl.CheckDead(c);
//        yl.Dead(c, global.Debug, pl.PlayerCurrency, exploYellowSprite);
//    }
//
//    // -------------------------------- Asteroid Code ----------------------------------
//
//    for (int c = 0; c < global.AsteroidCount; c++) {
//        as.CheckSelect(c, GlobalSelectBox1X, GlobalSelectBox1Y, GlobalSelectBox2X, GlobalSelectBox2Y);
//        as.CheckDraw(c, global.ViewX, global.ViewY);
//
//        as.InRange(c, pl.GlobalPlayerX, pl.GlobalPlayerY, pl.PlayerArmor, pl.PlayerCurrentHealth, global.AsteroidCount, global.Debug);
//
//        as.CheckDead(c);
//        as.Dead(c, exploAsterSprite, global.Debug, pl.PlayerCurrency);
//    }
//
//    //---------------------------------------------------------------------------------------
//
//
////
////    if (pl.ShieldsOn == true && pl.PlayerCurrentEnergy > 1) {
////        SShield.SetRotation(pl.PlayerHeading * -1);
////        SShield.SetPosition(pl.RenderPlayerX, pl.RenderPlayerY);
////
////        App.Draw(SShield);
////    }
//
//            float ftimer = ThrusterImgClock.GetElapsedTime() * 4;
//
//            if(ftimer <= .3){playerSprite.SetSubRect(sf::IntRect(120,0,220,44));}
//            else if(ftimer >= .4 && ftimer <= .7) {playerSprite.SetSubRect(sf::IntRect(0,0,110,44));}
//            else if(ftimer >= .9) {ThrusterImgClock.Reset();}
//
////        App.Draw(starField);
////
////starImage = App.Capture();
//
////App.Draw(starImage);
//    for (int x = 0; x < StarCount; x++) {
//        st.RenderStarX[x] = st.GlobalStarX[x] - global.ViewX;//(ScreenX/2);
//        st.RenderStarY[x] = st.GlobalStarY[x] - global.ViewY;
//        starField[x].SetPosition(st.RenderStarX[x], st.RenderStarY[x]);
//        App.Draw(starField[x]);
//    }
//
//        pl.RenderCalc(global.ViewX, global.ViewY);
//
//        playerSprite.SetRotation(pl.PlayerHeading * -1);
//        playerSprite.SetPosition(pl.RenderPlayerX, pl.RenderPlayerY);
//
//        App.Draw(playerSprite);
//
//    for(int x = 0; x < TurretCount; x++) {App.Draw(SRTurret[x]);}
//
//    if (MouseLeftDown == true) {App.Draw(sf::Shape::Rectangle(RenderSelectBox1X, RenderSelectBox1Y, MouseX, MouseY, sf::Color(125,255,0,100), 1.f, sf::Color::Green));}
//
//    if (MapMode == true) {pl.WayPointDraw();}
//
//
//    planet.Draw(global.PlanetCount, World1, World2, World3, World4);                        // Draws Planets
//
//    for(int c = 0; c < 8; c++) {stat.Draw(c, global.ViewX, global.ViewY, spacestationSprite);}
//    for(int c = 0; c < 8; c++) {mn.Draw(c, global.ViewX, global.ViewY, moonSprite);}
//
//    for (int c = 0; c < global.AsteroidCount; c++) {as.Draw(c, global.AsteroidCount, asteroidSprite);}
//    for (int c = 0; c < global.RedCount; c++) {rd.Draw(global.RedCount, c, redSprite);}
//    for (int c = 0; c < global.YellowCount; c++) {yl.Draw(global.YellowCount, c, yellowSprite);}
//
////    ShipFiring = false;
//    SpaceDown = false;
//    Num9Down = false;
//    PlayerThrustCheck = false;
//    QDown = false;
//    NDown = false;
//    MDown = false;
//
//    for (int c = 0; c < global.YellowCount; c++) {yl.IsDrawable[c] = false;} //yl.YellowMove[c] = false;
//    for (int c = 0; c < global.AsteroidCount; c++) {as.IsDrawable[c] = false;}
//    for (int c = 0; c < global.RedCount; c++) {rd.IsDrawable[c] = false;}
//    for (int c = 0; c < global.StarCount; c++) {st.IsDrawable[c] = false;}
//    for (int c = 0; c < global.PlanetCount; c++) {planet.IsDrawable[c] = false;}
//    for (int c = 0; c < 3; c++) {stat.IsDrawable[c] = false;}
//
//    App.SetView(App.GetDefaultView()); //Set View to correct ratio for GUI
//    App.Draw(SHealth);      //
//    App.Draw(STempTop);     //
//    App.Draw(HealthText);   //  GUI Draw Sequence
//    App.Draw(EnergyText);   //
//    App.Draw(FuelText);     //
//    App.Draw(CurrencyText); //
//
//    App.SetView(View);
//    App.Display();
//    }
//
//return EXIT_SUCCESS;
//}


int main() {

LoadMedia();
Menu();//Title, Easy, Med, Hard, Custom, Von, Voff, Don, Doff, Web, Background, Logo, MouseLeftDown, MenuMusic);
//Game(STempTop, SHealth, CurrencyText, FuelText, EnergyText, GameMusic, moonSprite, SRTurret, exploRedSprite, exploYellowSprite, exploAsterSprite, playerSprite, starField, World1, World2, World3, World4, spacestationSprite, moonSprite, asteroidSprite, redSprite, yellowSprite);


return EXIT_SUCCESS;
}

