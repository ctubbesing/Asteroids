#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <list>
#include <memory>

#include <glm/glm.hpp>

class MatrixStack;
class Program;
class SpaceShip;
class Projectile;

class Scene : public std::enable_shared_from_this<Scene>
{
public:
    Scene(std::string _DATA_DIR = "../data/");
    virtual ~Scene();

    void init();
    void update(double t, bool* controlKeys);
    
    void setProgSimple(std::shared_ptr<Program> prog) { progSimple = prog; }
    void setProgShapes(std::shared_ptr<Program> prog) { progShapes = prog; }

    void addProjectile(std::shared_ptr<Projectile> p) { projectiles.push_back(p); }

    void draw(std::shared_ptr<MatrixStack> P, std::shared_ptr<MatrixStack> MV, double t);

private:
    std::shared_ptr<SpaceShip> spaceship;
    std::list<std::shared_ptr<Projectile>> projectiles;
    // std::vector<std::shared_ptr<Asteroid>> asteroids;

    std::shared_ptr<Program> progSimple;
    std::shared_ptr<Program> progShapes;

    std::string DATA_DIR;
};

#endif
