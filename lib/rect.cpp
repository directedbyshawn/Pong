#include "rect.h"
#include "graphics.h"

dimensions::dimensions() : width(20), height(20) {}

dimensions::dimensions(double width, double height) : width(width), height(height) {}

Rect::Rect() : Shape(), size({20, 20}) {}

Rect::Rect(dimensions size) : Shape(), size(size), speed(0) {}

Rect::Rect(color fill) : Shape(fill), size({20, 20}), speed(0) {}

Rect::Rect(point center) : Shape(center), size({20, 20}), speed(0) {}

Rect::Rect(dimensions size, color fill) : Shape(fill), size(size), speed(0) {}

Rect::Rect(dimensions size, color fill, point center) : Shape(center, fill), size(size), speed(0) {}

dimensions Rect::getSize() const {
    return size;
}

void Rect::setSize(double width, double height) {
    size = {width, height};
}

double Rect::getWidth() const {
    return size.width;
}

void Rect::setWidth(double width) {
    size.width = width;
}

double Rect::getHeight() const {
    return size.height;
}

void Rect::setHeight(double height) {
    size.height = height;
}

void Rect::changeWidth(double deltaW) {
    size.width += deltaW;
}

void Rect::changeHeight(double deltaH) {
    size.height += deltaH;
}

double Rect::getLeftX() const {
    return center.x - size.width / 2;
}

double Rect::getRightX() const {
    return center.x + size.width / 2;
}

double Rect::getTopY() const {
    return center.y - size.height / 2;
}

double Rect::getBottomY() const {
    return center.y + size.height / 2;
}

int Rect::getSpeed() const {
    return speed;
}

void Rect::setSpeed(int speed) {
    speed = speed;
}

void Rect::draw() const {\
    // draw rectangle using OpenGL
    glBegin(GL_QUADS);
    glColor3f(getColor().red, getColor().green, getColor().blue);
    glVertex2f((int)getRightX(), (int)getTopY());
    glVertex2f((int)getLeftX(), (int)getTopY());
    glVertex2f((int)getLeftX(), (int)getBottomY());
    glVertex2f((int)getRightX(), (int)getBottomY());
    glEnd();
}


