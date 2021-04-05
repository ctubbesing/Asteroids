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
    SpaceShip() {}
    SpaceShip(std::shared_ptr<Program> progShapes, std::string DATA_DIR);
    virtual ~SpaceShip();

    //void init(std::shared_ptr<Program> progShapes, std::string DATA_DIR);
    void update(double t, bool* controlKeys);

    void draw(std::shared_ptr<MatrixStack> P, std::shared_ptr<MatrixStack> MV, double t);

    enum controlKeyVal
    {
        KEY_FORWARDS,
        KEY_LEFT,
        KEY_RIGHT,
        KEY_SHOOT
    };

private:
    float vMax;
    float a;
    float drag;     // speed lost per second

    //glm::vec3 pos;
    //float dir;
    //glm::vec3 v;
    //float rotSpeed; // seconds per rotation
    //double t_old;

    bool thrustersOn;
    bool triggerPressed;

    void fire();

    std::shared_ptr<Shape> body;
    std::shared_ptr<Shape> fin;
};

#endif
