#include "ball.h"
#include "graphics.h"

positionVector::positionVector() : x(0), y(0) {}

positionVector::positionVector(double x, double y) : x(x), y(y) {}

Ball::Ball() : Shape({0, 0}, {1, 1, 1}), radius(5), v({0, 0}) {}

Ball::Ball(double radius) : Shape({0, 0}, {1, 1, 1}), radius(radius), v({0, 0}) {}

Ball::Ball(double radius, point center) : Shape(center, {1, 1, 1}), radius(radius), v({0, 0}) {}

Ball::Ball(point center, double radius, positionVector v) : Shape(center, {1, 1, 1}), radius(radius), v(v) {}

Ball::Ball(point center, color fill, double radius) : Shape(center, fill), radius(radius), v({0, 0}) {}

Ball::Ball(point center, color fill, double radius, positionVector v) : Shape(center, fill), radius(radius), v(v) {};

double Ball::getRadius() const {
    return radius;
}

void Ball::setRadius(double radius) {
    radius = radius;
}

positionVector Ball::getVector() const {
    return v;
}

void Ball::setVector(double x, double y) {
    v.x = x;
    v.y = y;
}

void Ball::setVectorX(double x) {
    v.x = x;
}

void Ball::setVectorY(double y) {
    v.y = y;
}

double Ball::getLeftX() const {
    return center.x - radius;
}

double Ball::getRightX() const {
    return center.x + radius;
}

double Ball::getTopY() const {
    return center.y - radius;
}

double Ball::getBottomY() const {
    return center.y + radius;
}

void Ball::draw() const {
    // draw circle using OpenGL
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(getColor().red, getColor().green, getColor().blue);
    glVertex2i(center.x, center.y);
    for (double i = 0; i < 2.0*PI+0.05; i += (2.0*PI)/360.0) {
        glVertex2i(center.x + (radius * cos(i)),
                   center.y + (radius * sin(i)));
    }
    glEnd();
}
