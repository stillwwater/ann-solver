#include <string>
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
    this->solution = std::string();
}

Room::Room(const Room* room) {
    this->width = room->width;
    this->height = room->height;
    this->layers = room->layers;
    this->lookup = room->lookup;
    this->solution = room->solution;

    int size = room->width * room->height * room->layers;
    this->map = new Entity[size];
    std::copy(room->map, room->map + size, this->map);
    this->state = room->state;
}

Room::~Room() {
    delete[] this->map;
}

} // namespace Ann