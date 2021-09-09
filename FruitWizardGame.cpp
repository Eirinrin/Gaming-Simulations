#include "FruitWizardGame.h"
#include "SimObject.h"
#include "GameMap.h"
#include "TextureManager.h"
#include "GameSimsRenderer.h"
#include "GameSimsPhysics.h"
#include "PlayerCharacter.h"
#include "Fruit.h"
#include "Guard.h"
#include "Froggo.h"
#include "Pixie.h"
#include "PixieDust.h"
#include "Spell.h"
#include "CollisionVolume.h"
#include "../../Common/Window.h"
#include "../../Common/TextureLoader.h"
#include <random>


using namespace NCL;
using namespace CSC3222;

FruitWizardGame::FruitWizardGame()	{
	renderer	= new GameSimsRenderer();
	texManager	= new TextureManager();
	physics		= new GameSimsPhysics();
	SimObject::InitObjects(this, texManager);
	InitialiseGame();
}

FruitWizardGame::~FruitWizardGame()	{
	delete currentMap;
	delete texManager;
	delete renderer;
	delete physics;
}

void FruitWizardGame::Update(float dt) {
	for (auto i : newObjects) {
		gameObjects.emplace_back(i);
	}
	newObjects.clear();

	gameTime += dt;

	renderer->Update(dt);
	physics->Update(dt);
	currentMap->DrawMap(*renderer);

	srand((int)(gameTime * 1000.0f));

	for (auto i = gameObjects.begin(); i != gameObjects.end(); ) {
		(*i)->UpdateAnimFrame(dt);
		if (!(*i)->UpdateObject(dt)) { //object has said its finished with
			delete (*i);
			 i = gameObjects.erase(i);
		}
		else {
			(*i)->DrawObject(*renderer);
			//bool collides = false;
			CollisionVolume* collider = (*i)->GetCollider();
			/*CollisionVolume* secondCollider = (*i + 1)->GetCollider();
			if (collider->getShape()==CollisionVolume::CollisionShape::Rectangle) {//check if first shape is rectangle
				//std::cout << "Rectangle" << std::endl;
				if (secondCollider->getShape() == CollisionVolume::CollisionShape::Rectangle) {//check if next shape is also rectangle
					collides = collider->Collision(secondCollider);							//call rectangle-rectangle Collision() for 2 rectangle
				}
			}*/
			

			++i;
		}
	}	
	renderer->DrawString("Score:" + std::to_string(currentScore), 
		Vector2(32, 12), Vector4(1,1,1,1), 100.0f);
	renderer->DrawString("Lives:" + std::to_string(lives), 
		Vector2(144, 12), Vector4(1, 0,0, 1), 100.0f);
	renderer->DrawString("Magic:" + std::to_string(magicCount), 
		Vector2(256, 12), Vector4(1, 0, 0.5f, 1), 100.0f);
	renderer->DrawString("Dust:"  + std::to_string(dustCount), 
		Vector2(366, 12), Vector4(0.5f, 0.3f, 0.8f, 1), 100.0f);

	/*
	Some examples of debug rendering! 
	These all use coordinates in the same 'space' as the game positions
	*/
	/*renderer->DrawBox(Vector2(16,16), Vector2(8, 8), Vector4(1, 0, 0, 1));
	renderer->DrawLine(Vector2(16, 16), Vector2(120, 280), Vector4(1, 1, 0, 1));
	renderer->DrawCircle(Vector2(100, 100), 10.0f, Vector4(1, 0, 1, 1));

	renderer->DrawCircle(player->GetPosition(), 10.0f, Vector4(1, 0, 1, 1));
	renderer->DrawBox(player->GetPosition(), Vector2(8, 8), Vector4(1, 0, 0, 1));

	renderer->Render();*/
}

