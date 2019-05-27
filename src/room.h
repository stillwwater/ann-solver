#ifndef _ANN_ROOM
#define _ANN_ROOM
#include <vector>
#include "entity.h"
#include "vector2.h"

namespace Ann
{

struct Room
{
    enum State { Ok, Pass, Fail };
    int width, height, layers;
    State state;
    std::vector<Vector2> lookup;
    Entity* map;

    Room(int width, int height, int layers);
    ~Room();
};

} // namespace Ann

#endif
