//Main header
#include <Render.h>

//External headers
#include <math.h>


/*=================================================*/
/*==================   Metodos   ==================*/
/*=================================================*/

const int WINDOW_H = 720;
const int WINDOW_W = 1080;


/*=================================================*/
/*==================   Metodos   ==================*/
/*=================================================*/


/*
Destructor que llama a  la  funcion close de Render.
*/
Render::~Render()
{
    close();
}

/*
Inicializa el render creando una nueva ventana y reservando memoria para ella.
*/
void Render::init(Rvect size, std::string title)
{
    // Create the main window
    window = new sf::RenderWindow(sf::VideoMode(size.x, size.y), title);

    spritesCont = 1;

    globalScale = Rvect(1.f, 1.f);
    Render::getInstance()-> setMouse(false);    
}

/*
Llama a la funcion clearMemory() y libera la memoria reservada para la ventana.
*/
void Render::close()
{
    clearMemory();
    delete window;
}

/*
Devuelve true si la ventana esta abierta, sino devuelve false.
*/
bool Render::isWindowOpen()
{
    return window->isOpen();
}

/*
Devuelve la altura de la ventana.
*/
float Render::getWindowWidth()
{    
    return window->getSize().x;
}

/*
Devuelve la anchura de la ventana
*/
float Render::getWindowHeight(){
    
    return window->getSize().y;
}

/*
Funcion que se llama cuando incia el loop antes de pintar sprites.
Comprueba que la ventana este abierta, y borra todo lo dibujado antes.
*/
void Render::preLoop(float dt)
{
        // Process events
        sf::Event event;
        this->dt = dt;
        shakeTime -= dt;
        while (window->pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed){window->close();}

            if(event.type==sf::Event::KeyReleased){
                if(event.key.code == sf::Keyboard::Return){
                    enter_pressed=true;
                }
                if(event.key.code == sf::Keyboard::Escape){
                    escape_pressed=true;
                }
                if(event.key.code == sf::Keyboard::K){
                    k_pressed=true;
                }
            }    
            //else if(event.type == sf::Event::Resized)
            //{
            //    // update the view to the new size of the window
            //    globalScale.x = event.size.width / WINDOW_W;
            //    globalScale.y = event.size.height / WINDOW_H;
            //
            //    //sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            //    //window->setView(sf::View(visibleArea));
            //}
        }
        // Clear screen
        window->clear();
}

/*
Funcion que devuelve el valor de enter_pressed, para 
saber si el Enter ha sido pulsado.
*/
bool Render::isEnterPressed(){
    bool aux = enter_pressed;
    enter_pressed=false;
    return aux;
}

/*
Funcion que devuelve el valor de enter_pressed, para 
saber si el Escape ha sido pulsado.
*/
bool Render::isEscapePressed()
{
    return escape_pressed;
}

/*
Funcion que cambia el valor de la variable enter_pressed.
*/
void Render::setEscapePressed(bool press)
{
    escape_pressed=press;
}


/*
Funcion que devuelve el valor de k_pressed, para 
saber si la K ha sido pulsado.
*/
bool Render::isKPressed()
{
    return k_pressed;
}

/*
Funcion que cambia el valor de la variable k_pressed.
*/
void Render::setKPressed(bool press)
{
    k_pressed=press;
}

void Render::setMouse(bool mouse)
{
    window->setMouseCursorVisible(mouse);
}



/*
Funcion que se llama antes de terminar el loop.
Llama a la funcion update de la ventana.
*/
void Render::postLoop()
{
        // Update the window
        window->display();
}

/*
Borra toda la memoria reservada.
*/
void Render::clearMemory()
{
    sprites.clear();
    textures.clear();

    spritesCont = 1;
}

/*
Aplica la escala global a todos los sprites.
*/
void Render::setGlobalScale(Rvect scale)
{
    globalScale = scale;
}

/*
Devuelve la escala global que se aplica a todos los sprites.
*/
Rvect Render::getGlobalScale()
{
    return globalScale;
}

Rvect Render::getCursorPosition()
{
   sf::Vector2i pos = sf::Mouse::getPosition(*window); 	
   return Rvect(pos.x, pos.y);
}
/*
Carga la textura en la memoria, devuelve true si existe y false si no existe.
Si la textura ya estaba cargada no la actualiza
*/
bool Render::loadTexture(std::string texture)
{
    if(textures.find(texture)!=textures.end())
        return true;
        
    sf:: Texture*  tex= new sf::Texture();
    if(!tex->loadFromFile(texture))
        return false;

    textures.insert(std::pair<std::string, sf::Texture*>(texture, tex));

    return true;
}

/*
Borra la textura de la memoria y la libera, devuelve true si la textura existia
y false si no existia.
*/
bool Render::deleteTexture(std::string texture)
{
    bool r = false;
    if(textures.find(texture)!=textures.end())
    {
        delete textures.find(texture)->second;
        textures.erase(texture);
        r=true;
    }

    return r;
}

