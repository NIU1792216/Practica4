/*
Marco Rondón, 1794984
Mario Roda Sevilla, 1792216
*/
#include <stdio.h>
#include <stdlib.h>

double valors[] = { 5.6, 6.1, 1.2 , 2.3 , 9.8 };

typedef struct {
    int niu;
    float notes[5];
} Alu;

float mitjana(float [],int );
int comparacio (const void * a, const void * b);
int comparaciomitjana (const void * a, const void * b);
int comparacioniu (const void * a, const void * b);
int comparacioapartirdindex(const void * a, const void * b);
void imprimirtaula(int num_lin, Alu *alumnes);
void imprimirdesdindex(int num_lin, Alu **alumnes);

int main(){
    FILE *dades;
    Alu *alumnes, **indexmitjanes;
    int n, i, ll, num_lin = 0, lrg = 0;

    // Obrim el fitxer Llista.txt
    dades=fopen("./Llista.txt","r");
    if(dades==NULL){
        printf("\nNo s'ha accedit al fitxer de dades\n");
        return 1;
    }
    // Contem el nombre de línies
    while((ll = fgetc(dades)) != EOF){
        if (ll == '\n'){
            num_lin++;
        }
    }
    printf("\nHi ha %d linies al document.\n",num_lin);
    rewind(dades);
    // Reservem memoria per l'estructura Alu tenint en compte el nombre d'alumnes
    if ((alumnes = (Alu *)malloc(sizeof(Alu)*num_lin)) == NULL){
        printf("Error: no hi ha espai suficient en la memoria.");
        return 2;
    }
    if ((indexmitjanes = (Alu **)malloc(sizeof(Alu *)*num_lin)) == NULL){
        printf("Error: no hi ha espai suficient en la memoria.");
        return 2;
    }
    
    // Llegim el document i guardem les dades en les estructures Alu.
    while(!(fscanf(dades,"%i;",&n)==EOF)){
        alumnes[lrg].niu=n;
        for(i=0;i<4;i++){
            fscanf(dades,"%f",&alumnes[lrg].notes[i]);
            fgetc(dades);//llegeix i descarta els ; i el \n
        }
        alumnes[lrg].notes[4]=mitjana(alumnes[lrg].notes,4);
        indexmitjanes[lrg] = alumnes + lrg;
        lrg++;
    }
    fclose(dades);
    
    printf("La llista abans d'ordenar es: \n");
    for( n = 0 ; n < 5; n++ ) {
       printf("%g ", valors[n]);
    }
    printf("\n");
 
    qsort(valors, 5, sizeof(double), comparacio);
 
    printf("Despres d'ordenar, la llista es: \n");
    for( n = 0 ; n < 5; n++ ) {   
       printf("%g ", valors[n]);
    }
    printf("\n");

    printf("\nLa llista sense ordenar es:\n");
    imprimirdesdindex(num_lin, indexmitjanes);
    qsort(indexmitjanes, num_lin, sizeof(Alu *), comparacioapartirdindex);
    printf("\nLa llista ordenada es:\n");
    imprimirdesdindex(num_lin, indexmitjanes);
    
    // Alliberem memoria
    free(alumnes);
    free(indexmitjanes);
    return 0;
}

int comparacio (const void * a, const void * b) {
    if(*(double*)a<*(double*)b) return 1;
    else return -1;
}

int comparaciomitjana (const void * a, const void * b){
    if (((Alu *) a)->notes[4] > ((Alu *)b)->notes[4]) return 1;
    else return -1;
}

int comparacioniu (const void * a, const void * b){
    if (((Alu *) a)->niu > ((Alu *)b)->niu) return 1;
    else return -1;
}

int comparacioapartirdindex(const void * a, const void * b){
    if ((*((Alu **) a))->notes[4] > (*((Alu **)b))->notes[4]) return 1;
    else return -1;
}

float mitjana(float dades[],int n){
    int i;
    float m=0.;
    for(i=0;i<n;i++)
    {
        m+=dades[i];
    }
    return m/n;
}

// Funció per imprimir les dades
void imprimirtaula(int num_lin, Alu *alumnes){
    int i,j;
    for(j=0;j<num_lin;j++){
            printf("%d | ",alumnes[j].niu);
            for(i=0;i<4;i++){
                printf("%5.1f",alumnes[j].notes[i]);
            }
            printf(" |%6.2f",alumnes[j].notes[4]);
            printf("\n");
        }
}

void imprimirdesdindex(int num_lin, Alu **alumnes){
    int i,j;
    for (j=0;j<num_lin;j++){
        printf("%d | ",alumnes[j]->niu);
        for(i=0;i<4;i++){
            printf("%5.1f",alumnes[j]->notes[i]);
        }
        printf(" |%6.2f",alumnes[j]->notes[4]);
        printf("\n");
    }
}