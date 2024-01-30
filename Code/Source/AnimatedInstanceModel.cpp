#include "AnimatedCoreModel.h"
#include "ApplicationDX.h"
#include "EffectManager.h"
#include "RenderableVertexs.h"
#include "AnimatedInstanceModel.h"
#include "cal3d/cal3d.h"
#include "defines.h"
#include "TextureManager.h"
#include <vector>
#include "VertexTypes.h"
#include "UOCEngine.h"
#include "RenderManager.h"

CAnimatedInstanceModel::CAnimatedInstanceModel()
//TO DO : Inicializar la variable miembro m_AnimatedCoreModel a NULL
//TO DO : Inicializar la variable miembro m_CalModel a NULL
//TO DO : Inicializar la variable miembro m_CurrentAnimationId a -1
//TO DO : Inicializar la variable miembro m_CurrentCycle a -1
//TO DO : Inicializar la variable miembro m_NumVertices a 0
//TO DO : Inicializar la variable miembro m_NumFaces a 0
//TO DO : Inicializar la variable miembro m_CurrentAnimationTime a 0.0f
//TO DO : Inicializar la variable miembro m_RenderableVertexs a NULL
//TO DO : Inicializar la variable miembro m_Effect a NULL
{
}

CAnimatedInstanceModel::~CAnimatedInstanceModel()
{
	//TO DO : Llamar al m�todo Destroy
}

void CAnimatedInstanceModel::Render(ID3D11DeviceContext *DeviceContext)
{
	//TO DO : Asignar el valor de m_World de la variable miembro est�tica m_ObjectConstantBufferParameters de la clase CEffectManager el valor la matriz transpuesta de GetTransform utilizando el m�todo de DirectX XMMatrixTranspose, recordar que CAnimatedInstanceModel deriva de la clase CRenderableObject y que por ello podemos acceder a nuestro m�todo de nuestra clase base GetTransform
	//TO DO : Establecer los valores de constant buffer del shader para el objeto utilizando el m�todo SetObjectConstantBuffer que se encuentra en la clase CEffectManager que encontramos en la clase CUOCEngine
	//TO DO : Recorrer de 0 hasta el n�mero HardwareMeshCount que se encuentran en la variable miembro m_CalHardwareModel

	for ()
	{
		//TO DO : Activar la textura del vector m_TextureList utilizando el m�todo Activate que tiene como �ndice el �ndice del for creado previamente asig�ndola en la etapa 0 
		//TO DO : Utilizar el m�todo selectHardwareMesh de la variable miembro m_CalHardwareModel seg�n el �ndice del for
		XMMATRIX l_Transformations[MAXBONES];
		//TO DO : Recorrer de 0 hasta el n�mero de Bones que haya en la variable miembro m_CalHardwareModel
		for ()
		{	
			XMVECTOR l_Quaternion;
			//TO DO : Asignar en la variable l_Quaternion la rotaci�n del hueso en espacio hueso (getRotationBoneSpace) seg�n el �ndice del for de huesos y el esqueleto de m_CalModel que extraemos de la variable miembro m_CalHardwareModel. Para asignarlo a tipo XMVECTOR podemos utilizar la funci�n de DirectX XMLoadFloat4 ya que lo que nos devuelve el m�todo getRotationBoneSpace es una estructura formada por 4 floats continuos
			//TO DO : Asignar en la variable l_Transformations seg�n el id del for de huesos la matriz de rotaci�n calculada seg�n el quaternion l_Quaternion utilizando la funci�n DirectX::XMMatrixRotationQuaternion
			CalVector translationBoneSpace;
			//TO DO : Asignar en translationBoneSpace el valor de la posici�n del hueso en espacio hueso (getTranslationBoneSpace) de la variable miembro m_CalHardwareModel seg�n el id del for de huesos y el esqueleto de la variable miembro m_CalModel
			//TO DO : Asignar en l_Transformations seg�n el �ndice del hueso del for y atributo ._14 la posici�n en x de translationBoneSpace
			//TO DO : Asignar en l_Transformations seg�n el �ndice del hueso del for y atributo ._24 la posici�n en y de translationBoneSpace
			//TO DO : Asignar en l_Transformations seg�n el �ndice del hueso del for y atributo ._34 la posici�n en z de translationBoneSpace
			//TO DO : Asignar en l_Transformations seg�n el �ndice del hueso del for la matriz transpuesta de s� mismo utilizando la funci�n de DirectX XMMatrixTranspose
		}
		//TO DO : Copiar en la variable m_Bones de la variable miembro m_AnimatedModelConstantBufferParameters que se encuentra en la clase CEffectManager el array de valores que se encuentra en l_Transformations utilizando la funci�n memcpy
		//TO DO : Llamar al m�todo SetAnimatedModelConstantBuffer de la clase CEffectManager que se encuentra en la clase CUOCEngine para establecer los valores de las matrices de los huesos en el constant buffer del shader
		//TO DO : Llamar al m�todo DrawIndexed pas�ndole la variable miembro m_Effect, el n�mero de �ndices que calculamos a partir del n�mero de caras de la variable m_CalHardwareModel multiplicado por 3, el inicio del �ndice del m_CalHardwareModel, la base del �ndice de v�rtice del m_CalHardwareModel
	}
}

