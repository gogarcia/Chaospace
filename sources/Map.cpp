#include "Map.h"
#include "Player.h"
#include <iostream>
#include <Ship.h>
#include <Npc.h>

/*
Game update. Devuelve false si el jugador ha muerto.
*/
bool Map::update(float dt)
{
    player->update (dt);
    npc->update(dt);
}

/*
Borra toda la informacion del mapa
*/
void Map::clear()
{ 
 
}
 
/*
Inicia el mapa
*/
void Map::init()
{
    player = createPlayer(100.f, 360.f);
    npc = new Npc(4, 600.f, 360.f);

}

/*
Devuelve una nave creada
*/
Ship* Map::createShip()
{

}


/* 
Devuelve el player creado
*/
Player* Map::createPlayer(float x, float y)
{
    return new Player(x, y);
}
 

/*
Carga un nivel
*/
void Map::loadLevel()
{

}

/*
Carga toda la información del mapa
*/
void Map::loadMapInfo()
{

}

/*
Dibujado del mapa
*/  
void Map::draw()
{

}