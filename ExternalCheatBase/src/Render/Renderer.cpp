#include "../pch.h"
#include "Renderer.h"
#include "../Logging/Logger.h"
#include "../Features/CheatManager.h"
#include "../Config/ConfigInstance.h"

Renderer::Renderer() {}

Renderer::~Renderer() {
	Cleanup();
}

bool Renderer::Initialize(HWND targetWindow, const std::wstring& processName) {
	// Initialize Direct3D Device
	if (!InitD3DDevice(targetWindow)) {
		Loggus.log(Loggus.CRITICAL, "Failed to init D3D device.");
		return false;
	}

	// Initialize ImGui
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

	ImGui_ImplWin32_Init(targetWindow);
	ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
	io.Fonts->AddFontDefault();
	ImGui::StyleColorsDark();

	// Setup OverlayCord
	if (!SetupOverlayCord(processName)) {
		Loggus.log(Loggus.CRITICAL, "Failed to connect to discord overlay.");
		return false;
	}

	return true;
}

bool Renderer::SetupOverlayCord(const std::wstring& processName) {
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE) return false;

	PROCESSENTRY32W pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32W);

	DWORD processId = 0;

	if (Process32FirstW(hSnapshot, &pe32)) {
		do {
			if (processName == pe32.szExeFile) {
				processId = pe32.th32ProcessID;
				break;
			}
		} while (Process32NextW(hSnapshot, &pe32));
	}
	CloseHandle(hSnapshot);

	if (!processId) {
		Loggus.log(Loggus.CRITICAL, "Process not found.");
		return false;
	}

	overlayProcessInfo = {};
	overlayProcessInfo.ProcessId = processId;

	return OverlayCord::Communication::ConnectToProcess(overlayProcessInfo);
}

