#include "rigidbody.h"



RigidBody::RigidBody(PrimitiveType primType, Matrix4d modelMatrix, double mass)
    : Actor(PhysicsType::RIGID_BODY,primType,modelMatrix,mass) {
    this->angularVelocity = Vector3d(0.0, 0.0, 0.0);
    this->linearVelocity = Vector3d(0.0, 0.0, 0.0);
    this->inertiaTensor = Matrix3d::Identity();
}

void RigidBody::update(double delta) {
    //store initial state
    Vector3d oldPos = this->position;
    Matrix3d oldOrient = this->orientation;
    Vector3d oldLinVel = this->linearVelocity;
    Vector3d oldAngVel = this->angularVelocity;

    //compute derivatives at the current state
    Matrix<double, 3, 4> k1 = eulerDerivEval();

    //compute state at the midpoint using k1
    this->position = oldPos + 0.5 * delta * k1.col(0);
    this->orientation = oldOrient + 0.5 * delta * RigidBody::skewSymmetric(k1.col(1)) * oldOrient;
    this->linearVelocity = oldLinVel + 0.5 * delta * k1.col(2);
    this->angularVelocity = oldAngVel + 0.5 * delta * k1.col(3);

    Matrix<double, 3, 4> k2 = eulerDerivEval();

    //update state using derivatives at the midpoint
    this->position = oldPos + delta * k2.col(0);
    Vector3d d = k2.col(1);
    Matrix3d skew = RigidBody::skewSymmetric(d);
    this->orientation = oldOrient + delta * skew * oldOrient;
    this->linearVelocity = oldLinVel + delta * k2.col(2);
    this->angularVelocity = oldAngVel + delta * k2.col(3);

    //reorthogonalize orientation matrix
    Eigen::JacobiSVD<Matrix3d> svd(this->orientation, Eigen::ComputeFullU | Eigen::ComputeFullV);
    this->orientation = svd.matrixU() * svd.matrixV().transpose();

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            this->modelMatrix.coeffRef(i,j) = this->orientation.coeffRef(i,j);
        }
    }

    for (int i = 0; i < 3; ++i) {
        this->modelMatrix.coeffRef(i,3) = this->position[i];
    }
    this->forces.clear();

    Affine3f aff;
    aff.matrix() = this->modelMatrix.cast<float>();
    shape.setModelMatrix(aff);
}

Matrix3d RigidBody::skewSymmetric(Vector3d omega) {
    Matrix3d res;
    res << 0.0,-omega[2],omega[1],
        omega[2], 0.0,-omega[0],
        -omega[1],omega[0],0.;
    return res;
}


void RigidBody::applyForce(Vector3d force, Vector3d point) {
    Matrix<double, 2, 3> insert;
    insert.row(0) = force;
    insert.row(1) = point;
    forces.push_back(insert);
}

Matrix<double, 3, 4> RigidBody::eulerDerivEval() {
    Matrix<double, 3, 4> res = Matrix<double, 3, 4>::Zero();

    //apply any forces

    applyForce(Vector3d(0.0, -2.0, 0.0), this->position);//gravity

    //calculate total torque, forces
    Vector3d total_torque = Vector3d::Zero();
    Vector3d total_force = Vector3d::Zero();
    for (Matrix<double, 2, 3>& force : this->forces) {
        Vector3d f = force.row(0);
        Vector3d p = force.row(1);
        total_force += f;
        total_torque += f.cross(p - this->position);
    }

    res.col(0) = this->linearVelocity; //linear velocity
    res.col(1) = this->angularVelocity; //angular velocity
    res.col(2) = total_force / this->mass; //linear acceleration
    res.col(3) = this->inertiaTensor.inverse() * total_torque; //angular acceleration

    return res;
}

Vector3d RigidBody::checkCollision(Actor *a) {

}
