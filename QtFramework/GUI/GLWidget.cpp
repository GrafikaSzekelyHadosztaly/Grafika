#include "GLWidget.h"

#include <iostream>
using namespace std;

#include <GL/GLU.h>
#include <Core/Exceptions.h>
#include "Core/Constants.h"
#include "Core/Matrices.h"
#include "Test/TestFunctions.h"
#include "Core/Constants.h"
#include "Core/Lights.h"
#include "Core/Materials.h"
#include <fstream>
#include <string>

namespace cagd
{
    //--------------------------------
    // special and default constructor
    //--------------------------------
    GLWidget::GLWidget(QWidget *parent, const QGLFormat &format): QGLWidget(format, parent)
    {
        _timer = new QTimer(this);
        _timer->setInterval(0);


        connect(_timer, SIGNAL(timeout()),this, SLOT(_animate()));
    }

    GLWidget::~GLWidget()
    {
        for(GLuint i = 0; i < 5; i++)
        {
            if(_pc[i])
                delete _pc[i], _pc[i] = 0;

            if(_image_of_pc[i])
                delete _image_of_pc[i], _image_of_pc[i] = 0;
        }

        if(_dl)
            delete _dl;
    }


    //--------------------------------------------------------------------------------------
    // this virtual function is called once before the first call to paintGL() or resizeGL()
    //--------------------------------------------------------------------------------------
    void GLWidget::initializeGL()
    {
        // creating a perspective projection matrix
        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        _aspect = (float)width() / (float)height();
        _z_near = 1.0;
        _z_far = 1000.0;
        _fovy = 45.0;

        gluPerspective(_fovy, _aspect, _z_near, _z_far);

        // setting the model view matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        _eye[0] = _eye[1] = 0.0, _eye[2] = 6.0;
        _center[0] = _center[1] = _center[2] = 0.0;
        _up[0] = _up[2] = 0.0, _up[1] = 1.0;

        gluLookAt(_eye[0], _eye[1], _eye[2], _center[0], _center[1], _center[2], _up[0], _up[1], _up[2]);

        // enabling depth test
        glEnable(GL_DEPTH_TEST);
//Fcolor
        // setting the color of background
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // initial values of transformation parameters
        _angle_x = _angle_y = _angle_z = 0.0;
        _trans_x = _trans_y = _trans_z = 0.0;
        _zoom = 1.0;

        try
        {
            // initializing the OpenGL Extension Wrangler library
            glEnable(GL_POINT_SMOOTH);
            glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
            glEnable(GL_LINE_SMOOTH);
            glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
            glEnable(GL_POLYGON_SMOOTH);
            glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

            glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

            GLenum error = glewInit();

            if (error != GLEW_OK)
            {
                throw Exception("Could not initialize the OpenGL Extension Wrangler Library!");
            }

            if (!glewIsSupported("GL_VERSION_2_0"))
            {
                throw Exception("Your graphics card is not compatible with OpenGL 2.0+! "
                                "Try to update your driver or buy a new graphics adapter!");
            }

            // create and store your geometry in display lists or vertex buffer objects
            // ...

            _div_point_count = 100;
            _v_div_point_count = 200;
            _usage_flag = GL_STATIC_DRAW;

            _cc = 0;
            _img_cc = 0;

            _angle = 0.0;

            _before_interpolation = 0;
            _after_interpolation = 0;

            _img_select = 8;
            _img_index  = 0;

            _dl = 0;
            _dl = new DirectionalLight(GL_LIGHT0, HCoordinate3(0, 0, 1, 0), Color4(0.4, 0.4, 0.4), Color4(0.8, 0.8, 0.8), Color4(1.0,1.0,1.0));

            // PARAMETRIC CURVE
            {
                {
                    //spiral on cone
                    RowMatrix<ParametricCurve3::Derivative> derivative(3);
                    derivative(0) = spiral_on_cone::d0;
                    derivative(1) = spiral_on_cone::d1;
                    derivative(2) = spiral_on_cone::d2;

                    _pc[0] = new ParametricCurve3(derivative, spiral_on_cone::u_min, spiral_on_cone::u_max);
                    if(!_pc[0])
                    {
                        throw Exception("Parametric curve letrehozas hiba");
                    }

                    _image_of_pc[0] = _pc[0]->GenerateImage(_div_point_count, _usage_flag);

                    if(!_image_of_pc[0])
                    {
                        throw Exception("Parametric curve image letrehozas hiba");
                    }

                    if(!_image_of_pc[0]->UpdateVertexBufferObjects(_usage_flag))
                    {
                        throw Exception("Could not crete the vertex buffer object of the parametric curve!");
                    }
                }
                {
                    //torus
                    RowMatrix<ParametricCurve3::Derivative> derivative(3);
                    derivative(0) = torus::d0;
                    derivative(1) = torus::d1;
                    derivative(2) = torus::d2;

                    _pc[1] = new ParametricCurve3(derivative, torus::u_min, torus::u_max);
                    if(!_pc[1])
                    {
                        throw Exception("Parametric curve letrehozas hiba");
                    }

                    _image_of_pc[1] = _pc[1]->GenerateImage(_div_point_count, _usage_flag);

                    if(!_image_of_pc[1])
                    {
                        throw Exception("Parametric curve image letrehozas hiba");
                    }

                    if(!_image_of_pc[1]->UpdateVertexBufferObjects(_usage_flag))
                    {
                        throw Exception("Could not crete the vertex buffer object of the parametric curve!");
                    }

                }
                {
                    //elipszis
                    RowMatrix<ParametricCurve3::Derivative> derivative(3);
                    derivative(0) = ellipse::d0;
                    derivative(1) = ellipse::d1;
                    derivative(2) = ellipse::d2;

                    _pc[2] = new ParametricCurve3(derivative, ellipse::u_min, ellipse::u_max);
                    if(!_pc[2])
                    {
                        throw Exception("Parametric curve letrehozas hiba");
                    }

                    _image_of_pc[2] = _pc[2]->GenerateImage(_div_point_count, _usage_flag);

                    if(!_image_of_pc[2])
                    {
                        throw Exception("Parametric curve image letrehozas hiba");
                    }

                    if(!_image_of_pc[2]->UpdateVertexBufferObjects(_usage_flag))
                    {
                        throw Exception("Could not crete the vertex buffer object of the parametric curve!");
                    }
                }
                {
                    //hypo
                    RowMatrix<ParametricCurve3::Derivative> derivative(3);
                    derivative(0) = hypo::d0;
                    derivative(1) = hypo::d1;
                    derivative(2) = hypo::d2;

                    _pc[3] = new ParametricCurve3(derivative, hypo::u_min, hypo::u_max);
                    if(!_pc[3])
                    {
                        throw Exception("Parametric curve letrehozas hiba");
                    }

                    _image_of_pc[3] = _pc[3]->GenerateImage(_div_point_count, _usage_flag);

                    if(!_image_of_pc[3])
                    {
                        throw Exception("Parametric curve image letrehozas hiba");
                    }

                    if(!_image_of_pc[3]->UpdateVertexBufferObjects(_usage_flag))
                    {
                        throw Exception("Could not crete the vertex buffer object of the parametric curve!");
                    }
                }
                {
                    //helix
                    RowMatrix<ParametricCurve3::Derivative> derivative(3);
                    derivative(0) = helix::d0;
                    derivative(1) = helix::d1;
                    derivative(2) = helix::d2;

                    _pc[4] = new ParametricCurve3(derivative, helix::u_min, helix::u_max);
                    if(!_pc[4])
                    {
                        throw Exception("Parametric curve letrehozas hiba");
                    }

                    _image_of_pc[4] = _pc[4]->GenerateImage(_div_point_count, _usage_flag);

                    if(!_image_of_pc[4])
                    {
                        throw Exception("Parametric curve image letrehozas hiba");
                    }

                    if(!_image_of_pc[4]->UpdateVertexBufferObjects(_usage_flag))
                    {
                        throw Exception("Could not crete the vertex buffer object of the parametric curve!");
                    }
                }
                /*
                {
                    //butterfly
                    RowMatrix<ParametricCurve3::Derivative> derivative(1);
                    derivative(0) = butterfly::d0;

                    _pc = new ParametricCurve3(derivative, butterfly::u_min, butterfly::u_max);
                }
                */
            }

            // CYCLIC CURVE
            {
                _n = 3;   // 2*3 + 1 = 7 kontrollpont
                _cc = new CyclicCurve3(_n);

                if(!_cc)
                {
                    throw Exception("Could not generate cyclyc curve");
                }

                //(*_cc)[i] i. kontrollpont
                // define the controlpoints
                GLdouble step = TWO_PI / (2 * _n + 1);
                for(GLuint i = 0; i <= 2 * _n; i++)
                {
                    GLdouble u = i * step;
                    DCoordinate3 &cp = (*_cc)[i];
                    cp[0] = cos(u);
                    cp[1] = sin(u);
                    //cp[2] = u;        //... ha terbeli gorbet akarunk
                }

                //build the control polygon in the GPU
                if(!_cc->UpdateVertexBufferObjectsOfData())
                {
                    throw Exception("Could not update the vertex buffer objects of the cyclic curve");
                }

                _mod = 3;
                _img_cc = _cc->GenerateImage(_mod, _div_point_count);
                if(!_img_cc)
                {
                    throw Exception("Could not generate the cyclic curve");
                }

                if(!_img_cc->UpdateVertexBufferObjects())
                {
                    throw Exception("Could not update the VBO of the cyclic curve's iamge");
                }
            }

            // OFF FILE
            {
                if(_off_image[0].LoadFromOFF("Models/mouse.off",true)) {
                    if(_off_image[0].UpdateVertexBufferObjects(GL_DYNAMIC_DRAW)) {
                        _angle = 0.0;
                        _timer->start();
                    }
                }

                if(_off_image[1].LoadFromOFF("Models/sword.off",true)) {
                    if(_off_image[1].UpdateVertexBufferObjects(GL_DYNAMIC_DRAW)) {
                    }
                }
            }

            // PARAMETRIC SURFACE
            {
                TriangularMatrix<ParametricSurface3::PartialDerivative> derivative(2);

                {
                    // sphere
                    derivative(0,0) = sphere::d00;
                    derivative(1,0) = sphere::d10;
                    derivative(1,1) = sphere::d01;

                    _ps[0] = new ParametricSurface3(derivative, sphere::u_min, sphere::u_max, sphere::v_min, sphere::v_max);
                    _image_of_ps[0] = _ps[0]->GenerateImage(_div_point_count, _v_div_point_count, _usage_flag);
                    _image_of_ps[0]->UpdateVertexBufferObjects(GL_DYNAMIC_DRAW);
                }
                {
                    // cylindric
                    derivative(0,0) = cylindrical::d00;
                    derivative(1,0) = cylindrical::d10;
                    derivative(1,1) = cylindrical::d01;

                    _ps[1] = new ParametricSurface3(derivative, cylindrical::u_min, cylindrical::u_max, cylindrical::v_min, cylindrical::v_max);
                    _image_of_ps[1] = _ps[1]->GenerateImage(_div_point_count, _v_div_point_count, _usage_flag);
                    _image_of_ps[1]->UpdateVertexBufferObjects(GL_DYNAMIC_DRAW);
                }
                {
                    // hyperboloid
                    derivative(0,0) = hyperboloid::d00;
                    derivative(1,0) = hyperboloid::d10;
                    derivative(1,1) = hyperboloid::d01;

                    _ps[2] = new ParametricSurface3(derivative, hyperboloid::u_min, hyperboloid::u_max, hyperboloid::v_min, hyperboloid::v_max);
                    _image_of_ps[2] = _ps[2]->GenerateImage(_div_point_count, _v_div_point_count, _usage_flag);
                    _image_of_ps[2]->UpdateVertexBufferObjects(GL_DYNAMIC_DRAW);
                }
                {
                    // kleinbottle
                    derivative(0,0) = kleinbottle::d00;
                    derivative(1,0) = kleinbottle::d10;
                    derivative(1,1) = kleinbottle::d01;

                    _ps[3] = new ParametricSurface3(derivative, kleinbottle::u_min, kleinbottle::u_max, kleinbottle::v_min, kleinbottle::v_max);
                    _image_of_ps[3] = _ps[3]->GenerateImage(_div_point_count, _v_div_point_count, _usage_flag);
                    _image_of_ps[3]->UpdateVertexBufferObjects(GL_DYNAMIC_DRAW);
                }
                {
                    // duplincyclide
                    derivative(0,0) = duplincyclide::d00;
                    derivative(1,0) = duplincyclide::d10;
                    derivative(1,1) = duplincyclide::d01;

                    _ps[4] = new ParametricSurface3(derivative, duplincyclide::u_min, duplincyclide::u_max, duplincyclide::v_min, duplincyclide::v_max);
                    _image_of_ps[4] = _ps[4]->GenerateImage(_div_point_count, _v_div_point_count, _usage_flag);
                    _image_of_ps[4]->UpdateVertexBufferObjects(GL_DYNAMIC_DRAW);
                }
            }

            // BEZIER PATCH
            {
                _patch.SetData(0, 0, -2.0, -2.0, 0.0);
                _patch.SetData(0, 1, -2.0, -1.0, 0.0);
                _patch.SetData(0, 2, -2.0, 1.0, 0.0);
                _patch.SetData(0, 3, -2.0, 2.0, 0.0);

                _patch.SetData(1, 0, -1.0, -2.0, 0.0);
                _patch.SetData(1, 1, -1.0, -1.0, 2.0);
                _patch.SetData(1, 2, -1.0, 1.0, 2.0);
                _patch.SetData(1, 3, -1.0, 2.0, 0.0);

                _patch.SetData(2, 0, 1.0, -2.0, 0.0);
                _patch.SetData(2, 1, 1.0, -1.0, 2.0);
                _patch.SetData(2, 2, 1.0, 1.0, 2.0);
                _patch.SetData(2, 3, 1.0, 2.0, 0.0);

                _patch.SetData(3, 0, 2.0, -2.0, 0.0);
                _patch.SetData(3, 1, 2.0, -1.0, 0.0);
                _patch.SetData(3, 2, 2.0, 1.0, 0.0);
                _patch.SetData(3, 3, 2.0, 2.0, 0.0);

                 _patch.UpdateVertexBufferObjectsOfData();

                // generate the mesh of the surface patch
                _before_interpolation = _patch.GenerateImage(30, 30, GL_STATIC_DRAW);

                if (_before_interpolation)
                    _before_interpolation->UpdateVertexBufferObjects();
                else
                    throw Exception("_before_interpolation UpdateVertexBufferObjects error");

                // define an interpolation problem:
                // 1: create a knot vector in u-direction
                RowMatrix<GLdouble> u_knot_vector(4);
                u_knot_vector(0) = 0.0;
                u_knot_vector(1) = 1.0 / 3.0;
                u_knot_vector(2) = 2.0 / 3.0;
                u_knot_vector(3) = 1.0;

                // 2: create a knot vector in v-direction
                ColumnMatrix<GLdouble> v_knot_vector(4);
                v_knot_vector(0) = 0.0;
                v_knot_vector(1) = 1.0 / 3.0;
                v_knot_vector(2) = 2.0 / 3.0;
                v_knot_vector(3) = 1.0;

                // 3: define a matrix of data points, e.g. set them to the original control points
                Matrix<DCoordinate3> data_points_to_interpolate(4, 4);
                for (GLuint row = 0; row < 4; ++row)
                    for (GLuint column = 0; column < 4; ++column)
                        _patch.GetData(row, column, data_points_to_interpolate(row, column));

                // 4: solve the interpolation problem and generate the mesh of the interpolating patch
                if (_patch.UpdateDataForInterpolation(u_knot_vector, v_knot_vector, data_points_to_interpolate))
                {
                    _after_interpolation = _patch.GenerateImage(30, 30, GL_STATIC_DRAW);

                    if (_after_interpolation)
                        _after_interpolation->UpdateVertexBufferObjects();
                    else
                        throw Exception("_after_interpolation UpdateVertexBufferObjects error");
                }
                else
                    throw Exception("_patch.UpdateDataForInterpolation error");
            }

            // SHADER
            {
               _mesh.LoadFromOFF("Models/mouse.off", true);
               _mesh.UpdateVertexBufferObjects();

               _two_sided_lighting.InstallShaders("Shaders/two_sided_lighting.vert", "Shaders/two_sided_lighting.frag", GL_TRUE);

               _toon.InstallShaders("Shaders/toon.vert", "Shaders/toon.frag", GL_TRUE);
               _toon.Enable();
               _toon.SetUniformVariable4f("default_outline_color", 1.0, 0.0, 0.0, 1.0);
               _toon.Disable();


               _refelction_lines.InstallShaders("Shaders/reflection_lines.vert", "Shaders/reflection_lines.frag", GL_TRUE);
               _refelction_lines.Enable();
               _refelction_lines.SetUniformVariable1f("scale_factor", 4.0);
               _refelction_lines.SetUniformVariable1f("smoothing", 2.0);
               _refelction_lines.SetUniformVariable1f("shading", 1.0);
               _refelction_lines.Disable();
            }

            // HERMITE PATCH TESZT ILLESZTEST
            {
                _hermite_patch.SetCorner(0, 0, -1.0, -1.0, 0.0);
                _hermite_patch.SetCorner(0, 1, -1.0, +1.0, 0.0);
                _hermite_patch.SetCorner(1, 0, +1.0, -1.0, 0.0);
                _hermite_patch.SetCorner(1, 1, +1.0, +1.0, 0.0);

                _hermite_patch.SetUTangent(0, 0, -1.0, -2.0, -2.0);
                _hermite_patch.SetUTangent(0, 1, -1.0, +2.0, -2.0);
                _hermite_patch.SetUTangent(1, 0, +1.0, -2.0, -2.0);
                _hermite_patch.SetUTangent(1, 1, +1.0, +2.0, -2.0);

                _hermite_patch.SetVTangent(0, 0, -1.0, -1.0, -2.0);
                _hermite_patch.SetVTangent(0, 1, -1.0, +1.0, -2.0);
                _hermite_patch.SetVTangent(1, 0, +1.0, -1.0, +2.0);
                _hermite_patch.SetVTangent(1, 1, +1.0, +1.0, +2.0);

                _hermite_patch.SetTwist(0, 0, -1.0, -1.0, +2.0);
                _hermite_patch.SetTwist(0, 1, -1.0, +1.0, +2.0);
                _hermite_patch.SetTwist(1, 0, +1.0, -1.0, +2.0);
                _hermite_patch.SetTwist(1, 1, +1.0, +1.0, +2.0);

                _hermite_patch.UpdateVertexBufferObjectsOfData();

                _img_hermite_patch = 0;
                _img_hermite_patch = _hermite_patch.GenerateImage(30, 30, GL_STATIC_DRAW);

                if (_img_hermite_patch)
                    _img_hermite_patch->UpdateVertexBufferObjects();
                else
                    throw Exception("_img_hermite_patch UpdateVertexBufferObjects error");

                DCoordinate3 _test_join;
                _test_join = _hermite_patch.GetCorner(0, 1);
                _hermite_patch1.SetCorner(0, 0, _test_join);
                _hermite_patch1.SetCorner(0, 1, -2.0, +2.0, 0.0);
                _test_join = _hermite_patch.GetCorner(1, 1);
                _hermite_patch1.SetCorner(1, 0, _test_join);
                _hermite_patch1.SetCorner(1, 1, +2.0, +2.0, 0.0);

                _test_join = _hermite_patch.GetUTangent(0, 1);
                _hermite_patch1.SetUTangent(0, 0, _test_join);
                _hermite_patch1.SetUTangent(0, 1, -2.0, +3.0, -2.0);
                _test_join = _hermite_patch.GetUTangent(1, 1);
                _hermite_patch1.SetUTangent(1, 0, _test_join);
                _hermite_patch1.SetUTangent(1, 1, +2.0, +3.0, -2.0);

                _test_join = _hermite_patch.GetVTangent(0, 1);
                _hermite_patch1.SetVTangent(0, 0, _test_join);
                _hermite_patch1.SetVTangent(0, 1, -2.0, +2.0, -2.0);
                _test_join = _hermite_patch.GetVTangent(1, 1);
                _hermite_patch1.SetVTangent(1, 0, _test_join);
                _hermite_patch1.SetVTangent(1, 1, +2.0, +2.0, +2.0);

                _test_join = _hermite_patch.GetTwist(0, 1);
                _hermite_patch1.SetTwist(0, 0, _test_join);
                _hermite_patch1.SetTwist(0, 1, -2.0, +2.0, +2.0);
                _test_join = _hermite_patch.GetTwist(1, 1);
                _hermite_patch1.SetTwist(1, 0, _test_join);
                _hermite_patch1.SetTwist(1, 1, +2.0, +2.0, +2.0);


                _hermite_patch1.UpdateVertexBufferObjectsOfData();

                _img_hermite_patch1 = 0;
                _img_hermite_patch1 = _hermite_patch1.GenerateImage(30, 30, GL_STATIC_DRAW);

                if (_img_hermite_patch1)
                    _img_hermite_patch1->UpdateVertexBufferObjects();
                else
                    throw Exception("_img_hermite_patch UpdateVertexBufferObjects error");
            }

            // PROJEKT HERMITE COMPOSITE SURFACE
            {
                _file_index = 0;
                _patch_index = 0;
                _shader_index = 0;
                _material_index = 0;
                _patch1_index = 0;
                _corner_index = 0;
                _vector_index = 0;
                _xValue = 0;
                _yValue = 0;
                _zValue = 0;

                //_hermite_surface->SetSelectedMaterial(_patch1_index,&MatFBRuby);
                _patch2_index = 1;
                //_hermite_surface->SetSelectedMaterial(_patch2_index,&MatFBRuby);
                _dir1 = 0;
                _dir2 = 0;

                _hermite_surface = new HermiteCompositeSurface3();
                //_hermite_surface->SetMaterial(_patch1_index,&MatFBRuby);
                //_hermite_surface->SetSelectedMaterial(_patch2_index,&MatFBRuby);

                vector<DCoordinate3> corners;
                corners.resize(4);
                DCoordinate3 corners0(-1.0, +1.0, 0.0);
                DCoordinate3 corners1(-2.0, +2.0, 0.0);
                DCoordinate3 corners2(+1.0, +1.0, 0.0);
                DCoordinate3 corners3(+2.0, +2.0, 0.0);
                corners[0] = corners0;
                corners[1] = corners1;
                corners[2] = corners2;
                corners[3] = corners3;

                vector<DCoordinate3> uTangents;
                uTangents.resize(4);
                DCoordinate3 uTangents0(-1.0, +2.0, -2.0);
                DCoordinate3 uTangents1(-2.0, +3.0, -2.0);
                DCoordinate3 uTangents2(+1.0, +2.0, -2.0);
                DCoordinate3 uTangents3(+2.0, +3.0, -2.0);
                uTangents[0] = uTangents0;
                uTangents[1] = uTangents1;
                uTangents[2] = uTangents2;
                uTangents[3] = uTangents3;

                vector<DCoordinate3> vTangents;
                vTangents.resize(4);
                DCoordinate3 vTangents0(-1.0, +1.0, -2.0);
                DCoordinate3 vTangents1(-2.0, +2.0, -2.0);
                DCoordinate3 vTangents2(+1.0, +1.0, +2.0);
                DCoordinate3 vTangents3(+2.0, +2.0, +2.0);
                vTangents[0] = vTangents0;
                vTangents[1] = vTangents1;
                vTangents[2] = vTangents2;
                vTangents[3] = vTangents3;

                vector<DCoordinate3> twists;
                twists.resize(4);
                DCoordinate3 twists0(-1.0, +1.0, +2.0);
                DCoordinate3 twists1(-2.0, +2.0, +2.0);
                DCoordinate3 twists2(+1.0, +1.0, +2.0);
                DCoordinate3 twists3(+2.0, +2.0, +2.0);
                twists[0] = twists0;
                twists[1] = twists1;
                twists[2] = twists2;
                twists[3] = twists3;

                _hermite_surface->InsertIsolatedPatch(corners, uTangents, vTangents, twists);
                _hermite_surface->SetAttributes(0, &_two_sided_lighting, &MatFBGold);
                _hermite_surface->SetSelectedMaterial(0,&MatFBRuby);

                DCoordinate3 corners01(-1.0, -1.0, 0.0);
                DCoordinate3 corners11(-1.0, +0.0, 0.0);
                DCoordinate3 corners21(+1.0, -1.0, 0.0);
                DCoordinate3 corners31(+1.0, +0.0, 0.0);
                corners[0] = corners01;
                corners[1] = corners11;
                corners[2] = corners21;
                corners[3] = corners31;

                DCoordinate3 uTangents01(-1.0, -2.0, -2.0);
                DCoordinate3 uTangents11(-1.0, +2.0, -2.0);
                DCoordinate3 uTangents21(+1.0, -2.0, -2.0);
                DCoordinate3 uTangents31(+1.0, +2.0, -2.0);
                uTangents[0] = uTangents01;
                uTangents[1] = uTangents11;
                uTangents[2] = uTangents21;
                uTangents[3] = uTangents31;

                DCoordinate3 vTangents01(-1.0, -1.0, -2.0);
                DCoordinate3 vTangents11(-1.0, +1.0, -2.0);
                DCoordinate3 vTangents21(+1.0, -1.0, +2.0);
                DCoordinate3 vTangents31(+1.0, +1.0, +2.0);
                vTangents[0] = vTangents01;
                vTangents[1] = vTangents11;
                vTangents[2] = vTangents21;
                vTangents[3] = vTangents31;

                DCoordinate3 twists01(-1.0, -1.0, +2.0);
                DCoordinate3 twists11(-1.0, +1.0, +2.0);
                DCoordinate3 twists21(+1.0, -1.0, +2.0);
                DCoordinate3 twists31(+1.0, +1.0, +2.0);
                twists[0] = twists01;
                twists[1] = twists11;
                twists[2] = twists21;
                twists[3] = twists31;

                //read_patch(0);

                _hermite_surface->InsertIsolatedPatch(corners, uTangents, vTangents, twists);
                _hermite_surface->SetAttributes(1, &_two_sided_lighting, &MatFBGold);
                _hermite_surface->SetSelectedMaterial(1,&MatFBPearl);

                //_hermite_surface->MergeTwoPatches(0, 1, 4, 0);
                //_hermite_surface->JoinTwoPatches(0, 1, 4, 0);
                //_hermite_surface->ExtendPatch(1, 4);

                //init vectors value (X,Y,Z)



            }


            // HERMITE CURVE TEST
            {
                _arc_test = new HermiteArc();
                DCoordinate3 _p1(-1.0, -1.0, +2.0);
                DCoordinate3 _p2(-1.0, +1.0, +2.0);
                DCoordinate3 _t1(+1.0, -1.0, +2.0);
                DCoordinate3 _t2(+1.0, +1.0, +2.0);
                _arc_test->SetData(0,_p1);
                _arc_test->SetData(1,_p2);
                _arc_test->SetData(2,_t1);
                _arc_test->SetData(3,_t2);

                _arc_test->UpdateVertexBufferObjectsOfData();

               _arc_test_img = 0;
                _arc_test_img = _arc_test->GenerateImage(0,30,GL_STATIC_DRAW);

                if (_arc_test_img)
                    _arc_test_img->UpdateVertexBufferObjects();
                else
                    throw Exception("_arc_test_img UpdateVertexBufferObjects error");

            }


            //HERMITE COMPOSITE CURVE TEST
            {
                HermiteArc   *arc1 = new HermiteArc();
                DCoordinate3 p1(+1.0, +1.0, +2.0);
                DCoordinate3 p2(+1.0, +3.0, +2.0);
                DCoordinate3 t1(-1.0, +1.0, +2.0);
                DCoordinate3 t2(+1.0, +1.0, +2.0);
                arc1->SetData(0,p1);
                arc1->SetData(1,p2);
                arc1->SetData(2,t1);
                arc1->SetData(3,t2);

                HermiteArc   *arc2 = new HermiteArc();
                DCoordinate3 p12(+3.0, +0.0, +2.0);
                DCoordinate3 p22(+3.0, +2.0, +2.0);
                DCoordinate3 t12(-1.0, +1.0, +2.0);
                DCoordinate3 t22(+1.0, +1.0, +2.0);
                arc2->SetData(0,p12);
                arc2->SetData(1,p22);
                arc2->SetData(2,t12);
                arc2->SetData(3,t22);

                _hermit_cmp_curve = new HermiteCompositeCurve();
                _hermit_cmp_curve->InsertNewArc(arc1);
                _hermit_cmp_curve->InsertNewArc(arc2);
<<<<<<< HEAD
                _hermit_cmp_curve->PlusFromRight(1);
                _hermit_cmp_curve->PlusFromLeft(0);
=======
                //_hermit_cmp_curve->PlusFromRight(1);
                //_hermit_cmp_curve->PlusFromLeft(0);


                //MERGE PROBA
                //_hermit_cmp_curve->Merge(0,1,0); //jobbat ballal
                //_hermit_cmp_curve->Merge(0,1,1);//jobb jobbal
                //_hermit_cmp_curve->Merge(0,1,2);//bal ballal
                _hermit_cmp_curve->Merge(0,1,3);//bal jobbal
                _hermit_cmp_curve->SetColor(0,0,1,0);
                //_hermit_cmp_curve->PlusFromLeft(0);
                _hermit_cmp_curve->PlusFromRight(0);

                //_hermit_cmp_curve->PlusFromRight(1);

                //_hermit_cmp_curve->JoinFromRight(0,1);
                //_hermit_cmp_curve->SetTransX(1, 1, 0);
                //_hermit_cmp_curve->PlusFromRight(1);
                //_hermit_cmp_curve->PlusFromLeft(0);
                //_hermit_cmp_curve->SetArcTransX(1, 0);
                //_hermit_cmp_curve->SetArcTransY(1, 0);
                //_hermit_cmp_curve->SetArcTransZ(1, 0);
>>>>>>> 69de0a2c1a1a192f9f862d725063899613f2edb4
                //_hermit_cmp_curve->MergeFromRight(0,1);
                //_hermit_cmp_curve->PlusFromRight(0);
                //_hermit_cmp_curve->PlusFromRight(1);
                //_hermit_cmp_curve->PlusFromRight(2);

//                _hermit_cmp_curve->JoinCurves(0,1,0);
//                _hermit_cmp_curve->JoinCurves(0,1,1);
                _hermit_cmp_curve->JoinCurves(0,1,2);
                _hermit_cmp_curve->JoinCurves(0,1,3);

//                _hermit_cmp_curve->JoinFromRight(0,1);
            }

        }
        catch (Exception &e)
        {
            cout << e << endl;
        }
    }

