#include "Hermit/HermiteCompositeSurfaces3.h"

using namespace cagd;
using namespace std;
// valtoztatok
HermiteCompositeSurface3::HermiteCompositeSurface3()
{

}

HermiteCompositeSurface3::PatchAttributes::PatchAttributes()
{
    _patch      = nullptr;
    _img        = nullptr;
    _material   = &MatFBGold;

    ShaderProgram _two_sided_lighting;
    _two_sided_lighting.InstallShaders("Shaders/two_sided_lighting.vert", "Shaders/two_sided_lighting.frag", GL_TRUE);

    _shader     = &_two_sided_lighting;
    _neighbours.resize(8, nullptr);
}

GLboolean HermiteCompositeSurface3::GenerateImagesOfAllPatches(GLuint u_div_point_count, GLuint v_div_point_count, GLenum usage_flag)
{
    for(GLuint i = 0; i < _patches.size(); i++){
        delete _patches[i]._img;

        _patches[i]._img = _patches[i]._patch->GenerateImage(u_div_point_count, v_div_point_count, usage_flag);

        _patches[i]._img->UpdateVertexBufferObjects(usage_flag);
    }
    return GL_TRUE;
}

GLboolean HermiteCompositeSurface3::RenderAll() const
{
    for(GLuint i = 0; i < _patches.size(); i++)
    {
        if (!_patches[i]._img || !_patches[i]._material || !_patches[i]._shader)
        {
            return GL_FALSE;
        }
        glEnable(GL_LIGHTING);
            _patches[i]._material->Apply();
            _patches[i]._shader->Enable();
            _patches[i]._img->Render();
            _patches[i]._shader->Disable();
        glDisable(GL_LIGHTING);
    }
    return GL_TRUE;
}

GLboolean HermiteCompositeSurface3::InsertIsolatedPatch(vector<DCoordinate3> corners, vector<DCoordinate3> uTangents, vector<DCoordinate3> vTangents, vector<DCoordinate3> twists)
{// const &
    GLuint n = _patches.size();

    _patches.resize(n + 1);

    _patches[n]._patch = new HermitePatch();

    _patches[n]._patch->SetCorner(0, 0, corners[0]);
    _patches[n]._patch->SetCorner(0, 1, corners[1]);
    _patches[n]._patch->SetCorner(1, 0, corners[2]);
    _patches[n]._patch->SetCorner(1, 1, corners[3]);

    _patches[n]._patch->SetUTangent(0, 0, uTangents[0]);
    _patches[n]._patch->SetUTangent(0, 1, uTangents[1]);
    _patches[n]._patch->SetUTangent(1, 0, uTangents[2]);
    _patches[n]._patch->SetUTangent(1, 1, uTangents[3]);

    _patches[n]._patch->SetVTangent(0, 0, vTangents[0]);
    _patches[n]._patch->SetVTangent(0, 1, vTangents[1]);
    _patches[n]._patch->SetVTangent(1, 0, vTangents[2]);
    _patches[n]._patch->SetVTangent(1, 1, vTangents[3]);

    _patches[n]._patch->SetTwist(0, 0, twists[0]);
    _patches[n]._patch->SetTwist(0, 1, twists[1]);
    _patches[n]._patch->SetTwist(1, 0, twists[2]);
    _patches[n]._patch->SetTwist(1, 1, twists[3]);

    _patches[n]._img = _patches[n]._patch->GenerateImage(30, 30, GL_STATIC_DRAW);

    _patches[n]._img->UpdateVertexBufferObjects(GL_STATIC_DRAW);

    return GL_TRUE;
}

GLboolean HermiteCompositeSurface3::SetAttributes(GLuint index, ShaderProgram *shader, Material *material)
{
    _patches[index]._shader = shader;
    _patches[index]._material = material;
    return GL_TRUE;
}

GLboolean HermiteCompositeSurface3::SetShader(GLuint index, ShaderProgram *shader)
{
    _patches[index]._shader = shader;
     return GL_TRUE;
}

