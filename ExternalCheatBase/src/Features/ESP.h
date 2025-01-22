#ifndef ESP_H
#define ESP_H

#include "../pch.h"
#include "CheatFeature.h"
#include "../Render/Renderer.h"

class ESP : public CheatFeature {
public:
	ESP();

	void execute() override;

private:
	void UpdateEntities();
	void DrawEntities();
};

#endif
