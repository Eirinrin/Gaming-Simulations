#pragma once
#include "../../Common/Vector2.h"

#include <vector>
namespace NCL {
	using namespace Maths;
	namespace CSC3222 {
		
		class CollisionVolume {
			
			Vector2 position;
		public:
			bool testCollision(CollisionVolume* c);
			
			enum class CollisionShape {
				Circle,
				Rectangle
			};
			CollisionShape collisionShape;
			CollisionShape getShape() {
				return collisionShape;
			};
			static std::vector<CollisionVolume*> shapes;
			CollisionVolume();
			~CollisionVolume();

			Vector2 GetPosition() const {
				return position;
			}

			void SetPosition(const Vector2& newPosition) {
				if (this == nullptr) {
					std::cout << "No collider loaded" << std::endl;
				}
				else {
					position = newPosition;
				}
			}
			
		};
	}
}


	