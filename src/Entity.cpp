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

Entity::Entity(shared_ptr<Program> prog_, glm::vec3 pos_, float dir_, glm::vec3 v_, float rotSpeed_) :
    prog(prog_),
    pos(pos_),
    dir(dir_),
    v(v_),
    rotSpeed(rotSpeed_),
    t_old(0.0)//////////////////////////////// t_old too?
{

}

Entity::~Entity()
{

}

void Entity::init()
{

}

void Entity::kill()
{

}

void Entity::draw(std::shared_ptr<MatrixStack> P, std::shared_ptr<MatrixStack> MV, double t)
{

}
