
#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"

/**********************File I/O functions*******************************/
/***********************************************************************/

/*Gets an ascii pgm image file, store as a color pgm.*/
void getPGMfile (char filename[], PGMImage *img){
   FILE *in_file;
   char ch;
   int row, col, type;
   int ch_int;
 
   in_file = fopen(filename, "r");
   if (in_file == NULL){
     fprintf(stderr, "Error: Unable to open file %s\n\n", filename);
     exit(8);
   }
 
   printf("\nReading image file: %s\n", filename);
   
   /*determine pgm image type (only type three can be used)*/
   ch = getc(in_file);
   if(ch != 'P')
   {
      printf("ERROR(1): Not valid pgm/ppm file type\n");
      exit(1);
   }
   ch = getc(in_file);
   /*convert the one digit integer currently represented as a character to
     an integer(48 == '0')*/
   type = ch - 48;
   if((type != 2) && (type != 3) && (type != 5) && (type != 6))
   {
      printf("ERROR(2): Not valid pgm/ppm file type\n");
      exit(1);
   }
 
   while(getc(in_file) != '\n');             /* skip to end of line*/
 
   while (getc(in_file) == '#')              /* skip comment lines */
   {
     while (getc(in_file) != '\n');          /* skip to end of comment line */
   }
 
   /*there seems to be a difference between color and b/w.  This line is needed
     by b/w but doesn't effect color reading...*/
   fseek(in_file, -1, SEEK_CUR);             /* backup one character*/
   fscanf(in_file,"%d", &((*img).width));
   fscanf(in_file,"%d", &((*img).height));
   fscanf(in_file,"%d", &((*img).maxVal));
 
   printf("\n width  = %d",(*img).width);
   printf("\n height = %d",(*img).height);
   printf("\n maxVal = %d",(*img).maxVal);
   (*img).tipo = type;
   printf("\n");

   (*img).data = (int *)malloc((*img).height * (*img).width * sizeof(int)); 
 
   if(type == 2) {
      for (row=(*img).height-1; row >=0; row--)
        for (col=0; col< (*img).width; col++)
        {
           fscanf(in_file,"%d", &ch_int);
            *(img->data +row *img->width +col)= ch_int;
        }
   }
   else if(type == 5){
      while(getc(in_file) != '\n'); /*skip to end of line*/
 
        for (row=(*img).height-1; row >=0; row--)
         for (col=0; col< (*img).width; col++)
         {
            *(img->data +row *img->width +col)=getc(in_file);
         }
    }
  
   fclose(in_file);
   printf("\nDone reading file.\n");
  }
  
  
  void save(PGMImage *img)
  {
     int i, j, nr, nc, k;
     int red, green, blue;
     FILE *iop;
  
     nr = img->height;
     nc = img->width;

     iop = fopen("image1.pgm", "w");

     fprintf(iop, "P%d \n",(*img).tipo);
     fprintf(iop, "%d %d\n", nc, nr);
     fprintf(iop, "255\n");

     if ((*img).tipo == 5){
      k = 1;
      for(i = nr - 1; i  >= 0; i--)
      {
         for(j = 0; j <  nc; j++)
         {
            red = *(img->data + i * img->width + j);
            putc(red, iop);
         }

      }
      fprintf(iop, "\n");
      fclose(iop);

     }else{

         k = 1;
         for(i = nr - 1; i  >= 0; i--){
            for(j = 0; j <  nc; j++){
               red = *(img->data + i * img->width + j);

               fprintf( iop,"%d  " ,red);
            }
         fprintf(iop, "\n");
         }
         fclose(iop);
     }
  }



int main()
{
    FILE *imagein,*imageout;

    int row, col;

    int i,j;
    int ch_int;
//--- CHANGED ------ Start
    PGMImage *imginfo = malloc(sizeof(PGMImage));
//--- CHANGED ------ End
    char infpath[500],outfpath[500];

    printf("Enter PGM file path:");
    scanf("%s",infpath);

    getPGMfile(infpath, imginfo);
    save(imginfo);
    


}