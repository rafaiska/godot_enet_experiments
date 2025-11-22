#ifndef _vector2_h_
#define _vector2_h_

namespace rapinae {
    class Vector2 {
        public:
            Vector2(double _x, double _y): x(_x), y(_y){}
            double x;
            double y;
    };
}

#endif