/****************************************************************************
* FILE: ser_heat2D.c
* DESCRIPTION:
*   Serial HEAT2D Example - C Version
*   This example is based on a simplified
*   two-dimensional heat equation domain decomposition.  The initial
*   temperature is computed to be high in the middle of the domain and
*   zero at the boundaries.  The boundaries are held at zero throughout
*   the simulation.  During the time-stepping, an array containing two
*   domains is used; these domains alternate between old data and new data.
* AUTHOR: D. Turner
* Last Revised: 04/15/05 Blaise Barney
* Last Revised: 03/25/19 Doug Suh           iostream, C++
****************************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
//#include "parameters.h"
#define NXPROB 100
#define NYPROB 100
using namespace std;

void update(int, int, float *, float *);

void inidat(int, int, float *);

void prtdat(int, int, float *, char *);

//int nx, ny;
char *fnam;

class Parms {
public:
    float cx;
    float cy;
    int nts;

    Parms() {};

    Parms(float x, float y, int z) {
        cx = x;
        cy = y;
        nts = z;
    }
};

Parms parms;

int main(int argc, char *argv[]) {
    float u[2 * NXPROB * NYPROB], *u0, *u1;
    int ix, iy, iz, it;

    u0 = u;
    u1 = u + NXPROB * NYPROB;
    parms.cx = parms.cy = 0.1;
    parms.nts = 100;

    cout << "Starting serial version of 2D heat example...\n";
    cout << "Using [" << NXPROB << "][" << NYPROB << "] grid.\n";
    /* Initialize grid and create input file */
    cout << "Initializing grid and creating input file:";
    inidat(NXPROB, NYPROB, u0);
    prtdat(NXPROB, NYPROB, u0, (char *) "f_initial.txt");

    /* Iterate over all timesteps and create output file */
    cout << "Iterating over " << parms.nts << " time steps...\n";
    for (it = 0; it < parms.nts; it++) {
        if (it % 2) update(NXPROB, NYPROB, u1, u0);
        else update(NXPROB, NYPROB, u0, u1);
    }
    cout << "Done. Created output file: ";
    prtdat(NXPROB, NYPROB, u, (char *) "f_final.txt");
}

/****************************************************************************
*   (f(x,y)_n+1 - f(x,y)_n) / dt = gamma(d^2 f(x,y) / dx^2 + d^2 f(x,y) / dy^2)
* where
*     d^2 f(x,y) / dx^2 = ((f(x + dx,y) - f(x,y)) - (f(x,y) - f(x-dx,y))) / dx^2
*     d^2 f(x,y) / dy^2 = ((f(x,y + dy) - f(x,y)) - (f(x,y) - f(x,y)-dy)) / dy^2
****************************************************************************/
void update(int nx, int ny, float *u1, float *u2) {
    int ix, iy, ixiy;

    for (ix = 1; ix < nx - 1; ix++) {
        for (iy = 1; iy < ny - 1; iy++) {
            ixiy = ix * ny + iy;
            u2[ixiy] = u1[ixiy] +
                       parms.cx * (u1[ixiy + ny] + u1[ixiy - ny] - 2.0 * u1[ixiy]) +
                       parms.cy * (u1[ixiy + 1] + u1[ixiy - 1] - 2.0 * u1[ixiy]);
        }
    }
}

/*****************************************************************************
*  subroutine inidat  ????   f(x, y) = x*(Y-x)*y*(Y-y)    ????
*****************************************************************************/
void inidat(int nx, int ny, float *u0) {
    int ix, iy;
    float *u1 = u0 + nx * ny;
    // initial condition t = 0
    for (ix = 0; ix < nx; ix++)
        for (iy = 0; iy < ny; iy++)
            u0[ix * ny + iy] = (float) (ix * (nx - 1 - ix) * iy * (ny - 1 - iy)); //???
    // boundary condition (x, y)
    for (ix = 0; ix < nx; ix++) { // top and bottom
        u1[ix * ny] = u0[ix * ny];
        u1[ix * ny + ny - 1] = u0[ix * ny + ny - 1];
    }
    for (iy = 0; iy < ny; iy++) { // left and right
        u1[iy] = u0[iy];
        u1[(nx - 1) * ny + iy] = u0[(nx - 1) * ny + iy];
    }
}

/**************************************************************************
* subroutine prtdat
**************************************************************************/
void prtdat(int nx, int ny, float *u1, char *fnam) {
    int ix, iy;
    ofstream fp(fnam);

    for (iy = ny - 1; iy >= 0; iy--) {
        for (ix = 0; ix < nx; ix++) {
            fp << setw(8) << u1[ix * ny + iy];
            if (ix != nx - 1) fp << " "; else fp << endl;
        }
    }
    fp.close();
    cout << fnam << endl;
}
