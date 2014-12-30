/*
 *Author: Abdul Bezrati
 *Email : abezrati@hotmail.com
 */

#ifndef _Math_Tuple2_h_
#define _Math_Tuple2_h_

template <class T2>
class Tuple2
{
  public:
    Tuple2(T2 X = 0, T2 Y = 0)
    {
      x = X;
      y = Y;
    }

    Tuple2(const Tuple2<T2>& source)
    {
      x = source.x;
      y = source.y;
    }

    Tuple2<T2>& operator = (const Tuple2& right){
      x = right.x;
      y = right.y;
      return *this;
    }

    inline Tuple2<T2> operator + (const Tuple2<T2>& right)
    {
      return Tuple2<T2>(right.x + x, right.y + y);
    }

    inline Tuple2<T2> operator - (const Tuple2<T2>& right){
      return Tuple2<T2>(-right.x + x, -right.y + y);
    }


    inline Tuple2<T2> operator * (const T2 scale){
      return Tuple2<T2>(x*scale, y*scale);
    }

    inline Tuple2<T2>  operator / (const T2 scale){
      if(scale) 
        return Tuple2<T2>(x/scale, y/scale);
      return Tuple2<T2>(0, 0);
    }

    inline Tuple2<T2>& operator += (const Tuple2<T2>& right)
    {
      x+=right.x;
      y+=right.y;
      return *this;
    }

    inline Tuple2<T2>& operator -= (const Tuple2<T2>& right)
    {
      x-=right.x;
      y-=right.y;
      return *this;
    }

    inline Tuple2<T2>& operator *= (const T2 scale)
    {
      x*=scale;
      y*=scale;
      return *this;
    }

    inline Tuple2<T2>& operator /= (const T2 scale){
      if(scale)
      {
        x /=scale;
        y /=scale;
      }
      return *this;
    }

    inline operator const T2*() const { return &x; }
    inline operator T2*()             { return &x; }   

	  inline const T2  operator[](int i) const { return ((T2*)&x)[i]; }
	  inline       T2& operator[](int i)       { return ((T2*)&x)[i]; }

    bool operator == (const Tuple2<T2>& right)
    {
      return (x == right.x &&
              y == right.y);
    }

    bool operator != (const Tuple2<T2>& right)
    {
      return !(x == right.x &&
               y == right.y );
    }

    void set(T2 nx, T2 ny)
    {
      x = nx;
      y = ny;
    }

    inline void clamp(T2 min, T2 max)
    {
      x = x > max ? max : x < min ? min  : x;
      y = y > max ? max : y < min ? min  : y;
    }

    T2 x, y;
};

typedef Tuple2<int   > Tuple2i;
typedef Tuple2<float > Tuple2f;
typedef Tuple2<double> Tuple2d;

#endif