    //-----------------------
    // the rendering function
    //-----------------------
    void GLWidget::paintGL()
    {
        // clears the color and depth buffers
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // stores/duplicates the original model view matrix
        glPushMatrix();

            // applying transformations
            glRotatef(_angle_x, 1.0, 0.0, 0.0);
            glRotatef(_angle_y, 0.0, 1.0, 0.0);
            glRotatef(_angle_z, 0.0, 0.0, 1.0);
            glTranslated(_trans_x, _trans_y, _trans_z);
            glScaled(_zoom, _zoom, _zoom);

            // render your geometry (this is oldest OpenGL rendering technique, later we will use some advanced methods)

            // rended parametric curve
            if(_img_select == 0)
            if(_image_of_pc[_img_index])
            {
                glColor3f(1.0, 0.0, 0.0);
                glPointSize(5.0);
                _image_of_pc[_img_index]->RenderDerivatives(0, GL_LINE_STRIP);

                glPointSize(1.0);

                glColor3f(0.0 , 1.0, 0.0);
                _image_of_pc[_img_index]->RenderDerivatives(1, GL_LINES);
                _image_of_pc[_img_index]->RenderDerivatives(1, GL_POINTS);

                glColor3f(0.0 , 0.0, 1.0);
                _image_of_pc[_img_index]->RenderDerivatives(2, GL_LINES);
                _image_of_pc[_img_index]->RenderDerivatives(2, GL_POINTS);

               glPointSize(1.0);
            }

            // render cyclyc curve
            if(_img_select == 1)
            {
                if(_cc)
                {
                    glColor3f(1.0, 0.0, 0.0);
                    _cc->RenderData(GL_LINE_LOOP);
                }
                //
                if(_img_cc)
                {
                    glColor3f(1.0, 0.0, 0.0);
                    _img_cc->RenderDerivatives(0, GL_LINE_LOOP);
                    glColor3f(0.0, 0.5, 0.5);
                    _img_cc->RenderDerivatives(1, GL_LINES);
                    glColor3f(0.0, 1.0, 0.0);
                    _img_cc->RenderDerivatives(2, GL_LINES);
                    glColor3f(0.0, 0.0, 1.0);
                    _img_cc->RenderDerivatives(3, GL_LINES);
                }
            }

            // render off file
            if(_img_select == 2)
            {
                glEnable(GL_LIGHTING);
                _dl->Enable();
                MatFBPearl.Apply();
                _off_image[_img_index].Render();
                glDisable(GL_LIGHTING);
            }

            // render parametric surface
            if(_img_select == 3)
            if (_image_of_ps[_img_index])
            {
                glEnable(GL_LIGHTING);
                _dl->Enable();
                MatFBTurquoise.Apply();
                _image_of_ps[_img_index]->Render();
                glDisable(GL_LIGHTING);
            }

            // render bezier patch
            if(_img_select == 4)
            {
                glEnable(GL_LIGHTING);
                glEnable(GL_NORMALIZE);
                if (_before_interpolation)
                {
                    _dl->Enable();
                    MatFBRuby.Apply();
                    _patch.RenderData();
                    _patch.RenderData(GL_POINTS);

                    MatFBGold.Apply();
                    _before_interpolation->Render();
                    _dl->Disable();
                }
                if (_after_interpolation)
                {
                    _dl->Enable();
                    glEnable(GL_BLEND);
                    glDepthMask(GL_FALSE);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
                        MatFBTurquoise.Apply();
                        _after_interpolation->Render();
                    glDepthMask(GL_TRUE);
                    glDisable(GL_BLEND);
                    _dl->Disable();
                }
                glDisable(GL_LIGHTING);
                glDisable(GL_NORMALIZE);
            }

            // render shader
            if(_img_select == 5)
            {
                glEnable(GL_LIGHTING);
                _dl->Enable();

                if(_img_index == 0)
                    _two_sided_lighting.Enable();
                if(_img_index == 1)
                    _refelction_lines.Enable();
                if(_img_index == 2)
                    _toon.Enable();

                MatFBBrass.Apply();
                _mesh.Render();
                _dl->Disable();

                if(_img_index == 0)
                    _two_sided_lighting.Disable();
                if(_img_index == 1)
                    _refelction_lines.Disable();
                if(_img_index == 2)
                    _toon.Disable();

                glDisable(GL_LIGHTING);
            }

            // render triangle
            if(_img_select == 6)
            {
                (GL_LIGHTING);
                glDisable(GL_NORMALIZE);

                glColor3f(1.0f, 1.0f, 1.0f);

                glBegin(GL_LINES);
                    glVertex3f(0.0f, 0.0f, 0.0f);
                    glVertex3f(1.1f, 0.0f, 0.0f);

                    glVertex3f(0.0f, 0.0f, 0.0f);
                    glVertex3f(0.0f, 1.1f, 0.0f);

                    glVertex3f(0.0f, 0.0f, 0.0f);
                    glVertex3f(0.0f, 0.0f, 1.1f);
                glEnd();

                glBegin(GL_TRIANGLES);
                    // attributes
                    glColor3f(1.0f, 0.0f, 0.0f);
                    // associated with position
                    glVertex3f(1.0f, 0.0f, 0.0f);

                    // attributes
                    glColor3f(0.0, 1.0, 0.0);
                    // associated with position
                    glVertex3f(0.0, 1.0, 0.0);

                    // attributes
                    glColor3f(0.0f, 0.0f, 1.0f);
                    // associated with position
                    glVertex3f(0.0f, 0.0f, 1.0f);
                glEnd();
            }

            if(_img_select == 7)
            {
                glEnable(GL_LIGHTING);
                glEnable(GL_NORMALIZE);
                if (_img_hermite_patch)
                {
                    //_dl->Enable();
                    MatFBRuby.Apply();
                    glPointSize(5.0);
                    _hermite_patch.RenderData(GL_POINTS);

                    MatFBGold.Apply();
                    _two_sided_lighting.Enable();
                    _img_hermite_patch->Render();
                    _two_sided_lighting.Disable();
                    //_dl->Disable();
                }
                glDisable(GL_LIGHTING);
                glDisable(GL_NORMALIZE);

                glEnable(GL_LIGHTING);
                glEnable(GL_NORMALIZE);
                if (_img_hermite_patch)
                {
                    //_dl->Enable();
                    MatFBEmerald.Apply();
                    glPointSize(5.0);
                    _hermite_patch1.RenderData(GL_POINTS);

                    MatFBSilver.Apply();
                    _two_sided_lighting.Enable();
                    _img_hermite_patch1->Render();
                    _two_sided_lighting.Disable();
                    //_dl->Disable();
                }
                glDisable(GL_LIGHTING);
                glDisable(GL_NORMALIZE);
            }

            if(_img_select == 8)
            {
                // iranytu
                glPushMatrix();
                //glRotatef(0, 0.0, 0.0, 1.0);
                glTranslated(-7, 0, 0);
                glScaled(2, 2, 2);
                glEnable(GL_LIGHTING);
                _dl->Enable();
                MatFBRuby.Apply();
                _off_image[1].Render();
                glDisable(GL_LIGHTING);
                glPopMatrix();
                // iranytu_vege

                glEnable(GL_LIGHTING);
                glEnable(GL_NORMALIZE);
                //_two_sided_lighting.Enable();
                //_hermite_surface->GenerateImagesOfAllPatches();
                _hermite_surface->RenderAll();
                //_two_sided_lighting.Disable();
                glDisable(GL_LIGHTING);
                glDisable(GL_NORMALIZE);
            }


            if(_img_select == 9)
            {
                // iranytu
                glPushMatrix();
                //glRotatef(0, 0.0, 0.0, 1.0);
                glTranslated(-7, 0, 0);
                glScaled(2, 2, 2);
                glEnable(GL_LIGHTING);
                _dl->Enable();
                MatFBRuby.Apply();
                _off_image[1].Render();
                glDisable(GL_LIGHTING);
                glPopMatrix();
                // iranytu_vege

                glColor3f(0.0,1.0,0.0);
                _arc_test_img->RenderDerivatives(0,GL_LINE_STRIP);

            }

            if(_img_select == 10)
            {
                // iranytu
                glPushMatrix();
                //glRotatef(0, 0.0, 0.0, 1.0);
                glTranslated(-7, 0, 0);
                glScaled(2, 2, 2);
                glEnable(GL_LIGHTING);
                _dl->Enable();
                MatFBRuby.Apply();
                _off_image[1].Render();
                glDisable(GL_LIGHTING);
                glPopMatrix();
                // iranytu_vege

                _hermit_cmp_curve->RenderAll();
            }

        // pops the current matrix stack, replacing the current matrix with the one below it on the stack,
        // i.e., the original model view matrix is restored
        glPopMatrix();
    }

