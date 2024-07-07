#include "system.h"
#include <iostream>
#include <unordered_set>

System::System() {

}
using namespace std;


bool System::checkCollisions() {
    if(m_actors.size()<2) return false;
    return Collision::intersects(m_actors[0]->getOBB(),m_actors[1]->getOBB());
}