GLboolean HermiteCompositeSurface3::SetMaterial(GLuint index, Material *material)
{
    _patches[index]._material = material;
    return GL_TRUE;
}

GLboolean HermiteCompositeSurface3::MergeTwoPatches(GLuint patch1, GLuint patch2, GLuint dir1, GLuint dir2)
{
    if(_patches[patch1]._neighbours[dir1] != nullptr)
    {
        return GL_FALSE;
    }
    if(_patches[patch2]._neighbours[dir2] != nullptr)
    {
        return GL_FALSE;
    }

    DCoordinate3* _vectors1;
    DCoordinate3* _vectors2;
    DCoordinate3* _vectors;

    switch(dir1)
    {
    case 0:
        _vectors1 = GetNorth(patch1);
        switch(dir2)
        {
        case 0:
            _vectors2 = GetNorth(patch2);
            _vectors = Merge(_vectors1, _vectors2,8);
            SetNorth(patch2, _vectors);
            SetNorth(patch1, _vectors);
            break;
        case 2:
            _vectors2 = GetEast(patch2);
            _vectors = Merge(_vectors1, _vectors2,8);
            SetEast(patch2, _vectors);
            SetNorth(patch1, _vectors);
            break;
        case 4:
            _vectors2 = GetSouth(patch2);
            _vectors = Merge(_vectors1, _vectors2,8);
            SetSouth(patch2, _vectors);
            SetNorth(patch1, _vectors);
            break;
        case 6:
            _vectors2 = GetWest(patch2);
            _vectors = Merge(_vectors1, _vectors2,8);
            SetWest(patch2, _vectors);
            SetNorth(patch1, _vectors);
            break;
        }
        break;

    case 1:
        // NORTHEAST
        _vectors1 = GetNorthEast(patch1);
        switch(dir2)
        {
        case 1:
            _vectors2 = GetNorthEast(patch2);
            _vectors = Merge(_vectors1, _vectors2,4);
            SetNorthEast(patch2, _vectors);
            SetNorthEast(patch1, _vectors);
            break;
        case 3:
            _vectors2 = GetSouthEast(patch2);
            _vectors = Merge(_vectors1, _vectors2,4);
            SetSouthEast(patch2, _vectors);
            SetNorthEast(patch1, _vectors);
            break;
        case 5:
            _vectors2 = GetSouthWest(patch2);
            _vectors = Merge(_vectors1, _vectors2,4);
            SetSouthWest(patch2, _vectors);
            SetNorthEast(patch1, _vectors);
            break;
        case 7:
            _vectors2 = GetNorthWest(patch2);
            _vectors = Merge(_vectors1, _vectors2,4);
            SetNorthWest(patch2, _vectors);
            SetNorthEast(patch1, _vectors);
            break;
        }
        break;

    case 2:
        _vectors1 = GetEast(patch1);
        switch(dir2)
        {
        case 0:
            _vectors2 = GetNorth(patch2);
            _vectors = Merge(_vectors1, _vectors2,8);
            SetNorth(patch2, _vectors);
            SetEast(patch1, _vectors);
            break;
        case 2:
            _vectors2 = GetEast(patch2);
            _vectors = Merge(_vectors1, _vectors2,8);
            SetEast(patch2, _vectors);
            SetEast(patch1, _vectors);
            break;
        case 4:
            _vectors2 = GetSouth(patch2);
            _vectors = Merge(_vectors1, _vectors2,8);
            SetSouth(patch2, _vectors);
            SetEast(patch1, _vectors);
            break;
        case 6:
            _vectors2 = GetWest(patch2);
            _vectors = Merge(_vectors1, _vectors2,8);
            SetWest(patch2, _vectors);
            SetEast(patch1, _vectors);
            break;
        }
        break;

    case 3:
        // SOUTHEAST
        _vectors1 = GetSouthEast(patch1);
        switch(dir2)
        {
        case 1:
            _vectors2 = GetNorthEast(patch2);
            _vectors = Merge(_vectors1, _vectors2,4);
            SetNorthEast(patch2, _vectors);
            SetSouthEast(patch1, _vectors);
            break;
        case 3:
            _vectors2 = GetSouthEast(patch2);
            _vectors = Merge(_vectors1, _vectors2,4);
            SetSouthEast(patch2, _vectors);
            SetSouthEast(patch1, _vectors);
            break;
        case 5:
            _vectors2 = GetSouthWest(patch2);
            _vectors = Merge(_vectors1, _vectors2,4);
            SetSouthWest(patch2, _vectors);
            SetSouthEast(patch1, _vectors);
            break;
        case 7:
            _vectors2 = GetNorthWest(patch2);
            _vectors = Merge(_vectors1, _vectors2,4);
            SetNorthWest(patch2, _vectors);
            SetSouthEast(patch1, _vectors);
            break;
        }
        break;

    case 4:
        // SOUTH

        _vectors1 = GetSouth(patch1);
        switch(dir2)
        {
        case 0:
            _vectors2 = GetNorth(patch2);
            _vectors = Merge(_vectors1, _vectors2,8);
            SetNorth(patch2, _vectors);
            SetSouth(patch1, _vectors);
            break;
        case 2:
            _vectors2 = GetEast(patch2);
            _vectors = Merge(_vectors1, _vectors2,8);
            SetEast(patch2, _vectors);
            SetSouth(patch1, _vectors);
            break;
        case 4:
            _vectors2 = GetSouth(patch2);
            _vectors = Merge(_vectors1, _vectors2,8);
            SetSouth(patch2, _vectors);
            SetSouth(patch1, _vectors);
            break;
        case 6:
            _vectors2 = GetWest(patch2);
            _vectors = Merge(_vectors1, _vectors2,8);
            SetWest(patch2, _vectors);
            SetSouth(patch1, _vectors);
            break;
        }
        break;

    case 5:
        // SOUTHWEST

        _vectors1 = GetSouthWest(patch1);
        switch(dir2)
        {
        case 1:
            _vectors2 = GetNorthEast(patch2);
            _vectors = Merge(_vectors1, _vectors2,4);
            SetNorthEast(patch2, _vectors);
            SetSouthWest(patch1, _vectors);
            break;
        case 3:
            _vectors2 = GetSouthEast(patch2);
            _vectors = Merge(_vectors1, _vectors2,4);
            SetSouthEast(patch2, _vectors);
            SetSouthWest(patch1, _vectors);
            break;
        case 5:
            _vectors2 = GetSouthWest(patch2);
            _vectors = Merge(_vectors1, _vectors2,4);
            SetSouthWest(patch2, _vectors);
            SetSouthWest(patch1, _vectors);
            break;
        case 7:
            _vectors2 = GetNorthWest(patch2);
            _vectors = Merge(_vectors1, _vectors2,4);
            SetNorthWest(patch2, _vectors);
            SetSouthWest(patch1, _vectors);
            break;
        }
        break;
    case 6:
        // WEST
        _vectors1 = GetWest(patch1);
        switch(dir2)
        {
        case 0:
            _vectors2 = GetNorth(patch2);
            _vectors = Merge(_vectors1, _vectors2,8);
            SetNorth(patch2, _vectors);
            SetWest(patch1, _vectors);
            break;
        case 2:
            _vectors2 = GetEast(patch2);
            _vectors = Merge(_vectors1, _vectors2,8);
            SetEast(patch2, _vectors);
            SetWest(patch1, _vectors);
            break;
        case 4:
            _vectors2 = GetSouth(patch2);
            _vectors = Merge(_vectors1, _vectors2,8);
            SetSouth(patch2, _vectors);
            SetWest(patch1, _vectors);
            break;
        case 6:
            _vectors2 = GetWest(patch2);
            _vectors = Merge(_vectors1, _vectors2,8);
            SetWest(patch2, _vectors);
            SetWest(patch1, _vectors);
            break;
        }
        break;
    case 7:
        // NORTHWEST
        _vectors1 = GetNorthWest(patch1);
        switch(dir2)
        {
        case 1:
            _vectors2 = GetNorthEast(patch2);
            _vectors = Merge(_vectors1, _vectors2,4);
            SetNorthEast(patch2, _vectors);
            SetNorthWest(patch1, _vectors);
            break;
        case 3:
            _vectors2 = GetSouthEast(patch2);
            _vectors = Merge(_vectors1, _vectors2,4);
            SetSouthEast(patch2, _vectors);
            SetNorthWest(patch1, _vectors);
            break;
        case 5:
            _vectors2 = GetSouthWest(patch2);
            _vectors = Merge(_vectors1, _vectors2,4);
            SetSouthWest(patch2, _vectors);
            SetNorthWest(patch1, _vectors);
            break;
        case 7:
            _vectors2 = GetNorthWest(patch2);
            _vectors = Merge(_vectors1, _vectors2,4);
            SetNorthWest(patch2, _vectors);
            SetNorthWest(patch1, _vectors);
            break;
        }
        break;
    }
    _patches[patch1]._neighbours[dir1]   = &_patches[patch2];
    _patches[patch2]._neighbours[dir2]   = &_patches[patch1];
    GenerateImagesOfAllPatches();

    return GL_TRUE;
}

