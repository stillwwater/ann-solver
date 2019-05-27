#include "room.h"
#include "entity.h"

namespace Ann
{

Room::Room(int width, int height, int layers) {
    this->width = width;
    this->height = height;
    this->layers = layers;
    this->map = new Entity[width * height * layers];
    this->state = Room::Ok;
}

Room::~Room() {
    delete[] this->map;
}

} // namespace Ann