    //----------------------------------------------------------------------------
    // when the main window is resized one needs to redefine the projection matrix
    //----------------------------------------------------------------------------
    void GLWidget::resizeGL(int w, int h)
    {
        // setting the new size of the rendering context
        glViewport(0, 0, w, h);

        // redefining the projection matrix
        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        _aspect = (float)w / (float)h;

        gluPerspective(_fovy, _aspect, _z_near, _z_far);

        // switching back to the model view matrix
        glMatrixMode(GL_MODELVIEW);

        updateGL();
    }

    //-----------------------------------
    // implementation of the public slots
    //-----------------------------------

    void GLWidget::set_angle_x(int value)
    {
        if (_angle_x != value)
        {
            _angle_x = value;
            updateGL();
        }
    }

    void GLWidget::set_angle_y(int value)
    {
        if (_angle_y != value)
        {
            _angle_y = value;
            updateGL();
        }
    }

    void GLWidget::set_angle_z(int value)
    {
        if (_angle_z != value)
        {
            _angle_z = value;
            updateGL();
        }
    }

    void GLWidget::set_zoom_factor(double value)
    {
        if (_zoom != value)
        {
            _zoom = value;
            updateGL();
        }
    }

    void GLWidget::set_trans_x(double value)
    {
        if (_trans_x != value)
        {
            _trans_x = value;
            updateGL();
        }
    }

