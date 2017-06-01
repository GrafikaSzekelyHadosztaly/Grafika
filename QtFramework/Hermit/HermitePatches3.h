#pragma once

#include "Core/TensorProductSurfaces3.h"

namespace cagd {
    class HermitePatch: public TensorProductSurface3 //->beagyazott osztaly: class PartialDerivatives:public TriangularMatrix<DCoordinate3>
    {
        protected:
            //possible shape parameters
        public:
            HermitePatch(/*Possible shape parameters*/);
            GLboolean UBlendingFunctionValues(GLdouble u, RowMatrix<GLdouble> &values) const;
            GLboolean VBlendingFunctionValues(GLdouble v, RowMatrix<GLdouble> &values) const;
            GLboolean CalculatePartialDerivatives(GLuint max_order_of_partial_derivaives/*(>=1)*/, GLdouble u, GLdouble v, PartialDerivatives &pd) const;

            GLboolean SetCorner(GLuint i, GLuint j, GLdouble x, GLdouble y, GLdouble z);
            GLboolean SetCorner(GLuint i, GLuint j, const DCoordinate3 &corner);
            DCoordinate3& GetCorner(GLuint i, GLuint j);

            GLboolean SetUTangent(GLuint i, GLuint j, GLdouble x, GLdouble y, GLdouble z);
            GLboolean SetUTangent(GLuint i, GLuint j, const DCoordinate3 &tangent);
            DCoordinate3& GetUTangent(GLuint i, GLuint j);

            GLboolean SetVTangent(GLuint i, GLuint j, GLdouble x, GLdouble y, GLdouble z);
            GLboolean SetVTangent(GLuint i, GLuint j, const DCoordinate3 &tangent);
            DCoordinate3& GetVTangent(GLuint i, GLuint j);

            GLboolean SetTwist(GLuint i, GLuint j, GLdouble x, GLdouble y, GLdouble z);
            GLboolean SetTwist(GLuint i, GLuint j, const DCoordinate3 &twist);
            DCoordinate3& GetTwist(GLuint i, GLuint j);

            GLboolean UBlendingFunctionValues_d1(GLdouble u, RowMatrix<GLdouble> & u_d1_blending_values) const;
            GLboolean VBlendingFunctionValues_d1(GLdouble u, RowMatrix<GLdouble> & u_d1_blending_values) const;
            GLboolean UBlendingFunctionValues_d2(GLdouble u, RowMatrix<GLdouble> & u_d2_blending_values) const;
            GLboolean VBlendingFunctionValues_d2(GLdouble u, RowMatrix<GLdouble> & u_d2_blending_values) const;
            GLboolean UBlendingFunctionValues_d3(GLdouble u, RowMatrix<GLdouble> & u_d3_blending_values) const;
            GLboolean VBlendingFunctionValues_d3(GLdouble u, RowMatrix<GLdouble> & u_d3_blending_values) const;
    };
}
