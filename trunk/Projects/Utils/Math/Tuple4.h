/*
 *Author: Abdul Bezrati
 *Email : abezrati@hotmail.com
 */

#ifndef _Math_Tuple4_h_
#define _Math_Tuple4_h_


#include <iostream>
#include "Tuple3.h"

using namespace std;

template <class type>

class Tuple4
{
  public:
    Tuple4<type>(type X = 0, type Y = 0, type Z = 0, type W = 0)
    {
      x = X;
      y = Y;
      z = Z;
      w = W;
    }

    Tuple4<type>(type XYZW)
    {
      x =  
      y =  
      z =  
      w = XYZW;
    }

    Tuple4<type>(const Tuple4<type>& source)
    {
      x = source.x;
      y = source.y;
      z = source.z;
      w = source.w;
    }
 
    Tuple4<type>(const Tuple3<type>& source, const type W = 1)
    {
      x = source.x;
      y = source.y;
      z = source.z;
      w = W;
    }

    inline operator const type*() const { return& x; }
    inline operator type*() { return& x; }   

	  inline const type  operator[](int i) const { return ((type*)&x)[i]; }
	  inline       type& operator[](int i)       { return ((type*)&x)[i]; }
 
    inline Tuple4<type>& operator = (const Tuple4<type>& source){
      x = source.x;
      y = source.y;
      z = source.z;
      w = source.w;
      return *this;
    }

    inline Tuple4<type>& operator = (const Tuple3<type>& source)
    {
      x = source.x;
      y = source.y;
      z = source.z;
      w = 1.0f;
      return *this;
    }

    inline Tuple4<type> operator + (const Tuple4<type>& right){
      return Tuple4<type>(right.x + x, right.y + y, right.z + z, right.w + w );
    }

    inline Tuple4<type> operator - (const Tuple4<type>&  right){
      return Tuple4<type>(-right.x + x, -right.y + y, -right.z + z, -right.w + w );
    }

    inline Tuple4<type> operator * (const type scale){
      return Tuple4<type>(x*scale, y*scale, z*scale, w*scale);
    }

    inline Tuple4<type> operator / (const type scale){
       return scale ? Tuple4<type>(x/scale, y/scale, z/scale, w/scale) : Tuple4<type>(0, 0, 0, 0);
    }

    inline Tuple4<type>& operator += (const Tuple4<type>& right)
    {
      x +=right.x;
      y +=right.y;
      z +=right.z;
      w +=right.w;
      return *this;
    }

    inline Tuple4<type> operator -= (const Tuple4<type>& right)
    {
      x-=right.x;
      y-=right.y;
      z-=right.z;
      w-=right.w;
      return *this;
    }

    inline Tuple4<type> clamp(const type min, const type max)
    {
      x = x < min ? min : x > max ? max : x;
      y = y < min ? min : y > max ? max : y;
      z = z < min ? min : z > max ? max : z;
      w = w < min ? min : w > max ? max : w;
      return *this;
    }

    inline Tuple4<type> operator *= (const type scale)
    {
      x*=scale;
      y*=scale;
      z*=scale;
      w*=scale;
      return *this;
    } 

    inline Tuple4<type> operator /= (const type scale)
    {
      if(scale)
      {
        x/=scale;
        y/=scale;
        z/=scale;
        w/=scale;
      }
      return *this;
    }

    inline bool operator == (const Tuple4<type>& right){
      return (x == right.x &&
              y == right.y &&
              z == right.z &&
              w == right.w);
    }

    bool operator != (const Tuple4<type>& right){
      return !(x == right.x &&
               y == right.y &&
               z == right.z &&
               w == right.w);
    }

    inline void set(type xyzw)
    {
      x = 
      y =  
      z =  
      w = xyzw;
    }

    inline void set(type nx, type ny, type nz, type nw)
     {
      x = nx;
      y = ny;
      z = nz;
      w = nw;
    }

    inline void set(const Tuple4<type>&   vec)
    {
      x = vec.x;
      y = vec.y;
      z = vec.z;
      w = vec.w;   
    }

    inline void set(const Tuple3<type>&   vec, const type W = 1){
      x = vec.x;
      y = vec.y;
      z = vec.z;
      w = W;   
    }

      friend ostream&  operator<< ( ostream&  out, const Tuple4<type>&  right){
      return out << "Tuple4( " << right.x
                               << ", "
                               << right.y
                               << ", "
                               << right.z
                               << ", "
                               << right.w
                               << ")\n";
    }

    type x, y, z, w;
};

typedef Tuple4<int   > Tuple4i;
typedef Tuple4<float > Tuple4f;
typedef Tuple4<double> Tuple4d;

#endif
