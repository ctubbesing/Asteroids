#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SpaceShip.h"
#include "Entity.h"
#include "Program.h"
#include "Shape.h"
#include "MatrixStack.h"

#ifndef M_PI
#define M_PI (float)3.14159265358979323846
#endif

#define CLAMP(X, MAX, MIN) (X > MAX ? MAX : (X < MIN ? MIN : X))

using namespace std;

SpaceShip::SpaceShip() :
    pos(-3.0f, 0.0f, 0.0f),
    //pos(0.0f),
    dir(0.0f)
{

}

SpaceShip::SpaceShip(shared_ptr<Program> progShapes, string DATA_DIR) :
    Entity(progShapes),
    pos(0.0f, 0.0f, 0.0f),
    v(0.0f, 0.0f, 0.0f),
    vMax(10.0f),
    dir(0.0f),
    rotSpeed(2*M_PI / 3), // 3 seconds per rotation
    a(15.0f),
    drag(0.5f),
    t_old(0.0)
{
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

void SpaceShip::init(shared_ptr<Program> progShapes, string DATA_DIR)
{
    
}

void SpaceShip::update(double t, bool* controlKeys)
{
    //cout << "controlKeys:" << endl;
    //cout << "    " << "forward: " << (controlKeys[KEY_FORWARDS] ? 1 : 0) << endl;
    //cout << "    " << "left:    " << (controlKeys[KEY_LEFT] ? 1 : 0) << endl;
    //cout << "    " << "right:   " << (controlKeys[KEY_RIGHT] ? 1 : 0) << endl;
    //cout << "    " << "shoot:   " << (controlKeys[KEY_SHOOT] ? 1 : 0) << endl;

    float dt = t - t_old;
    t_old = t;

    // update orientation
    if (controlKeys[KEY_LEFT]) {
        dir += rotSpeed * dt;
    }
    if (controlKeys[KEY_RIGHT]) {
        dir -= rotSpeed * dt;
    }
    //cout << "dir: " << dir << endl;

    // update velocity
    float speedSq = v.x * v.x + v.z * v.z;
    //cout << "speed^2: " << speedSq << endl;
    float maxSpeed = 500.0f;
    float minSpeed = 0.5f;
    if (controlKeys[KEY_FORWARDS]) {
        // speed up
        if (speedSq < maxSpeed) {
            v.x += sin(dir) * a * dt;
            v.z += cos(dir) * a * dt;
        }

        //v.x = CLAMP(v.x + (dir) * a * dt, vMax, 0.0f);
        //v.z = CLAMP(v.z + (dir) * a * dt, vMax, 0.0f);
    }
    else {
        // apply drag
        if (speedSq < minSpeed) {
            v.x = 0.0f;
            v.z = 0.0f;
        }
        else {
            v -= dt * drag * v;
        }
    }
    //cout << "v = (" << v.x << ", " << v.y << ")" << endl;

    // update position
    pos += v * dt;
    if (pos.x < -80.0f) {
        pos.x += 160.0f;
    }
    else if (pos.x > 80.0f) {
        pos.x -= 160.f;
    }
    if (pos.z < -45.0f) {
        pos.z += 90.0f;
    }
    else if (pos.z > 45.0f) {
        pos.z -= 90.0f;
    }
    

    //cout << endl;
}

void SpaceShip::draw(std::shared_ptr<MatrixStack> P, std::shared_ptr<MatrixStack> MV, double t)
{
    glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P->topMatrix()));

    MV->pushMatrix();

    MV->translate(pos);
    MV->rotate(dir, 0.0f, 1.0f, 0.0f);
    MV->translate(0.0f, 0.0f, -2.0f);

    // draw body
    glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
    glUniform3f(prog->getUniform("kd"), 0.2f, 0.5f, 0.6f);
    glUniform3f(prog->getUniform("ka"), 0.02f, 0.05f, 0.06f);
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
}
