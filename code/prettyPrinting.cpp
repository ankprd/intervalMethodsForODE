#include "prettyPrinting.h"
#include <string>

using namespace std;

void printBoundingBoxesToFile(string nomFichier, vector<BoundingBox> boxes){
    ofstream myfile;
    myfile.open (nomFichier);
    for(int curB = 0; curB < boxes.size()l curB++){
        myfile << Inf(boxes[curB].interTime) << " " << Sup(boxes[curB].interTime) << " " << Inf(boxes[curB].interVals) << " " << Sup(boxes[curB].interVals) << endl;
    }
    myfile.close();
}

