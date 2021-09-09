#include "Spell.h"
#include "TextureManager.h"
#include "GameSimsRenderer.h"
#include "FruitWizardGame.h"
#include "../../Common/Maths.h"

#include "../../Common/Vector3.h"
#include "../../Common/Vector4.h"

using namespace NCL;
using namespace CSC3222;

Vector4 activeFrames[] = {
	Vector4(512,384, 32, 32),
	Vector4(512,384, 32, 32),
	Vector4(512,384, 32, 32),
	Vector4(384,416, 32, 32),
	Vector4(384,416, 32, 32),
	Vector4(384,416, 32, 32),
};

Vector4 explodeFrames[] = {
	Vector4(512,384, 32, 32),
	Vector4(384,416, 32, 32),
	Vector4(416,416, 32, 32),
	Vector4(448,416, 32, 32),
	Vector4(480,416, 32, 32),
	Vector4(512,416, 32, 32),	
};

Spell::Spell(Vector2 d) : SimObject()	{
	texture		= texManager->GetTexture("FruitWizard\\mini_fantasy_sprites_oga_ver.png");
	velocity	= d;
	direction = velocity;
	animFrameCount = 6;
	timeSpawned = 0.0;

}

Spell::~Spell()	{
}

void Spell::DrawObject(GameSimsRenderer &r) {
	Vector4	texData = explodeFrames[currentanimFrame];
	Vector2 texPos	= Vector2(texData.x, texData.y);
	Vector2 texSize = Vector2(texData.z, texData.w);
	r.DrawTextureArea((OGLTexture*)texture, texPos, texSize, position);
}

bool Spell::UpdateObject(float dt) {
	timeSpawned += dt;
	collider->SetPosition(position);
	if (timeSpawned + dt > 3.0) {
		return false;
	}
	else {
		animFrameData = explodeFrames[currentanimFrame];
	
			AddForce(direction*Vector2(700, 0));
			
		
	}
	
}