void CAnimatedInstanceModel::Update(float ElapsedTime)
{
	//TO DO : Llamar al m�todo Update de la variable miembro m_CalModel
	//TO DO : Incrementar la variable miembro m_CurrentAnimationTime seg�n el ElapsedTime
	//TO DO : Si la variable m_CurrentAnimationId es diferente de -1 y la duraci�n de la animaci�n que tiene por id m_CurrentAnimationId es menor que el tiempo transcurrido de m_CurrentAnimationTime. Para extraer la duraci�n de una animaci�n debemos acceder al coreModel de la variable miembro m_CalModel, buscar la coreAnimation seg�n un id y pedirle su duraci�n
	if ()
	{
		//TO DO : Asignar el valor de 0 a m_CurrentAnimationTime
		//TO DO : Asignar el valor de -1 a m_CurrentAnimationId
	}
}

void CAnimatedInstanceModel::Initialize(CAnimatedCoreModel *AnimatedCoreModel)
{
	//TO DO : Asignar el valor AnimatedCoreModel en la variable miembro m_AnimatedCoreModel
	//TO DO : Construir la variable miembro m_CalModel de tipo CalModel seg�n el CoreModel del par�metro AnimatedCoreModel
	//TO DO : Construir la variable miembro m_CalHardwareModel de tipo CalHardwareModel seg�n el CoreModel del par�metro AnimatedCoreModel
	//TO DO : Implementar un for desde 0 hasta el n�mero de CoreMesh que contiene el CoreModel de la instancia m_AnimatedCoreModel
	for ()
	{
		//TO DO : Atachar la malla en la instancia del modelo m_CalModel utilizando el m�todo attachMesh
	}
	//TO DO : Llamar al m�todo BlendCycle para que inserte la animaci�n de tipo ciclo con id 0 y tiempo de entrada 0.0f
	//TO DO : Llamar al m�todo Update con ElapsedTime a 0.0f para que se inicialicen los huesos del modelo animado
}

void CAnimatedInstanceModel::InitD3D(ID3D11Device *Device)
{
	//TO DO : Asignar el efecto en la variable miembro m_Effect que recogemos de la clase CEffectManager que se encuentra en la clase CUOCEngine seg�n el tipo UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX::GetVertexType()
	//TO DO : Llamar al m�todo LoadVertexBuffer para crear el vertex buffer e index buffer del modelo animado
	//TO DO : Llamar al m�todo LoadTexture para cargar las texturas de nuestro modelo animado
}

