#include "../pch.h"
#include "ESP.h"
#include "../SDK/CEntity.h"
#include "../SDK/LocalPlayer.h"
#include "../Misc/Util.h"
#include "../Config/ConfigInstance.h"

ESP::ESP() {

}

void DrawBoundingBox(Vector3 position, uintptr_t boneArray, float distance)
{
	// Read head position from the bone array
	Vector3 head = mem.RPM<Vector3>(boneArray + 6 * 32); 
	head.z += 20;

	Vector2 screenPos = gGame.WorldToScreen(position);
	Vector2 screenHead = gGame.WorldToScreen(head);


	if (screenHead.x <= 0 || screenHead.y <= 0 || screenPos.x <= 0 || screenPos.y <= 0)
		return;

	float boxHeight = std::abs(screenPos.y - screenHead.y);

	float boxWidth = boxHeight / 2.0f;

	Vector2 topLeft = { screenHead.x - boxWidth / 2.0f, screenHead.y };
	Vector2 bottomRight = { screenHead.x + boxWidth / 2.0f, screenPos.y };

	// Draw the bounding box
	g_Renderer.drawCommands.emplace_back(
		Renderer::DrawCommand::RECT,
		topLeft.x, topLeft.y,
		bottomRight.x, bottomRight.y,
		0, 0, // x3, y3 are unused for RECT
		IM_COL32(0, 255, 0, 255) // Green color
	);
}

void DrawFOV()
{
	float fovRadius = (ConfigInstances.Aimbot.fov / 90.0f) * (g_Globals.screenWidth / 2);

	if (fovRadius <= 0) {
		Loggus.log(Loggus.WARNING, "FOV Radius is invalid. Skipping draw.");
		return;
	}

	g_Renderer.drawCommands.emplace_back(
		Renderer::DrawCommand::CIRCLE,
		g_Globals.screenCenter.x, g_Globals.screenCenter.y,
		0, 0, 0, 0, // x2, y2, x3, y3 are unused for CIRCLE
		IM_COL32(255, 255, 255, 255), // White color
		fovRadius // Circle radius
	);
}

void DrawSkeleton(uintptr_t boneArray, float distance)
{
	Vector3 previous, current;
	Vector3 head = mem.RPM<Vector3>(boneArray + 6 * 32);
	Vector2 headPos = gGame.WorldToScreen(head);

	if (headPos.x > 0 && headPos.y > 0)
	{
		float jointSize = Util.getJointSize(6.5f, distance);
		g_Renderer.drawCommands.emplace_back(Renderer::DrawCommand::CIRCLE_FILLED, static_cast<int>(headPos.x), static_cast<int>(headPos.y), 0, 0, IM_COL32(255, 255, 255, 255), jointSize);
	}

	for (std::vector<int> currentGroup : Util.boneGroups.allGroups)
	{
		previous = { 0.f, 0.f, 0.f };

		for (int currentBone : currentGroup)
		{
			current = mem.RPM<Vector3>(boneArray + currentBone * 32);

			if (previous.IsZero())
			{
				previous = current;
				continue;
			}
			Vector2 currentScreenPos = gGame.WorldToScreen(current);
			Vector2 previousScreenPos = gGame.WorldToScreen(previous);

			if (currentScreenPos.x > 0 && currentScreenPos.y > 0 &&
				previousScreenPos.x > 0 && previousScreenPos.y > 0)
			{
				g_Renderer.drawCommands.emplace_back(
					Renderer::DrawCommand::LINE,
					previousScreenPos.x, previousScreenPos.y,
					currentScreenPos.x, currentScreenPos.y,
					0, 0, // x3, y3 are unused for LINE
					IM_COL32(0, 255, 0, 255), // Green color
					0, // Radius not applicable
					2.0f // Thickness
				);
			}

			previous = current;
		}
	}
}

void DrawPlayerName(const std::string& playerName, const Vector2& screenHead)
{
	ImGuiIO& io = ImGui::GetIO();
	if (io.Fonts->Fonts.empty() || !ImGui::GetFont()) {
		Loggus.log(Loggus.WARNING, "No valid font loaded. Skipping DrawPlayerName.");
		return;
	}

	ImFont* font = ImGui::GetFont();
	float fontSize = font->FontSize;

	if (fontSize <= 0) {
		Loggus.log(Loggus.WARNING, "Invalid font size detected. Setting default size.");
		fontSize = 14.0f; // Fallback size
	}

	if (playerName.empty()) return;
	const char* text = playerName.c_str();
	ImVec2 textSize = ImGui::CalcTextSize(text);
	float textX = screenHead.x - (textSize.x / 2.0f);
	float textY = screenHead.y - textSize.y - 8.0f;

	g_Renderer.drawCommands.emplace_back(
		Renderer::DrawCommand::TEXT,
		textX, textY,
		0, 0, 0, 0, // x2, y2, x3, y3 are unused for TEXT
		IM_COL32(255, 255, 255, 255), // White color
		0, 1.0f, // Radius and thickness are unused for TEXT
		playerName // The text to render
	);
}

