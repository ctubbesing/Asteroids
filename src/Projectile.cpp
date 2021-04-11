#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Projectile.h"
#include "Program.h"
#include "Shape.h"
#include "MatrixStack.h"

using namespace std;

Projectile::Projectile(std::shared_ptr<Program> prog_, std::string& DATA_DIR_, glm::vec3 pos_, float dir_, double t, float speed) : //////prolly won't want to pass in v anyways
    Entity(prog_, DATA_DIR_, pos_, dir_, glm::vec3(0.0f), 2 * M_PI / 0.5f, t),
    age(0.0f),
    lifespan(80.0f / speed) // units traveled / speed
{
    v = glm::vec3(sin(dir) * speed, 0.0f, cos(dir) * speed); // + v;

    // initialize shape
    shape = make_shared<Shape>();
    shape->loadMesh(DATA_DIR + "projectile.obj");
    shape->refreshNormals();
    shape->setProgram(prog);
    shape->scale(1.0f); /////////////////maybe translate here
    shape->init();
}

Projectile::~Projectile()
{

}

void Projectile::update(double t)
{
    float dt = t - t_old;
    t_old = t;

    // update age
    age += dt;
    //if (age > lifespan) {
    //    kill();
    //    return;
    //}

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
}

bool Projectile::isAlive()
{
    return (age < lifespan);
}

void Projectile::draw(std::shared_ptr<MatrixStack> P, std::shared_ptr<MatrixStack> MV, double t)
{
    glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P->topMatrix()));

    MV->pushMatrix();

    float sinDir = sin(dir);
    float cosDir = cos(dir);
    MV->translate(pos);
    //MV->translate(-1.5f * sinDir, 0.0f, -1.5f * cosDir);
    MV->rotate(5 * t, sin(dir), 0.0f, cos(dir));
    MV->rotate(dir, 0.0f, 1.0f, 0.0f);
    //MV->translate(1.5f * sinDir * sinDir, 0.0f, 1.5f * cosDir * cosDir);
    //MV->translate(0.0f, 0.0f, -2.0f);

    glUniform3f(prog->getUniform("kd"), 0.7f, 0.0f, 0.0f);
    glUniform3f(prog->getUniform("ka"), 0.07f, 0.0f, 0.0f);
    glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
    shape->draw();

    MV->popMatrix();
}