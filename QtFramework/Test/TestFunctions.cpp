#include <cmath>
#include "TestFunctions.h"
#include "../Core/Constants.h"

using namespace cagd;
using namespace std;

//spiral_on_cone
GLdouble spiral_on_cone::u_min = -TWO_PI;
GLdouble spiral_on_cone::u_max = +TWO_PI;

DCoordinate3 spiral_on_cone::d0(GLdouble u)
{
    return DCoordinate3(u * cos(u), u * sin(u), u);
}

DCoordinate3 spiral_on_cone::d1(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u);
    return DCoordinate3(c - u * s, s + u * c, 1.0);
}

DCoordinate3 spiral_on_cone::d2(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u);
    return DCoordinate3(-2.0 * s - u * c, 2.0 * c - u * s, 0);
}

//torus

GLdouble torus::u_min = 0.0;
GLdouble torus::u_max = 6*PI;

DCoordinate3 torus::d0(GLdouble u)
{
    return DCoordinate3((2+cos(2*u/3))*cos(u), (2+cos(2*u/3))*sin(u), sin(2*u/3));
}

DCoordinate3 torus::d1(GLdouble u)
{
    return DCoordinate3(-(2+cos(2*u/3))*sin(u)-2.0/3*sin(2*u/3)*cos(u), (2+cos(2*u/3))*cos(u)-2.0/3*sin(2*u/3)*sin(u), 2.0/3*cos(2*u/3));
}

DCoordinate3 torus::d2(GLdouble u)
{
    return DCoordinate3(1.33*sin((2*u)/3)*sin(u)-0.44*cos((2*u)/3)*cos(u)-(cos((2*u)/3)+2)*cos(u),
                        -1.33*sin((2*u)/3)*cos(u)-0.44*cos((2*u)/3)*sin(u)-(cos((2*u)/3)+2)*sin(u),
                        -0.44*sin(2*u)/3);
}

//ellipse

GLdouble ellipse::u_min = -PI;
GLdouble ellipse::u_max = +PI;

DCoordinate3 ellipse::d0(GLdouble u)
{
    return DCoordinate3(8 * cos(u), 4 * sin(u), 0);
}
DCoordinate3 ellipse::d1(GLdouble u)
{
    return DCoordinate3(-8 * sin(u), 4 * cos(u), 0);
}
DCoordinate3 ellipse::d2(GLdouble u)
{
    return DCoordinate3(-8 * cos(u), -4 * sin(u), 0);
}

//hypo

GLdouble hypo::u_min = -3.0;
GLdouble hypo::u_max = +3.0;

DCoordinate3 hypo::d0(GLdouble u)
{
    return DCoordinate3(5*cos(u)+cos(5*u), 5*sin(u)-sin(5*u), 0);
}

DCoordinate3 hypo::d1(GLdouble u)
{
    return DCoordinate3(-5*sin(u)-5*sin(5*u), 5*cos(u)-5*cos(5*u), 0);
}

DCoordinate3 hypo::d2(GLdouble u)
{
    return DCoordinate3(-5*cos(u)-25*cos(5*u), -5*sin(u)+25*sin(5*u), 0);
}

//helix

GLdouble helix::u_min = 0;
GLdouble helix::u_max = 24*PI;

DCoordinate3 helix::d0(GLdouble u)
{
    return 0.2* DCoordinate3(cos(u),sin(u), u/7);
}

DCoordinate3 helix::d1(GLdouble u)
{
    return 0.2* DCoordinate3(-sin(u),cos(u), 1/7);
}

DCoordinate3 helix::d2(GLdouble u)
{
    return 0.2* DCoordinate3(-cos(u),-sin(u), 0);
}

//butterfly

GLdouble butterfly::u_min = 0;
GLdouble butterfly::u_max = 2 * TWO_PI;

DCoordinate3 butterfly::d0(GLdouble u)
{
    return DCoordinate3(sin(u)*(exp(cos(u)-2*cos(4*u)-sin(u/12)*sin(u/12)*sin(u/12)*sin(u/12)*sin(u/12))),
                        cos(u)*(exp(cos(u)-2*cos(4*u)-sin(u/12)*sin(u/12)*sin(u/12)*sin(u/12)*sin(u/12))),
                        0);
}

//sphere
GLdouble sphere::u_min=EPS;
GLdouble sphere::u_max=PI-EPS;
GLdouble sphere::v_min=0;
GLdouble sphere::v_max=PI;
GLdouble sphere::r=1.0;

DCoordinate3 sphere::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3(r*sin(u)*cos(v),r*sin(u)*sin(v),r*cos(u));
}

DCoordinate3 sphere::d10(GLdouble u, GLdouble v)
{
    return DCoordinate3(r*cos(u)*cos(v),r*cos(u)*sin(v),-r*sin(u));
}

