#include "vaisseau.h"
#include "../rendu/rendu.h"
#include <iostream>

Vaisseau::Vaisseau(){
    this->pos[0] = 0;
    this->pos[1] = 0;
    this->pos[2] = 0;
    this->angle = 0;
    camera = new Camera(posx(), posy() + 10, posz() + 30);
    
    for (int i =0 ; i<5;++i){
       Tir *t = new Tir(posx(), posy() , posz() );
       t->setTirActif(false);
       tirs.push_back(t); 
    }       
    vitesse = 0;
}
Vaisseau::~Vaisseau(){}

void Vaisseau::move(GLfloat x, GLfloat y, GLfloat z){
    this->pos[0] += x;
    this->pos[1] += y;
    this->pos[2] += z;
  

    /*  Si le vaisseau dépasse les limites, il réaparrait de l'autre côté et la caméra aussi*/

    if(posx() > 100){
        this->pos[0] += -200;
        camera->setPos(camera->posx() - 200, camera->posy(), camera->posz());
    }
    else if(posx() < -100){
        this->pos[0] += 200;
        camera->setPos(camera->posx() + 200, camera->posy(), camera->posz());
    }
    if(posy() > 100){
        this->pos[1] += -200;
        camera->setPos(camera->posx(), camera->posy()-200, camera->posz());
    }
    else if(posy() < -100){
        this->pos[1] += 200;
        camera->setPos(camera->posx(), camera->posy()+200, camera->posz());
    }
    if(posz() > 100){
        this->pos[2] += -200;
        camera->setPos(camera->posx(), camera->posy(), camera->posz() - 200);
    }
    else if(posz() < -100){
        this->pos[2] += 200;
        camera->setPos(camera->posx(), camera->posy(), camera->posz() + 200);
    }
}

void Vaisseau::setAngle(GLfloat a){  //angle x z
    this->angle += a;

    a *= 3.14 / 180;

    // Rotation de la caméra
    GLfloat xCam = camera->posx() - posx();
    //GLfloat yCam = camera->posy() - posy();
    GLfloat zCam = camera->posz() - posz();

    /*camera->setPos(
        xCam * cos(a) + zCam * sin(a) + posx(), 
        camera->posy(),
        -xCam * sin(a) + zCam * cos(a) + posz()
    );

    /*camera->setPos(
        xCam * (cos(a)*cos(a) - cos(a)*sin(a)*sin(a)) + yCam * (- cos(a)*sin(a) - cos(a)*cos(a)*sin(a)) + zCam * sin(a)*sin(a) + posx(),
        xCam * (sin(a)*cos(a) + cos(a)*sin(a)*cos(a)) + yCam * (-sin(a)*sin(a) + cos(a)*cos(a)*cos(a)) + zCam * -cos(a)*sin(a) + posy(),
        xCam * sin(a)*sin(a) + yCam * (sin(a)*cos(a)) + zCam * cos(a) + posz()
    );*/


     for (unsigned int i = 0; i< tirs.size();++i){ // les munitions se déplacent avec le vaisseau (angle)
        if(!tirs.at(i)->getTirActif()) tirs.at(i)->setAngle(this->angle);
     }
}



void Vaisseau::setAngle2(GLfloat a){  //angle y z
    this->angle2 += a;
    a *= 3.14 / 180;

    // Rotation de la caméra
    //GLfloat xCam = camera->posx() - posx();
    GLfloat yCam = camera->posy() - posy();
    GLfloat zCam = camera->posz() - posz();

   /* camera->setPos(
        camera->posx(),  
        yCam * cos(a) + zCam * sin(a) + posy(),
        -yCam * sin(a) + zCam * cos(a) + posz()
    );*/

    /*camera->setPos(
        xCam * (cos(a)*cos(a) - cos(a)*sin(a)*sin(a)) + yCam * (- cos(a)*sin(a) - cos(a)*cos(a)*sin(a)) + zCam * sin(a)*sin(a) + posx(),
        xCam * (sin(a)*cos(a) + cos(a)*sin(a)*cos(a)) + yCam * (-sin(a)*sin(a) + cos(a)*cos(a)*cos(a)) + zCam * -cos(a)*sin(a) + posy(),
        xCam * sin(a)*sin(a) + yCam * (sin(a)*cos(a)) + zCam * cos(a) + posz()
    );*/

     for (unsigned int i = 0; i< tirs.size();++i){ // les munitions se déplacent avec le vaisseau (angle)
        if(!tirs.at(i)->getTirActif()) tirs.at(i)->setAngle(this->angle);
     }
}

void Vaisseau::moveForward(){
    GLfloat calculRotationTranslatex = -vitesse * sin((getAngle()) * 3.14 / 180);
    GLfloat calculRotationTranslatey = vitesse * sin(getAngle2() * 3.14 / 180);
    GLfloat calculRotationTranslatez =  -vitesse * cos((getAngle()-getAngle2()) * 3.14 / 180);
 
    if (cos((getAngle2()) * 3.14 / 180) >=0){
        this->move(calculRotationTranslatex, calculRotationTranslatey, calculRotationTranslatez);    
        camera->move(calculRotationTranslatex,calculRotationTranslatey, calculRotationTranslatez);

        for (unsigned int i = 0; i< tirs.size();++i){  // les munitions se déplacent avec le vaisseau (position)
          if(!tirs.at(i)->getTirActif()) tirs.at(i)->move(calculRotationTranslatex, calculRotationTranslatey, calculRotationTranslatez);
        }
    }

    if (cos((getAngle2()) * 3.14 / 180) <0){
        this->move(-calculRotationTranslatex, calculRotationTranslatey, calculRotationTranslatez);    
        camera->move(-calculRotationTranslatex,calculRotationTranslatey, calculRotationTranslatez);

        for (unsigned int i = 0; i< tirs.size();++i){  // les munitions se déplacent avec le vaisseau (position)
          if(!tirs.at(i)->getTirActif()) tirs.at(i)->move(-calculRotationTranslatex, calculRotationTranslatey, calculRotationTranslatez);
        }
    }
}

void Vaisseau::decreaseSpeed(){
    if(vitesse > 0) vitesse *= 0.96;
    
}


GLvoid Vaisseau::tirer(){ // tire une balle 
  for (unsigned int i = 0; i< tirs.size();++i){
        GLfloat longueur = sqrt( (tirs.at(i)->posX()-posx())*(tirs.at(i)->posX()-posx()) 
                                +(tirs.at(i)->posY()-posy())*(tirs.at(i)->posY()-posy())
                                +(tirs.at(i)->posZ()-posz())*(tirs.at(i)->posZ()-posz())  );
    
        GLfloat calculRotationTranslatexTir = -tirs.at(i)->getSpeed() * sin(tirs.at(i)->getAngle() * 3.14 / 180);
        GLfloat calculRotationTranslatezTir = -tirs.at(i)->getSpeed() * cos(tirs.at(i)->getAngle() * 3.14 / 180);
        tirs.at(i)->move(calculRotationTranslatexTir, 0, calculRotationTranslatezTir);

    //on remet la balle a sa place si il atteint la portée grace au calcul de la longueur
    if ( longueur > 20 ){        
        tirs.at(i)->setSpeed(0);   
        tirs.at(i)->setPos(this->posx(),this->posy(),this->posz());
        tirs.at(i)->setTirActif(false);
        tirs.at(i)->setAngle(getAngle());    
    }
  }
}