/*
Si la textura estaba cargada en la memoria devuelve un puntero.
Si no estaba cargada devuelve nullptr.
*/
sf::Texture* Render::getTexture(std::string texture)
{
    auto it = textures.find(texture);
    if (it != textures.end())
        return it->second;
    
    return nullptr;
}


/*
Carga un sprite con la textura pasada por parametro.
Devuelve el ide en sprite. Devuelve 0 si no existe la textura
y no carga nada.
*/
Rint Render::createSprite(std::string texture)
{
    if(!loadTexture(texture))
        return 0;
    
    Rint id = spritesCont;
    spritesCont++;

    sf::Sprite* s = new sf::Sprite(*getTexture(texture));

    sprites.insert(std::pair<Rint, sf::Sprite*>(id, s));

    return id;
}

/*
Carga un sprite con la textura recortada por rectangle pasada por parametro.
Devuelve el id en sprite. Devuelve 0 si no existe la textura
y no carga nada.
*/
Rint Render::createSprite(std::string texture, Rrect rectangle)
{
        if(!loadTexture(texture))
        return 0;
    
    Rint id = spritesCont;
    spritesCont++;

    sf::Sprite* s = new sf::Sprite(*getTexture(texture), sf::IntRect(rectangle.x, rectangle.y, rectangle.w, rectangle.h));

    sprites.insert(std::pair<Rint, sf::Sprite*>(id, s));

    return id;
}

/*
Devuelve el puntero al sprite identificado en sprite, si no existe devuelve nullptr
*/
sf::Sprite* Render::getSprite(Rint sprite)
{
    auto it = sprites.find(sprite);
    if (it != sprites.end())
        return it->second;
    
    return nullptr;
}

/*
Borra el sprite de la memoria y la libera, devuelve true si el sprite existia
y false si no existia.
*/
bool Render::deleteSprite(Rint sprite)
{
    bool r = false;
    if(sprites.find(sprite)!=sprites.end())
    {
        delete sprites.find(sprite)->second;
        sprites.erase(sprite);
        r=true;
    }

    return r;
}

/*
Dibuja el sprite pasado por parametro.
Devuelve false si no existe.
*/
bool Render::drawSprite(Rint sprite)
{
    bool r = false;
    if(sprites.find(sprite)!=sprites.end())
    {
        sprites.find(sprite)->second->setScale(sf::Vector2f(1, 1));
        sprites.find(sprite)->second->scale(sf::Vector2f(globalScale.x, globalScale.y));
        window->draw(*sprites.find(sprite)->second);
        
        r=true;
    }

    return r;
}


/*
Dibuja el sprite  pasado por parametro. Si centerd es true coloca el origen en el centro del objeto, sino en el 0,0.
Aplica las transformaciones pasadas en el orden S R T. Justo tras el escalado aplica el escalado global.
*/
bool Render::drawSprite(Rint sprite, Rvect position, float rotation, float scale, bool centered)
{
    if(sprites.find(sprite)==sprites.end())
        return false;


    sf::Sprite* s = sprites.find(sprite)->second;

    if(centered)
    {
        s->setOrigin(s->getLocalBounds().width*.5, s->getLocalBounds().height*.5);
    }else
    {
        s->setOrigin(0.f, 0.f);
    }
    
    s->setScale(sf::Vector2f(scale, scale));
    s->scale(sf::Vector2f(globalScale.x, globalScale.y));
    s->setRotation(rotation);

    float sh = 0.f;

    if(shakeTime>0.f)
        sh = 4*sin(shakeTime * 80);

    s->setPosition(sf::Vector2f(position.x*globalScale.x + sh, position.y*globalScale.y + sh)); 

    window->draw(*s);

    return true;   
}


/*
Crea una animacion con los fps dados y devuelve el id de ella.
*/
Rint Render::createAnimation(float fps)
{
    Rint id = animationsCont;
    animationsCont++;

    Animation* a = new Animation(fps);

    animations.insert(std::pair<Rint, Animation*>(id, a));

    return id;
}

/*
Si encuentra la animacion , le añade el fotograma sprite, y devuelve true, sino devuelve false.
*/
bool Render::addFrameToAnimation(Rint animation, Rint sprite)
{
    bool r = false;
    if(animations.find(animation)!=animations.end())
    {
        animations.find(animation)->second->addFrame(sprite);
        r=true;
    }

    return r;
}

/*
Devuelve un puntero al objeto animation. En caso de no existir devuelve nullptr.
*/
Animation* Render::getAnimation(Rint animation)
{
    if(animations.find(animation)!=animations.end())
        return animations.find(animation)->second;

    return nullptr;
}

/*
Llama al desctructor de la case animation, que a su vez llama al destructor de todos los sprites, y se 
libera toda la memoria. En caso de que no encuentre la animacion devuelve false.
*/
bool Render::deleteAnimation(Rint animation)
{
    bool r = false;
    if(animations.find(animation)!=animations.end())
    {
        delete animations.find(animation)->second;
        animations.erase(animation);
        r=true;
    }

    return r;
}

