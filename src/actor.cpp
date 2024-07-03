#include "actor.h"
#include <unordered_set>

Actor::Actor(PhysicsType physType, PrimitiveType primType, Matrix4d modelMatrix, double mass)
    : modelMatrix(modelMatrix), physType(physType), primType(primType), mass(mass) {
    this->position = (modelMatrix * Vector4d(0.0, 0.0, 0.0, 1.0)).head<3>();
    this->orientation = Matrix3d::Identity();
}

void Actor::initShape() {
    string mesh_path;
    switch(primType) {
    case CUBE:
        mesh_path = "./example-meshes/cube.mesh";
        break;
    case SPHERE:
        mesh_path = "./example-meshes/sphere.mesh";
        break;
    default:
        mesh_path = "./example-meshes/single-tet.mesh";
        break;
    }
    std::vector<Vector3d> vertices;
    std::vector<Vector4i> tets;
    if (MeshLoader::loadTetMesh(mesh_path, vertices, tets)) {
        std::vector<Vector3i> faces;
        for(Vector4i t : tets) {
            std::vector<Vector3i> tet_faces({Vector3i(t[0],t[2],t[1]),
                                             Vector3i(t[0],t[1],t[3]),Vector3i(t[1],t[2],t[3]),Vector3i(t[0],t[3],t[2])});
            ensureUnique(faces,tet_faces);
        }

        shape.init(vertices, faces,tets);
        Affine3f aff;
        aff.matrix() = this->modelMatrix.cast<float>();
        shape.setModelMatrix(aff);
    }
}

void Actor::draw(Shader* shader) {
    shape.draw(shader);
}
