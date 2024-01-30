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
#include <iterator>
#include <list>

CAnimatedInstanceModel::CAnimatedInstanceModel() :
//TO DO : Inicializar la variable miembro m_AnimatedCoreModel a NULL
	m_AnimatedCoreModel{ NULL },
//TO DO : Inicializar la variable miembro m_CalModel a NULL
	m_CalModel{ NULL },
//TO DO : Inicializar la variable miembro m_CurrentAnimationId a -1
	m_CurrentAnimationId{-1},
//TO DO : Inicializar la variable miembro m_CurrentCycle a -1
	m_CurrentCycle{-1},
//TO DO : Inicializar la variable miembro m_NumVertices a 0
	m_NumVertices{0},
//TO DO : Inicializar la variable miembro m_NumFaces a 0
	m_NumFaces{0},
//TO DO : Inicializar la variable miembro m_CurrentAnimationTime a 0.0f
	m_CurrentAnimationTime{0.0f},
//TO DO : Inicializar la variable miembro m_RenderableVertexs a NULL
	m_RenderableVertexs{NULL},
//TO DO : Inicializar la variable miembro m_Effect a NULL
	m_Effect{NULL},
	m_CalHardwareModel{}
{
}

CAnimatedInstanceModel::~CAnimatedInstanceModel()
{
	//TO DO : Llamar al método Destroy
	Destroy();
}

void CAnimatedInstanceModel::Render(ID3D11DeviceContext *DeviceContext)
{
	//TO DO : Asignar el valor de m_World de la variable miembro estática m_ObjectConstantBufferParameters de la clase CEffectManager el valor la matriz transpuesta de GetTransform utilizando el método de DirectX XMMatrixTranspose, recordar que CAnimatedInstanceModel deriva de la clase CRenderableObject y que por ello podemos acceder a nuestro método de nuestra clase base GetTransform
	CEffectManager::m_ObjectConstantBufferParameters.m_World = DirectX::XMMatrixTranspose(GetTransform());
	//TO DO : Establecer los valores de constant buffer del shader para el objeto utilizando el método SetObjectConstantBuffer que se encuentra en la clase CEffectManager que encontramos en la clase CUOCEngine
	CUOCEngine::GetEngine()->GetEffectManager()->SetObjectConstantBuffer(DeviceContext);
	//TO DO : Recorrer de 0 hasta el número HardwareMeshCount que se encuentran en la variable miembro m_CalHardwareModel

	for (int m = 0; m < m_CalHardwareModel->getHardwareMeshCount(); ++m)
	{
		//TO DO : Activar la textura del vector m_TextureList utilizando el método Activate que tiene como índice el índice del for creado previamente asigándola en la etapa 0 
		m_TextureList[m]->Activate(DeviceContext, m); // TODO review
		//TO DO : Utilizar el método selectHardwareMesh de la variable miembro m_CalHardwareModel según el índice del for
		const bool _ = m_CalHardwareModel->selectHardwareMesh(m);

		XMMATRIX l_Transformations[MAXBONES]{};
		//TO DO : Recorrer de 0 hasta el número de Bones que haya en la variable miembro m_CalHardwareModel
		for (int b = 0; b < m_CalHardwareModel->getBoneCount(); ++b)
		{	
			XMVECTOR l_Quaternion;
			//TO DO : Asignar en la variable l_Quaternion la rotación del hueso en espacio hueso (getRotationBoneSpace) según el índice del for de huesos y el esqueleto de m_CalModel que extraemos de la variable miembro m_CalHardwareModel. Para asignarlo a tipo XMVECTOR podemos utilizar la función de DirectX XMLoadFloat4 ya que lo que nos devuelve el método getRotationBoneSpace es una estructura formada por 4 floats continuos
			CalQuaternion l_BoneRotation = m_CalHardwareModel->getRotationBoneSpace(b, m_CalModel->getSkeleton());
			XMFLOAT4 l_BoneRotationArray{l_BoneRotation.x, l_BoneRotation.y, l_BoneRotation.z, l_BoneRotation.w};
			l_Quaternion = DirectX::XMLoadFloat4(&l_BoneRotationArray);
			//TO DO : Asignar en la variable l_Transformations según el id del for de huesos la matriz de rotación calculada según el quaternion l_Quaternion utilizando la función DirectX::XMMatrixRotationQuaternion
			CalVector translationBoneSpace;
			l_Transformations[b] = DirectX::XMMatrixRotationQuaternion(l_Quaternion);
			//TO DO : Asignar en translationBoneSpace el valor de la posición del hueso en espacio hueso (getTranslationBoneSpace) de la variable miembro m_CalHardwareModel según el id del for de huesos y el esqueleto de la variable miembro m_CalModel
			translationBoneSpace = m_CalHardwareModel->getTranslationBoneSpace(b, m_CalModel->getSkeleton());
			//TO DO : Asignar en l_Transformations según el índice del hueso del for y atributo ._14 la posición en x de translationBoneSpace
			l_Transformations[b]._14 = translationBoneSpace.x;
			//TO DO : Asignar en l_Transformations según el índice del hueso del for y atributo ._24 la posición en y de translationBoneSpace
			l_Transformations[b]._24 = translationBoneSpace.y;
			//TO DO : Asignar en l_Transformations según el índice del hueso del for y atributo ._34 la posición en z de translationBoneSpace
			l_Transformations[b]._34 = translationBoneSpace.z;
			//TO DO : Asignar en l_Transformations según el índice del hueso del for la matriz transpuesta de sí mismo utilizando la función de DirectX XMMatrixTranspose
			l_Transformations[b] = DirectX::XMMatrixTranspose(l_Transformations[b]);

		}
		//TO DO : Copiar en la variable m_Bones de la variable miembro m_AnimatedModelConstantBufferParameters que se encuentra en la clase CEffectManager el array de valores que se encuentra en l_Transformations utilizando la función memcpy
		_memccpy(l_Transformations, CUOCEngine::GetEngine()->GetEffectManager()->m_AnimatedModelConstantBufferParameters.m_Bones, 1, sizeof(XMMATRIX)* m_CalHardwareModel->getBoneCount());
		//TO DO : Llamar al método SetAnimatedModelConstantBuffer de la clase CEffectManager que se encuentra en la clase CUOCEngine para establecer los valores de las matrices de los huesos en el constant buffer del shader
		CUOCEngine::GetEngine()->GetEffectManager()->SetAnimatedModelConstantBuffer(DeviceContext);
		//TO DO : Llamar al método DrawIndexed pasándole la variable miembro m_Effect, el número de índices que calculamos a partir del número de caras de la variable m_CalHardwareModel multiplicado por 3, el inicio del índice del m_CalHardwareModel, la base del índice de vértice del m_CalHardwareModel
		DeviceContext->DrawIndexed(/*m_Effect,*/ m_CalHardwareModel->getFaceCount() * 3, 0, m_CalHardwareModel->getBaseVertexIndex());
	}
}

