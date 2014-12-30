/*
 *Author: Abdul Bezrati
 *Email : abezrati@hotmail.com
 */
#ifndef MATRIX4_H
#define MATRIX4_H

#include <iostream>
#include "Tuple3.h"
#include "Tuple4.h"
using namespace std;

template <class T>
class Matrix4
{
  public:
    Matrix4<T>()
    {
      setIdentity();
    }

    Matrix4<T>(T  m0, T  m1, T  m2, T  m3,
               T  m4, T  m5, T  m6, T  m7,
               T  m8, T  m9, T m10, T m11,
               T m12, T m13, T m14, T m15)
   {
      m[ 0] =  m0; m[ 1] =  m1; m[ 2] =  m2; m[ 3] =  m3;
      m[ 4] =  m4; m[ 5] =  m5; m[ 6] =  m6; m[ 7] =  m7;
      m[ 8] =  m8; m[ 9] =  m9; m[10] = m10; m[11] = m11;
      m[12] = m12; m[13] = m13; m[14] = m14; m[15] = m15;
    }

    Matrix4<T>(const T* elements)
    {
      memcpy(m, elements, sizeof(T)*16);
    }

    Matrix4<T>(const Matrix4<T>& mat)
    {
      memcpy(m, mat.m, sizeof(T)*16);
    }

   	inline Matrix4<T> operator + (const Matrix4<T>& mat){
      return Matrix4(m[ 0] + mat.m[ 0], m[ 1] + mat.m[ 1], m[ 2] + mat.m[ 2], m[ 3] + mat.m[ 3],
                     m[ 4] + mat.m[ 4], m[ 5] + mat.m[ 5], m[ 6] + mat.m[ 6], m[ 7] + mat.m[ 7],
                     m[ 8] + mat.m[ 8], m[ 9] + mat.m[ 9], m[10] + mat.m[10], m[11] + mat.m[11],
                     m[12] + mat.m[12], m[13] + mat.m[13], m[14] + mat.m[14], m[15] + mat.m[15]);
    }

    inline Matrix4<T> operator - (const Matrix4<T>& mat){
      return Matrix4(m[ 0] - mat.m[ 0], m[ 1] - mat.m[ 1], m[ 2] - mat.m[ 2], m[ 3] - mat.m[ 3],
                     m[ 4] - mat.m[ 4], m[ 5] - mat.m[ 5], m[ 6] - mat.m[ 6], m[ 7] - mat.m[ 7],
                     m[ 8] - mat.m[ 8], m[ 9] - mat.m[ 9], m[10] - mat.m[10], m[11] - mat.m[11],
                     m[12] - mat.m[12], m[13] - mat.m[13], m[14] - mat.m[14], m[15] - mat.m[15]);
    }

    inline Matrix4<T> operator * (const Matrix4<T>& mat){
      return Matrix4(m[0]*mat.m[ 0]+m[4]*mat.m[ 1]+m[ 8]*mat.m[ 2]+ m[12]*mat.m[ 3],
                     m[1]*mat.m[ 0]+m[5]*mat.m[ 1]+m[ 9]*mat.m[ 2]+ m[13]*mat.m[ 3],
                     m[2]*mat.m[ 0]+m[6]*mat.m[ 1]+m[10]*mat.m[ 2]+ m[14]*mat.m[ 3],
                     m[3]*mat.m[ 0]+m[7]*mat.m[ 1]+m[11]*mat.m[ 2]+ m[15]*mat.m[ 3],
                     m[0]*mat.m[ 4]+m[4]*mat.m[ 5]+m[ 8]*mat.m[ 6]+ m[12]*mat.m[ 7],
                     m[1]*mat.m[ 4]+m[5]*mat.m[ 5]+m[ 9]*mat.m[ 6]+ m[13]*mat.m[ 7],
                     m[2]*mat.m[ 4]+m[6]*mat.m[ 5]+m[10]*mat.m[ 6]+ m[14]*mat.m[ 7],
                     m[3]*mat.m[ 4]+m[7]*mat.m[ 5]+m[11]*mat.m[ 6]+ m[15]*mat.m[ 7],
                     m[0]*mat.m[ 8]+m[4]*mat.m[ 9]+m[ 8]*mat.m[10]+ m[12]*mat.m[11],
                     m[1]*mat.m[ 8]+m[5]*mat.m[ 9]+m[ 9]*mat.m[10]+ m[13]*mat.m[11],
                     m[2]*mat.m[ 8]+m[6]*mat.m[ 9]+m[10]*mat.m[10]+ m[14]*mat.m[11],
                     m[3]*mat.m[ 8]+m[7]*mat.m[ 9]+m[11]*mat.m[10]+ m[15]*mat.m[11],
                     m[0]*mat.m[12]+m[4]*mat.m[13]+m[ 8]*mat.m[14]+ m[12]*mat.m[15],
                     m[1]*mat.m[12]+m[5]*mat.m[13]+m[ 9]*mat.m[14]+ m[13]*mat.m[15],
                     m[2]*mat.m[12]+m[6]*mat.m[13]+m[10]*mat.m[14]+ m[14]*mat.m[15],
                     m[3]*mat.m[12]+m[7]*mat.m[13]+m[11]*mat.m[14]+ m[15]*mat.m[15]);
    }

