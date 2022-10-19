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

void ellipsePlot(int Cx, int Cy, int x, int y)
{
	setPixel(Cx + x, Cy + y);//marking function according to the output device
	setPixel(Cx - x, Cy + y);
	setPixel(Cx + x, Cy - y);
	setPixel(Cx - x, Cy - y);
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
void rotation(int xCenter, int yCenter, int x, int y, double r) {
	int rx, ry;
	rx = (x - xCenter) * cos(r) - (y - yCenter) * sin(r) + xCenter;
	ry = (x - xCenter) * sin(r) + (y - yCenter) * cos(r) + yCenter;
	setPixel(rx, ry); //픽셀값 지정
}
void ellipsePlot(int xCenter, int yCenter, int x, int y, int r)
{ // ( rot 회전 픽셀함수 대신 ation ) 으로 변경
	rotation(xCenter, yCenter, xCenter + x, yCenter + y, r * (3.14 / 180));
	rotation(xCenter, yCenter, xCenter - x, yCenter + y, r * (3.14 / 180));
	rotation(xCenter, yCenter, xCenter + x, yCenter - y, r * (3.14 / 180));
	rotation(xCenter, yCenter, xCenter - x, yCenter - y, r * (3.14 / 180));
}
void rellipseMidpoint(int xCenter, int yCenter, int Rx, int Ry, int r)
{
	int Rx2 = Rx * Rx, Ry2 = Ry * Ry, twoRx2 = 2 * Rx2, twoRy2 = 2 * Ry2;
	int p, x = 0, y = Ry, px = 0, py = twoRx2 * y;
	//Region 1
	p = ROUND(Ry2 - (Rx2 * Ry) + (0.25 * Rx2));
	while (px < py) {
		x++;
		px += twoRy2;
		if (p < 0) p += Ry2 + px;
		else { y--; py -= twoRx2; p += Ry2 + px - py; }

		ellipsePlot(xCenter, yCenter, x, y, r);
	}
	//Region 2
	p = ROUND(Ry2 * (x + 0.5) * (x + 0.5) + Rx2 * (y - 1) * (y - 1) - Rx2 * Ry2);
	while (y > 0) {
		y--;
		py -= twoRx2;
		if (p > 0) p += Rx2 - py;
		else { x++; px += twoRy2; p += Rx2 - py + px; }

		ellipsePlot(xCenter, yCenter, x, y, r);
	}
}
void ellipseMidpoint(int xCenter, int yCenter, int Rx, int Ry, int r)
{
	int Rx2 = Rx * Rx, Ry2 = Ry * Ry, twoRx2 = 2 * Rx2, twoRy2 = 2 * Ry2;
	int p, x = 0, y = Ry, px = 0, py = twoRx2 * y;
	//Region 1
	p = ROUND(Ry2 - (Rx2 * Ry) + (0.25 * Rx2));
	while (px < py) {
		x++;
		px += twoRy2;
		if (p < 0) p += Ry2 + px;
		else { y--; py -= twoRx2; p += Ry2 + px - py; }

		ellipsePlot(xCenter, yCenter, x, y, r); // , 색 회전각 매개변수 추가
	}
	//Region 2
	p = ROUND(Ry2 * (x + 0.5) * (x + 0.5) + Rx2 * (y - 1) * (y - 1) - Rx2 * Ry2);
	while (y > 0) {
		y--;
		py -= twoRx2;
		if (p > 0) p += Rx2 - py;
		else { x++; px += twoRy2; p += Rx2 - py + px; }

		ellipsePlot(xCenter, yCenter, x, y, r);
	}
}

void main()
{
	FILE* fp;
	
	fp = fopen("eclipse.ppm", "wb");
	ellipseMidpoint(201, 202, 60, 105, 0);
	r = 255; g = 0; b = 0;
	ellipseMidpoint(201, 202, 60, 105, 90);
	r = 0; g = 0; b = 255;
	ellipseMidpoint(301, 502, 100, 65, 30);
	r = 255; g = 255; b = 0;
	ellipseMidpoint(301, 545, 100, 65, -30);
	r = 0; g = 255; b = 255;
	ellipseMidpoint(431, 352, 50, 400, 0);
	fprintf(fp, "P6\n");
	fprintf(fp, "%d %d\n", W, H);
	fprintf(fp, "255\n");

	fwrite(outImg, sizeof(char), H * W * 3, fp);
	fclose(fp);
}