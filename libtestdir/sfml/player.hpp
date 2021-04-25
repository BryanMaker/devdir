#ifndef PLAYER
#define PLAYER
#include "libsfml.hpp"
#include <cmath>

class Player:public sf::Drawable
{
private:
    sf::RectangleShape _shape;
    sf::Vector2f _velocity;


    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
public:
    Player();
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    
    template<typename...Args>
    void setPosition(Args&&...args);
    void update(sf::Time deltaTime);

    bool isMoving;
    int rotation;
};
#endif
