#ifndef STATIC_H
#define STATIC_H
#include "actor.h"

class Static : Actor
{
public:
    Static(PrimitiveType primType, Vector3d position);
    Static(PrimitiveType primType, Matrix4d modelMatrix);
    void update(double delta) override {

    }
    Matrix<double, 3, 4>  eulerDerivEval();
    void applyForce(Vector3d force,Vector3d point) override {

    }

private:
    Matrix4d posToMatrix(Vector3d pos) {
        modelMatrix = Matrix4d::Identity();
        modelMatrix.col(3).head<3>() = pos;
        return modelMatrix;
    }
};

#endif // STATIC_H
