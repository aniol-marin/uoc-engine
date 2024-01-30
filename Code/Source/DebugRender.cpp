#include "DebugRender.h"
#include "UOCEngine.h"
#include "VertexTypes.h"
#include "RenderableVertexs.h"
#include "defines.h"
#include <assert.h>
#include "EffectManager.h"

CDebugRender::CDebugRender(ID3D11Device *Device)
{
	//TO DO : Establecer la variable m_Effect pidi�ndole el Effect a la clase CEffectManager que se encuentra en el motor, pediremos el Efecto que tiene por tipo de v�rtice UOC_POSITION_COLOR_VERTEX::GetVertexType()
	//AXIS
	UOC_POSITION_COLOR_VERTEX l_AxisVtxs[6]=
	{
		{XMFLOAT3( 0.0f, 0.0f, 0.0f ), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
		{XMFLOAT3( 1.0f, 0.0f, 0.0f ), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
			
		{XMFLOAT3( 0.0f, 0.0f, 0.0f ), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},
		{XMFLOAT3( 0.0f, 1.0f, 0.0f ), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},

		{XMFLOAT3( 0.0f, 0.0f, 0.0f ), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)},
		{XMFLOAT3( 0.0f, 0.0f, 1.0f ), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)}
	};
	
	m_AxisRenderableVertexs=new CLinesListRenderableVertexs<UOC_POSITION_COLOR_VERTEX>(Device, l_AxisVtxs, 6, 3);
	
	//CUBE
	const float l_SizeCube=1.0f;
	UOC_POSITION_COLOR_VERTEX l_CubeVtxs[] =
	{
		//TO DO : Construye todos los v�rtices de la base del cubo para que el tama�o del cubo sea l_SizeCube, debemos crear dos v�rtices por linea, por tanto 8 v�rtices
		//TO DO : Construye todos los v�rtices de la tapa del cubo para que el tama�o del cubo sea l_SizeCube, debemos crear dos v�rtices por linea, por tanto 8 v�rtices
		//TO DO : Construye todos los v�rtices de las lineas laterales del cubo para que el tama�o del cubo sea l_SizeCube, debemos crear dos v�rtices por linea, por tanto 8 v�rtices
	};

	//TO DO : Construye la instancia m_CubeRenderableVertexs de tipo CLinesListRenderableVertexs<UOC_POSITION_COLOR_VERTEX> pas�ndole los v�rtices del cubo l_CubeVtxs, el n�mero de v�rtices y el n�mero de primitivas (n�mero de lineas)

	//GRID
	float l_Size=10.0f;
	const int l_Grid=10;
	UOC_POSITION_COLOR_VERTEX l_GridVtxs[(l_Grid+1)*2*2];
	//TO DO : Construye todos los v�rtices de la grid en el eje X, cada linea estar� formada por dos v�rtices y el tama�o de la grid ser� l_Size y el n�mero de secciones de la grid ser� l_Grid
	//TO DO : Construye todos los v�rtices de la grid en el eje Z, cada linea estar� formada por dos v�rtices y el tama�o de la grid ser� l_Size y el n�mero de secciones de la grid ser� l_Grid
	//TO DO : Construye la instancia m_GridRenderableVertexs de tipo CLinesListRenderableVertexs<UOC_POSITION_COLOR_VERTEX> pas�ndole los v�rtices del cubo l_GridVtxs, el n�mero de v�rtices y el n�mero de primitivas (n�mero de lineas)
	
	//SPHERE
	const int l_Aristas=10;
	UOC_POSITION_COLOR_VERTEX l_SphereVtxs[4*l_Aristas*l_Aristas];
	//TO DO : Construye todos los v�rtices de la esfera, para ello crearemos c�rculos sobre el plano XZ desplazados en el eje Y seg�n el n�mero de Aristas, recordar que al pintarse con lineas esos c�rculos debemos crear dos v�rtices por l�nea
	//TO DO : Construye todos los v�rtices de la esfera, para ello crearemos c�rculos sobre el plano XY desplazados en el eje Z seg�n el n�mero de Aristas, recordar que al pintarse con lineas esos c�rculos debemos crear dos v�rtices por l�nea
	//TO DO : Construye la instancia m_SphereRenderableVertexs de tipo CLinesListRenderableVertexs<UOC_POSITION_COLOR_VERTEX> pas�ndole los v�rtices de la esfera l_SphereVtxs, el n�mero de v�rtices y el n�mero de primitivas (n�mero de lineas)
}

