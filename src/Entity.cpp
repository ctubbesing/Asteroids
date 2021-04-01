#include "Entity.h"

using namespace std;

Entity::Entity(shared_ptr<Program> prog_) :
    prog(prog_)
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
