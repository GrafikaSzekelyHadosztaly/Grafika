#pragma once

#include "../Core/DCoordinates3.h"

namespace cagd
{
    namespace spiral_on_cone
    {
        extern GLdouble u_min, u_max;

        DCoordinate3 d0(GLdouble);
        DCoordinate3 d1(GLdouble);
        DCoordinate3 d2(GLdouble);
    }

    namespace torus
    {
        extern GLdouble u_min, u_max;

        DCoordinate3 d0(GLdouble);
        DCoordinate3 d1(GLdouble);
        DCoordinate3 d2(GLdouble);
    }

    namespace ellipse
    {
        extern GLdouble u_min, u_max;

        DCoordinate3 d0(GLdouble);
        DCoordinate3 d1(GLdouble);
        DCoordinate3 d2(GLdouble);
    }

    namespace hypo
    {
        extern GLdouble u_min, u_max;

        DCoordinate3 d0(GLdouble);
        DCoordinate3 d1(GLdouble);
        DCoordinate3 d2(GLdouble);
    }

    namespace helix
    {
        extern GLdouble u_min, u_max;

        DCoordinate3 d0(GLdouble);
        DCoordinate3 d1(GLdouble);
        DCoordinate3 d2(GLdouble);
    }

    namespace butterfly
    {
        extern GLdouble u_min, u_max;

        DCoordinate3 d0(GLdouble);

    }

    namespace sphere
    {
        extern GLdouble u_min, u_max, v_min, v_max, r;

        DCoordinate3 d00(GLdouble,GLdouble);
        DCoordinate3 d10(GLdouble,GLdouble);
        DCoordinate3 d01(GLdouble,GLdouble);
    }

    namespace cylindrical
    {
        extern GLdouble u_min, u_max,v_min,v_max;

        DCoordinate3 d00(GLdouble,GLdouble);
        DCoordinate3 d10(GLdouble,GLdouble);
        DCoordinate3 d01(GLdouble,GLdouble);
    }

    namespace hyperboloid
    {
        extern GLdouble u_min, u_max,v_min,v_max;

        DCoordinate3 d00(GLdouble,GLdouble);
        DCoordinate3 d10(GLdouble,GLdouble);
        DCoordinate3 d01(GLdouble,GLdouble);
    }

    namespace kleinbottle
    {
        extern GLdouble u_min, u_max,v_min,v_max;

        DCoordinate3 d00(GLdouble,GLdouble);
        DCoordinate3 d10(GLdouble,GLdouble);
        DCoordinate3 d01(GLdouble,GLdouble);
    }

    namespace duplincyclide
    {
        extern GLdouble u_min, u_max,v_min,v_max;

        DCoordinate3 d00(GLdouble,GLdouble);
        DCoordinate3 d10(GLdouble,GLdouble);
        DCoordinate3 d01(GLdouble,GLdouble);
    }

}
