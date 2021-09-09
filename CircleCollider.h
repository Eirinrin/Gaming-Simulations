#pragma once
#include "CollisionVolume.h"
#include "../../Common/Vector2.h"
namespace NCL {
    using namespace Maths;
    namespace CSC3222 {
        class RectangleCollider;
        class CircleCollider :
            public CollisionVolume
        {
        public:
            CircleCollider( int radius);
            CircleCollider();
            int getRadius();
            void setRadius(int radius);
            bool Collision(CircleCollider* c);
            bool Collision(RectangleCollider* s);


        private:
            int radius;
        };
    }
}