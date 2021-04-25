#include <iostream>
//#include <stdlib.h>
#include <cmath>

#include "Scene.h"
#include "MatrixStack.h"
#include "Program.h"
#include "SpaceShip.h"
#include "Projectile.h"
#include "Asteroid.h"

using namespace std;

float randFloat(float l, float h)
{
    float r = rand() / (float)RAND_MAX;
    return ((1.0f - r) * l + r * h);
}

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

    //shared_ptr<Asteroid> ast = make_shared<Asteroid>(progShapes, DATA_DIR, glm::vec3(0.0f), glm::vec3(0.0f), 0.0, 4);
    shared_ptr<Asteroid> ast = make_shared<Asteroid>(progShapes, DATA_DIR, glm::vec3(0.0f), glm::vec3(5.0f, 0.0f, -3.0f), 0.0, 4);
    asteroids.push_back(ast);
}

void Scene::update(double t, bool* controlKeys)
{
    // update spaceship
    spaceship->update(t, controlKeys);

    // update projectiles
    while (projectiles.size() > 0 && !projectiles.front()->isAlive()) {
        projectiles.pop_front();
    }

    for (auto p : projectiles) {
        p->update(t);
    }

    // update asteroids
    vector<shared_ptr<Asteroid>> deadAsteroids;
    vector<shared_ptr<Projectile>> deadProjectiles;
    //for (int i = 0; i < asteroids.size(); i++) {
    //    shared_ptr<Asteroid> a = asteroids.;
    for (auto a : asteroids) {
        // check projectile collision
        for (auto p : projectiles) {
            if (a->isCollision(p->getPos())) {
                // delete asteroid and projectile
                deadAsteroids.push_back(a);
                deadProjectiles.push_back(p);
                //projectiles.remove(p);
                cout << "asteroid removed. " << asteroids.size() << " remaining." << endl;
                cout << "projectile removed. " << projectiles.size() << " remaining." << endl;

                // explosion spawns smaller asteroids
                if (a->getSize() > 1) {
                    int numChildren = floor(randFloat(2.0f, 5.0f));///////////////////////////////////////////////  <<<<<<<<<<<<<<<<<<<<<<<----------------------------
                    cout << "Spawning " << numChildren << " child asteroids of size " << a->getSize() / 2 << endl;
                    //int numChildren = floor(rand() * 4) % 4;

                    for (int i = 0; i < numChildren; i++) {
                        float maxV = 10.0f;
                        glm::vec3 newV(randFloat(-maxV, maxV), 0.0f, randFloat(-maxV, maxV));

                        // inherit velocity from parent
                        newV += a->getV();

                        // create asteroid
                        shared_ptr<Asteroid> child = make_shared<Asteroid>(progShapes, DATA_DIR, a->getPos(), newV, t, a->getSize() / 2);
                        asteroids.push_back(child);
                    }
                }

                break;
            }
        }

        for (auto p : deadProjectiles) { ////////////////// don't like doing it this way
            projectiles.remove(p);
        }
    }

    for (auto a : deadAsteroids) { ////////////////// don't like doing it this way fix it
        asteroids.remove(a);
    }

    for (auto a : asteroids) {
        a->update(t);
    }

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
        if (p->inBounds()) {
            p->draw(P, MV, t);
        }
    }
    MV->popMatrix();

    // draw asteroids
    MV->pushMatrix();
    for (shared_ptr<Asteroid> a : asteroids) {
        if (a->inBounds()) {
            a->draw(P, MV, t);
        }
    }
    MV->popMatrix();

    progShapes->unbind();
}