    inline Matrix4<T>& lookAt(T viewX , T viewY , T viewZ ,
                              T focusX, T focusY, T focusZ,
                              T upX   , T upY   , T upZ   )
    {
      return lookAt(Tuple3<T>(viewX , viewY , viewZ ),
                    Tuple3<T>(focusX, focusY, focusZ),
                    Tuple3<T>(upX   , upY   , upZ   ));
    }

    inline Matrix4<T>& lookAt(Tuple3<T>& viewPosition,
                              Tuple3<T>& viewFocus, 
                              Tuple3<T>& upVector)
    {
      Tuple3<T> *xaxis = (Tuple3<T> *)m ,
                *up    = (Tuple3<T> *)(m + 4),
                *at    = (Tuple3<T> *)(m + 8);

      *at  = viewFocus;
      *at -= viewPosition;
      at->normalize();
 
      xaxis->crossProduct(*at, upVector);
      xaxis->normalize();

      up->crossProduct(*xaxis, *at);

      *at *= -1.f;

      m[3]  = 0.f;
      m[7]  = 0.f;
      m[11] = 0.f;
 
      m[12] = viewPosition.x;
      m[13] = viewPosition.y; 
      m[14] = viewPosition.z;
      m[15] = 1.f;
      setInverse();
      return *this;
    }

    inline Matrix4<T>& operator +=(const Matrix4<T>& mat){
      for(int i = 0; i < 16; i += 1)
        m[i] += mat.m[i];
      return *this;
    }

    inline Matrix4<T>& operator -=(const Matrix4<T>& mat){
      for(int i = 0; i < 16; i += 1)
        m[i] -= mat.m[i];
      return *this;
    }
 
    inline Matrix4<T>& operator *=(const T f){
      for(int i = 0; i < 16; i += 1)
        m[i] *= f;
      return *this;
    }

    inline Matrix4<T>& setInfinitePerspective(T fovy, T aspect, T zNear)
    {
    	float tangent = tanf(1.57f*((fovy/2.0f)/180.0f));
      T     y       = tangent * zNear,
            x       = aspect  * y;

	    return setInfiniteFrustum(-x, x, -y, y, zNear);
    }

    inline Matrix4<T>& setInfiniteFrustum(T left,    T  right,
						                               T  bottom, T  top,
						                               T  zNear)
    {
      setIdentity();
      m[ 0] = (2*zNear) / (right - left);
	    m[ 2] = (right + left) / (right - left);
	
	    m[ 5] = (2*zNear) / (top - bottom);
	    m[ 6] = (top + bottom) / (top - bottom);
	
      float nudge = 1 - 1.0 / (1<<23);

	    m[10] = -1 * nudge;
	    m[11] = -2* zNear * nudge;
	
      m[14] = -1;
    	m[15] =  0;
      return *this;
    }