    void GLWidget::set_trans_y(double value)
    {
        if (_trans_y != value)
        {
            _trans_y = value;
            updateGL();
        }
    }

    void GLWidget::set_trans_z(double value)
    {
        if (_trans_z != value)
        {
            _trans_z = value;
            updateGL();
        }
    }

    void GLWidget::_animate()
    {
        GLfloat *vertex = _off_image[0].MapVertexBuffer(GL_READ_WRITE);
        GLfloat *normal = _off_image[0].MapNormalBuffer(GL_READ_ONLY);

        _angle += DEG_TO_RADIAN;
        if(_angle>=TWO_PI)
            _angle -= TWO_PI;

        GLfloat scale = sin(_angle) / 3000.0;
        for(GLuint i = 0; i<_off_image[0].VertexCount(); ++i)
        {
            for(GLuint coordinate = 0; coordinate<3; ++coordinate, ++vertex, ++normal)
                *vertex += scale * (*normal);
        }

        _off_image[0].UnmapVertexBuffer();
        _off_image[0].UnmapNormalBuffer();

        updateGL();
    }

    void GLWidget::set_img(int value)
    {
        if (_img_select != value)
        {
            _img_select = value;
            updateGL();
        }
    }

    void GLWidget::set_index(int value)
    {
        if (_img_index != value)
        {
            _img_index = value;
            updateGL();
        }
    }

