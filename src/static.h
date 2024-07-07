#ifndef STATIC_H
#define STATIC_H
#include "actor.h"

class Static : public Actor
{
public:
    Static(PrimitiveType primType, Vector3d position);
    Static(PrimitiveType primType, Matrix4d modelMatrix);
    void update(double delta) override {

    }
    Matrix<double, 3, 4>  eulerDerivEval();
    void applyForce(Vector3d force,Vector3d point) override {

    }

    //TEMP
    static Matrix4d groundMatrix() {
        Matrix4d res = Matrix4d::Identity();
        res(0,0) = 10.;
        res(1,1) = .1;
        res(2,2) = 10.;
        res.col(3)= Vector4d(0.,0.,0.,1.0);
        return res;

    }

private:
    Matrix4d posToMatrix(Vector3d pos) {
        modelMatrix = Matrix4d::Identity();
        modelMatrix.col(3).head<3>() = pos;
        return modelMatrix;
    }
};

#endif // STATIC_H
