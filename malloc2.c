#include <stdio.h>
#include <stdlib.h>

int main(){
    int i, number;
    scanf("%d", &number);
    int *a= malloc(sizeof(int)*number);
    if( a== NULL){
        printf("Memory allocaited failed!");
        return 1;

    }
    for( i=0; i< number; i++) {
        printf("%d", *(a+i));
    }

    free(a); //free memory
    a= NULL; //de-referencing the pointer 
    return 0;
}