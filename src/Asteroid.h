#pragma once
#ifndef ASTEROID_H
#define ASTEROID_H

#include <string>

#include <glm/glm.hpp>

#include "Entity.h"

class MatrixStack;
class Program;
class Shape;

class Asteroid : public Entity
{
public:
    Asteroid() {}
    Asteroid(std::shared_ptr<Program> prog_, std::string& DATA_DIR_, glm::vec3 pos_, glm::vec3 v_, double t_old_, int size_);
    virtual ~Asteroid();

    void update(double t);

    //bool isCollision(glm::vec3 p);
    void explode();

    glm::vec3 getPos();
    glm::vec3 getV();
    int getSize();

    void draw(std::shared_ptr<MatrixStack> P, std::shared_ptr<MatrixStack> MV, double t);

private:
    int size;
    glm::vec3 axis;
    glm::vec3 color;

    std::shared_ptr<Shape> shape;

    void generateShape();
};

#endif
