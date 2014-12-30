/*
 *Author: Abdul Bezrati
 *Email : abezrati@hotmail.com
 */

#ifndef _Math_Tuple3_h_
#define _Math_Tuple3_h_

#include <cmath>
#include <float.h>
#include <iostream>
 
#include "Tuple2.h"
using namespace std;

template <class T>
class Tuple3
{
  public:
    Tuple3<T>(T nx = 0, T ny = 0, T nz = 0)
    {
      x = nx;
      y = ny;
      z = nz;
    }

    Tuple3<T>(T xyz)
    {
      x = 
      y = 
      z = xyz;
    }

    Tuple3<T>(const Tuple3<T>& source)
    {
      x = source.x;
      y = source.y;
      z = source.z;
    }

    Tuple3<T>(const Tuple2<T>& source, const T Z){
      x = source.x;
      y = source.y;
      z = Z;
    }

    inline Tuple3<T>& operator = (const Tuple3<T>& right){
      x = right.x;
      y = right.y;
      z = right.z;
      return *this;
    }
 
    inline Tuple3<T> operator + (const Tuple3<T>& right){
      return Tuple3(right.x + x, right.y + y, right.z + z);
    }
 
    inline Tuple3<T> operator - (const Tuple3<T>& right){
      return Tuple3<T>(-right.x + x, -right.y + y, -right.z + z);
    }
 
    inline Tuple3<T> operator * (const T scale){
      return Tuple3<T>(x*scale, y*scale, z*scale);
    }
 
    inline Tuple3<T>  operator / (const T scale){
      return scale ? Tuple3f<T>(x/scale, y/scale, z/scale); Tuple3<T>(0, 0, 0);
    }

    inline Tuple3<T>& operator += (const Tuple3<T>& right)
    {
      x+=right.x;
      y+=right.y;
      z+=right.z;
      return *this;
    }

    inline Tuple3<T>& operator += (const T xyz)
    {
      x += xyz;
      y += xyz;
      z += xyz;
      return *this;
    }

    inline Tuple3<T>& operator -= (const Tuple3<T>& right)
    {
      x-=right.x;
      y-=right.y;
      z-=right.z;
      return *this;
    }

    inline Tuple3<T>& operator -= (const T xyz)
    {
      x -= xyz;
      y -= xyz;
      z -= xyz;
      return *this;
    }

    inline Tuple3<T>& operator *= (const T scale) 
    {
      x*=scale;
      y*=scale;
      z*=scale;
      return *this;
    }

    inline Tuple3<T>& operator /= (const T scale)
    {
      if(scale) 
	    {
        x/=scale;
        y/=scale;
        z/=scale;
      }
      return *this;
    }

    bool operator == (const Tuple3& right)
    {
      return (x == right.x &&
              y == right.y &&
              z == right.z);
    }

    bool operator != (const Tuple3& right)
    {
      return !(x == right.x &&
               y == right.y &&
               z == right.z);
    }

    inline operator const T*() const { return &x; }
    inline operator T*() { return &x; }   

	  inline const T  operator[](int i) const { return ((T*)&x)[i]; }
	  inline       T& operator[](int i)       { return ((T*)&x)[i]; }

    inline void set(const T nx, const T ny, const T nz)
    {
      x = nx;
      y = ny;
      z = nz;
    }

    inline void set(const T xyz)
    {
      x =   
      y =  
      z = xyz;
    }

    inline void set(const Tuple3<T>&  t)
    {
      x = t.x;
      y = t.y;
      z = t.z;
    }

    inline Tuple3<T>& normalize()
    {
      T length  = getLength();

      if(!length)
      {
        set(0,0,0);
        return *this;
      }
      x/=length;
      y/=length;
      z/=length;
      return *this;
    }

    inline const T getLengthSquared() const { return  x*x + y*y + z*z; }
    inline const T getLength()        const { return sqrtf(x*x + y*y + z*z); }

    inline const T getDotProduct(const Tuple3<T>& t) const
    {
      return x*t.x + y*t.y + z*t.z;
    }

    inline Tuple3<T> operator ^(const Tuple3<T>& t)
    {
      return Tuple3<T>(y   * t.z - z   * t.y,
                       t.x * z   - t.z * x,
                       x   * t.y - y   * t.x);
    }  

    inline Tuple3<T>& operator ^=(const Tuple3<T>& t)
    {
       set(y   * t.z - z   * t.y,
           t.x * z   - t.z * x,
           x   * t.y - y   * t.x);
       return *this;
    }

    inline Tuple3<T>& crossProduct(const Tuple3<T>& t1, const Tuple3<T>& t2)
    {
      set(t1.y * t2.z - t1.z * t2.y,
          t2.x * t1.z - t2.z * t1.x,
          t1.x * t2.y - t1.y * t2.x);
      return *this;
    }

    inline const T getDistance(const Tuple3<T>& v2)  const 
    {
      return sqrtf((v2.x - x) * (v2.x - x) +
                   (v2.y - y) * (v2.y - y) +
                   (v2.z - z) * (v2.z - z));
    }

    inline const T getAngle(const Tuple3<T>& v2)  const 
    {             
              
      T angle = acos(getDotProduct(v2) / (getLength() * v2.getLength()));
      if(_isnan(angle))
        return 0;
      return angle ;
    }

    inline Tuple3<T>& clamp(T min, T max)
    {
      x = x > max ? max : x < min ? min  : x;
      y = y > max ? max : y < min ? min  : y;
      z = z > max ? max : z < min ? min  : z;
      return *this;
    }

    friend ostream&  operator << ( ostream&  out, const Tuple3<T>& right){
      return out << "Tuple(" << right.x << ", " << right.y << ", " << right.z <<")";
    }

    friend istream&  operator >> (istream&  in, Tuple3<T>& right){
      return in >> right.x >> right.y >> right.z;
    }
    T x, y, z;
};

typedef Tuple3<int>           Tuple3i;
typedef Tuple3<float>         Tuple3f;
typedef Tuple3<double>        Tuple3d;
typedef Tuple3<char>          Tuple3b;
typedef Tuple3<unsigned char> Tuple3ub;
#endif
