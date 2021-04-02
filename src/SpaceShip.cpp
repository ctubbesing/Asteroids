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
    a(4.0f),
    drag(1.0f),
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
    float dt = t - t_old;
    t_old = t;

    // update orientation
    if (controlKeys[KEY_LEFT]) {
        dir += rotSpeed * dt;
    }
    if (controlKeys[KEY_RIGHT]) {
        dir -= rotSpeed * dt;
    }

    // update velocity
    if (controlKeys[KEY_FORWARDS]) {
        v.x += sin(dir) * a * dt; ////////////////////////// change this to have a max v
        v.z += cos(dir) * a * dt; ////////////////////////// change this to have a max v

        //v.x = CLAMP(v.x + (dir) * a * dt, vMax, 0.0f);
        //v.z = CLAMP(v.z + (dir) * a * dt, vMax, 0.0f);
    }
    else {
        //v.x -= sin(dir) * drag * dt; ////////////////////////// change this to have a max v
        //v.z -= cos(dir) * drag * dt; ////////////////////////// change this to have a max v

        v.x = CLAMP(v.x - (dir) * a * dt, vMax, 0.0f);
        v.z = CLAMP(v.z - (dir) * a * dt, vMax, 0.0f);

        ///////////////////////////////////////////////////////////////so gotta subtract from the negative direction of the ship's velocity
        //////////////////////////////////////////////////////////maybe just v -= drag * v; if(magnitude(v) < smallVal) v = 0;?
    }
    cout << "v = (" << v.x << ", " << v.y << ")" << endl;
    // update position
    pos += v * dt;
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
