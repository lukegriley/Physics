#ifndef ACTOR_H
#define ACTOR_H
#include "graphics/shape.h"
#include "graphics/meshloader.h"
#include "collision.h"
#include <Eigen/Dense>
enum PhysicsType {STATIC,RIGID_BODY};

enum PrimitiveType {CUBE,SPHERE,CONE,CYLINDER,MESH};

using namespace Eigen;
using namespace std;



class Actor
{
public:
    Actor(PhysicsType physType, PrimitiveType primType,Matrix4d modelMatrix, double mass);
    virtual void update(double delta) {};
    virtual void applyForce(Vector3d force,Vector3d point) {};
    Matrix4d getModelMatrix() {return this->modelMatrix;}
    void draw(Shader* shader);
    void initShape();
    void setID(int id) {
        this->id = id;
    }
    void setColor(Vector3f rgb) {
        shape.setColor(rgb);
    }
    OBB getOBB();


    virtual Vector3d checkCollision(Actor *a) {return Vector3d::Zero();};

    PhysicsType physType;
    PrimitiveType primType;
    Matrix4d modelMatrix;
    Vector3d position;
    Matrix3d orientation;
    double mass;
    int id;
protected:

    Shape shape;

private:

    bool equivalentFace(Vector3i f1, Vector3i f2) {
        std::vector<int> indices1 = {f1[0],f1[1],f1[2]};
        std::vector<int> indices2 = {f2[0],f2[1],f2[2]};

        std::sort(indices1.begin(), indices1.end());
        std::sort(indices2.begin(), indices2.end());

        return indices1 == indices2;
    }

    struct Vector3iHash {
        size_t operator()(const Vector3i& v) const {
            size_t hashValue = std::hash<int>()(v[0]);
            hashValue ^= std::hash<int>()(v[1]) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
            hashValue ^= std::hash<int>()(v[2]) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
            return hashValue;
        }
    };

    void ensureUnique(std::vector<Vector3i>& faces, std::vector<Vector3i>& tet_faces) {
        for(Vector3i& tet_face : tet_faces) {
            bool pushback = true;
            std::vector<Vector3i>::iterator it = faces.begin();
            while (it != faces.end()) {
                if (equivalentFace(tet_face,*it)) {
                    faces.erase(it);
                    pushback = false;
                } else {
                    it++;
                }
            }
            if (pushback) {
                faces.push_back(tet_face);
            }
        }
    }

    Vector3i sortedFace(Vector3i f1) {
        std::vector<int> indices1 = {f1[0],f1[1],f1[2]};

        std::sort(indices1.begin(), indices1.end());

        Vector3i res(indices1[0],indices1[1],indices1[2]);
        return res;
    }

};

#endif // ACTOR_H
