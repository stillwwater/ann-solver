#include <string>
#include <iostream>
#include "engine.h"
#include "vector2.h"
#include "entity.h"

namespace ann
{
namespace engine
{

Room* create_room(const char* level, int width, int height) {
    auto room = new Room(width, height, 2);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Entity entity;
            entity.position = Vector2(x, y);
            entity.token = level[x + y * width];

            int layer = map_layer(entity.token);
            if (layer < 0) return nullptr;
            entity.layer = layer;

            if (layer >= 1) {
                room->lookup.push_back(Vector2(x, y));
            }
            int flip_layer = std::abs(layer - 1);
            write(room, Entity(Entity::Empty, Vector2(x, y), flip_layer));
            write(room, entity);
        }
    }
    return room;
}

Entity& read(Room* room, Vector2 position, int layer) {
    int z = layer;
    int x = position.x;
    int y = position.y;
    return room->map[z + room->layers * (x + y * room->width)];
}

void write(Room* room, Entity entity) {
    int z = entity.layer;
    int x = entity.position.x;
    int y = entity.position.y;
    room->map[z + room->layers * (x + y * room->width)] = entity;
}

size_t hash(Room* room) {
    int size = room->width * room->height * room->layers;
    int h = 0;
    for (int i = 0; i < size; i++) {
        char token = room->map[i].token;
        h = token + (h << 6) + (h << 16) - h;
    }
    return h;
}

