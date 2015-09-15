#ifndef RED_H_INCLUDED
#define RED_H_INCLUDED


class Red
{
public:
    Red (sf::RenderWindow &window, float RS = 5.0f, int RR = 120, int RA = 1, int RMH = 500);

    void InRange(int, float, float, float, float, float, int&, int);
    void IsAlive(int);
    void Spawn(int);
    void RandPos(int);
    void GetHit(int, int);
    void RenderCalc(int,int,int);

    void Initialize(int);

    void CheckDraw(float,float, int);
    void Draw(int, int, sf::Sprite*);

    void CheckSelect(int,int,int,int,int);

    void CheckDead(int);
    void Dead(int, bool, int&, sf::Sprite*);

    float RedSpeed;
    int RedRange;
    int RedAttack;
    int RedMaxHealth;

    vector <int> RedCurrentHealth;

    vector <float> GlobalRedX;
    vector <float> GlobalRedY;

    vector <float> RenderRedX;
    vector <float> RenderRedY;

    vector <int> RedHeading;

    vector <bool> IsDrawable;
    vector <bool> IsSelect;
    vector <bool> IsDead;

private:
    sf::RenderWindow &Window;
};

Red::Red(sf::RenderWindow &window, float RS, int RR, int RA, int RMH):

           RedSpeed(RS),
           RedRange(RR),
           RedAttack(RA),
           RedMaxHealth(RMH),
           Window (window)

{}

void Red::Initialize(int RedCount)
{
    for (unsigned int cycle = 0; cycle < RedCount; ++cycle)
    {
        GlobalRedX.push_back(NULL);
        GlobalRedY.push_back(NULL);

        RenderRedX.push_back(NULL);
        RenderRedY.push_back(NULL);

        IsDrawable.push_back(false);
        IsSelect.push_back(false);
        IsDead.push_back(false);
        RedHeading.push_back(NULL);

        RedCurrentHealth.push_back(500);
    }
}

void Red::GetHit(int BulletDamage, int c)
{
    RedCurrentHealth[c] -= BulletDamage;
}

void Red::CheckDead(int c)
{
    if (RedCurrentHealth[c] <= 0)
    {
        IsDead[c] = true;
    }
}

void Red::CheckSelect(int c, int GlobalSelectBox1X, int GlobalSelectBox1Y, int GlobalSelectBox2X, int GlobalSelectBox2Y)
{
    if ((GlobalRedY[c] >= GlobalSelectBox1Y && GlobalRedY[c] <= GlobalSelectBox2Y) || (GlobalRedY[c] >= GlobalSelectBox2Y && GlobalRedY[c] <= GlobalSelectBox1Y))
    {
        if ((GlobalRedX[c] >= GlobalSelectBox1X && GlobalRedX[c] <= GlobalSelectBox2X) || (GlobalRedX[c] >= GlobalSelectBox2X && GlobalRedX[c] <= GlobalSelectBox1X))
        {
            IsSelect[c] = true;
        }
    }
}

void Red::Dead(int c, bool Debug, int &PlayerCurrency, sf::Sprite* exploRedSprite)
{
    if (IsDead[c] == true)
    {

    exploRedSprite[c].SetPosition(RenderRedX[c], RenderRedY[c]);
    Window.Draw(exploRedSprite[c]);

    RedCurrentHealth[c] = RedMaxHealth;
    RandPos(c);
    IsDead[c]= false;

    if (Debug == true) {   cout << "Yellow # " << c << "terminated\n";  }


    PlayerCurrency += 5;
    }
}

void Red::CheckDraw(float GlobalPlayerX, float GlobalPlayerY, int c)
{
    if ((GlobalRedY[c] - GlobalPlayerY >= -500 && GlobalRedY[c] <= GlobalPlayerY) || (GlobalRedY[c] - GlobalPlayerY <= 500 && GlobalRedY[c] >= GlobalPlayerY))
    {
        if ((GlobalRedX[c] - GlobalPlayerX >= -500 && GlobalRedX[c] <= GlobalPlayerX) || (GlobalRedX[c] - GlobalPlayerX <= 500 && GlobalRedX[c] >= GlobalPlayerX))
        {
            IsDrawable[c] = true;
        }
    }
}

void Red::Draw(int RedCount, int c, sf::Sprite* redSprite)
{
    if(IsDrawable[c] == true)
    {
        if (IsSelect[c] == true)
            {
                Window.Draw(sf::Shape::Circle(RenderRedX[c], RenderRedY[c], 25.f, sf::Color(125,255,0,100), 1.f, sf::Color::Green));
            }

        redSprite[c].SetPosition(RenderRedX[c],RenderRedY[c]);
        redSprite[c].SetRotation(RedHeading[c] * -1);
        Window.Draw(redSprite[c]);
    }
}

