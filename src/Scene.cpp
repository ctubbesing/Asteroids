#include "Scene.h"
#include "Program.h"
#include "SpaceShip.h"

using namespace std;

Scene::Scene(string _DATA_DIR) :
    DATA_DIR(_DATA_DIR)
{

}

Scene::~Scene()
{

}

void Scene::init()
{
    // initialize spaceship
    spaceship->init(progShapes, DATA_DIR);
}

void Scene::draw(std::shared_ptr<MatrixStack> P, std::shared_ptr<MatrixStack> MV, double t)
{

}
