#include "Entity.h"

using namespace std;

Entity::Entity(shared_ptr<Program> prog_) :
    prog(prog_),
    pos(glm::vec3(0.0f)),
    dir(0.0f),
    v(glm::vec3(0.0f)),
    rotSpeed(0.0f),
    t_old(0.0)
{

}

Entity::Entity(shared_ptr<Program> prog_, string& DATA_DIR_, glm::vec3 pos_, float dir_, glm::vec3 v_, float rotSpeed_, double t_old_) :
    prog(prog_),
    DATA_DIR(DATA_DIR_),
    pos(pos_),
    dir(dir_),
    v(v_),
    rotSpeed(rotSpeed_),
    t_old(t_old_),
    doWrap(true)
{

}

Entity::~Entity()
{

}

bool Entity::inBounds()
{
    return (pos.x > -80.0f && pos.x < 80.0f && pos.z > -45.0f && pos.z < 45.0f);
}

void Entity::draw(std::shared_ptr<MatrixStack> P, std::shared_ptr<MatrixStack> MV, double t)
{

}

void Entity::updatePos(float dt)
{
    pos += v * dt;

    if (doWrap) {
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
}

float Entity::randFloat(float l, float h)
{
    float r = rand() / (float)RAND_MAX;
    return (1.0f - r) * l + r * h;
}
