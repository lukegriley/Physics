#include "simulation.h"
#include "graphics/meshloader.h"
#include <unordered_set>

#include <iostream>

using namespace Eigen;
using namespace std;

Simulation::Simulation() : m_actor(PrimitiveType::CUBE,Affine3d(Translation3d(0.,2.,0.)).matrix(),10.0),
    m_floor(PrimitiveType::CUBE,Static::groundMatrix()){}

void Simulation::init()
{

    m_system.loadActor(&m_actor);
    m_system.loadActor(&m_floor);

    m_actor.initShape();
    m_floor.initShape();
    m_floor.setColor(Vector3f(1.f,1.f,1.f));
    m_actor.applyForce(Vector3d(0.0, 0.0, 100.0),Vector3d(0.0, 0.1, 0.0));
    m_actor.applyForce(Vector3d(0.0, 200.0, 0.0),Vector3d(0.2, 0.0, 0.0));
}

void Simulation::update(double seconds)
{
    if(m_running) {
        m_actor.update(seconds);

        if(m_system.checkCollisions()) {
            cout <<"COLLIDED"<<endl;
            toggleRunning();
        }
        if(once) {
            m_running = false;
        }
    }
}

void Simulation::draw(Shader *shader)
{
    Grid::drawGrid(100.f,1.f);
    m_actor.draw(shader);
    m_floor.draw(shader);

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
    // m_ground.init(groundVerts, groundFaces);

}

void Simulation::toggleRunning() {
    if(!m_running) {
        m_running = true;
        once = false;
    } else {
        m_running = false;
    }
}
