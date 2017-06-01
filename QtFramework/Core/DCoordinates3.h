#pragma once

#include <cmath>
#include <GL/glew.h>
#include <iostream>

namespace cagd
{
    //-------------------
    // class DCoordinate3
    //-------------------
    class DCoordinate3
    {
    private:
        GLdouble _data[3];      // egy vektor koordinatai: data[0] x, data[1] y, data[2] z

    public:

        // default constructor
        DCoordinate3();

        // special constructor
        DCoordinate3(GLdouble x, GLdouble y, GLdouble z = 0.0);

        // get components by value
        GLdouble operator [](GLuint index) const;
        GLdouble x() const;
        GLdouble y() const;
        GLdouble z() const;


        // get components by reference
        GLdouble& operator [](GLuint index);
        GLdouble& x();
        GLdouble& y();
        GLdouble& z();

        // change sign
        const DCoordinate3 operator +() const;
        const DCoordinate3 operator -() const;

        // add
        const DCoordinate3 operator +(const DCoordinate3& rhs) const;   //rhs right hand side, lhs left hand side

        // add to *this
        DCoordinate3& operator +=(const DCoordinate3& rhs);

        // subtract
        const DCoordinate3 operator -(const DCoordinate3& rhs) const;

        // subtract from *this
        DCoordinate3& operator -=(const DCoordinate3& rhs);

        // cross product
        const DCoordinate3 operator ^(const DCoordinate3& rhs) const;   //vektorszorzat

        // cross product, result is stored by *this
        DCoordinate3& operator ^=(const DCoordinate3& rhs);

        // dot product
        GLdouble operator *(const DCoordinate3& rhs) const;     //skalaris szorzat

        // scale
        const DCoordinate3 operator *(const GLdouble& rhs) const;   //skalazas
        const DCoordinate3 operator /(const GLdouble& rhs) const;

        // scale *this
        DCoordinate3& operator *=(const GLdouble& rhs);
        DCoordinate3& operator /=(const GLdouble& rhs);

        // length
        GLdouble length() const;

        // normalize
        DCoordinate3& normalize();

        // logical operators
        GLboolean operator !=(const GLdouble& rhs) const;
    };

    //-------------------------------------
    // implementation of class DCoordinate3
    //-------------------------------------

    // default constructor
    inline DCoordinate3::DCoordinate3()
    {
        _data[0] = _data[1] = _data[2] = 0.0;
    }

    // special constructor
    inline DCoordinate3::DCoordinate3(GLdouble x, GLdouble y, GLdouble z)
    {
        _data[0] = x;
        _data[1] = y;
        _data[2] = z;
    }

    // get components by value
    inline GLdouble DCoordinate3::operator [](GLuint index) const
    {
        return _data[index];
    }

    inline GLdouble DCoordinate3::x() const
    {
        return _data[0];
    }

    inline GLdouble DCoordinate3::y() const
    {
        return _data[1];
    }

    inline GLdouble DCoordinate3::z() const
    {
        return _data[2];
    }

    // get components by reference
    inline GLdouble& DCoordinate3::operator [](GLuint index)
    {
        return _data[index];
    }

    inline GLdouble& DCoordinate3::x()
    {
        return _data[0];
    }

    inline GLdouble& DCoordinate3::y()
    {
        return _data[1];
    }

    inline GLdouble& DCoordinate3::z()
    {
        return _data[2];
    }

    // change sign
    inline const DCoordinate3 DCoordinate3::operator +() const
    {
        return DCoordinate3(_data[0], _data[1], _data[2]);
    }

    inline const DCoordinate3 DCoordinate3::operator -() const
    {
        return DCoordinate3(-_data[0], -_data[1], -_data[2]);
    }

    // add
    inline const DCoordinate3 DCoordinate3::operator +(const DCoordinate3& rhs) const
    {
        return DCoordinate3(_data[0] + rhs._data[0], _data[1] + rhs._data[1], _data[2] + rhs._data[2]);
    }

    // add to *this
    inline DCoordinate3& DCoordinate3::operator +=(const DCoordinate3& rhs)
    {
        _data[0] += rhs._data[0];
        _data[1] += rhs._data[1];
        _data[2] += rhs._data[2];
        return *this;
    }