    void GLWidget::set_file_index(int value)
    {
        if (_file_index != value)
        {
            _file_index = value;
        }
    }

    void GLWidget::call_read_patch()
    {
        read_patch(_file_index);
    }

    GLboolean GLWidget::read_patch(GLuint i)
    {
        string filename;
        if(i < 10)
            filename = "Patches/patch0" + to_string(i) + ".txt";
        else
            filename = "Patches/patch" + to_string(i) + ".txt";

        ifstream file(filename);
        if(!file.good())
        {
            cout << "Patch file " << filename<< " does not exist" << endl;
            return GL_FALSE;
        }

        float x, y, z;

        vector<DCoordinate3> corners;
        corners.resize(4);
        file >> x >> y >> z;
        DCoordinate3 corners0(x, y, z);
        file >> x >> y >> z;
        DCoordinate3 corners1(x, y, z);
        file >> x >> y >> z;
        DCoordinate3 corners2(x, y, z);
        file >> x >> y >> z;
        DCoordinate3 corners3(x, y, z);
        corners[0] = corners0;
        corners[1] = corners1;
        corners[2] = corners2;
        corners[3] = corners3;

        vector<DCoordinate3> uTangents;
        uTangents.resize(4);
        file >> x >> y >> z;
        DCoordinate3 uTangents0(x, y, z);
        file >> x >> y >> z;
        DCoordinate3 uTangents1(x, y, z);
        file >> x >> y >> z;
        DCoordinate3 uTangents2(x, y, z);
        file >> x >> y >> z;
        DCoordinate3 uTangents3(x, y, z);
        uTangents[0] = uTangents0;
        uTangents[1] = uTangents1;
        uTangents[2] = uTangents2;
        uTangents[3] = uTangents3;

        vector<DCoordinate3> vTangents;
        vTangents.resize(4);
        file >> x >> y >> z;
        DCoordinate3 vTangents0(x, y, z);
        file >> x >> y >> z;
        DCoordinate3 vTangents1(x, y, z);
        file >> x >> y >> z;
        DCoordinate3 vTangents2(x, y, z);
        file >> x >> y >> z;
        DCoordinate3 vTangents3(x, y, z);
        vTangents[0] = vTangents0;
        vTangents[1] = vTangents1;
        vTangents[2] = vTangents2;
        vTangents[3] = vTangents3;

        vector<DCoordinate3> twists;
        twists.resize(4);
        file >> x >> y >> z;
        DCoordinate3 twists0(x, y, z);
        file >> x >> y >> z;
        DCoordinate3 twists1(x, y, z);
        file >> x >> y >> z;
        DCoordinate3 twists2(x, y, z);
        file >> x >> y >> z;
        DCoordinate3 twists3(x, y, z);
        twists[0] = twists0;
        twists[1] = twists1;
        twists[2] = twists2;
        twists[3] = twists3;

        _hermite_surface->InsertIsolatedPatch(corners, uTangents, vTangents, twists);

        file.close();

        return GL_TRUE;
    }

