#pragma once

#include <cassert>
#include <iostream>
#include <vector>
#include <GL/glew.h>

#include <Core/Exceptions.h>

namespace cagd
{
    // forward declaration of template class Matrix
    template <typename T>
    class Matrix;

    // forward declaration of template class RowMatrix
    template <typename T>
    class RowMatrix;

    // forward declaration of template class ColumnMatrix
    template <typename T>
    class ColumnMatrix;

	// forward declaration of template class TriangularMatrix
    template <typename T>
    class TriangularMatrix;

    // forward declarations of overloaded and templated input/output from/to stream operators
    template <typename T>
    std::ostream& operator << (std::ostream& lhs, const Matrix<T>& rhs);

    template <typename T>
    std::istream& operator >>(std::istream& lhs, Matrix<T>& rhs);

	template <typename T>
    std::istream& operator >>(std::istream& lhs, TriangularMatrix<T>& rhs);
    
    template <typename T>
    std::ostream& operator << (std::ostream& lhs, const TriangularMatrix<T>& rhs);

    //----------------------
    // template class Matrix
    //----------------------
    template <typename T>
    class Matrix
    {
        friend std::ostream& cagd::operator << <T>(std::ostream&, const Matrix<T>& rhs); // T tipusu lesz csak barat
        friend std::istream& cagd::operator >> <T>(std::istream&, Matrix<T>& rhs);

    protected:
        GLuint                          _row_count;
        GLuint                          _column_count;
        std::vector<std::vector<T>>     _data;
    public:
        // special constructor (can also be used as a default constructor)
        Matrix(GLuint row_count = 1, GLuint column_count = 1);

        // copy constructor 1 - bitenkenti masolas ok, mert nincsenek mutatok; 2! - melysegi masolas
        Matrix(const Matrix& m);

        // assignment operator
        Matrix& operator =(const Matrix& m);

        // get element by reference
        T& operator ()(GLuint row, GLuint column);

        // get copy of an element
        T operator ()(GLuint row, GLuint column) const;

        // get dimensions
        GLuint GetRowCount() const;
        GLuint GetColumnCount() const;

        // set dimensions
        virtual GLboolean ResizeRows(GLuint row_count);
        virtual GLboolean ResizeColumns(GLuint column_count);

        // update
        GLboolean SetRow(GLuint index, const RowMatrix<T>& row);
        GLboolean SetColumn(GLuint index, const ColumnMatrix<T>& column);

        // destructor
        virtual ~Matrix() {}
    };


    //-------------------------
    // template class RowMatrix
    //-------------------------
    template <typename T>
    class RowMatrix: public Matrix<T>
    {
    public:
        // special constructor (can also be used as a default constructor)
        RowMatrix(GLuint column_count = 1);

        // get element by reference
        T& operator ()(GLuint column);
        T& operator [](GLuint column);

        // get copy of an element
        T operator ()(GLuint column) const;
        T operator [](GLuint column) const;

        // a row matrix consists of a single row - row_count ha 1-nel kisebb vagy 1-nel nagyobb, akkor false
        GLboolean ResizeRows(GLuint row_count);
    };

    //----------------------------
    // template class ColumnMatrix
    //----------------------------
    template <typename T>
    class ColumnMatrix: public Matrix<T>
    {
    public:
        // special constructor (can also be used as a default constructor)
        ColumnMatrix(GLuint row_count = 1);

        // get element by reference
        T& operator ()(GLuint row);
        T& operator [](GLuint row);

        // get copy of an element
        T operator ()(GLuint row) const;
        T operator [](GLuint row) const;

        // a column matrix consists of a single column
        GLboolean ResizeColumns(GLuint column_count);
    };

	//--------------------------------
    // template class TriangularMatrix
    //--------------------------------
    template <typename T>
    class TriangularMatrix
    {
        friend std::istream& cagd::operator >> <T>(std::istream&, TriangularMatrix<T>& rhs);
        friend std::ostream& cagd::operator << <T>(std::ostream&, const TriangularMatrix<T>& rhs);
    protected:
        GLuint                        _row_count;
        std::vector< std::vector<T> > _data;

