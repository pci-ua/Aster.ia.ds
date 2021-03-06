#include "../objets/vaisseau.h"
#include "../objets/camera.h"
#include "../objets/asteroidePetit.h"
#include "../objets/asteroideMoyen.h"
#include "../objets/asteroideGrand.h"
#include "../objets/tir.h"
#include "../objets/fonctionsEnnemi.h"
#include "../fonctions/obj.h"

void renduAsteroide( int taille,struct objmtl as);
void renduCamera(Vaisseau * v);
void renduTir(int etatVaisseau, Tir *t);
void renduVaisseau(int etatVaisseau ,struct objmtl v);
void renduEnnemi(struct objmtl e);
void renduPlanete(struct objmtl planete);
void renduCoeur(struct objmtl coeur);