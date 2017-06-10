#include "HermiteCompositeCurves3.h"
#include "../Core/DCoordinates3.h"
#include <iostream>

using namespace std;
using namespace cagd;

HermiteCompositeCurve::HermiteCompositeCurve()
{
    _arcs.reserve(100);
}

GLboolean HermiteCompositeCurve::SetDefaultData(GLuint arc_index,GLuint u_div_point_count,GLuint max_order_of_derivatives)
{

    if (arc_index >= _arcs.size() || !_arcs[arc_index].arc)
    {
        return GL_FALSE;
    }

//    DCoordinate3 &point = (*_attributes[attribute_index].arc)[0];
//    point[0] = 0.0;
//    point[1] = 0.0;
//    point[2] = 0.0; //DCoordinate3(0,0,0);

    DCoordinate3 p = *new DCoordinate3(0,0,0);
    _arcs[arc_index].arc->SetData(0,p);
    p = *new DCoordinate3(1,0,0);
    _arcs[arc_index].arc->SetData(1,p);
    p = *new DCoordinate3(0,0,0);
    _arcs[arc_index].arc->SetData(2,p);
    p = *new DCoordinate3(1,-1,0);
    _arcs[arc_index].arc->SetData(3,p);

    if (_arcs[arc_index].image)
    {
        delete _arcs[arc_index].image;
        _arcs[arc_index].image = nullptr;
    }

    _arcs[arc_index].image = _arcs[arc_index].arc->GenerateImage(max_order_of_derivatives,u_div_point_count);

    if (!_arcs[arc_index].image)
    {
        return GL_FALSE;
    }

    if (!_arcs[arc_index].image->UpdateVertexBufferObjects())
    {
        std::cout<<"StDefaultData error in UpdateVertexBufferObjects"<<std::endl;
        delete _arcs[arc_index].arc;
        delete _arcs[arc_index].image;
        _arcs.resize(_arcs.size() - 1);
        return GL_FALSE;
    }

    _arcs[arc_index].color = nullptr;
    return GL_TRUE;
}

GLboolean HermiteCompositeCurve::InsertNewArc(GLuint u_div_point_count,GLuint max_order_of_derivatives)
{
    GLuint size = _arcs.size();

    _arcs.resize(size + 1);

    _arcs[size].arc = new HermiteArc();

    if (!_arcs[size].arc)
    {
        _arcs.resize(size);
        return GL_FALSE;
    }
    return SetDefaultData(size, u_div_point_count, max_order_of_derivatives);
}

GLboolean HermiteCompositeCurve::InsertNewArc(HermiteArc *curve)
{
    GLuint size = _arcs.size();

    _arcs.resize(size + 1);

    _arcs[size].arc = new HermiteArc();
    _arcs[size].arc = curve;

    if (!_arcs[size].arc)
    {
        _arcs.resize(size);
        return GL_FALSE;
    }

    return GenerateImageOfSelectedCurve(size);
}

GLboolean HermiteCompositeCurve::RenderAll(GLboolean elso, GLboolean masod){
    for(GLuint i = 0;i < _arcs.size();i++)
    {
        if (!_arcs[i].image )//|| !_attributes[x].material)// || !_attributes[x].shader)
        {
            return GL_FALSE;
        }
        glColor3f(1.0,0.0,0.0);
         _arcs[i].image->RenderDerivatives(0,GL_LINE_STRIP);


         if (elso) {
             glColor3f(0.0,0.5,0.0);
            _arcs[i].image ->RenderDerivatives(1,GL_LINES);
            _arcs[i].image ->RenderDerivatives(1,GL_POINTS);
         }

         if (masod) {
            glColor3f(0.1,0.5,0.9);
            _arcs[i].image ->RenderDerivatives(2,GL_LINES);
            _arcs[i].image ->RenderDerivatives(2,GL_POINTS);
         }
         glPointSize(1.0);

    }
    return GL_TRUE;
}

