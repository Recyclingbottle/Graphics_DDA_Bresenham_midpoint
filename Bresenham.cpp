#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define H 480
#define W 640

unsigned char outImg[H][W][3];
int r = 0, g = 255, b = 0;

void lineBres(int x1, int y1, int x2, int y2)
{
	int dx = abs(x2 - x1), dy = abs(y2 - y1);
	int p, twoDy, twoDyDx, twoDx;
	int x, y, xEnd, yEnd, IorD;

	if (dx > dy) {
		p = 2 * dy - dx; twoDy = 2 * dy; twoDyDx = 2 * (dy - dx);

		if (x1 > x2) { x = x2; y = y2; xEnd = x1; if (y1 - y2 > 0)IorD = 1; else IorD = -1; }
		else { x = x1; y = y1; xEnd = x2; if (y2 - y1 > 0)IorD = 1; else IorD = -1; }

		outImg[x][y][0] = r; outImg[x][y][1] = g; outImg[x][y][2] = b;// start point marking with a user-defined color(r,g,b) 

		while (x < xEnd) {
			x++;
			if (p < 0) p += twoDy;
			else { y += IorD; p += twoDyDx; }
			outImg[x][y][0] = r; outImg[x][y][1] = g; outImg[x][y][2] = b;//marking
		}// end of while
	}// end of if
	else {
		//You should complete this block....
		//Hint: The role of x has to be changed with that of y...
		p = 2 * dx - dy;  twoDx = 2 * dx; twoDyDx = 2 * (dx - dy);

		if (y1 > y2) { x = x2; y = y2; yEnd = y1; if (x1 - x2 > 0)IorD = 1; else IorD = -1; }
		else { x = x1; y = y1; yEnd = y2; if (x2 - x1 > 0)IorD = 1; else IorD = -1; }
		outImg[x][y][0] = r; outImg[x][y][1] = g; outImg[x][y][2] = b;

		while (y < yEnd) {
			y++;
			if (p < 0) p += twoDx;
			else { x += IorD; p += twoDyDx; }
			outImg[x][y][0] = r; outImg[x][y][1] = g; outImg[x][y][2] = b;//marking
		}// end of while

	}// end of else

}

void main()
{
	FILE* fp;

	lineBres(0, 0, 200, 10);
	r = 255; g = 0; b = 0;
	lineBres(0, 0, 10, 300);
	r = 0; g = 0; b = 255;
	lineBres(230, 100, 80, 10);
	r = 255; g = 255; b = 0;
	lineBres(40, 50, 100, 110);
	fp = fopen("bresenham.ppm", "wb");
	fprintf(fp, "P6\n");
	fprintf(fp, "%d %d\n", W, H);
	fprintf(fp, "255\n");

	fwrite(outImg, sizeof(char), H * W * 3, fp);
	fclose(fp);

}