void CAnimatedInstanceModel::LoadTexture(ID3D11Device *Device)
{
	//TO DO : Implementamos el for desde 0 hasta el n�mero de texturas que se encuentran en la variable m_AnimatedCoreModel utilizando el m�todo GetNumTextures
	for ()
	{
		//TO DO : A�adir la textura en el vector m_TextureList, para ello utilizaremos el m�todo LoadTexture de la clase CTextureManager que se encuentra el la clase CUOCEngine, el nombre de la textura a cargar lo extraeremos utilizando el m�todo GetTextureName de la variable miembro m_AnimatedCoreModel
	}
}

void CAnimatedInstanceModel::Destroy()
{
	//TO DO : Destruir la variable miembro m_RenderableVertexs utilizando la macro CHECKED_DELETE
	//TO DO : Destruir la variable miembro m_CalHardwareModel utilizando la macro CHECKED_DELETE
	//TO DO : Destruir la variable miembro m_CalModel utilizando la macro CHECKED_DELETE
}

void CAnimatedInstanceModel::ExecuteAction(int Id, float Time)
{
	//TO DO : Asignamos en la variable m_CurrentAnimationTime el valor de 0.0f
	//TO DO : Asignamos el valor del animaci�n de tipo acci�n Id en la variable miembro m_CurrentAnimationId
	//TO DO : Utilizamos el m�todo executeAction del mixer de la variable miembro m_CalModel con tiempo de entrada Time, tiempo de entrada 0.0f, peso 1.0f y autolock a false
}

void CAnimatedInstanceModel::BlendCycle(int Id, float Time)
{
	//TO DO : Si el m_CurrentCycle es diferente de -1 llamamos al m�todo clearCycle de mixer de la variable miembro m_CalModel pasando el par�metro m_CurrentCycle
	//TO DO : Utilizamos el m�todo blendCycle del mixer de la variable miembro m_CalModel
	//TO DO : Asignamos el valor de animaci�n de tipo ciclo Id en la variable miembro m_CurrentCycle
}

void CAnimatedInstanceModel::ClearCycle(float Time)
{
	//TO DO : Llamar al m�todo clearCycle del mixer que se encuentra en la variable miembro m_CalModel seg�n el ciclo actual m_CurrentCycle
}

int CAnimatedInstanceModel::GetCurrentCycle() const
{
	//TO DO : Devolver el id de la animaci�n actual de tipo ciclo que se encuentra en la variable miembro m_CurrentCycle
}

int CAnimatedInstanceModel::GetAnimationId() const
{
	//TO DO : Devolver el id de la animaci�n actual de tipo acci�n que se encuentra en la variable miembro m_CurrentAnimationId
}

