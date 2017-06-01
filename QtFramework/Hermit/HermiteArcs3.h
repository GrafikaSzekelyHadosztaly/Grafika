#pragma once

#include "Core/LinearCombination3.h"

namespace cagd
{
    class HermiteArc3:public LinearCombination3 // -> beagyazott osztaly: class Derivatives:public ColumnMatrix<DCoordinate3>
    {
        protected:
            //possible shape parameters (e.g. GLdouble _alpha)
        public:
            HermiteArc3(/*possible shape parameters*/);
            GLdouble BlendingFunctionValues(GLdouble u, RowMatrix<GLdouble> &values); //values: [F0(u), F1(u),F2(u),F3(u)] -> fuggveny implementalas, projektfuggo
            GLboolean CalculateDerivatives(GLdouble maximum_order_of_derivatives /*(>=2)*/, GLdouble u, Derivatives &d) const;
            
    };
}
