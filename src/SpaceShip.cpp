#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SpaceShip.h"
#include "MatrixStack.h"
#include "Program.h"
#include "Shape.h"
#include "Scene.h"
#include "Projectile.h"

#define CLAMP(X, MAX, MIN) (X > MAX ? MAX : (X < MIN ? MIN : X))

using namespace std;

float randFloat(float l, float h)
{
    float r = rand() / (float)RAND_MAX;
    return (1.0f - r) * l + r * h;
}

SpaceShip::SpaceShip(shared_ptr<Scene> _scene, shared_ptr<Program> prog_, string& DATA_DIR_, double t) :
    Entity(prog_, DATA_DIR_, glm::vec3(0.0f), 0.0f, glm::vec3(0.0f), 2*M_PI / 2.0f, t), // rotSpeed = 2*pi / secsPerRotation
    vMax(1000.0f),
    a(50.0f),
    drag(1.0f),
    thrustersOn(false),
    triggerPressed(false),
    cooldownDuration(0.5f),
    timeLeft(0.0f)
{
    setScene(_scene);

    // initialize body & fins
    body = make_shared<Shape>();
    body->loadMesh(DATA_DIR + "spaceship_body.obj");
    body->refreshNormals();
    body->setProgram(prog);
    body->scale(1.0f);
    body->init();

    fin = make_shared<Shape>();
    fin->loadMesh(DATA_DIR + "spaceship_fin.obj");
    fin->refreshNormals();
    fin->setProgram(prog);
    fin->scale(1.0f);
    fin->init();
}

SpaceShip::~SpaceShip()
{

}

void SpaceShip::update(double t, bool* controlKeys)
{
    float dt = t - t_old;
    t_old = t;

    // fire projectile
    if (controlKeys[KEY_SHOOT]) {
        timeLeft -= dt;
        if (timeLeft < 0.0f) {
            fire();
            timeLeft = cooldownDuration;
        }
    }
    else {
        timeLeft = 0.0f;
    }

    // update thrusters
    thrustersOn = controlKeys[KEY_FORWARDS];

    // update orientation
    if (controlKeys[KEY_LEFT]) {
        dir += rotSpeed * dt;
    }
    if (controlKeys[KEY_RIGHT]) {
        dir -= rotSpeed * dt;
    }

    // update velocity
    float speedSq = v.x * v.x + v.z * v.z;
    float minSpeed = 0.5f;

    // apply drag
    if (speedSq < minSpeed) {
        v.x = 0.0f;
        v.z = 0.0f;
    }
    else {
        v -= dt * drag * v;
    }

    // apply thrust
    if (controlKeys[KEY_FORWARDS] && speedSq < vMax) {
        v.x += sin(dir) * a * dt;
        v.z += cos(dir) * a * dt;
    }

    // update position
    updatePos(dt);
}

void SpaceShip::fire()
{
    shared_ptr<Projectile> proj = make_shared<Projectile>(prog, DATA_DIR, pos, dir, t_old);

    scene->addProjectile(proj);
}

void SpaceShip::draw(std::shared_ptr<MatrixStack> P, std::shared_ptr<MatrixStack> MV, double t)
{
    glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P->topMatrix()));

    MV->pushMatrix();

    MV->translate(pos);
    MV->rotate(dir, 0.0f, 1.0f, 0.0f);
    MV->translate(0.0f, 0.0f, -2.0f);

    MV->pushMatrix();
    // draw body
    glUniform3f(prog->getUniform("kd"), 0.2f, 0.5f, 0.6f);
    glUniform3f(prog->getUniform("ka"), 0.02f, 0.05f, 0.06f);
    glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
    body->draw();

    //draw fins
    glUniform3f(prog->getUniform("kd"), 0.1f, 0.3f, 0.4f);
    glUniform3f(prog->getUniform("ka"), 0.01f, 0.03f, 0.04f);
    fin->draw(); // left fin

    MV->pushMatrix();
    MV->rotate(M_PI, 0.0f, 0.0f, 1.0f);
    glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
    fin->draw(); // right fin (mirror of left)
    MV->popMatrix();

    MV->popMatrix();

    // draw thrusters (just a recolor of the same shape)
    if (thrustersOn) {
        MV->pushMatrix();

        MV->rotate(M_PI, glm::vec3(0.0f, 1.0f, 0.0f));
        MV->translate(0.0f, 0.0f, -1.5f);
        MV->scale(0.5f);

        glUniform3f(prog->getUniform("kd"), 0.8f, randFloat(0.0f, 0.8f), 0.0f);
        glUniform3f(prog->getUniform("ka"), 0.08f, randFloat(0.0f, 0.08f), 0.0f);
        glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
        body->draw();

        glUniform3f(prog->getUniform("kd"), 0.8f, randFloat(0.0f, 0.8f), 0.0f);
        glUniform3f(prog->getUniform("ka"), 0.08f, randFloat(0.0f, 0.08f), 0.0f);
        glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
        fin->draw();

        MV->rotate(M_PI, 0.0f, 0.0f, 1.0f);
        glUniform3f(prog->getUniform("kd"), 0.8f, randFloat(0.0f, 0.8f), 0.0f);
        glUniform3f(prog->getUniform("ka"), 0.08f, randFloat(0.0f, 0.08f), 0.0f);
        glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
        fin->draw();

        MV->popMatrix();
    }
}
