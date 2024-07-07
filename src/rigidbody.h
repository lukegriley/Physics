#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#include "actor.h"

class RigidBody : public Actor
{
public:
    RigidBody(PrimitiveType primType, Matrix4d modelMatrix, double mass);

    void update(double delta) override;
    Matrix<double, 3, 4>  eulerDerivEval();
    void applyForce(Vector3d force,Vector3d point) override;
    Vector3d checkCollision(Actor *a) override;
    static Matrix3d skewSymmetric(Vector3d omega);

private:

    vector<Matrix<double,2,3>> forces;
    Vector3d linearVelocity;
    Vector3d angularVelocity;
    Matrix3d inertiaTensor;
};


#endif // RIGIDBODY_H