GLboolean HermiteCompositeCurve::SetArcTransX(GLdouble x, GLuint index_of_arc)
{
    if(index_of_arc > _arcs.size() || !_arcs[index_of_arc].arc)
    {
        cout << "Arc index not existing" << endl;
        return GL_FALSE;
    }

    _arcs[index_of_arc].arc->GetData(0)[0] += x;
    _arcs[index_of_arc].arc->GetData(1)[0] += x;

    ArcAttributes *nextarc = _arcs[index_of_arc].next;
    ArcAttributes *previousarc = _arcs[index_of_arc].previous;

    while(nextarc != nullptr)
    {
        nextarc->arc->GetData(0)[0] += x;
        nextarc->arc->GetData(1)[0] += x;

        nextarc = nextarc->next;
    }

    while(previousarc != nullptr)
    {
        previousarc->arc->GetData(0)[0] += x;
        previousarc->arc->GetData(1)[0] += x;

        previousarc = previousarc->previous;
    }

    GenerateImageOfCurves();

    return GL_TRUE;
}

GLboolean HermiteCompositeCurve::SetArcTransY(GLdouble y, GLuint index_of_arc)
{
    if(index_of_arc > _arcs.size() || !_arcs[index_of_arc].arc)
    {
        cout << "Arc index not existing" << endl;
        return GL_FALSE;
    }

    _arcs[index_of_arc].arc->GetData(0)[1] += y;
    _arcs[index_of_arc].arc->GetData(1)[1] += y;

    ArcAttributes *nextarc = _arcs[index_of_arc].next;
    ArcAttributes *previousarc = _arcs[index_of_arc].previous;

    while(nextarc != nullptr)
    {
        nextarc->arc->GetData(0)[1] += y;
        nextarc->arc->GetData(1)[1] += y;

        nextarc = nextarc->next;
    }

    while(previousarc != nullptr)
    {
        previousarc->arc->GetData(0)[1] += y;
        previousarc->arc->GetData(1)[1] += y;

        previousarc = previousarc->previous;
    }

    GenerateImageOfCurves();

    return GL_TRUE;
}

GLboolean HermiteCompositeCurve::SetArcTransZ(GLdouble z, GLuint index_of_arc)
{
    if(index_of_arc > _arcs.size() || !_arcs[index_of_arc].arc)
    {
        cout << "Arc index not existing" << endl;
        return GL_FALSE;
    }

    _arcs[index_of_arc].arc->GetData(0)[2] += z;
    _arcs[index_of_arc].arc->GetData(1)[2] += z;

    ArcAttributes *nextarc = _arcs[index_of_arc].next;
    ArcAttributes *previousarc = _arcs[index_of_arc].previous;

    while(nextarc != nullptr)
    {
        nextarc->arc->GetData(0)[2] += z;
        nextarc->arc->GetData(1)[2] += z;

        nextarc = nextarc->next;
    }

    while(previousarc != nullptr)
    {
        previousarc->arc->GetData(0)[2] += z;
        previousarc->arc->GetData(1)[2] += z;

        previousarc = previousarc->previous;
    }

    GenerateImageOfCurves();

    return GL_TRUE;
}

GLboolean HermiteCompositeCurve::SetTransX(GLdouble x, GLuint index_of_arc, GLuint index)
{
    if(index_of_arc > _arcs.size() || !_arcs[index_of_arc].arc)
    {
        return GL_FALSE;
    }
    if(index == 0)
    {
        _arcs[index_of_arc].arc->GetData(0)[0] += x;
        if(_arcs[index_of_arc].previous != nullptr)
        {
            _arcs[index_of_arc].previous->arc->GetData(1)[0] += x;
        }
    }
    else
    {
        if(_arcs[index_of_arc].next != nullptr)
        {
            _arcs[index_of_arc].next->arc->GetData(0)[0] += x;
        }
        _arcs[index_of_arc].arc->GetData(1)[0] += x;
    }

    GenerateImageOfCurves();

    return GL_TRUE;
}