void CAnimatedInstanceModel::Update(float ElapsedTime)
{
	//TO DO : Llamar al método Update de la variable miembro m_CalModel
	m_CalModel->update(ElapsedTime);
	//TO DO : Incrementar la variable miembro m_CurrentAnimationTime según el ElapsedTime
	m_CurrentAnimationTime += ElapsedTime;
	//TO DO : Si la variable m_CurrentAnimationId es diferente de -1 y la duración de la animación que tiene por id m_CurrentAnimationId es menor que el tiempo transcurrido de m_CurrentAnimationTime. Para extraer la duración de una animación debemos acceder al coreModel de la variable miembro m_CalModel, buscar la coreAnimation según un id y pedirle su duración
	if (-1 != m_CurrentAnimationId && m_CurrentAnimationTime < m_CalModel->getCoreModel()->getCoreAnimation(m_CurrentAnimationId)->getDuration())
	{
		//TO DO : Asignar el valor de 0 a m_CurrentAnimationTime
		m_CurrentAnimationTime = 0;
		//TO DO : Asignar el valor de -1 a m_CurrentAnimationId
		m_CurrentAnimationTime = -1;
	}
}

void CAnimatedInstanceModel::Initialize(CAnimatedCoreModel *AnimatedCoreModel)
{
	//TO DO : Asignar el valor AnimatedCoreModel en la variable miembro m_AnimatedCoreModel
	m_AnimatedCoreModel = AnimatedCoreModel;
	//TO DO : Construir la variable miembro m_CalModel de tipo CalModel según el CoreModel del parámetro AnimatedCoreModel
	m_CalModel = new CalModel(AnimatedCoreModel->GetCoreModel());
	//TO DO : Construir la variable miembro m_CalHardwareModel de tipo CalHardwareModel según el CoreModel del parámetro AnimatedCoreModel
	m_CalHardwareModel = new CalHardwareModel(AnimatedCoreModel->GetCoreModel());
	//TO DO : Implementar un for desde 0 hasta el número de CoreMesh que contiene el CoreModel de la instancia m_AnimatedCoreModel
	for (int m = 0; m < AnimatedCoreModel->GetCoreModel()->getCoreMeshCount(); ++m)
	{
		//TO DO : Atachar la malla en la instancia del modelo m_CalModel utilizando el método attachMesh
		m_CalModel->attachMesh(m);
	}
	//TO DO : Llamar al método BlendCycle para que inserte la animación de tipo ciclo con id 0 y tiempo de entrada 0.0f
	BlendCycle(0, 0.0f);
	//TO DO : Llamar al método Update con ElapsedTime a 0.0f para que se inicialicen los huesos del modelo animado
	Update(0.0f);
}