    void GLWidget::call_write_patch(){
        if(_patch_index < _hermite_surface->GetNumberOfPatches()){
            _hermite_surface->write_patch(_patch_index);
        }
        else{
            cout << "Patch index " << _patch_index << " does not exist!" << endl;
        }
    }

    void GLWidget::set_patch_index(int value)
    {
        if(_patch_index != value)
        {
            _patch_index = value;
        }
    }

    GLboolean GLWidget::set_shader_index(int value)
    {

        GLuint n = _hermite_surface->GetNumberOfPatches();
        if(_patch_index > n - 1)
        {
            cout << "Not existing patch index" << endl;
            return GL_FALSE;
        }

        if(_shader_index != value)
        {
            _shader_index = value;
        }

        switch(_shader_index)
        {
        case 0:
            _hermite_surface->SetShader(_patch_index, &_two_sided_lighting);
            break;
        case 1:
            _hermite_surface->SetShader(_patch_index, &_toon);
            break;
        case 2:
            _hermite_surface->SetShader(_patch_index, &_refelction_lines);
            break;
        }

        return GL_TRUE;
    }

    GLboolean GLWidget::set_material_index(int value)
    {
        GLuint n = _hermite_surface->GetNumberOfPatches();
        if(_patch_index > n - 1)
        {
            cout << "Not existing patch index" << endl;
            return GL_FALSE;
        }

        if(_material_index != value)
        {
            _material_index = value;
        }

        switch(_material_index)
        {
        case 0:
            _hermite_surface->SetMaterial(_patch_index, &MatFBBrass);
            break;
        case 1:
            _hermite_surface->SetMaterial(_patch_index, &MatFBGold);
            break;
        case 2:
            _hermite_surface->SetMaterial(_patch_index, &MatFBSilver);
            break;
        case 3:
            _hermite_surface->SetMaterial(_patch_index, &MatFBEmerald);
            break;
        /*case 4:
            _hermite_surface->SetMaterial(_patch_index, &MatFBPearl);
            break;
        case 5:
            _hermite_surface->SetMaterial(_patch_index, &MatFBRuby);
            break;*/
        case 4:
            _hermite_surface->SetMaterial(_patch_index, &MatFBTurquoise);
            break;
        case 5:
            _hermite_surface->SetMaterial(_patch_index, &MatFBBrass);
            break;
        }

        return GL_TRUE;
    }