DCoordinate3* HermiteCompositeSurface3::Merge(DCoordinate3 *vectors1, DCoordinate3 *vectors2,GLuint count)
{
    DCoordinate3 *ret = new DCoordinate3[count];
    for(GLuint i = 0; i < count; i++)
    {
        ret[i] = (vectors1[i] + vectors2[i]) / 2;
    }

    return ret;
}

GLboolean HermiteCompositeSurface3::JoinTwoPatches(GLuint patch1, GLuint patch2, GLuint dir1, GLuint dir2)
{
    if(_patches[patch1]._neighbours[dir1] != nullptr)
    {
        return GL_FALSE;
    }
    if(_patches[patch2]._neighbours[dir2] != nullptr)
    {
        return GL_FALSE;
    }

    DCoordinate3* _vectors1;
    DCoordinate3* _vectors2;

    //dir1 = 2*dir1;
    //dir2 = 2*dir2;

    GLuint n = _patches.size();
    _patches.resize(n + 1);
    _patches[n]._patch = new HermitePatch();

    switch (dir2) {
        case 0:
            _vectors2 = GetNorth(patch2);
            break;
        case 2:
            _vectors2 = GetEast(patch2);
            break;
        case 4:
            _vectors2 = GetSouth(patch2);
            break;
        case 6:
            _vectors2 = GetWest(patch2);
            break;
        default:
            break;
        }

        switch(dir1)
        {
        case 0:
            // NOTRH
            // switch(dir2) case 0, 2, 4, 6

            _vectors1 = GetNorth(patch1);

            SetSouth(n, _vectors1);
            SetNorth(n, _vectors2);
            break;

        case 2:
            // EAST

            _vectors1 = GetEast(patch1);

            SetWest(n, _vectors1);
            SetEast(n, _vectors2);
            break;

        case 4:
            // SOUTH

            _vectors1 = GetSouth(patch1);

            SetNorth(n, _vectors1);
            SetSouth(n, _vectors2);
            break;

        case 6:
            // WEST

            _vectors1 = GetWest(patch1);

            SetEast(n, _vectors1);
            SetWest(n, _vectors2);
            break;
        }

    _patches[patch1]._neighbours[dir1]  = &_patches[n];

    _patches[n]._neighbours[dir2]       = &_patches[patch1];
    _patches[n]._neighbours[dir1]       = &_patches[patch2];

    _patches[patch2]._neighbours[dir2]  = &_patches[n];

    GenerateImagesOfAllPatches();

    return GL_TRUE;
}

