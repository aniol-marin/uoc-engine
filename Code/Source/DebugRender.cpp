#include "DebugRender.h"
#include "UOCEngine.h"
#include "VertexTypes.h"
#include "RenderableVertexs.h"
#include "defines.h"
#include <assert.h>
#include "EffectManager.h"
#include <vector>
#include <functional>

CDebugRender::CDebugRender(ID3D11Device* Device) :
	//TO DO : Establecer la variable m_Effect pidi�ndole el Effect a la clase CEffectManager que se encuentra en el motor, pediremos el Efecto que tiene por tipo de v�rtice UOC_POSITION_COLOR_VERTEX::GetVertexType()
	m_Effect{ CUOCEngine::GetEngine()->GetEffectManager()->GetEffect(UOC_POSITION_COLOR_VERTEX::GetVertexType()) },
	m_GridRenderableVertexs{},
	m_SphereRenderableVertexs{}
{
	//AXIS
	UOC_POSITION_COLOR_VERTEX l_AxisVtxs[6] =
	{
		{XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
		{XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},

		{XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},
		{XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},

		{XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)},
		{XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)}
	};

	m_AxisRenderableVertexs = new CLinesListRenderableVertexs<UOC_POSITION_COLOR_VERTEX>(Device, l_AxisVtxs, 6, 3);

	//CUBE
	constexpr float l_SizeCube = 1.0f;
	constexpr float l_OffsetCube = l_SizeCube / 2.0f;
	constexpr XMFLOAT4 l_Color = g_White;
	std::vector<UOC_POSITION_COLOR_VERTEX> l_CubeVtxs{
		//TO DO : Construye todos los v�rtices de la base del cubo para que el tama�o del cubo sea l_SizeCube, debemos crear dos v�rtices por linea, por tanto 8 v�rtices
		{resize(l_OffsetCube, combine(g_Down, g_Right, g_Front)),l_Color},
		{resize(l_OffsetCube, combine(g_Down, g_Right, g_Back)),l_Color},
		{resize(l_OffsetCube, combine(g_Down, g_Left, g_Front)),l_Color},
		{resize(l_OffsetCube, combine(g_Down, g_Left, g_Back)),l_Color},
		{resize(l_OffsetCube, combine(g_Down, g_Right, g_Front)),l_Color},
		{resize(l_OffsetCube, combine(g_Down, g_Left, g_Front)),l_Color},
		{resize(l_OffsetCube, combine(g_Down, g_Right, g_Back)),l_Color},
		{resize(l_OffsetCube, combine(g_Down, g_Left, g_Back)),l_Color},

		//TO DO : Construye todos los v�rtices de la tapa del cubo para que el tama�o del cubo sea l_SizeCube, debemos crear dos v�rtices por linea, por tanto 8 v�rtices
		{resize(l_OffsetCube, combine(g_Up, g_Right, g_Front)),l_Color},
		{resize(l_OffsetCube, combine(g_Up, g_Right, g_Back)),l_Color},
		{resize(l_OffsetCube, combine(g_Up, g_Left, g_Front)),l_Color},
		{resize(l_OffsetCube, combine(g_Up, g_Left, g_Back)),l_Color},
		{resize(l_OffsetCube, combine(g_Up, g_Right, g_Front)),l_Color},
		{resize(l_OffsetCube, combine(g_Up, g_Left, g_Front)),l_Color},
		{resize(l_OffsetCube, combine(g_Up, g_Right, g_Back)),l_Color},
		{resize(l_OffsetCube, combine(g_Up, g_Left, g_Back)),l_Color},

		//TO DO : Construye todos los v�rtices de las lineas laterales del cubo para que el tama�o del cubo sea l_SizeCube, debemos crear dos v�rtices por linea, por tanto 8 v�rtices
		{resize(l_OffsetCube, combine(g_Up,	g_Right,g_Back)),l_Color},
		{resize(l_OffsetCube, combine(g_Down,	g_Right,g_Back)),l_Color},
		{resize(l_OffsetCube, combine(g_Up,	g_Left,	g_Back)),l_Color},
		{resize(l_OffsetCube, combine(g_Down,	g_Left,	g_Back)),l_Color},
		{resize(l_OffsetCube, combine(g_Up,	g_Right,g_Front)),l_Color},
		{resize(l_OffsetCube, combine(g_Down,	g_Right,g_Front)),l_Color},
		{resize(l_OffsetCube, combine(g_Up,	g_Left,	g_Front)),l_Color},
		{resize(l_OffsetCube, combine(g_Down,	g_Left,	g_Front)),l_Color},
	};
	assert(!(l_CubeVtxs.size() % 2));

	m_CubeRenderableVertexs = new CLinesListRenderableVertexs<UOC_POSITION_COLOR_VERTEX>(
		Device,
		l_CubeVtxs.data(),
		l_CubeVtxs.size(),
		vertexToLines(l_CubeVtxs.size()));

	//GRID
	const std::function<float(int, float, int)> lf_LocalGridPos = [](int position, float size, int count) { return (position - (double)count / 2.0) * size/(double)count; };
	constexpr float l_Size = 10.0f;
	constexpr int l_Grid = 10;
	//TO DO : Construye todos los v�rtices de la grid en el eje X, cada linea estar� formada por dos v�rtices y el tama�o de la grid ser� l_Size y el n�mero de secciones de la grid ser� l_Grid
	std::vector<UOC_POSITION_COLOR_VERTEX> l_GridVtxs((l_Grid + 1) * 2 * 2);

	//TO DO : Construye la instancia m_GridRenderableVertexs de tipo CLinesListRenderableVertexs<UOC_POSITION_COLOR_VERTEX> pas�ndole los v�rtices del cubo l_GridVtxs, el n�mero de v�rtices y el n�mero de primitivas (n�mero de lineas)
	for (int i = 0; i <= l_Grid; ++i) {
		float l_Distance = lf_LocalGridPos(i, l_Size, l_Grid);

		l_GridVtxs.push_back({ combine(resize(l_Size / 2.0f, g_Left), resize(l_Distance, g_Front)), l_Color });
		l_GridVtxs.push_back({ combine(resize(l_Size / 2.0f, g_Right), resize(l_Distance, g_Front)), l_Color });
	}

	//TO DO : Construye todos los v�rtices de la grid en el eje Z, cada linea estar� formada por dos v�rtices y el tama�o de la grid ser� l_Size y el n�mero de secciones de la grid ser� l_Grid
	for (int i = 0; i <= l_Grid; ++i) {
		float l_Distance = lf_LocalGridPos(i, l_Size, l_Grid);

		l_GridVtxs.push_back({ combine(resize(l_Distance,g_Right), resize(l_Size / 2.0f,g_Front)), l_Color });
		l_GridVtxs.push_back({ combine(resize(l_Distance,g_Right),resize(l_Size / 2.0f,g_Back)), l_Color });
	}

	m_GridRenderableVertexs = new CLinesListRenderableVertexs<UOC_POSITION_COLOR_VERTEX>(
		Device,
		l_GridVtxs.data(),
		l_GridVtxs.size(),
		vertexToLines(l_GridVtxs.size()));

	//SPHERE
	const std::function<XMFLOAT3(int, int, float, int)> localSpherePos = [](int hPos, int vPos, float size, int count) {
		float l_HorizontalSection = g_FullCircleDeg / (float)count;
		float l_VerticalSection = g_HalfCircleDeg / (float)count;

		XMFLOAT3 vertex;
		DirectX::XMStoreFloat3(&vertex, size * DirectX::XMVector3Normalize(eulerToDirection(
			f_0,
			deg2Rad(vPos * l_VerticalSection - g_QuarterCircleDeg),
			deg2Rad(hPos * l_HorizontalSection))));

		return vertex;
	};
	const int l_Aristas = 10;
	const float l_SizeSphere = f_1;
	std::vector<UOC_POSITION_COLOR_VERTEX> l_SphereVtxs(4 * l_Aristas * l_Aristas);

	//TO DO : Construye todos los v�rtices de la esfera, para ello crearemos c�rculos sobre el plano XZ desplazados en el eje Y seg�n el n�mero de Aristas, recordar que al pintarse con lineas esos c�rculos debemos crear dos v�rtices por l�nea
	for (int y = 0; y < l_Aristas; ++y) {
		for (int x = 0; x < l_Aristas; ++x) {
			l_SphereVtxs.push_back({ localSpherePos(x, y, l_SizeSphere, l_Aristas), l_Color });
			l_SphereVtxs.push_back({ localSpherePos(x + 1, y, l_SizeSphere, l_Aristas), l_Color });
		}
	}
	
	//TO DO : Construye todos los v�rtices de la esfera, para ello crearemos c�rculos sobre el plano XY desplazados en el eje Z seg�n el n�mero de Aristas, recordar que al pintarse con lineas esos c�rculos debemos crear dos v�rtices por l�nea
	for (int x = 0; x < l_Aristas; ++x) {
		for (int y = 0; y < l_Aristas; ++y) {
			l_SphereVtxs.push_back({ localSpherePos(x, y, l_SizeSphere, l_Aristas), l_Color });
			l_SphereVtxs.push_back({ localSpherePos(x, y + 1, l_SizeSphere, l_Aristas), l_Color });
		}
	}

	//TO DO : Construye la instancia m_SphereRenderableVertexs de tipo CLinesListRenderableVertexs<UOC_POSITION_COLOR_VERTEX> pas�ndole los v�rtices de la esfera l_SphereVtxs, el n�mero de v�rtices y el n�mero de primitivas (n�mero de lineas)
	m_SphereRenderableVertexs = new CLinesListRenderableVertexs<UOC_POSITION_COLOR_VERTEX>(
		Device,
		l_SphereVtxs.data(),
		l_SphereVtxs.size(),
		vertexToLines(l_SphereVtxs.size()));
}

