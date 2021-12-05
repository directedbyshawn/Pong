#include "shape.h"

point::point() : x(0), y(0) {}

point::point(double x, double y) : x(x), y(y) {}

color::color() : red(0), green(0), blue(0), alpha(0) {}

color::color(double r, double g, double b) : red(r), green(g), blue(b), alpha(1) {}

color::color(double r, double g, double b, double a) : red(r), green(g), blue(b), alpha(a) {}

Shape::Shape() : center({0, 0}), fill({0, 0, 0, 1}) {}

Shape::Shape(color fill) : center({0, 0}), fill(fill) {}

Shape::Shape(point center) : center(center), fill({0, 0, 0, 1}) {}

Shape::Shape(point center, color fill) : center(center), fill(fill) {}

color Shape::getColor() const {
    return fill;
}

void Shape::setColor(color fill) {
    fill = fill;
}

point Shape::getCenter() const {
    return center;
}

void Shape::setCenter(point center) {
    center = center;
}

double Shape::getCenterX() const {
    return center.x;
}

double Shape::getCenterY() const {
    return center.y;
}

void Shape::setCenterX(double x) {
    center.x = x;
}

void Shape::setCenterY(double y) {
    center.y = y;
}

void Shape::move(double deltaX, double deltaY) {
    center.x += deltaX;
    center.y += deltaY;
}
