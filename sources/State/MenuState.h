#pragma once

//Headers
#include <State.h>

//Forward declarations
class Menu;

class MenuState : public State 
{
    private: 
        Menu* menu;
        MenuState(){}         
    public:

        static MenuState* getInstance(){
            static MenuState only_instance;
            return &only_instance;
        }
        virtual void initState();
        virtual void update(float dt);
        virtual void clear();
        virtual void draw();

};