    void GLWidget::set_direction1(int value) {
        if(_dir1 != value)
        {
            _dir1 = value;
        }
    }

    void GLWidget::set_direction2(int value) {
        if(_dir2 != value)
        {
            _dir2 = value;
        }
    }

    void GLWidget::set_patch1_index(int value)
    {
        if(value >= (int)_hermite_surface->GetNumberOfPatches())
        {
            _hermite_surface->SetSelectedMaterial(_patch1_index,nullptr);
            _patch1_index = value;
        }
        else if(_patch1_index != value)
        {
            _hermite_surface->SetSelectedMaterial(_patch1_index,nullptr);

            if(_patch1_index == _patch2_index)
            {
                _hermite_surface->SetSelectedMaterial(_patch2_index,&MatFBPearl);
            }
            _patch1_index = value;
            _hermite_surface->SetSelectedMaterial(_patch1_index,&MatFBRuby);
        }
    }

    void GLWidget::set_patch2_index(int value)
    {
        if(value >= (int)_hermite_surface->GetNumberOfPatches())
        {
            _hermite_surface->SetSelectedMaterial(_patch2_index,nullptr);
            _patch2_index = value;
        }
        else if(_patch2_index != value)
        {
            _hermite_surface->SetSelectedMaterial(_patch2_index,nullptr);

            if(_patch1_index == _patch2_index)
            {
                _hermite_surface->SetSelectedMaterial(_patch1_index,&MatFBRuby);
            }
            _patch2_index = value;
            _hermite_surface->SetSelectedMaterial(_patch2_index,&MatFBPearl);
        }
    }

