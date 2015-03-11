#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "interface_io.h"
#include "verification.h"

int sudoku[81];
bool sudokupossible[81][9];

void placer(int num,int lig, int col){
	for (int m=0; m<9; m++){
		sudokupossible[lig*9+col][m]=false;
	}
	for (int i=0; i<9; i++){
		sudokupossible[i*9+col][num-1]=false;
	}
	for (int i=0; i<9; i++){
		sudokupossible[lig*9+i][num-1]=false;
	}
	for (int i=lig-lig%3; i<lig-lig%3+3; i++){
		for (int j=col-col%3; j<col-col%3+3; j++){
			sudokupossible[i*9+j][num-1]=false;
		}
	}
	sudokupossible[lig*9+col][num-1]=true;
}

void creepossible(void){
	for ( int i=0 ; i<81 ; i++ ){
		for ( int k=0; k<9; k++){
			sudokupossible[i][k]=true;
		}
	}
	for ( int i=0 ; i<9 ; i++ ){
		for ( int j=0 ; j<9 ; j++ ){
			if (sudoku[i*9+j]!=0){
				placer(sudoku[i*9+j],i,j);
			}
		}
	}
}

void elagage(void){
	struct num {
		int compt;
		int pos[9];
	};
	struct classenbrposs {
		int compt;
		int num[9];
	};
	struct num carres[9][9];
	void initcarre(int premier, int numcar){
		for (int i=0; i<9; i++){
			for (int j=0; j<9; j++){
				carres[i][j].compt=0;
				for (int k=0; k<9; k++){
					carres[i][j].pos[k]=-1;
				}
			}
		}
		for ( int i=premier/9 ; i<(premier/9+3) ; i++ ){
			for ( int j=premier%9 ; j<premier%9+3 ; j++ ){
				for ( int k=0; k<9; k++){
					if (sudokupossible[i*9+j][k]){
						carres[numcar][k].pos[carres[numcar][k].compt]=i*9+j;
						carres[numcar][k].compt++;
					}
				}
			}
		}
	}
	void elagcarre(int premier, int numcar){
		initcarre(premier,numcar);
		struct classenbrposs classe[9];
		for (int k=0;k<9;k++){
			classe[k].compt=0;
		}
		for (int k=0;k<9;k++){
			int classek=carres[numcar][k].compt;
			int nbr=classe[classek].compt;
			classe[classek].num[nbr]=k;
			classe[classek].compt++;
		}
		for (int k=0;k<classe[1].compt;k++){
			int numero=classe[1].num[k];
			int position=carres[numcar][numero].pos[0];
			for (int m=0; m<9; m++){
				sudokupossible[position][m]=false;
			}
			sudokupossible[position][numero]=true;
		}
		for (int k=0;k<classe[2].compt-1;k++){
			int numero0=classe[2].num[k];
			int position00=carres[numcar][numero0].pos[0];
			int position01=carres[numcar][numero0].pos[1];
			for (int j=k+1;j<classe[2].compt;j++){
				int numero1=classe[2].num[j];
				int position10=carres[numcar][numero1].pos[0];
				int position11=carres[numcar][numero1].pos[1];
				if (position00==position10 && position01==position11){
					for (int m=0; m<9; m++){
						sudokupossible[position00][m]=false;
					}
					for (int m=0; m<9; m++){
						sudokupossible[position01][m]=false;
					}
					sudokupossible[position00][numero0]=true;
					sudokupossible[position01][numero0]=true;
					sudokupossible[position00][numero1]=true;
					sudokupossible[position01][numero1]=true;
				}
			}
		}
		for (int k=0;k<classe[3].compt-2;k++){
			int numero0=classe[3].num[k];
			int position00=carres[numcar][numero0].pos[0];
			int position01=carres[numcar][numero0].pos[1];
			int position02=carres[numcar][numero0].pos[2];
			for (int j=k+1;j<classe[3].compt-1;j++){
				int numero1=classe[3].num[j];
				int position10=carres[numcar][numero1].pos[0];
				int position11=carres[numcar][numero1].pos[1];
				int position12=carres[numcar][numero1].pos[2];
				for (int i=j+1;i<classe[3].compt;i++){
					int numero2=classe[3].num[i];
					int position20=carres[numcar][numero2].pos[0];
					int position21=carres[numcar][numero2].pos[1];
					int position22=carres[numcar][numero2].pos[2];
					if (position00==position10 && position00==position20 &&
							position01==position11 && position01==position21 && 
							position02==position12 && position02==position22){
						for (int m=0; m<9; m++){
							sudokupossible[position00][m]=false;
						}
						for (int m=0; m<9; m++){
							sudokupossible[position01][m]=false;
						}
						for (int m=0; m<9; m++){
							sudokupossible[position02][m]=false;
						}

						sudokupossible[position00][numero0]=true;
						sudokupossible[position01][numero0]=true;
						sudokupossible[position02][numero0]=true;
						sudokupossible[position00][numero1]=true;
						sudokupossible[position01][numero1]=true;
						sudokupossible[position02][numero1]=true;
						sudokupossible[position00][numero2]=true;
						sudokupossible[position01][numero2]=true;
						sudokupossible[position02][numero2]=true;
					}
				}
			}
		}
		void supprposcol(int col,int nbr){
			for (int i=0;i<9;i++){
				sudokupossible[i*9+col][nbr]=false;
			}
		}
		void supprposlig(int lig, int nbr){
			for (int j=0;j<9;j++){
				sudokupossible[lig*9+j][nbr]=false;
			}
		}

		for (int k=0;k<9;k++){
			int nbr=carres[numcar][k].compt;
			int pos0=carres[numcar][k].pos[0];
			int pos1=carres[numcar][k].pos[1];
			int pos2=carres[numcar][k].pos[2];
			if (nbr==1){
				supprposcol(pos0%9,k);
				supprposlig(pos0/9,k);
				sudokupossible[pos0][k]=true;
			}else if (nbr==2){
				if (pos0%9==pos1%9){
					supprposcol(pos0%9,k);
					sudokupossible[pos0][k]=true;
					sudokupossible[pos1][k]=true;
				}else if (pos0/9==pos1/9){
					supprposlig(pos0/9,k);
					sudokupossible[pos0][k]=true;
					sudokupossible[pos1][k]=true;
				}
			}else if (nbr==3){
				if (pos0%9==pos1%9 && pos0%9==pos2%9){
					supprposcol(pos0%9,k);
					sudokupossible[pos0][k]=true;
					sudokupossible[pos1][k]=true;
					sudokupossible[pos2][k]=true;
				}else if (pos0/9==pos1/9 && pos0/9==pos2/9){
					supprposlig(pos0/9,k);
					sudokupossible[pos0][k]=true;
					sudokupossible[pos1][k]=true;
					sudokupossible[pos2][k]=true;
				}
			}
		}
	}
	elagcarre(0,0);
	elagcarre(3,1);
	elagcarre(6,2);
	elagcarre(27,3);
	elagcarre(27+3,4);
	elagcarre(27+6,5);
	elagcarre(54,6);
	elagcarre(54+3,7);
	elagcarre(54+6,8);


	struct num lignes[9][9];
	void initligne(int lig){
		for (int i=0; i<9; i++){
			for (int j=0; j<9; j++){
				lignes[i][j].compt=0;
				for (int k=0; k<9; k++){
					lignes[i][j].pos[k]=-1;
				}
			}
		}
		for ( int j=0; j<9 ; j++ ){
			for ( int k=0; k<9; k++){
				if (sudokupossible[lig*9+j][k]){
					lignes[lig][k].pos[lignes[lig][k].compt]=lig*9+j;
					lignes[lig][k].compt++;
				}
			}
		}
	}
	void elagligne(int lig){
		initligne(lig);
		struct classenbrposs classe[9];
		for (int k=0;k<9;k++){
			classe[k].compt=0;
		}
		for (int k=0;k<9;k++){
			int classek=lignes[lig][k].compt;
			int nbr=classe[classek].compt;
			classe[classek].num[nbr]=k;
			classe[classek].compt++;
		}
		for (int k=0;k<classe[1].compt;k++){
			int numero=classe[1].num[k];
			int position=lignes[lig][numero].pos[0];
			for (int m=0; m<9; m++){
				sudokupossible[position][m]=false;
			}
			sudokupossible[position][numero]=true;
		}
		for (int k=0;k<classe[2].compt-1;k++){
			int numero0=classe[2].num[k];
			int position00=lignes[lig][numero0].pos[0];
			int position01=lignes[lig][numero0].pos[1];
			for (int j=k+1;j<classe[2].compt;j++){
				int numero1=classe[2].num[j];
				int position10=lignes[lig][numero1].pos[0];
				int position11=lignes[lig][numero1].pos[1];
				if (position00==position10 && position01==position11){
					for (int m=0; m<9; m++){
						sudokupossible[position00][m]=false;
					}
					for (int m=0; m<9; m++){
						sudokupossible[position01][m]=false;
					}
					sudokupossible[position00][numero0]=true;
					sudokupossible[position01][numero0]=true;
					sudokupossible[position00][numero1]=true;
					sudokupossible[position01][numero1]=true;
				}
			}
		}
		for (int k=0;k<classe[3].compt-2;k++){
			int numero0=classe[3].num[k];
			int position00=lignes[lig][numero0].pos[0];
			int position01=lignes[lig][numero0].pos[1];
			int position02=lignes[lig][numero0].pos[2];
			for (int j=k+1;j<classe[3].compt-1;j++){
				int numero1=classe[3].num[j];
				int position10=lignes[lig][numero1].pos[0];
				int position11=lignes[lig][numero1].pos[1];
				int position12=lignes[lig][numero1].pos[2];
				for (int i=j+1;i<classe[3].compt;i++){
					int numero2=classe[3].num[i];
					int position20=lignes[lig][numero2].pos[0];
					int position21=lignes[lig][numero2].pos[1];
					int position22=lignes[lig][numero2].pos[2];
					if (position00==position10 && position00==position20 &&
							position01==position11 && position01==position21 && 
							position02==position12 && position02==position22){
						for (int m=0; m<9; m++){
							sudokupossible[position00][m]=false;
						}
						for (int m=0; m<9; m++){
							sudokupossible[position01][m]=false;
						}
						for (int m=0; m<9; m++){
							sudokupossible[position02][m]=false;
						}

						sudokupossible[position00][numero0]=true;
						sudokupossible[position01][numero0]=true;
						sudokupossible[position02][numero0]=true;
						sudokupossible[position00][numero1]=true;
						sudokupossible[position01][numero1]=true;
						sudokupossible[position02][numero1]=true;
						sudokupossible[position00][numero2]=true;
						sudokupossible[position01][numero2]=true;
						sudokupossible[position02][numero2]=true;
					}
				}
			}
		}
		void supprposcar(int premier,int nbr){
			for (int i=premier/9;i<premier/9+3;i++){
				for (int j=premier%9;j<premier%9+3;j++){
					sudokupossible[i*9+j][nbr]=false;
				}
			}
		}
		int precar(int pos){
			int lig=pos/9-(pos/9)%3;
			int col=pos%9-(pos%9)%3;
			return lig*9+col;
		}
		for (int k=0;k<9;k++){
			int nbr=lignes[lig][k].compt;
			int pos0=lignes[lig][k].pos[0];
			int pos1=lignes[lig][k].pos[1];
			int pos2=lignes[lig][k].pos[2];
			int ppos0=precar(pos0);
			int ppos1=precar(pos1);
			int ppos2=precar(pos2);
			if (nbr==1){
				supprposcar(ppos0,k);
				sudokupossible[pos0][k]=true;
			}else if (nbr==2){
				if (ppos0==ppos1){
					supprposcar(ppos0,k);
					sudokupossible[pos0][k]=true;
					sudokupossible[pos1][k]=true;
				}
			}else if (nbr==3){
				if (ppos0==ppos1 && ppos0==ppos2){
					supprposcar(ppos0,k);
					sudokupossible[pos0][k]=true;
					sudokupossible[pos1][k]=true;
					sudokupossible[pos2][k]=true;
				}
			}
		}
	}
	elagligne(0);
	elagligne(1);
	elagligne(2);
	elagligne(3);
	elagligne(4);
	elagligne(5);
	elagligne(6);
	elagligne(7);
	elagligne(8);


	struct num colonnes[9][9];
	void initcolonne(int col){
		for (int i=0; i<9; i++){
			for (int j=0; j<9; j++){
				colonnes[i][j].compt=0;
				for (int k=0; k<9; k++){
					colonnes[i][j].pos[k]=-1;
				}
			}
		}
		for ( int i=0; i<9 ; i++ ){
			for ( int k=0; k<9; k++){
				if (sudokupossible[i*9+col][k]){
					colonnes[col][k].pos[colonnes[col][k].compt]=i*9+col;
					colonnes[col][k].compt++;
				}
			}
		}
	}
	void elagcolonne(int col){
		initcolonne(col);
		struct classenbrposs classe[9];
		for (int k=0;k<9;k++){
			classe[k].compt=0;
		}
		for (int k=0;k<9;k++){
			int classek=colonnes[col][k].compt;
			int nbr=classe[classek].compt;
			classe[classek].num[nbr]=k;
			classe[classek].compt++;
		}
		for (int k=0;k<classe[1].compt;k++){
			int numero=classe[1].num[k];
			int position=colonnes[col][numero].pos[0];
			for (int m=0; m<9; m++){
				sudokupossible[position][m]=false;
			}
			sudokupossible[position][numero]=true;
		}
		for (int k=0;k<classe[2].compt-1;k++){
			int numero0=classe[2].num[k];
			int position00=colonnes[col][numero0].pos[0];
			int position01=colonnes[col][numero0].pos[1];
			for (int j=k+1;j<classe[2].compt;j++){
				int numero1=classe[2].num[j];
				int position10=colonnes[col][numero1].pos[0];
				int position11=colonnes[col][numero1].pos[1];
				if (position00==position10 && position01==position11){
					for (int m=0; m<9; m++){
						sudokupossible[position00][m]=false;
					}
					for (int m=0; m<9; m++){
						sudokupossible[position01][m]=false;
					}
					sudokupossible[position00][numero0]=true;
					sudokupossible[position01][numero0]=true;
					sudokupossible[position00][numero1]=true;
					sudokupossible[position01][numero1]=true;
				}
			}
		}
		for (int k=0;k<classe[3].compt-2;k++){
			int numero0=classe[3].num[k];
			int position00=colonnes[col][numero0].pos[0];
			int position01=colonnes[col][numero0].pos[1];
			int position02=colonnes[col][numero0].pos[2];
			for (int j=k+1;j<classe[3].compt-1;j++){
				int numero1=classe[3].num[j];
				int position10=colonnes[col][numero1].pos[0];
				int position11=colonnes[col][numero1].pos[1];
				int position12=colonnes[col][numero1].pos[2];
				for (int i=j+1;i<classe[3].compt;i++){
					int numero2=classe[3].num[i];
					int position20=colonnes[col][numero2].pos[0];
					int position21=colonnes[col][numero2].pos[1];
					int position22=colonnes[col][numero2].pos[2];
					if (position00==position10 && position00==position20 &&
							position01==position11 && position01==position21 && 
							position02==position12 && position02==position22){
						for (int m=0; m<9; m++){
							sudokupossible[position00][m]=false;
						}
						for (int m=0; m<9; m++){
							sudokupossible[position01][m]=false;
						}
						for (int m=0; m<9; m++){
							sudokupossible[position02][m]=false;
						}

						sudokupossible[position00][numero0]=true;
						sudokupossible[position01][numero0]=true;
						sudokupossible[position02][numero0]=true;
						sudokupossible[position00][numero1]=true;
						sudokupossible[position01][numero1]=true;
						sudokupossible[position02][numero1]=true;
						sudokupossible[position00][numero2]=true;
						sudokupossible[position01][numero2]=true;
						sudokupossible[position02][numero2]=true;
					}
				}
			}
		}
		void supprposcar(int premier,int nbr){
			for (int i=premier/9;i<premier/9+3;i++){
				for (int j=premier%9;j<premier%9+3;j++){
					sudokupossible[i*9+j][nbr]=false;
				}
			}
		}
		int precar(int pos){
			int lig=pos/9-(pos/9)%3;
			int col=pos%9-(pos%9)%3;
			return lig*9+col;
		}
		for (int k=0;k<9;k++){
			int nbr=colonnes[col][k].compt;
			int pos0=colonnes[col][k].pos[0];
			int pos1=colonnes[col][k].pos[1];
			int pos2=colonnes[col][k].pos[2];
			int ppos0=precar(pos0);
			int ppos1=precar(pos1);
			int ppos2=precar(pos2);
			if (nbr==1){
				supprposcar(ppos0,k);
				sudokupossible[pos0][k]=true;
			}else if (nbr==2){
				if (ppos0==ppos1){
					supprposcar(ppos0,k);
					sudokupossible[pos0][k]=true;
					sudokupossible[pos1][k]=true;
				}
			}else if (nbr==3){
				if (ppos0==ppos1 && ppos0==ppos2){
					supprposcar(ppos0,k);
					sudokupossible[pos0][k]=true;
					sudokupossible[pos1][k]=true;
					sudokupossible[pos2][k]=true;
				}
			}
		}

	}
	elagcolonne(0);
	elagcolonne(1);
	elagcolonne(2);
	elagcolonne(3);
	elagcolonne(4);
	elagcolonne(5);
	elagcolonne(6);
	elagcolonne(7);
	elagcolonne(8);


}

