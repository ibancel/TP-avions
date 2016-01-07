#include "Avion.h"
#include "AvionEnnemi.h"
#include "AvionAmi.h"

#include <cmath>

AvionEnnemi::AvionEnnemi(int id, int x, int y, int z, int dx, int dy, int dz): Avion(id, 'E', x, y, z, dx, dy, dz)
{
    this->pretATirer = true;
    this->detruit = false;
}

void AvionEnnemi::deplacement()
{
    /* Le déplacement se fait simplement en additionnant la direction a la position : ici, les avions peuvent traverser les murs */

    x+=dx;
    if(x<0) x=TAILLE-1;
    if(x==TAILLE) x=0;

    y+=dy;
    if(y<0) y=TAILLE-1;
    if(y==TAILLE) y=0;

    z+=dz;
    if(z<0) z=TAILLE-1;
    if(z==TAILLE) z=0;
}

void AvionEnnemi::tir()
{
    if (pretATirer)                                 // Si l'avion est pret a tirer
    {
        for (int j=0; j<TAILLE; j++)                // On fait des tests sur toutes les cases dans la direction de notre avion
        {
            for (int i=0; i<avions.size(); i++)     // On parcourt la liste d'avions
            {
                if (Avion::avions[i]->getSymbole()=='A')         // On prend les avions amis comme cible
                {
                    AvionAmi* a= dynamic_cast<AvionAmi*>( Avion::avions[i] );
                    if(a->getX()==j*dx+x && a->getY()==j*dy+y && a->getX()==j*dz+z)         // On regarde si l'avion ami est sur cette case
                    {
                        /* Dans ce cas, on tire et on change l'etat de la cible */
                        this->pretATirer=false;
                        Avion::avions[i]->setDetruit(true);
                    }
                }
            }
        }
    }
    else
    {
        pretATirer=true;                // Si l'avion n'est pas pret a tirer, on change son etat pour le prochain tour
    }
}

