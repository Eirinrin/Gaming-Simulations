#pragma once
#include "CollisionVolume.h"
#include "../../Common/Vector2.h"
namespace NCL {
    using namespace Maths;
    namespace CSC3222 {
        class CircleCollider;
        class RectangleCollider :
            public CollisionVolume

        {
        public:
            RectangleCollider( int width, int height);
            RectangleCollider();
            int getWidth();
            int getHeight();
            void setWidth(int newwidth);
            void setHeight(int newheight);
            bool Collision(RectangleCollider* s);
            bool Collision(CircleCollider* c);

        private:
            int width;
            int height;


        };
    }
}