GLboolean HermiteCompositeCurve::SetTransY(GLdouble y, GLuint index_of_arc, GLuint index)
{
    if(index_of_arc > _arcs.size() || !_arcs[index_of_arc].arc)
    {
        return GL_FALSE;
    }
    if (index == 0)
    {
        if(_arcs[index_of_arc].previous != nullptr)
        {
            _arcs[index_of_arc].previous->arc->GetData(1)[1] += y;
        }
        _arcs[index_of_arc].arc->GetData(0)[1] += y;
    }
    else
    {
        if(_arcs[index_of_arc].next != nullptr)
        {
            _arcs[index_of_arc].next->arc->GetData(0)[1] += y;
        }
        _arcs[index_of_arc].arc->GetData(1)[1] += y;
    }

    GenerateImageOfCurves();

    return GL_TRUE;
}

GLboolean HermiteCompositeCurve::SetTransZ(GLdouble z, GLuint index_of_arc, GLuint index)
{
    if(index_of_arc > _arcs.size() || !_arcs[index_of_arc].arc)
    {
        return GL_FALSE;
    }
    if (index == 0)
    {
        if(_arcs[index_of_arc].previous != nullptr)
        {
            _arcs[index_of_arc].previous->arc->GetData(1)[2] += z;
        }
        _arcs[index_of_arc].arc->GetData(0)[2] += z;
    }
    else
    {
        if(_arcs[index_of_arc].next != nullptr)
        {
            _arcs[index_of_arc].next->arc->GetData(0)[2] += z;
        }
        _arcs[index_of_arc].arc->GetData(1)[2] += z;
    }

    GenerateImageOfCurves();

    return GL_TRUE;
}

GLboolean HermiteCompositeCurve::SetTransTangentX(GLdouble x, GLuint index_of_arc, GLuint index)
{
    if(index_of_arc > _arcs.size() || !_arcs[index_of_arc].arc)
    {
        return GL_FALSE;
    }
    if (index == 0)
    {
        if(_arcs[index_of_arc].previous != nullptr)
        {
            _arcs[index_of_arc].previous->arc->GetData(3)[0] += x;
        }
        _arcs[index_of_arc].arc->GetData(2)[0] += x;
    }
    else
    {
        if(_arcs[index_of_arc].next != nullptr)
        {
            _arcs[index_of_arc].next->arc->GetData(2)[0] += x;
        }
        _arcs[index_of_arc].arc->GetData(3)[0] += x;
    }

    GenerateImageOfCurves();

    return GL_TRUE;
}

GLboolean HermiteCompositeCurve::SetTransTangentY(GLdouble y, GLuint index_of_arc, GLuint index)
{
    if(index_of_arc > _arcs.size() || !_arcs[index_of_arc].arc)
    {
        return GL_FALSE;
    }
    if (index == 0)
    {
        if(_arcs[index_of_arc].previous != nullptr)
        {
            _arcs[index_of_arc].previous->arc->GetData(3)[1] += y;
        }
        _arcs[index_of_arc].arc->GetData(2)[1] += y;
    }
    else
    {
        if(_arcs[index_of_arc].next != nullptr)
        {
            _arcs[index_of_arc].next->arc->GetData(2)[1] += y;
        }
        _arcs[index_of_arc].arc->GetData(3)[1] += y;
    }

    GenerateImageOfCurves();

    return GL_TRUE;
}

GLboolean HermiteCompositeCurve::SetTransTangentZ(GLdouble z, GLuint index_of_arc, GLuint index)
{
    if(index_of_arc > _arcs.size() || !_arcs[index_of_arc].arc)
    {
        return GL_FALSE;
    }
    if (index == 0)
    {
        if(_arcs[index_of_arc].previous != nullptr)
        {
            _arcs[index_of_arc].previous->arc->GetData(3)[2] += z;
        }
        _arcs[index_of_arc].arc->GetData(2)[2] += z;
    }
    else
    {
        if(_arcs[index_of_arc].next != nullptr)
        {
            _arcs[index_of_arc].next->arc->GetData(2)[2] += z;
        }
        _arcs[index_of_arc].arc->GetData(3)[2] += z;
    }

    GenerateImageOfCurves();

    return GL_TRUE;
}

