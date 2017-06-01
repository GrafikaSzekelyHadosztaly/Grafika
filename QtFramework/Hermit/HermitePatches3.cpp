#include "Hermit/HermitePatches3.h"
#include "Core/Constants.h"
#include <iostream>

using namespace std;

using namespace cagd;

HermitePatch::HermitePatch(): TensorProductSurface3(EPS, 1.0-EPS, EPS, 1.0-EPS, 4, 4)
{
}

// Alap fuggvenyek:
GLdouble F0(GLdouble i) {
    return 2*i*i*i - 3*i*i + 1;
}

GLdouble F1(GLdouble i) {
    return -2*i*i*i + 3*i*i;
}

GLdouble F2(GLdouble i) {
    return i*i*i - 2*i*i + i;
}

GLdouble F3(GLdouble i) {
    return i*i*i - i*i;
}

// Elsorendu derivaltak:
GLdouble F0_d1(GLdouble i) {
    return 6 * i * (i-1);
}

GLdouble F1_d1(GLdouble i) {
    return -6 * i * (i-1);
}

GLdouble F2_d1(GLdouble i) {
    return 3*i*i - 4*i + 1;
}

GLdouble F3_d1(GLdouble i) {
    return i * (3*i - 2);
}

// Masodrendu derivaltak:
GLdouble F0_d2(GLdouble i) {
    return 12 * i - 6;
}

GLdouble F1_d2(GLdouble i) {
    return -12 * i + 6;
}

GLdouble F2_d2(GLdouble i){
    return 6 * i - 4;
}

GLdouble F3_d2(GLdouble i){
    return 6 * i - 2;
}

// Harmadrendu derivaltak:
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


GLboolean HermitePatch::SetCorner(GLuint i, GLuint j, GLdouble x, GLdouble y, GLdouble z)
{
    if (i > 1 || j > 1)
    {
        return GL_FALSE;
    }

    DCoordinate3 &corner = _data(i, j);

    corner[0] = x;
    corner[1] = y;
    corner[2] = z;

    return GL_TRUE;
}

GLboolean HermitePatch::SetCorner(GLuint i, GLuint j, const DCoordinate3 &corner)
{
    if (i > 1 || j > 1)
    {
        return GL_FALSE;
    }

    _data(i, j) = corner;

    return GL_TRUE;
}

DCoordinate3& HermitePatch::GetCorner(GLuint i, GLuint j){
    return _data(i, j);
}

GLboolean HermitePatch::SetUTangent(GLuint i, GLuint j, GLdouble x, GLdouble y, GLdouble z)
{
    if (i > 1 || j > 1)
    {
        return GL_FALSE;
    }

    DCoordinate3 &tangent = _data(i + 2, j);

    tangent[0] = x;
    tangent[1] = y;
    tangent[2] = z;

    return GL_TRUE;
}

GLboolean HermitePatch::SetUTangent(GLuint i, GLuint j, const DCoordinate3 &tangent)
{
    if (i > 1 || j > 1)
    {
        return GL_FALSE;
    }

    _data(i + 2, j) = tangent;

    return GL_TRUE;
}

DCoordinate3& HermitePatch::GetUTangent(GLuint i, GLuint j){
    return _data(i + 2, j);
}

GLboolean HermitePatch::SetVTangent(GLuint i, GLuint j, GLdouble x, GLdouble y, GLdouble z)
{
    if (i > 1 || j > 1)
    {
        return GL_FALSE;
    }

    DCoordinate3 &tangent = _data(i, j + 2);

    tangent[0] = x;
    tangent[1] = y;
    tangent[2] = z;

    return GL_TRUE;
}

GLboolean HermitePatch::SetVTangent(GLuint i, GLuint j, const DCoordinate3 &tangent)
{
    if (i > 1 || j > 1)
    {
        return GL_FALSE;
    }

    _data(i, j + 2) = tangent;

    return GL_TRUE;
}

DCoordinate3& HermitePatch::GetVTangent(GLuint i, GLuint j){
    return _data(i, j + 2);
}

GLboolean HermitePatch::SetTwist(GLuint i, GLuint j, GLdouble x, GLdouble y, GLdouble z)
{
    if (i > 1 || j > 1)
    {
        return GL_FALSE;
    }

    DCoordinate3 &twist = _data(i + 2, j + 2);

    twist[0] = x;
    twist[1] = y;
    twist[2] = z;

    return GL_TRUE;
}



