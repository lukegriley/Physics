#include "static.h"

Static::Static(PrimitiveType primType, Matrix4d modelMatrix) : Actor(PhysicsType::STATIC,primType,modelMatrix,0.0) {

}

Static::Static(PrimitiveType primType, Vector3d position) : Actor(PhysicsType::STATIC,primType,posToMatrix(position),0.0) {

}

