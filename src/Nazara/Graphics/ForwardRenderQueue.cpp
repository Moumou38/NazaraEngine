// Copyright (C) 2013 Jérôme Leclercq
// This file is part of the "Nazara Engine - Graphics module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Graphics/ForwardRenderQueue.hpp>
#include <Nazara/Graphics/Camera.hpp>
#include <Nazara/Graphics/Light.hpp>
#include <Nazara/Graphics/Model.hpp>
#include <Nazara/Renderer/Material.hpp>
#include <Nazara/Utility/SkeletalMesh.hpp>
#include <Nazara/Utility/StaticMesh.hpp>
#include <Nazara/Graphics/Debug.hpp>

void NzForwardRenderQueue::AddDrawable(const NzDrawable* drawable)
{
	#if NAZARA_GRAPHICS_SAFE
	if (!drawable)
	{
		NazaraError("Invalid drawable");
		return;
	}
	#endif

	otherDrawables.push_back(drawable);
}

void NzForwardRenderQueue::AddLight(const NzLight* light)
{
	#if NAZARA_GRAPHICS_SAFE
	if (!light)
	{
		NazaraError("Invalid light");
		return;
	}
	#endif

	switch (light->GetLightType())
	{
		case nzLightType_Directional:
			directionnalLights.push_back(light);
			break;

		case nzLightType_Point:
		case nzLightType_Spot:
			visibleLights.push_back(light);
			break;

		#ifdef NAZARA_DEBUG
		default:
			NazaraError("Light type not handled (0x" + NzString::Number(light->GetLightType(), 16) + ')');
		#endif
	}
}

void NzForwardRenderQueue::AddModel(const NzModel* model)
{
	#if NAZARA_GRAPHICS_SAFE
	if (!model)
	{
		NazaraError("Invalid model");
		return;
	}

	if (!model->IsDrawable())
	{
		NazaraError("Model is not drawable");
		return;
	}
	#endif

	const NzMatrix4f& transformMatrix = model->GetTransformMatrix();

	NzMesh* mesh = model->GetMesh();
	unsigned int submeshCount = mesh->GetSubMeshCount();

	for (unsigned int i = 0; i < submeshCount; ++i)
	{
		NzSubMesh* subMesh = mesh->GetSubMesh(i);
		NzMaterial* material = model->GetMaterial(subMesh->GetMaterialIndex());

		switch (subMesh->GetAnimationType())
		{
			case nzAnimationType_Skeletal:
			{
				///TODO
				/*
				** Il y a ici deux choses importantes à gérer:
				** -Pour commencer, la mise en cache de std::vector suffisamment grands pour contenir le résultat du skinning
				**  l'objectif ici est d'éviter une allocation à chaque frame, donc de réutiliser un tableau existant
				**  Note: Il faudrait évaluer aussi la possibilité de conserver le buffer d'une frame à l'autre.
				**        Ceci permettant de ne pas skinner inutilement ce qui ne bouge pas, ou de skinner partiellement un mesh.
				**        Il faut cependant voir où stocker ce set de buffers, qui doit être communs à toutes les RQ d'une même scène.
				**
				** -Ensuite, la possibilité de regrouper les modèles skinnés identiques, une centaine de soldats marchant au pas
				**  ne devrait requérir qu'un skinning.
				*/
				NazaraError("Skeletal mesh not supported yet, sorry");
				break;
			}

			case nzAnimationType_Static:
			{
				NzStaticMesh* staticMesh = static_cast<NzStaticMesh*>(subMesh);
				if (material->IsAlphaBlendingEnabled())
				{
					unsigned int index = transparentStaticModels.size();
					transparentStaticModels.resize(index+1);

					TransparentStaticModel& data = transparentStaticModels.back();
					data.material = material;
					data.mesh = staticMesh;
					data.transformMatrix = transformMatrix;

					visibleTransparentsModels.push_back(std::make_pair(index, true));
				}
				else
					visibleModels[material].second[staticMesh].push_back(transformMatrix);

				break;
			}
		}
	}
}

