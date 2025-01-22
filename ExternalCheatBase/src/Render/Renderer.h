#include "../pch.h"
#ifndef RENDERER_H
#define RENDERER_H

#include "OverlayCord.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include <d3d11.h>
#include <dxgi.h>

class Renderer {
public:
	
	struct DrawCommand {
		enum CommandType { RECT, CIRCLE, LINE, TEXT, RECT_FILLED, CIRCLE_FILLED, TRIANGLE };
		CommandType type;

		float x, y, x2, y2, x3, y3, radius, thickness;
		std::string text;
		ImU32 color;

		DrawCommand(CommandType type, float x, float y, float x2 = 0, float y2 = 0, float x3 = 0, float y3 = 0,
			ImU32 color = 0, float radius = 0, float thickness = 1.0f, const std::string& text = "")
			: type(type), x(x), y(y), x2(x2), y2(y2), x3(x3), y3(y3), radius(radius), thickness(thickness), text(text), color(color) {}
	};

	Renderer();
	~Renderer();

	bool Initialize(HWND targetWindow, const std::wstring& processName);
	void RenderFrame(int overlayWidth, int overlayHeight);
	void ClearOverlayBuffer(int overlayWidth, int overlayHeight);
	void Cleanup();

	void ToggleMenu();

	bool isMenuVisible() const { return showMenu; }

	void DrawCircleFilled(float x, float y, float radius, ImU32 color, int segments = 0);
	void DrawRect(float x, float y, float width, float height, ImU32 color);
	void DrawTextA(float x, float y, const std::string& text, ImU32 color);
	void DrawLine(float x1, float y1, float x2, float y2, ImU32 color, float thickness = 1.0f);
	void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, ImU32 color);

	std::vector<DrawCommand> drawCommands;
private:
	bool InitD3DDevice(HWND hwnd);
	void UpdateImGuiInput(int overlayWidth, int overlayHeight);

	bool SetupOverlayCord(const std::wstring& processName);
	void SendBufferToOverlay(int overlayWidth, int overlayHeight);

	ID3D11Device* g_pd3dDevice = nullptr;
	ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
	IDXGISwapChain* g_pSwapChain = nullptr;
	ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;

	OverlayCord::Communication::ConnectedProcessInfo overlayProcessInfo;

	bool showMenu = false;
};


#endif