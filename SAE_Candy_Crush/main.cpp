#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <algorithm>

#include <type.h>
#include <cst.h>
#include <affichage.h>


using namespace std;


void initMat (CMatrice & mat, const size_t & nbLignes = 10,
             const size_t & nbColonnes = 10,
             const unsigned & nbMax= KPlusGrandNombreDansLaMatrice){
    mat.resize(nbColonnes);
    for (size_t i=0 ; i < nbLignes ; ++i){
        mat[i].resize(nbLignes);
        for (size_t j=0 ; j< nbLignes; ++j){
            mat[i][j] = rand() % KPlusGrandNombreDansLaMatrice +1 ;
        }
    }
}

void explositionUneBombeHorizontale (CMatrice & mat, const size_t & numLigne,
                                    const size_t & numColonne, const size_t & aLaSuite){
    for (size_t i=numLigne ; i>0 ; i=i-1){
        for (size_t j = 0 ; j < aLaSuite ; ++j){
            mat[i][numColonne+j]=mat[i-1][numColonne+j];
        }
    }
    for (size_t p=0 ; p < aLaSuite ; ++p){
        mat[0][numColonne+p]=rand() % KPlusGrandNombreDansLaMatrice +1;
    }
}


void explositionUneBombeVerticale (CMatrice & mat, const size_t & numLigne,const size_t & numColonne, const size_t & aLaSuite) {
    size_t nombreAFaireDescendre = 0;
    for(; nombreAFaireDescendre < numLigne; ++nombreAFaireDescendre){


    }
    // Cette boucle remplace simplement par des 0 les valeurs alignés
    //        mat[i][numColonne] = 0;
    //        mat[numLigne+aLaSuite-1][numColonne] = mat[nombreAFaireDescendre-1][numColonne];
    //        mat[numLigne+aLaSuite-2][numColonne] = mat[nombreAFaireDescendre-2][numColonne];
    //         mat[numLigne+aLaSuite-3][numColonne] = mat[0][numColonne];

    //    }
    //    mat[nombreAFaireDescendre-1][numColonne] = 0;
    //    mat[nombreAFaireDescendre-2][numColonne] = 0;
    //    mat[0][numColonne] = 0;
    for (size_t i = numLigne ; i < numLigne+aLaSuite; ++i){

        mat[nombreAFaireDescendre][numColonne] = 0;
        for (size_t j = 1 ; j < nombreAFaireDescendre+1 ; ++j){

            mat[numLigne+aLaSuite-j][numColonne] = mat[nombreAFaireDescendre-j][numColonne];

        }


    }
    for (size_t x = 0; x < aLaSuite; ++x){
        mat[x][numColonne] = rand() % KPlusGrandNombreDansLaMatrice +1;
    }
}

bool detectionExplositionUneBombeHorizontale (CMatrice & mat){
    bool auMoinsUneExplosion (false);
    size_t caseAct ;
    size_t temp;
    size_t aLaSuite = 0 ;
    for (size_t i = 0 ; i < mat[0].size() ; ++i){
        caseAct = 0 ;
        for (size_t j = 0 ; j< mat[0].size() ; ++j){
            if (caseAct != mat[i][j]){
                aLaSuite = 1 ;
                temp = j+1;
                caseAct=mat[i][j];
            }
            else {
                ++aLaSuite;
                if (aLaSuite >=3 && mat[i][j+1]!= caseAct){
                    auMoinsUneExplosion = true;
                    cout << "on a une suite en position numLigne = " << i+1
                         << "; colonne = " << temp
                         << "; sur  " << aLaSuite << " cases" << endl;
                    cout << string (20, '-') << endl << "matrice avant suppresion" << endl;
                    afficheMatriceV2(mat);
                    explositionUneBombeHorizontale (mat, i, temp-1, aLaSuite);
                    cout << string (20, '-') << endl << "matrice après suppresion" << endl;
                                afficheMatriceV2(mat);
                }
            }

        }
    }
    return auMoinsUneExplosion;
}

bool detectionExplositionUneBombeVerticale(CMatrice & mat){
    bool auMoinsUneExplosion (false);
    size_t caseAct ;
    size_t aLaSuite = 0 ;
    vector<size_t>tab ;
    for (size_t colonne = 0 ; colonne < mat[0].size() ; ++colonne){
        for (size_t ligne = 0 ; ligne < mat[0].size() ; ++ligne ){
            tab.push_back(mat[ligne][colonne]);
        }
    }
    for(size_t i=0 ; i < tab.size() ; ++i){
        if (caseAct != tab[i]){
            caseAct = tab[i];
            aLaSuite = 1;
        }
        else{
            ++ aLaSuite ;
            if (aLaSuite >= 3 && tab[i+1] != caseAct){
                auMoinsUneExplosion = true;
                cout << "on a une suite en position numLigne = " << i%10 -aLaSuite/2
                     << "; colonne = " << 1 + i/10
                     << "; sur  " << aLaSuite << " cases" << endl;
                cout << string (20, '-') << endl << "matrice avant suppresion" << endl;
                afficheMatriceV2(mat);
                explositionUneBombeVerticale(mat, i%10 -aLaSuite/2-1, i/10, aLaSuite);
                cout << string (20, '-') << endl << "matrice après suppresion" << endl;
                            afficheMatriceV2(mat);
            }
        }
    }
    return auMoinsUneExplosion;
}

void faitUnMouvement(CMatrice & mat, const size_t &numLigne, const size_t &numCol) {

    afficheMatriceVSwitch(mat, numLigne, numCol);

    char  deplacement;
    cin >> deplacement ;


    switch (tolower(deplacement)) {
    case 'z':
        cout << "Déplacement vers le haut demandé." << endl;

                    swap(mat[numLigne][numCol], mat[numLigne - 1][numCol]);

        cout << "Échange effectué." << endl;

    // ... (autres cas)
    default:
        cout << "Choisissez z, q, s, d" << endl;

    }
}

void testSwitch(CMatrice &mat) {
    cout << "Fonction testSwitch appelée." << endl;
            afficheMatriceV2(mat);
    cout << "Veuillez faire un mouvement" << endl;
    faitUnMouvement(mat, 4, 4);

}



int main() {
    clearScreen();
    CMatrice mat ;
    initMat(mat,10,10,20);
    while (true) {
        if (detectionExplositionUneBombeHorizontale(mat) || detectionExplositionUneBombeVerticale(mat)){


        // Appeler la fonction une seule fois et stocker le résultat
        detectionExplositionUneBombeHorizontale(mat);
        detectionExplositionUneBombeVerticale(mat);
        }
        testSwitch(mat);

    }

    }


