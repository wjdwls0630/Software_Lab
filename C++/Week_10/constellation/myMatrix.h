void scalarmult(int n, int m, float a, float *b, float *c);

void matrixadd(int n, int m, float *a, float *b, float *c);

void matrixmult(int N, int K, int M, float *C, float *D, float *E);

float dot(int N, float *C, float *D);

int GaussElimination(int, float *, float *);

void showMatrix(int n, int m, float *F);

void showMatrix(char *name, int n, int m, float *F);

void showequation(int N, float *a, float *b);