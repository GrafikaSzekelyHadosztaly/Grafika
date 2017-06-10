#pragma once

#include <GL/glew.h>
#include <QGLWidget>
#include <QGLFormat>
#include "Parametric/ParametricCurves3.h"
#include "Core/Exceptions.h"
#include <memory>
#include "Cyclic/CyclicCurves3.h"
#include "Core/GenericCurves3.h"
#include "Core/TriangulatedMeshes3.h"
#include <QTimer>
#include "Parametric/ParametricSurfaces3.h"
#include "Core/Lights.h"
#include "Bezier/BicubicBezierPatches.h"
#include "Core/ShaderPrograms.h"

#include "Hermit/HermiteArcs3.h"
#include "Hermit/HermiteCompositeCurves3.h"
#include "Hermit/HermitePatches3.h"
#include "Hermit/HermiteCompositeSurfaces3.h"

namespace cagd
{
    class GLWidget: public QGLWidget
    {
        Q_OBJECT

    private:


        // variables defining the projection matrix
        float       _aspect;            // aspect ratio of the rendering window
        float       _fovy;              // field of view in direction y
        float       _z_near, _z_far;    // distance of near and far clipping planes

        // variables defining the model-view matrix
        float       _eye[3], _center[3], _up[3];

        // variables needed by transformations
        int         _angle_x, _angle_y, _angle_z;
        double      _zoom;
        double      _trans_x, _trans_y, _trans_z;

        // your other declarations

        GLuint _div_point_count;
        GLuint _v_div_point_count;
        GLenum _usage_flag;

        //curves
        ParametricCurve3*   _pc[5];
        GenericCurve3*      _image_of_pc[5];

        //cyclic curve
        CyclicCurve3*   _cc;
        GenericCurve3*  _img_cc;
        GLuint          _n, _mod;

        //OFF file
        TriangulatedMesh3   _off_image[2];

        QTimer*         _timer;
        GLdouble        _angle;

        //surfaces
        ParametricSurface3* _ps[5];
        TriangulatedMesh3*  _image_of_ps[5];

        // a bicubic Bezier patch
        BicubicBezierPatch  _patch;

        // triangulated meshes
        TriangulatedMesh3   *_before_interpolation, *_after_interpolation;

        // shader
        TriangulatedMesh3   _mesh;
        ShaderProgram       _refelction_lines,
                            _two_sided_lighting,
                            _toon;

        // feny
        DirectionalLight*   _dl;
        // gui
        GLuint  _img_select;
        GLuint  _img_index;

        // hermite
        HermitePatch        _hermite_patch;
        TriangulatedMesh3   *_img_hermite_patch;
        HermitePatch        _hermite_patch1;
        TriangulatedMesh3   *_img_hermite_patch1;

        // PROJEKT
        HermiteCompositeSurface3 *_hermite_surface;
        // patch file index olvasashoz
        GLuint _file_index;
        // patch attributum valtoztatas
        GLuint _patch_index;
        GLuint _shader_index;
        GLuint _material_index;
        // patch ext, join, merge
        GLuint _patch1_index;
        GLuint _patch2_index;
        GLuint _dir1;
        GLuint _dir2;
        //sarok cb_index, vektor cb_index
        GLuint _corner_index;
        GLuint _vector_index;

        GLdouble _xValue;
        GLdouble _yValue;
        GLdouble _zValue;


        // HERMITE ARC
        HermiteArc              *_arc_test;
        GenericCurve3           *_arc_test_img;
        HermiteCompositeCurve   *_hermit_cmp_curve;

        // hermite change indexes
        GLuint _selected_curve1;
        GLuint _selected_curve2;
        GLuint _direction1;
        GLuint _direction2;
        //egy arc kivalasztott vektorjanak mozgatasa
        GLuint      _arc_vector_index;
        GLuint      _arc_vector_nr_index;
        // CURVES MANIPULATION STUFF
        GLuint      index_of_curve;
        float       R;
        float       G;
        float       B;


    //protected:

    public:
        // special and default constructor
        // the format specifies the properties of the rendering window
        GLWidget(QWidget* parent = 0, const QGLFormat& format = QGL::Rgba | QGL::DepthBuffer | QGL::DoubleBuffer);

        // redeclared virtual functions
        void initializeGL();
        void paintGL();
        void resizeGL(int w, int h);

        virtual ~GLWidget();

    public slots:
        // public event handling methods/slots
        void set_angle_x(int value);
        void set_angle_y(int value);
        void set_angle_z(int value);

        void set_zoom_factor(double value);

        void set_trans_x(double value);
        void set_trans_y(double value);
        void set_trans_z(double value);

        void set_img(int value);
        void set_index(int value);

        // PROJEKT
        // patch olvasas filebol
        void set_file_index(int);
        void call_read_patch();
        GLboolean read_patch(GLuint i);

        void call_write_patch();
        // patch attributumok valtoztatasa
        void set_patch_index(int);
        GLboolean set_shader_index(int);
        GLboolean set_material_index(int);
        // patch ext, join, merge
        void set_direction1(int);
        void set_direction2(int);
        void set_patch1_index(int);
        void set_patch2_index(int);

        //CURVE MANIPLUATION
        void set_index_of_curve(int);
        void set_pb_Y_up();
        void set_pb_Y_down();
        void set_pb_X_up();
        void set_pb_X_down();
        void set_pb_Z_up();
        void set_pb_Z_down();
        void set_R(double);
        void set_G(double);
        void set_B(double);
        void set_curve_color();

        GLboolean call_extend_patch();
        GLboolean call_extend_new_patch();
        GLboolean call_join_patch();
        GLboolean call_merge_patch();
        // translacio x, y, z iranyokba
        void plus_X();
        void minus_X();
        void plus_Y();
        void minus_Y();
        void plus_Z();
        void minus_Z();

        //egy sarok vektorertekeinek valtoztatasai - (x,y,z)
        GLboolean set_corners_index(int);
        GLboolean set_vectors_index(int);
        GLboolean _xValue_changed(double);
        GLboolean _yValue_changed(double);
        GLboolean _zValue_changed(double);

        GLboolean _change_bt_clicked();

        //gorbe modositasa
        GLboolean curve1_index_spin_changed(int);
        GLboolean curve2_index_spin_changed(int);
        GLboolean direction1_combo_changed(int);
        GLboolean direction2_combo_changed(int);
        GLboolean call_extend_curve();
        GLboolean call_merge_curve();
        GLboolean call_join_curve();
        //egy arc kivalasztott vektorjanak mozgatasa
        GLboolean set_arc_vector_index(int);
        GLboolean set_vector_nr_index(int);

        void arc_vector_plus_X();
        void arc_vector_plus_Y();
        void arc_vector_plus_Z();
        void arc_vector_minus_X();
        void arc_vector_minus_Y();
        void arc_vector_minus_Z();



    private slots:
        void _animate();
    };
}
