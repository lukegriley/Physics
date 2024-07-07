#ifndef GRID_H
#define GRID_H
#include <GL/glew.h>

class Grid
{
public:
    Grid();
    static void drawGrid(float size, float step);
};

#endif // GRID_H
