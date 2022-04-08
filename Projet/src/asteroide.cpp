#include"asteroide.h"
//extern float vitesse_reelle;

Asteroide::Asteroide( int i ,GLfloat rad, GLfloat sli, GLfloat sta){
    this->_id=i; 
    this->_x=r[i][0];;
    this->_y=r[i][1];;
    this->_z=r[i][2];;
    this->_radius=rad;
    this->_slide=sli;
    this->_stack=sta;
    this->_angle = angle_ast[i];

   
}

GLvoid Asteroide::renduAsteroide(){
   glPushMatrix();
   {
    glColor3f(0.5,0.5,0.5);
    glTranslatef(_x,_y,-_z);
    
    
    
    glutSolidSphere(_radius,_slide,_stack);
    glColor3f(1, 1, 1);
   }
   glPopMatrix();
}

 Asteroide::~Asteroide(){ }