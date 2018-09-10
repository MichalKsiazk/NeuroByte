#pragma once
#include "entity.h"
#include "game_clock.h"
#include "collider_2d.h"

class Pipe : public Entity
{
public:
	Pipe(Transform* transform, ShaderProgram& shaderProgram, Renderer& renderer, Texture& texture, GameClock *clock);
	RectCollider2D* collider;
	void Update(Camera* camera);
	virtual ~Pipe();


protected:
	GameClock* game_clock;
};

