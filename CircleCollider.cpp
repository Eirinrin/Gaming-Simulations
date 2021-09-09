#include "CircleCollider.h"
#include <iostream>
#include "Math.h"
#include <algorithm>
#include "RectangleCollider.h"
using namespace std;
using namespace NCL;
using namespace CSC3222;
/** Parameterised constructor for the CircleCollider object
*/
CircleCollider::CircleCollider( int radius) : CollisionVolume()  {
    setRadius(radius);
    CollisionShape circle = CollisionShape::Circle;
    
}
/** Default constructor for the CircleCollider object
*/
CircleCollider::CircleCollider() {
    setRadius(1);
    CollisionShape circle = CollisionShape::Circle;
}
// accessors for the radius
int CircleCollider::getRadius() { return radius; }
void CircleCollider::setRadius(int radius) { this->radius = radius; }

/**Determine wether two CircleCollider objects overlap
*
* @param c second circle tested for collision
*/
bool CircleCollider::Collision(CircleCollider* c) {
    int dx = GetPosition().x - c->GetPosition().x;
    int dy = GetPosition().y - c->GetPosition().y;
    int dist = sqrt(dx * dx + dy * dy);         //compute the ditance between the two circles' centre points
    if (dist < getRadius() + c->getRadius()) {   //if dist is smaller than the sum of the two radii, the circles are colliding
        return true;
    }


}
/**Determine wether a CircleCollider object overlaps a RectangleCollider object
*
* @param s RectangleCollider tested for collision
*/
bool CircleCollider::Collision(RectangleCollider* s) {
    float rectangle_center_x = s->GetPosition().x + s->getWidth() / 2;          //calculate the x coord of the rectangle's center
    float rectangle_center_y = s->GetPosition().y + s->getHeight() / 2;         //calculate the y coord of the rectangle's center
    if (rectangle_center_x == 0 && rectangle_center_y == 0) {         //if the rectangle is at the origin,test for collision 
        float dx = min((float)(GetPosition().x), (float)(s->getWidth() * .5));
        float dx1 = max(dx, (float)(-s->getWidth() * .5));
        float dy = min(float(GetPosition().y), (float)(s->getHeight() * .5));
        float dy1 = max(dy, (float)(-s->getHeight() * .5));
        return(dx1 - GetPosition().x) * (dx1 - GetPosition().x) +
            (dy1 - GetPosition().y) * (dy1 - GetPosition().y) <= getRadius() * getRadius();
    }
    else {     //if the rectangle is not at origin, move it there and test for collision
        float x = GetPosition().x - rectangle_center_x;
        float y = GetPosition().y - rectangle_center_y;
        SetPosition(Vector2(x,y));
        float dx = min(float (GetPosition().x), (float)(s->getWidth() * .5));
        float dx1 = max(dx, (float)(-s->getWidth() * .5));
        float dy = min(float(GetPosition().y), (float)(s->getHeight() * .5));
        float dy1 = max(dy, (float)(-s->getHeight() * .5));
        return(dx1 - GetPosition().x) * (dx1 - GetPosition().x) +
            (dy1 - GetPosition().y) * (dy1 - GetPosition().y) <= getRadius() * getRadius();
    }
}