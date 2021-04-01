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
    dir(0.0f)
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

void SpaceShip::draw(std::shared_ptr<MatrixStack> P, std::shared_ptr<MatrixStack> MV, double t)
{
    glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P->topMatrix()));

    MV->pushMatrix();

    MV->translate(pos);
    MV->rotate(dir, 0.0f, 1.0f, 0.0f);

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