GLboolean HermiteCompositeCurve::GenerateImageOfSelectedCurve(GLuint index_of_arc)
 {
    if (index_of_arc >= _arcs.size() || !_arcs[index_of_arc].arc)
    {
        return GL_FALSE;
    }

    if (_arcs[index_of_arc].image)
    {
        delete _arcs[index_of_arc].image;
        _arcs[index_of_arc].image = nullptr;
    }

    _arcs[index_of_arc].image = _arcs[index_of_arc].arc->GenerateImage(2,40);

    if (!_arcs[index_of_arc].image)
    {
        return GL_FALSE;
    }

    if (!_arcs[index_of_arc].image->UpdateVertexBufferObjects())
    {
        std::cout<<"StDefaultData error"<<std::endl;
        delete _arcs[index_of_arc].arc;
        delete _arcs[index_of_arc].image;
        _arcs.resize(_arcs.size() - 1);
        return GL_FALSE;
    }

    _arcs[index_of_arc].color = nullptr;


     return GL_TRUE;
 }

GLboolean HermiteCompositeCurve::GenerateImageOfCurves()
 {
    for( GLuint i = 0;i < _arcs.size();i++){
        GenerateImageOfSelectedCurve(i);
     }
     return GL_TRUE;
 }

GLboolean HermiteCompositeCurve::PlusFromRight(GLuint index_of_arc)
{
    if (index_of_arc >= _arcs.size() || !_arcs[index_of_arc].arc)
    {
        return GL_FALSE;
    }

    GLuint size = _arcs.size();
    InsertNewArc();

    DCoordinate3 p1 = *new DCoordinate3();
    p1 = _arcs[index_of_arc].arc->GetData(1);
    _arcs[size].arc->SetData(0, p1);

    p1 = _arcs[index_of_arc].arc->GetData(3);
    _arcs[size].arc->SetData(2, p1);

    p1 = _arcs[index_of_arc].arc->GetData(1);
    p1 = 2* p1 - _arcs[index_of_arc].arc->GetData(0);
    _arcs[size].arc->SetData(1,p1);

    p1 = _arcs[index_of_arc].arc->GetData(2);
    _arcs[size].arc->SetData(3,p1);

    _arcs[index_of_arc].next = &_arcs[size];

    return GenerateImageOfCurves();
}

GLboolean HermiteCompositeCurve::PlusFromLeft(GLuint index_of_arc)
{
    if (index_of_arc >= _arcs.size() || !_arcs[index_of_arc].arc)
    {
        return GL_FALSE;
    }

    GLuint size = _arcs.size();
    InsertNewArc();

    DCoordinate3 p1 = *new DCoordinate3();
    p1 = _arcs[index_of_arc].arc->GetData(0);
    _arcs[size].arc->SetData(0, p1);

    p1 = _arcs[index_of_arc].arc->GetData(2);
    _arcs[size].arc->SetData(2, -p1);

    p1 = _arcs[index_of_arc].arc->GetData(0);
    p1 = 2* p1 - _arcs[index_of_arc].arc->GetData(1);
    _arcs[size].arc->SetData(1,p1);

    p1 = _arcs[index_of_arc].arc->GetData(3);
    _arcs[size].arc->SetData(3,-p1);

    _arcs[index_of_arc].previous = &_arcs[size];

    return GenerateImageOfCurves();
}