void DrawHealthBar(float x, float topY, float bottomY, int health, float boxWidth) {

	float boxHeight = bottomY - topY;

	float healthPercent = static_cast<float>(health) / 100;

	float filledHeight = boxHeight * healthPercent;

	float barWidth = 3.0f;
	float barLeft = x + boxWidth / 2 + 5.0f;
	float barRight = barLeft + barWidth;
	float barBottom = bottomY;
	float barTop = barBottom - filledHeight;

	g_Renderer.drawCommands.emplace_back(Renderer::DrawCommand::RECT_FILLED,
		barLeft, topY, barRight, barBottom,
		IM_COL32(100, 100, 100, 255));

	// Filled portion
	g_Renderer.drawCommands.emplace_back(Renderer::DrawCommand::RECT_FILLED,
		barLeft, barTop, barRight, barBottom, IM_COL32(0, 255, 0, 255));

	// Border
	g_Renderer.drawCommands.emplace_back(Renderer::DrawCommand::RECT,
		barLeft, topY, barRight, barBottom,
		IM_COL32(255, 255, 255, 255));
}

void ESP::UpdateEntities() {
	gGame.PlayerList.clear();
	gLocalPlayer.GetPlayerPawn(gGame.GetClientDLLAddy());
	gLocalPlayer.GetLocalTeam();

	for (int i = 0; i < 64; i++)
	{
		auto entity = std::make_shared<CEntity>();
		entity->Controller.GetListEntry(gGame.GetEntityListAddress(), i);
		entity->Controller.GetController(i);

		if (entity->Controller.Address == 0)
			continue;

		entity->Controller.GetPlayerTeam();
		entity->Controller.GetPlayerName();

		if (strcmp(entity->Controller.PlayerName.c_str(), "DemoRecorder") == 0) {
			continue;
		}

		entity->Pawn.Address = entity->Controller.GetPawnAddress();
		entity->Pawn.GetListEntry(gGame.GetEntityListAddress());
		entity->Pawn.GetPlayerPawn();
		if (gLocalPlayer.playerPawn == entity->Pawn.playerPawn)
			continue;

		entity->Pawn.GetPlayerHealth();
		if (entity->Pawn.Health <= 0) {
			continue;
		}

		entity->Pawn.Address = entity->Controller.GetPawnAddress();
		if (entity->Pawn.Address == 0) {
			continue;
		}

		entity->SceneNode.address = entity->Pawn.GetSceneNode();

		entity->Pawn.GetOrigin();
		entity->SceneNode.GetBoneArray();
		
		gGame.PlayerList.push_back(entity);

	}
}

void ESP::DrawEntities()
{

	for (const auto& entity : gGame.GetPlayerList()) {
		if (!entity) continue;
		
		if (entity->Pawn.Health <= 0 || entity->Pawn.Health > 100 || entity->Controller.Team == gLocalPlayer.myTeam) continue;

		Vector2 screenPos = gGame.WorldToScreen(entity->Pawn.Position);
		if (!screenPos.x > 0 && !screenPos.y > 0) continue;
		Vector3 head = mem.RPM<Vector3>(entity->SceneNode.boneArray + 6 * 32);
		Vector2 headScreen = gGame.WorldToScreen(head);

		float distance = Util.getDistance(entity->Pawn.Position, gLocalPlayer.Position) / 100;
		float boxHeight = std::abs(screenPos.y - headScreen.y);
		float boxWidth = boxHeight / 2.0f;

		if(ConfigInstances.ESP.drawSkeleton)
			DrawSkeleton(entity->SceneNode.boneArray, distance);
		if(ConfigInstances.ESP.drawBoundingBox)
			DrawBoundingBox(entity->Pawn.Position,entity->SceneNode.boneArray, distance);
		if (ConfigInstances.ESP.drawPlayerName)
			DrawPlayerName(entity->Controller.PlayerName, headScreen);
		if(ConfigInstances.ESP.drawHealthBar)
			DrawHealthBar(headScreen.x, headScreen.y, screenPos.y, entity->Pawn.Health, boxWidth);
		if (ConfigInstances.Aimbot.showFov) {
			DrawFOV();
		}
	}
	RayTrace.DebugRenderTriangles();
}

void ESP::execute() {
	if (!enabled) return;

	UpdateEntities();
	DrawEntities();
}

