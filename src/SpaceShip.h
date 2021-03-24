#pragma once
#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <memory>
#include <string>

#include <glm/glm.hpp>

#include "Entity.h"

class MatrixStack;
class Program;
class Shape;

class SpaceShip : public Entity
{
public:
    SpaceShip();
    virtual ~SpaceShip();

    void init(std::shared_ptr<Program> progShapes, std::string DATA_DIR);

    void draw(std::shared_ptr<MatrixStack> P, std::shared_ptr<MatrixStack> MV, double t);

private:
    std::shared_ptr<Shape> body;
    std::shared_ptr<Shape> fin;
};

#endif
#pragma once