    public:
        // special constructor (can also be used as a default constructor)
        TriangularMatrix(GLuint row_count = 1);

        // get element by reference
        T& operator ()(GLuint row, GLuint column);

        // get copy of an element
        T operator ()(GLuint row, GLuint column) const;

        // get dimension
        GLuint GetRowCount() const;

        // set dimension
        GLboolean ResizeRows(GLuint row_count);
    };







    //--------------------------------------------------
    // homework: implementation of template class Matrix
    //--------------------------------------------------

    // special constructor (can also be used as a default constructor)
    template <typename T>
    inline Matrix<T>::Matrix(GLuint row_count, GLuint column_count)
    {
        _row_count = row_count;
        _column_count = column_count;
        _data.resize(_row_count);
        for (GLuint i = 0; i < row_count; i++)
        {
            _data[i].resize(_column_count);
        }
    }

    /* special constructor - another implementation
    template <typename T>
    inline Matrix<T>::Matrix(GLuint row_count, GLuint column_count): _row_count(row_count),
                                                                     _column_count(column_count),
                                                                     _data(_row_count, std::vector<T>(_column_count))
    { }
    */

    // copy constructor 1 - bitenkenti masolas ok, mert nincsenek mutatok; 2! - melysegi masolas
    template <typename T>
    inline Matrix<T>::Matrix(const Matrix& m): _row_count(m._row_count),
                                               _column_count(m._column_count),
                                               _data(m._data)
    { }

    // assignment operator
    template <typename T>
    inline Matrix<T>& Matrix<T>::operator =(const Matrix& m)
    {
        if (this != &m)
        {
            _row_count = m._row_count;
            _column_count = m._column_count;
            _data = m._data;
        }
        return *this;
    }

    // get element by reference
    template <typename T>
    inline T& Matrix<T>::operator ()(GLuint row, GLuint column)
    {
        assert(row < _row_count && column < _column_count);
        return _data[row][column];
    }

    // get copy of an element
    template <typename T>
    inline T Matrix<T>::operator ()(GLuint row, GLuint column) const
    {
        assert(row < _row_count && column < _column_count);
        return _data[row][column];
    }

    // get dimensions
    template <typename T>
    inline GLuint Matrix<T>::GetRowCount() const
    {
        return _row_count;
    }

    template <typename T>
    inline GLuint Matrix<T>::GetColumnCount() const
    {
        return _column_count;
    }

    // set dimensions
    template <typename T>
    inline GLboolean Matrix<T>::ResizeRows(GLuint row_count)
    {
        /*
        //if (row_count <= 0)
        //    return GL_FALSE;
        if (_row_count == row_count)
            return GL_TRUE;
        else
        {
            if (_row_count > row_count)           // kisebb lett a matrix
            {
                _data.resize(row_count);
                _row_count = row_count;
            }
            else                                  // nagyobb lesz a matrix
            {
                //_data.resize(row_count, std::vector<T>(_column_count));
                _data.resize(row_count);
                for (int i = _row_count; i < row_count; i++)
                    _data[i].resize(_column_count);
                _row_count = row_count;
            }
        }
        return GL_TRUE;
        */

        // Agoston 1
        /*
        _data.resize(row_count);
        for (GLuint r = _row_count; r < row_count; r++)
        {
            _data[i].resize(_column_count;)
        }
        */

        // Agoston 2
        _data.resize(row_count, std::vector<T>(_column_count));         // resize megtartja az eddigi elemeket
        _row_count = row_count;
        return GL_TRUE;
    }

    template <typename T>
    inline GLboolean Matrix<T>::ResizeColumns(GLuint column_count)
    {
        //if (column_count <= 0)
        //    return GL_FALSE;
        //if (_column_count == column_count)
        //    return GL_TRUE;
        //else
        if (_column_count != column_count)
        {
            for (GLuint i = 0; i < _row_count; i++)
                _data[i].resize(column_count);
            _column_count = column_count;
        }
        return GL_TRUE;
    }

