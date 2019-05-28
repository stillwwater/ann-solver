#ifndef _ANN_ENTITY
#define _ANN_ENTITY

#include "vector2.h"

namespace ann
{
struct Entity
{
    static const char Empty   = '.';
    static const char Wall    = '#';
    static const char Damaged = 'x';
    static const char Ava     = 'a';
    static const char Steve   = 'b';
    static const char Carl    = 'c';
    static const char _Ava    = '1';
    static const char _Steve  = '2';
    static const char _Carl   = '3';

    char token;
    int layer;
    Vector2 position;

    Entity(char token, Vector2 position, int layer);
    Entity();
    ~Entity();
};

enum MoveState { Move, Cancel, Block, Merge, Destroy, Inherit };
} // namespace ann

#endif
