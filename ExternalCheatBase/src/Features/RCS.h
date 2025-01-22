#ifndef RCS_H
#define RCS_H

#include "../pch.h"
#include "CheatFeature.h"
#include "../Render/Renderer.h"

class RCS : public CheatFeature {
public:
	RCS();
	void execute() override;
private:
	void RunRCS();
};

#endif
