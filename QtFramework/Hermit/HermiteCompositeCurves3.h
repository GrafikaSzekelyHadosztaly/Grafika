#pragma once

#include "HermiteArcs3.h"
#include "Core/Colors4.h"

using namespace std;

namespace cagd {
    class HermiteCompositeCurve3
    {
        public:
            class ArcAttributes //jellemzok
            {
                HermiteArc3     *_arc;
                GenericCurve3   *_img;
                Color4          *_color;

                ArcAttributes *_next, *_prev;
                
                //default konstruktor: mindent NULL pointerre allit (inicializalas)
                ArcAttributes();
            };
        protected:
            vector<ArcAttributes> _arcs; //kezdetben ures
            
        public:
            //konstruktor, masolo konstr, destruktor, =, render (rajzolni), VBO handling
            //insert new isolated arc, continue existing arc
            // --- Constans: enum ArcDirection<LEFT, RIGHT>
            //join existing arcs, merge args
            //translate arc, rotate arc, scale arc (eltolas, forgatas, skalazas) M3,3 X M3,1 oszlop
    };
}