void FruitWizardGame::InitialiseGame() {
	delete currentMap;
	for (auto o : gameObjects) {
		delete o;
	}
	gameObjects.clear();

	currentMap = new GameMap("FruitWizardMap.txt", gameObjects, *texManager);

	renderer->SetScreenProperties(16, currentMap->GetMapWidth(), currentMap->GetMapHeight());

	player = new PlayerCharacter();
	player->SetPosition(Vector2(100, 32));
	AddNewObject(player);

	Guard* testGuard = new Guard();
	testGuard->SetPosition(Vector2(40, 224));
	AddNewObject(testGuard);


	
	GenerateFruit(16);
	

	PixieDust* testDust = new PixieDust();
	testDust->SetPosition(Vector2(285, 220));
	AddNewObject(testDust);

	Pixie* pixie = new Pixie();
	pixie->SetPosition(Vector2(350, 96));
	AddNewObject(pixie);

	Froggo* testFroggo = new Froggo();
	testFroggo->SetPosition(Vector2(250, 285));
	AddNewObject(testFroggo);

	gameTime		= 0;
	currentScore	= 0;
	magicCount		= 0;
	dustCount		= 0;
	lives			= 3;
}

void FruitWizardGame::AddNewObject(SimObject* object) {
	newObjects.emplace_back(object);
	physics->AddRigidBody(object);
	if (object->GetCollider()) {
		physics->AddCollider(object->GetCollider());
	}
}
//spawn fruit
void FruitWizardGame::GenerateFruit(int y) {
	
	for (int i = 0; i <= y;i++) {


		const std::vector<int> yCoordList{ 21, 88, 150, 215, 280 };//a list of all the viable y coordinated
		std::random_device Y_rd;
		std::mt19937 yCoord(Y_rd());
		std::uniform_int_distribution<> Y_distr(0, yCoordList.size() - 1);
		int Y_coord = yCoordList[Y_distr(yCoord)];

		if (Y_coord == 21) {//fruit will be placed on the ground level
			std::random_device X_rd; // obtain a random number from hardware
			std::mt19937 xCoord(X_rd()); // seed the generator
			std::uniform_int_distribution<> X_distr(20, 420); // define the range
			Fruit* fruit = new Fruit();
			fruit->SetPosition(Vector2(X_distr(xCoord), Y_coord));//randomly place fruit in viable positions
			AddNewObject(fruit);
		}
		else if (Y_coord == 88) {//fruit will be placed on the first level
			std::random_device X_rd;
			std::mt19937 xCoord(X_rd());
			//viable x coord ranges are 20-150 & 190-420 
			std::uniform_int_distribution<> X_distr(0, 361);
			int X_coord = X_distr(xCoord);
			if (X_coord < 131) {
				X_coord = X_coord + 20;
			}
			else {
				X_coord = 190 + X_coord - 131;
			}

			Fruit* fruit = new Fruit();
			fruit->SetPosition(Vector2(X_coord, Y_coord));
			AddNewObject(fruit);
		}
		else if (Y_coord == 150) {//fruit will be placed on the second level
			std::random_device X_rd;
			std::mt19937 xCoord(X_rd());
			std::uniform_int_distribution<> X_distr(195, 420);
			Fruit* fruit = new Fruit();
			fruit->SetPosition(Vector2(X_distr(xCoord), Y_coord));
			AddNewObject(fruit);
		}
		else if (Y_coord == 215) {//fruit will be placed on the third level
			std::random_device X_rd;
			std::mt19937 xCoord(X_rd());
			//20-170 & 250-300
			std::uniform_int_distribution<> X_distr(0, 201);
			int X_coord = X_distr(xCoord);
			if (X_coord < 151) {
				X_coord = X_coord + 20;
			}
			else {
				X_coord = 250 + X_coord - 151;
			}
			Fruit* fruit = new Fruit();
			fruit->SetPosition(Vector2(X_coord, Y_coord));
			AddNewObject(fruit);
		}
		else if (Y_coord == 280) {//fruit will be placed on the fourth level
			std::random_device X_rd;
			std::mt19937 xCoord(X_rd());
			//20-120 & 220-420
			std::uniform_int_distribution<> X_distr(0, 301);
			int X_coord = X_distr(xCoord);
			if (X_coord < 101) {
				X_coord = X_coord + 20;
			}
			else {
				X_coord = 220 + X_coord - 101;
			}
			Fruit* fruit = new Fruit();
			fruit->SetPosition(Vector2(X_coord, Y_coord));
			AddNewObject(fruit);
		}



	}
}