CDebugRender::~CDebugRender()
{
	//TO DO : Destruir la variable miembro m_AxisRenderableVertexs utilizando la macro CHECKED_DELETE
	CHECKED_DELETE(m_AxisRenderableVertexs);
	//TO DO : Destruir la variable miembro m_GridRenderableVertexs utilizando la macro CHECKED_DELETE
	CHECKED_DELETE(m_GridRenderableVertexs);
	//TO DO : Destruir la variable miembro m_CubeRenderableVertexs utilizando la macro CHECKED_DELETE
	CHECKED_DELETE(m_CubeRenderableVertexs);
	//TO DO : Destruir la variable miembro m_SphereRenderableVertexs utilizando la macro CHECKED_DELETE
	CHECKED_DELETE(m_SphereRenderableVertexs);
}


void CDebugRender::DrawAxis(ID3D11DeviceContext* DeviceContext, float Size)
{
	CEffectManager* l_EffectManager = CUOCEngine::GetEngine()->GetEffectManager();
	auto& l_ConstantBuffer = l_EffectManager->m_ObjectConstantBufferParameters;

	//TO DO : Establecer el color blanco (XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)) en la variable miembro m_BaseColor que se encuentra en la variable miembro est�tica m_ObjectConstantBufferParameters de la clase CEffectManager
	l_ConstantBuffer.m_BaseColor = g_White;
	//TO DO : Establecer el tama�o seg�n el Size en la variable miembro m_DebugRenderScale que se encuentra en la variable miembro est�tica m_ObjectConstantBufferParameters de la clase CEffectManager
	l_ConstantBuffer.m_DebugRenderScale = resize(Size, g_UnitaryXMF4);
	//TO DO : Llamar al m�todo SetObjectConstantBuffer para establecer las constantes del objeto en el shader que se encuentra en el EffectManager del motor
	l_EffectManager->SetObjectConstantBuffer(DeviceContext);
	//TO DO : Pintar los ejes utilizando el m�todo Draw de la instancia m_AxisRenderableVertexs utilizando el CEffect m_Effect
	m_AxisRenderableVertexs->Draw(DeviceContext, m_Effect);
}