    // subtract
    inline const DCoordinate3 DCoordinate3::operator -(const DCoordinate3& rhs) const
    {
        return DCoordinate3(_data[0] - rhs._data[0], _data[1] - rhs._data[1], _data[2] - rhs._data[2]);
    }

    // subtract from *this
    inline DCoordinate3& DCoordinate3::operator -=(const DCoordinate3& rhs)
    {
        _data[0] -= rhs._data[0];
        _data[1] -= rhs._data[1];
        _data[2] -= rhs._data[2];
        return *this;
    }

    // cross product
    inline const DCoordinate3 DCoordinate3::operator ^(const DCoordinate3& rhs) const
    {
        return DCoordinate3(
                _data[1] * rhs._data[2] - _data[2] * rhs._data[1],
                _data[2] * rhs._data[0] - _data[0] * rhs._data[2],
                _data[0] * rhs._data[1] - _data[1] * rhs._data[0]);
    }

    // cross product, result is stored by *this
    inline DCoordinate3& DCoordinate3::operator ^=(const DCoordinate3& rhs)
    {
        GLdouble _temp[3];
        _temp[0] = _data[0];
        _temp[1] = _data[1];
        _temp[2] = _data[2];

        _data[0] = _temp[1] * rhs._data[2] - _temp[2] * rhs._data[1];
        _data[1] = _temp[2] * rhs._data[0] - _temp[0] * rhs._data[2];
        _data[2] = _temp[0] * rhs._data[1] - _temp[1] * rhs._data[0];
        return *this;
    }

    // dot product
    inline GLdouble DCoordinate3::operator *(const DCoordinate3& rhs) const
    {
        return _data[0] * rhs._data[0] + _data[1] * rhs._data[1] + _data[2] * rhs._data[2];
    }

    // scale
    inline const DCoordinate3 DCoordinate3::operator *(const GLdouble& rhs) const
    {
        return DCoordinate3(_data[0] * rhs, _data[1] * rhs, _data[2] * rhs);
    }

    inline const DCoordinate3 operator *(const GLdouble& lhs, const DCoordinate3& rhs)
    {
        return DCoordinate3(lhs * rhs[0], lhs * rhs[1], lhs * rhs[2]);
    }

    inline const DCoordinate3 DCoordinate3::operator /(const GLdouble& rhs) const
    {
        DCoordinate3 a(_data[0],_data[1],_data[2]);
        a._data[0]/=rhs;
        a._data[1]/=rhs;
        a._data[2]/=rhs;
        return a;
    }

    // scale *this
    inline DCoordinate3& DCoordinate3::operator *=(const GLdouble& rhs)
    {
        _data[0] *= rhs;
        _data[1] *= rhs;
        _data[2] *= rhs;

        return *this;
    }

    inline DCoordinate3& DCoordinate3::operator /=(const GLdouble& rhs)
    {
        _data[0] /= rhs;
        _data[1] /= rhs;
        _data[2] /= rhs;
        return *this;
    }

    // length
    inline GLdouble DCoordinate3::length() const
    {
        return std::sqrt((*this) * (*this));
    }

    // normalize
    inline DCoordinate3& DCoordinate3::normalize()
    {
        GLdouble l = length();

        if (l && l != 1.0)
            *this /= l;

        return *this;
    }

    // logical operators
    inline GLboolean DCoordinate3::operator !=(const GLdouble& rhs) const
    {
        return (_data[0] != rhs || _data[1] != rhs || _data[2] != rhs);
    }

    //----------------------------------------------------------------
    // definitions of overloaded input/output from/to stream operators
    //----------------------------------------------------------------

    // output to stream
    inline std::ostream& operator <<(std::ostream& lhs, const DCoordinate3& rhs)
    {
        return lhs << rhs[0] << " " << rhs[1] << " " << rhs[2];
    }

    // input from stream
    inline std::istream& operator >>(std::istream& lhs, DCoordinate3& rhs)
    {
        return lhs >> rhs[0] >> rhs[1] >> rhs[2];
    }
}