GLboolean HermiteCompositeSurface3::ExtendPatch(GLuint index, GLuint dir)
{
    if(_patches[index]._neighbours[dir] != nullptr)
    {
        return GL_FALSE;
    }

    DCoordinate3* _vectors1;
    DCoordinate3* _vectors2;
    DCoordinate3* _vectors;

    switch(dir)
        {
        case 0:
            // NOTRH
            _vectors1 = GetNorth(index);
            _vectors2 = GetSouth(index);
            _vectors = Extend(_vectors1, _vectors2, 8);

            SetSouth(index, _vectors);
            break;

        case 1:
            // NORTHEAST
            _vectors1 = GetNorthEast(index);
            _vectors2 = GetSouthWest(index);
            _vectors = Extend(_vectors1, _vectors2, 4);

            SetSouth(index, _vectors);
            break;

        case 2:
            // EAST
            _vectors1 = GetEast(index);
            _vectors2 = GetWest(index);
            _vectors = Extend(_vectors1, _vectors2, 8);

            SetSouth(index, _vectors);
            break;

        case 3:
            // SOUTHEAST
            _vectors1 = GetSouthEast(index);
            _vectors2 = GetNorthWest(index);
            _vectors = Extend(_vectors1, _vectors2, 4);

            SetSouth(index, _vectors);
            break;

        case 4:
            // SOUTH
            _vectors1 = GetSouth(index);
            _vectors2 = GetNorth(index);
            _vectors = Extend(_vectors1, _vectors2, 8);

            SetSouth(index, _vectors);
            break;

        case 5:
            // SOUTHWEST
            _vectors1 = GetSouthWest(index);
            _vectors2 = GetNorthEast(index);
            _vectors = Extend(_vectors1, _vectors2, 4);

            SetSouth(index, _vectors);
            break;

        case 6:
            // WEST
            _vectors1 = GetWest(index);
            _vectors2 = GetEast(index);
            _vectors = Extend(_vectors1, _vectors2, 8);

            SetSouth(index, _vectors);
            break;

        case 7:
            // NORTHWEST
            _vectors1 = GetNorthWest(index);
            _vectors2 = GetSouthEast(index);
            _vectors = Extend(_vectors1, _vectors2, 4);

            SetSouth(index, _vectors);
            break;
        }

    GenerateImagesOfAllPatches();

    return GL_TRUE;
}

