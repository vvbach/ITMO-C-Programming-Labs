#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void GameLife(int** life, int hei, int wid) {
	int N;
	int** tmp = (int**)malloc(sizeof(int*) * hei);
	for (int i = 0; i < hei; ++i) {
		tmp[i] = (int*)malloc(sizeof(int) * wid);
	}
	int x, y;
	int inf = 0;
	for (y = 0; y < hei; y++)
		for (x = 0; x < wid; x++)
			tmp[y][x] = life[y][x];
	for (y = 1; y < hei - 1; y++) {
		for (x = 1; x < wid - 1; x++) {
			N = life[y + 1][x - 1] + life[y + 1][x] + life[y + 1][x + 1] + life[y][x - 1] + life[y][x + 1] + life[y - 1][x - 1] + life[y - 1][x] + life[y - 1][x + 1];
			if (tmp[y][x] == 1) {
				if (N == 2) tmp[y][x] = life[y][x];
				if (N == 3) tmp[y][x] = life[y][x];
				if (N > 3) tmp[y][x] = 0;
				if (N < 2) tmp[y][x] = 0;
			}
			else {
				if (N == 3) tmp[y][x] = 1;
			}
			N = 0;
		}
	}
	for (y = 0; y < hei; y++)
		for (x = 0; x < wid; x++) {
			if (life[y][x] == tmp[y][x])
				inf++;
			life[y][x] = tmp[y][x];
		}
	for (int i = 0; i < hei; ++i) {
		free(tmp[i]);
	}
	free(tmp);
	if (inf == hei * wid)
		exit(0);
}

struct Bmp {
	int Width;
	int Height;
	int Size;
};

int main(int argc, char* argv[]) {
	struct Bmp Image;
	unsigned char header[54];
	int i, j, k, l, m;
	int maxiter = 100, dumpfreq = 1;
	char* dirname = NULL;
	FILE* file = NULL;

	//GAME SETTING

	for (i = 0; i < argc; i++) {
		if (!strcmp("--input", argv[i])) {
			file = fopen(argv[1 + 1], "rb");
		}
		if (!strcmp("--output", argv[i])) {
			dirname = argv[i + 1];
		}
		if (!strcmp("--max_iter", argv[i])) {
			maxiter = strtol(argv[i + 1], 0, 10);
		}
		if (!strcmp("--dump_freq", argv[i])) {
			dumpfreq = strtol(argv[i + 1], 0, 10);
		}
	}

	//READ IMAGE SIZE, HEIGHT, WIDTH, BYTE
	fread(header, sizeof(unsigned char), 54, file);
	Image.Width = header[21] * 256 * 256 * 256 + header[20] * 256 * 256 + header[19] * 256 + header[18];
	Image.Height = header[25] * 256 * 256 * 256 + header[24] * 256 * 256 + header[23] * 256 + header[22];
	Image.Size = header[5] * 256 * 256 * 256 + header[4] * 256 * 256 + header[3] * 256 + header[2];
	unsigned char* imagebyte = (unsigned char*)malloc((Image.Size - 54) * sizeof(unsigned char));
	fread(imagebyte, sizeof(unsigned char), Image.Size, file);

	int** img = (int**)malloc(Image.Height * sizeof(int*));
	for (i = 0; i < Image.Height; i++)
		img[i] = (int*)malloc(Image.Width * sizeof(int));

	//int w4 = Image.Width % 4;
	//MAKE TO ONE-ZERO ARRAY
	//k = -w4;
	k = 0;
	for (i = Image.Height - 1; i >= 0; i--) {
		//k += w4;
		for (j = 0; j < Image.Width; j++) {
			if (imagebyte[k] == 255)
				img[i][j] = 0;
			else
				img[i][j] = 1;
			k += 3;
		}
	}

	for (l = 1; l <= maxiter; l++) {
		//GameLife(img, Image.Height, Image.Width);

		if (l % dumpfreq != 0) continue;

		char way[256];
		char filename[16];
		strcpy(way, dirname);
		strcat(way, "\\");
		strcat(way, _itoa(l, filename, 10));
		strcat(way, ".bmp");
		FILE* life = fopen(way, "wb");
		fwrite(header, 1, 54, life);
		m = 0;
		// MAKE BITMAP
		for (i = Image.Height - 1; i >= 0; i--) {
			for (j = 0; j < Image.Width; j++) {
				for (k = 0; k < 3; k++) {
					if (img[i][j] == 1)
						imagebyte[m] = 0;
					else
						imagebyte[m] = 255;
					m++;
				}
			}
			// while (m % 4 != 0) {
			// 	imagebyte[m] = 0;
			// 	m++;
			// }
		}
		fwrite(imagebyte, sizeof(unsigned char), Image.Size, life);
		fclose(life);
	}

	for (i = 0; i < Image.Height; i++) {
		free(img[i]);
	}
	free(img);
	free(imagebyte);
	return 0;
}