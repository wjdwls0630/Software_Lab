/***************************************************************************
* FILE: ser_wave.c
* DESCRIPTION:
*   Serial Concurrent Wave Equation - C Version
*   This program implements the concurrent wave equation described
*   in Chapter 5 of Fox et al., 1988, Solving Problems on Concurrent
*   Processors, vol 1.
* AUTHOR: unknown
* LAST REVISED:  04/15/05 Blaise Barney
* LAST REVISED:  03/26/19 Doug Suh          C++
***************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

#define MAXPOINTS 1000 // x direction
#define MAXSTEPS 1000  // t steps
#define MINPOINTS 20
#define PI 3.14159265

void init_param(void);

void init_line(void);

void update(void);

void printfinal(void);

int nsteps,                    /* number of time steps */
        tpoints,                /* total points along string */
        rcode;                    /* generic return code */
float *fxn, *fxnp1, *fxnm1;    /* values at time t */
float *fxhalf, *fxforth;

/***************************************************************************
*	Obtains input values from user
***************************************************************************/
void init_param(void) {
    string tchar;

    /* set number of points, number of iterations */
    tpoints = 0;
    nsteps = 0;
    while ((tpoints < MINPOINTS) || (tpoints > MAXPOINTS)) {
        cout << "Enter number of points along vibrating string [" << MINPOINTS << "," << MAXPOINTS << "]" << endl;
        //cin << tchar;
        //tpoints = stoi(tchar);
        tpoints = MAXPOINTS * 2 / 3;   // suh
        if ((tpoints < MINPOINTS) || (tpoints > MAXPOINTS))
            cout << "Invalid. Please enter value [" << MINPOINTS << "," << MAXPOINTS << "]" << endl;
    }
    while ((nsteps < 1) || (nsteps > MAXSTEPS)) {
        cout << "Enter number of time steps [1-" << MAXSTEPS << "]\n";
        //scanf("%s", tchar);
        //nsteps = atoi(tchar);
        nsteps = MAXSTEPS * 2 / 3;   // suh
        if ((nsteps < 1) || (nsteps > MAXSTEPS))
            cout << "Invalid. Please enter value  [1-" << MAXSTEPS << "]\n";
    }
    printf("Using points = %d, steps = %d\n", tpoints, nsteps);
}

/***************************************************************************
*     Initialize points on line
**************************************************************************/
void init_line(void) {
    int i, j;
    double x, fac, k, tmp;

    /* Calculate initial values based on sine curve */
    fac = 2.0 * PI;
    k = 0.0;
    tmp = tpoints - 1;                // 1 period
    for (j = 1; j <= tpoints; j++) {
        x = k / tmp;
        fxn[j] = sin(fac * x);     // initial condition f(x, t)
        k = k + 1.0;
    }
    /* Initialize old values array */
    for (i = 1; i <= tpoints; i++)
        fxnm1[i] = fxn[i];         // initial condition f(x, t-dt) = f(x, t)
}

/***************************************************************************
*      Calculate new values using wave equation
* d^2 f(x,t) / dt^2 = gamma (d^2 f(x,t) / dx^2 )
**************************************************************************/
void do_math(int i) {
    double dtime, c, dx, tau, sqtau;

    dtime = 0.3;
    c = 1.0;
    dx = 1.0;
    tau = (c * dtime / dx);
    sqtau = tau * tau;
    fxnp1[i] = (2.0 * fxn[i]) - fxnm1[i]
               + (sqtau * (fxn[i - 1] - (2.0 * fxn[i]) + fxn[i + 1]));
}

/***************************************************************************
*     Update all values along line a specified number of times
**************************************************************************/
void update() {
    int i, j;
    /* Update values for each time step */
    for (i = 1; i <= nsteps; i++) {                          // time t
        /* Update points along line for this time step */
        for (j = 1; j <= tpoints; j++) {                     // location x
            /* global endpoints */
            if ((j == 1) || (j == tpoints))
                fxnp1[j] = 0.0;
            else
                do_math(j);
        }
        /* Update old values with new values */
        for (j = 1; j <= tpoints; j++) {
            fxnm1[j] = fxn[j];  // f(x, t-dt) = f(x, t)
            fxn[j] = fxnp1[j];  // f(x, t) = f(x, t+dt)
        }
        if (i == nsteps / 2) for (j = 1; j <= tpoints; j++) fxhalf[j - 1] = fxn[j];
        if (i == nsteps / 4) for (j = 1; j <= tpoints; j++) fxforth[j - 1] = fxn[j];
    }
}

/***************************************************************************
*     Print final results
**************************************************************************/
void printfinal() {
    ofstream fp("final_wave.txt");

    int i;

    fp << setw(15) << "t = T/4 " << setw(15) << "t = T/2 " << setw(15) << "t = T " << endl;
    for (i = 1; i <= tpoints; i++) {
        fp << setw(15) << fxforth[i - 1] << setw(15) << fxhalf[i - 1] << setw(15) << fxn[i] << endl;
    }
    fp.close();
}

/***************************************************************************
*	Main program
**************************************************************************/
int main(int argc, char *argv[]) {
    cout << "Starting serial version of wave equation...\n";
    init_param();
    // allocate memory
    fxn = new float[tpoints + 2];
    fxnp1 = new float[tpoints + 2];
    fxnm1 = new float[tpoints + 2];
    fxhalf = new float[tpoints];
    fxforth = new float[tpoints];
    cout << "Initializing points on the line...\n";
    init_line();
    cout << "Updating all points for all time steps...\n";
    update();
    cout << "Printing final results...\n";
    printfinal();
    cout << "\nDone.\n\n";
    getchar(); // suh
}
