#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <memory>

#include <glm/glm.hpp>

class MatrixStack;

class Entity
{
public:
    Entity();
    virtual ~Entity();

    void init();

    void kill();

    void draw(std::shared_ptr<MatrixStack> P, std::shared_ptr<MatrixStack> MV, double t);

protected:
};

#endif
#pragma once