#include "Room.h"

Room::Room()
    : Cube(Surface(Color(255, 0, 0), 1.0), Vector3D(600, 600, 500), Vector3D(-300, -300, -200)) {
    invert_normals();
    Color colors[6] = {
        Color(100, 100, 140),
        Color(100, 100, 140),
        Color(50, 50, 70),
        Color(50, 50, 70),
        Color(200, 200, 240),
        Color(25, 25, 45)
    };
    for (int i = 0; i < surface().size(); i += 2) {
        surface()[i]->color = colors[i / 2];
        surface()[i + 1]->color = colors[i / 2];
    }
}
