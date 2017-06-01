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
        GLuint _file_index;
        GLuint _patch_index;
        GLuint _shader_index;
        GLuint _material_index;

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
        void set_file_index(int);
        void call_read_patch();
        GLboolean read_patch(GLuint i);

        void set_patch_index(int);
        GLboolean set_shader_index(int);
        GLboolean set_material_index(int);

    private slots:
        void _animate();
    };
}
