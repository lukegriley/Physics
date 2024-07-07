#include "Types.h"
#ifndef SYSTEM_H
#define SYSTEM_H
using namespace Eigen;
using namespace std;
#include "collider.h"
#include "graphics/camera.h"
#include "actor.h"


class System
{
public:
    System();
    void loadActor(Actor *a) {
        m_actors.push_back(a);
        a->setID(count);
        count++;
    }

    bool checkCollisions();
    static Vector3d collides(Actor *a, Actor *b);


private:
    vector<Actor *> m_actors;//TODO: upgrade to BVH
    int count = 0;

};

#endif // SYSTEM_H
