#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "inversion-counter.h"

int
main(int argc, char *argv[])
{
    if ( argc != 3 ) {
       printf( "Usage: %s [list] [list length]\n", argv[0] );
       exit( EXIT_FAILURE );
    }

    FILE * fp;
    char * line = NULL;
    size_t len = 0;

    int list_len = atoi( argv[2] );
    int *list = (int *) malloc( sizeof(int) * list_len );
    long int *inversions = (long int *) calloc( 1, sizeof(long int) );

    fp = fopen( argv[1], "r" );
    if ( fp == NULL )
       exit( EXIT_FAILURE );

    for (int i = 0; i < list_len; i++) {
       getline( &line, &len, fp ); 
       list[i] = atoi( line );
    }

    inversion_counter( list, list_len, inversions );

    //print_arr(list, list_len);

    printf("Inversions: %ld\n", *inversions);
    

    if (line)
       free( line );
    exit( EXIT_SUCCESS );
}
