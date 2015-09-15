#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include <vector>

using namespace std;

class Star
    {
        public:
        Star(sf::RenderWindow &window);
        void Draw(int, int, int, int, int);
        void Initialize(int);

        vector <float> GlobalStarX;
        vector <float> GlobalStarY;

        vector <float> RenderStarX;
        vector <float> RenderStarY;

        vector <float> StarRad;

        vector <bool> IsDrawable;

        sf::Vector2f StarPos[5000];

        private:
        sf::RenderWindow &Window;
    };

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Planet
    {
        public:
            Planet(sf::RenderWindow &window);

            void Draw(int, sf::Sprite*, sf::Sprite*, sf::Sprite*, sf::Sprite*);
            void Initialize(int);
            void CheckDraw(int,int,int);

            vector <float> GlobalPlanetX;
            vector <float> GlobalPlanetY;

            vector <float> RenderPlanetX;
            vector <float> RenderPlanetY;

            vector <float> PlanetRand;
            vector <float> PlanetSize;

            vector <bool> IsDrawable;

        private:
            sf::RenderWindow &Window;
    };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Moon
    {
        public:
        Moon(sf::RenderWindow &window);
        void Draw(int, int, int, sf::Sprite*);
        void Initialize();
        void CheckDraw(int,int,int);
        void Move(int, vector<float>, vector<float>, vector<float>, sf::Sprite*);

        vector <float> GlobalMoonX;
        vector <float> GlobalMoonY;

        vector <float> RenderMoonX;
        vector <float> RenderMoonY;

//        vector <float> MoonRad;

        vector <bool> IsDrawable;

        float theta;

        private:
        sf::RenderWindow &Window;
    };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Spacestation
    {
        public:
        Spacestation(sf::RenderWindow &window);
        void Draw(int, int, int, sf::Sprite*);
        void Initialize();
        void CheckDraw(int,int,int);
        void Move(int, vector<float>, vector<float>);

        vector <float> GlobalStationX;
        vector <float> GlobalStationY;

        vector <float> RenderStationX;
        vector <float> RenderStationY;

        vector <float> StationRad;

        vector <bool> IsDrawable;

        float theta;

        private:
        sf::RenderWindow &Window;
    };
#endif // BACKGROUND_H_INCLUDED