    // update
    template <typename T>
    inline GLboolean Matrix<T>::SetRow(GLuint index, const RowMatrix<T>& row)
    {
        if (index < _row_count && row.GetColumnCount() == _data[index].size())
        {
            //for (GLuint i = 0; i < _data[index].size(); i++)
            //{
            //    _data[index][i] = row(i);
            //}
            _data[index] = row._data[0];
            return GL_TRUE;
        }
        else
            return GL_FALSE;
    }

    template <typename T>
    inline GLboolean Matrix<T>::SetColumn(GLuint index, const ColumnMatrix<T>& column)
    {
        if (index < _column_count && column.GetRowCount() == _data.size())
        {
            for (GLuint i = 0; i < _data.size(); i++)
            {
                _data[i][index] = column(i);
            }
            return GL_TRUE;
        }
        else
            return GL_FALSE;
    }

    //-----------------------------------------------------
    // homework: implementation of template class RowMatrix
    //-----------------------------------------------------

    template <typename T>
    inline RowMatrix<T>::RowMatrix(GLuint column_count): Matrix<T>(1, column_count)
    { }

    // get element by reference
    template <typename T>
    inline T& RowMatrix<T>::operator ()(GLuint column)
    {
        return Matrix<T>::operator ()(0, column);
    }

    template <typename T>
    inline T& RowMatrix<T>::operator [](GLuint column)
    {
        return Matrix<T>::operator ()(0, column);
    }

    // get copy of an element
    template <typename T>
    inline T RowMatrix<T>::operator ()(GLuint column) const
    {
        return Matrix<T>::operator ()(0, column);
    }

    template <typename T>
    inline T RowMatrix<T>::operator [](GLuint column) const
    {
        return Matrix<T>::operator ()(0, column);
    }

    // a row matrix consists of a single row - row_count ha 1-nel kisebb vagy 1-nel nagyobb, akkor false
    template <typename T>
    inline GLboolean RowMatrix<T>::ResizeRows(GLuint row_count)
    {
        return row_count == 1;
    }

    //--------------------------------------------------------
    // homework: implementation of template class ColumnMatrix
    //--------------------------------------------------------

    // special constructor (can also be used as a default constructor)
    template <typename T>
    inline ColumnMatrix<T>::ColumnMatrix(GLuint row_count): Matrix<T>(row_count, 1)
    { }

    // get element by reference
    template <typename T>
    inline T& ColumnMatrix<T>::operator ()(GLuint row)
    {
        return Matrix<T>::operator ()(row, 0);
    }

    template <typename T>
    inline T& ColumnMatrix<T>::operator [](GLuint row)
    {
        return Matrix<T>::operator ()(row, 0);
    }


    // get copy of an element
    template <typename T>
    inline T ColumnMatrix<T>::operator ()(GLuint row) const
    {
        return Matrix<T>::operator ()(row, 0);
    }

    template <typename T>
    inline T ColumnMatrix<T>::operator [](GLuint row) const
    {
        return Matrix<T>::operator ()(row, 0);
    }

    // a column matrix consists of a single column
    template <typename T>
    inline GLboolean ColumnMatrix<T>::ResizeColumns(GLuint column_count)
    {
        return column_count == 1;
    }


	//------------------------------------------------------------
    // homework: implementation of template class TriangularMatrix
    //------------------------------------------------------------

    // special constructor (can also be used as a default constructor)
    template <typename T>
    inline TriangularMatrix<T>::TriangularMatrix(GLuint row_count)
    {
        _row_count = row_count;
        _data.resize(_row_count);
        for (GLuint i = 0; i < row_count; i++)
        {
            _data[i].resize(i+1);
        }
    }

    // get element by reference
    template <typename T>
    inline T& TriangularMatrix<T>::operator ()(GLuint row, GLuint column)
    {
        assert(row < _row_count && column <= row);
        return _data[row][column];
    }

