#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "shape.h"
#include "rect.h"
#include "ball.h"

#include "graphics.h"

using namespace std;

GLdouble width, height;
int wd;

const color black(0.0, 0.0, 0.0);
const color white(1.0, 1.0, 1.0);

// game settings & data
Screen screen;
vector<int> score;
double random;
double multiplier;
double vertBounds = 60;
int maxScore = 5;
bool goalFlag = false;
bool resetFlag = false;
bool playSound = false;
bool firstGame;
int goalTimer;
int resetTimer;
string p1Score;
string p2Score;
string winner;
string startMessage = "Welcome to pong! Press the spacebar to play!";
string endMessage;

// game entities
Rect player1;
Rect player2;
Ball ball;
vector<Shape*> gameEntities;

void initPlayers() {

    // two identical paddles on opposite sides of screen
    player1 = Rect({5, 40}, white, {width / 2 - 350, height / 2});
    player2 = Rect({5, 40}, white, {width / 2 + 350, height / 2});

}

void initBall() {

    // ball is initialized and is given a position vector that is somewhat random to
    // keep the game interesting.

    ball = Ball({width / 2, height / 2}, white, 8);

    // position vector and general path decided
    int genPath = rand() % 4;
    int specX = rand() % 3 + 4;
    int specY = rand() % 3 + 6;

    if (genPath == 0) {
        ball.setVector(-1*specX, specY);
    }
    else if (genPath == 1) {
        ball.setVector(-1*specX, -1*specY);
    }
    else if (genPath == 2) {
        ball.setVector(specX, specY);
    }
    else {
        ball.setVector(specX, -1*specY);
    }

}

void initGame() {

    // game data is initialized and entities are added to their vector
    screen = START;
    score.push_back(0);
    score.push_back(0);
    gameEntities.push_back(&player1);
    gameEntities.push_back(&player2);
    gameEntities.push_back(&ball);

}

