#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED


class Bullet
{
public:
    Bullet (sf::RenderWindow &window, float BD = 100);

    float BulletSpeed[ConstBulletCount];
    float BulletDamage;
    float BulletX[ConstBulletCount];
    float BulletY[ConstBulletCount];
    float BulletX2[ConstBulletCount];
    float BulletY2[ConstBulletCount];
    float BulletHeading[ConstBulletCount];
    float BulletHeading2[ConstBulletCount];

    void Disappear(int);

private:
    sf::RenderWindow &Window;
};

Bullet::Bullet(sf::RenderWindow &window, float BD):

    BulletDamage(BD),
    Window(window)

{}
//
//void Bullet::Disappear(int TurretX, int TurretY)
//{
//    BulletX[x] = TurretX;
//    BulletY[x] = TurretY;
//    BulletSpeed[x] = 0;
//
//    BulletOn = false;
//}


//void Bullet::Move()
//{
//    for (int x = 0; x < global.BulletCount; x++)
//    {
//        bl.BulletX[x] += cos(bl.BulletHeading[x] * pi / 180) * bl.BulletSpeed[x];
//        bl.BulletY[x] += sin(bl.BulletHeading[x] * pi / 180) * bl.BulletSpeed[x];
//
//        bl.BulletX2[x] += cos(bl.BulletHeading2[x] * pi / 180) * bl.BulletSpeed[x];
//        bl.BulletY2[x] += sin(bl.BulletHeading2[x] * pi / 180) * bl.BulletSpeed[x];
//     {
//}
//
//void Bullet::Draw()
//{
//        SRBullet[x].SetPosition(bl.BulletX[x], bl.BulletY[x]);
//        SRBullet[x].SetRotation(bl.BulletHeading[x] * -1);
//        App.Draw(SRBullet[x]);
//
//        SRBullet2[x].SetPosition(bl.BulletX2[x], bl.BulletY2[x]);
//        SRBullet2[x].SetRotation(bl.BulletHeading2[x] * -1);
//        App.Draw(SRBullet2[x]);
//}

//    for (int c = 0; c < global.AsteroidCount; c++)
//        {
//            for (int x = 0; x < global.BulletCount; x++)
//            {
//                if ((bl.BulletY[x] - as.RenderAsteroidY[c] >= 25 * -1 && bl.BulletY[x] <= as.RenderAsteroidY[c]) || (bl.BulletY[x] - as.RenderAsteroidY[c] <= 25 && bl.BulletY[x] >= as.RenderAsteroidY[c]))
//                {
//                    if ((bl.BulletX[x] - as.RenderAsteroidX[c] >= 25 * -1 && bl.BulletX[x] <= as.RenderAsteroidX[c]) || (bl.BulletX[x] - as.RenderAsteroidX[c] <= 25 && bl.BulletX[x] >= as.RenderAsteroidX[c]))
//                    {
//                        as.AsteroidCurrentHealth[c] -= bl.BulletDamage;
//                        bl.Disappear(c);
//
//                        if (global.Debug == true) {cout << "Asteroid # " << c << "hit!";}
//                    }
//                }
////            if ((bl.BulletY2[x] - as.RenderAsteroidY[c] >= 25 * -1 && bl.BulletY2[x] <= as.RenderAsteroidY[c]) || (bl.BulletY2[x] - as.RenderAsteroidY[c] <= 25 && bl.BulletY2[x] >= as.RenderAsteroidY[c]))
////            {
////            if ((bl.BulletX2[x] - as.RenderAsteroidX[c] >= 25 * -1 && bl.BulletX2[x] <= as.RenderAsteroidX[c]) || (bl.BulletX2[x] - as.RenderAsteroidX[c] <= 25 && bl.BulletX2[x] >= as.RenderAsteroidX[c]))
////                {
////                    as.AsteroidCurrentHealth[c] -= bl.BulletDamage;
////                    bl.BulletX2[x] = NULL;
////                    bl.BulletY2[x] = NULL;
////
////                    if (global.Debug == true) {cout << "Asteroid # " << c << "hit!";}
////                }
////                }
//            }
//        }

//---------------------- Shoot -----------------------

//    if (TurretFiring == true)
//    {
//

//                if (global.Debug == true)
//                {   cout << "Reload!\n";    }
//
//                BulletCounter = 0;
//            }
//
//                TempMX[BulletCounter] = MouseX;
//                TempMY[BulletCounter] = MouseY;
//
//                bl.BulletX[BulletCounter] = tr.TurretX[0];
//                bl.BulletY[BulletCounter] = tr.TurretY[0];
//
//                bl.BulletHeading[BulletCounter] = atan2(TempMY[BulletCounter] - bl.BulletY[BulletCounter],
//                                                        TempMX[BulletCounter] - bl.BulletX[BulletCounter]) * 180 / pi;
//                if (pl.PlayerLevel >= 2)
//                {
//                    bl.BulletX2[BulletCounter] = tr.TurretX[1];
//                    bl.BulletY2[BulletCounter] = tr.TurretY[1];
//
//                    bl.BulletHeading2[BulletCounter] = atan2(TempMY[BulletCounter] - bl.BulletY2[BulletCounter],
//                                                        TempMX[BulletCounter] - bl.BulletX2[BulletCounter]) * 180 / pi;
//                }
//    }
//
//    if (ShipFiring == true)
//    {
//        if (BulletCounter <= global.BulletCount - 2)
//        {
//            BulletCounter += 1;
//
//            float LaserX[ConstBulletCount];
//            float LaserY[ConstBulletCount];
//
//            LaserX[BulletCounter] = 1500 * cos(0.017453277777 * pl.PlayerHeading) + pl.RenderPlayerX;
//            LaserY[BulletCounter] = 1500 * sin(0.017453277777 * pl.PlayerHeading) + pl.RenderPlayerY;
//
//            bl.BulletX[BulletCounter] = pl.RenderPlayerX;
//            bl.BulletY[BulletCounter] = pl.RenderPlayerY;
//            bl.BulletSpeed[BulletCounter] = 25;
//
//            bl.BulletHeading[BulletCounter] = atan2(LaserY[BulletCounter] - bl.BulletY[BulletCounter], LaserX[BulletCounter] - bl.BulletX[BulletCounter]) * 180 / pi;
//        }
//
//        else if (BulletCounter == global.BulletCount - 1) { BulletCounter = 1;}
//    }


#endif // BULLET_H_INCLUDED