void CDebugRender::DrawGrid(ID3D11DeviceContext* DeviceContext, float Size, XMFLOAT4 Color)
{
	CEffectManager* l_EffectManager = CUOCEngine::GetEngine()->GetEffectManager();
	auto& l_ConstantBuffer = l_EffectManager->m_ObjectConstantBufferParameters;

	//TO DO : Establecer el color en la variable miembro m_BaseColor que se encuentra en la variable miembro est�tica m_ObjectConstantBufferParameters de la clase CEffectManager
	l_ConstantBuffer.m_BaseColor = Color;
	//TO DO : Establecer el tama�o seg�n el Size en la variable miembro m_DebugRenderScale que se encuentra en la variable miembro est�tica m_ObjectConstantBufferParameters de la clase CEffectManager
	l_ConstantBuffer.m_DebugRenderScale = resize(Size, g_UnitaryXMF4);
	//TO DO : Llamar al m�todo SetObjectConstantBuffer para establecer las constantes del objeto en el shader que se encuentra en el EffectManager del motor
	l_EffectManager->SetObjectConstantBuffer(DeviceContext);
	//TO DO : Pintar la grid utilizando el m�todo Draw de la instancia m_GridRenderableVertexs utilizando el CEffect m_Effect
	m_GridRenderableVertexs->Draw(DeviceContext, m_Effect);
}

