#include <math.h>
#include <iostream>

using namespace std;


template<class T> class Vector
{
private:
  T x;
  T y;

public:
  Vector() {}

  Vector(T x1, T y1)
  {
    x = x1;
    y = y1;
  }


  T getX();
  T getY();

  void setX(T newX);
  void setY(T newY);

  void setVector(T newX, T newY);
  void setVector(Vector<T> vect);

  void add(Vector<T> other);
  void sub(Vector<T> other);
  void mult(Vector<T> other);
  void div(Vector<T> other);

  void add(double val);
  void sub(double val);
  void mult(double val);
  void div(double val);

  static Vector<T> * add(Vector<T> v1, Vector<T> v2);
  static Vector<T> * sub(Vector<T> v1, Vector<T> v2);
  static Vector<T> * mult(Vector<T> v1, Vector<T> v2);
  static Vector<T> * div(Vector<T> v1, Vector<T> v2);

  double getDis(Vector<T> other);

  void perp();

  double getMag();
  void normalize();
  void setMag(double mag);
  void limitMag(double mag);

  void turn(double rad);

  double getRad();

  void toString();

  static Vector<double>* radianToVector(double rad);
  static Vector<double>* degreeToVector(double ang);

  bool equal(Vector<T> * other);


};

//getters :

template<class T> T Vector<T>::getX() { return x; }
template<class T> T Vector<T>::getY() { return y; }

template<class T> double Vector<T>::getDis(Vector<T> other){
  return sqrt(pow(x - other.getX(), 2) + pow(y - other.getY(), 2));
}

template<class T> double Vector<T>::getMag() { return sqrt(pow(x, 2) + pow(y, 2)); }

//setters :

template<class T> void Vector<T>::setX(T newX) { x = newX; }
template<class T> void Vector<T>::setY(T newY) { y = newY; }

template<class T> void Vector<T>::setVector(T newX, T newY) { x = newX; y = newY; }
template<class T> void Vector<T>::setVector(Vector<T> vect) { x = vect.getX(); y = vect.getY(); }

// mutators :

template<class T> void Vector<T>::add(Vector<T> other) {
  x += other.getX();
  y += other.getY();
}

template<class T> void Vector<T>::sub(Vector<T> other) {
  x -= other.getX();
  y -= other.getY();
}

template<class T> void Vector<T>::mult(Vector<T> other) {
  x *= other.getX();
  y *= other.getY();
}

template<class T> void Vector<T>::div(Vector<T> other) {

  if( other.getX() != 0 ) { x /= other.getX(); }
  else { x = 0; }

  if( other.getY() != 0 ) { y /= other.getY(); }
  else { y = 0; }
}

// --

template<class T> void Vector<T>::add(double val) {
  y += val;
  x += val;
}

template<class T> void Vector<T>::sub(double val) {
  y -= val;
  x -= val;
}

template<class T> void Vector<T>::mult(double val) {
  y *= val;
  x *= val;
}

template<class T> void Vector<T>::div(double val) {
  if (val != 0) {
    y /= val;
    x /= val;
  }
  else { x = 0; y = 0; }
}

// --
template<class T> Vector<T> * Vector<T>::add(Vector<T> v1, Vector<T> v2) {
  T x = v1.getX() + v2.getX();
  T y = v1.getY() + v2.getY();

  return ( new Vector<T>(x, y) );
}

template<class T> Vector<T> * Vector<T>::sub(Vector<T> v1, Vector<T> v2) {
  T x = v1.getX() - v2.getX();
  T y = v1.getY() - v2.getY();

  return ( new Vector<T>(x, y) );
}

template<class T> Vector<T> * Vector<T>::mult(Vector<T> v1, Vector<T> v2) {
  T x = v1.getX() * v2.getX();
  T y = v1.getY() * v2.getY();

  return ( new Vector<T>(x, y) );
}

template<class T> Vector<T> * Vector<T>::div(Vector<T> v1, Vector<T> v2) {
  T x1, y1;
  if (v2.getX() != 0) { x1 = v1.getX() / v2.getX(); }
  else { x1 = 0;}

  if (v2.getY() != 0) { y1 = v1.getY() / v2.getY(); }
  else { y1 = 0;}

  return ( new Vector<T>(x1, y1) );
}

// --

template<class T> void Vector<T>::perp()
{
  T temp = y;
  y = -x;
  x = temp;
}

// --

template<class T> void Vector<T>::normalize() { div(getMag()); }
template<class T> void Vector<T>::setMag(double mag) { normalize(); mult(mag); }
template<class T> void Vector<T>::limitMag(double mag) {
  double selfMag = getMag();
  if(selfMag > mag) { div(selfMag); mult(mag); }
}

//--
template<class T> void Vector<T>::turn(double rad) {
  double new_x = (x * cos(rad)) - (y * sin(rad));
  double new_y = (x * sin(rad)) + (y * cos(rad));

  x = new_x;
  y = new_y;
}

//--
template<class T> double Vector<T>::getRad() {
  int flip = (int)(abs(x) / x) - 1;
  return atan(y / x) + ((M_PI / 2) * flip) - (M_PI / 2);
}


template<class T> Vector<double>* Vector<T>::radianToVector(double rad) { return new Vector<double>(cos(rad), sin(rad)); }
template<class T> Vector<double>* Vector<T>::degreeToVector(double ang) { return radianToVector((ang * M_PI) / 180.0); }

template<class T> bool Vector<T>::equal(Vector<T> * other) { return ( x == other->getX() && y == other->getY() ); }

template<class T> void Vector<T>::toString() { std::cout << "Vector:[x=" << x << ", y=" << y << "]"<< '\n';}
