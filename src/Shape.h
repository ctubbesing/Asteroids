#pragma once
#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <vector>
//#include <memory>

class Program;

/**
 * A shape defined by a list of triangles
 * - posBuf should be of length 3*ntris
 * - norBuf should be of length 3*ntris (if normals are available)
 * - texBuf should be of length 2*ntris (if texture coords are available)
 * posBufID, norBufID, and texBufID are OpenGL buffer identifiers.
 */
class Shape
{
public:
    Shape();
    virtual ~Shape();
    void loadObj(const std::string &filename, std::vector<float> &pos, std::vector<float> &nor, std::vector<float> &tex, bool loadNor = true, bool loadTex = true);
    void loadMesh(const std::string &meshName);
    void refreshNormals();
    void setProgram(std::shared_ptr<Program> &prog) { this->prog = prog; }
    void init();
    void draw() const;

    std::vector<float> getPosBuf() { return posBuf; }
    void scale(float c);

protected:
    std::vector<float> posBuf;
    std::vector<float> norBuf;
    std::vector<float> texBuf;
    unsigned posBufID;
    unsigned norBufID;
    unsigned texBufID;

    std::shared_ptr<Program> prog;
};

#endif
#pragma once