GLboolean HermiteCompositeCurve::MergeFromRight(GLuint index_of_arc_1, GLuint index_of_arc_2)
{
    if (index_of_arc_1 >= _arcs.size() || !_arcs[index_of_arc_1].arc ||
        index_of_arc_2 >= _arcs.size() || !_arcs[index_of_arc_2].arc )
    {
        return GL_FALSE;
    }

    DCoordinate3 middle = *new DCoordinate3();
    middle = (_arcs[index_of_arc_1].arc->GetData(1) + _arcs[index_of_arc_2].arc->GetData(0)) / 2;
    _arcs[index_of_arc_1].arc->SetData(1,middle);
    _arcs[index_of_arc_2].arc->SetData(0,middle);

    middle = (_arcs[index_of_arc_1].arc->GetData(3) + _arcs[index_of_arc_2].arc->GetData(2)) / 2;
    _arcs[index_of_arc_1].arc->SetData(3,middle);
    _arcs[index_of_arc_2].arc->SetData(2,middle);
    return GenerateImageOfCurves();
    //return GL_TRUE;
}

GLboolean HermiteCompositeCurve::MergeFromLeft(GLuint index_of_arc_1, GLuint index_of_arc_2)
{
    if (index_of_arc_1 >= _arcs.size() || !_arcs[index_of_arc_1].arc ||
        index_of_arc_2 >= _arcs.size() || !_arcs[index_of_arc_2].arc )
    {
        return GL_FALSE;
    }

    DCoordinate3 middle = *new DCoordinate3();
    middle = (_arcs[index_of_arc_1].arc->GetData(0) + _arcs[index_of_arc_2].arc->GetData(1)) / 2;
    _arcs[index_of_arc_1].arc->SetData(0,middle);
    _arcs[index_of_arc_2].arc->SetData(1,middle);

    middle = (_arcs[index_of_arc_1].arc->GetData(2) + _arcs[index_of_arc_2].arc->GetData(3)) / 2;
    _arcs[index_of_arc_1].arc->SetData(2,middle);
    _arcs[index_of_arc_2].arc->SetData(3,middle);


    return GL_TRUE;
}

GLboolean HermiteCompositeCurve::JoinFromRight(GLuint index_of_arc_1, GLuint index_of_arc_2)
{
    if (index_of_arc_1 >= _arcs.size() || !_arcs[index_of_arc_1].arc ||
        index_of_arc_2 >= _arcs.size() || !_arcs[index_of_arc_2].arc ||
        index_of_arc_1 == index_of_arc_2)
    {
        return GL_FALSE;
    }

    GLuint size = _arcs.size();
    InsertNewArc();
    _arcs.resize(size + 1);

    _arcs[size].arc->SetData(0, _arcs[index_of_arc_1].arc->GetData(1));
    _arcs[size].arc->SetData(1, _arcs[index_of_arc_2].arc->GetData(0));

    _arcs[size].arc->SetData(2, _arcs[index_of_arc_1].arc->GetData(3));

    _arcs[size].arc->SetData(3, _arcs[index_of_arc_2].arc->GetData(2));

    return GL_TRUE;
}

GLboolean HermiteCompositeCurve::JoinFromLeft(GLuint index_of_arc_1, GLuint index_of_arc_2)
{
    if (index_of_arc_1 >= _arcs.size() || !_arcs[index_of_arc_1].arc ||
        index_of_arc_2 >= _arcs.size() || !_arcs[index_of_arc_2].arc ||
        index_of_arc_1 == index_of_arc_2)
    {
        return GL_FALSE;
    }

    GLuint size = _arcs.size();
    InsertNewArc();
    _arcs.resize(size + 1);

    _arcs[size].arc->SetData(0, _arcs[index_of_arc_2].arc->GetData(1));
    _arcs[size].arc->SetData(1, _arcs[index_of_arc_1].arc->GetData(0));

    _arcs[size].arc->SetData(2, _arcs[index_of_arc_2].arc->GetData(3));

    _arcs[size].arc->SetData(3, _arcs[index_of_arc_1].arc->GetData(2));

    return GL_TRUE;
}

HermiteCompositeCurve::~HermiteCompositeCurve(){
    for (GLuint i = 0;i<_arcs.size();i++)
    {
        if (_arcs[i].arc)
            delete _arcs[i].arc;
        if (_arcs[i].image)
            delete _arcs[i].image;
        if (_arcs[i].color)
            delete _arcs[i].color;


    }
    _arcs.clear();
}
