#ifndef STAR_H
#define STAR_H
#include "cmath"
#include <QPainter>
using namespace std;
const int dim = 2, borderMassC = 10;
int numStars = 300;
double systemRadius = 1e12, distConnect = 1e9;
const double G = 6.67408e-11, dt = 10000, massSun   = 1.98892e30,
             massJup   = 1898.6e24, massUran  = 86.832e24, massEarth = 5.9742e24, massVenus = 4.867e24;
const double borderMass[] = {borderMassC*massEarth, borderMassC*massUran, borderMassC*massJup, borderMassC*massSun};
const QColor colStar[] = {Qt::cyan, Qt::darkGreen, Qt::magenta, Qt::yellow, Qt::white};
const int nColor = sizeof(colStar) / sizeof(colStar[0]);

class star{
public:
    static int starCounter;
    double x[dim]; double v[dim]; double f[dim];
    double m;
    QColor col;

    friend star operator + (star element1, star element2){
        element1.m += element2.m;
        return element1;
    }
    star(){};
    star(double *coord, double *speed, double mass);
    ~star(){starCounter--;}
};

int star::starCounter = 0;

star::star(double *coord, double *speed, double mass){
    for(int k = 0; k < dim; ++k){
        x[k] = coord[k];
        v[k] = speed[k];
    }
    m = mass;
    col = colStar[nColor-1];
    for(int i = 0; i < nColor-1; ++i)
        if(m <= borderMass[i]){
            col = colStar[i];
            break;
        }
    starCounter++;
}

class galaxy{
public:
    int num;
    star **stars;
    galaxy(int n = numStars):num(n){
        stars = new star*[num];
        double x1[dim] = {0}, v1[dim] = {0};
        stars[0] = new star(x1, v1, massSun);
        double rad;
        for(int i = 1; i < num; ++i){
            rad = 0;
            double R = rand() * systemRadius / RAND_MAX,
            fi  = (2 * M_PI * rand()) / RAND_MAX,
            theta = (M_PI * rand()) / RAND_MAX;
            x1[0] = R  * cos(fi);
            x1[1] = R  * sin(fi);
            if(dim == 3){
                x1[0] *= sin(theta);
                x1[1] *= sin(theta);
                x1[3] = R * cos(theta);
            }
            for(int k = 0; k < dim; ++k){
                rad += x1[k] * x1[k];
            }
            double absV = sqrt(G * stars[0]->m / sqrt(rad));//, alpha = (2 * M_PI * rand()) / RAND_MAX;
            v1[0] =  absV * sin(fi);
            v1[1] = -absV * cos(fi);
            stars[i] = new star(x1, v1, massEarth / num * (6 * i));
        }
    };
    ~galaxy(){delete[] stars;};
    double border[dim];

    double GetMass(){
        double mass = 0;
        for(int i = 0; i < num; ++i){
            if (stars[i] != nullptr){
                mass += stars[i]->m;
            }
        }
        return mass;
    }

    star* getStars(){
        double m1 = -1, m2 = -2, m3 = -3;
        star * s = new star[3];
        for(int i = 0; i < num; ++i){
            if (stars[i] != nullptr){
                if(stars[i]->m > m1){
                    m3=m2;
                    m2 = m1;
                    m1 = stars[i]->m;
                    s[2] = s[1];
                    s[1] = s[0];
                    s[0] = *stars[i];
                }
                else if (stars[i]->m > m2){
                    m3=m2;
                    m2 = stars[i]->m;
                    s[2] = s[1];
                    s[1] = *stars[i];
                }
                else if (stars[i]->m > m3){
                    m3 = stars[i]->m;
                    s[2] = *stars[i];
                }
            }
        }
        return s;
    }

    void Absorption(){
        for(int i = 0; i < num; ++i)
            for(int j = i+1; j < num; ++j)
                if ( j != i)
                    if (stars[i] != nullptr && stars[j] != nullptr)
                        if(sqrt(pow(stars[i]->x[0] - stars[j]->x[0], 2) + pow(stars[i]->x[1] - stars[j]->x[1], 2)) < distConnect){
                            *stars[i] = *stars[i] + *stars[j];
                            stars[j] = nullptr;
                        }
    }

    void move(){
        double dist;
        double dCoord[dim];
        for(int i = 0; i < num; ++i)
            for(int k = 0; k < dim; ++k)
                if(stars[i])
                    stars[i]->f[k] = 0;

        for(int i = 0; i < num; i++)
            if(stars[i])
                for(int j = i + 1; j < num; j++)
                    if(i != j && stars[j]){
                        dist = 0;
                        for(int k = 0; k < dim; ++k){
                            dCoord[k] = stars[i]->x[k] - stars[j]->x[k];
                            dist += dCoord[k] * dCoord[k];
                        }
                        if(sqrt(dist) < distConnect){
                            double tmpM = stars[i]->m + stars[j]->m, tmpX[dim], tmpV[dim];
                            for(int k = 0; k < dim; ++k){
                                tmpX[k] = (stars[i]->x[k] * stars[i]->m + stars[j]->x[k] * stars[j]->m)/tmpM;
                                tmpV[k] = (stars[i]->v[k] * stars[i]->m + stars[j]->v[k] * stars[j]->m)/tmpM;
                            }
                            delete stars[j];
                            stars[j] = nullptr;
                            stars[i]->m = tmpM;
                            for(int k = 0; k < dim; ++k){
                                stars[i]->x[k] = tmpX[k];
                                stars[i]->v[k] = tmpV[k];
                            }
                        }
                    }

        for(int i = 0; i < num; i++)
            if(stars[i])
                for(int j = i + 1; j < num; j++)
                    if(i != j && stars[j]){
                        dist = 0;
                        for(int k = 0; k < dim; ++k){
                            dCoord[k] = stars[i]->x[k] - stars[j]->x[k];
                            dist += dCoord[k] * dCoord[k];
                        } // dist = sqrt(dist);
                        for(int k = 0; k < dim; ++k){
                            double tmp = G * stars[i]->m * stars[j]->m / dist;
                            stars[i]->f[k] -= tmp * dCoord[k] / sqrt(dist);
                            stars[j]->f[k] += tmp * dCoord[k] / sqrt(dist);
                        }
                    }

        for(int i = 0; i < num; ++i)
            if(stars[i]){
                for(int k = 0; k < dim; ++k)
                    stars[i]->v[k] += dt * stars[i]->f[k] / stars[i]->m;
                for(int k = 0; k < dim; ++k)
                    stars[i]->x[k] += dt * stars[i]->v[k];
            }
    }

    void SetAll(int counter, double size, double distance ){
        numStars = counter;
        systemRadius = size;
        distConnect = distance;
        return;
    }
};

#endif // STAR_H
