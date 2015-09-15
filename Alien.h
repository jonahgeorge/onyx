#ifndef ALIEN_H_INCLUDED
#define ALIEN_H_INCLUDED


class Alien
{
public:
    Alien (sf::RenderWindow &window, float AS = 1.5f, int AR = 120, int AA = 1, int AMH = 500);
    void InRange(float, float, float, int&, int);
//    int Attack(float, float, int);
    void IsAlive(int);
    void Rand(int);
//    void BulletHit(float,float, float, float, int, int, bool);

    float AlienSpeed;
    int AlienRange;
    int AlienAttack;
    int AlienCurrentHealth[AlienCount], AlienMaxHealth;
    float AlienX[AlienCount], AlienY[AlienCount];
    int AlienHeading[AlienCount];

private:
    sf::RenderWindow &Window;
};

Alien::Alien(sf::RenderWindow &window, float AS, int AR, int AA, int AMH):

           AlienSpeed(AS),
           AlienRange(AR),
           AlienAttack(AA),
           AlienMaxHealth(AMH),
           Window (window)

{}

void Alien::Rand(int AlienCount)
{
    for (int c = 0; c < AlienCount; c++)
    {
        AlienX[c] = rand()%width+1;
        AlienY[c] = rand()%height+1;

        AlienCurrentHealth[c] = 500;
    }
}

void Alien::InRange(float PlayerX, float PlayerY, float PlayerArmor, int &PlayerCurrentHealth, int AlienCount)
{
        for (int c = 0; c < AlienCount; c++)
        {
            AlienHeading[c] = atan2(PlayerY - AlienY[c], PlayerX - AlienX[c]) * 180 / pi;


        if ((AlienY[c] - PlayerY >= AlienRange * -1 && AlienY[c] <= PlayerY)
            || (AlienY[c] - PlayerY <= AlienRange && AlienY[c] >= PlayerY))
        {
            if ((AlienX[c] - PlayerX >= AlienRange * -1 && AlienX[c] <= PlayerX)
                || (AlienX[c] - PlayerX <= AlienRange && AlienX[c] >= PlayerX))
            {
                PlayerCurrentHealth -= AlienAttack / PlayerArmor;
                Window.Draw(sf::Shape::Line(AlienX[c], AlienY[c], PlayerX, PlayerY, 1.f, sf::Color::Red));
            }

            else
            {
                AlienX[c] += cos(AlienHeading[c] * pi / 180) * AlienSpeed;
                AlienY[c] += sin(AlienHeading[c] * pi / 180) * AlienSpeed;
            }
        }
        else
        {
            AlienX[c] += cos(AlienHeading[c] * pi / 180) * AlienSpeed;
            AlienY[c] += sin(AlienHeading[c] * pi / 180) * AlienSpeed;
        }
}
}

//void Alien::BulletHit(float BulletX, float BulletY, float BulletX2, float BulletY2, int BulletDamage, int AlienCount, bool Debug) //Checks if bullet collides with Asteroid
//{
//        for (int c = 0; c < AlienCount; c++)
//        {
//            if ((BulletY - AlienY[c] >= 25 * -1 && BulletY <= AlienY[c]) || (BulletY - AlienY[c] <= 25 && BulletY >= AlienY[c]))
//            {
//            if ((BulletX - AlienX[c] >= 25 * -1 && BulletX <= AlienX[c]) || (BulletX - AlienX[c] <= 25 && BulletX >= AlienX[c]))
//                {
//                    AlienCurrentHealth[c] -= BulletDamage;
//                    BulletX = 2000;
//                    BulletY = 2000;
//
//                    if(Debug == true)
//                    {
//                    cout << "Alien # " << c << "hit!";
//                    }
//                }
//            }
//            if ((BulletY2 - AlienY[c] >= 25 * -1 && BulletY2 <= AlienY[c]) || (BulletY2 - AlienY[c] <= 25 && BulletY2 >= AlienY[c]))
//            {
//            if ((BulletX2 - AlienX[c] >= 25 * -1 && BulletX2 <= AlienX[c]) || (BulletX2 - AlienX[c] <= 25 && BulletX2 >= AlienX[c]))
//                {
//                    AlienCurrentHealth[c] -= BulletDamage;
//                    BulletX2 = 2000;
//                    BulletY2 = 2000;
//
//                    if(Debug == true)
//                    {
//                    cout << "Alien # " << c << "hit!";
//                    }
//                }
//            }
//        }
//}

void Alien::IsAlive(int AlienCount)
{
    for (int c = 0; c < AlienCount; c++)
    {
        if (AlienCurrentHealth[c] <= 0)
        {
                AlienCurrentHealth[c] = AlienMaxHealth;
                cout << "Alien terminated\n";
                AlienX[c] = rand()%(width+100) + width;
                AlienY[c] = rand()%(height+100) + height;
        }
    }
}

//int Alien::Attack(float PlayerX, float PlayerY, int PlayerCurrentHealth)
//{
//            if (InRange(PlayerX, PlayerY) == true)
//            {
//            PlayerCurrentHealth -= AlienAttack;
//            std::cout << "Alien (Hit)\n";
//            std::cout << PlayerCurrentHealth;
//            }
//
//            return PlayerCurrentHealth;
//}


#endif // Alien_H_INCLUDED