void Red::RenderCalc(int RedCount, int ViewX, int ViewY)
{
    for (int c = 0; c < RedCount; c++)
    {
        RenderRedX[c] = GlobalRedX[c] - ViewX;
        RenderRedY[c] = GlobalRedY[c] - ViewY;
    }
}

void Red::RandPos(int c)
{
    GlobalRedX[c] = rand()%GameWidth + 1;
    GlobalRedY[c] = rand()%GameHeight + 1;
}

void Red::Spawn(int RedCount)
{
    for (int c = 0; c < RedCount; c++)
    {
        RandPos(c);
        //GlobalRedX[c] = rand()%GameWidth + 1;
        //GlobalRedY[c] = rand()%GameHeight + 1;
        RedCurrentHealth[c] = 500;
    }
}

void Red::InRange(int c, float GlobalPlayerX, float GlobalPlayerY, float RenderPlayerX, float RenderPlayerY, float PlayerArmor, int &PlayerCurrentHealth, int RedCount)
{
            RedHeading[c] = atan2(GlobalPlayerY - GlobalRedY[c], GlobalPlayerX - GlobalRedX[c]) * 180 / pi;


        if ((GlobalRedY[c] - GlobalPlayerY >= RedRange * -1 && GlobalRedY[c] <= GlobalPlayerY)
            || (GlobalRedY[c] - GlobalPlayerY <= RedRange && GlobalRedY[c] >= GlobalPlayerY))
        {
            if ((GlobalRedX[c] - GlobalPlayerX >= RedRange * -1 && GlobalRedX[c] <= GlobalPlayerX)
                || (GlobalRedX[c] - GlobalPlayerX <= RedRange && GlobalRedX[c] >= GlobalPlayerX))
            {
                PlayerCurrentHealth -= RedAttack / PlayerArmor;
                Window.Draw(sf::Shape::Line(RenderRedX[c], RenderRedY[c], RenderPlayerX, RenderPlayerY, 1.f, sf::Color::Yellow, 1.f, sf::Color(255,255,0,100)));
            }

            else
            {
                GlobalRedX[c] += cos(RedHeading[c] * pi / 180) * RedSpeed;
                GlobalRedY[c] += sin(RedHeading[c] * pi / 180) * RedSpeed;
            }
        }
        else
        {
            GlobalRedX[c] += cos(RedHeading[c] * pi / 180) * RedSpeed;
            GlobalRedY[c] += sin(RedHeading[c] * pi / 180) * RedSpeed;
        }
}

//void Red::BulletHit(float BulletX, float BulletY, float BulletX2, float BulletY2, int BulletDamage, int RedCount, bool Debug) //Checks if bullet collides with Asteroid
//{
//        for (int c = 0; c < RedCount; c++)
//        {
//            if ((BulletY - RedY[c] >= 25 * -1 && BulletY <= RedY[c]) || (BulletY - RedY[c] <= 25 && BulletY >= RedY[c]))
//            {
//            if ((BulletX - RedX[c] >= 25 * -1 && BulletX <= RedX[c]) || (BulletX - RedX[c] <= 25 && BulletX >= RedX[c]))
//                {
//                    RedCurrentHealth[c] -= BulletDamage;
//                    BulletX = 2000;
//                    BulletY = 2000;
//
//                    if(Debug == true)
//                    {
//                    cout << "Red # " << c << "hit!";
//                    }
//                }
//            }
//            if ((BulletY2 - RedY[c] >= 25 * -1 && BulletY2 <= RedY[c]) || (BulletY2 - RedY[c] <= 25 && BulletY2 >= RedY[c]))
//            {
//            if ((BulletX2 - RedX[c] >= 25 * -1 && BulletX2 <= RedX[c]) || (BulletX2 - RedX[c] <= 25 && BulletX2 >= RedX[c]))
//                {
//                    RedCurrentHealth[c] -= BulletDamage;
//                    BulletX2 = 2000;
//                    BulletY2 = 2000;
//
//                    if(Debug == true)
//                    {
//                    cout << "Red # " << c << "hit!";
//                    }
//                }
//            }
//        }
//}

void Red::IsAlive(int RedCount)
{
//    for (int c = 0; c < RedCount; c++)
//    {
//        if (RedCurrentHealth[c] <= 0)
//        {
//                RedCurrentHealth[c] = RedMaxHealth;
//                cout << "Red terminated\n";
//                RedX[c] = rand()%(width+100) + width;
//                RedY[c] = rand()%(height+100) + height;
//        }
//    }
}

//int Red::Attack(float PlayerX, float PlayerY, int PlayerCurrentHealth)
//{
//            if (InRange(PlayerX, PlayerY) == true)
//            {
//            PlayerCurrentHealth -= RedAttack;
//            std::cout << "Red (Hit)\n";
//            std::cout << PlayerCurrentHealth;
//            }
//
//            return PlayerCurrentHealth;
//}


#endif // RED_H_INCLUDED
