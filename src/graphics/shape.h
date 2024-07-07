#ifndef SHAPE_H
#define SHAPE_H

#include <GL/glew.h>
#include <vector>

#include <Eigen/Dense>

class Shader;

class Shape
{
public:
    Shape();

    void init(const std::vector<Eigen::Vector3d> &vertices, const std::vector<Eigen::Vector3d> &normals, const std::vector<Eigen::Vector3i> &triangles);
    void init(const std::vector<Eigen::Vector3d> &vertices, const std::vector<Eigen::Vector3i> &triangles);
    void init(const std::vector<Eigen::Vector3d> &vertices, const std::vector<Eigen::Vector3i> &triangles, const std::vector<Eigen::Vector4i> &tetIndices);

    void setVertices(const std::vector<Eigen::Vector3d> &vertices, const std::vector<Eigen::Vector3d> &normals);
    void setVertices(const std::vector<Eigen::Vector3d> &vertices);

    void setModelMatrix(const Eigen::Affine3f &model);
    void setColor(Eigen::Vector3f rgb) {
        m_red = rgb[0];
        m_green = rgb[1];
        m_blue = rgb[2];
    }

    void toggleWireframe();

    void draw(Shader *shader);


private:
    GLuint m_surfaceVao;
    GLuint m_tetVao;
    GLuint m_surfaceVbo;
    GLuint m_tetVbo;
    GLuint m_surfaceIbo;
    GLuint m_tetIbo;
    Eigen::Vector3f rgb;

    unsigned int m_numSurfaceVertices;
    unsigned int m_numTetVertices;
    unsigned int m_verticesSize;
    float m_red;
    float m_blue;
    float m_green;
    float m_alpha;

    std::vector<Eigen::Vector3i> m_faces;
    std::vector<Eigen::Vector3d> m_verts;

    Eigen::Matrix4f m_modelMatrix;

    bool m_wireframe;
};

#endif // SHAPE_H
