#pragma once
#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <string>

#include <glm/glm.hpp>

#include "Entity.h"

class MatrixStack;
class Program;
class Shape;
class Scene;

class SpaceShip : public Entity
{
public:
    SpaceShip() {}
    SpaceShip(std::shared_ptr<Scene> _scene, std::shared_ptr<Program> prog_, std::string& DATA_DIR_, double t);
    virtual ~SpaceShip();

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
    float drag; // speed lost per second

    bool thrustersOn;
    bool triggerPressed;
    float cooldownDuration;
    float timeLeft;

    std::shared_ptr<Shape> body;
    std::shared_ptr<Shape> fin;

    void fire();
};

#endif
