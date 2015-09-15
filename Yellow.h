#ifndef YELLOW_H_INCLUDED
#define YELLOW_H_INCLUDED

class Yellow
{
public:
    Yellow (sf::RenderWindow &window, float YS = 9.f, int YR = 70, int YA = 1, int YMH = 100);
    void InRange(int, float, float, float, float, float, int&, int);
//    void Chase(float, float, int);

    void RenderCalc(int,int,int);

    void Spawn(int);

    void Initialize(int);
    void RandPos(int);

    void CheckSelect(int,int,int,int,int);

    void CheckDraw(int,float,float, int);
    void Draw(int, int, sf::Sprite*);

    void CheckDead(int);
    void Dead(int, bool, int&, sf::Sprite*);

    float YellowSpeed;
    int YellowRange;
    int YellowAttack;
    int YellowMaxHealth;

    //vector <bool> YellowMove;

    vector <int> YellowCurrentHealth;

    vector <float> GlobalYellowX;
    vector <float> GlobalYellowY;

    vector <float> RenderYellowX;
    vector <float> RenderYellowY;

    vector <int> YellowHeading;

    vector <bool> IsDrawable;
    vector <bool> IsSelect;
    vector <bool> IsDead;

private:
    sf::RenderWindow &Window;
};

Yellow::Yellow(sf::RenderWindow &window, float YS, int YR, int YA, int YMH):

           YellowSpeed(YS),
           YellowRange(YR),
           YellowAttack(YA),
           YellowMaxHealth(YMH),
           Window (window)

{}

void Yellow::Initialize(int YellowCount)
{
    for (unsigned int cycle = 0; cycle < RedCount; ++cycle)
    {
        GlobalYellowX.push_back(NULL);
        GlobalYellowY.push_back(NULL);

        RenderYellowX.push_back(NULL);
        RenderYellowY.push_back(NULL);

        IsDrawable.push_back(false);
        IsSelect.push_back(false);
        IsDead.push_back(false);

        YellowHeading.push_back(NULL);
        YellowCurrentHealth.push_back(NULL);
    }
}

void Yellow::Spawn(int YellowCount)
{
    for (int c = 0; c < YellowCount; c++)
    {
        RandPos(c);
        //GlobalRedX[c] = rand()%GameWidth + 1;
        //GlobalRedY[c] = rand()%GameHeight + 1;
        YellowCurrentHealth[c] = 100;
    }
}

void Yellow::CheckDead(int c)
{
    if (YellowCurrentHealth[c] <= 0)
    {
        IsDead[c] = true;
    }
}

void Yellow::RandPos(int c)
{
    GlobalYellowX[c] = rand()%GameWidth + 1;
    GlobalYellowY[c] = rand()%GameHeight + 1;
}

void Yellow::Dead(int c, bool Debug, int &PlayerCurrency, sf::Sprite* exploYellowSprite)
{
    if (IsDead[c] == true)
    {
    exploYellowSprite[c].SetPosition(RenderYellowX[c], RenderYellowY[c]);
    Window.Draw(exploYellowSprite[c]);

    YellowCurrentHealth[c] = YellowMaxHealth;
    RandPos(c);
    IsDead[c]= false;

    if (Debug == true) {   cout << "Yellow # " << c << "terminated\n";  }


    PlayerCurrency += 5;
    }
}

void Yellow::CheckSelect(int c, int GlobalSelectBox1X, int GlobalSelectBox1Y, int GlobalSelectBox2X, int GlobalSelectBox2Y)
{
    if ((GlobalYellowY[c] >= GlobalSelectBox1Y && GlobalYellowY[c] <= GlobalSelectBox2Y) || (GlobalYellowY[c] >= GlobalSelectBox2Y && GlobalYellowY[c] <= GlobalSelectBox1Y))
    {
        if ((GlobalYellowX[c] >= GlobalSelectBox1X && GlobalYellowX[c] <= GlobalSelectBox2X) || (GlobalYellowX[c] >= GlobalSelectBox2X && GlobalYellowX[c] <= GlobalSelectBox1X))
        {
            IsSelect[c] = true;
        }
    }
}

void Yellow::CheckDraw(int YellowCount, float GlobalPlayerX, float GlobalPlayerY, int c)
{
    if ((GlobalYellowY[c] - GlobalPlayerY >= -500 && GlobalYellowY[c] <= GlobalPlayerY) || (GlobalYellowY[c] - GlobalPlayerY <= 500 && GlobalYellowY[c] >= GlobalPlayerY))
    {
        if ((GlobalYellowX[c] - GlobalPlayerX >= -500 && GlobalYellowX[c] <= GlobalPlayerX) || (GlobalYellowX[c] - GlobalPlayerX <= 500 && GlobalYellowX[c] >= GlobalPlayerX))
        {
            IsDrawable[c] = true;
        }
    }
}

