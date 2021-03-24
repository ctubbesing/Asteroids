#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>

#include <glm/glm.hpp>

class MatrixStack;
class Program;
//class Entity;

class Scene : public std::enable_shared_from_this<Scene>
{
public:
    Scene(std::string _DATA_DIR = "");
    virtual ~Scene();

    void init();
    
    void setProgSimple(std::shared_ptr<Program> prog) { progSimple = prog; }
    void setProgShapes(std::shared_ptr<Program> prog) { progShapes = prog; }

    void draw(std::shared_ptr<MatrixStack> P, std::shared_ptr<MatrixStack> MV, double t);

private:    
    std::shared_ptr<Program> progSimple;
    std::shared_ptr<Program> progShapes;

    std::string DATA_DIR;
};

#endif
#pragma once