void AvionEnnemi::nouvelleDirection(){
   int iDistanceMin = 0; //numéro de l'avion le plus proche
   float distanceMin = 10000; //distance de l'avion le plus proche
    for(int i=0; i<avions.size();i++) // On parcourt toute la liste d'avion
    {
        if(Avion::avions[i]->getSymbole()=='A') // Seuls les avions amis sont pris en compte
        {
            float dis = (avions[i]->getX()+avions[i]->getDx()-x)^2+(avions[i]->getY()+avions[i]->getDy()-y)^2+(avions[i]->getZ()+avions[i]->getDz()-z)^2;
            dis = sqrt(dis);
            if (dis<distanceMin) //Si la distance trouvée est plus petite que la distance enregistré, on remplace.
            {
                distanceMin=dis;
                iDistanceMin = i;
            }
        }
    }
    // Calcul des composantes du vecteur reliant l'avion ennemi actuel à l'avion ami le plus proche.
    int Vx, Vy, Vz;
    Vx = avions[iDistanceMin]->getX()+avions[iDistanceMin]->getDx()-x;
    Vy = avions[iDistanceMin]->getY()+avions[iDistanceMin]->getDy()-y;
    Vz = avions[iDistanceMin]->getZ()+avions[iDistanceMin]->getDz()-z;

    struct coupleDirection{  //structure permettant une sortie plus jolie pour le prochain vecteur
        int composanteVecteur;
        int *valeurDirectionActuelle;
    };
    coupleDirection dirX, dirY, dirZ;

    dirX.composanteVecteur = Vx;
    dirX.valeurDirectionActuelle = &dx;
    dirY.composanteVecteur = Vy;
    dirY.valeurDirectionActuelle = &dy;
    dirZ.composanteVecteur = Vz;
    dirZ.valeurDirectionActuelle = &dz;

    std::vector <coupleDirection> direction; // Ce tableau nous permet de classer les composantes du vecteur afin de prioritariser les ordres de déplacement

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
                                case 1 :
                                    *(direction[2].valeurDirectionActuelle)=0;
                                    break;
                                case 0 :
                                    *(direction[2].valeurDirectionActuelle)=-1;
                                    break;
                            }
                        }
                        else
                        {
                            switch(*(direction[2].valeurDirectionActuelle))
                            {
                                case -1 :
                                    *(direction[2].valeurDirectionActuelle)=0;
                                    break;
                                case 1 :
                                    *(direction[2].valeurDirectionActuelle)=0;
                                    break;
                            }
                        }
                    break;
                }
            }
            else if (direction[1].composanteVecteur<0)
            {
                switch(*(direction[1].valeurDirectionActuelle))
                {
                    case 1 :
                        *(direction[1].valeurDirectionActuelle)=0;
                        break;
                    case 0 :
                        *(direction[1].valeurDirectionActuelle)=-1;
                        break;
                    case -1 :
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
                                case 1 :
                                    *(direction[2].valeurDirectionActuelle)=0;
                                    break;
                                case 0 :
                                    *(direction[2].valeurDirectionActuelle)=-1;
                                    break;
                            }
                        }
                        else
                        {
                            switch(*(direction[2].valeurDirectionActuelle))
                            {
                                case -1 :
                                    *(direction[2].valeurDirectionActuelle)=0;
                                    break;
                                case 1 :
                                    *(direction[2].valeurDirectionActuelle)=0;
                                    break;
                            }
                        }
                        break;
                }
            }
            else
            {
                switch(*(direction[1].valeurDirectionActuelle))
                {
                    case 1 :
                        *(direction[1].valeurDirectionActuelle)=0;
                        break;
                    case -1 :
                        *(direction[1].valeurDirectionActuelle)=0;
                        break;
                    case 0 :
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
                                case 1 :
                                    *(direction[2].valeurDirectionActuelle)=0;
                                    break;
                                case 0 :
                                    *(direction[2].valeurDirectionActuelle)=-1;
                                    break;
                            }
                        }
                        else
                        {
                            switch(*(direction[2].valeurDirectionActuelle))
                            {
                                case -1 :
                                    *(direction[2].valeurDirectionActuelle)=0;
                                    break;
                                case 1 :
                                    *(direction[2].valeurDirectionActuelle)=0;
                                    break;
                            }
                        }
                        break;
                }
            }
            break;
        }
    }
    else if (direction[0].composanteVecteur<0)
    {
        switch(*(direction[0].valeurDirectionActuelle))
        {
        case 1 :
            *(direction[0].valeurDirectionActuelle)=0;
            break;
        case 0 :
            *(direction[0].valeurDirectionActuelle)=-1;
            break;
        case -1 :
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
                                case 1 :
                                    *(direction[2].valeurDirectionActuelle)=0;
                                    break;
                                case 0 :
                                    *(direction[2].valeurDirectionActuelle)=-1;
                                    break;
                            }
                        }
                        else
                        {
                            switch(*(direction[2].valeurDirectionActuelle))
                            {
                                case -1 :
                                    *(direction[2].valeurDirectionActuelle)=0;
                                    break;
                                case 1 :
                                    *(direction[2].valeurDirectionActuelle)=0;
                                    break;
                            }
                        }
                    break;
                }
            }
            else if (direction[1].composanteVecteur<0)
            {
                switch(*(direction[1].valeurDirectionActuelle))
                {
                    case 1 :
                        *(direction[1].valeurDirectionActuelle)=0;
                        break;
                    case 0 :
                        *(direction[1].valeurDirectionActuelle)=-1;
                        break;
                    case -1 :
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
                                case 1 :
                                    *(direction[2].valeurDirectionActuelle)=0;
                                    break;
                                case 0 :
                                    *(direction[2].valeurDirectionActuelle)=-1;
                                    break;
                            }
                        }
                        else
                        {
                            switch(*(direction[2].valeurDirectionActuelle))
                            {
                                case -1 :
                                    *(direction[2].valeurDirectionActuelle)=0;
                                    break;
                                case 1 :
                                    *(direction[2].valeurDirectionActuelle)=0;
                                    break;
                            }
                        }
                        break;
                }
            }
            else
            {
                switch(*(direction[1].valeurDirectionActuelle))
                {
                    case 1 :
                        *(direction[1].valeurDirectionActuelle)=0;
                        break;
                    case -1 :
                        *(direction[1].valeurDirectionActuelle)=0;
                        break;
                    case 0 :
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
                                case 1 :
                                    *(direction[2].valeurDirectionActuelle)=0;
                                    break;
                                case 0 :
                                    *(direction[2].valeurDirectionActuelle)=-1;
                                    break;
                            }
                        }
                        else
                        {
                            switch(*(direction[2].valeurDirectionActuelle))
                            {
                                case -1 :
                                    *(direction[2].valeurDirectionActuelle)=0;
                                    break;
                                case 1 :
                                    *(direction[2].valeurDirectionActuelle)=0;
                                    break;
                            }
                        }
                        break;
                }
            }
            break;
        }
    }
    else
    {
        switch(*(direction[0].valeurDirectionActuelle))
        {
        case 1 :
            *(direction[0].valeurDirectionActuelle)=0;
            break;
        case -1 :
            *(direction[0].valeurDirectionActuelle)=0;
            break;
        case 0 :
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
                                case 1 :
                                    *(direction[2].valeurDirectionActuelle)=0;
                                    break;
                                case 0 :
                                    *(direction[2].valeurDirectionActuelle)=-1;
                                    break;
                            }
                        }
                        else
                        {
                            switch(*(direction[2].valeurDirectionActuelle))
                            {
                                case -1 :
                                    *(direction[2].valeurDirectionActuelle)=0;
                                    break;
                                case 1 :
                                    *(direction[2].valeurDirectionActuelle)=0;
                                    break;
                            }
                        }
                    break;
                }
            }
            else if (direction[1].composanteVecteur<0)
            {
                switch(*(direction[1].valeurDirectionActuelle))
                {
                    case 1 :
                        *(direction[1].valeurDirectionActuelle)=0;
                        break;
                    case 0 :
                        *(direction[1].valeurDirectionActuelle)=-1;
                        break;
                    case -1 :
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
                                case 1 :
                                    *(direction[2].valeurDirectionActuelle)=0;
                                    break;
                                case 0 :
                                    *(direction[2].valeurDirectionActuelle)=-1;
                                    break;
                            }
                        }
                        else
                        {
                            switch(*(direction[2].valeurDirectionActuelle))
                            {
                                case -1 :
                                    *(direction[2].valeurDirectionActuelle)=0;
                                    break;
                                case 1 :
                                    *(direction[2].valeurDirectionActuelle)=0;
                                    break;
                            }
                        }
                        break;
                }
            }
            else
            {
                switch(*(direction[1].valeurDirectionActuelle))
                {
                    case 1 :
                        *(direction[1].valeurDirectionActuelle)=0;
                        break;
                    case -1 :
                        *(direction[1].valeurDirectionActuelle)=0;
                        break;
                    case 0 :
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
                                case 1 :
                                    *(direction[2].valeurDirectionActuelle)=0;
                                    break;
                                case 0 :
                                    *(direction[2].valeurDirectionActuelle)=-1;
                                    break;
                            }
                        }
                        else
                        {
                            switch(*(direction[2].valeurDirectionActuelle))
                            {
                                case -1 :
                                    *(direction[2].valeurDirectionActuelle)=0;
                                    break;
                                case 1 :
                                    *(direction[2].valeurDirectionActuelle)=0;
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
