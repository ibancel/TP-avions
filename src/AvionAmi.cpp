#include "AvionAmi.h"


AvionAmi::AvionAmi(int id, int x, int y, int z, int dx, int dy, int dz): Avion(id, 'A', x, y, z, dx, dy, dz)
{
    this->pretATirer = true;
    this->detruit = false;
}



void AvionAmi::tir() //tir pour l'avion ami
{
	typedef struct vec
	{
		int x;
		int y;
		int z;
	} vec;
	vec Bullet;
	vec right;
	vec SuppVector;

	Bullet.x=x; //moving the bullet
	Bullet.y=y;
	Bullet.z=z;

	right.x = 0; //sample vector Y
	right.y = 1;
	right.z = 0;

	int normeright;
	int normesupp;
	int normebullet;

    bool no_collision = true; //collision defining flag

    //defining that we're not on the border

    if (pretATirer)
	{
		while ( no_collision && (Bullet.x<TAILLE) && (Bullet.y<TAILLE) && (Bullet.z<TAILLE) )
		{
			Bullet.x=Bullet.x+dx; //moving the bullet
			Bullet.y=Bullet.y+dy;
			Bullet.z=Bullet.z+dz;

			//tracing the vector of planes and looking at the collision flag

			for (int i=0; i<Avion::avions.size(); i++)
			{
				if (Avion::avions[i]->getSymbole()=='E') // if enemy is detected
				{
					// calculation of supplemenary coordinate system

					SuppVector.x = Bullet.y * right.z - Bullet.z * right.y;
					SuppVector.y = Bullet.z * right.x - Bullet.x * right.z;
					SuppVector.z = Bullet.x * right.y - Bullet.y * right.x;

					if ((SuppVector.x == 0)&&(SuppVector.y == 0)&&(SuppVector.z == 0))
						  {
							 right.x = 1; //sample vector X if Y and Bullet are collineaires
							 right.y = 0;
							 right.z = 0;

							 SuppVector.x = Bullet.y * right.z - Bullet.z * right.y;
							 SuppVector.y = Bullet.z * right.x - Bullet.x * right.z;
							 SuppVector.z = Bullet.x * right.y - Bullet.y * right.x;

						  }

					right.x = SuppVector.y * Bullet.z - Bullet.z * SuppVector.y;
					right.y = Bullet.z * SuppVector.x - Bullet.x * SuppVector.z;
					right.z = SuppVector.x * Bullet.y - Bullet.y * SuppVector.x;

					//Normalisation of the vectors

					normeright = sqrt(right.x*right.x+right.y*right.y+right.z*right.z);
					normesupp = sqrt(SuppVector.x*SuppVector.x+SuppVector.y*SuppVector.y+SuppVector.z*SuppVector.z);
					//normebullet = sqrt(Bullet.x*Bullet.x+Bullet.y*Bullet.y+Bullet.z*Bullet.z);

                    /*if (normeright!=0){
                        right.x = right.x/normeright;
                        right.y = right.y/normeright;
                        right.z = right.z/normeright;
                    }
                    if (normebullet!=0){
                        Bullet.x=Bullet.x/normebullet;
                        Bullet.y=Bullet.y/normebullet;
                        Bullet.z=Bullet.z/normebullet;
                    }
                    if (normesupp!=0){
                        SuppVector.x = SuppVector.x/normesupp;
                        SuppVector.y = SuppVector.y/normesupp;
                        SuppVector.z = SuppVector.z/normesupp;
                    }*/

					if ((Avion::avions[i]->getX())==(Bullet.x+right.x)&&((Avion::avions[i]->getY())==(Bullet.y+right.y))&&((Avion::avions[i]->getZ())==(Bullet.y+right.y)))
					{
						no_collision = false;
						detruit = true;
						Avion::avions[i]->setDetruit(true);
						cout << "Tir" << id << " cible" << Avion::avions[i]->getId() << endl;
					}

					if ((Avion::avions[i]->getX())==(Bullet.x-right.x)&&((Avion::avions[i]->getY())==(Bullet.y-right.y))&&((Avion::avions[i]->getZ())==(Bullet.y-right.y)))
					{
						no_collision = false;
						detruit = true;
						Avion::avions[i]->setDetruit(true);
						cout << "Tir" << id << " cible" << Avion::avions[i]->getId() << endl;
					}

					if ((Avion::avions[i]->getX())==(Bullet.x+SuppVector.x)&&((Avion::avions[i]->getY())==(Bullet.y+SuppVector.y))&&((Avion::avions[i]->getZ())==(Bullet.y+SuppVector.y)))
					{
						no_collision = false;
						detruit = true;
						Avion::avions[i]->setDetruit(true);
						cout << "Tir" << id << " cible" << Avion::avions[i]->getId() << endl;
					}

					if ((Avion::avions[i]->getX())==(Bullet.x-SuppVector.x)&&((Avion::avions[i]->getY())==(Bullet.y-SuppVector.y))&&((Avion::avions[i]->getZ())==(Bullet.y-SuppVector.y)))
					{
						no_collision = false;
						detruit = true;
						Avion::avions[i]->setDetruit(true);
						cout << "Tir" << id << " cible" << Avion::avions[i]->getId() << endl;
					}

					if ((Avion::avions[0]->getX())==(Bullet.x)&&(Avion::avions[0]->getY())==(Bullet.y)&&(Avion::avions[0]->getZ())==(Bullet.z))
					{
						no_collision = false;
						detruit = true;
						Avion::avions[i]->setDetruit(true);
						cout << "Tir" << id << " cible" << Avion::avions[i]->getId() << endl;
					}

				}
			}
        }

    }
}