DCoordinate3* HermiteCompositeSurface3::Extend(DCoordinate3* vectors1, DCoordinate3* vectors2, GLuint count){
    DCoordinate3 *ret = new DCoordinate3[count];
    for(GLuint i = 0; i < count; i++)
    {
        ret[i] = (2*vectors1[i] - vectors2[i]);
    }

    return ret;
}

GLuint HermiteCompositeSurface3::GetNumberOfPatches()
{
    GLuint n = _patches.size();
    return n;
}

DCoordinate3* HermiteCompositeSurface3::GetSouth(GLuint i)
{
    DCoordinate3 *ret = new DCoordinate3[8];

    ret[0] = _patches[i]._patch->GetCorner(0, 0);
    ret[1] = _patches[i]._patch->GetCorner(1, 0);

    ret[2] = _patches[i]._patch->GetUTangent(0, 0);
    ret[3] = _patches[i]._patch->GetUTangent(1, 0);

    ret[4] = _patches[i]._patch->GetVTangent(0, 0);
    ret[5] = _patches[i]._patch->GetVTangent(1, 0);

    ret[6] = _patches[i]._patch->GetTwist(0, 0);
    ret[7] = _patches[i]._patch->GetTwist(1, 0);

    return ret;
}

DCoordinate3* HermiteCompositeSurface3::GetNorth(GLuint i)
{
    DCoordinate3 *ret = new DCoordinate3[8];

    ret[0] = _patches[i]._patch->GetCorner(0, 1);
    ret[1] = _patches[i]._patch->GetCorner(1, 1);

    ret[2] = _patches[i]._patch->GetUTangent(0, 1);
    ret[3] = _patches[i]._patch->GetUTangent(1, 1);

    ret[4] = _patches[i]._patch->GetVTangent(0, 1);
    ret[5] = _patches[i]._patch->GetVTangent(1, 1);

    ret[6] = _patches[i]._patch->GetTwist(0, 1);
    ret[7] = _patches[i]._patch->GetTwist(1, 1);

    return ret;
}