GLboolean HermitePatch::SetTwist(GLuint i, GLuint j, const DCoordinate3 &twist)
{
    if (i > 1 || j > 1)
    {
        return GL_FALSE;
    }

    _data(i + 2, j + 2) = twist;

    return GL_TRUE;
}

DCoordinate3& HermitePatch::GetTwist(GLuint i, GLuint j){
    return _data(i + 2, j + 2);
}

GLboolean HermitePatch::UBlendingFunctionValues(GLdouble u, RowMatrix<GLdouble> &blending_values) const
{
    if(u < _u_min || u > _u_max){
        cout << "in UBlendingFunctionValues()" << endl;
        return GL_FALSE;
    }

    blending_values.ResizeColumns(4);
    blending_values(0) = F0(u);
    blending_values(1) = F1(u);
    blending_values(2) = F2(u);
    blending_values(3) = F3(u);

    return GL_TRUE;
}

GLboolean HermitePatch::VBlendingFunctionValues(GLdouble v, RowMatrix<GLdouble> &blending_values) const
{
    if(v < _v_min || v > _v_max){
        cout << "in VBlendingFunctionValues()" << endl;
        return GL_FALSE;
    }
    blending_values.ResizeColumns(4);
    blending_values(0) = F0(v);
    blending_values(1) = F1(v);
    blending_values(2) = F2(v);
    blending_values(3) = F3(v);

    return GL_TRUE;
}

// Elsorendu derivaltak
GLboolean HermitePatch::UBlendingFunctionValues_d1(GLdouble u, RowMatrix<GLdouble> & u_d1_blending_values) const
{
    if(u < _u_min || u > _u_max)
        return GL_FALSE;

    u_d1_blending_values.ResizeColumns(4);
    u_d1_blending_values[0] = F0_d1(u);
    u_d1_blending_values[1] = F1_d1(u);
    u_d1_blending_values[2] = F2_d1(u);
    u_d1_blending_values[3] = F3_d1(u);
    return GL_TRUE;
}

GLboolean HermitePatch::VBlendingFunctionValues_d1(GLdouble v, RowMatrix<GLdouble> & v_d1_blending_values) const
{
    if(v < _v_min || v > _v_max)
        return GL_FALSE;

    v_d1_blending_values.ResizeColumns(4);
    v_d1_blending_values[0] = F0_d1(v);
    v_d1_blending_values[1] = F1_d1(v);
    v_d1_blending_values[2] = F2_d1(v);
    v_d1_blending_values[3] = F3_d1(v);
    return GL_TRUE;
}

// Masodrendu derivaltak
GLboolean HermitePatch::UBlendingFunctionValues_d2(GLdouble u, RowMatrix<GLdouble> & u_d2_blending_values) const
{
    if(u < _u_min || u > _u_max)
        return GL_FALSE;

    u_d2_blending_values.ResizeColumns(4);
    u_d2_blending_values[0] = F0_d2(u);
    u_d2_blending_values[1] = F1_d2(u);
    u_d2_blending_values[2] = F2_d2(u);
    u_d2_blending_values[3] = F3_d2(u);
    return GL_TRUE;
}

GLboolean HermitePatch::VBlendingFunctionValues_d2(GLdouble v, RowMatrix<GLdouble> & v_d2_blending_values) const
{
    if(v < _v_min || v > _v_max)
        return GL_FALSE;

    v_d2_blending_values.ResizeColumns(4);
    v_d2_blending_values[0] = F0_d2(v);
    v_d2_blending_values[1] = F1_d2(v);
    v_d2_blending_values[2] = F2_d2(v);
    v_d2_blending_values[3] = F3_d2(v);
    return GL_TRUE;
}

// Harmadrendu derivaltak
GLboolean HermitePatch::UBlendingFunctionValues_d3(GLdouble u, RowMatrix<GLdouble> & u_d3_blending_values) const
{
    if(u < _u_min || u > _u_max)
        return GL_FALSE;

    u_d3_blending_values.ResizeColumns(4);
    u_d3_blending_values[0] = F0_d3(u);
    u_d3_blending_values[1] = F1_d3(u);
    u_d3_blending_values[2] = F2_d3(u);
    u_d3_blending_values[3] = F3_d3(u);
    return GL_TRUE;
}

