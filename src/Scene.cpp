#include <iostream>

#include "Scene.h"
#include "MatrixStack.h"
#include "Program.h"
#include "SpaceShip.h"
#include "Projectile.h"

using namespace std;

Scene::Scene(string _DATA_DIR) :
    DATA_DIR(_DATA_DIR)
{

}

Scene::~Scene()
{

}

void Scene::init()
{
    // initialize spaceship
    spaceship = make_shared<SpaceShip>(shared_from_this(), progShapes, DATA_DIR, 0.0);
}

void Scene::update(double t, bool* controlKeys)
{
    // update spaceship
    spaceship->update(t, controlKeys);

    // update projectiles
    while (projectiles.size() > 0 && !projectiles.front()->isAlive()) {
        projectiles.pop_front();
        cout << "pop projectile" << endl;
    }

    for (auto p : projectiles) {
        p->update(t);
    }

    // update asteroids

    // update particles?
}

void Scene::draw(std::shared_ptr<MatrixStack> P, std::shared_ptr<MatrixStack> MV, double t)
{
    progShapes->bind();

    // draw spaceship
    MV->pushMatrix();
    spaceship->draw(P, MV, t);
    MV->popMatrix();

    // draw projectiles
    MV->pushMatrix();
    for (shared_ptr<Projectile> p : projectiles) {
        p->draw(P, MV, t);
    }
    MV->popMatrix();

    progShapes->unbind();
}
