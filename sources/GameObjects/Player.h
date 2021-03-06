#pragma once

//Header
#include <Ship.h>

class Player : public Ship {
    protected:
        int powerUp; //Variable que dicta si el Player ha cogido un powerUp pasivo, y lo identifica mediante un numero.
        int shield = 0;
        float vtime = 0;
        unsigned int escudo;
        unsigned int velocity;
        bool show_velocity=false;
    public: 
        Player(float x, float y); //Constructor por defecto de la clase Player.

        //Player(sf::Texture t); //Metodo constructor de la clase Player. Es necesario pasarle una Textura.

        ~Player(); //Metodo destructor de la clase Player.

        void move(); //Sobrecarga del metodo de movimiento la clase padre.

        void shoot(bool p = true);

        int getPUp(); //Metodo para recuperar el powerUp pasivo actual del Player.

        void setPUp(int i); //Metodo para cambiar el powerUp pasivo actual del Player.

        void hpUp(int hp);

        void speedUp();
        
        void setShield();

        bool hpDown(int hp);

        void setHp(int nu);

        void cambioArma();
        
        void update(float dt);

        void draw();

        

};

