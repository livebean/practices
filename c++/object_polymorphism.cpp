#include <iostream>

using namespace std;

class Sharp {
  protected:
    int width, height;

  public:
    Sharp(int w = 0, int h = 0 ) {
      width = w;
      height = h;
    }

    int area() {
      cout << "Parent class area : " << endl;
      return 0;
    }
};

class Rectangle : public Sharp {
  public:
    Rectangle(int w = 0, int h = 0) : Sharp( w, h) {}

    int area(){
      cout << "Rectangle class area : " << endl;
      return (width * height);
    }
};

class Triangle : public Sharp {
  public:
    Triangle(int a = 0, int b = 0 ) : Sharp(a, b) {}

    int area() {
      cout << "Triangle class area : " << endl;
      return (width * height / 2);
    }
};

int main() {
  Sharp *sharp;
  Rectangle rec(10, 7);
  Triangle tri(10, 5);

  sharp = &rec;
  sharp -> area();

  sharp = &tri;
  sharp -> area();

  return 0;
}