DCoordinate3* HermiteCompositeSurface3::GetEast(GLuint i)
{
    DCoordinate3 *ret = new DCoordinate3[8];

    ret[0] = _patches[i]._patch->GetCorner(1, 1);
    ret[1] = _patches[i]._patch->GetCorner(1, 0);

    ret[2] = _patches[i]._patch->GetUTangent(1, 1);
    ret[3] = _patches[i]._patch->GetUTangent(1, 0);

    ret[4] = _patches[i]._patch->GetVTangent(1, 1);
    ret[5] = _patches[i]._patch->GetVTangent(1, 0);

    ret[6] = _patches[i]._patch->GetTwist(1, 1);
    ret[7] = _patches[i]._patch->GetTwist(1, 0);

    return ret;
}

DCoordinate3* HermiteCompositeSurface3::GetWest(GLuint i)
{
    DCoordinate3 *ret = new DCoordinate3[8];

    ret[0] = _patches[i]._patch->GetCorner(0, 1);
    ret[1] = _patches[i]._patch->GetCorner(0, 0);

    ret[2] = _patches[i]._patch->GetUTangent(0, 1);
    ret[3] = _patches[i]._patch->GetUTangent(0, 0);

    ret[4] = _patches[i]._patch->GetVTangent(0, 1);
    ret[5] = _patches[i]._patch->GetVTangent(0, 0);

    ret[6] = _patches[i]._patch->GetTwist(0, 1);
    ret[7] = _patches[i]._patch->GetTwist(0, 0);

    return ret;
}

DCoordinate3* HermiteCompositeSurface3::GetNorthEast(GLuint i)
{
    DCoordinate3 *ret = new DCoordinate3[4];

    ret[0] = _patches[i]._patch->GetCorner(1, 1);

    ret[1] = _patches[i]._patch->GetUTangent(1, 1);

    ret[2] = _patches[i]._patch->GetVTangent(1, 1);

    ret[3] = _patches[i]._patch->GetTwist(1, 1);

    return ret;
}

DCoordinate3* HermiteCompositeSurface3::GetNorthWest(GLuint i)
{
    DCoordinate3 *ret = new DCoordinate3[4];

    ret[0] = _patches[i]._patch->GetCorner(0, 1);

    ret[1] = _patches[i]._patch->GetUTangent(0, 1);

    ret[2] = _patches[i]._patch->GetVTangent(0, 1);

    ret[3] = _patches[i]._patch->GetTwist(0, 1);

    return ret;
}

DCoordinate3* HermiteCompositeSurface3::GetSouthEast(GLuint i)
{
    DCoordinate3 *ret = new DCoordinate3[4];

    ret[0] = _patches[i]._patch->GetCorner(1, 0);

    ret[1] = _patches[i]._patch->GetUTangent(1,0);

    ret[2] = _patches[i]._patch->GetVTangent(1, 0);

    ret[3] = _patches[i]._patch->GetTwist(1, 0);

    return ret;
}

DCoordinate3* HermiteCompositeSurface3::GetSouthWest(GLuint i)
{
    DCoordinate3 *ret = new DCoordinate3[4];

    ret[0] = _patches[i]._patch->GetCorner(0, 0);

    ret[1] = _patches[i]._patch->GetUTangent(0, 0);

    ret[2] = _patches[i]._patch->GetVTangent(0, 0);

    ret[3] = _patches[i]._patch->GetTwist(0, 0);

    return ret;
}

GLboolean HermiteCompositeSurface3::SetNorth(GLuint i, DCoordinate3 *vectors)
{
    _patches[i]._patch->SetCorner(0, 1, vectors[0]);
    _patches[i]._patch->SetCorner(1, 1, vectors[1]);

    _patches[i]._patch->SetUTangent(0, 1, vectors[2]);
    _patches[i]._patch->SetUTangent(1, 1, vectors[3]);

    _patches[i]._patch->SetVTangent(0, 1, vectors[4]);
    _patches[i]._patch->SetVTangent(1, 1, vectors[5]);

    _patches[i]._patch->SetTwist(0, 1, vectors[6]);
    _patches[i]._patch->SetTwist(1, 1, vectors[7]);

    return GL_TRUE;
}

