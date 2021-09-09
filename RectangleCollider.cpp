#include "RectangleCollider.h"
#include <iostream>
#include <algorithm>
#include "CircleCollider.h"

using namespace std;
using namespace NCL;
using namespace CSC3222;
/** Parameterised constructor for the RectangleCollider object
*/
RectangleCollider::RectangleCollider( int width,int height) : CollisionVolume() {
    setWidth(width);
    setHeight(height);
    CollisionShape rectangle = CollisionShape::Rectangle;

}
/** Default constructor for the RectangleCollider object
*/
RectangleCollider::RectangleCollider() {
    setWidth(1.0);
    setHeight(1.0);
    CollisionShape rectangle = CollisionShape::Rectangle;
}

// accessors for width and height
int RectangleCollider::getWidth() { return RectangleCollider::width; }
void RectangleCollider::setWidth(int width) { this->width = width; }
int RectangleCollider::getHeight() { return RectangleCollider::height; }
void RectangleCollider::setHeight(int height) { this->width = height; }
/**Determine wether two RectangleCollider objects overlap
*
* @param s second rectangle tested for collision
*/
bool RectangleCollider::Collision(RectangleCollider* s) {
    if (GetPosition().x < s->GetPosition().x + s->getWidth() &&
        GetPosition().x + getWidth() > s->GetPosition().x &&
        GetPosition().y < s->GetPosition().y + s->getHeight() &&
        GetPosition().y + getHeight() > s->GetPosition().y
        )
        return true;
    else {
        return false;
    }
    }

/**Determine wether a RectangleCollider object overlaps a CircleCollider object
*
* @param c CircleCollider tested for collision
*/
bool RectangleCollider::Collision(CircleCollider* c) {

    float rectangle_center_x = GetPosition().x + getWidth() / 2;          //calculate the x coord of the rectangle's center
    float rectangle_center_y = GetPosition().y + getHeight() / 2;          //calculate the y coord of the rectangle's center
    if (rectangle_center_x == 0 && rectangle_center_y == 0) {     //if the rectangle is at the origin,test for collision
        float dx = min(float(c->GetPosition().x), (float)(getWidth() * .5));
        float dx1 = max(dx, (float)(-getWidth() * .5));
        float dy = min(float(c->GetPosition().y), (float)(getHeight() * .5));
        float dy1 = max(dy, (float)(-getHeight() * .5));
        return(dx1 - c->GetPosition().x) * (dx1 - c->GetPosition().x +
            (dy1 - c->GetPosition().y) * (dy1 - c->GetPosition().y) <= c->getRadius() * c->getRadius());
    }
    else {                                                  //if the rectangle is not at origin, move it there and test for collision
        
        float x = c->GetPosition().x - rectangle_center_x;
        float y = c->GetPosition().y - rectangle_center_y;
        SetPosition(Vector2(x,y));
        float dx = min(float(c->GetPosition().x), (float)(getWidth() * .5));
        float dx1 = max(dx, (float)(-getWidth() * .5));
        float dy = min(float(c->GetPosition().y), (float)(getHeight() * .5));
        float dy1 = max(dy, (float)(-getHeight() * .5));
        return(dx1 - c->GetPosition().x) * (dx1 - c->GetPosition().x) +
            (dy1 - c->GetPosition().y) * (dy1 - c->GetPosition().y) <= c->getRadius() * c->getRadius();
    }


}