void printNames() {

    // renders player names above their scores

    string playerOne = "Player 1";
    string playerTwo = "Player 2";

    glColor3f(1, 1, 1);
    glRasterPos2i((width / 4) - (4*playerOne.length()), 30);
    for (const char &c : playerOne) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glColor3f(1, 1, 1);
    glRasterPos2i(width - (width / 4) - (4*playerTwo.length()), 30);
    for (const char &c : playerTwo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

}

void printScores() {

    // convert scores to strings
    p1Score = to_string(score[0]);
    p2Score = to_string(score[1]);

    // print player 1 score
    glColor3f(1, 1, 1);
    glRasterPos2i((width / 4) - (4*p1Score.length()), 50);
    for (const char &c : p1Score) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    // print player 2 scoer
    glColor3f(1, 1, 1);
    glRasterPos2i((width - (width / 4)) - (4*p2Score.length()), 50);
    for (const char &c : p2Score) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

}

void printMidLine() {

    // draws midline down center of screen

    double lineWidth = 3;
    double lineHeight = 10;
    point center = {width / 2, lineHeight / 2};
    Rect midLine;
    while (center.y <= height) {
        midLine = Rect({lineWidth, lineHeight}, white, center);
        midLine.draw();
        center.y += lineHeight + lineHeight / 2;
    }

}

void checkBallPath() {

    // ball hit ceiling or floor and needs to be redirected
    if (ball.getTopY() < vertBounds || ball.getBottomY() > height - vertBounds) {

        if (playSound) {
            PlaySound("../sounds/wall.wav", NULL, SND_ASYNC|SND_FILENAME);
        }

        // position vector is reflected on the y axis and is somewhat random to keep
        // game interesting
        random = (double)((rand() % 25) + 90);
        multiplier = -1 * (random / 100);
        ball.setVectorY(multiplier*ball.getVector().y);

        // ball is moved away from boundary, necessary to prevent bug where ball
        // gets stuck in state of thinking it has hit a boundary
        if (ball.getVector().y < 0.0) {
            ball.move(0, -20.0);
        }
        else {
            ball.move(0, 20.0);
        }

    }
    else if (ball.getLeftX() < player1.getRightX()) {

        // ball crossed left player, see if the ball and the square are overlapping
        // conditions for if ball hit the pad or not

        bool conditionOne = ball.getBottomY() >= player1.getTopY() && ball.getTopY() <= player1.getTopY();
        bool conditionTwo = ball.getBottomY() >= player1.getTopY() && ball.getBottomY() <= player1.getBottomY();
        bool conditionThree = ball.getTopY() <= player1.getBottomY() && ball.getBottomY() >= player1.getBottomY();

        if (conditionOne || conditionTwo || conditionThree) {
            // ball has hit the left paddle
            if (playSound) {
                PlaySound("../sounds/paddle.wav", NULL, SND_ASYNC|SND_FILENAME);
            }
            ball.setVectorX(-1 * ball.getVector().x);
            ball.move(3, 0);
        }
        else {
            // ball has passed paddle, goal for player 2
            goalFlag = true;
            score[1]++;
        }

    }
    else if (ball.getRightX() > player2.getLeftX()) {

        // ball crossed right player, see if the ball and the square are overlapping
        // conditions for if ball hit the pad or not

        bool conditionOne = ball.getBottomY() >= player2.getTopY() && ball.getTopY() <= player2.getTopY();
        bool conditionTwo = ball.getBottomY() >= player2.getTopY() && ball.getBottomY() <= player2.getBottomY();
        bool conditionThree = ball.getTopY() <= player2.getBottomY() && ball.getBottomY() >= player2.getBottomY();

        if (conditionOne || conditionTwo || conditionThree) {
            // ball has hit the right paddle
            if (playSound) {
                PlaySound("../sounds/paddle.wav", NULL, SND_ASYNC|SND_FILENAME);
            }
            ball.setVectorX(-1 * ball.getVector().x);
            ball.move(-3, 0);
        }
        else {
            // ball has passed paddle, goal for player 1
            goalFlag = true;
            score[0]++;
        }

    }

}

void ballTimer(int dummy) {
    if (screen == PLAY) {
        // set off when ball gets past paddle
        if (goalFlag) {
            goalTimer++;
            // timeout
            if (goalTimer > 40) {
                if (playSound) {
                    PlaySound("../sounds/goal.wav", NULL, SND_ASYNC|SND_FILENAME);
                }
                // reset flags and reset paddles & ball to initial positions
                goalFlag = false;
                resetFlag = true;
                goalTimer = 0;
                initBall();
                initPlayers();
            }
            // keep ball moving so it flys past paddle
            ball.move(ball.getVector().x, ball.getVector().y);
        }
        // reset flag gives player time to get ready before ball launches
        if (resetFlag) {
            resetTimer++;
            if (resetTimer > 70) {
                resetFlag = false;
                resetTimer = 0;
            }
        }
        // ball moves normally if goal hasnt occured
        if (!resetFlag && !goalFlag) {
            ball.move(ball.getVector().x, ball.getVector().y);
        }

    }
    glutPostRedisplay();
    glutTimerFunc(30, ballTimer, dummy);
}

void init() {

    //  sets window dimensions and initializes game settings & data

    width = 800;
    height = 600;
    srand(time(0));
    initPlayers();
    initBall();
    initGame();

}

void initGL() {

    // sets background color of window
    glClearColor(0, 0, 0, 1);

}

void display() {

    // OpenGL settings
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

    glClear(GL_COLOR_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // determines which screen game is currently on and renders appropriate data
    if (screen == START) {
        // renders start message to screen
        glColor3f(1, 1, 1);
        glRasterPos2i((width / 2) - (4*startMessage.length()), height / 2);
        for (const char &c : startMessage) {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
        }
        firstGame = true;
    }
    else if (screen == PLAY) {
        // render game data each tick
        if (firstGame) {
            firstGame = false;
            resetFlag = true;
        }
        if (!goalFlag) {
            checkBallPath();
        }
        printMidLine();
        printScores();
        printNames();
        for (Shape* entity : gameEntities) {
            entity->draw();
        }
        if (!goalFlag) {
            // determines if score limit has been reached
            if (score[0] >= maxScore || score[1] >= maxScore) {
                screen = END;
                if (score[0] > score[1]) {
                    winner = "Player 1";
                }
                else {
                    winner = "Player 2";
                }
            }
        }
    }
    else if (screen == END) {
        // prints end message with winner
        endMessage = "Game over! " + winner + " won the game!";
        glColor3f(1, 1, 1);
        glRasterPos2i((width / 2) - (4*endMessage.length()), height / 2);
        for (const char &c : endMessage) {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
        }
    }
    else {
        glutDestroyWindow(wd);
        exit(0);
    }

    glFlush();

}

void kbd(unsigned char key, int x, int y) {
    // player 1 moves up
    if (key == 'w') {
        if (screen == PLAY) {
            if (player1.getTopY() > vertBounds) {
                player1.move(0, -20);
            }
        }
    }
    // player 1 moves down
    if (key == 's') {
        if (screen == PLAY) {
            if (player1.getBottomY() < height - vertBounds) {
                player1.move(0, 20);
            }
        }
    }
    // toggle sound
    if (key == 'p') {
        if (playSound) {
            playSound = false;
        }
        else {
            playSound = true;
        }
    }
    // spacebar to start game
    if (key == 32) {
        if (screen == START) {
            screen = PLAY;
        }
    }
    // esc to exit game at any time
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }
    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    // player 2 moves up
    if (key == GLUT_KEY_UP) {
        if (screen == PLAY) {
            if (player2.getTopY() > vertBounds) {
                player2.move(0, -20);
            }
        }
    }
    // player 2 moves down
    if (key == GLUT_KEY_DOWN) {
        if (screen == PLAY) {
            if (player2.getBottomY() < height - vertBounds) {
                player2.move(0, 20);
            }
        }
    }
    glutPostRedisplay();
}

void cursor(int x, int y) {
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    glutPostRedisplay();
}

int main(int argc, char** argv) {

    init();

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(500, 200);

    wd = glutCreateWindow("pong");

    glutDisplayFunc(display);

    initGL();

    glutKeyboardFunc(kbd);
    glutSpecialFunc(kbdS);
    glutPassiveMotionFunc(cursor);
    glutMouseFunc(mouse);

    glutTimerFunc(0, ballTimer, 0);

    glutMainLoop();

    return 0;
}
