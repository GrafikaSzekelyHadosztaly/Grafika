#include "HermiteCompositeCurves3.h"
#include "../Core/DCoordinates3.h"
#include <iostream>

using namespace std;
using namespace cagd;

HermiteCompositeCurve::HermiteCompositeCurve()
{
    _arcs.reserve(100);
}

GLboolean HermiteCompositeCurve::InsertNewArc()
{
    GLuint size = _arcs.size();

    _arcs.resize(size + 1);

    _arcs[size].arc = new HermiteArc();

    if (!_arcs[size].arc)
    {
        _arcs.resize(size);
        return GL_FALSE;
    }
    return GL_TRUE;
}

GLuint HermiteCompositeCurve::GetSizeOfArcs(){
    return _arcs.size();
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

GLboolean HermiteCompositeCurve::InsertIsolatedCurve(vector<DCoordinate3> corners, vector<DCoordinate3> tangents)
{// const &
    GLuint n = _arcs.size();

    _arcs.resize(n + 1);

    _arcs[n]._arc = new HermiteArc();

    _arcs[n].->arc->SetData(0, corners[0]);
    _arcs[n].->arc->SetData(1, corners[1]);

    _arcs[n].->arc->SetData(2, tangents[0]);
    _arcs[n].->arc->SetData(3, tangents[1]);

    GenerateImageOfCurves();

    RenderAll();

    return GL_TRUE;
}

GLboolean HermiteCompositeCurve::RenderAll(GLboolean der1, GLboolean der2){
    for(GLuint i = 0;i < _arcs.size();i++)
    {
        if (!_arcs[i].image )//|| !_attributes[x].material)// || !_attributes[x].shader)
        {
            return GL_FALSE;
        }
        double r = _arcs[i].color[0];
        float g = _arcs[i].color[1];
        float b = _arcs[i].color[2];
        glColor3f(r,g,b);
         _arcs[i].image->RenderDerivatives(0,GL_LINE_STRIP);


         if (der1) {
             glColor3f(0.0,0.5,0.0);
            _arcs[i].image ->RenderDerivatives(1,GL_LINES);
            _arcs[i].image ->RenderDerivatives(1,GL_POINTS);
         }

         if (der2) {
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

    //_arcs[index_of_arc].color = nullptr;


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
    if (index_of_arc >= _arcs.size() || !_arcs[index_of_arc].arc || _arcs[index_of_arc].next!=nullptr)
    {
        return GL_FALSE;
    }
    if(_arcs[index_of_arc].next != nullptr){
        cout << "The selected direction is no free!\n";
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
    _arcs[size].previous = &_arcs[index_of_arc];

    return GenerateImageOfCurves();
}

GLboolean HermiteCompositeCurve::PlusFromLeft(GLuint index_of_arc)
{
    if (index_of_arc >= _arcs.size() || !_arcs[index_of_arc].arc || _arcs[index_of_arc].previous!=nullptr)
    {
        return GL_FALSE;
    }
    if(_arcs[index_of_arc].previous != nullptr){
        cout << "The selected direction is no free!\n";
        return GL_FALSE;
    }

    GLuint size = _arcs.size();
    InsertNewArc();

    DCoordinate3 p1 = *new DCoordinate3();
    p1 = _arcs[index_of_arc].arc->GetData(0);
    _arcs[size].arc->SetData(1, p1);

    p1 = _arcs[index_of_arc].arc->GetData(2);
    _arcs[size].arc->SetData(3, p1);

    p1 = _arcs[index_of_arc].arc->GetData(0);
    p1 = 2* p1 - _arcs[index_of_arc].arc->GetData(1);
    _arcs[size].arc->SetData(0,p1);

    p1 = _arcs[index_of_arc].arc->GetData(3);
    _arcs[size].arc->SetData(2,p1);

    _arcs[index_of_arc].previous = &_arcs[size];
    _arcs[size].next = &_arcs[index_of_arc];

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

    return GenerateImageOfCurves();
    //return GL_TRUE;
}

GLboolean HermiteCompositeCurve::Merge(GLuint index_of_arc_1, GLuint index_of_arc_2, GLuint ind)
{
    if (index_of_arc_1 >= _arcs.size() || !_arcs[index_of_arc_1].arc ||
        index_of_arc_2 >= _arcs.size() || !_arcs[index_of_arc_2].arc )
    {
        return GL_FALSE;
    }
    switch (ind) {
    case 0: // 1-nek a jobb oldalat 2-nek a bal oldalaval
    {
        if(_arcs[index_of_arc_1].next != nullptr || _arcs[index_of_arc_2].previous!=nullptr)
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

        _arcs[index_of_arc_1].next = &_arcs[index_of_arc_2];
        _arcs[index_of_arc_2].previous = &_arcs[index_of_arc_1];
        return GenerateImageOfCurves();

    };
    case 1: //1-nek a jobb oldalaval 2-nek a jobb oldalaval
    {
        if(_arcs[index_of_arc_1].next != nullptr || _arcs[index_of_arc_2].next!=nullptr)
        {
            return GL_FALSE;
        }
        DCoordinate3 middle = *new DCoordinate3();
        middle = (_arcs[index_of_arc_1].arc->GetData(1) + _arcs[index_of_arc_2].arc->GetData(1)) / 2;
        _arcs[index_of_arc_1].arc->SetData(1,middle);
        _arcs[index_of_arc_2].arc->SetData(1,middle);

        middle = (_arcs[index_of_arc_1].arc->GetData(3) + _arcs[index_of_arc_2].arc->GetData(3)) / 2;
        _arcs[index_of_arc_1].arc->SetData(3,middle);
        _arcs[index_of_arc_2].arc->SetData(3,middle);

        _arcs[index_of_arc_1].next = &_arcs[index_of_arc_2];
        _arcs[index_of_arc_2].next = &_arcs[index_of_arc_1];
        return GenerateImageOfCurves();

    };
    case 2: //1-nek a bal oldalat 2-nek a bal oldalaval
    {
        if(_arcs[index_of_arc_1].previous != nullptr || _arcs[index_of_arc_2].previous!=nullptr)
        {
            return GL_FALSE;
        }
        DCoordinate3 middle = *new DCoordinate3();
        middle = (_arcs[index_of_arc_1].arc->GetData(0) + _arcs[index_of_arc_2].arc->GetData(0)) / 2;
        _arcs[index_of_arc_1].arc->SetData(0,middle);
        _arcs[index_of_arc_2].arc->SetData(0,middle);

        middle = (_arcs[index_of_arc_1].arc->GetData(2) + _arcs[index_of_arc_2].arc->GetData(2)) / 2;
        _arcs[index_of_arc_1].arc->SetData(2,middle);
        _arcs[index_of_arc_2].arc->SetData(2,middle);

        _arcs[index_of_arc_1].previous = &_arcs[index_of_arc_2];
        _arcs[index_of_arc_2].previous = &_arcs[index_of_arc_1];
        return GenerateImageOfCurves();
    };
    case 3: //1-nek a bal oldalat 2-nek a jobb oldalaval
    {
        if(_arcs[index_of_arc_1].previous != nullptr || _arcs[index_of_arc_2].next!=nullptr)
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

        _arcs[index_of_arc_1].previous = &_arcs[index_of_arc_2];
        _arcs[index_of_arc_2].next = &_arcs[index_of_arc_1];
        return GenerateImageOfCurves();
    };
    default:
        return GL_FALSE;
        break;
    }
}

GLboolean HermiteCompositeCurve::JoinFromRight(GLuint index_of_arc_1, GLuint index_of_arc_2)
{
    if (index_of_arc_1 >= _arcs.size() || !_arcs[index_of_arc_1].arc ||
        index_of_arc_2 >= _arcs.size() || !_arcs[index_of_arc_2].arc ||
        index_of_arc_1 == index_of_arc_2)
    {
        return GL_FALSE;
    }

    if(_arcs[index_of_arc_2].previous != nullptr || _arcs[index_of_arc_1].next != nullptr){
        return GL_FALSE;
    }

    GLuint size = _arcs.size();
    InsertNewArc();
    _arcs.resize(size + 1);

    _arcs[size].arc->SetData(0, _arcs[index_of_arc_1].arc->GetData(1));
    _arcs[size].arc->SetData(1, _arcs[index_of_arc_2].arc->GetData(0));

    _arcs[size].arc->SetData(2, _arcs[index_of_arc_1].arc->GetData(3));

    _arcs[size].arc->SetData(3, _arcs[index_of_arc_2].arc->GetData(2));

    _arcs[size].previous = &_arcs[index_of_arc_1];
    _arcs[size].next = &_arcs[index_of_arc_2];

    _arcs[index_of_arc_1].next = &_arcs[size];
    _arcs[index_of_arc_2].previous = &_arcs[size];

    return GenerateImageOfCurves();
}

GLboolean HermiteCompositeCurve::JoinFromLeft(GLuint index_of_arc_1, GLuint index_of_arc_2)
{
    if (index_of_arc_1 >= _arcs.size() || !_arcs[index_of_arc_1].arc ||
        index_of_arc_2 >= _arcs.size() || !_arcs[index_of_arc_2].arc ||
        index_of_arc_1 == index_of_arc_2)
    {
        return GL_FALSE;
    }

    if(_arcs[index_of_arc_1].previous != nullptr || _arcs[index_of_arc_2].next != nullptr){
        return GL_FALSE;
    }

    GLuint size = _arcs.size();
    InsertNewArc();
    _arcs.resize(size + 1);

    _arcs[size].arc->SetData(0, _arcs[index_of_arc_2].arc->GetData(1));
    _arcs[size].arc->SetData(1, _arcs[index_of_arc_1].arc->GetData(0));

    _arcs[size].arc->SetData(2, _arcs[index_of_arc_2].arc->GetData(3));

    _arcs[size].arc->SetData(3, _arcs[index_of_arc_1].arc->GetData(2));

    _arcs[size].previous = &_arcs[index_of_arc_2];
    _arcs[size].next = &_arcs[index_of_arc_1];

    _arcs[index_of_arc_2].next = &_arcs[size];
    _arcs[index_of_arc_1].previous = &_arcs[size];

    return GenerateImageOfCurves();
}

GLboolean HermiteCompositeCurve::JoinCurves(GLuint index_of_arc_1, GLuint index_of_arc_2, GLuint case_nr){
    //case_nr - if 0 right to left
    //          if 1 right to right
    //          if 2 left to left
    //          if 3 left to right

    if(index_of_arc_1 >= _arcs.size() || !_arcs[index_of_arc_1].arc ||
            index_of_arc_2 >= _arcs.size() || !_arcs[index_of_arc_2].arc ||
            index_of_arc_1 == index_of_arc_2 || case_nr > 3){
        return GL_FALSE;
    }



    int left_nr, right_nr;

    switch (case_nr) {
    case 0:
        if(_arcs[index_of_arc_1].next != nullptr || _arcs[index_of_arc_2].previous != nullptr){
            return GL_FALSE;
        }
        left_nr = 1;
        right_nr = 0;
        break;
    case 1:
        if(_arcs[index_of_arc_1].next != nullptr || _arcs[index_of_arc_2].next != nullptr){
            return GL_FALSE;
        }
        left_nr = 1;
        right_nr = 1;
        break;
    case 2:
        if(_arcs[index_of_arc_1].previous != nullptr || _arcs[index_of_arc_2].previous != nullptr){
            return GL_FALSE;
        }
        left_nr = 0;
        right_nr = 0;
        break;
    case 3:
        if(_arcs[index_of_arc_1].previous != nullptr || _arcs[index_of_arc_2].next != nullptr){
            return GL_FALSE;
        }
        left_nr = 0;
        right_nr = 1;
        break;
    }

    GLuint size = _arcs.size();
    InsertNewArc();
    _arcs.resize(size + 1);



    _arcs[size].arc->SetData(0, _arcs[index_of_arc_2].arc->GetData(left_nr));
    _arcs[size].arc->SetData(1, _arcs[index_of_arc_1].arc->GetData(right_nr));

    _arcs[size].arc->SetData(2, _arcs[index_of_arc_2].arc->GetData(left_nr + 2));

    _arcs[size].arc->SetData(3, _arcs[index_of_arc_1].arc->GetData(right_nr + 2));

    _arcs[size].previous = &_arcs[index_of_arc_1];
    _arcs[size].next = &_arcs[index_of_arc_2];

    switch (case_nr) {
    case 0:
        _arcs[index_of_arc_1].next = &_arcs[size];
        _arcs[index_of_arc_2].previous = &_arcs[size];
        break;
    case 1:
        _arcs[index_of_arc_1].next = &_arcs[size];
        _arcs[index_of_arc_2].next = &_arcs[size];
        break;
    case 2:
        _arcs[index_of_arc_1].previous = &_arcs[size];
        _arcs[index_of_arc_2].previous = &_arcs[size];
        break;
    case 3:
        _arcs[index_of_arc_1].previous = &_arcs[size];
        _arcs[index_of_arc_2].next = &_arcs[size];
        break;
    }


    return GenerateImageOfCurves();
}

GLboolean HermiteCompositeCurve::SetColor(GLuint index_of_arc, float r, float g, float b)
{
    if (index_of_arc >= _arcs.size() || !_arcs[index_of_arc].arc)
    {
        return GL_FALSE;
    }
    _arcs[index_of_arc].color = *new DCoordinate3(r,g,b);
}


void HermiteCompositeCurve::writeToFile_curve(GLuint i){
    string filename;
    int j = -1;

    ifstream file1;
    do
    {
        j++;
        if(j < 10)
            filename = "Curves/curve0" + to_string(j) + ".txt";
        else
            filename = "Curves/curve" + to_string(j) + ".txt";
        file1.close();
        file1.open(filename);
    }while(file1.good());

    file1.close();

    ofstream file(filename);
    DCoordinate3 out_data;

    out_data = _arcs[i].arc->GetData(0);
    file << out_data[0] << " " << out_data[1] << " " << out_data[2] << endl;
    out_data = _arcs[i].arc->GetData(1);
    file << out_data[0] << " " << out_data[1] << " " << out_data[2] << endl;
    out_data = _arcs[i].arc->GetData(2);
    file << out_data[0] << " " << out_data[1] << " " << out_data[2] << endl;
    out_data = _arcs[i].arc->GetData(3);
    file << out_data[0] << " " << out_data[1] << " " << out_data[2] << endl;

    file.close();
}



HermiteCompositeCurve::~HermiteCompositeCurve(){
    for (GLuint i = 0;i<_arcs.size();i++)
    {
        if (_arcs[i].arc)
            delete _arcs[i].arc;
        if (_arcs[i].image)
            delete _arcs[i].image;
        //if (_arcs[i].color)
         //   delete _arcs[i].color;


    }
    _arcs.clear();
}
