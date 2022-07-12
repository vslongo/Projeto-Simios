#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

char **leMatriz(size_t *, size_t *, char *);
void imprimeMatriz(char**, size_t, size_t);
void liberaMatriz(char**, size_t);
int analisaMatriz (char**, size_t, size_t);
int analisaLinhasSubMatriz(char**, int, int, size_t, size_t);
int analisaColunasSubMatriz(char**, int, int, size_t, size_t);
int analisaDiagonalPrincipalSubMatriz(char**, int, int, size_t, size_t);
int analisaDiagonalSecundariaSubMatriz(char**, int, int, size_t, size_t);
void simioDetectado(char**, int, int, int, size_t, size_t);
void linhaDetectada(char**, int, int, size_t, size_t);
void colunaDetectada(char**, int, int, size_t, size_t);
void diagonalPrincipalDetectada(char**, int, int, size_t, size_t);
void diagonalSecundariaDetectada(char**, int, int, size_t, size_t);

int main () {
  size_t col, lin;

  char arquivo[256];

  printf("Digite o nome do arquivo contendo o DNA (Ex: dna.txt): ");
  scanf("%s", arquivo);

  char** matriz = leMatriz(&col, &lin, arquivo);

  if(matriz == NULL) {
    fprintf(stderr, "nao foi possivel ler metriz\n");
    return 1;
  }

  imprimeMatriz(matriz, col, lin);

  int isSimian = analisaMatriz(matriz, lin, col);
  if (isSimian == 0) {
    printf("DNA pertence a um humano!");
  }

  liberaMatriz(matriz, lin);

  return 0;
}

void linhaDetectada(char** mat, int i, int j, size_t lin, size_t col) {
  printf("Simio detectado na linha %d!\n", (i+1));
  for (int k = 0; k < lin; k++) {
    for (int l = 0; l < col; l++) {
      if (k == i && ((l == j) || (l == j+1) || (l == j+2) || (l == j + 3))) {
        printf("\x1B[31m" "%-3c " "\x1B[0m",mat[k][l]);
      } else {
        printf("%-3c ", mat[k][l]);
      }
    }
    printf("\n");
  } 
}

void colunaDetectada(char** mat, int i, int j, size_t lin, size_t col) {
  printf("Simio detectado na coluna %d!\n", (i+1));
  for (int k = 0; k < lin; k++) {
    for (int l = 0; l < col; l++) {
      if (l == j && ((k == i) || (k == i+1) || (k == i+2) || (k == i + 3))) {
        printf("\x1B[31m" "%-3c " "\x1B[0m",mat[k][l]);
      } else {
        printf("%-3c ", mat[k][l]);
      }
    }
    printf("\n");
  } 
}

void diagonalPrincipalDetectada(char** mat, int i, int j, size_t lin, size_t col) {
  printf("Simio detectado na diagonal principal, comecando na linha %d e na coluna %d\n", (i+1), (j+1));
  for (int k = 0; k < lin; k++) {
    for (int l = 0; l < col; l++) {
      if (((k == i) && (l == j)) || ((k == i+1) && (l == j+1)) || ((k == i+2) && (l == j+2)) || (k == i+3) && 
      (l == j+3)) {
        printf("\x1B[31m" "%-3c " "\x1B[0m",mat[k][l]);
      } else {
        printf("%-3c ", mat[k][l]);
      }
    }
    printf("\n");
  } 
}

void diagonalSecundariaDetectada(char** mat, int i, int j, size_t lin, size_t col) {
  printf("Simio detectado na diagonal secundaria, comecando na linha  %d e na coluna %d\n", (i+1), (j+4));
  for (int k = 0; k < lin; k++) {
    for (int l = 0; l < col; l++) {
      if (((k == i) && (l == j+3)) || ((k == i+1) && (l == j+2)) ||
      ((k == i+2) && (l == j+1)) || ((k == i+3) && (l == j))) {
        printf("\x1B[31m" "%-3c " "\x1B[0m",mat[k][l]);
      } else {
        printf("%-3c ", mat[k][l]);
      }
    }
    printf("\n");
  } 
}

void simioDetectado(char** mat, int i, int j, int identificador, size_t lin, size_t col) {
  switch (identificador) {
  case 0:
    linhaDetectada(mat, i, j, lin, col);
    break;

  case 1:
    colunaDetectada(mat, i, j, lin, col);
    break;

  case 2:
    diagonalPrincipalDetectada(mat, i, j, lin, col);
    break;

  case 3:
    diagonalSecundariaDetectada(mat, i, j, lin, col);
    break;
  }
}

