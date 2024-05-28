#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>

using namespace std;

bool lerArquivo(FILE* fp, int& altura, int& largura, vector<vector<int>>& pixels) {
    // Lê o cabeçalho do arquivo PGM
    char formato[3];
    fscanf(fp, " %2s", formato); // Lê apenas 2 caracteres, ignorando espaços

    if (strcmp(formato, "P2") == 0) { // Verifica se o formato é "P2"
        cout << "Formato inválido!\n";
        return false;
    }

    // Lê o comentário (opcional)
    char comentario[200];
    fgetc(fp); // Descarta o caractere de quebra de linha após o formato
    fgets(comentario, 200, fp);
    cout << comentario << endl;

    // Lê a resolução da imagem
    fscanf(fp, "%d %d", &altura, &largura);
    cout << "Resolução: " << altura << "x" << largura << endl;

    // Lê o valor máximo do brilho
    int max_cor;
    fscanf(fp, "%d", &max_cor);
    cout << "Brilho máximo: " << max_cor << endl;

    // Cria um vetor 2D para armazenar os pixels
    pixels.resize(largura);
    for (int i = 0; i < largura; i++) {
        pixels[i].resize(altura);
    }

    // Lê os pixels da imagem
    for (int i = 0; i < largura; i++) {
        for (int j = 0; j < altura; j++) {
            fscanf(fp, "%d", &pixels[i][j]);
        }
    }

    return true;
}
/*
bool negativo(FILE* fp, int){
    for (int i = 0; i < largura; i++){
        for (int j = 0; j < altura; j++){
            pixel[i][j] =-
        }
        
    }
    
}
*/


int main() {
    int altura, largura;
    vector<vector<int>> pixels;

    FILE* fp;
    fp = fopen("balloons.ascii.pgm", "a");
    if (fp == NULL) {
        cout << "Erro ao abrir arquivo 'balloons.ascii.pgm'\n";
        return 1;
    }

    if (lerArquivo(fp, altura, largura, pixels)) {
        // Processa os pixels da imagem
        // ...
    }

    fclose(fp);

    return 0;
}