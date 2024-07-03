#include "simulation.h"
#include "graphics/meshloader.h"
#include <unordered_set>

#include <iostream>

using namespace Eigen;
using namespace std;

Simulation::Simulation() : m_actor(PrimitiveType::CUBE,Matrix4d::Identity(),10.0) {}

void Simulation::init()
{

    m_actor.initShape();
    initGround();
    m_actor.applyForce(Vector3d(0.0, 1000.0, 0.0),Vector3d(-.4, 0.0, 0.0));
}

void Simulation::update(double seconds)
{
    if(m_running) {
        m_actor.update(seconds);
        if(once) {
            m_running = false;
        }
    }

}

void Simulation::draw(Shader *shader)
{
    m_actor.draw(shader);
    m_ground.draw(shader);
}

void Simulation::toggleWire()
{
    m_shape.toggleWireframe();
}

void Simulation::initGround()
{
    std::vector<Vector3d> groundVerts;
    std::vector<Vector3i> groundFaces;
    groundVerts.emplace_back(-5, 0, -5);
    groundVerts.emplace_back(-5, 0, 5);
    groundVerts.emplace_back(5, 0, 5);
    groundVerts.emplace_back(5, 0, -5);
    groundFaces.emplace_back(0, 1, 2);
    groundFaces.emplace_back(0, 2, 3);
    m_ground.init(groundVerts, groundFaces);

}

void Simulation::toggleRunning() {
    if(!m_running) {
        m_running = true;
        once = false;
    } else {
        m_running = false;
    }
}