GLboolean HermiteCompositeSurface3::SetSouth(GLuint i, DCoordinate3 *vectors)
{
    _patches[i]._patch->SetCorner(0, 0, vectors[0]);
    _patches[i]._patch->SetCorner(1, 0, vectors[1]);

    _patches[i]._patch->SetUTangent(0, 0, vectors[2]);
    _patches[i]._patch->SetUTangent(1, 0, vectors[3]);

    _patches[i]._patch->SetVTangent(0, 0, vectors[4]);
    _patches[i]._patch->SetVTangent(1, 0, vectors[5]);

    _patches[i]._patch->SetTwist(0, 0, vectors[6]);
    _patches[i]._patch->SetTwist(1, 0, vectors[7]);

    return GL_TRUE;
}

GLboolean HermiteCompositeSurface3::SetEast(GLuint i, DCoordinate3 *vectors)
{
    _patches[i]._patch->SetCorner(1, 1, vectors[0]);
    _patches[i]._patch->SetCorner(1, 0, vectors[1]);

    _patches[i]._patch->SetUTangent(1, 1, vectors[2]);
    _patches[i]._patch->SetUTangent(1, 0, vectors[3]);

    _patches[i]._patch->SetVTangent(1, 1, vectors[4]);
    _patches[i]._patch->SetVTangent(1, 0, vectors[5]);

    _patches[i]._patch->SetTwist(1, 1, vectors[6]);
    _patches[i]._patch->SetTwist(1, 0, vectors[7]);

    return GL_TRUE;
}

GLboolean HermiteCompositeSurface3::SetWest(GLuint i, DCoordinate3 *vectors)
{
    _patches[i]._patch->SetCorner(0, 1, vectors[0]);
    _patches[i]._patch->SetCorner(0, 0, vectors[1]);

    _patches[i]._patch->SetUTangent(0, 1, vectors[2]);
    _patches[i]._patch->SetUTangent(0, 0, vectors[3]);

    _patches[i]._patch->SetVTangent(0, 1, vectors[4]);
    _patches[i]._patch->SetVTangent(0, 0, vectors[5]);

    _patches[i]._patch->SetTwist(0, 1, vectors[6]);
    _patches[i]._patch->SetTwist(0, 0, vectors[7]);

    return GL_TRUE;
}

GLboolean HermiteCompositeSurface3::SetNorthEast(GLuint i, DCoordinate3 *vectors)
{
    _patches[i]._patch->SetCorner(1, 1, vectors[0]);

    _patches[i]._patch->SetUTangent(1, 1, vectors[1]);

    _patches[i]._patch->SetVTangent(1, 1, vectors[2]);

    _patches[i]._patch->SetTwist(1, 1, vectors[3]);

    return GL_TRUE;
}

GLboolean HermiteCompositeSurface3::SetNorthWest(GLuint i, DCoordinate3 *vectors)
{
    _patches[i]._patch->SetCorner(0, 1, vectors[0]);

    _patches[i]._patch->SetUTangent(0, 1, vectors[1]);

    _patches[i]._patch->SetVTangent(0, 1, vectors[2]);

    _patches[i]._patch->SetTwist(0, 1, vectors[3]);

    return GL_TRUE;
}

GLboolean HermiteCompositeSurface3::SetSouthEast(GLuint i, DCoordinate3 *vectors)
{
    _patches[i]._patch->SetCorner(1, 0, vectors[0]);

    _patches[i]._patch->SetUTangent(1, 0, vectors[1]);

    _patches[i]._patch->SetVTangent(1, 0, vectors[2]);

    _patches[i]._patch->SetTwist(1, 0, vectors[3]);

    return GL_TRUE;
}

GLboolean HermiteCompositeSurface3::SetSouthWest(GLuint i, DCoordinate3 *vectors)
{
    _patches[i]._patch->SetCorner(0, 0, vectors[0]);

    _patches[i]._patch->SetUTangent(0, 0, vectors[1]);

    _patches[i]._patch->SetVTangent(0, 0, vectors[2]);

    _patches[i]._patch->SetTwist(0, 0, vectors[3]);

    return GL_TRUE;
}