int analisaLinhasSubMatriz(char** mat, int i, int j, size_t lin, size_t col) {
  int l;
  for (l = i; l < i + 4; l++) {
    if (mat[l][j] == mat[l][j+1] && mat[l][j+1] == mat[l][j+2] && mat[l][j+2] == mat[l][j+3]) {
      simioDetectado(mat, l, j, 0, lin, col);
      return 1;
    }
  }
  return 0;
}

int analisaColunasSubMatriz(char** mat, int i, int j, size_t lin, size_t col) {
  int c;
  for (c = j; c < j + 4; c++) {
    if (mat[i][c] == mat[i+1][c] && mat[i+1][c] == mat[i+2][c] && mat[i+2][c] == mat[i+3][c]) {
      simioDetectado(mat, i, c, 1, lin, col);
      return 1;
    }
  }
  return 0;
}

int analisaDiagonalPrincipalSubMatriz(char** mat, int i, int j, size_t lin, size_t col) {
  if (mat[i][j] == mat[i+1][j+1] && mat[i+1][j+1] == mat[i+2][j+2] && mat[i+2][j+2] == mat[i+3][j+3]) {
    simioDetectado(mat, i, j, 2, lin, col);
    return 1;
  }
  return 0;
}

int analisaDiagonalSecundariaSubMatriz(char** mat, int i, int j, size_t lin, size_t col) {
  if (mat[i][j+3] == mat[i+1][j+2] && mat[i+1][j+2] == mat[i+2][j+1] && mat[i+2][j+1] == mat[i+3][j]) {
    simioDetectado(mat, i, j, 3, lin, col);
    return 1;
  }
  return 0;
}

int analisaMatriz (char** matriz, size_t lin, size_t col) {
  int i, j;
  int isSimian = 0; 
  for (i = 0; i < lin - 3; i++ ) {
    for (j = 0; j < col - 3; j++ ) {
      isSimian = analisaLinhasSubMatriz(matriz, i, j, lin, col);
      if (isSimian == 1) return 1;

      isSimian = analisaColunasSubMatriz(matriz, i, j, lin, col);
      if (isSimian == 1) return 1;

      isSimian = analisaDiagonalPrincipalSubMatriz(matriz, i, j, lin, col);
      if (isSimian == 1) return 1;

      isSimian = analisaDiagonalSecundariaSubMatriz(matriz, i, j, lin, col);
      if (isSimian == 1) return 1;
    }
  }
  return isSimian;
}

void imprimeMatriz(char** matriz, size_t lin, size_t col) {
  for(int i = 0; i < lin; ++i) {
    for(int j = 0; j < col; ++j) {
      printf("%-3c ", matriz[i][j]);
    }
    printf("\n");
  }
}

void liberaMatriz(char** matriz, size_t lin) {
  for(size_t i = 0; i < lin; ++i)
    free(matriz[i]);
  free(matriz);
}

char **leMatriz(size_t *linhas, size_t *cols, char *filename) {
  if (linhas == NULL || cols == NULL || filename == NULL)
    return NULL;

  *linhas = 0;
  *cols = 0;

  FILE *fp = fopen(filename, "r");

  if (fp == NULL) {
    fprintf(stderr, "nao foi possivel abrir %s: %s\n", filename, strerror(errno));
    return NULL;
  }

  char **matriz = NULL, **tmp;

  char linha[1024];

  while(fgets(linha, sizeof linha, fp)) {
    if(*cols == 0) {
      char *scan = linha;
      char dummy;
      int offset = 0;
      while (sscanf(scan, "%c%n", &dummy, &offset) == 1) {
        scan += offset;
        (*cols)++;
      }
    }
    tmp = realloc(matriz, (*linhas + 1) * sizeof *matriz);

    if(tmp == NULL) {
        fclose(fp);
        return matriz;
    }

    matriz = tmp;

    matriz[*linhas] = calloc(*cols, sizeof *matriz[*linhas]);

    if (matriz[*linhas] == NULL) {
      fclose(fp);
      if (*linhas == 0) {
        fclose(fp);
        free(matriz);
        return NULL;
      }

      return matriz;
    }

    int offset = 0;
    char *scan = linha;
    for (size_t j = 0; j < *cols; ++j) {
      if (sscanf(scan, "%c%n", matriz[*linhas] + j, &offset) == 1)
        scan += offset;
      else
        matriz[*linhas][j] = 0;
    }

    (*linhas)++;
  }

  fclose(fp);
  return matriz;
}
