#pragma once
#include <iostream>
#include <vector>
#include <QFile>
#include <QTextStream>
#include "../Core/DCoordinates3.h"
#include "../Core/Colors4.h"
#include "../Core/GenericCurves3.h"
#include "../Hermit/HermiteArcs3.h"

using namespace cagd;
class HermiteCompositeCurve
{
public:
    HermiteCompositeCurve();

    class ArcAttributes
              {
                  public:
                      HermiteArc      *arc;
                      GenericCurve3   *image;
                      Color4          *color;
                      ArcAttributes   *next;
                      ArcAttributes   *previous;
                      //konstruktor

                      ArcAttributes()
                      {
                          arc = nullptr;
                          image = nullptr;
                          color = nullptr;
                          next = nullptr;
                          previous = nullptr;

                      }
              };

protected:
            std::vector<ArcAttributes>  _arcs;
public:

            GLboolean SetDefaultData(GLuint arc_index, GLuint u_div_point_count,GLuint max_order_of_derivatives);
            GLboolean InsertNewArc(GLuint u_div_point_count = 40,GLuint max_order_of_derivatives = 2);
            GLboolean InsertNewArc(HermiteArc* curve);
            GLboolean RenderAll(GLboolean elso = GL_FALSE, GLboolean masod = GL_FALSE);
            GLboolean GenerateImageOfSelectedCurve(GLuint arc_index);
            GLboolean GenerateImageOfCurves();
            GLboolean SetArcTransX(GLdouble x, GLuint index_of_arc);
            GLboolean SetArcTransY(GLdouble y, GLuint index_of_arc);
            GLboolean SetArcTransZ(GLdouble z, GLuint index_of_arc);
            GLboolean SetTransX(GLdouble x, GLuint index_of_arc, GLuint index);
            GLboolean SetTransY(GLdouble y, GLuint index_of_arc, GLuint index);
            GLboolean SetTransZ(GLdouble z, GLuint index_of_arc, GLuint index);
            GLboolean SetTransTangentX(GLdouble x, GLuint index_of_arc, GLuint index);
            GLboolean SetTransTangentY(GLdouble y, GLuint index_of_arc, GLuint index);
            GLboolean SetTransTangentZ(GLdouble z, GLuint index_of_arc, GLuint index);

            GLboolean PlusFromRight(GLuint attribute_index);
            GLboolean PlusFromLeft(GLuint attribute_index);

            GLboolean MergeFromRight(GLuint attribute_index_1, GLuint attribute_index_2);
            GLboolean MergeFromLeft(GLuint attribute_index_1, GLuint attribute_index_2);

            GLboolean JoinFromRight(GLuint attribute_index_1, GLuint attribute_index_2);
            GLboolean JoinFromLeft(GLuint attribute_index_1, GLuint attribute_index_2);

            ~HermiteCompositeCurve();

};