void Renderer::RenderFrame(int overlayWidth, int overlayHeight) {
	UpdateImGuiInput(overlayWidth, overlayHeight);

	g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);

	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f }; // Transparent
	g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clearColor);

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	if (showMenu) {
		ImGui::Begin("Menu");
		ImGui::Text("Example Menu");

		if (ImGui::CollapsingHeader("ESP Settings")) {
			if (ImGui::Checkbox("Enable ESP", &ConfigInstances.ESP.enabled)) {
				cheatManager.setFeatureState(0, ConfigInstances.ESP.enabled);
			}
			ImGui::Checkbox("Draw Skeleton", &ConfigInstances.ESP.drawSkeleton);
			ImGui::Checkbox("Draw Bounding Box", &ConfigInstances.ESP.drawBoundingBox);
			ImGui::Checkbox("Draw Player Name", &ConfigInstances.ESP.drawPlayerName);
			ImGui::Checkbox("Draw Health Bar", &ConfigInstances.ESP.drawHealthBar);
		}

		if (ImGui::CollapsingHeader("Aimbot Settings")) {
			if (ImGui::Checkbox("Enable Aimbot", &ConfigInstances.Aimbot.enabled)) {
				cheatManager.setFeatureState(2, ConfigInstances.Aimbot.enabled);
				cheatManager.setFeatureState(1, !ConfigInstances.Aimbot.enabled);
			}
			ImGui::Checkbox("Lock to Target", &ConfigInstances.Aimbot.lockToTarget);
			ImGui::Checkbox("Recoil Control System (RCS)", &ConfigInstances.Aimbot.rcs);
			ImGui::Checkbox("Visible Check", &ConfigInstances.Aimbot.visibleCheck);
			ImGui::Checkbox("Show FOV Circle", &ConfigInstances.Aimbot.showFov);
			ImGui::SliderFloat("FOV", &ConfigInstances.Aimbot.fov, 0.1f, 30.f, "%.1f");
			ImGui::SliderFloat("Smoothing", &ConfigInstances.Aimbot.smoothing, 0.1f, 10.f, "%.1f");
			ImGui::SliderFloat("Noise Factor", &ConfigInstances.Aimbot.noiseFactor, 0.0f, 1.0f, "%.2f");
			ImGui::SliderFloat("RCS X", &ConfigInstances.Aimbot.rcsXMulti, 1, 100);
			ImGui::SliderFloat("RCS Y", &ConfigInstances.Aimbot.rcsYMulti, 1, 100);
			ImGui::SliderInt("Bezier Steps", &ConfigInstances.Aimbot.bezierSteps, 1, 50);

			if (ImGui::BeginCombo("Target Bone", ConfigInstances.Aimbot.bones[ConfigInstances.Aimbot.boneSelect].c_str())) {
				for (size_t i = 0; i < ConfigInstances.Aimbot.bones.size(); ++i) {
					bool isSelected = (ConfigInstances.Aimbot.boneSelect == i);
					if (ImGui::Selectable(ConfigInstances.Aimbot.bones[i].c_str(), isSelected)) {
						ConfigInstances.Aimbot.boneSelect = static_cast<int>(i);
					}
					if (isSelected) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
		}

		ImGui::End();
	}

	g_Renderer.drawCommands.emplace_back(
		Renderer::DrawCommand::LINE,
		100, 100, // Start (x, y)
		400, 400, // End (x, y)
		IM_COL32(255, 0, 0, 255), // Red color
		5.0f // Thickness
	);

	for (const auto& cmd : drawCommands) {
		switch (cmd.type) {
		case DrawCommand::RECT_FILLED:
			ImGui::GetBackgroundDrawList()->AddRectFilled(
				ImVec2(cmd.x, cmd.y),
				ImVec2(cmd.x2, cmd.y2),
				cmd.color
			);
			break;
		case DrawCommand::RECT:
			ImGui::GetBackgroundDrawList()->AddRect(ImVec2(cmd.x, cmd.y), ImVec2(cmd.x2, cmd.y2), cmd.color);
			break;
		case DrawCommand::CIRCLE:
			ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(cmd.x, cmd.y), cmd.radius, cmd.color);
			break;
		case DrawCommand::CIRCLE_FILLED:
			DrawCircleFilled(cmd.x, cmd.y, cmd.radius, cmd.color);
			//ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(cmd.x, cmd.y), cmd.radius, cmd.color);
			break;
		case DrawCommand::LINE:
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(cmd.x, cmd.y), ImVec2(cmd.x2, cmd.y2), cmd.color, cmd.thickness);
			break;
		case DrawCommand::TEXT:
			ImGui::GetBackgroundDrawList()->AddText(ImVec2(cmd.x, cmd.y), cmd.color, cmd.text.c_str());
			break;
		case DrawCommand::TRIANGLE:
			ImGui::GetBackgroundDrawList()->AddTriangle(
				ImVec2(cmd.x, cmd.y),
				ImVec2(cmd.x2, cmd.y2),
				ImVec2(cmd.x3, cmd.y3),
				cmd.color
			);
			break;
		}
	}

	drawCommands.clear();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	g_pSwapChain->Present(1, 0);

	SendBufferToOverlay(overlayWidth, overlayHeight);
}

void Renderer::SendBufferToOverlay(int overlayWidth, int overlayHeight) {
	ID3D11Texture2D* backBuffer = nullptr;
	g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

	D3D11_TEXTURE2D_DESC desc;
	backBuffer->GetDesc(&desc);
	desc.Usage = D3D11_USAGE_STAGING;
	desc.BindFlags = 0;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

	ID3D11Texture2D* stagingTexture = nullptr;
	g_pd3dDevice->CreateTexture2D(&desc, nullptr, &stagingTexture);

	g_pd3dDeviceContext->CopyResource(stagingTexture, backBuffer);

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	g_pd3dDeviceContext->Map(stagingTexture, 0, D3D11_MAP_READ, 0, &mappedResource);

	UINT bufferSize = overlayHeight * mappedResource.RowPitch;
	memcpy(overlayProcessInfo.MappedAddress->Buffer, mappedResource.pData, bufferSize);
	overlayProcessInfo.MappedAddress->FrameCount++;

	g_pd3dDeviceContext->Unmap(stagingTexture, 0);
	stagingTexture->Release();
	backBuffer->Release();
}