CDebugRender::~CDebugRender()
{
	//TO DO : Destruir la variable miembro m_AxisRenderableVertexs utilizando la macro CHECKED_DELETE
	//TO DO : Destruir la variable miembro m_GridRenderableVertexs utilizando la macro CHECKED_DELETE
	//TO DO : Destruir la variable miembro m_CubeRenderableVertexs utilizando la macro CHECKED_DELETE
	//TO DO : Destruir la variable miembro m_SphereRenderableVertexs utilizando la macro CHECKED_DELETE
}


void CDebugRender::DrawAxis(ID3D11DeviceContext *DeviceContext, float Size)
{
	//TO DO : Establecer el color blanco (XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)) en la variable miembro m_BaseColor que se encuentra en la variable miembro est�tica m_ObjectConstantBufferParameters de la clase CEffectManager
	//TO DO : Establecer el tama�o seg�n el Size en la variable miembro m_DebugRenderScale que se encuentra en la variable miembro est�tica m_ObjectConstantBufferParameters de la clase CEffectManager
	//TO DO : Llamar al m�todo SetObjectConstantBuffer para establecer las constantes del objeto en el shader que se encuentra en el EffectManager del motor
	//TO DO : Pintar los ejes utilizando el m�todo Draw de la instancia m_AxisRenderableVertexs utilizando el CEffect m_Effect
}

void CDebugRender::DrawGrid(ID3D11DeviceContext *DeviceContext, float Size, XMFLOAT4 Color)
{
	//TO DO : Establecer el color en la variable miembro m_BaseColor que se encuentra en la variable miembro est�tica m_ObjectConstantBufferParameters de la clase CEffectManager
	//TO DO : Establecer el tama�o seg�n el Size en la variable miembro m_DebugRenderScale que se encuentra en la variable miembro est�tica m_ObjectConstantBufferParameters de la clase CEffectManager
	//TO DO : Llamar al m�todo SetObjectConstantBuffer para establecer las constantes del objeto en el shader que se encuentra en el EffectManager del motor
	//TO DO : Pintar la grid utilizando el m�todo Draw de la instancia m_GridRenderableVertexs utilizando el CEffect m_Effect
}

void CDebugRender::DrawCube(ID3D11DeviceContext *DeviceContext, float Size, XMFLOAT4 Color)
{
	//TO DO : Establecer el color en la variable miembro m_BaseColor que se encuentra en la variable miembro est�tica m_ObjectConstantBufferParameters de la clase CEffectManager
	//TO DO : Establecer el tama�o seg�n el Size en la variable miembro m_DebugRenderScale que se encuentra en la variable miembro est�tica m_ObjectConstantBufferParameters de la clase CEffectManager
	//TO DO : Llamar al m�todo SetObjectConstantBuffer para establecer las constantes del objeto en el shader que se encuentra en el EffectManager del motor
	//TO DO : Pintar el cubo utilizando el m�todo Draw de la instancia m_CubeRenderableVertexs utilizando el CEffect m_Effect
}

void CDebugRender::DrawSphere(ID3D11DeviceContext *DeviceContext, float Radius, XMFLOAT4 Color)
{
	//TO DO : Establecer el color en la variable miembro m_BaseColor que se encuentra en la variable miembro est�tica m_ObjectConstantBufferParameters de la clase CEffectManager
	//TO DO : Establecer el tama�o seg�n el Radius en la variable miembro m_DebugRenderScale que se encuentra en la variable miembro est�tica m_ObjectConstantBufferParameters de la clase CEffectManager
	//TO DO : Llamar al m�todo SetObjectConstantBuffer para establecer las constantes del objeto en el shader que se encuentra en el EffectManager del motor
	//TO DO : Pintar la esfera utilizando el m�todo Draw de la instancia m_SphereRenderableVertexs utilizando el CEffect m_Effect
}