DCoordinate3 sphere::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3(-r*sin(u)*sin(v),r*sin(u)*cos(v),0);
}

//cycylindrical
GLdouble cylindrical::u_min=0;
GLdouble cylindrical::u_max=2;
GLdouble cylindrical::v_min=0;
GLdouble cylindrical::v_max=3*TWO_PI;

DCoordinate3 cylindrical::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3((2+u)*cos(v),(2+u)*sin(v),v);
}

DCoordinate3 cylindrical::d10(GLdouble u, GLdouble v)
{
    return DCoordinate3(cos(v),sin(v),v);
}

DCoordinate3 cylindrical::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3(-(2+u)*sin(v),(2+u)*cos(v),1);
}

//hyperboloid
GLdouble hyperboloid::u_min=0;
GLdouble hyperboloid::u_max=3;
GLdouble hyperboloid::v_min=0;
GLdouble hyperboloid::v_max=TWO_PI;

DCoordinate3 hyperboloid::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3((1+cosh(u-3.0/2.0))*sin(v),(1+cosh(u-3.0/2.0))*cos(v),sinh(u-3.0/2.0));
}

DCoordinate3 hyperboloid::d10(GLdouble u, GLdouble v)
{
    return DCoordinate3(sinh(u-3.0/2.0)*sin(v),sinh(u-3.0/2.0)*cos(v),cosh(u-3.0/2.0));
}

DCoordinate3 hyperboloid::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3((1+cosh(u-3.0/2.0))*cos(v),-(1+cosh(u-3.0/2.0))*sin(v),sinh(u-3.0/2.0));
}

//kleinbottle
GLdouble kleinbottle::u_min=0;
GLdouble kleinbottle::u_max=TWO_PI;
GLdouble kleinbottle::v_min=0;
GLdouble kleinbottle::v_max=TWO_PI;

DCoordinate3 kleinbottle::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3(3*cos(u)+1.0/2.0*(1+cos(2*u))*sin(v)+1.0/2.0*sin(2*u)*sin(2*v),
                        3*sin(u)+1.0/2.0*(sin(2*u))*sin(v)-1.0/2.0*(1-cos(2*u))*sin(2*v),
                        cos(u)*sin(2*v)+sin(u)*sin(v));
}

DCoordinate3 kleinbottle::d10(GLdouble u, GLdouble v)
{
    return DCoordinate3(-3*sin(u)-sin(v)*sin(2*u)-cos(2*u)*sin(2*v),
                        -sin(2*v)*sin(2*u)+sin(v)*cos(2*u)+3*(cos(u)),
                        sin(v)*cos(u)-sin(2*v)*sin(u));
}

DCoordinate3 kleinbottle::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3(-sin(2*u)*cos(v)-2*cos(2*u)*cos(2*v),
                        (sin(2*u)*cos(v))/2.0-(1-cos(2*u)*cos(2*v)),
                        2*cos(u)*sin(2*v)+sin(u)*cos(v));
}

//duplincyclide
GLdouble duplincyclide::u_min=0;
GLdouble duplincyclide::u_max=TWO_PI;
GLdouble duplincyclide::v_min=0;
GLdouble duplincyclide::v_max=TWO_PI;

DCoordinate3 duplincyclide::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3((3*(2-6*cos(u)*cos(v))+32*cos(u))/(6-2*cos(u)*cos(v)),
                        (4*sqrt(2)*sin(u)*(6-3*cos(v)))/(6-2*cos(u)*cos(v)),
                        (4*sqrt(2)*sin(v)*(2*cos(u)-3))/(6-2*cos(u)*cos(v)));
}

DCoordinate3 duplincyclide::d10(GLdouble u, GLdouble v)
{
    return DCoordinate3((24*(cos(v)-2)*sin(u))/((cos(v)*cos(u)-3)*(cos(v)*cos(u)-3)),
                        (3*2.8284*(cos(v)-2)*(cos(v)*(sin(u)*sin(u))+cos(v)*(cos(u)*cos(u))-3*cos(u)))/((cos(v)*cos(u)-3)*(cos(v)*cos(u)-3)),
                        (3*2.8284*(cos(v)-2)*sin(v)*sin(u))/((cos(v)*cos(u)-3)*(cos(v)*cos(u)-3)));
}

DCoordinate3 duplincyclide::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3(-(8*cos(u)*(2*cos(u)-3)*sin(v))/((cos(u)*cos(v)-3)*(cos(u)*cos(v)-3)),
                        -((3*2.8284*(2*cos(u)-3)*sin(u)*sin(v))/((cos(u)*cos(v)-3)*(cos(u)*cos(v)-3))),
                        -(2.8284*(2*cos(u)-3)*(cos(u)*(sin(v)*sin(v))+cos(u)*(cos(v)*cos(v))-3*cos(v))/((cos(u)*cos(v)-3)*(cos(u)*cos(v)-3))));
}