bool CAnimatedInstanceModel::LoadVertexBuffer(ID3D11Device *Device)
{
	CalRenderer *pCalRenderer;
	int meshCount;
	int meshId;
	int submeshId;

	//TO DO : Inicializar la variable miembro m_NumVertices a 0
	//TO DO : Inicializar la variable miembro m_NumFaces a 0
	//TO DO : Inicializar la variable miembro pCalRenderer al Renderer de la variable miembro m_CalModel
	//TO DO : Inicializar la variable miembro meshCount al MeshCount de la instancia pCalRenderer
	//TO DO : Implementar el for para recorrer desde 0 hasta meshCount
	for ()
	{
		int submeshCount;
		//TO DO : Asignar en submeshCount el n�mero de submeshes que contiene pCalRenderer seg�n el �ndice del for
		//TO DO : Implementar el for para recorrer desde 0 hasta submeshCount
		for ()
		{		
			//TO DO : Llamar al m�todo selectMeshSubmesh de pCalRenderer dentro del if seg�n el �ndice de mesh del primer for y el �ndice de submesh seg�n el segundo for
			if ()
			{
				//TO DO : Incrementar m_NumFaces seg�n el n�mero de caras que contiene pCalRenderer usando el m�todo getFaceCount
				//TO DO : Incrementar m_NumVertices seg�n el n�mero de v�rtices que contiene pCalRenderer usando el m�todo getVertexCoun
			}
		}
	}

	UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX *l_Vertexs;
	//TO DO : Reservar en memoria RAM utilizando la funci�n malloc la cantidad de bytes del tama�o de UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX por 3 por el n�mero de v�rtices m_NumVertices y asignarla a la variable l_Vertexs
	CalIndex *l_Faces;
	//TO DO : Reservar en memoria RAM utilizando la funci�n malloc la cantidad de bytes del tama�o de CalIndex por 3 por n�mero de caras y asignarla a la variable l_Vertexs l_Faces

	//TO DO : Llamar al m�todo setVertexBuffer de m_CalHardwareModel para extraer la informaci�n posiciones geom�tricas, pasamos como par�metro la direcci�n de los v�rtices l_Vertex m�s un offset de 0 bytes y el tama�o de la estructura UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX (utilizamos la funci�n sizeof para extraer el tama�o de la estructura)
	//TO DO : Llamar al m�todo setWeightBuffer de m_CalHardwareModel para extraer la informaci�n de los pesos de huesos de cada v�rtice, pasamos como par�metro la direcci�n de los v�rtices l_Vertex m�s un offset de 12 bytes y el tama�o de la estructura UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX (utilizamos la funci�n sizeof para extraer el tama�o de la estructura)
	//TO DO : Llamar al m�todo setMatrixIndexBuffer de m_CalHardwareModel para extraer la informaci�n de los �ndices de huesos de cada v�rtice, pasamos como par�metro la direcci�n de los v�rtices l_Vertex m�s un offset de 28 bytes y el tama�o de la estructura UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX (utilizamos la funci�n sizeof para extraer el tama�o de la estructura)
	//TO DO : Llamar al m�todo setNormalBuffer de m_CalHardwareModel para extraer la informaci�n de normales, pasamos como par�metro la direcci�n de los v�rtices l_Vertex m�s un offset de 44 bytes y el tama�o de la estructura UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX (utilizamos la funci�n sizeof para extraer el tama�o de la estructura)
	//TO DO : Llamar al m�todo setTextureCoordNum de m_CalHardwareModel pas�ndole el n�mero de coordenadas de texturas que contiene nuestro modelo, en este caso 1
	//TO DO : Llamar al m�todo setTextureCoordBuffer de m_CalHardwareModel para extraer la informaci�n de coordenadas de textura (0), pasamos como par�metro la direcci�n de los v�rtices l_Vertex m�s un offset de 56 bytes y el tama�o de la estructura UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX (utilizamos la funci�n sizeof para extraer el tama�o de la estructura)
	//TO DO : Llamar al m�todo setIndexBuffer de m_CalHardwareModel pas�ndole las caras l_Faces

	//TO DO : Llamar al m�todo load de la variable miembro m_CalHardwareModel con baseVertexIndex=0, startIndex=0 y maxBonesPerMesh=MAXBONES

	//TO DO : Asignar en m_NumFaces el n�mero de caras totales (getTotalFaceCount) que tiene m_CalHardwareModel
	//TO DO : Asignar en m_NumVertices el n�mero de v�rtices totales (getTotalVertexCount) que tiene m_CalHardwareModel

	//TO DO : Si el tama�o del tipo CalIndex es 2 bytes. Utilizamos la funci�n sizeof para saber el tama�o en bytes de un tipo
	if ()
		//TO DO : Construir la variable miembro m_RenderableVertexs de tipo CTriangleListRenderableIndexed16Vertexs<UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX> d�nde le pasamos los v�rtices, n�mero de v�rtices, caras y el n�mero de �ndices que contiene las caras (caras*3)
	else
		//TO DO : Construir la variable miembro m_RenderableVertexs de tipo CTriangleListRenderableIndexed32Vertexs<UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX> d�nde le pasamos los v�rtices, n�mero de v�rtices, caras y el n�mero de �ndices que contiene las caras (caras*3)
	//TO DO : Liberar de memoria l_Vertexs utilizando la funci�n free
	//TO DO : Liberar de memoria l_Faces utilizando la funci�n free

	return true;
}
