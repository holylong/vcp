// Factory Pattern
// Design Pattern Modern C++ - Page 32
#include <memory>
#include <iostream>


// Virtual Product
class Shape {
public:
    virtual void draw() = 0;
};

// Actual Product Circle
class Circle : public Shape {
public:
    void draw() override {
        std::cout << "Circle::draw()" << std::endl;
    }
};

// Actual Product Square
class Square : public Shape {
public:
    void draw() override {
        std::cout << "Square::draw()" << std::endl;
    }
};

// Virtual Factory
class Factory{
public:
    virtual std::unique_ptr<Shape> createShape() = 0;
};

// Actual Factory Circle
class CircleFactory : public Factory {
public:
    std::unique_ptr<Shape> createShape() override {
        return std::make_unique<Circle>();
    }
};

// Actual Facotry Square
class SquareFactory : public Factory {
public:
    std::unique_ptr<Shape> createShape() override {
        return std::make_unique<Square>();
    }
};

int main(int argc, char* argv[]) {
    Factory* circleFactory = new CircleFactory();
    Factory* squareFactory = new SquareFactory();

    auto circle = circleFactory->createShape();
    auto square = squareFactory->createShape();

    circle->draw();
    square->draw();
}