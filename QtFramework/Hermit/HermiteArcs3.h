#pragma once

#include "../Core/LinearCombination3.h"

namespace cagd
{
    class  HermiteArc : public LinearCombination3
    {
        private:
            GLuint   _n; //order
        public:
            HermiteArc();
            GLboolean BlendingFunctionValues(GLdouble u, RowMatrix<GLdouble>& values) const;
            GLboolean CalculateDerivatives(GLuint max_order_of_derivatives, GLdouble u, Derivatives& d) const;
            GLboolean SetData(GLuint i,DCoordinate3 point);
            DCoordinate3& GetData(GLuint i);
            GLboolean  BlendingFunctionValues_d1(GLdouble u, RowMatrix<GLdouble>& values) const;
            GLboolean  BlendingFunctionValues_d2(GLdouble u, RowMatrix<GLdouble>& values) const;
    };

}
