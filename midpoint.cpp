#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define H 480
#define W 640
#define ROUND(x) (int)(x+0.5)
unsigned char outImg[H][W][3];
int r = 0, g = 255, b = 0;
void setPixel(int x, int y) {
	//만들어라.
	outImg[x][y][0] = r;
	outImg[x][y][1] = g;
	outImg[x][y][2] = b;
}
void circlePlot(int Cx, int Cy, int x, int y)
{
	setPixel(Cx + x, Cy + y);//marking function according to the output device
	setPixel(Cx - x, Cy + y);
	setPixel(Cx + x, Cy - y);
	setPixel(Cx - x, Cy - y);
	setPixel(Cx + y, Cy + x);
	setPixel(Cx - y, Cy + x);
	setPixel(Cx + y, Cy - x);
	setPixel(Cx - y, Cy - x);
}


void circleMidpoint(int xCenter, int yCenter, int radius)
{
	int x = 0, y = radius, p = 1 - radius;

	circlePlot(xCenter, yCenter, x, y);//start pixel marking..

	while (x <= y) {
		x++;
		if (p < 0) p += 2 * x + 1;
		else { y--; p += 2 * (x - y) + 1; }

		circlePlot(xCenter, yCenter, x, y);//marking..
	}
}


void main()
{
	FILE* fp;

	fp = fopen("circle.ppm", "wb");
	circleMidpoint(101, 151, 60);
	r = 255;
	circleMidpoint(201, 202, 30);
	g = 0; b = 255; r = 0;
	circleMidpoint(100, 400, 80);

	fprintf(fp, "P6\n");
	fprintf(fp, "%d %d\n", W, H);
	fprintf(fp, "255\n");

	fwrite(outImg, sizeof(char), H * W * 3, fp);
	fclose(fp);
}