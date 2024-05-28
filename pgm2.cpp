#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

void negativo(int **resetPix, int altura, int largura){
    for (int i = 0; i < largura; i++){
        for (int j = 0; j < altura; j++){
            resetPix[i][j] = 255 - resetPix[i][j];
    }
}
}

void Limiar(int **resetPix, int altura, int largura){
    for(int i = 0; i < largura; i ++){
        for (int j; j < altura; j++){
            if (resetPix[i][j] < 128){
                resetPix[i][j] = 255;
        }   else{
            resetPix[i][j] = 0;
        }
        
    }
}
}    
void brilho(int **resetPix, int altura, int largura, int ajuste){
    for(int i=0; i < largura; i++){
        for(int j; j < altura; j++){
            resetPix[i][j]+= ajuste;
            if(resetPix[i][j] > 255) resetPix[i][j] = 255;
            if(resetPix[i][j] < 0) resetPix[i][j] = 0;
        }
    }
}

void contraste(int  **resetPix, int altura, int largura){
    int soma = 0;
    for (int i = 0; i < largura; i++){
        for (int j; j < altura; j++){
            soma += resetPix[i][j];
        }
    }
    int media = soma/(altura*largura);

    for (int i = 0; i < largura; i++){
        for (int j; j < altura; j++){
            int novoPixel = media + (resetPix[i][j] - media);
            if (novoPixel > 255) novoPixel = 255;
            if (novoPixel < 0) novoPixel = 0;
            resetPix[i][j] = novoPixel;
        }
    }
}

void desfoque(int **pixels, int largura, int altura) {
  int kernel[3][3] = {
    {1, 1, 1},
    {1, 1, 1},
    {1, 1, 1}
  };
  int divisor = 9;

  int **temp = (int **)malloc(altura * sizeof(int *));
  for (int i = 0; i < altura; i++) {
    temp[i] = (int *)malloc(largura * sizeof(int));
  }

  for (int i = 1; i < altura - 1; i++) {
    for (int j = 1; j < largura - 1; j++) {
      int soma = 0;
      for (int ki = -1; ki <= 1; ki++) {
        for (int kj = -1; kj <= 1; kj++) {
          soma += pixels[i + ki][j + kj] * kernel[ki + 1][kj + 1];
        }
      }
      temp[i][j] = soma / divisor;
    }
  }

    for (int i = 1; i < altura; i++){
        for (int j = 1; i < largura; j++){
            pixels[i][j] = temp[i][j];
        }
    }
    for (int i = 0; i < altura; i++){
        free(temp[i]);
    }
    free(temp);
}

void reset(int **resetPix, int **pixel, int altura, int largura){
    for (int i = 0; i < altura; i++){
        for (int j = 0; j < largura; j++){
            resetPix[i][j] = pixel[i][j];
        }
    }
}

int main() {
    FILE *fp;
    char arquivo[200];
    int **pixels;
    char formato[3];
    char comentario[200];
    int altura, largura, max_cor, ajs;

    cout << "Caminho da imagem PGM: ";
    scanf("%[^\n]s", arquivo);

    fp = fopen(arquivo, "rt");
    if (fp == NULL) {
        cout << "Erro ao abrir arquivo '" << arquivo << "'\n";
        return -1;
    }
    fscanf(fp, " %s", formato);
    if (strcmp(formato, "P2") != 0) {
        cout << "Formato invalido!\n";
        return -2;
    }
    fgetc(fp);
    fgets(comentario, 200, fp);
    fscanf(fp, "%d %d", &altura, &largura);
    // cout << "Resolucao: " << altura << "x" << largura << endl;
    fscanf(fp, "%d", &max_cor);
    // cout << "Brilho maximo: " << max_cor << endl;

    pixels = (int **)malloc(largura * sizeof(int *));
    for (int i = 0; i < largura; i++) {
        pixels[i] = (int *)malloc(altura * sizeof(int));
    }
    for (int i = 0; i < largura; i++) {
        for (int j = 0; j < altura; j++) {
            fscanf(fp, "%d", &pixels[i][j]);
        }
    }

    fp = fopen("negativo.ascii.pgm", "wt");

    negativo(resetPix, altura, largura);

    fprintf(fp, "%s", formato);
    fputc('\n', fp);
    fputs(comentario, fp);
    fprintf(fp, "%d %d\n", altura, largura);
    fprintf(fp, "%d\n", max_cor);

    for (int i = 0; i < largura; i++){
        for (int j = 0; j < altura; j++){
            fprintf(fp, "%d ", resetPix[i][j]);
        }
    fprintf(fp, "\n");
    }

    fclose(fp);

    reset(resetPix, pixels, altura, largura);

    fp = fopen("Limiar.ascii.pgm", "wt");

    Limiar(resetPix, altura, largura);

    fprintf(fp, "%s", formato);
    fputc('\n', fp);
    fputs(comentario, fp);
    fprintf(fp, "%d %d\n", altura, largura);
    fprintf(fp, "%d\n", max_cor);

    for (int i = 0; i < largura; i++){
        for (int j = 0; j < altura; j++){
            fprintf(fp, "%d ", resetPix[i][j]);
        }
    fprintf(fp, "\n");
    }

    fclose(fp);

    reset(resetPix, pixels, altura, largura);

    fp = fopen("brilho.ascii.pgm", "wt");

    brilho(resetPix, altura, largura, ajs);
    fprintf(fp, "%s", formato);
    fputc('\n', fp);
    fputs(comentario, fp);
    fprintf(fp, "%d %d\n", altura, largura);
    fprintf(fp, "%d\n", max_cor);

    for (int i = 0; i < largura; i++){
        for (int j = 0; j < altura; j++){
            fprintf(fp, "%d ", resetPix[i][j]);
        }
    fprintf(fp, "\n");
    }

    fclose(fp);

    reset(resetPix, pixels, altura, largura);

    fp = fopen("Desforque.ascii.pgm", "wt");
    
    desfoque(resetPix, altura, largura);

    fprintf(fp, "%s", formato);
    fputc('\n', fp);
    fputs(comentario, fp);
    fprintf(fp, "%d %d\n", altura, largura);
    fprintf(fp, "%d\n", max_cor);

    for (int i = 0; i < largura; i++){
        for (int j = 0; j < altura; j++){
            fprintf(fp, "%d ", resetPix[i][j]);
        }
    fprintf(fp, "\n");
    }

    fclose(fp);

    reset(resetPix, pixels, altura, largura);


/*
    cout << "Matriz de pixels:\n";
    for (int i = 0; i < largura; i++) {
        for (int j = 0; j < altura; j++) {
            printf("%3d ", pixels[i][j]);
        }
        cout << endl;
    }
*/



    return 0;
}
