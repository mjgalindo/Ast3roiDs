//Constructor
Nave::Nave(sf::Vector2f posicion_inicial){
    puntos[0] = sf::Vector2f(0.0,0.2);
    puntos[1] = sf::Vector2f(-0.1,-0.2);
    puntos[2] = sf::Vector2f(0.1,-0.2);

    direccion = 0;

    //Posicion de la nave
    posicion = posicion_inicial;
    //Velocidad de la nave
    sf::Vector2f velocidad = sf::Vector2f(0.0, 0.0);
    //Numero de disparos
    int disparos = 0;
}

//Destructor
Nave::~Nave(){}

//Setters
void Nave::setPuntos(sf::Vector3f ps[3]){
    puntos = ps;
}

void Nave::setDireccion(float dir){
    direccion = dir;
}

void Nave::setPosicion(sf::Vector2f posicion){
    posicion = pos;
}

void Nave::setVelocidad(sf::Vector2f vel){
    velocidad = vel;
}

//Getters
sf::Vector2f* Nave::getPuntos(){
    return puntos;
}

float Nave::getDireccion(){
    return direccion;
}

sf::Vector2f Nave::getPosicion(){
    return posicion;
}

sf::Vector2f Nave::getVelocidad(){
    return velocidad;
}

//Otros
void Nave::disparar(){

}

void Nave::rotarIzda(){
    direccion += V_ANGULAR;
}

void Nave::rotarDcha(){
    direccion -= V_ANGULAR;
}

void Nave::mover(){
    posicion.x += velocidad.x;
    posicion.y += velocidad.y;
}

void Nave::acelerar(){
    velocidad.x += sen(direccion);
    velocidad.y += cos(direccion);
}