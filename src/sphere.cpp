#include "sphere.h"

Sphere::Sphere(Water* water_ptr, double r, double p, Point ori, Color cl)
{
    delta = 0;
    water = water_ptr;

    poid = p*G;

    v_archimede = Vector(0,0,0);
    v_masse = Vector(0,0,poid);
    v_vitesse = Vector(0,-SPEED_INIT_Y,-default_val_speed / 1000);
    v_frottement = Vector(0,0,0);

    radius = r;
    col = cl;
    origin = ori;
    textureToApply = true;

    resetPosition();
}


void Sphere::update(double delta_t)
{
    delta += delta_t;
    if(delta >= STEP_ANIM)
    {
        // 50ms depuis la derni�re it�ration
        //ADD LINKAGE
        v_masse.z = default_val_masse * G;
        poid = default_val_masse * G;
        radius = default_val_rayon / 100.0;

        double z = anim.getPos().z;
        double y = anim.getPos().y;

        double vc = ( 4 / 3 ) * PI * radius * radius * radius;
        bool came_from_water = false;

        double submerged_volume = sphere_submerged_volume(anim.getPos(), radius, water->getLvl()->getVdir1(), water->getLvl()->getVdir2(), water->getLvl()->getAnim().getPos());
        v_archimede.z = archimede(submerged_volume);

        v_somme.z = -v_masse.z + v_archimede.z + v_frottement.z;
        v_somme.y =  v_frottement.y;

        v_vitesse.z = v_vitesse.z + v_somme.z * delta;
        v_vitesse.y = v_vitesse.y + v_somme.y * delta;

        if(z - radius > water->getLvlz()) // Dessus de l'eau
        {
            v_frottement.y = 0;
            v_frottement.z = 0;
        }
        else // Dans l'eau
        {
            v_frottement.z = 6 * PI * radius * NU * (-v_vitesse.z);
            v_frottement.y = 6 * PI * radius * 1 * (-v_vitesse.y);

            if(v_vitesse.z > 0)
                came_from_water = true;
        }

        if(vc >= v_masse.z)
        {

        }
        else if(came_from_water == true)
        {
            if(v_archimede.z + DELTA_ERR < v_masse.z)
            {
                ++count_water_jump;
                std::cout << "HERE ! " << std::endl<< std::endl<< std::endl<< std::endl<< std::endl;
                v_vitesse.z = 0;
                v_somme.z = 0;
            }
        }

        //MAJ DES VALS EN INTERFACES
        if(count_water_jump >= 5)
        {
            if(old_val_densite == default_val_densite && old_val_masse == default_val_masse && old_val_rayon == default_val_rayon)
                v_vitesse.z = 0;
            else
            {
                old_val_densite = default_val_densite;
                old_val_masse = default_val_masse;
                old_val_rayon = default_val_rayon;
                count_water_jump = 0;
            }
        }
        double futur_pos = z + (v_vitesse.z * delta);
        double futur_pos_y = y + (v_vitesse.y * delta_t);

        if (came_from_water == true && futur_pos - radius > water->getLvlz())
        {
            //futur_pos = water->getLvlz() + radius;
            v_vitesse.z = 0;
        }/*

        if(v_archimede.z >= v_masse.z - DELTA_ERR && v_archimede.z <= v_masse.z + DELTA_ERR)
        {
            v_vitesse = 0;
        }*/

        anim.setPos(Point(anim.getPos().x, futur_pos_y, futur_pos));
        std::cout << "POS: " << z << "\tSUM: " << v_somme.z << "\tVIT: " << v_vitesse.z << "\tFROTT: " << v_frottement.z << "\tARCHI: " << v_archimede.z << "\tMASSE: " << v_masse.z << std::endl;

        if(futur_pos - radius < water->getDeepz())
        {
            anim.setPos(Point(anim.getPos().x, anim.getPos().y, radius + water->getDeepz())); // On met la sph�re sur le sol.
            v_vitesse.z = default_val_speed;

        }

        delta = 0;

        //double futur_pos = z - v_vitesse.z/* - v_masse.z */+ v_archimede.z;

        // Si le prochain mouvement se retrouve ne se retrouve pas sous le sol.
        /*if(futur_pos - radius > 0)
        {
            anim.setPos(Point(0, futur_pos, 0));
            std::cout << "POS: " << futur_pos - radius << std::endl;

            double submerged_volume = sphere_submerged_volume(anim.getPos(), radius, water->getLvl()->getVdir1(), water->getLvl()->getVdir2(), water->getLvl()->getAnim().getPos());

            if(submerged_volume > 0) // Dans l'eau
            {
                if(v_vitesse.z > v_masse.z)
                //if(v_vitesse.z > 0)
                {
                    double coef_fr = 0.045;
                    v_vitesse.z -= v_vitesse.z * coef_fr;
                }
            }
            else    // Or de l'eau
            {
                v_vitesse.x++;
                v_vitesse.z += G*0.000001*v_vitesse.x;
            }

            v_archimede.z = archimede(submerged_volume);

            //std::cout << "Archi : " << v_archimede.z << "  -  Vit : " << v_vitesse << "  +  " << v_masse << std::endl;
            //std::cout << "zpos : " << futur_pos << std::endl;
        }
        else // La sph�re se retrouve sous le sol.
        {
            anim.setPos(Point(0, radius, 0)); // On met la sph�re sur le sol.
        }*/
    }
}


void Sphere::render(void)
{
    Form::render();
    GLUquadric *quad = NULL;

    glEnable(GL_ALPHA_TEST);
    glEnable(GL_DEPTH_TEST);

    glEnable ( GL_TEXTURE_2D );
    glBindTexture ( GL_TEXTURE_2D, this->texture);


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    quad = gluNewQuadric();

    gluQuadricDrawStyle(quad,GLU_FILL);

    if(textureToApply)
    {

        gluQuadricTexture( quad, GL_TRUE);
    }



    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    Point pos = anim.getPos();
    glTranslated(pos.x, pos.y, pos.z);


    glColor3f(255,255, 255);
    gluSphere(quad, radius, SPHERE_SLICES, SPHERE_STACKS);


    gluDeleteQuadric(quad);

    if(displayVect == true)
    {
        glBegin(GL_LINE_LOOP);
        {
            glColor3f(255,0,0);
            glVertex3d(0,0,0);
            glVertex3d(v_somme.x/50, v_somme.y/50, v_somme.z/50);

            glColor3f(0,150,150);
            glVertex3d(0,0,0);
            glVertex3d(v_vitesse.x, v_vitesse.y, v_vitesse.z);
            //glVertex3d(0, - (v_vitesse.z + v_masse.z)*20, 0);
        }
        glEnd();
    }



    glPopMatrix();
}

Point Sphere::getCenter(void)
{
    return anim.getPos();
}

void Sphere::setMasse(Vector masse_vec)
{
    v_masse = masse_vec;
}


void Sphere::resetPosition(void)
{
    anim.setPos(origin);
    v_masse.z = poid;
    //v_vitesse = Vector(0,0,-SPEED_INIT);
    v_vitesse = Vector(0,-SPEED_INIT_Y,-default_val_speed / 1000);
    radius = default_val_rayon / 100.0;
    v_archimede = Vector(0, 0, 0);
    v_somme = Vector(0, 0, 0);
    v_frottement = Vector(0,0,0);
    count_water_jump = 0;
}
