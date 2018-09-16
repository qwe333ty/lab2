//
#include "stdafx.h"
#include "draw.h"

#include <SDL.h> 
#include <math.h>
#include <stdio.h>

const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGTH = 700;

void drawLineBresenhamAlgorithm(int xFirst, int yFirst, int xSecond, int ySecond, SDL_Renderer *renderer);
void drawSquare(float *xCoordinate, float *yCoordinate, SDL_Renderer *renderer);
void changingCoordinatesXYForAllDots(float *xCoordinate, float *yCoordinate, float param);

int _tmain(int argc, char *args[])
{
	SDL_Window    *window;
	SDL_Renderer  *renderer;
	SDL_Event      event;
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGTH, 0, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

	const int numberOfFigures = 5;
	const float angleInRad = M_PI / 4 / numberOfFigures;
	const float param = (sin(angleInRad) / cos(angleInRad))
		/
		(1 + (sin(angleInRad) / cos(angleInRad)));
	float *xCoordinate = (float*)calloc(5, sizeof(float)),
		*yCoordinate = (float*)calloc(5, sizeof(float));

	xCoordinate[0] = 100; yCoordinate[0] = 100;
	xCoordinate[1] = 100; yCoordinate[1] = 600;
	xCoordinate[2] = 600; yCoordinate[2] = 600;
	xCoordinate[3] = 600; yCoordinate[3] = 100;
	xCoordinate[4] = 100; yCoordinate[4] = 100;

	for (int i = 0; i < numberOfFigures; i++) {
		drawSquare(xCoordinate, yCoordinate, renderer);
		changingCoordinatesXYForAllDots(xCoordinate, yCoordinate, param);
	}

	SDL_RenderPresent(renderer);
	bool flag = true;
	while (flag) {
		SDL_WaitEvent(&event);
		while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
			case SDL_QUIT:
				flag = false;
			}
		}
	}
	return 0;
}

void drawLineBresenhamAlgorithm(int xFirst, int yFirst, int xSecond, int ySecond, SDL_Renderer *renderer) {
	int dx = abs(xSecond - xFirst);
	int dy = abs(ySecond - yFirst);
	int sx = xSecond >= xFirst ? 1 : -1;
	int sy = ySecond >= yFirst ? 1 : -1;

	if (dy <= dx) {
		int d = (dy << 1) - dx;
		int d1 = dy << 1;
		int d2 = (dy - dx) << 1;

		SDL_RenderDrawPoint(renderer, xFirst, yFirst);
		for (int x = xFirst + sx, y = yFirst, i = 1; i <= dx; i++, x += sx) {
			if (d > 0) {
				d += d2;
				y += sy;
			}
			else
				d += d1;
			SDL_RenderDrawPoint(renderer, x, y);
		}
	}
	else {
		int d = (dx << 1) - dy;
		int d1 = dx << 1;
		int d2 = (dx - dy) << 1;

		SDL_RenderDrawPoint(renderer, xFirst, yFirst);
		for (int x = xFirst, y = yFirst + sy, i = 1; i <= dy; i++, y += sy) {
			if (d > 0) {
				d += d2;
				x += sx;
			}
			else
				d += d1;
			SDL_RenderDrawPoint(renderer, x, y);
		}
	}
}

void drawSquare(float *xCoordinate, float *yCoordinate, SDL_Renderer *renderer) {
	for (int i = 0; i < 4; i++) {
		drawLineBresenhamAlgorithm(xCoordinate[i], yCoordinate[i], xCoordinate[i + 1], yCoordinate[i + 1], renderer);
	}
}

void changingCoordinatesXYForAllDots(float *xCoordinate, float *yCoordinate, const float param) {
	for (int i = 0; i < 4; i++) {
		xCoordinate[i] = (1 - param)*xCoordinate[i] + param*xCoordinate[i + 1];
		yCoordinate[i] = (1 - param)*yCoordinate[i] + param*yCoordinate[i + 1];
	}
	xCoordinate[4] = xCoordinate[0];
	yCoordinate[4] = yCoordinate[0];
}