#pragma once

#include "graphics/shape.h"
#include "system.h"
#include "Types.h"
#include "graphics/camera.h"
#include "collider.h"
#include "rigidbody.h"


class Shader;

class Simulation
{
public:
    Simulation();

    void init();

    void update(double seconds);

    void draw(Shader *shader);

    void toggleWire();

    void loadCamera(Camera *_cam) {
        cam = _cam;
    }

    void toggleRunning();
    void forwardOnce() {
        if(!m_running) {
            once = true;
            m_running = true;
        }
    }


    void goToBreakpoint() {
        int x =0;
    }
    System m_system;
    RigidBody m_actor;

private:
    Shape m_shape;



    void initSphereCollider();


    bool once = false;
    bool breakpoint = false;
    Camera *cam;

    Shape m_ground;
    Shape m_sphere;
    void initGround();
    bool m_running = false;
    std::vector<Vector3d> m_verts;




};