void CAnimatedInstanceModel::InitD3D(ID3D11Device *Device)
{
	//TO DO : Asignar el efecto en la variable miembro m_Effect que recogemos de la clase CEffectManager que se encuentra en la clase CUOCEngine según el tipo UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX::GetVertexType()
	m_Effect = CUOCEngine::GetEngine()->GetEffectManager()->GetEffect(UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX::GetVertexType());
	//TO DO : Llamar al método LoadVertexBuffer para crear el vertex buffer e index buffer del modelo animado
	LoadVertexBuffer(Device);
	//TO DO : Llamar al método LoadTexture para cargar las texturas de nuestro modelo animado
	LoadTexture(Device);
}

void CAnimatedInstanceModel::LoadTexture(ID3D11Device *Device)
{
	//TO DO : Implementamos el for desde 0 hasta el número de texturas que se encuentran en la variable m_AnimatedCoreModel utilizando el método GetNumTextures
	for (size_t t = 0; t < m_AnimatedCoreModel->GetNumTextures(); ++t)
	{
		//TO DO : Añadir la textura en el vector m_TextureList, para ello utilizaremos el método LoadTexture de la clase CTextureManager que se encuentra el la clase CUOCEngine, el nombre de la textura a cargar lo extraeremos utilizando el método GetTextureName de la variable miembro m_AnimatedCoreModel
		CUOCEngine::GetEngine()->GetTextureManager()->LoadTexture(Device, m_AnimatedCoreModel->GetTextureName(t));
	}
}

void CAnimatedInstanceModel::Destroy()
{
	//TO DO : Destruir la variable miembro m_RenderableVertexs utilizando la macro CHECKED_DELETE
	CHECKED_DELETE(m_RenderableVertexs);
	//TO DO : Destruir la variable miembro m_CalHardwareModel utilizando la macro CHECKED_DELETE
	CHECKED_DELETE(m_CalHardwareModel);
	//TO DO : Destruir la variable miembro m_CalModel utilizando la macro CHECKED_DELETE
	CHECKED_DELETE(m_CalModel);
}

void CAnimatedInstanceModel::ExecuteAction(int Id, float Time)
{
	//TO DO : Asignamos en la variable m_CurrentAnimationTime el valor de 0.0f
	m_CurrentAnimationTime = 0.0f;
	//TO DO : Asignamos el valor del animación de tipo acción Id en la variable miembro m_CurrentAnimationId
	m_CurrentAnimationId = Id;
	//TO DO : Utilizamos el método executeAction del mixer de la variable miembro m_CalModel con tiempo de entrada Time, tiempo de entrada 0.0f, peso 1.0f y autolock a false
	m_CalModel->getMixer()->executeAction(Id, 0.0f, Time);
}

