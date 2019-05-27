#include "entity.h"

namespace Ann
{

Entity::Entity() : token(Entity::Empty), position() { }
Entity::~Entity() { }

Entity::Entity(char token, Vector2 position, int layer) {
    this->token = token;
    this->position = position;
    this->layer = layer;
}

} // namespace Ann
