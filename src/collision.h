#ifndef COLLISION_H
#define COLLISION_H

#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

struct OBB {
    Vector3d point;
    Matrix3d axes;
    Vector3d extents;
};

class Collision
{
public:
    Collision();
    static bool intersects(const OBB& obb1, const OBB& obb2) {
        vector<Vector3d> axes;
        axes.push_back(obb1.axes.col(0));
        axes.push_back(obb1.axes.col(1));
        axes.push_back(obb1.axes.col(2));
        axes.push_back(obb2.axes.col(0));
        axes.push_back(obb2.axes.col(1));
        axes.push_back(obb2.axes.col(2));
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                axes.push_back(obb1.axes.col(i).cross(obb2.axes.col(j)));
            }
        }
        for (const auto& axis : axes) {
            if (axis.squaredNorm() < numeric_limits<double>::epsilon()) continue;
            if (!overlapsOnAxis(obb1,obb2,axis)) return false;
        }
        return true;
    }

    /**
     * @brief projectOBB projects OBB onto an axis
     * @param obb
     * @param axis that is projected on
     * @return Vector2d extent of the projection interval on the axis: (min,max)
     */
    static Vector2d projectOBB(const OBB& obb, Vector3d axis) {
        double center_projected = axis.dot(obb.point);
        double extent_projected = abs(axis.dot(obb.axes.col(0))) * obb.extents[0] +
                                  abs(axis.dot(obb.axes.col(1))) * obb.extents[1] +
                                  abs(axis.dot(obb.axes.col(2))) * obb.extents[2];
        return Vector2d(center_projected-extent_projected,center_projected+extent_projected);
    }


    static bool overlapsOnAxis(const OBB& obb1, const OBB& obb2, Vector3d axis) {
        Vector2d proj1 = projectOBB(obb1,axis);
        Vector2d proj2 = projectOBB(obb2,axis);
        return (proj1[0] <= proj2[1] && proj2[0] <= proj1[1]);
    }



};

#endif // COLLISION_H
