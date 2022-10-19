#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define H 480
#define W 640

unsigned char outImg[H][W][3];
int r = 0, g = 255, b = 0;
void lineDDA(int x1, int y1, int x2, int y2, int linetype)
{
	int dx = x2 - x1, dy = y2 - y1, step, k;
	float xinc, yinc, x = (float)x1, y = (float)y1;

	if (abs(dx) > abs(dy)) step = abs(dx);
	else step = abs(dy);
	xinc = dx / (float)step;
	yinc = dy / (float)step;

	outImg[x1][y1][0] = r; // start pixel marking(setpixel function)
	outImg[x1][y1][1] = g;
	outImg[x1][y1][2] = b;
	switch (linetype)
	{
	case 1: //실선
		for (k = 0; k < step; k++) {
			x += xinc;
			y += yinc;
			outImg[(int)(x + 0.5)][(int)(y + 0.5)][0] = 255;// marking(setpixel function)
			outImg[(int)(x + 0.5)][(int)(y + 0.5)][1] = 255;
			outImg[(int)(x + 0.5)][(int)(y + 0.5)][2] = 255;
		}
		break;
	case 2: //파선
		for (k = 0; k < step; k++) {
			x += xinc;
			y += yinc;
			if (k % 4 == 0) {
				outImg[(int)(x + 0.5)][(int)(y + 0.5)][0] = 0;// marking(setpixel function)
				outImg[(int)(x + 0.5)][(int)(y + 0.5)][1] = 0;
				outImg[(int)(x + 0.5)][(int)(y + 0.5)][2] = 0;
			}
			else
			{
				outImg[(int)(x + 0.5)][(int)(y + 0.5)][0] = 255;// marking(setpixel function)
				outImg[(int)(x + 0.5)][(int)(y + 0.5)][1] = 0;
				outImg[(int)(x + 0.5)][(int)(y + 0.5)][2] = 0;
			}

		}
		break;
	case 3: //점선
		for (k = 0; k < step; k++) {
			x += xinc;
			y += yinc;
			if (k % 2 == 0 ) {
				outImg[(int)(x + 0.5)][(int)(y + 0.5)][0] = 0;// marking(setpixel function)
				outImg[(int)(x + 0.5)][(int)(y + 0.5)][1] = 0;
				outImg[(int)(x + 0.5)][(int)(y + 0.5)][2] = 0;
			}
			else
			{
				outImg[(int)(x + 0.5)][(int)(y + 0.5)][0] = 0;// marking(setpixel function)
				outImg[(int)(x + 0.5)][(int)(y + 0.5)][1] = 0;
				outImg[(int)(x + 0.5)][(int)(y + 0.5)][2] = 255;
			}

		}
		break;
	default:
		printf("TYPE ERROR \n");
	}
	
}

void main()
{
	FILE* fp;

	lineDDA(0, 0, H - 1, W - 1, 1);
	lineDDA(400, 100, 100, 400, 2);
	lineDDA(80, 60, 230, 210, 3);
	fp = fopen("DDA.ppm", "wb");
	fprintf(fp, "P6\n");
	fprintf(fp, "%d %d\n", W, H);
	fprintf(fp, "255\n");

	fwrite(outImg, sizeof(char), H * W * 3, fp);
	fclose(fp);

}