GLboolean HermitePatch::VBlendingFunctionValues_d3(GLdouble v, RowMatrix<GLdouble> & v_d3_blending_values) const
{
    if(v < _v_min || v > _v_max)
        return GL_FALSE;

    v_d3_blending_values.ResizeColumns(4);
    v_d3_blending_values[0] = F0_d3(v);
    v_d3_blending_values[1] = F1_d3(v);
    v_d3_blending_values[2] = F2_d3(v);
    v_d3_blending_values[3] = F3_d3(v);
    return GL_TRUE;
}

GLboolean HermitePatch::CalculatePartialDerivatives(GLuint maximum_order_of_derivatives,
                                               GLdouble u, GLdouble v, PartialDerivatives &pd) const
{
    if(u < _u_min || u > _u_max || v < _v_min || v > _v_max || maximum_order_of_derivatives > 3){
        pd.ResizeRows(0);
        cout << 0 << endl;
        return GL_FALSE;
    }


    // u-val sima:
    RowMatrix<GLdouble> u_blending_values(4);
    // v-vel sima:
    RowMatrix<GLdouble> v_blending_values(4);

    if(!UBlendingFunctionValues(u,u_blending_values) || !VBlendingFunctionValues(v,v_blending_values))
    {
        pd.ResizeRows(0);
        cout << 1 << endl;
        return GL_FALSE;
    }

    // u-val elsorendu derivalt:
    RowMatrix<GLdouble> u_d1_blending_values(4);
    // v-vel elsorendu derivalt:
    RowMatrix<GLdouble> v_d1_blending_values(4);

    if(!UBlendingFunctionValues_d1(u,u_d1_blending_values) || !VBlendingFunctionValues_d1(v,v_d1_blending_values))
    {
        pd.ResizeRows(0);
        return GL_FALSE;
    }
/*
    // u-val masodrendu derivalt:
    RowMatrix<GLdouble> u_d2_blending_values;
    // v-vel masodrendu derivalt:
    RowMatrix<GLdouble> v_d2_blending_values;

    if(!UBlendingFunctionValues_d2(u,u_d2_blending_values) || !VBlendingFunctionValues_d2(v,v_d2_blending_values))
    {
        pd.ResizeRows(0);
        return GL_FALSE;
    }

    // u-val harmadrendu derivalt:
    RowMatrix<GLdouble> u_d3_blending_values;
    // v-vel harmadrendu derivalt:
    RowMatrix<GLdouble> v_d3_blending_values;

    if(!UBlendingFunctionValues_d3(u,u_d3_blending_values) || !VBlendingFunctionValues_d3(v,v_d3_blending_values))
    {
        pd.ResizeRows(0);
        return GL_FALSE;
    }
*/

    pd.ResizeRows(maximum_order_of_derivatives + 1);
    pd.LoadNullVectors();

    for (GLuint i = 0; i < _data.GetRowCount(); i++)
    {
        DCoordinate3 aux_d0_v, aux_d1_v, aux_d2_v, aux_d3_v;
        for (GLuint j = 0; j < _data.GetColumnCount(); j++)
        {
            aux_d0_v += _data(i,j) * v_blending_values(j);
            aux_d1_v += _data(i,j) * v_d1_blending_values(j);
           // aux_d2_v += _data(i,j) * v_d2_blending_values(j);
           // aux_d3_v += _data(i,j) * v_d3_blending_values(j);
        }

        pd(0,0) += aux_d0_v * u_blending_values(i);
        pd(1,0) += aux_d0_v * u_d1_blending_values(i);
        pd(1,1) += aux_d1_v * u_blending_values(i);

      /*  pd(2,0) += aux_d0_v * u_d2_blending_values(i);
        pd(2,1) += aux_d1_v * u_d1_blending_values(i);
        pd(2,2) += aux_d2_v * u_blending_values(i);

        pd(3,0) += aux_d0_v * u_d3_blending_values(i);
        pd(3,1) += aux_d1_v * u_d2_blending_values(i);
        pd(3,2) += aux_d2_v * u_d1_blending_values(i);
        pd(3,3) += aux_d3_v * u_blending_values(i);*/
    }

    return GL_TRUE;
}