    inline Matrix4<T>& setPerspective(float fov, float aspect, float zNear, float zFar)
    {
	    float sine, cotangent, deltaZ;
		  float radians = fov / 2.0f * 0.017453f;

		  deltaZ = zFar - zNear;
		  sine   = sinf(radians);

      setIdentity();
	  	if ((deltaZ == 0.0f) || (sine == 0.0f) || (aspect == 0.0f))
			  return *this;
		
      cotangent = cosf(radians) / sine;


		  m[ 0] = cotangent / aspect;
		  m[ 5] = cotangent;
		  m[10] = - (zFar + zNear) / deltaZ;
		  m[11] = -1.0f;
		  m[14] = -2.0f * zNear * zFar / deltaZ;
	  	m[15] = 0.0f;
      return *this;
    }

    inline Matrix4<T>&  operator *= (const Matrix4<T>& mat)
    {
      set(m[0]*mat.m[ 0]+m[4]*mat.m[ 1]+m[ 8]*mat.m[ 2]+ m[12]*mat.m[ 3],
          m[1]*mat.m[ 0]+m[5]*mat.m[ 1]+m[ 9]*mat.m[ 2]+ m[13]*mat.m[ 3],
          m[2]*mat.m[ 0]+m[6]*mat.m[ 1]+m[10]*mat.m[ 2]+ m[14]*mat.m[ 3],
          m[3]*mat.m[ 0]+m[7]*mat.m[ 1]+m[11]*mat.m[ 2]+ m[15]*mat.m[ 3],
          m[0]*mat.m[ 4]+m[4]*mat.m[ 5]+m[ 8]*mat.m[ 6]+ m[12]*mat.m[ 7],
          m[1]*mat.m[ 4]+m[5]*mat.m[ 5]+m[ 9]*mat.m[ 6]+ m[13]*mat.m[ 7],
          m[2]*mat.m[ 4]+m[6]*mat.m[ 5]+m[10]*mat.m[ 6]+ m[14]*mat.m[ 7],
          m[3]*mat.m[ 4]+m[7]*mat.m[ 5]+m[11]*mat.m[ 6]+ m[15]*mat.m[ 7],
          m[0]*mat.m[ 8]+m[4]*mat.m[ 9]+m[ 8]*mat.m[10]+ m[12]*mat.m[11],
          m[1]*mat.m[ 8]+m[5]*mat.m[ 9]+m[ 9]*mat.m[10]+ m[13]*mat.m[11],
          m[2]*mat.m[ 8]+m[6]*mat.m[ 9]+m[10]*mat.m[10]+ m[14]*mat.m[11],
          m[3]*mat.m[ 8]+m[7]*mat.m[ 9]+m[11]*mat.m[10]+ m[15]*mat.m[11],
          m[0]*mat.m[12]+m[4]*mat.m[13]+m[ 8]*mat.m[14]+ m[12]*mat.m[15],
          m[1]*mat.m[12]+m[5]*mat.m[13]+m[ 9]*mat.m[14]+ m[13]*mat.m[15],
          m[2]*mat.m[12]+m[6]*mat.m[13]+m[10]*mat.m[14]+ m[14]*mat.m[15],
          m[3]*mat.m[12]+m[7]*mat.m[13]+m[11]*mat.m[14]+ m[15]*mat.m[15]);
      return *this;
    } 
  
    inline bool operator == (const Matrix4<T>& mat)
    {
      return memcmp(m, mat.m, sizeof(T)*16) == 0;
    }

    inline bool operator != (const Matrix4<T>& mat)
    {
      return memcmp(m, mat.m, sizeof(T)*16) != 0;
    }

    inline Matrix4& operator  = (const Matrix4<T>& mat)
    {
      memcpy(m,mat.m, sizeof(T)*16);
      return *this;
    }

    inline operator const T*() const { return m; }
    inline operator       T*()       { return m; }   

    inline friend Tuple3<T> operator * (const Tuple3<T>& t,const Matrix4<T>& mat){
      return Tuple3<T>(mat.m[ 0]*t.x + mat.m[ 4]*t.y + mat.m[ 8]*t.z + mat.m[12],
                       mat.m[ 1]*t.x + mat.m[ 5]*t.y + mat.m[ 9]*t.z + mat.m[13],
                       mat.m[ 2]*t.x + mat.m[ 6]*t.y + mat.m[10]*t.z + mat.m[14]);
    }

