#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Asteroid.h"
#include "Program.h"
#include "Shape.h"
#include "MatrixStack.h"

using namespace std;

Asteroid::Asteroid(std::shared_ptr<Program> prog_, std::string& DATA_DIR_, glm::vec3 pos_, glm::vec3 v_, double t_old_, int size_) :
    Entity(prog_, DATA_DIR_, pos_, 0.0f, v_, randFloat(-1.0f, 1.0f), t_old_), //////////////////////////////////////  prolly want to modify rotspeed bounds and randomize dir
    size(size_),
    axis(glm::normalize(glm::vec3(randFloat(), randFloat(), randFloat()))),
    color(glm::vec3(randFloat(0.5f, 0.7f), randFloat(0.4f, 0.5f), randFloat(0.6f, 0.7f)))
{
    // initialize shape
    shape = make_shared<Shape>();
    shape->loadMesh(DATA_DIR + "sphere2.obj");
    shape->refreshNormals();
    shape->setProgram(prog);
    shape->scale(2.0f);///////////////////// scale this to size 1 asteroid
    shape->init();
}

Asteroid::~Asteroid()
{

}

void Asteroid::generateShape()
{

}

void Asteroid::update(double t)
{
    float dt = t - t_old;
    t_old = t;

    // update position
    updatePos(dt);
}

bool Asteroid::isCollision(glm::vec3 p)
{
    return false;
}

void Asteroid::explode()
{

}

void Asteroid::draw(std::shared_ptr<MatrixStack> P, std::shared_ptr<MatrixStack> MV, double t)
{
    glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P->topMatrix()));

    MV->pushMatrix();

    MV->translate(pos);
    MV->rotate(rotSpeed * t, axis);
    MV->rotate(dir, 0.0f, 1.0f, 0.0f);

    glUniform3f(prog->getUniform("kd"), color.r, color.g, color.b);
    glUniform3f(prog->getUniform("ka"), color.r / 10, color.g / 10, color.b / 10);
    glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
    shape->draw();

    MV->popMatrix();
}