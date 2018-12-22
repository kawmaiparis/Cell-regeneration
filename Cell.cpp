#include <iostream>
#include <algorithm>

using namespace std;

class Cell {
 private:
  char thisCharacter = 'O';
 protected:
  char token;

 public:

  Cell() {}

  Cell(bool alive) {
    if (alive) {
      this->token = thisCharacter;
    }
    else {
      this->token = '.';
    }
  }

  virtual void kill() {
    this->token = '.';
  }

  virtual void respawn() {
    this->token = thisCharacter;
  }

  virtual char getToken() {
    return this->token;
  }

  virtual bool isAlive() {
    return this->token == thisCharacter;
  }
};

class CancerCell : public Cell {
 private:
  char thisCharacter = 'X';
 public:
  CancerCell(bool b) : Cell(b) {
  }
};
//
//template<int XValue=1>
//struct A {
//  static const int X = XValue;
//  static void printX() {std::cout << "X " << X << std::endl; };
//};
//
//template<int XValue=2>
//struct B: public A<XValue> {
//};
//
//struct C: public B<3> {
//};
//
//int main(int, char**){
//  B<> b;
//  b.printX();
//}