    inline friend Tuple3<T> operator * (const Matrix4<T>& mat,const Tuple3<T>& t){
      return Tuple3<T>(mat.m[ 0]*t.x + mat.m[ 4]*t.y + mat.m[ 8]*t.z + mat.m[12],
                       mat.m[ 1]*t.x + mat.m[ 5]*t.y + mat.m[ 9]*t.z + mat.m[13],
                       mat.m[ 2]*t.x + mat.m[ 6]*t.y + mat.m[10]*t.z + mat.m[14]);
    }

    inline friend Tuple4<T> operator * (const Matrix4<T>& mat, const Tuple4<T>& t){
      return Tuple4<T>(mat.m[ 0]*t.x + mat.m[ 4]*t.y + mat.m[ 8]*t.z + mat.m[12]*t.w,
                       mat.m[ 1]*t.x + mat.m[ 5]*t.y + mat.m[ 9]*t.z + mat.m[13]*t.w,
                       mat.m[ 2]*t.x + mat.m[ 6]*t.y + mat.m[10]*t.z + mat.m[14]*t.w,
                       mat.m[ 3]*t.x + mat.m[ 7]*t.y + mat.m[11]*t.z + mat.m[15]*t.w);
    }

    inline friend Tuple4<T> operator * (const Tuple4<T>& t,const Matrix4<T>& mat){
      return Tuple4<T>(mat.m[ 0]*t.x + mat.m[ 4]*t.y + mat.m[ 8]*t.z + mat.m[12]*t.w,
                       mat.m[ 1]*t.x + mat.m[ 5]*t.y + mat.m[ 9]*t.z + mat.m[13]*t.w,
                       mat.m[ 2]*t.x + mat.m[ 6]*t.y + mat.m[10]*t.z + mat.m[14]*t.w,
                       mat.m[ 3]*t.x + mat.m[ 7]*t.y + mat.m[11]*t.z + mat.m[15]*t.w);
    }

    inline friend  void operator *=(Tuple3<T>& t,const Matrix4<T>& mat){
      t.set(mat.m[ 0]*t.x + mat.m[ 4]*t.y + mat.m[ 8]*t.z + mat.m[12],
            mat.m[ 1]*t.x + mat.m[ 5]*t.y + mat.m[ 9]*t.z + mat.m[13],
            mat.m[ 2]*t.x + mat.m[ 6]*t.y + mat.m[10]*t.z + mat.m[14]);
    }

    inline friend void operator *=(Tuple4<T>& t,const Matrix4<T>& mat){
      t.set(mat.m[ 0]*t.x + mat.m[ 4]*t.y + mat.m[ 8]*t.z + mat.m[12]*t.w,
            mat.m[ 1]*t.x + mat.m[ 5]*t.y + mat.m[ 9]*t.z + mat.m[13]*t.w,
            mat.m[ 2]*t.x + mat.m[ 6]*t.y + mat.m[10]*t.z + mat.m[14]*t.w,
            mat.m[ 3]*t.x + mat.m[ 7]*t.y + mat.m[11]*t.z + mat.m[15]*t.w);
    }

    __forceinline T getDeterminant()
    {	
      T det;
		  det = m[0] * m[5] * m[10];
		  det += m[4] * m[9] * m[2];
	  	det += m[8] * m[1] * m[6];
	  	det -= m[8] * m[5] * m[2];
		  det -= m[4] * m[1] * m[10];
		  det -= m[0] * m[9] * m[6];
	  	return det;
    }


