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

REAL factorialOfInt(int n){
    REAL res = 1;
    REAL temp = 1;
    for(int i = 1; i <=n; i++){
        res *= temp;
        temp += 1;
    }
    return res;
}

template <typename T>
void fi(int i, T* x, T* y){
    REAL div = factorialOfInt(i);
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
    y[0] /= div;
    y[1] /= div;
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
    REAL div = factorialOfInt(i);
    J[0][0] /= div;
    J[0][1] /= div;
    J[1][0] /= div;
    J[1][1] /= div;
}

template <typename T>
void sumMatrix(T A[2][2], T B[2][2]){
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            A[i][j] += B[i][j];
}

template<typename T>
void prodRealMatrix(REAL h, T A[2][2]){
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            A[i][j] *= h;
}

template<typename T>
void prodRealVector(REAL h, T A[2]){
    for(int i = 0; i < 2; i++)
        A[i] *= h;
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

void printMatrix(REAL m[2][2]){
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++)
            cout << m[i][j] << " ";
        cout << endl;
    }
}

REAL step1SimpleMethod(INTERVAL* Xi, REAL maxH, REAL alpha, INTERVAL* newYLarge){
    INTERVAL temp[2];
    REAL h = maxH;
    INTERVAL hInter(0, h);
    INTERVAL alphaInter(-alpha, alpha);
    INTERVAL oldYLarge[2];
    oldYLarge[0] = Xi[0];
    oldYLarge[1] = Xi[1];
    fi(1, Xi, temp);
    newYLarge[0] = Xi[0] + hInter * temp[0];
    newYLarge[1] = Xi[1] + hInter * temp[1];
    //int limWhile = 5;
    //int limS = 0;
    //cout << "newYLarge[0] " << newYLarge[0] << " et newYLarge[1] " << newYLarge[1] << endl;

    while(!(newYLarge[0] <= oldYLarge[0]) || !(newYLarge[1] <= oldYLarge[1])){
        /*if(limS >= limWhile)
            break;
        limS++;*/
        oldYLarge[0] += alphaInter;
        oldYLarge[1] += alphaInter;
        h /= 2;
        //cout << "h = " << h << endl;
        //cout << "oldYLarge[0] " << oldYLarge[0] << " et oldYLarge[1] " << oldYLarge[1] << endl;
        INTERVAL newH(0, h);
        hInter = newH;
        fi(1, oldYLarge, temp);
        newYLarge[0] = Xi[0] + hInter * temp[0];
        newYLarge[1] = Xi[1] + hInter * temp[1];
        //cout << "newYLarge[0] " << newYLarge[0] << " et newYLarge[1] " << newYLarge[1] << endl;
    }
    newYLarge[0] = oldYLarge[0];
    newYLarge[1] = oldYLarge[1];
    return h;
}

void step2Eij(int k, INTERVAL* yLarge, REAL h, INTERVAL* yTight, REAL A[2][2], INTERVAL* x, INTERVAL* ySuivTight, REAL ASuiv[2][2], INTERVAL* xSuiv){
    REAL yMil[2] = {Mid(yTight[0]), Mid(yTight[1])};

    //cout << "YMil : " << yMil[0] << ", " << yMil[1] << endl;

    INTERVAL vSuiv[2];
    vSuiv[0] = INTERVAL(0);
    vSuiv[1] = INTERVAL(0);
    for(int i = 0; i < k; i++){
        REAL temp[2];
        fi(i, yMil, temp);
        vSuiv[0] += temp[0] * pow(h, i);
        vSuiv[1] += temp[1] * pow(h, i);
        //cout << " pour i = " << i << "vSuiv : " << vSuiv[0] << ", " << vSuiv[1] << endl;
    }
    INTERVAL temp[2];
    fi(k, yLarge, temp);
    vSuiv[0] += temp[0] * pow(h, k);
    vSuiv[1] += temp[1] * pow(h, k);

    //cout << "vSuiv : " << vSuiv[0] << ", " << vSuiv[1] << endl;

    //jacobiennes -> les fi sont lineaires donc c'est la meme que fi
    REAL SReal[2][2] = {0, 0, 0, 0};
    for(int i = 0; i < k; i++){
        jacobFi(i);
        prodRealMatrix(pow(h, i), J);
        sumMatrix(SReal, J);
    }
    //cout << "S : " << endl;
    //printMatrix(SReal);
    
    //pas besoin de Sj intervale : vu que F est lineaire, la jacobienne est constante donc intervalle  = [i, i] donc Sinter - Sreal = 0
    INTERVAL c[2];
    REAL Sy[2] = {yMil[0], yMil[1]};
    prodMatrixVector(SReal, Sy);
    for(int i = 0; i < 2; i++)
        c[i] = vSuiv[i] - Sy[i];

    //cout << "c " << c[0] << " " << c[1] << endl;
    
    prodMatrixMatrix(SReal, A, ASuiv);
    //cout << "Asuiv " << endl;
    //printMatrix(ASuiv);

    REAL invAS[2][2];
    inverseMatrix(ASuiv, invAS);
    //cout << "ASuivInv " << endl;
    //printMatrix(invAS);

    for(int i = 0; i < 2; i++)
        xSuiv[i] = c[i];
    prodMatrixVector(invAS, xSuiv);
    sumVector(x, xSuiv, xSuiv);
    //cout << "xSuiv : " << xSuiv[0] << ", " << xSuiv[1] << endl;
    //cout << "Xinf : " << Inf(xSuiv[0]) << "et sup : " << Sup(xSuiv[0]) << endl;  

    for(int i = 0; i < 2; i++)
        ySuivTight[i] = xSuiv[i];
    prodMatrixVector(ASuiv, ySuivTight);
}

