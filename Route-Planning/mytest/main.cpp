// Example solution for Rectangle and Square friend classes
#include <assert.h>

// Declare class Rectangle
class Rectangle;

// Define class Square as friend of Rectangle
class Square {
public:
    Square(int s) : side_(s) {}
    friend class Rectangle;
private:
    int side_;
};

class Rectangle{
public:
    Rectangle(Square s) {
        width_ = s.side_;
        height_ = s.side_;
    }
    int Area() {
        return width_ * height_;
    }
private:
    int width_;
    int height_;
};

int main()
{
    Square square(4);
    Rectangle rectangle(square);
    assert(rectangle.Area() == 16);
}