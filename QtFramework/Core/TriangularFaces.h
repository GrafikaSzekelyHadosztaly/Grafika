#pragma once

#include <GL/glew.h>
#include <iostream>
#include <vector>

namespace cagd
{
    class TriangularFace
    {
    protected:
        GLuint _node[3];

    public:
        // default constructor
        TriangularFace();

        // homework: copy constructor
        TriangularFace(const TriangularFace& face);

        // homework: assignment operator
        TriangularFace& operator =(const TriangularFace& rhs);

        // homework: get node identifiers by value
        GLuint operator [](GLuint i) const;

        // homework: get node identifiers by reference
        GLuint& operator [](GLuint i);
    };

    // default constructor
    inline TriangularFace::TriangularFace()
    {
        _node[0] = _node[1] = _node[2] = 0;
    }
    // copy constructor
    inline TriangularFace::TriangularFace(const TriangularFace& face)
    {
        _node[0] = face[0];
        _node[1] = face[1];
        _node[2] = face[2];
    }

    // get node identifiers by value
    inline GLuint TriangularFace::operator [](GLuint i) const
    {
        return _node[i];
    }
    //get node identifiers by reference
    inline GLuint& TriangularFace::operator [](GLuint i)
    {
        return _node[i];
    }

    // assignment operator
    inline TriangularFace& TriangularFace::operator =(const TriangularFace& rhs)
    {
        if (this != &rhs)
        {
            _node[0] = rhs[0];
            _node[1] = rhs[1];
            _node[2] = rhs[2];
        }
        return *this;
    }

    // output to stream
    inline std::ostream& operator <<(std::ostream& lhs, const TriangularFace& rhs)
    {
        lhs << 3;
        for (GLuint i = 0; i < 3; ++i)
            lhs  << " " << rhs[i];
        return lhs;
    }

    // homework
    inline std::istream& operator >>(std::istream& lhs, TriangularFace& rhs)
    {
        GLuint vertex_count;
        return lhs>>vertex_count>>rhs[0]>>rhs[1]>>rhs[2];
    }
}
