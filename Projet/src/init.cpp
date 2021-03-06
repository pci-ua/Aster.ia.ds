#include "../includes/constant.h"

#include "init.h"

#include "touches/actions.h"

#include "fonctions/texture.h"
#include "fonctions/ppm.h"

#include "rendu/rendu.h"
#include "rendu/decor.h"

#include "discordRichPresence/interface.h"

GLuint texture[1];
int window = 0;
GLfloat ambiente[4] = {0.7, 0.7, 0.7, 1};

struct objmtl vaisseauObj	= loadObj("models/vaisseau");
struct objmtl asteroideObj	= loadObj("models/asteroides1");
struct objmtl asteroide2Obj	= loadObj("models/asteroides2");
struct objmtl asteroide3Obj	= loadObj("models/asteroides3");
struct objmtl ennemiobj		= loadObj("models/ennemi");
struct objmtl heartObj		= loadObj("models/heart");

Vaisseau *vaisseau = new Vaisseau(gameconf::PLAYER_BASE_BULLETS_NUMBER);
Vaisseau *ennemi = new Vaisseau(gameconf::ENEMY_BASE_BULLETS_NUMBER);
std::vector<Asteroide *> asteroides;
GLfloat score = gameconf::BASE_SCORE;

int argc;
char **argv;
extern GLvoid Modelisation();

extern std::string pseudonyme;
extern bool writeOnce;

GLvoid Redimensionne(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (GLfloat)width / (GLfloat)height, 0.1, 3000.0);
	glMatrixMode(GL_MODELVIEW);
}

int notre_init(int argc1, char **argv1, void (*Modelisation)())
{
	argc = argc1;
	argv = argv1;
	initialise();

	glutInit(&argc1, argv1);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1280, 960);
	glutInitWindowPosition(0, 0);
	window = glutCreateWindow("Aster.ia.ds");

	glutFullScreen();
	glutDisplayFunc(Modelisation);
	glutIdleFunc(Modelisation);
	glutReshapeFunc(&Redimensionne);
	glutKeyboardFunc(&touche);
	glutKeyboardUpFunc(&releaseTouche);
	glutSpecialFunc(&toucheSpeciale);
	glutSpecialUpFunc(&releaseToucheSpeciale);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambiente);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	renduVaisseau(1, vaisseauObj);
	renduVaisseau(2, vaisseauObj);
	renduAsteroide(1, asteroideObj);
	renduAsteroide(2, asteroide2Obj);
	renduAsteroide(3, asteroide3Obj);
	renduEnnemi(ennemiobj);
	renduCoeur(heartObj);
	decorPlanetes();

	// implementation des fichiers de textures
	TEXTURE_STRUCT *night = readPpm("pic/night.ppm");
	Parametres_texture(0, night, texture[0]);

	glutMainLoop();
	return 1;
}

void initialise()
{

	DiscordRichPresence::make().setStatus( DiscordRichPresenceStatus::playing );

	asteroides.clear();
	creationAsteroides();

	auto getRandPosition = []() { return Rand(gameconf::ENEMY_MIN_RAND_POS, gameconf::ENEMY_MAX_RAND_POS); };

	ennemi->setVie(gameconf::ENEMY_BASE_LIFE);
	ennemi->setPos(getRandPosition(), getRandPosition(), getRandPosition() );
}

void reinitialisation()
{
	delete vaisseau;
	vaisseau = new Vaisseau(gameconf::PLAYER_BASE_BULLETS_NUMBER);

	delete ennemi;
	ennemi = new Vaisseau(gameconf::ENEMY_BASE_BULLETS_NUMBER);

	score = gameconf::BASE_SCORE;
	writeOnce = false;

	glutExit();
	notre_init(argc, argv, &Modelisation);
}

float Rand(float a, float b) // fonction rand
{
	if (b < a)
		return Rand(b, a);
	float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	return (r * (b - a)) + a;
}

int rand_i(int a, int b)
{
	if (b < a)
		return rand_i(b, a);
	return (rand() % (b - a)) + a;
}

void creationAsteroides()
{
	for (int i = 0; i < gameconf::BASE_ASTEROIDS_NUMBER; ++i)
		asteroides.push_back(new AsteroideGrand(asteroides.size()));
}
