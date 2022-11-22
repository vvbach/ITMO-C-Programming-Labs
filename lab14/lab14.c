#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct BMP
{
    int width;
    int height;
    int size;
} BMP;

int Live(int** currentGen, int x, int y, int w, int h){
    int count = 0;
    for (int i = y - 1; i <= y + 1; i++){
        for (int j = x - 1; j <= x + 1; j++){
            if ((i == y && j == x) || (i < 0 || j < 0) || (i >= h || j >= w)){
                continue;
            }
            if(currentGen[i][j] == 1){
                count++;
            }
        }
    }
    if (currentGen[y][x]){
        if (count >= 2 && count <= 3) return 1;
        return 0;
    } else {
        if (count == 3) return 1;
        return 0;
    }
    
}

void GameOfLife(int **currentGen , int width, int height){
    int numOfLivingCells;
    int **nextGen = (int**)malloc(sizeof(int*) * height);
    for (int i = 0; i < height; i++){
        nextGen[i] = (int*)malloc(sizeof(int) * width);
    }

    int x, y;
    for (y = 0; y < height; y++){
        for (x = 0; x < width; x++){
            nextGen[y][x] = currentGen[y][x];
        }
    }
    for (y = 0; y < height; y++){
        for (x = 0; x < width; x++){
            if (Live(currentGen, x, y, width, height)){
                nextGen[y][x] = 1;
            }
            else {
                nextGen[y][x] = 0;
            }
        }
    }
    for (y = 0; y < height; y++){
        for (x = 0; x < width; x++){
            currentGen[y][x] = nextGen[y][x];
            
        }
        
    }
    for (int i = 0; i < height; i++){
        free(nextGen[i]);
    }
    free(nextGen);
}


int main(int argc, char* argv[]){
    BMP image;
    unsigned char *inputFile, *outputDir;
    int max_iter = 100;
    int dump_freq = 1;
    int i, j, padding;
    for (i = 1; i < argc; i++){
        if (strstr(argv[i], "--input")){
            inputFile = argv[i + 1];
        }
        else if (strstr(argv[i], "--output")){
            outputDir = argv[i + 1];
        }
        else if (strstr(argv[i], "--max_iter")){
            max_iter = atoi(argv[i + 1]);
        }
        else if (strstr(argv[i], "--dump_freq")){
            dump_freq = atoi(argv[i + 1]);
        }
    }

    FILE *f = fopen(inputFile, "rb");
    unsigned char header[54];
    fread(header, 54, 1, f);
    image.size = header[2] + (header[3] << 8) + (header[4] << 16) + (header[5] << 24);
    image.width = header[18] + (header[19] << 8) + (header[20] << 16) + (header[21] << 24);
    image.height = header[22] + (header[23] << 8) + (header[24] << 16) + (header[25] << 24);
    
    unsigned char* original = (unsigned char*)malloc((image.size - 54) * sizeof(unsigned char));
	fread(original, sizeof(unsigned char), image.size, f);

    int **data = (int**)malloc(image.height * sizeof(int*));
    for (i = 0; i < image.height; i++){
        data[i] = (int*)malloc(image.width * sizeof(int));
    }

    int k = 0;
    for (i = image.height - 1; i >= 0; i--) {
		for (j = 0; j < image.width; j++) {
			if (original[k] == 255){
				data[i][j] = 0;
            }
			else{
				data[i][j] = 1;
            }
			k += 3;
		}
        for (padding = 0; padding < (image.width * 3) % 4; padding++){
            k++;
        }
	}
    int byteCounter;
    for (int iter = 0; iter < max_iter; iter++){
        GameOfLife(data, image.width, image.height);
        if (iter % dump_freq != 0){
            continue;
        }
        char outputFile[20];
        char filepath[100] = "";
        strcat(filepath, outputDir);
        strcat(filepath, "/");
        strcat(filepath, itoa(iter, outputFile, 10));
        strcat(filepath, ".bmp");
        FILE *output = fopen(filepath, "wb");
        fwrite(header, 1, 54, output);
        
        byteCounter = 0;
        for (i = image.height - 1; i >= 0; i--) {
            for (j = 0; j < image.width; j++) {
                for (k = 0; k < 3; k++){
                    if (data[i][j] == 1){
                        original[byteCounter] = 0; 
                    }
                    else{
                        original[byteCounter] = 255; 
                    }
                    byteCounter++;
                } 
            }
            for (padding = 0; padding < (image.width * 3) % 4; padding++){
                original[byteCounter] = 0; 
                byteCounter++;
            }
        }
        fwrite(original, sizeof(unsigned char), image.size, output);
        fclose(output);
    }
    for (i = 0; i < image.height; i++) {
		free(data[i]);
	}
	free(data);
	free(original);
    return 0;
}