#include "Materials.h"

using namespace cagd;

Material::Material(
    const Color4& front_ambient,
    const Color4& front_diffuse,
    const Color4& front_specular,
    const Color4& front_emissive,
    GLfloat front_shininess,

    const Color4& back_ambient,
    const Color4& back_diffuse,
    const Color4& back_specular,
    const Color4& back_emissive,
    GLfloat back_shininess):

    _front_ambient	(front_ambient),
    _front_diffuse	(front_diffuse),
    _front_specular	(front_specular),
    _front_emissive	(front_emissive),
    _front_shininess	(front_shininess),

    _back_ambient	(back_ambient),
    _back_diffuse	(back_diffuse),
    _back_specular	(back_specular),
    _back_emissive	(back_emissive),
    _back_shininess	(back_shininess)
{
}

GLvoid Material::SetAmbientColor(GLenum face, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    switch (face)
    {
    case GL_FRONT:
        _front_ambient.r() = r;
        _front_ambient.g() = g;
        _front_ambient.b() = b;
        _front_ambient.a() = a;
    break;

    case GL_BACK:
        _back_ambient.r() = r;
        _back_ambient.g() = g;
        _back_ambient.b() = b;
        _back_ambient.a() = a;
    break;

    case GL_FRONT_AND_BACK:
        _front_ambient.r() = r;
        _front_ambient.g() = g;
        _front_ambient.b() = b;
        _front_ambient.a() = a;

        _back_ambient.r()  = r;
        _back_ambient.g()  = g;
        _back_ambient.b()  = b;
        _back_ambient.a()  = a;
    break;
    }
}

GLvoid Material::Apply()
{
    glMaterialfv(GL_FRONT, GL_AMBIENT,   &_front_ambient.r());
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   &_front_diffuse.r());
    glMaterialfv(GL_FRONT, GL_SPECULAR,  &_front_specular.r());
    glMaterialfv(GL_FRONT, GL_EMISSION,  &_front_emissive.r());
    glMaterialf (GL_FRONT, GL_SHININESS, _front_shininess);

    glMaterialfv(GL_BACK, GL_AMBIENT,    &_back_ambient.r());
    glMaterialfv(GL_BACK, GL_DIFFUSE,    &_back_diffuse.r());
    glMaterialfv(GL_BACK, GL_SPECULAR,   &_back_specular.r());
    glMaterialfv(GL_BACK, GL_EMISSION,   &_back_emissive.r());
    glMaterialf (GL_BACK, GL_SHININESS,  _back_shininess);
}

