#ifndef ASTEROID_H_INCLUDED
#define ASTEROID_H_INCLUDED

#include <vector>

using namespace std;

class Asteroid
{
public:
    Asteroid (sf::RenderWindow &window, float AS = 1.f, int AR = 25, int AA = 1, int AMH = 100);

    void InRange(int, float, float, float, int&, int, bool);
    void Drift(int);
    void IsAlive(int&);
    void Rand(int);
    void RenderCalc(int,int,int);
    void Initialize(int);

    void CheckSelect(int,int,int,int,int);

    void CheckDraw(int,int,int);
    void Draw(int, int, sf::Sprite*);

    void CheckDead(int);
    void Dead(int, sf::Sprite*, bool, int);

    float AsteroidSpeed;
    int AsteroidRange;
    int AsteroidAttack;

    vector <int> AsteroidCurrentHealth; //[AsteroidCount]

    float AsteroidMaxHealth;

    vector <float> GlobalAsteroidX;
    vector <float> GlobalAsteroidY;

    vector <float> RenderAsteroidX;
    vector <float> RenderAsteroidY;

    vector <int> AsteroidHeading;

    vector <bool> IsDrawable;
    vector <bool> IsSelect;
    vector <bool> IsDead;

private:
    sf::RenderWindow &Window;
};

#endif // ASTEROID_H_INCLUDED




//void Asteroid::BulletHit(float& BulletX, float& BulletY, float& BulletX2, float& BulletY2, int BulletDamage, int AsteroidCount, bool Debug, int BulletCount) //Checks if bullet collides with Asteroid
//{
//        for (int c = 0; c < AsteroidCount; c++)
//        {
//                for (int x = 0; x < BulletCount; x++)
//                {
//            if ((BulletY[x] - AsteroidY[c] >= 25 * -1 && BulletY[x] <= AsteroidY[c]) || (BulletY[x] - AsteroidY[c] <= 25 && BulletY[x] >= AsteroidY[c]))
//            {
//            if ((BulletX[x] - AsteroidX[c] >= 25 * -1 && BulletX[x] <= AsteroidX[c]) || (BulletX[x] - AsteroidX[c] <= 25 && BulletX[x] >= AsteroidX[c]))
//                {
//                    AsteroidCurrentHealth[c] -= BulletDamage;
//                    BulletX[x] = 2000;
//                    BulletY[x] = 2000;
//
//                    if (Debug == true)
//                    {
//                    cout << "Asteroid # " << c << "hit!";
//                    }
//                }
//            }
//            if ((BulletY2[x] - AsteroidY[c] >= 25 * -1 && BulletY2[x] <= AsteroidY[c]) || (BulletY2[x] - AsteroidY[c] <= 25 && BulletY2[x] >= AsteroidY[c]))
//            {
//            if ((BulletX2[x] - AsteroidX[c] >= 25 * -1 && BulletX2[x] <= AsteroidX[c]) || (BulletX2[x] - AsteroidX[c] <= 25 && BulletX2[x] >= AsteroidX[c]))
//                {
//                    AsteroidCurrentHealth[c] -= BulletDamage;
//                    BulletX2[x] = 2000;
//                    BulletY2[x] = 2000;
//
//                    if (Debug == true)
//                    {
//                    cout << "Asteroid # " << c << "hit!";
//                    }
//                }
//                }
//            }
//        }
//}

//void Asteroid::IsAlive(int &PlayerCurrentExp)
//{
//        for (int c = 0; c < AsteroidCount; c++)
//    {
//        if (AsteroidCurrentHealth[c] <= 0)
//        {
////                SExplo.SetCenter(AsteroidX[c], AsteroidY[c]);
//                Window.Draw(SExplo);
//
//                AsteroidCurrentHealth[c] = AsteroidMaxHealth;
//                std::cout << "Asteroid #" << c << " || Terminated\n";
//                AsteroidX[c] = 0;
//                AsteroidY[c] = 0;
//                PlayerCurrentExp += 5;
//        }
//    }
//}
//
//int Asteroid::Attack(float PlayerX, float PlayerY, int PlayerCurrentHealth)
//{
//         for (int c = 0; c < AsteroidCount; c++)
//    {
//            if (InRange(PlayerX, PlayerY) == true)
//            {
//            PlayerCurrentHealth -= AsteroidAttack;
//            std::cout << "Asteroid (Hit)\n";
//            std::cout << PlayerCurrentHealth;
//            }
//            return PlayerCurrentHealth;
//    }
//}



