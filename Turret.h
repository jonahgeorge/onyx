#ifndef TURRET_H_INCLUDED
#define TURRET_H_INCLUDED


class Turret
{
public:
    Turret (sf::RenderWindow &window, float TR = 250, float TA = 5);

    float TurretHeading[TurretCount];
    float TurretRange;
    float TurretAttack;
    float TurretDistance[TurretCount];
    float TurretX[TurretCount];
    float TurretY[TurretCount];

    void OnTarget(float,float,int, sf::Sprite*);

private:
    sf::RenderWindow &Window;
};

Turret::Turret(sf::RenderWindow &window, float TR, float TA):

    TurretRange(TR),
    TurretAttack(TA),
    Window(window)

{
TurretDistance[0] = -2;
//TurretDistance[1] = 0.5;
//TurretDistance[2] = -15;
}

void Turret::OnTarget(float RenderPlayerX, float RenderPlayerY, int PlayerHeading, sf::Sprite* SRTurret)
{
//    const sf::Input& Input = Window.GetInput();
    sf::Vector2f MousePos = Window.ConvertCoords(Window.GetInput().GetMouseX(), Window.GetInput().GetMouseY());

    float A2[2] = {};
    float B2[2] = {};
//    float C2[2] = {};

        for(int x = 0; x < TurretCount; x++)
    {
        TurretX[x] = TurretDistance[x] * cos(0.017453277777 * PlayerHeading) + RenderPlayerX;
        TurretY[x] = TurretDistance[x] * sin(0.017453277777 * PlayerHeading) + RenderPlayerY;

        SRTurret[x].SetPosition(TurretX[x],TurretY[x]);

        A2[x] = (MousePos.x - RenderPlayerX);
        B2[x] = (MousePos.y - RenderPlayerY);
//        C2[x] = sqrt(A2[x] + B2[x]);

        TurretHeading[x] = ((-180 / pi) * atan(B2[x] /A2[x])) + 90;

        if (TurretHeading[x] < 0) {TurretHeading[x] = 360;}
        if (TurretHeading[x] > 360) {TurretHeading[x] = 0;}
        if (MousePos.x > RenderPlayerX) {TurretHeading[x] = TurretHeading[x] + 180;}

        SRTurret[x].SetRotation(TurretHeading[x]);
    }
}
#endif // TURRET_H_INCLUDED
