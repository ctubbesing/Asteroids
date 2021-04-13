#pragma once
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <string>

#include <glm/glm.hpp>

#include "Entity.h"

class MatrixStack;
class Program;
class Shape;

class Projectile : public Entity
{
public:
    Projectile() {}
    Projectile(std::shared_ptr<Program> prog_, std::string& DATA_DIR_, glm::vec3 pos_, float dir_, double t);
    virtual ~Projectile();

    void update(double t);
    bool isAlive();

    void draw(std::shared_ptr<MatrixStack> P, std::shared_ptr<MatrixStack> MV, double t);

private:
    float speed;
    float age;
    float lifespan;

    std::shared_ptr<Shape> shape;
};

#endif
