#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <memory>

#include <glm/glm.hpp>

#ifndef M_PI
#define M_PI (float)3.14159265358979323846
#endif

class MatrixStack;
class Program;

class Entity
{
public:
    Entity() {}
    Entity(std::shared_ptr<Program> prog_);
    Entity(std::shared_ptr<Program> prog_, glm::vec3 pos_, float dir_, glm::vec3 v_, float rotSpeed_); /////////////////////maybe do t_old too idk
    virtual ~Entity();

    void init();

    void kill();

    void draw(std::shared_ptr<MatrixStack> P, std::shared_ptr<MatrixStack> MV, double t);

protected:
    glm::vec3 pos;
    float dir;
    glm::vec3 v;
    float rotSpeed; // seconds per rotation

    double t_old;

    std::shared_ptr<Program> prog;
};

#endif