void NzForwardRenderQueue::Clear()
{
	directionnalLights.clear();
	otherDrawables.clear();
	visibleLights.clear();
	visibleModels.clear();
	visibleTransparentsModels.clear();
	transparentSkeletalModels.clear();
	transparentStaticModels.clear();
}

void NzForwardRenderQueue::Sort(const NzCamera& camera)
{
	struct TransparentModelComparator
	{
		bool operator()(const std::pair<unsigned int, bool>& index1, const std::pair<unsigned int, bool>& index2)
		{
			const NzMatrix4f& matrix1 = (index1.second) ?
			                            queue->transparentStaticModels[index1.first].transformMatrix :
			                            queue->transparentSkeletalModels[index1.first].transformMatrix;

			const NzMatrix4f& matrix2 = (index1.second) ?
			                            queue->transparentStaticModels[index2.first].transformMatrix :
			                            queue->transparentSkeletalModels[index2.first].transformMatrix;

			return nearPlane.Distance(matrix1.GetTranslation()) < nearPlane.Distance(matrix2.GetTranslation());
		}

		NzForwardRenderQueue* queue;
		NzPlanef nearPlane;
	};

	TransparentModelComparator comparator {this, camera.GetFrustum().GetPlane(nzFrustumPlane_Near)};
	std::sort(visibleTransparentsModels.begin(), visibleTransparentsModels.end(), comparator);
}

bool NzForwardRenderQueue::SkeletalMeshComparator::operator()(const NzSkeletalMesh* subMesh1, const NzSkeletalMesh* subMesh2)
{
	const NzIndexBuffer* iBuffer1 = subMesh1->GetIndexBuffer();
	const NzBuffer* buffer1 = (iBuffer1) ? iBuffer1->GetBuffer() : nullptr;

	const NzIndexBuffer* iBuffer2 = subMesh1->GetIndexBuffer();
	const NzBuffer* buffer2 = (iBuffer2) ? iBuffer2->GetBuffer() : nullptr;

	if (buffer1 == buffer2)
		return subMesh1 < subMesh2;
	else
		return buffer2 < buffer2;
}

bool NzForwardRenderQueue::StaticMeshComparator::operator()(const NzStaticMesh* subMesh1, const NzStaticMesh* subMesh2)
{
	const NzIndexBuffer* iBuffer1 = subMesh1->GetIndexBuffer();
	const NzBuffer* buffer1 = (iBuffer1) ? iBuffer1->GetBuffer() : nullptr;

	const NzIndexBuffer* iBuffer2 = subMesh1->GetIndexBuffer();
	const NzBuffer* buffer2 = (iBuffer2) ? iBuffer2->GetBuffer() : nullptr;

	if (buffer1 == buffer2)
	{
		buffer1 = subMesh1->GetVertexBuffer()->GetBuffer();
		buffer2 = subMesh2->GetVertexBuffer()->GetBuffer();

		if (buffer1 == buffer2)
			return subMesh1 < subMesh2;
		else
			return buffer1 < buffer2;
	}
	else
		return buffer1 < buffer2;
}

bool NzForwardRenderQueue::MaterialComparator::operator()(const NzMaterial* mat1, const NzMaterial* mat2)
{
	const NzShader* shader1 = mat1->GetCustomShader();
	const NzShader* shader2 = mat2->GetCustomShader();

	if (shader1)
	{
		if (shader2)
		{
			if (shader1 != shader2)
				return shader1 < shader2;
		}
		else
			return true;
	}
	else if (shader2)
		return false;
	else
	{
		nzUInt32 shaderFlags1 = mat1->GetShaderFlags();
		nzUInt32 shaderFlags2 = mat2->GetShaderFlags();

		if (shaderFlags1 != shaderFlags2)
			return shaderFlags1 < shaderFlags2;
	}

	return mat1 < mat2;
}