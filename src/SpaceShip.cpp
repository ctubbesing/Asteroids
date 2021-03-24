#include "SpaceShip.h"
#include "Entity.h"
#include "Program.h"
#include "Shape.h"

using namespace std;

SpaceShip::SpaceShip()
{

}

SpaceShip::~SpaceShip()
{

}

void SpaceShip::init(shared_ptr<Program> progShapes, string DATA_DIR)
{
    body = make_shared<Shape>();
    body->loadMesh(DATA_DIR + "spaceship_body.obj");
    body->refreshNormals();
    body->setProgram(progShapes);
    body->scale(1.0f);
    body->init();

    fin = make_shared<Shape>();
    fin->loadMesh(DATA_DIR + "spaceship_fin.obj");
    fin->refreshNormals();
    fin->setProgram(progShapes);
    fin->scale(1.0f);
    fin->init();
}

void SpaceShip::draw(std::shared_ptr<MatrixStack> P, std::shared_ptr<MatrixStack> MV, double t)
{

}
