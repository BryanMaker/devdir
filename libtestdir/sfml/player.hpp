#ifndef PLAYER
#define PLAYER
#include "libsfml.hpp"

class Player:public sf::Drawable
{
private:
    sf::RectangleShape _shape;
    sf::Vector2f _velocity;
    
public:
    Player();
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    
    template<typename...Args>
    void setPosition(Args&&...args)
    {
        _shape.setPosition(std::forward<Args>(args)...);
    }
};
#endif
