//
// Autodesk DXF to POV-Ray SDL converter
//
// Supported entities: 3DMESH
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX 80

int main(int argc, char* argv[])
{
  char* filein;
  char  fileout[FILENAME_MAX];
  char  line[LINE_MAX];
  size_t len = 0;
  #ifdef __linux__
    size_t eol = 2;
  #elif _WIN32
    size_t eol = 1;
  #endif

  if (argc < 2) {
      fprintf(stderr, "Autodesk DXF to Povray SDL converter: creates 'mesh' object from '3DFACE's.\n\
Usage: dxf2pov infile [outfile]\n");
  exit(1);
  }

  filein = argv[1];

  if (argc < 3) {
    size_t len = strlen(filein);
    memcpy(fileout, filein, len);
    memcpy(&fileout[len-4], ".inc\0", 6);
  } else {
    memcpy(fileout, argv[2], strlen(argv[2]) + 1);
  }

  FILE* fin = fopen(filein, "r");
  if (fin == NULL) {
    fprintf(stderr, "Can't open file '%s'\n", filein);
    exit(1);
  }

  FILE* fout = fopen(fileout, "w");
  if (fout == NULL) {
    fprintf(stderr, "Can't open file '%s'\n", fileout);
    exit(1);
  }

  int face = 0;
  
  fwrite("#declare Geom = mesh\n{\n", 23, 1, fout);
  while (fgets(line, LINE_MAX, fin) != NULL)
  {
    len = strlen(line);
    line[len-eol] = '\0';

    if(!strcmp(line, "3DFACE"))
    {
      fwrite("  triangle { " , 13, 1, fout);
      face = 1;
    }
    else if (!strcmp(line, "10") && face) {
      fgets(line, LINE_MAX, fin);
      fwrite("<", 1, 1, fout);
      fwrite(line, strlen(line) - eol, 1, fout);
      fwrite(",", 1, 1, fout);
    }
      else if (!strcmp(line, "20") && face) {
      fgets(line, LINE_MAX, fin);
      fwrite(line, strlen(line) - eol, 1, fout);
      fwrite(",", 1, 1, fout);
    }
      else if (!strcmp(line, "30") && face) {
      fgets(line, LINE_MAX, fin);
      fwrite(line, strlen(line) - eol, 1, fout);
      fwrite(">, ", 3, 1, fout);
    }
      else if (!strcmp(line, "11") && face) {
      fgets(line, LINE_MAX, fin);
      fwrite("<", 1, 1, fout);
      fwrite(line, strlen(line) - eol, 1, fout);
      fwrite(",", 1, 1, fout);
    }
      else if (!strcmp(line, "21") && face) {
      fgets(line, LINE_MAX, fin);
      fwrite(line, strlen(line) - eol, 1, fout);
      fwrite(",", 1, 1, fout);
    }
      else if (!strcmp(line, "31") && face) {
      fgets(line, LINE_MAX, fin);
      fwrite(line, strlen(line) - eol, 1, fout);
      fwrite(">, ", 3, 1, fout);
    }
      else if (!strcmp(line, "12") && face) {
      fgets(line, LINE_MAX, fin);
      fwrite("<", 1, 1, fout);
      fwrite(line, strlen(line) - eol, 1, fout);
      fwrite(",", 1, 1, fout);
    }
      else if (!strcmp(line, "22") && face) {
      fgets(line, LINE_MAX, fin);
      fwrite(line, strlen(line) - eol, 1, fout);
      fwrite(",", 1, 1, fout);
    }
      else if (!strcmp(line, "32") && face) {
      fgets(line, LINE_MAX, fin);
      fwrite(line, strlen(line) - eol, 1, fout);
      fwrite("> }\n", 4, 1, fout);

      face = 0;
    }

    /*  TODO: Compare with 12, 22, 32
      else if (!strcmp(line, "13\r\n")) {
      fgets(line, LINE_MAX, fin);
      fwrite("<", 1, 1, fout);
      fwrite(line, strlen(line) - eol, 1, fout);
    }
      else if (!strcmp(line, "23\r\n")) {
      fgets(line, LINE_MAX, fin);
      fwrite(line, strlen(line) - eol, 1, fout);
    }
      else if (!strcmp(line, "33\r\n")) {
      fgets(line, LINE_MAX, fin);
      fwrite(line, strlen(line) - eol, 1, fout);

      fwrite(">}\n", 3, 1, fout);
    }
    */
  }

  fwrite("}\n", 2, 1, fout);

  fclose(fin);
  fclose(fout);
}