void CAnimatedInstanceModel::BlendCycle(int Id, float Time)
{
	//TO DO : Si el m_CurrentCycle es diferente de -1 llamamos al método clearCycle de mixer de la variable miembro m_CalModel pasando el parámetro m_CurrentCycle
	if (m_CurrentCycle != -1) {
		m_CalModel->getMixer()->clearCycle(m_CurrentCycle, 0.0f);
	}
	//TO DO : Utilizamos el método blendCycle del mixer de la variable miembro m_CalModel
	m_CalModel->getMixer()->blendCycle(Id, 0, 0);//TODO check parameters
	//TO DO : Asignamos el valor de animación de tipo ciclo Id en la variable miembro m_CurrentCycle
	auto l_Begin = m_CalModel->getMixer()->getAnimationCycle().begin();
	auto& l_Style = l_Begin;
	std::advance(l_Style, Id);
	m_CurrentCycle = std::distance(l_Begin, l_Style);
}

void CAnimatedInstanceModel::ClearCycle(float Time)
{
	//TO DO : Llamar al método clearCycle del mixer que se encuentra en la variable miembro m_CalModel según el ciclo actual m_CurrentCycle
	m_CalModel->getMixer()->clearCycle(m_CurrentCycle, Time);
}

int CAnimatedInstanceModel::GetCurrentCycle() const
{
	//TO DO : Devolver el id de la animación actual de tipo ciclo que se encuentra en la variable miembro m_CurrentCycle
	return m_CurrentCycle;
}

int CAnimatedInstanceModel::GetAnimationId() const
{
	//TO DO : Devolver el id de la animación actual de tipo acción que se encuentra en la variable miembro m_CurrentAnimationId
	return m_CurrentAnimationId;
}

