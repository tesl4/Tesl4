#pragma once
#include "Actor.h"
class TriangleActor : public CActor
{
public:
	TriangleActor();
	virtual ~TriangleActor();

	void Tick(float delta) override;
	void Render() override;
};