/*
Busca la animacion y borra todos sus sprites.
*/
bool Render::clearAnimation(Rint animation)
{
    bool r = false;
    if(animations.find(animation)!=animations.end())
    {
        animations.find(animation)->second->clear();
        r = true;
    }

    return r;
}



/*
Si encuentra la animacion, dibuja el fotograma correspondiente sin aplicarle ninguna transfomrmacion y devuelve true.
En caso de no encontrar la animacion devuelve false.
*/
bool Render::drawAnimation(Rint animation)
{
    bool r = false;
    if(animations.find(animation)!=animations.end())
    {
        animations.find(animation)->second->draw(dt);        
        r=true;
    }

    return r;
}

/*
Si encuentra la animacion, dibuja el fotograma correspondiente aplicandole las transformaciones dadas por parametro y devuelve true.
En caso de no encontrar la animacion devuelve false.
*/
bool Render::drawAnimation(Rint animation, Rvect position, float rotation, float scale, bool centered)
{
    bool r = false;
    if(animations.find(animation)!=animations.end())
    {
        animations.find(animation)->second->draw(dt, position, rotation, scale, centered);        
        r=true;
     
    }

    return r;
}

/*
It shakes all the window for .2f seconds 
*/
void Render::shake()
{

    shakeTime = .2f;
}


/*
Devuelve las coordenadas polares pasadas por parametro en coordenadas cartesiaanas
*/
Rvect Render::polarToCartesian(float r, float a)
{
    float toRadians = 3.1415926/180;
    float x = r*cos(a*toRadians);
    float y = r*sin(a*toRadians);

    return Rvect(x, y);
}

/*
Text is NOT supported on this facade, so if you want to write some text, you will hay to handle it!
This function is for draw your text.
*/
void Render::drawText(sf::Text text)
{
    window->draw(text);
}

void Render::drawRectangle(sf::RectangleShape rectangle)
{
    window->draw(rectangle);

}

void Render::drawCircle(Rvect position, float radious, bool centered)
{
    float x = position.x;
    float y = position.y;
    c.setRadius(radious);
    if(centered)
    {
        x -= radious;
        y -= radious;
    }
    c.setPosition(sf::Vector2f(x, y));
    c.setOutlineThickness(1);
    c.setOutlineColor(sf::Color(0, 225, 0));
    c.setFillColor(sf::Color(0, 0, 0, 0));
    window->draw(c);
}

void Render::drawRectangle(Rvect position, Rvect size, bool centered)
{
    r.setSize(sf::Vector2f(size.x, size.y));
    float x = position.x;
    float y = position.y;
    if(centered)
    {
        x -= size.x/2;
        y -= size.y/2;
    }

    r.setPosition(sf::Vector2f(x, y));
    r.setOutlineThickness(1);
    r.setOutlineColor(sf::Color(0, 225, 0));
    r.setFillColor(sf::Color(0, 0, 0, 0));
    window->draw(r);
}





/*
=============================================================================================
=============================================================================================
====================    Funciones de la clase Animacion     =================================
=============================================================================================
=============================================================================================
*/
/*
Crea una animacion con la velodicad en fps a la que se cambiara de frame.
*/
Animation::Animation(Rint fps)
{
    frames = 0;
    this->fps = fps;
    dt = 0.f;
    drawing = 0;
}


/*
Llama a la funcin deleteSprite de la clase Render de todos los sprites que tiene la animacion.
*/
Animation::~Animation()
{
    for(size_t i = 0; i< sprites.size(); i++)
    {
        if(sprites.at(i))
            Render::getInstance()->deleteSprite(sprites.at(i));
    }
    sprites.clear();
}

/*
Añade un nuevo fotograma a la animacion.
*/
void Animation::addFrame(Rint frame)
{
    sprites.push_back(frame);
    frames++;
}

/*
Borra todos los frames de la animacion
*/
void Animation::clear()
{
    for(std::size_t i = 0; i< sprites.size(); i++)
            Render::getInstance()->deleteSprite(sprites.at(i));

    sprites.clear();
}

/*
Dibuja la animacion.
*/
void Animation::draw(float dt)
{
    this->dt += dt;

    if(this->dt<1/fps)
    {
        this->dt = 0.f;
        drawing++;

        if(drawing>=frames)
            drawing = 0;
    }
    Render::getInstance()->drawSprite(sprites.at(drawing));

}

/*
Dibuja la animacion aplicandole las transformaciones pasadas por parametro
*/
void Animation::draw(float dt, Rvect position, float rotation, float scale, bool centered)
{
    this->dt += dt;
    float et = 1.f/fps;
    if(this->dt>et)
    {
        this->dt = 0.f;
        drawing++;

        if(drawing>=frames)
            drawing = 0;
    }

    Render::getInstance()->drawSprite(sprites.at(drawing), position, rotation, scale, centered);
}