  __forceinline bool setInverse()
  {
		int i, j, k, swap;
		T temp[16], t;

	  memcpy(temp, m, 16*sizeof(T));
    setIdentity();

    for (i = 0; i < 4; i += 1) {
			swap = i;
      for (j = i + 1; j < 4; j += 1)
      {
        if (fabs(temp[j*4 + i]) >  fabs(temp[i*4 + i]))
        {
          swap = j;
				}
			}

      if (swap != i) {
				for (k = 0; k < 4; k += 1) {
					t                = temp[i*4 + k];
					temp[i*4 + k]    = temp[swap*4 + k];
					temp[swap*4 + k] = t;

					t             = m[i*4 + k];
					m[i*4 + k]    = m[swap*4 + k];
  				m[swap*4 + k] = t;
				}
			}

			if(!temp[i*4 + i])
				return false;

			t = temp[i*4 + i];

			for (k = 0; k < 4; k += 1) {
				temp[i*4 + k] /= t;
				m[i*4 + k]     = m[i*4 + k] / t;
			}

			for (j = 0; j < 4; j += 1) {
				if (j != i) {
					t = temp[j*4 + i];
					for (k = 0; k < 4; k += 1) {
						temp[j*4 + k] -= temp[i*4 + k] * t;
						m[j*4 + k]     = m[j*4 + k] - m[i*4 + k] * t;
					}
				}
			}
		}
		return true;
	}

    inline void setScales(const Tuple3<T>& axis) 
    {
	    setIdentity();
      m[ 0] = axis.x;
      m[ 5] = axis.y;
      m[10] = axis.z;     
    }

    inline void setScales(T x, T y, T z){
	    setIdentity();
      m[ 0] = x;
      m[ 5] = y;
      m[10] = z;     
    }

    inline void rotateAxis(float angle, const Tuple3<T>& axis) {
      float sinAngle = fastSin(angle),
            cosAngle = fastCos(angle),
            oneMinusCosAngle = 1.0f - cosAngle;

      setIdentity();

      m[ 0] = (axis.x)*(axis.x) + cosAngle*(1-(axis.x)*(axis.x));
      m[ 4] = (axis.x)*(axis.y)*(oneMinusCosAngle) - sinAngle*axis.z;
      m[ 8] = (axis.x)*(axis.z)*(oneMinusCosAngle) + sinAngle*axis.y;

      m[ 1] = (axis.x)*(axis.y)*(oneMinusCosAngle) + sinAngle*axis.z;
      m[ 5] = (axis.y)*(axis.y) + cosAngle*(1-(axis.y)*(axis.y));
      m[ 9] = (axis.y)*(axis.z)*(oneMinusCosAngle) - sinAngle*axis.x;

      m[ 2] = (axis.x)*(axis.z)*(oneMinusCosAngle) - sinAngle*axis.y;
      m[ 6] = (axis.y)*(axis.z)*(oneMinusCosAngle) + sinAngle*axis.x;
      m[10] = (axis.z)*(axis.z) + cosAngle*(1-(axis.z)*(axis.z));
    }

    __forceinline void set(const T* elements){
       memcpy(m, elements, sizeof(T)*16);
    }

    void set(T  m0, T  m1, T  m2, T  m3,
             T  m4, T  m5, T  m6, T  m7,
             T  m8, T  m9, T m10, T m11,
             T m12, T m13, T m14, T m15)
    {
      m[ 0] =  m0; m[ 1] =  m1; m[ 2] =  m2; m[ 3] =  m3;
      m[ 4] =  m4; m[ 5] =  m5; m[ 6] =  m6; m[ 7] =  m7;
      m[ 8] =  m8; m[ 9] =  m9; m[10] = m10; m[11] = m11;
      m[12] = m12; m[13] = m13; m[14] = m14; m[15] = m15;
    }

    __forceinline void setTranspose()
    {
      T    temp = 0;
      temp  = m[4];  m[4]  = m[1];
      m[1]  = temp;  temp  = m[8];
      m[8]  = m[2];  m[2]  = temp;
      temp  = m[12]; m[12] = m[3];
      m[3]  = temp;  temp  = m[9];
      m[9]  = m[6];  m[6]  = temp;
      temp  = m[13]; m[13] = m[7];
      m[7]  = temp;  temp  = m[14];
      m[14] = m[11]; m[11] = temp;
    }

