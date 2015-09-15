#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

class Enemy
{
    public:
        Enemy (sf::RenderWindow &window);

        void Initialize();

        void RenderCalc();
        //void Rand();

        void Spawn();
        void RandPos();
        void GetHit();

        void CheckSelect();

        void CheckDraw();
        virtual void Draw();

        void CheckDead();
        virtual void Dead();

        void InRange();

        virtual float Speed;
        virtual int Range;
        virtual int Attack;
        virtual int MaxHealth;

        vector <float> GlobalX;
        vector <float> GlobalY;

        vector <float> RenderX;
        vector <float> RenderY;

        vector <int> Heading;
        vector <int> CurrentHealth;

        vector <bool> IsSelected;
        vector <bool> IsDrawable;
        vector <bool> IsDead;

    private:
        sf::RenderWindow &Window;
};

Enemy::Enemy(sf::RenderWindow &window):

    Window (window)

{};


class Seeker : public Enemy
{
    public:
        Seeker (sf::RenderWindow &window, float S = 7.f, int R = 100, int A = 0.5f, int MH = 100)

        void Draw();
        void Dead();

        float Speed;
        int Range;
        int Attack;
        int MaxHealth;

};

Seeker::Seeker(sf::RenderWindow &window, float S, int R, int A, int MH)

    Speed(S),
    Range(R),
    Attack(A),
    MaxHealth(MH),
    Window (window)

{};


class Fighter : public Enemy
{
    public:
        Fighter (sf::RenderWindow &window, float S = 5.f, int R = 150, int A = 1f, int MH = 500)

        void Draw();
        void Dead();

        float Speed;
        int Range;
        int Attack;
        int MaxHealth;
};

Fighter::Fighter(sf::RenderWindow &window, float S, int R, int A, int MH)

    Speed(S),
    Range(R),
    Attack(A),
    MaxHealth(MH),
    Window (window)

{};

class Titan : public Enemy
{
    public:
        Titan (sf::RenderWindow &window, float S = 3.f, int R = 200, int A = 2.f, int MH = 1000)

        void Draw();
        void Dead();

        float Speed;
        int Range;
        int Attack;
        int MaxHealth;
};

Titan::Titan(sf::RenderWindow &window, float S, int R, int A, int MH)

    Speed(S),
    Range(R),
    Attack(A),
    MaxHealth(MH),
    Window (window)

{};

void Enemy::Initialize(int c)
{
    for (unsigned int cycle = 0; cycle < c; ++cycle)
    {
        GlobalX.push_back(NULL);
        GlobalY.push_back(NULL);

        RenderX.push_back(NULL);
        RenderY.push_back(NULL);

        IsDrawable.push_back(false);
        IsSelect.push_back(false);
        IsDead.push_back(false);

        Heading.push_back(NULL);
        CurrentHealth.push_back(MaxHealth);
    }
}

void Enemy::RenderCalc(int c, int ViewX, int ViewY)
{
        RenderX[c] = GlobalX[c] - ViewX;
        RenderY[c] = GlobalY[c] - ViewY;
}

void Enemy::RandPos(int c)
{
    GlobalX[c] = rand()%GameWidth + 1;
    GlobalY[c] = rand()%GameHeight + 1;
}

void Enemy::Spawn(int c)
{
        RandPos(c);

        CurrentHealth[c] = 500;
}

void Enemy::GetHit(int PlayerAttack, int c)
{
    CurrentHealth[c] -= PlayerAttack;
}

void Enemy::CheckDead(int c)
{
    if (CurrentHealth[c] <= 0)
    {
        IsDead[c] = true;
    }
}

void Enemy::CheckSelect(int c, int GlobalSelectBox1X, int GlobalSelectBox1Y, int GlobalSelectBox2X, int GlobalSelectBox2Y)
{
    if ((GlobalY[c] >= GlobalSelectBox1Y && GlobalY[c] <= GlobalSelectBox2Y) || (GlobalY[c] >= GlobalSelectBox2Y && GlobalY[c] <= GlobalSelectBox1Y))
    {
        if ((GlobalX[c] >= GlobalSelectBox1X && GlobalX[c] <= GlobalSelectBox2X) || (GlobalX[c] >= GlobalSelectBox2X && GlobalX[c] <= GlobalSelectBox1X))
        {
            IsSelect[c] = true;
        }
    }
}

void Enemy::CheckDraw(int ViewX, int ViewY, int c)
{
    if ((GlobalRedY[c] - ViewY >= WindowHeight * -1 && GlobalRedY[c] <= ViewY) || (GlobalRedY[c] - ViewY <= WindowHeight && GlobalRedY[c] >= ViewY))
    {
        if ((GlobalRedX[c] - ViewX >= WindowWidth * -1 && GlobalRedX[c] <= ViewX) || (GlobalRedX[c] - ViewX <= WindowWidth && GlobalRedX[c] >= ViewX))
        {
            IsDrawable[c] = true;
        }
    }
}

#endif // ENEMY_H_INCLUDED