void AvionAmi::deplacement()
{
    //direction
    x=x+dx;
    y=y+dy;
    z=z+dz;
    if (x==TAILLE || y==TAILLE || z==TAILLE || x<0 || y<0 || z<0)
    {
        detruit = true;
		cout << "Avion" << id << " sorti du jeu (" << x << " " << y << " " << z << ")" << endl;
    }
}


void AvionAmi::nouvelleDirection()
{
    int Vx = 0, Vy = 0, Vz = 0; //décalage entre l'avion et sa cible sur X, Y et Z
    for (int i=0; i<avions.size(); i++)
    {
        if (avions[i]->getSymbole()=='E')//Les deux avions ciblent le même avion
        {
            Vx = avions[i]->getX() - x;
			Vy = avions[i]->getY() - y;
            Vz = avions[i]->getZ() - z;
            break;
        }
    }

	typedef struct coupleDirection{  //structure permettant une sortie plus jolie pour le prochain vecteur    -- L.O.L.
        int composanteVecteur;
        int *valeurDirectionActuelle;
    } coupleDirection;
    coupleDirection dirX, dirY, dirZ;

    dirX.composanteVecteur = Vx;
    dirX.valeurDirectionActuelle = &dx;
    dirY.composanteVecteur = Vy;
    dirY.valeurDirectionActuelle = &dy;
    dirZ.composanteVecteur = Vz;
    dirZ.valeurDirectionActuelle = &dz;

    std::vector <coupleDirection> direction; // Ce tableau nous permet de classer les composantes du vecteur afin de prioriser les ordres de déplacement

    if ((abs(Vx)>= abs(Vy))&&(abs(Vx)>= abs(Vz)))
    {
        direction.push_back(dirX);
        if(abs(Vy)>= abs(Vz))
        {
            direction.push_back(dirY);
            direction.push_back(dirZ);
        }
        else
        {
            direction.push_back(dirZ);
            direction.push_back(dirY);
        }
    }
    else if ((abs(Vy)>= abs(Vz))&&(abs(Vy)>= abs(Vx)))
    {
        direction.push_back(dirY);
        if(abs(Vx)>= abs(Vz))
        {
            direction.push_back(dirX);
            direction.push_back(dirZ);
        }
        else
        {
            direction.push_back(dirZ);
            direction.push_back(dirX);
        }
    }
    else
    {
        direction.push_back(dirZ);
        if(abs(Vx)>= abs(Vy))
        {
            direction.push_back(dirX);
            direction.push_back(dirY);
        }
        else
        {
            direction.push_back(dirY);
            direction.push_back(dirX);
        }
    }

    if (direction[0].composanteVecteur>0)
    {
        switch(*(direction[0].valeurDirectionActuelle))
        {
        case -1 :
            *(direction[0].valeurDirectionActuelle)=0;
            break;
        case 0 :
            *(direction[0].valeurDirectionActuelle)=1;
            break;
        case 1 :
            if (direction[1].composanteVecteur>0)
            {
                switch(*(direction[1].valeurDirectionActuelle))
                {
                    case -1 :
                        *(direction[1].valeurDirectionActuelle)=0;
                        break;
                    case 0 :
                        *(direction[1].valeurDirectionActuelle)=1;
                        break;
                    case 1 :
                        if (direction[2].composanteVecteur>0)
                        {
                            switch(*(direction[2].valeurDirectionActuelle))
                            {
                                case -1 :
                                    *(direction[2].valeurDirectionActuelle)=0;
                                    break;
                                case 0 :
                                    *(direction[2].valeurDirectionActuelle)=1;
                                    break;
                            }
                        }
                        else if (direction[2].composanteVecteur<0)
                        {
                            switch(*(direction[2].valeurDirectionActuelle))
                            {
                                case -1 :
                                    *(direction[2].valeurDirectionActuelle)=0;
                                    break;
                                case 0 :
                                    *(direction[2].valeurDirectionActuelle)=1;
                                    break;
                            }
                        }
                        break;

                }
            }
            break;
        }
    }
    }
