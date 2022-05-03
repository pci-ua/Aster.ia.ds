#include "rendu.h"

void renduAsteroide(struct objmtl as, const Asteroide & a){
    glPushMatrix();
    {
    glColor3f(0.5,0.5,0.5);
    glTranslatef(a.posX(),a.posY(),a.posZ());
    glRotatef(a.getAngle(),1,1,1);
    for(const auto& face : as.obj.faces){
            glBegin(GL_POLYGON);

            int indexMat = face.at(face.size() - 1).at(0);
            GLfloat shin = as.materiaux.at(indexMat-1).Ns;
            glMaterialfv(GL_FRONT, GL_SHININESS, &shin);

            glNormal3f(as.obj.vn.at(face.at(0).at(2)-1).at(0), as.obj.vn.at(face.at(0).at(2)-1).at(1), as.obj.vn.at(face.at(0).at(2)-1).at(2));
            glColor3f(as.materiaux.at(indexMat-1).Kd.at(0), as.materiaux.at(indexMat-1).Kd.at(1), as.materiaux.at(indexMat-1).Kd.at(2));
            for(const auto& vertex : face) {
                glVertex3f(as.obj.v.at(vertex.at(0) - 1).at(0), as.obj.v.at(vertex.at(0) - 1).at(1), as.obj.v.at(vertex.at(0) - 1).at(2));
            }
            glEnd(); 
        }      
   }
   glPopMatrix();
}

void renduCamera(Vaisseau * vaisseau){
    gluLookAt(vaisseau->camera->posx(), vaisseau->camera->posy(), vaisseau->camera->posz(), vaisseau->posx(), vaisseau->posy(), vaisseau->posz(), 0, 1, 0);
}

void renduTir(Tir * t){
     glPushMatrix();
       {  
        glColor3f(1, 1, 0);
        glTranslatef(t->posX(), t->posY(), t->posZ() );
        glRotatef(t->getAngle(),0.0,1.0,0.0);
        glScalef(0.1,0.1,1);
        glutSolidCube(1);    
       }
    glPopMatrix();
}

void renduVaisseau(struct objmtl v, Vaisseau * vaisseau){
    glNewList(1, GL_COMPILE_AND_EXECUTE);
    glPushMatrix();
    {
        glScalef(0.5, 0.5, 0.5);
        for(const auto& face : v.obj.faces){
            glBegin(GL_POLYGON);

            /*int indexMat = face.at(face.size() - 1).at(0);
            GLfloat shin = v.materiaux.at(indexMat-1).Ns;
            glMaterialfv(GL_FRONT, GL_SHININESS, &shin);*/

            glNormal3f(v.obj.vn.at(face.at(0).at(2)-1).at(0), v.obj.vn.at(face.at(0).at(2)-1).at(1), v.obj.vn.at(face.at(0).at(2)-1).at(2));
            //glColor3f(v.materiaux.at(indexMat-1).Kd.at(0), v.materiaux.at(indexMat-1).Kd.at(1), v.materiaux.at(indexMat-1).Kd.at(2));
            for(const auto& vertex : face) {
                glVertex3f(v.obj.v.at(vertex.at(0) - 1).at(0), v.obj.v.at(vertex.at(0) - 1).at(1), v.obj.v.at(vertex.at(0) - 1).at(2));
            }
            glEnd(); 
        }
    }
    glPopMatrix();
    glEndList();
}

void constrObj(struct objmtl o){

}


