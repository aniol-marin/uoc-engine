#ifndef __DEFINES_H
#define __DEFINES_H

#include <string>

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

using DirectX::XMFLOAT3;
using DirectX::XMFLOAT4;
using DirectX::XMMATRIX;
using DirectX::XMVECTOR;

#define PATH_WORLD			".\\Data\\Models\\World\\"
#define PATH_TEXTURES		".\\Data\\Models\\Textures\\"

#define CHECKED_DELETE(x) if(x!=NULL) {delete x; x=NULL;}
#define CHECKED_RELEASE(x) if(x!=NULL) {x->Release(); x=NULL;}

#define LENGTH(a,b) sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z))

enum TCameraControllerType
{
	FPS_CAMERA_CONTROLLER = 0,
	SPHERICAL_CAMERA_CONTROLLER
};

void GetFilename(const char* path, std::string* filename);

#define DEG2RAD(x) x*DirectX::XM_PI/180.0f
#define RAD2DEG(x) x*180.0f/DirectX::XM_PI

float DistanceSqrXZ(const XMFLOAT3& PosA, const XMFLOAT3& PosB);
float CalculateYAW(const XMFLOAT3& VDir);
float DistanceSqr(const XMFLOAT3& Pos1, const XMFLOAT3& Pos2);

std::wstring str2wstr(const std::string& s);


#if __cplusplus > 202002
#include <stdfloat>
using f32 = std::float32_t;
#else
using f32 = long double;
#endif
constexpr f32 f32_0{ 0.0 };
constexpr f32 f32_1{ 1.0 };
constexpr f32 f32_2{ 2.0 };
constexpr float f_0{ 0.0 };
constexpr float f_1{ 1.0 };

constexpr float g_RollDefault{ f_0 };
constexpr float g_PitchDefault{ f_0 };
constexpr float g_YawDefault{ f_0 };

constexpr XMFLOAT3 g_Center{ XMFLOAT3(f32_0,f32_0,f32_0) };
constexpr XMFLOAT3 g_Front{ XMFLOAT3(f32_0,f32_0,f32_1) };
constexpr XMFLOAT3 g_Back{ XMFLOAT3(f32_0,f32_0,-f32_1) };
constexpr XMFLOAT3 g_Left{ XMFLOAT3(f32_1,f32_0,f32_0) };
constexpr XMFLOAT3 g_Right{ XMFLOAT3(-f32_1,f32_0,f32_0) };
constexpr XMFLOAT3 g_Up{ XMFLOAT3(f32_0,f32_1,f32_0) };
constexpr XMFLOAT3 g_Down{ XMFLOAT3(f32_0,-f32_1, f32_0) };

constexpr float g_FullCircleDeg{ 360.0f };
constexpr float g_HalfCircleDeg{ g_FullCircleDeg / 2.0f };
constexpr float g_QuarterCircleDeg{ g_FullCircleDeg / 4.0f };
constexpr XMFLOAT3 g_UnitaryXMF3{ XMFLOAT3{f32_1, f32_1, f32_1} };
constexpr XMFLOAT4 g_UnitaryXMF4{ XMFLOAT4{f32_1, f32_1, f32_1, f32_1} };

constexpr XMFLOAT4 g_Black{ XMFLOAT4{f32_0, f32_0, f32_0, f32_1} };
constexpr XMFLOAT4 g_White{ XMFLOAT4{f32_1, f32_1, f32_1, f32_1} };
constexpr XMFLOAT4 g_Red{ XMFLOAT4{f32_1, f32_0, f32_0, f32_1} };
constexpr XMFLOAT4 g_Green{ XMFLOAT4{f32_0, f32_1, f32_0, f32_1} };
constexpr XMFLOAT4 g_Blue{ XMFLOAT4{f32_0, f32_0, f32_1, f32_1} };

constexpr int vertexToLines(int vertex) { return vertex / 2; }
constexpr float deg2Rad(float x) { return DEG2RAD(x); };
constexpr XMFLOAT3 combine(XMFLOAT3 a, XMFLOAT3 b) {
	return XMFLOAT3(
		a.x + b.x,
		a.y + b.y,
		a.z + b.z);
}
constexpr XMFLOAT3 combine(XMFLOAT3 a, XMFLOAT3 b, XMFLOAT3 c) {
	return XMFLOAT3(
		a.x + b.x + c.x,
		a.y + b.y + c.y,
		a.z + b.z + c.z);
}
constexpr XMFLOAT3 resize(float s, XMFLOAT3 f) {
	return XMFLOAT3(
		f.x * s,
		f.y * s,
		f.z * s);
}
constexpr XMFLOAT4 resize(float s, XMFLOAT4 f) {
	return XMFLOAT4(
		f.x * s,
		f.y * s,
		f.z * s,
		f.w * s);
}
constexpr XMFLOAT3 sum(XMFLOAT3 f, XMFLOAT3 s) {
	return XMFLOAT3(
		f.x + s.x,
		f.y + s.y,
		f.z + s.z);
}
constexpr XMFLOAT3 sum(XMFLOAT3 f, XMVECTOR s) {
	return XMFLOAT3(
		f.x + s.vector4_f32[0],
		f.y + s.vector4_f32[1],
		f.z + s.vector4_f32[2]);
}
XMVECTOR eulerToDirection(float roll, float pitch, float yaw);
#endif
