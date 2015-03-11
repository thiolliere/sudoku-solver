#include <stdlib.h>
#include <stdio.h>
#include "interface_io.h"

void afficher (int sudoku[]){
	for ( int i=0 ; i<9 ; i++ ){
		for ( int j=0 ; j<9 ; j++ ){
			if (j%3 == 2 ){
				printf("%d|",sudoku[i*9+j]);
			}else if (i%3==2) {
				printf("%d_",sudoku[i*9+j]);
			}else{
				printf("%d ",sudoku[i*9+j]);
			}
		}
		printf("\n");
	}
}

void ecrire (int sudoku[]){
	for ( int i=0 ; i<9 ; i++ ){
		for ( int j=0 ; j<9 ; j++ ){
			scanf("%d",&sudoku[i*9+j]);
		}
	}
/*	int rep=-1;
	while (rep!=0){
		printf("votre sudoku : \n");
		afficher(sudoku);
		printf("valider : 0");
		printf("\tmodifier ligne : 1");
		printf("\tmodifier colonne : 2\n"); 
		scanf("%d",&rep);
		if (rep==1){
			printf(" ligne : ");
			int lig=0;
			scanf("%d",&lig);
			for (int i=0;i<9;i++){
				scanf("%d",&sudoku[lig*9+i]); 
			}
		}else if (rep==2){
			printf(" colonne : ");
			int col=0;
			scanf("%d",&col);
			for (int i=0;i<9;i++){
				scanf("%d",&sudoku[i*9+col]);
			}
		}
	}*/
}
