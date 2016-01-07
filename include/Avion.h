#ifndef AVION_H
#define AVION_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <vector>

#include <osgViewer/Viewer>
#include <osg/ShapeDrawable>
#include <osg/Material>
#include <osg/StateSet>
#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>
#include <osg/Geometry>
#include <osgDB/ReadFile>
#include <osg/Texture2D>
#include <osg/Light>
#include <osg/LightSource>
#include <osg/Fog>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>

using namespace std;

const int TAILLE = 14;

class Avion{
protected:
    int id;

	int x;
	int y;
	int z;

	int dx; // valent 0, -1 , 1
	int dy;
	int dz;

	char symbole; // 'A':Ami 'E':Ennemi

	bool pretATirer;
	bool detruit;

public:
	static std::vector<Avion*> avions;

    int getId();
    void setId(int id);

	int getX();
	int getY();
	int getZ();
	void setX(int x);
	void setY(int y);
	void setZ(int z);

	int getDx();
	int getDy();
	int getDz();
	void setDx(int dx);
	void setDy(int dy);
	void setDz(int dz);

	char getSymbole();

	bool getPretATirer();
	void setPretATirer(bool a);

	bool getDetruit();
	void setDetruit(bool a);

    Avion(int id, char symbole, int x, int y, int z, int dx, int dy, int dz);

    virtual void deplacement()=0;
	virtual void tir()=0; //modifie l'avion cible
	virtual void nouvelleDirection()=0;
};

#endif
