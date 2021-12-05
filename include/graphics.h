#ifndef PONG_GRAPHICS_H
#define PONG_GRAPHICS_H

#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

enum Screen {START, PLAY, END};

// used to reset/initialize game settings
void initPlayers();
void initBall();
void initGame();

// renders game data to screen excluding player entities and ball
void printScores();
void printNames();
void printMidLine();

// lets the ball reflect off wall & paddles, changes position vector to keep
// it moving on the correct path. has some minor randomness to keep the game
// interesting.
void checkBallPath();

// moves ball every tick and performs reset and goal logic when necessary.
void ballTimer(int dummy);

// glut functions
void init();
void initGL();
void display();
void kbd(unsigned char key, int x, int y);
void kbdS(int key, int x, int y);
void cursor(int x, int y);
void mouse(int button, int state, int x, int y);

#endif //PONG_GRAPHICS_H