int ecrituredespossibilitesuniques(void){
	int nbrtrouve=0;
	int nbr(bool tab[]){
		int compteur=0;
		for (int i=0; i<9; i++){
			if (tab[i]) {
				compteur++;
			}
		}
		return compteur;
	}
	void ecrire(int k){
		int i=0;
		while (sudokupossible[k][i]==false){
			i++;
		}
		sudoku[k]=i+1;
	}


	for ( int i=0 ; i<9 ; i++ ){
		for ( int j=0 ; j<9 ; j++ ){
			if (nbr(sudokupossible[i*9+j])==1 && sudoku[i*9+j]==0){
				ecrire(i*9+j);
				nbrtrouve++;
			}
		}
	}
	return nbrtrouve;
}

int main (void) {
	ecrire(sudoku);
	creepossible();
	bool sudokupossibleprec[81][9];
	bool egal=false;
	while (!egal){
		for (int i=0;i<81;i++){
			for (int j=0;j<9;j++){
				sudokupossibleprec[i][j]=sudokupossible[i][j];
			}
		}
		elagage();
		egal=true;
		for (int i=0;i<81;i++){
			for (int j=0;j<9;j++){
				egal=egal&&(sudokupossibleprec[i][j]==sudokupossible[i][j]);
			}
		}
		printf("\tUn élagage a été opéré, ");
		int nbr=ecrituredespossibilitesuniques();
		printf("%d chiffres ont été trouvés.",nbr);
		if (valider(sudoku)){
			printf("valide\n");
		}else{
			printf("invalide\n");
		}
	}
	int nbr=ecrituredespossibilitesuniques();
	printf("%d chiffres ont été trouvés.\n",nbr);
	afficher(sudoku);
	if (valider(sudoku)){
		printf("\nvalide\n");
	}else{
		printf("\ninvalide...\n");
	}
	if (fini(sudoku)){
		printf("\nfini\n");
	}else{
		printf("\npas fini...\n");
	}
	return 0;
}