void Renderer::Cleanup() {

	int overlayWidth = GetSystemMetrics(SM_CXSCREEN);
	int overlayHeight = GetSystemMetrics(SM_CYSCREEN);

	ClearOverlayBuffer(overlayWidth, overlayHeight);

	if (overlayProcessInfo.MappedAddress) {
		OverlayCord::Communication::DisconnectFromProcess(overlayProcessInfo);
	}
	if (g_mainRenderTargetView) g_mainRenderTargetView->Release();
	if (g_pSwapChain) g_pSwapChain->Release();
	if (g_pd3dDeviceContext) g_pd3dDeviceContext->Release();
	if (g_pd3dDevice) g_pd3dDevice->Release();
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}


void Renderer::ToggleMenu() {
	showMenu = !showMenu;
}

void Renderer::ClearOverlayBuffer(int overlayWidth, int overlayHeight) {
	if (!overlayProcessInfo.MappedAddress) return;

	OverlayCord::Drawing::Frame blankFrame = OverlayCord::Drawing::CreateFrame(overlayWidth, overlayHeight);
	OverlayCord::Drawing::CleanFrame(blankFrame);

	OverlayCord::Communication::SendFrame(overlayProcessInfo, blankFrame.Width, blankFrame.Height, blankFrame.Buffer, blankFrame.Size);

	free(blankFrame.Buffer);
}

bool Renderer::InitD3DDevice(HWND hwnd) {
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferCount = 1;
	sd.BufferDesc.Width = GetSystemMetrics(SM_CXSCREEN);
	sd.BufferDesc.Height = GetSystemMetrics(SM_CYSCREEN);
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&g_pSwapChain,
		&g_pd3dDevice,
		nullptr,
		&g_pd3dDeviceContext
	);

	if (FAILED(hr)) {
		return false;
	}

	ID3D11Texture2D* pBackBuffer;
	g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
	g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
	pBackBuffer->Release();

	return true;
}

void Renderer::UpdateImGuiInput(int overlayWidth, int overlayHeight) {
	ImGuiIO& io = ImGui::GetIO();
	POINT mousePos;
	GetCursorPos(&mousePos);

	float screenWidth = static_cast<float>(GetSystemMetrics(SM_CXSCREEN));
	float screenHeight = static_cast<float>(GetSystemMetrics(SM_CYSCREEN));

	io.MousePos = ImVec2(
		(mousePos.x / screenWidth) * overlayWidth,
		(mousePos.y / screenHeight) * overlayHeight
	);

	io.AddMouseButtonEvent(0, (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0);
	io.AddMouseButtonEvent(1, (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0);
}

void Renderer::DrawCircleFilled(float x, float y, float radius, ImU32 color, int segments) {
	ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(x, y), radius, color, segments);
}

void Renderer::DrawRect(float x, float y, float width, float height, ImU32 color) {
	//Loggus.log(Loggus.INFO, "Drawing Rect: (" + std::to_string(x) + ", " + std::to_string(y) + ")");
	ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + width, y + height), color);
}

void Renderer::DrawTextA(float x, float y, const std::string& text, ImU32 color) {
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(x, y), color, text.c_str());
}

void Renderer::DrawLine(float x1, float y1, float x2, float y2, ImU32 color, float thickness) {
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), color, thickness);
}

void Renderer::DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, ImU32 color) {
	g_Renderer.drawCommands.emplace_back(
		Renderer::DrawCommand::TRIANGLE,
		x1, y1, // First point
		x2, y2, // Second point
		x3, y3, // Third point
		IM_COL32(0, 255, 0, 128) // Green with transparency
	);
}

