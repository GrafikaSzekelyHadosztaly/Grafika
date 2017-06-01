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
                        Color4(0.329412, 0.223529, 0.027451, 0.4),
                        Color4(0.780392, 0.568627, 0.113725, 0.6),
                        Color4(0.992157, 0.941176, 0.807843, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        27.8974,
                        Color4(0.329412, 0.223529, 0.027451, 0.4),
                        Color4(0.780392, 0.568627, 0.113725, 0.6),
                        Color4(0.992157, 0.941176, 0.807843, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        27.8974);

// emerald
Material cagd::MatFBEmerald = Material(
                        Color4(0.021500, 0.174500, 0.021500, 0.4),
                        Color4(0.075680, 0.614240, 0.075680, 0.6),
                        Color4(0.633000, 0.727811, 0.633000, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        76.8,
                        Color4(0.021500, 0.174500, 0.021500, 0.4),
                        Color4(0.075680, 0.614240, 0.075680, 0.6),
                        Color4(0.633000, 0.727811, 0.633000, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        76.8);

// gold
Material cagd::MatFBGold = Material(
                        Color4(0.247250, 0.199500, 0.074500, 0.4),
                        Color4(0.751640, 0.606480, 0.226480, 0.6),
                        Color4(0.628281, 0.555802, 0.366065, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        51.2,
                        Color4(0.247250, 0.199500, 0.074500, 0.4),
                        Color4(0.751640, 0.606480, 0.226480, 0.6),
                        Color4(0.628281, 0.555802, 0.366065, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        51.2);

// pearl
Material cagd::MatFBPearl = Material(
                        Color4(0.250000, 0.207250, 0.207250, 0.4),
                        Color4(1.000000, 0.829000, 0.829000, 0.6),
                        Color4(0.296648, 0.296648, 0.296648, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        11.264,
                        Color4(0.250000, 0.207250, 0.207250, 0.4),
                        Color4(1.000000, 0.829000, 0.829000, 0.6),
                        Color4(0.296648, 0.296648, 0.296648, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        11.264);

// ruby
Material cagd::MatFBRuby = Material(
                        Color4(0.174500, 0.011750, 0.011750, 0.4),
                        Color4(0.614240, 0.041360, 0.041360, 0.6),
                        Color4(0.727811, 0.626959, 0.626959, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        76.8,
                        Color4(0.174500, 0.011750, 0.011750, 0.4),
                        Color4(0.614240, 0.041360, 0.041360, 0.6),
                        Color4(0.727811, 0.626959, 0.626959, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        76.8);

// silver
Material cagd::MatFBSilver = Material(
                        Color4(0.192250, 0.192250, 0.192250, 0.4),
                        Color4(0.507540, 0.507540, 0.507540, 0.6),
                        Color4(0.508273, 0.508273, 0.508273, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        51.2,
                        Color4(0.192250, 0.192250, 0.192250, 0.4),
                        Color4(0.507540, 0.507540, 0.507540, 0.6),
                        Color4(0.508273, 0.508273, 0.508273, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        51.2);

// turquoise
Material cagd::MatFBTurquoise = Material(
                        Color4(0.100000, 0.187250, 0.174500, 0.4),
                        Color4(0.396000, 0.741510, 0.691020, 0.6),
                        Color4(0.297254, 0.308290, 0.306678, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        12.8,
                        Color4(0.100000, 0.187250, 0.174500, 0.4),
                        Color4(0.396000, 0.741510, 0.691020, 0.6),
                        Color4(0.297254, 0.308290, 0.306678, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        12.8);