    // get copy of an element
    template <typename T>
    inline T TriangularMatrix<T>::operator ()(GLuint row, GLuint column) const
    {
        assert(row < _row_count && column <= row);
        return _data[row][column];
    }

    // get dimension
    template <typename T>
    inline GLuint TriangularMatrix<T>::GetRowCount() const
    {
        return _row_count;
    }

    // set dimension
    template <typename T>
    inline GLboolean TriangularMatrix<T>::ResizeRows(GLuint row_count)
    {
        //if (row_count <= 0)
        //    return GL_FALSE;
        if (_row_count == row_count)
            return GL_TRUE;
        else
        {
            if (_row_count > row_count)           // kisebb lett a matrix
            {
                _data.resize(row_count);
                _row_count = row_count;
            }
            else                                  // nagyobb lesz a matrix
            {
                _data.resize(row_count);
                for (GLuint i = _row_count; i < row_count; i++)
                    _data[i].resize(i+1);
                _row_count = row_count;
            }
        }
        return GL_TRUE;
    }


    //------------------------------------------------------------------------------
    // definitions of overloaded and templated input/output from/to stream operators
    //------------------------------------------------------------------------------
    //------------------------------------------------------------------------------
    // Matrix
    //------------------------------------------------------------------------------

    // output to stream
    template <typename T>
    std::ostream& operator <<(std::ostream& lhs, const Matrix<T>& rhs)
    {
        lhs << rhs._row_count << " " << rhs._column_count << std::endl;
        //for (typename std::vector< std::vector<T> >::const_iterator row = rhs._data.begin(); row != rhs._data.end(); ++row)
        for (const auto& row : rhs._data)
        {
            //for (typename std::vector<T>::const_iterator column = row->begin(); column != row->end(); ++column)
            for (const T& x : row)
                lhs << x << " ";
            lhs << std::endl;
        }
        return lhs;
    }

    /*
    // mine --
    // input from stream
    template <typename T>
    std::istream& operator >>(std::istream& lhs, Matrix<T>& rhs)
    {
        int rows, columns;
        lhs >> rows >> columns;

        rhs.ResizeRows(rows);
        rhs.ResizeColumns(columns);

        for (int i = 0; i < rhs._row_count; i++)
        {
            for (int j = 0; j < rhs._column_count; j++)
                lhs >> rhs(i,j);
        }
        return lhs;
    }
    */

    // input from stream
    template <typename T>
    std::istream& operator >>(std::istream& lhs, Matrix<T>& rhs)
    {
        lhs >> rhs._row_count >> rhs._column_count;
        rhs._data.resize(rhs._row_count);
        for (typename std::vector<std::vector<T>>::iterator row = rhs._data.begin(); row != rhs._data.end(); row++)
        {
            row->resize(rhs._column_count);
            for (typename std::vector<T>::iterator column = row->begin(); column != row->end(); column++)
                lhs >> *column;
        }
        return lhs;
    }


    //------------------------------------------------------------------------------
    // TriangularMatrix
    //------------------------------------------------------------------------------

    // output to stream
    template <typename T>
    std::ostream& operator <<(std::ostream& lhs, const TriangularMatrix<T>& rhs)
    {
        lhs << rhs._row_count << std::endl;
        //for (typename std::vector< std::vector<T> >::const_iterator row = rhs._data.begin(); row != rhs._data.end(); ++row)
        for (const auto& row : rhs._data)
        {
            //for (typename std::vector<T>::const_iterator column = row->begin(); column != row->end(); ++column)
            for (const T& x : row)
                lhs << x << " ";
            lhs << std::endl;
        }
        return lhs;
    }


    // homework
    // input from stream
    template <typename T>
    std::istream& operator >>(std::istream& lhs, TriangularMatrix<T>& rhs)
    {
        int rows;
        lhs >> rows;

        rhs.ResizeRows(rows);

        for (int i = 0; i < rhs._row_count; i++)
        {
            for (int j = 0; j <= i; j++)
                lhs >> rhs(i,j);
        }
        return lhs;
    }
}
