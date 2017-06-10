#pragma once

#include "HermitePatches3.h"
#include "Core/TriangulatedMeshes3.h"
#include "Core/Materials.h"
#include "Core/ShaderPrograms.h"
#include "Core/Matrices.h"

using namespace std;

namespace cagd {
    class HermiteCompositeSurface3
    {
        public:
            class PatchAttributes
            {
            public:
                HermitePatch        *_patch;
                TriangulatedMesh3   *_img;
                Material            *_material;
                Material            *_selected_material;
                ShaderProgram       *_shader;
                bool                _visited;
                GLuint              _index;

                vector<PatchAttributes *>  _neighbours; // 8

                //textura, ez-az

                //alapertelmezett konstruktor:mindent NULL pointerre inicializal es helyet foglall a neighbors tombnek
                PatchAttributes();
            };
            //RowMatrix<GenericCurve3 *>     *_uIsoLines;
            //RowMatrix<GenericCurve3 *>     *_vIsoLines;

            //---Constants: enum PatchDirection{North = 0, NorthWest,..., NorthEast}
            enum PatchDirection{NORTH = 0, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST};
        protected:
            vector<PatchAttributes> _patches;
        public:
            HermiteCompositeSurface3();
            // _patches[mind]._img letrehozasa
            GLboolean GenerateImagesOfAllPatches(GLuint u_div_point_count = 30, GLuint v_div_point_count = 30, GLenum usage_flag = GL_STATIC_DRAW);
            // _patches[mind]._img kirajzolasa
            GLboolean RenderAll() const;
            // _patches[uj]._patch beszurasa (vectorok beallitasa)
            GLboolean InsertIsolatedPatch(vector<DCoordinate3> corners, vector<DCoordinate3> uTangents, vector<DCoordinate3> vTangents, vector<DCoordinate3> twists);
            // _patches[valasztott]._shader es _material beallitasa
            GLboolean SetAttributes(GLuint index, ShaderProgram *shader, Material *material);
            GLboolean SetShader(GLuint index, ShaderProgram *shader);
            GLboolean SetMaterial(GLuint index, Material *material);
            GLboolean SetSelectedMaterial(GLuint index, Material *selected_material);

            // _patches._patch[ind1] es _patches._patch[ind2] osszemosasa adott iranyoknak
            GLboolean MergeTwoPatches(GLuint index1, GLuint index2, GLuint dir1, GLuint dir2);
            DCoordinate3* Merge(DCoordinate3* vectors1, DCoordinate3* vectors2, GLuint count);
            // _patches._patch[ind1] es _patches._patch[ind2] csatlakoztatasa uj patch letrehozasaval
            // adott iranyok kozott
            GLboolean JoinTwoPatches(GLuint index1, GLuint index2, GLuint dir1, GLuint dir2);
            // egy patch megnyujtasa adott iranyban
            GLboolean ExtendPatch(GLuint index, GLuint dir);
            // egy patch megnyujtasakent uj patch letrehozasa
            GLboolean ExtendNewPatch(GLuint index, GLuint dir);
            DCoordinate3* Extend(DCoordinate3* vectors1, DCoordinate3* vectors2, GLuint count);

            GLboolean SetTransX(GLuint index, GLdouble x);
            GLboolean SetTransY(GLuint index, GLdouble y);
            GLboolean SetTransZ(GLuint index, GLdouble z);

            GLuint GetNumberOfPatches();

            DCoordinate3* GetSouth(GLuint i);
            DCoordinate3* GetNorth(GLuint i);
            DCoordinate3* GetEast(GLuint i);
            DCoordinate3* GetWest(GLuint i);
            DCoordinate3* GetNorthEast(GLuint i);
            DCoordinate3* GetNorthWest(GLuint i);
            DCoordinate3* GetSouthEast(GLuint i);
            DCoordinate3* GetSouthWest(GLuint i);

            GLboolean SetNorth(GLuint i, DCoordinate3* vectors);
            GLboolean SetSouth(GLuint i, DCoordinate3* vectors);
            GLboolean SetWest(GLuint i, DCoordinate3* vectors);
            GLboolean SetEast(GLuint i, DCoordinate3* vectors);
            GLboolean SetNorthEast(GLuint i, DCoordinate3* vectors);
            GLboolean SetNorthWest(GLuint i, DCoordinate3* vectors);
            GLboolean SetSouthEast(GLuint i, DCoordinate3* vectors);
            GLboolean SetSouthWest(GLuint i, DCoordinate3* vectors);
            GLboolean setVectorXYZ(GLuint i,GLuint j,GLdouble _xValue,GLdouble _yValue,GLdouble _zValue,GLuint _patch_index);
            GLboolean setCornerXYZ(GLuint j,GLdouble _xValue,GLdouble _yValue,GLdouble _zValue,GLuint _patch_index);
            GLboolean setUTangentXYZ(GLuint j,GLdouble _xValue,GLdouble _yValue,GLdouble _zValue,GLuint _patch_index);
            GLboolean setVTangentXYZ(GLuint j,GLdouble _xValue,GLdouble _yValue,GLdouble _zValue,GLuint _patch_index);
            GLboolean setTwistXYZ(GLuint j,GLdouble _xValue,GLdouble _yValue,GLdouble _zValue,GLuint _patch_index);

            void write_patch(GLuint i);
    };
}