void pprint(Room* room) {
    for (int y = 0; y < room->height; y++) {
        for (int x = 0; x < room->width; x++) {
            Entity entity = read(room, Vector2(x, y), 1);

            if (entity.token == Entity::Empty)
                entity = read(room, Vector2(x, y), 0);

            std::cout << entity.token;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void print_state(const Room* room) {
    switch (room->state) {
        case Room::Ok:
            std::cout << "world: Ok" << std::endl;
            break;
        case Room::Fail:
            std::cout << "world: Failed" << std::endl;
            break;
        case Room::Pass:
            std::cout << "world: Passed" << std::endl;
            break;
    }
    std::cout << "remaining: " << room->lookup.size() << std::endl;
}

// @Todo: Hash instead std::hash instance
char* serialize(Room* room) {
    int size = (room->width * room->height * room->layers) + 1;
    char* buffer = new char[size];

    for (int i = 0; i < size-1; i++) {
        buffer[i] = room->map[i].token;
    }
    buffer[size-1] = '\0';
    return buffer;
}

Room::State exec(Room* room, const char* input, bool show) {
    std::cout << "state: 0" << std::endl;
    pprint(room);

    for (int i = 0; input[i] != 0; i++) {
        move(room, input[i]);
        if (show) {
            std::cout << "state: " << i + 1 << std::endl;
            std::cout << "input: " << input[i] << std::endl;
            pprint(room);
        }
        if (room->state != Room::Ok) {
            return room->state;
        }
    }
    room->state = Room::Fail;
    return Room::Fail;
}

bool move(Room* room, char direction) {
    switch (direction) {
        case 'u':
        case 'U': return move(room, Vector2(0, -1));
        case 'r':
        case 'R': return move(room, Vector2(+1, 0));
        case 'd':
        case 'D': return move(room, Vector2(0, +1));
        case 'l':
        case 'L': return move(room, Vector2(-1, 0));
    }
    return false;
}

bool move(Room* room, Vector2 direction) {
    bool did_move = false;
    auto new_lookup = std::vector<Vector2>();
    auto new_state = std::vector<char>();
    new_state.reserve(room->lookup.size());
    new_lookup.reserve(room->lookup.size());

    for (int i = 0; i < room->lookup.size(); i++) {
        Entity entity = read(room, room->lookup[i], 1);
        Vector2 new_pos = move(room, &entity, direction);

        if (new_pos != entity.position) {
            did_move = true;
        }

        if (new_pos == Vector2(-1, -1)) {
            continue;
        }
        new_lookup.push_back(new_pos);
        new_state.push_back(entity.token);
    }

    // Clear layer 1 state
    for (int i = 0; i < room->lookup.size(); i++) {
        Entity entity;
        entity.layer = 1;
        entity.token = Entity::Empty;
        entity.position = room->lookup[i];
        write(room, entity);
    }

    // Write changes to layer 1
    for (int i = 0; i < new_state.size(); i++) {
        Entity entity;
        entity.layer = 1;
        entity.token = new_state[i];
        entity.position = new_lookup[i];
        write(room, entity);
    }

    if (new_lookup.size() == 0) {
        // Win condition: no crew left in room
        room->state = Room::Pass;
    }

    room->lookup = new_lookup;
    return did_move;
}

/// Entity is always a layer 1 entity
Vector2 move(Room* room, Entity* entity, Vector2 direction) {
    Vector2 new_pos = entity->position + direction;
    Entity tile = read(room, entity->position, 0);
    Entity neighbour = read(room, new_pos, 1);

    if (neighbour.token == Entity::Empty)
        neighbour = read(room, new_pos, 0);

    MoveState state;
    state = leave(tile.token, entity->token);

    if (state == Destroy) {
        // When tiles get destroyed they become blocked
        if (tile.token == Entity::Damaged) {
            tile.token = Entity::Wall;
            write(room, tile);
        }

    }
    state = collide(entity->token, neighbour.token);

    {
        Entity e = neighbour;
        Vector2 pos = new_pos + direction;

        while (state == Inherit) {
            Entity neighbour = read(room, pos, 1);

            if (neighbour.token == Entity::Empty)
                neighbour = read(room, pos, 0);

            state = collide(e.token, neighbour.token);
            e = neighbour;
            pos = pos + direction;
        }
    }

    if (state == Destroy) {
        entity->token = Entity::Empty;
        neighbour.token = Entity::Empty;
        neighbour.layer = 0;
        write(room, neighbour);
        return Vector2(-1, -1);
    }
    if (state == Block) {
        return entity->position;
    }

    if (state == Cancel) {
        room->state = Room::Fail;
        return new_pos;
    }

    if (state == Merge) {
        neighbour = read(room, new_pos + direction, 0);
        // Only merge if neighbour is against a wall
        if (neighbour.token == Entity::Wall) {
            return Vector2(-1, -1);
        }
    }

    return new_pos;
}

/// Left is always a layer 1 entity
MoveState collide(char left, char right) {
    switch (right) {
        case Entity::Wall: return Block;

        case Entity::Ava:
        case Entity::Steve:
        case Entity::Carl:
            return left == right ? Merge : Inherit;

        case Entity::_Ava: return left == Entity::Ava ? Destroy : Cancel;
        case Entity::_Carl: return left == Entity::Carl ? Destroy : Cancel;
        case Entity::_Steve: return left == Entity::Steve ? Destroy : Cancel;
    }
    return Move;
}

/// Right is always a layer 1 entity
MoveState leave(char left, char right) {
    return left == Entity::Damaged && right != Entity::Ava ? Destroy : Move;
}

int map_layer(char token) {
    switch (token) {
        case Entity::Wall:
        case Entity::Empty:
        case Entity::Damaged:
        case Entity::_Steve:
        case Entity::_Ava:
        case Entity::_Carl:
            return 0;
        case Entity::Ava:
        case Entity::Steve:
        case Entity::Carl:
            return 1;

        default: return -1;
    }
}

bool is_crew(char token) {
    switch (token) {
        case Entity::Steve:
        case Entity::Ava:
        case Entity::Carl:
            return true;
    }
    return false;
}

bool is_exit(char token) {
    switch (token) {
        case Entity::_Steve:
        case Entity::_Ava:
        case Entity::_Carl:
            return true;
    }
    return false;
}

} // namespace engine
} // namespace ann
