#include <stdlib.h>
#include <stdbool.h>
#include "verification.h"

bool fini(int sudoku[]){
	for ( int i=0 ; i<9 ; i++ ){
		for ( int j=0 ; j<9 ; j++ ){
			if (sudoku[i*9+j]==0){
				return false;
			}
		}
	}
	return true;
}

void validerligne(int sudoku[],bool *valide){
	for ( int i=0 ; i<9 ; i++ ){
		bool memoire[10]={false};
		for ( int j=0 ; j<9 ; j++ ){
			int numero = sudoku[i*9+j];
			if (numero!=0){
				if (memoire[numero]){
					*valide=false;
					return;
				}else{
					memoire[numero]=true;
				}
			}
		}
	}
}

void validercolonne(int sudoku[],bool *valide){
	for ( int j=0 ; j<9 ; j++ ){
		bool memoire[10]={false};
		for ( int i=0 ; i<9 ; i++ ){
			int numero = sudoku[i*9+j];
			if (numero!=0){
				if (memoire[numero]){
					*valide=false;
					return;
				}else{
					memoire[numero]=true;
				}
			}
		}
	}
}

void validercase(int sudoku[],bool *valide){
	void validercasenumerohautgauche(int premier, bool *valide){
		bool memoire[10]={false};
		for ( int i=premier/9 ; i<(premier/9+3) ; i++ ){
			for ( int j=premier%9 ; j<premier%9+3 ; j++ ){
				int numero = sudoku[i*9+j];
				if (numero!=0){
					if (memoire[numero]){
						*valide=false;
						return;
					}else{
						memoire[numero]=true;
					}
				}
			}
		}
	}
	validercasenumerohautgauche(0,valide);
	validercasenumerohautgauche(3,valide);
	validercasenumerohautgauche(6,valide);
	validercasenumerohautgauche(27,valide);
	validercasenumerohautgauche(27+3,valide);
	validercasenumerohautgauche(27+6,valide);
	validercasenumerohautgauche(54,valide);
	validercasenumerohautgauche(54+3,valide);
	validercasenumerohautgauche(54+6,valide);
}

bool valider(int sudoku[]){
	bool valide=true;
	validerligne(sudoku,&valide);
	validercolonne(sudoku,&valide);
	validercase(sudoku,&valide);
	return valide;
}
