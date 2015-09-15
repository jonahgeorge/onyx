#ifndef GREEN_H_INCLUDED
#define GREEN_H_INCLUDED


class Green
{
public:
    Green (sf::RenderWindow &window, float GS = 0.2f, int GR = 120, int GA = 1, int GMH = 1000);
    void InRange(float, float, float, int&, int);
//    int Attack(float, float, int);
    void IsAlive(int);
    void Rand(int);
//    void BulletHit(float,float, float, float, int, int, bool);

    float GreenSpeed;
    int GreenRange;
    int GreenAttack;
    int GreenCurrentHealth[GreenCount], GreenMaxHealth;
    float GreenX[GreenCount], GreenY[GreenCount];
    int GreenHeading[GreenCount];

private:
    sf::RenderWindow &Window;
};

Green::Green(sf::RenderWindow &window, float GS, int GR, int GA, int GMH):

           GreenSpeed(GS),
           GreenRange(GR),
           GreenAttack(GA),
           GreenMaxHealth(GMH),
           Window (window)

{}

void Green::Rand(int GreenCount)
{
    for (int c = 0; c < GreenCount; c++)
    {
        GreenX[c] = rand()%GameWidth+1;
        GreenY[c] = rand()%GameHeight+1;

        GreenCurrentHealth[c] = 500;
    }
}

void Green::InRange(float PlayerX, float PlayerY, float PlayerArmor, int &PlayerCurrentHealth, int GreenCount)
{
        for (int c = 0; c < GreenCount; c++)
        {
            GreenHeading[c] = atan2(PlayerY - GreenY[c], PlayerX - GreenX[c]) * 180 / pi;


        if ((GreenY[c] - PlayerY >= GreenRange * -1 && GreenY[c] <= PlayerY)
            || (GreenY[c] - PlayerY <= GreenRange && GreenY[c] >= PlayerY))
        {
            if ((GreenX[c] - PlayerX >= GreenRange * -1 && GreenX[c] <= PlayerX)
                || (GreenX[c] - PlayerX <= GreenRange && GreenX[c] >= PlayerX))
            {
                PlayerCurrentHealth -= GreenAttack / PlayerArmor;
                Window.Draw(sf::Shape::Line(GreenX[c], GreenY[c], PlayerX, PlayerY, 2.f, sf::Color::Yellow));
            }

            else
            {
                GreenX[c] += cos(GreenHeading[c] * pi / 180) * GreenSpeed;
                GreenY[c] += sin(GreenHeading[c] * pi / 180) * GreenSpeed;
            }
        }
        else
        {
            GreenX[c] += cos(GreenHeading[c] * pi / 180) * GreenSpeed;
            GreenY[c] += sin(GreenHeading[c] * pi / 180) * GreenSpeed;
        }
}
}

void Green::IsAlive(int GreenCount)
{
//    for (int c = 0; c < GreenCount; c++)
//    {
//        if (GreenCurrentHealth[c] <= 0)
//        {
//                GreenCurrentHealth[c] = GreenMaxHealth;
//                cout << "Green terminated\n";
//                GreenX[c] = rand()%(width+100) + width;
//                GreenY[c] = rand()%(height+100) + height;
//        }
//    }
}




#endif // GREEN_H_INCLUDED
