#include "GeneralCallback.h"

GeneralCallback::GeneralCallback()
{
	t = osg::Timer();
	t.setStartTick();
	precedentTour = t.tick();
	precedentFrame = t.tick();
}

void GeneralCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
    float dtTour = t.delta_u(precedentTour, t.tick()) / 1000000.0;
    if(dtTour > 1.0)
    {
        phaseDeJeu();
        precedentTour = t.tick();
    }

    deplacementGraphique();
    precedentFrame = t.tick();

	traverse(node,nv);
}

void GeneralCallback::deplacementGraphique()
{
    float dtTour = t.delta_u(precedentTour, t.tick()) / 1000000.0;
    float dtFrame = t.delta_u(precedentFrame, t.tick()) / 1000000.0;

    for (int i=0; i< Avion::avions.size(); i++)
    {
		Avion* avion = Avion::avions[i];
		int x = avion->getX();
		int y = avion->getY();
		int z = avion->getZ();
		int dx = avion->getDx();
		int dy = avion->getDy();
		int dz = avion->getDz();

		// Position
        patAvions[avion->getId()].get()->setPosition(osg::Vec3f(x + dx*dtTour, y + dy*dtTour, z + dz*dtTour));

		// Rotation
		osg::Quat qR;
		osg::Vec3d dl = osg::Vec3f(x + dx*dtTour, y + dy*dtTour, z + dz*dtTour);
		osg::Vec3d normale = osg::Vec3d(1,0,0)^dl;
		float angle = asin( normale.normalize()/dl.normalize() );
		qR.makeRotate(angle, normale);
		patAvions[avion->getId()]->setAttitude(qR);
    }
}


void GeneralCallback::phaseDeJeu()
{
	for (unsigned int i = 0; i<Avion::avions.size() ; i++)
	{
		Avion::avions[i]->deplacement();
	}

	/*for (unsigned int i = 0; i<Avion::avions.size() ; i++)
	{
		Avion::avions[i]->tir(); //Phase de tir: cette fonction effectuera le tir si besoin
	}*/
	//Retire de la liste si detruit
	for (unsigned int i = 0; i<Avion::avions.size() ; i++)
	{
		if (Avion::avions[i]->getDetruit())
		{
			cout << "Avion" << Avion::avions[i]->getId() << " detruit !" << endl;
			patAvions[Avion::avions[i]->getId()]->setPosition(osg::Vec3f(Avion::avions[i]->getId(), -2, 0)); // On met les avions morts sur le bord
			Avion::avions.erase(Avion::avions.begin() + i);
		}
	}

	for (unsigned int i = 0; i<Avion::avions.size() ; i++) //Les avionsAmi choisissent leur direction en premier
	{
	    if ( Avion::avions[i]->getSymbole() == 'A')
		    Avion::avions[i]->nouvelleDirection();
	}
	for (unsigned int i = 0; i<Avion::avions.size() ; i++) //Les avionsEnnemi choisissent leur direction ensuite
	{
	    if ( Avion::avions[i]->getSymbole() == 'E')
		    Avion::avions[i]->nouvelleDirection();
	}
}
