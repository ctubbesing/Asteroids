#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <string>

#include <glm/glm.hpp>

#ifndef M_PI
#define M_PI (float)3.14159265358979323846
#endif

class MatrixStack;
class Program;
class Scene;

class Entity
{
public:
    Entity() {}
    Entity(std::shared_ptr<Program> prog_);
    Entity(std::shared_ptr<Program> prog_, std::string& _DATA_DIR, glm::vec3 pos_, float dir_, glm::vec3 v_, float rotSpeed_, double t_old_);
    virtual ~Entity();

    void setScene(std::shared_ptr<Scene> scene_) { scene = scene_; }

    bool inBounds();
    bool isCollision(glm::vec3 p, float otherR = 0.0f);

    virtual void draw(std::shared_ptr<MatrixStack> P, std::shared_ptr<MatrixStack> MV, double t);

protected:
    glm::vec3 pos;
    float dir;
    glm::vec3 v;
    float rotSpeed; // seconds per rotation
    float r;

    double t_old;

    bool doWrap; // wrap around edges

    std::shared_ptr<Scene> scene;
    std::shared_ptr<Program> prog;
    std::string DATA_DIR;

    void updatePos(float dt);
    float randFloat(float l = 0.0f, float h = 1.0f);
};

#endif
