#include "HermiteArcs3.h"


using namespace cagd;

HermiteArc::HermiteArc() : LinearCombination3(0,1,4)
{
    _n = 2;
}

GLdouble Z0(GLdouble i) {
    return 2*i*i*i - 3*i*i + 1;
}

GLdouble Z1(GLdouble i) {
    return -2*i*i*i + 3*i*i;
}

GLdouble Z2(GLdouble i) {
    return i*i*i - 2*i*i + i;
}

GLdouble Z3(GLdouble i) {
    return i*i*i - i*i;
}

// Elsorendu derivaltak:
GLdouble Z0_d1(GLdouble i) {
    return 6 * i * (i-1);
}

GLdouble Z1_d1(GLdouble i) {
    return -6 * i * (i-1);
}

GLdouble Z2_d1(GLdouble i) {
    return 3*i*i - 4*i + 1;
}

GLdouble Z3_d1(GLdouble i) {
    return i * (3*i - 2);
}


// Masodrendu derivaltak:
GLdouble Z0_d2(GLdouble i) {
    return 12 * i - 6;
}

GLdouble Z1_d2(GLdouble i) {
    return -12 * i + 6;
}

GLdouble Z2_d2(GLdouble i){
    return 6 * i - 4;
}

GLdouble Z3_d2(GLdouble i){
    return 6 * i - 2;
}

// Harmadrendu derivaltak:
/*
GLdouble F0_d3(GLdouble i){
    return 12;
}

GLdouble F1_d3(GLdouble i){
    return -12;
}

GLdouble F2_d3(GLdouble i){
    return 6;
}

GLdouble F3_d3(GLdouble i){
    return 6;
}
*/

GLboolean HermiteArc::BlendingFunctionValues(GLdouble u, RowMatrix<GLdouble>& values) const
{
    if(u < _u_min || u > _u_max)
        return GL_FALSE;

    values.ResizeColumns(4);
    values[0] = Z0(u);
    values[1] = Z1(u);
    values[2] = Z2(u);
    values[3] = Z3(u);
    return GL_TRUE;
}

GLboolean HermiteArc::BlendingFunctionValues_d1(GLdouble u, RowMatrix<GLdouble>& values) const
{
    if(u < _u_min || u > _u_max)
        return GL_FALSE;

    values.ResizeColumns(4);
    values[0] = Z0_d1(u);
    values[1] = Z1_d1(u);
    values[2] = Z2_d1(u);
    values[3] = Z3_d1(u);
    return GL_TRUE;
}

GLboolean HermiteArc::BlendingFunctionValues_d2(GLdouble u, RowMatrix<GLdouble>& values) const
{
    if(u < _u_min || u > _u_max)
        return GL_FALSE;

    values.ResizeColumns(4);
    values[0] = Z0_d2(u);
    values[1] = Z1_d2(u);
    values[2] = Z2_d2(u);
    values[3] = Z3_d2(u);
    return GL_TRUE;
}
 GLboolean HermiteArc::CalculateDerivatives(GLuint max_order_of_derivatives, GLdouble u, Derivatives& d) const
 {
     if (max_order_of_derivatives > 2)
     {
         return GL_FALSE;
     }

     Matrix<GLdouble> dF(max_order_of_derivatives+1,_data.GetRowCount());
     d.ResizeRows(max_order_of_derivatives + 1);
     d.LoadNullVectors();
      //be kell tenni a nulla es elsorendu derivaltakat
     RowMatrix<GLdouble> u_blending_values(4);
     RowMatrix<GLdouble> u_blending_values_d1(4);
     RowMatrix<GLdouble> u_blending_values_d2(4);
     if (!BlendingFunctionValues(u,u_blending_values) || !BlendingFunctionValues_d1(u,u_blending_values_d1) || !BlendingFunctionValues_d2(u,u_blending_values_d2))
     {
         d.ResizeColumns(0);
         return GL_FALSE;
     }
    dF.SetRow(0,u_blending_values);
    dF.SetRow(1,u_blending_values_d1);
    dF.SetRow(2,u_blending_values_d2);
    for(int r = 0;r<= max_order_of_derivatives; r++)
    {
        for(int i = 0;i < _data.GetRowCount(); i++)
        {
            d[r] += _data[i] * dF(r,i);
        }
    }

     return GL_TRUE;

 }

GLboolean HermiteArc::SetData(GLuint i, DCoordinate3 point)
{
    //lekezeles
    _data[i] = point;
    return GL_TRUE;
}

DCoordinate3& HermiteArc::GetData(GLuint i)
{
    return _data[i];
}