// brass
Material cagd::MatFBBrass = Material(
                        Color4((GLfloat)0.329412, (GLfloat)0.223529, (GLfloat)0.027451, (GLfloat)0.4),
                        Color4((GLfloat)0.780392, (GLfloat)0.568627, (GLfloat)0.113725, (GLfloat)0.6),
                        Color4((GLfloat)0.992157, (GLfloat)0.941176, (GLfloat)0.807843, (GLfloat)0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        27.8974,
                        Color4((GLfloat)0.329412, (GLfloat)0.223529, (GLfloat)0.027451, (GLfloat)0.4),
                        Color4((GLfloat)0.780392, (GLfloat)0.568627, (GLfloat)0.113725, (GLfloat)0.6),
                        Color4((GLfloat)0.992157, (GLfloat)0.941176, (GLfloat)0.807843, (GLfloat)0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        (GLfloat)27.8974);

// emerald
Material cagd::MatFBEmerald = Material(
                        Color4((GLfloat)0.021500, (GLfloat)0.174500, (GLfloat)0.021500, (GLfloat)0.4),
                        Color4((GLfloat)0.075680, (GLfloat)0.614240, (GLfloat)0.075680, (GLfloat)0.6),
                        Color4((GLfloat)0.633000, (GLfloat)0.727811, (GLfloat)0.633000, (GLfloat)0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        76.8,
                        Color4((GLfloat)0.021500, (GLfloat)0.174500, (GLfloat)0.021500, (GLfloat)0.4),
                        Color4((GLfloat)0.075680, (GLfloat)0.614240, (GLfloat)0.075680, (GLfloat)0.6),
                        Color4((GLfloat)0.633000, (GLfloat)0.727811, (GLfloat)0.633000, (GLfloat)0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        (GLfloat)76.8);

// gold
Material cagd::MatFBGold = Material(
                        Color4((GLfloat)0.247250, (GLfloat)0.199500, (GLfloat)0.074500, (GLfloat)0.4),
                        Color4((GLfloat)0.751640, (GLfloat)0.606480, (GLfloat)0.226480, (GLfloat)0.6),
                        Color4((GLfloat)0.628281, (GLfloat)0.555802, (GLfloat)0.366065, (GLfloat)0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        51.2,
                        Color4((GLfloat)0.247250, (GLfloat)0.199500, (GLfloat)0.074500, (GLfloat)0.4),
                        Color4((GLfloat)0.751640, (GLfloat)0.606480, (GLfloat)0.226480, (GLfloat)0.6),
                        Color4((GLfloat)0.628281, (GLfloat)0.555802, (GLfloat)0.366065, (GLfloat)0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        (GLfloat)51.2);

// pearl
Material cagd::MatFBPearl = Material(
                        Color4((GLfloat)0.250000, (GLfloat)0.207250, (GLfloat)0.207250, (GLfloat)0.4),
                        Color4((GLfloat)1.000000, (GLfloat)0.829000, (GLfloat)0.829000, (GLfloat)0.6),
                        Color4((GLfloat)0.296648, (GLfloat)0.296648, (GLfloat)0.296648, (GLfloat)0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        11.264,
                        Color4((GLfloat)0.250000, (GLfloat)0.207250, (GLfloat)0.207250, (GLfloat)0.4),
                        Color4((GLfloat)1.000000, (GLfloat)0.829000, (GLfloat)0.829000, (GLfloat)0.6),
                        Color4((GLfloat)0.296648, (GLfloat)0.296648, (GLfloat)0.296648, (GLfloat)0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        (GLfloat)11.264);

// ruby
Material cagd::MatFBRuby = Material(
                        Color4((GLfloat)0.174500, (GLfloat)0.011750, (GLfloat)0.011750, (GLfloat)0.4),
                        Color4((GLfloat)0.614240, (GLfloat)0.041360, (GLfloat)0.041360, (GLfloat)0.6),
                        Color4((GLfloat)0.727811, (GLfloat)0.626959, (GLfloat)0.626959, (GLfloat)0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        76.8,
                        Color4((GLfloat)0.174500, (GLfloat)0.011750, (GLfloat)0.011750, (GLfloat)0.4),
                        Color4((GLfloat)0.614240, (GLfloat)0.041360, (GLfloat)0.041360, (GLfloat)0.6),
                        Color4((GLfloat)0.727811, (GLfloat)0.626959, (GLfloat)0.626959, (GLfloat)0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        (GLfloat)76.8);

// silver
Material cagd::MatFBSilver = Material(
                        Color4((GLfloat)0.192250, (GLfloat)0.192250, (GLfloat)0.192250, (GLfloat)0.4),
                        Color4((GLfloat)0.507540, (GLfloat)0.507540, (GLfloat)0.507540, (GLfloat)0.6),
                        Color4((GLfloat)0.508273, (GLfloat)0.508273, (GLfloat)0.508273, (GLfloat)0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        51.2,
                        Color4((GLfloat)0.192250, (GLfloat)0.192250, (GLfloat)0.192250, (GLfloat)0.4),
                        Color4((GLfloat)0.507540, (GLfloat)0.507540, (GLfloat)0.507540, (GLfloat)0.6),
                        Color4((GLfloat)0.508273, (GLfloat)0.508273, (GLfloat)0.508273, (GLfloat)0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        (GLfloat)51.2);

// turquoise
Material cagd::MatFBTurquoise = Material(
                        Color4((GLfloat)0.100000, (GLfloat)0.187250, (GLfloat)0.174500, (GLfloat)0.4),
                        Color4((GLfloat)0.396000, (GLfloat)0.741510, (GLfloat)0.691020, (GLfloat)0.6),
                        Color4((GLfloat)0.297254, (GLfloat)0.308290, (GLfloat)0.306678, (GLfloat)0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        12.8,
                        Color4((GLfloat)0.100000, (GLfloat)0.187250, (GLfloat)0.174500, (GLfloat)0.4),
                        Color4((GLfloat)0.396000, (GLfloat)0.741510, (GLfloat)0.691020, (GLfloat)0.6),
                        Color4((GLfloat)0.297254, (GLfloat)0.308290, (GLfloat)0.306678, (GLfloat)0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        (GLfloat)12.8);
