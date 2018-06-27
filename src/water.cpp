#include "water.h"

Water::Water(Point deep_pt, Vector deep_v1, Vector deep_v2, Point lvl_pt, Vector lvl_v1, Vector lvl_v2)
{
    deep = new Cube_face(deep_v1, deep_v2, deep_pt);
    lvl = new Cube_face(lvl_v1, lvl_v2, lvl_pt);
}

Water::~Water(void)
{
    delete deep;
    delete lvl;
}

void Water::update(double delta_t)
{
    deep->update(delta_t);
    lvl->update(delta_t);
}

void Water::render(void)
{
    deep->render();
    lvl->render();
}

Cube_face* Water::getDeep(void)
{
    return deep;
}

Cube_face* Water::getLvl(void)
{
    return lvl;
}

Point Water::getLvlPoint(void)
{
    return lvl->getAnim().getPos();
}

double Water::getLvlY(void)
{
    return lvl->getAnim().getPos().y;
}

Point Water::getDeepPoint(void)
{
    return deep->getAnim().getPos();
}

double Water::getDeepY(void)
{
    return deep->getAnim().getPos().y;
}
