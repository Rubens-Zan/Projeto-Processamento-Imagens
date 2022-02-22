#include<stdio.h>
#include<stdlib.h>

struct PGMstructure
{
    int maxVal;
    int width;
    int height;
    int data[800][800];
};


int main()
{
    FILE *imagein,*imageout;

    int row, col;

    int i,j;
    int ch_int;
//--- CHANGED ------ Start
    struct PGMstructure *imginfo = malloc(sizeof(struct PGMstructure));
//--- CHANGED ------ End
    char infpath[500],outfpath[500];

    printf("Enter PGM file path:");
    scanf("%s",infpath);
    imagein = fopen(infpath,"r+");

    if(imagein == NULL)
    {
        printf("Error opening first file");
        exit(8);
    }

//--- CHANGED ------ Start
    while(getc(imagein) != '\n');           // Ignore the first line in the input file

    if (getc(imagein) == '#' )              // If it is the case, ignore the second line in the input file
        {
        while(getc(imagein) != '\n');
        }
    else
        {
        fseek(imagein, -1, SEEK_CUR);
        }
//--- CHANGED ------ End

    fscanf(imagein,"%d", &imginfo->width);
    fscanf(imagein,"%d", &imginfo->height);
    fscanf(imagein,"%d", &imginfo->maxVal);
    printf("\n width  = %d\n",imginfo->width);
    printf("\n height = %d\n",imginfo->height);
    printf("\n maxVal = %d\n",imginfo->maxVal);

    for (row=0; row<imginfo->height; row++){

        for (col=0; col < imginfo->width; col++)
        {
            fscanf(imagein,"%d", &ch_int);
            imginfo->data[row][col] = ch_int;
        }
    }

//--- CHANGED ------ Start
    fclose(imagein);
//--- CHANGED ------ End

    printf("Enter path of output file:");

    scanf("%s",outfpath);
    imageout = fopen(outfpath,"w+");

//--- CHANGED ------ Start
    for ( i = 0 ; i < imginfo->height ; i++ )
    {
        for ( j = 0 ; j < imginfo->width ; j++ )
        {
            fprintf( imageout,"%d  " , imginfo->data[i][j] );
        }
            fprintf( imageout,"\n" );
    }

    fclose(imageout);
    free(imginfo);
//--- CHANGED ------ End

    return 0;
}