    GLboolean GLWidget::call_extend_patch()
    {
        GLuint n = _hermite_surface->GetNumberOfPatches();
        if(_patch1_index > n - 1)
        {
            cout << "Patch 1 index not existing" << endl;
            return GL_FALSE;
        }

        _hermite_surface->ExtendPatch(_patch1_index, _dir1);

        return GL_TRUE;
    }

    GLboolean GLWidget::call_extend_new_patch(){
        GLuint n = _hermite_surface->GetNumberOfPatches();
        if(_patch1_index > n - 1)
        {
            cout << "Patch 1 index not existing" << endl;
            return GL_FALSE;
        }

        if(_dir1 % 2 == 1)
        {
            cout << "Extend new can be only done in sides" << endl;
            return GL_FALSE;
        }

        return _hermite_surface->ExtendNewPatch(_patch1_index, _dir1);
    }

    GLboolean GLWidget::call_join_patch()
    {
        GLuint n = _hermite_surface->GetNumberOfPatches();
        if(_patch1_index > n - 1)
        {
            cout << "Patch 1 index not existing" << endl;
            return GL_FALSE;
        }
        if(_patch2_index > n - 1)
        {
            cout << "Patch 2 index not existing" << endl;
            return GL_FALSE;
        }
        if(_patch1_index == _patch2_index)
        {
            cout << "Patch 1 index can't be equal with Patch 2 index" << endl;
            return GL_FALSE;
        }
        if(_dir1 % 2 == 1 || _dir2 % 2 == 1)
        {
            cout << "Join can be only done in sides" << endl;
            return GL_FALSE;
        }

        _hermite_surface->JoinTwoPatches(_patch1_index, _patch2_index, _dir1, _dir2);

        return GL_TRUE;
    }

    GLboolean GLWidget::call_merge_patch()
    {
        GLuint n = _hermite_surface->GetNumberOfPatches();
        if(_patch1_index > n - 1)
        {
            cout << "Patch 1 index not existing" << endl;
            return GL_FALSE;
        }
        if(_patch2_index > n - 1)
        {
            cout << "Patch 2 index not existing" << endl;
            return GL_FALSE;
        }
        if(_patch1_index == _patch2_index)
        {
            cout << "Patch 1 index can't be equal with Patch 2 index" << endl;
            return GL_FALSE;
        }

        _hermite_surface->MergeTwoPatches(_patch1_index, _patch2_index, _dir1, _dir2);

        return GL_TRUE;
    }

    void GLWidget::plus_X()
    {
        _hermite_surface->SetTransX(_patch_index, 0.1);
        updateGL();
    }

    void GLWidget::minus_X()
    {
        _hermite_surface->SetTransX(_patch_index, -0.1);
        updateGL();
    }

    void GLWidget::plus_Y()
    {
        _hermite_surface->SetTransY(_patch_index, 0.1);
        updateGL();
    }

    void GLWidget::minus_Y()
    {
        _hermite_surface->SetTransY(_patch_index, -0.1);
        updateGL();
    }

    void GLWidget::plus_Z()
    {
        _hermite_surface->SetTransZ(_patch_index, 0.1);
        updateGL();
    }

    void GLWidget::minus_Z()
    {
        _hermite_surface->SetTransZ(_patch_index, -0.1);
        updateGL();
    }

    GLboolean GLWidget::set_corners_index(int value)
    {

        _corner_index = value;

        return GL_TRUE;
    }

    GLboolean GLWidget::set_vectors_index(int value)
    {

        _vector_index = value;

        return GL_TRUE;
    }

    GLboolean GLWidget::_xValue_changed(double value)
    {
        _xValue = value;
        return GL_TRUE;
    }

    GLboolean GLWidget::_yValue_changed(double value)
    {
        _yValue = value;
        return GL_TRUE;
    }

    GLboolean GLWidget::_zValue_changed(double value)
    {
         _zValue = value;
        return GL_TRUE;
    }


    GLboolean GLWidget::_change_bt_clicked()
    {
        _hermite_surface->setVectorXYZ(_vector_index,_corner_index,_xValue,_yValue,_zValue,_patch_index);

        return GL_TRUE;
    }


}
