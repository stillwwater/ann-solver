#ifndef _ANN_ENGINE
#define _ANN_ENGINE
#include <string>
#include "vector2.h"
#include "entity.h"
#include "room.h"

namespace Ann
{
namespace Engine
{

Room* create_room(const char* level, int width, int height);

Room::State exec(Room* room, const char* input, bool show);
Room::State exec(Room* room, char direction);

bool move(Room* room, Vector2 direction);
Vector2 move(Room* room, Entity* entity, Vector2 direction);

Entity& read(Room* room, Vector2 position, int layer);
void write(Room* room, Entity entity);

char* serialize(Room* room);
void pprint(Room* room);
void print_state(const Room* word);

int map_layer(char token);

MoveState leave(char left, char right);
MoveState collide(char left, char right);

} // namespace Engine
} // namespace Ann

#endif