void CDebugRender::DrawCube(ID3D11DeviceContext* DeviceContext, float Size, XMFLOAT4 Color)
{
	CEffectManager* l_EffectManager = CUOCEngine::GetEngine()->GetEffectManager();
	auto& l_ConstantBuffer = l_EffectManager->m_ObjectConstantBufferParameters;

	//TO DO : Establecer el color en la variable miembro m_BaseColor que se encuentra en la variable miembro est�tica m_ObjectConstantBufferParameters de la clase CEffectManager
	l_ConstantBuffer.m_BaseColor = Color;
	//TO DO : Establecer el tama�o seg�n el Size en la variable miembro m_DebugRenderScale que se encuentra en la variable miembro est�tica m_ObjectConstantBufferParameters de la clase CEffectManager
	l_ConstantBuffer.m_DebugRenderScale = resize(Size, g_UnitaryXMF4);
	//TO DO : Llamar al m�todo SetObjectConstantBuffer para establecer las constantes del objeto en el shader que se encuentra en el EffectManager del motor
	l_EffectManager->SetObjectConstantBuffer(DeviceContext);
	//TO DO : Pintar el cubo utilizando el m�todo Draw de la instancia m_CubeRenderableVertexs utilizando el CEffect m_Effect
	m_CubeRenderableVertexs->Draw(DeviceContext, m_Effect);
}

void CDebugRender::DrawSphere(ID3D11DeviceContext* DeviceContext, float Radius, XMFLOAT4 Color)
{
	CEffectManager* l_EffectManager = CUOCEngine::GetEngine()->GetEffectManager();
	auto& l_ConstantBuffer = l_EffectManager->m_ObjectConstantBufferParameters;

	//TO DO : Establecer el color en la variable miembro m_BaseColor que se encuentra en la variable miembro est�tica m_ObjectConstantBufferParameters de la clase CEffectManager
	l_ConstantBuffer.m_BaseColor = Color;
	//TO DO : Establecer el tama�o seg�n el Radius en la variable miembro m_DebugRenderScale que se encuentra en la variable miembro est�tica m_ObjectConstantBufferParameters de la clase CEffectManager
	l_ConstantBuffer.m_DebugRenderScale = resize(Radius, g_UnitaryXMF4);
	//TO DO : Llamar al m�todo SetObjectConstantBuffer para establecer las constantes del objeto en el shader que se encuentra en el EffectManager del motor
	l_EffectManager->SetObjectConstantBuffer(DeviceContext);
	//TO DO : Pintar la esfera utilizando el m�todo Draw de la instancia m_SphereRenderableVertexs utilizando el CEffect m_Effect
	m_SphereRenderableVertexs->Draw(DeviceContext, m_Effect);
}