void step2SimpleMethod(int k, INTERVAL* yLarge, REAL h, INTERVAL* yTight, INTERVAL* ySuivTight){
    ySuivTight[0] = INTERVAL(0,0);
    ySuivTight[1] = INTERVAL(0,0);

    INTERVAL temp[2];

    for(int i = 0; i < k; i++){
        fi(i, yTight, temp);
        prodRealVector(pow(h, i), temp);
        sumVector(temp, ySuivTight, ySuivTight);
    }

    fi(k, yLarge, temp);
    prodRealVector(pow(h, k), temp);
    sumVector(temp, ySuivTight, ySuivTight);
}

int main(){
    F[0][0] = 0;
    F[0][1] = 1;
    F[1][0] = -1;
    F[1][1] = 0;

    int nbSteps = 100;

    INTERVAL oldYtight[2];
    REAL maxH = 1;
    REAL alpha = 0.1;
    INTERVAL newYLarge[2];
    oldYtight[0] = INTERVAL(1, 1);
    oldYtight[1] = INTERVAL(0, 0);
    REAL t = 0;

    int k = 3;
    INTERVAL yTight[2];
    REAL A[2][2];
    INTERVAL x[2];
    INTERVAL ySuivTight[2];
    REAL ASuiv[2][2];
    INTERVAL xSuiv[2];

    yTight[0] = INTERVAL(1, 1);
    yTight[1] = INTERVAL(0, 0);
    A[0][0] = 1;
    A[0][1] = 0;
    A[1][0] = 0;
    A[1][1] = 1;
    x[0] = INTERVAL(1, 1);
    x[1] = INTERVAL(0, 0);

    int methode;

    cout << "Simple method : 0, eij : 1" << endl;
    cin >> methode;

    if(methode){
        for(int i = 0; i < nbSteps; i++){
            REAL h = step1SimpleMethod(oldYtight, maxH, alpha, newYLarge);
            //cout << "At time t = " << t << "h = " << h << " et inter[0]" << newYLarge[0] << " et inter [1] = " << newYLarge[1] << endl;

            step2Eij(k, newYLarge, h, yTight, A, x, ySuivTight, ASuiv, xSuiv);
            //cout << "And newYtight[0] = [" << Inf(ySuivTight[0]) << " , " << Sup(ySuivTight[0]) << "et newYtight[1] = " << ySuivTight[1] << endl; 
            
            t+= h;
            oldYtight[0] = ySuivTight[0];
            oldYtight[1] = ySuivTight[1];
            yTight[0] = ySuivTight[0];
            yTight[1] = ySuivTight[1];
            x[0] = xSuiv[0];
            x[1] = xSuiv[1];
            
            for(int i = 0; i < 2; i++)
                for(int j = 0; j < 2; j++)
                    A[i][j] = ASuiv[i][j];
        }
    }
    else{
        for(int i = 0; i < nbSteps; i++){
            REAL h = step1SimpleMethod(oldYtight, maxH, alpha, newYLarge);
            //cout << "At time t = " << t << "h = " << h << " et inter[0]" << newYLarge[0] << " et inter [1] = " << newYLarge[1] << endl;

            step2SimpleMethod(k, newYLarge, h, yTight, ySuivTight);
            //cout << "And newYtight[0] = [" << Inf(ySuivTight[0]) << " , " << Sup(ySuivTight[0]) << "et newYtight[1] = " << ySuivTight[1] << endl; 
            
            t+= h;
            oldYtight[0] = ySuivTight[0];
            oldYtight[1] = ySuivTight[1];
            yTight[0] = ySuivTight[0];
            yTight[1] = ySuivTight[1];
        }
    }
    cout << "And newYtight[0] = [" << Inf(ySuivTight[0]) << " , " << Sup(ySuivTight[0]) << "et newYtight[1] = " << ySuivTight[1] << endl; 
    

    return 0;
}