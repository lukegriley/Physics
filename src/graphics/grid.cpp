#include "grid.h"

Grid::Grid() {}

void Grid::drawGrid(float size, float step) {
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_LINES);
    glColor3f(0.5f, 0.5f, 0.5f);

    for(float i = -size; i <= size; i += step) {
        glVertex3f(i, 0, -size);
        glVertex3f(i, 0, size);

        glVertex3f(-size, 0, i);
        glVertex3f(size, 0, i);
    }

    glEnd();
}