void Yellow::Draw(int YellowCount, int c, sf::Sprite* yellowSprite)
{
    if(IsDrawable[c] == true)
    {
        if (IsSelect[c] == true)
            {
                Window.Draw(sf::Shape::Circle(RenderYellowX[c], RenderYellowY[c], 25.f, sf::Color(125,255,0,100), 1.f, sf::Color::Green));
            }

        yellowSprite[c].SetPosition(RenderYellowX[c],RenderYellowY[c]);
        yellowSprite[c].SetRotation(YellowHeading[c] * -1);
        Window.Draw(yellowSprite[c]);
}
}

void Yellow::RenderCalc(int YellowCount, int ViewX, int ViewY)
{
    for (int c = 0; c < YellowCount; c++)
{
        RenderYellowX[c] = GlobalYellowX[c] - ViewX;
        RenderYellowY[c] = GlobalYellowY[c] - ViewY;
}
}


//
//void Yellow::Chase(float PlayerX, float PlayerY, int YellowCount, int c)
//{
//    YellowHeading[c] = atan2(PlayerY - YellowY[c], PlayerX - YellowX[c]) * 180 / pi;
//
//    YellowX[c] += cos(YellowHeading[c] * pi / 180) * YellowSpeed;
//    YellowY[c] += sin(YellowHeading[c] * pi / 180) * YellowSpeed;
//
//    YellowMove[c] = true;
//}

void Yellow::InRange(int c, float GlobalPlayerX, float GlobalPlayerY, float RenderPlayerX, float RenderPlayerY, float PlayerArmor, int &PlayerCurrentHealth, int YellowCount)
{
        YellowHeading[c] = atan2(GlobalPlayerY - GlobalYellowY[c], GlobalPlayerX - GlobalYellowX[c]) * 180 / pi;

        if ((GlobalYellowY[c] - GlobalPlayerY >= YellowRange * -1 && GlobalYellowY[c] <= GlobalPlayerY)
            || (GlobalYellowY[c] - GlobalPlayerY <= YellowRange && GlobalYellowY[c] >= GlobalPlayerY))
        {
            if ((GlobalYellowX[c] - GlobalPlayerX >= YellowRange * -1 && GlobalYellowX[c] <= GlobalPlayerX)
                || (GlobalYellowX[c] - GlobalPlayerX <= YellowRange && GlobalYellowX[c] >= GlobalPlayerX))
            {

                PlayerCurrentHealth -= YellowAttack / PlayerArmor;

                Window.Draw(sf::Shape::Line(RenderYellowX[c], RenderYellowY[c], RenderPlayerX, RenderPlayerY, 1.f, sf::Color::Yellow));
            }
            else
            {
                GlobalYellowX[c] += cos(YellowHeading[c] * pi / 180) * YellowSpeed;
                GlobalYellowY[c] += sin(YellowHeading[c] * pi / 180) * YellowSpeed;

//                YellowMove[c] = true;
            }
        }
        else
        {
            GlobalYellowX[c] += cos(YellowHeading[c] * pi / 180) * YellowSpeed;
            GlobalYellowY[c] += sin(YellowHeading[c] * pi / 180) * YellowSpeed;

  //          YellowMove[c] = true;
        }
}

//void Yellow::BulletHit(float BulletX, float BulletY, float BulletX2, float BulletY2, int BulletDamage, int YellowCount, bool Debug) //Checks if bullet collides with Asteroid
//{
//        for (int c = 0; c < YellowCount; c++)
//        {
//            if ((BulletY - YellowY[c] >= 25 * -1 && BulletY <= YellowY[c]) || (BulletY - YellowY[c] <= 25 && BulletY >= YellowY[c]))
//            {
//            if ((BulletX - YellowX[c] >= 25 * -1 && BulletX <= YellowX[c]) || (BulletX - YellowX[c] <= 25 && BulletX >= YellowX[c]))
//                {
//                    YellowCurrentHealth[c] -= BulletDamage;
//                    BulletX = 2000;
//                    BulletY = 2000;
//
//                    if(Debug == true)
//                    {
//                    cout << "Yellow # " << c << "hit!";
//                    }
//                }
//            }
//            if ((BulletY2 - YellowY[c] >= 25 * -1 && BulletY2 <= YellowY[c]) || (BulletY2 - YellowY[c] <= 25 && BulletY2 >= YellowY[c]))
//            {
//            if ((BulletX2 - YellowX[c] >= 25 * -1 && BulletX2 <= YellowX[c]) || (BulletX2 - YellowX[c] <= 25 && BulletX2 >= YellowX[c]))
//                {
//                    YellowCurrentHealth[c] -= BulletDamage;
//                    BulletX2 = 2000;
//                    BulletY2 = 2000;
//
//                    if(Debug == true)
//                    {
//                    cout << "Yellow # " << c << "hit!";
//                    }
//                }
//            }
//        }
//}

//void Yellow::IsAlive(int YellowCount)
//{
////    for (int c = 0; c < YellowCount; c++)
////    {
////        if (YellowCurrentHealth[c] <= 0)
////        {
////                YellowCurrentHealth[c] = YellowMaxHealth;
////                cout << "Yellow terminated\n";
////                YellowX[c] = rand()%(width+100) + width;
////                YellowY[c] = rand()%(height+100) + height;
////        }
////    }
//}

#endif // YELLOW_H_INCLUDED
