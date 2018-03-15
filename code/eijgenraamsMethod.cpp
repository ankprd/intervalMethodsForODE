#include<vector>
#include<cstdio>
#include<cmath>
#include<Interval.h>
using namespace std;

/*Eijgenraam's method for the system y1'=y2, y2'=y1*/

/*Notations : 
yiTight = enclosure des valeurs de y a tj -> [yi] du papier
yiLarge = enclosure des valeurs de y entre tj et tj+1 -> [yi~] du papier*/


REAL F[2][2];
REAL J[2][2];

void f(INTERVAL *x, INTERVAL* y){
    y[0] = x[1];
    y[1] = x[0];
}

template <typename T>
void fi(int i, T* x, T* y){
    if(i % 4 == 0){
        y[0] = x[0];
        y[1] = x[1];
    }

    if(i % 4 == 1){
        y[0] = x[1];
        y[1] = -x[0];
    }

    if(i % 4 == 2){
        y[0] = -x[0];
        y[1] = -x[1];
    }

    if(i % 4 == 3){
        y[0] = -x[1];
        y[1] = x[0];
    }
}

void jacobFi(int i){//change la valeur de la matrice globale J
    if(i % 4 == 1){
        J[0][0] = 0;
        J[0][1] = 1;
        J[1][0] = -1;
        J[1][1] = 0;
    }

    if(i % 4 == 2){
        J[0][0] = -1;
        J[0][1] = 0;
        J[1][0] = 0;
        J[1][1] = -1;
    }

    if(i % 4 == 3){
        J[0][0] = 0;
        J[0][1] = -1;
        J[1][0] = 1;
        J[1][1] = 0;
    }

    if(i % 4 == 0){
        J[0][0] = 1;
        J[0][1] = 0;
        J[1][0] = 0;
        J[1][1] = 1;
    }
}

template <typename T>
void sumMatrix(T A[2][2], T B[2][2]){
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            A[i][j] += B[i][j];
}

template<typename T>
void prodRealMatrix(REAL h, T A){
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            A[i][j] *= h;
}

template<typename T>
void prodMatrixVector(REAL A[2][2], T vect[2]){
    T temp[2];
    temp[0] = A[0][0] * vect[0] + A[0][1] * vect[1];
    temp[1] = A[1][0] * vect[0] + A[1][1] * vect[1];
    vect[0] = temp[0];
    vect[1] = temp[1];
}

void prodMatrixMatrix(REAL A[2][2], REAL B[2][2], REAL C[2][2]){
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++){
            C[i][j] = 0;
            for(int k = 0; k < 2; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

void inverseMatrix(REAL A[2][2], REAL invA[2][2]){
    REAL det = A[0][0] * A[1][1] - A[0][1] * A[1][0];
    if(det == 0){
        printf("A non inversible\n");
        return;
    }
    invA[0][0] = A[1][1] / det;
    invA[0][1] = - A[0][1] / det;
    invA[1][0] = - A[1][0] / det;
    invA[1][1] = A[0][0] / det;
}

template <typename T>
void sumVector(T v[2], T t[2], T u[2]){
    for(int i = 0; i < 2; i++)
        u[i] = v[i]+ t[i];
}

REAL step1SimpleMethod(INTERVAL* oldYtight, REAL maxH, REAL alpha, INTERVAL* newYLarge){
    INTERVAL temp[2];
    REAL h = maxH;
    INTERVAL hInter(0, h);
    INTERVAL alphaInter(-alpha, alpha);
    INTERVAL oldYLarge[2];
    oldYLarge[0] = oldYtight[0];
    oldYLarge[1] = oldYtight[1];
    f(oldYtight, temp);
    newYLarge[0] = oldYLarge[0] + hInter * temp[0];
    newYLarge[1] = oldYLarge[1] + hInter * temp[1];
    while(!(newYLarge[0] <= oldYLarge[0]) || !(newYLarge[1] <= oldYLarge[1])){
        oldYLarge[0] += alphaInter * oldYLarge[0];
        oldYLarge[1] += alphaInter * oldYLarge[1];
        h /= 2;
        INTERVAL newH(0, h);
        hInter = newH;
        f(oldYtight, temp);
        newYLarge[0] = oldYLarge[0] + hInter * temp[0];
        newYLarge[1] = oldYLarge[1] + hInter * temp[1];
    }
    newYLarge[0] = oldYLarge[0];
    newYLarge[1] = oldYLarge[1];
    return h;
}

void step2Eij(int k, INTERVAL* yLarge, REAL h, INTERVAL* yTight, REAL A[2][2], INTERVAL* x, INTERVAL* ySuivLarge, REAL ASuiv[2][2], INTERVAL* xSuiv){
    REAL yMil[2] = {Mid(yTight[0]), Mid(yTight[1])};

    INTERVAL vSuiv[2];
    vSuiv[0] = INTERVAL(0);
    vSuiv[1] = INTERVAL(0);
    for(int i = 0; i < k; i++){
        REAL temp[2];
        fi(i, yMil, temp);
        vSuiv[0] += temp[0] * pow(h, i);
        vSuiv[1] += temp[1] * pow(h, i);
    }
    INTERVAL temp[2];
    fi(k, yLarge, temp);
    vSuiv[0] += temp[0] * pow(h, k);
    vSuiv[1] += temp[1] * pow(h, k);

    //jacobiennes -> les fi sont lineaires donc c'est la meme que fi
    REAL SReal[2][2] = {0, 0, 0, 0};
    for(int i = 0; i < k; i++){
        jacobFi(i);
        prodRealMatrix(pow(h, i), J);
        sumMatrix(SReal, J);
    }
    
    //pas besoin de Sj intervale : vu que F est lineaire, la jacobienne est constante donc intervalle  = [i, i] donc Sinter - Sreal = 0
    INTERVAL c[2];
    REAL Sy[2] = {yMil[0], yMil[1]};
    prodMatrixVector(SReal, Sy);
    for(int i = 0; i < 2; i++)
        c[i] = vSuiv[i] - Sy[i];
    
    prodMatrixMatrix(SReal, A, ASuiv);

    REAL invA[2][2];
    inverseMatrix(A, invA);
    for(int i = 0; i < 2; i++)
        xSuiv[i] = c[i];
    prodMatrixVector(invA, xSuiv);
    sumVector(x, xSuiv, xSuiv);

    for(int i = 0; i < 2; i++)
        ySuivLarge[i] = xSuiv[i];
    prodMatrixVector(ASuiv, ySuivLarge);
}

int main(){
    F[0][0] = 0;
    F[0][1] = 1;
    F[1][0] = -1;
    F[1][1] = 0;

    return 0;
}