bool CAnimatedInstanceModel::LoadVertexBuffer(ID3D11Device *Device)
{
	CalRenderer *pCalRenderer;
	int meshCount;
	int meshId;
	int submeshId;

	//TO DO : Inicializar la variable miembro m_NumVertices a 0
	m_NumVertices = { 0 };
	//TO DO : Inicializar la variable miembro m_NumFaces a 0
	m_NumFaces = { 0 };
	//TO DO : Inicializar la variable miembro pCalRenderer al Renderer de la variable miembro m_CalModel
	pCalRenderer = { m_CalModel->getRenderer() };
	//TO DO : Inicializar la variable miembro meshCount al MeshCount de la instancia pCalRenderer
	meshCount = { pCalRenderer->getMeshCount() };
	//TO DO : Implementar el for para recorrer desde 0 hasta meshCount
	for (meshId = 0; meshId < meshCount; ++meshId)
	{
		int submeshCount;
		//TO DO : Asignar en submeshCount el número de submeshes que contiene pCalRenderer según el índice del for
		submeshCount = { pCalRenderer->getSubmeshCount(meshId) };
		//TO DO : Implementar el for para recorrer desde 0 hasta submeshCount
		for (submeshId = 0; submeshId < submeshCount; ++submeshId)
		{		
			//TO DO : Llamar al método selectMeshSubmesh de pCalRenderer dentro del if según el índice de mesh del primer for y el índice de submesh según el segundo for
			if (pCalRenderer->selectMeshSubmesh(meshId, submeshId))
			{
				//TO DO : Incrementar m_NumFaces según el número de caras que contiene pCalRenderer usando el método getFaceCount
				m_NumFaces += pCalRenderer->getFaceCount();
				//TO DO : Incrementar m_NumVertices según el número de vértices que contiene pCalRenderer usando el método getVertexCoun
				m_NumVertices += pCalRenderer->getVertexCount();
			}
		}
	}

	UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX *l_Vertexs;
	//TO DO : Reservar en memoria RAM utilizando la función malloc la cantidad de bytes del tamaño de UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX por 3 por el número de vértices m_NumVertices y asignarla a la variable l_Vertexs
	l_Vertexs = (UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX*)malloc(sizeof(UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX) * 3);
	CalIndex *l_Faces;
	//TO DO : Reservar en memoria RAM utilizando la función malloc la cantidad de bytes del tamaño de CalIndex por 3 por número de caras y asignarla a la variable l_Vertexs l_Faces
	l_Faces = (CalIndex*)malloc(sizeof(CalIndex) * 3);

	//TO DO : Llamar al método setVertexBuffer de m_CalHardwareModel para extraer la información posiciones geométricas, pasamos como parámetro la dirección de los vértices l_Vertex más un offset de 0 bytes y el tamaño de la estructura UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX (utilizamos la función sizeof para extraer el tamaño de la estructura)
	m_CalHardwareModel->setVertexBuffer((char*)l_Vertexs, sizeof(UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX));
	//TO DO : Llamar al método setWeightBuffer de m_CalHardwareModel para extraer la información de los pesos de huesos de cada vértice, pasamos como parámetro la dirección de los vértices l_Vertex más un offset de 12 bytes y el tamaño de la estructura UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX (utilizamos la función sizeof para extraer el tamaño de la estructura)
	m_CalHardwareModel->setWeightBuffer((char*)l_Vertexs + 12, sizeof(UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX));
	//TO DO : Llamar al método setMatrixIndexBuffer de m_CalHardwareModel para extraer la información de los índices de huesos de cada vértice, pasamos como parámetro la dirección de los vértices l_Vertex más un offset de 28 bytes y el tamaño de la estructura UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX (utilizamos la función sizeof para extraer el tamaño de la estructura)
	m_CalHardwareModel->setMatrixIndexBuffer((char*)l_Vertexs + 28, sizeof(UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX));
	//TO DO : Llamar al método setNormalBuffer de m_CalHardwareModel para extraer la información de normales, pasamos como parámetro la dirección de los vértices l_Vertex más un offset de 44 bytes y el tamaño de la estructura UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX (utilizamos la función sizeof para extraer el tamaño de la estructura)
	m_CalHardwareModel->setNormalBuffer((char*)l_Vertexs + 44, sizeof(UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX));
	//TO DO : Llamar al método setTextureCoordNum de m_CalHardwareModel pasándole el número de coordenadas de texturas que contiene nuestro modelo, en este caso 1
	m_CalHardwareModel->setTextureCoordNum(1);
	//TO DO : Llamar al método setTextureCoordBuffer de m_CalHardwareModel para extraer la información de coordenadas de textura (0), pasamos como parámetro la dirección de los vértices l_Vertex más un offset de 56 bytes y el tamaño de la estructura UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX (utilizamos la función sizeof para extraer el tamaño de la estructura)
	m_CalHardwareModel->setTextureCoordBuffer(0,(char*)l_Vertexs + 56, sizeof(UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX));
	//TO DO : Llamar al método setIndexBuffer de m_CalHardwareModel pasándole las caras l_Faces
	m_CalHardwareModel->setIndexBuffer(l_Faces);

	//TO DO : Llamar al método load de la variable miembro m_CalHardwareModel con baseVertexIndex=0, startIndex=0 y maxBonesPerMesh=MAXBONES
	m_CalHardwareModel->load(0, 0, MAXBONES);

	//TO DO : Asignar en m_NumFaces el número de caras totales (getTotalFaceCount) que tiene m_CalHardwareModel
	m_NumFaces = m_CalHardwareModel->getTotalFaceCount();
	//TO DO : Asignar en m_NumVertices el número de vértices totales (getTotalVertexCount) que tiene m_CalHardwareModel
	m_NumVertices = m_CalHardwareModel->getTotalVertexCount();

	//TO DO : Si el tamaño del tipo CalIndex es 2 bytes. Utilizamos la función sizeof para saber el tamaño en bytes de un tipo
	if (sizeof(CalIndex) == 2)
		//TO DO : Construir la variable miembro m_RenderableVertexs de tipo CTriangleListRenderableIndexed16Vertexs<UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX> dónde le pasamos los vértices, número de vértices, caras y el número de índices que contiene las caras (caras*3)
		m_RenderableVertexs = new CTriangleListRenderableIndexed16Vertexs<UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX>(Device, l_Vertexs, m_NumVertices, l_Faces, m_NumFaces *3 );
	else
		//TO DO : Construir la variable miembro m_RenderableVertexs de tipo CTriangleListRenderableIndexed32Vertexs<UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX> dónde le pasamos los vértices, número de vértices, caras y el número de índices que contiene las caras (caras*3)
		m_RenderableVertexs = new CTriangleListRenderableIndexed32Vertexs<UOC_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX>(Device, l_Vertexs, m_NumVertices, l_Faces, m_NumFaces * 3);
	//TO DO : Liberar de memoria l_Vertexs utilizando la función free
	free(l_Vertexs);
	//TO DO : Liberar de memoria l_Faces utilizando la función free
	free(l_Faces);

	return true;
}