     __forceinline void setIdentity()
    {
      m[ 0] = 1; m[ 1] = 0; m[ 2] = 0; m[ 3] = 0;
      m[ 4] = 0; m[ 5] = 1; m[ 6] = 0; m[ 7] = 0;
      m[ 8] = 0; m[ 9] = 0; m[10] = 1; m[11] = 0;
      m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
    }

    __forceinline void setInverseTranspose()
    {
      if(!setInverse())
        return;
      setTranspose(); 
    }

    void setZero(){
      memset(m, 0, sizeof(T)*16);
    }

    void  set(const Matrix4<T>&  matrix)
    {
      memcpy(m, matrix.m, sizeof(T) * 16);
    }
  
    inline void rotateX(const float angle){
      setIdentity();
      m[ 5] =  fastCos(angle);
      m[ 6] =  fastSin(angle);
      m[ 9] = -m[6];
      m[10] =  m[5];
    }

    inline void rotateY(const float angle){
      setIdentity();
      m[ 0] =  fastCos(angle);
      m[ 2] =  fastSin(angle);
      m[ 8] = -m[2];
      m[10] =  m[0];
    }  

    inline void rotateZ(const float angle){
      setIdentity();
      m[0] =  fastCos(angle);
      m[1] =  fastSin(angle);
      m[4] = -m[1];
      m[5] =  m[0];
    }

    inline void rotateXYZ(const Tuple3<T>& t)
    {
      float cosX = fastCos(t.x), sinX = fastSin(t.x),
            cosY = fastCos(t.y), sinY = fastSin(t.y),
            cosZ = fastCos(t.z), sinZ = fastSin(t.z);

      set(cosY * cosZ + sinX * sinY * sinZ,   -cosX * sinZ,    sinX * cosY * sinZ - sinY * cosZ,  0,
          cosY * sinZ - sinX * sinY * cosZ,    cosX * cosZ,   -sinY * sinZ - sinX * cosY * cosZ,  0,
          cosX * sinY,                         sinX,           cosX * cosY,                       0,
          0,                                   0,              0,                                 1);
    }

    inline void rotateXYZ(float x, float y, float z)
    {
      float cosX = fastCos(x), sinX = fastSin(x),
            cosY = fastCos(y), sinY = fastSin(y),
            cosZ = fastCos(z), sinZ = fastSin(z);

      set(cosY * cosZ + sinX * sinY * sinZ,   -cosX * sinZ,    sinX * cosY * sinZ - sinY * cosZ,  0,
          cosY * sinZ - sinX * sinY * cosZ,    cosX * cosZ,   -sinY * sinZ - sinX * cosY * cosZ,  0,
          cosX * sinY,                         sinX,           cosX * cosY,                       0,
                    0,                                   0,              0,                                 1);
    }


    void setTranslations(const Tuple3<T>& t)
    {
      setIdentity();
      m[12] =  t.x;
      m[13] =  t.y;
      m[14] =  t.z;
    }
   
    void  setTranslations(const float x,const float y,const float z){
      setIdentity();
      m[12] =  x;
      m[13] =  y;
      m[14] =  z;
    }

    void  setTranslations(const double x,const double y,const double z){
      setIdentity();
      m[12] =  x;
      m[13] =  y;
      m[14] =  z;
    }

    friend ostream&  operator << ( ostream&  out, const Matrix4<T>&  right){
      return out <<
       "Matrix4[" << right.m[ 0] << ", " << right.m[ 1] << ", "<< right.m[ 2] << ", "<< right.m[ 3] << "),\n"
       "       [" << right.m[ 4] << ", " << right.m[ 5] << ", "<< right.m[ 6] << ", "<< right.m[ 7] << "),\n"
       "       [" << right.m[ 8] << ", " << right.m[ 9] << ", "<< right.m[10] << ", "<< right.m[11] << "),\n"
       "       [" << right.m[12] << ", " << right.m[13] << ", "<< right.m[14] << ", "<< right.m[15] << ")]\n";
                  
    }

    __declspec(align(16)) T  m[16];
};

typedef Matrix4<int>    Matrix4i;
typedef Matrix4<float>  Matrix4f;
typedef Matrix4<double> Matrix4d;

static Matrix4f IDENTITY;

#endif

