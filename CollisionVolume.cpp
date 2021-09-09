#include "CollisionVolume.h"
#include "../../Common/Vector2.h"
#include "../../Common/Vector4.h"

using namespace NCL;
using namespace CSC3222;


CollisionVolume::CollisionVolume()
{

}

CollisionVolume::~CollisionVolume()
{
}


	






/**Test every two shapes for overllaping and remove the ones that are
*/
/*
bool CollisionVolume::testCollision(CollisionVolume* c) {
bool colision=false;
	for (std::size_t i = 0; i < shapes.size(); ++i) {							// iterate over all the shapes
		if (RectangleCollider* rectangle = dynamic_cast<RectangleCollider8>(shapes[i]))					//check if first shape is rectangle
		{
			if (RectangleCollider* rectangle2 = dynamic_cast<RectangleCollider*>(shapes[i + 1])) {		//check if next shape is also rectangle
				collides = rectangle->Collision(rectangle2);							//call rectangle-rectangle Collision() for 2 rectangles
				if (collides) {
					collision=true;
				}

			}
			else if (CircleCollider* circle = dynamic_cast<CircleCollider*>(shapes[i + 1])) {	//if next shape wasn't rectangle, check if it is circle. While thsi check may seem redundant, it makes easier to expand the program to more shapes.
				collides = rectangle->Collision(circle);							//call rectangle-circle Collision()  
				if (collides) {
					collision=true;
				}
			}

		}
		else if (CircleCollider* circle = dynamic_cast<CircleCollider*>(shapes[i])) {			//if first shape wasn't rectangle, check if it is circle	
			if (CircleCollider* circle2 = dynamic_cast<CircleCollider*>(shapes[i + 1])) {		//check if second shape is circle
				collides = circle->Collision(circle2);							//call circle-circle Collision()
				if (collides) {
				collision=true;
				}
			}
			else if (RectangleCollider* rectangle = dynamic_cast<RectangleCollider*>(shapes[i + 1])) {	//if second shape wasn't circle, check if it is rectangle
				collides = circle->Collision(rectangle);							//call circle-rectangle Collision()
				if (collides) {
				collision=true;

				}
			}
		}

	}
}
*/