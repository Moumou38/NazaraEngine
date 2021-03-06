// Copyright (C) 2014 Jérôme Leclercq
// This file is part of the "Nazara Engine - Graphics module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_ENUMS_GRAPHICS_HPP
#define NAZARA_ENUMS_GRAPHICS_HPP

enum nzBackgroundType
{
	nzBackgroundType_Color,   // NzColorBackground
	nzBackgroundType_Skybox,  // NzSkyboxBackground
	nzBackgroundType_Texture, // NzTextureBackground
	nzBackgroundType_User,

	nzBackgroundType_Max = nzBackgroundType_User
};

enum nzLightType
{
	nzLightType_Directional,
	nzLightType_Point,
	nzLightType_Spot,

	nzLightType_Max = nzLightType_Spot
};

enum nzRenderPassType
{
	nzRenderPassType_AA,
	nzRenderPassType_Bloom,
	nzRenderPassType_DOF,
	nzRenderPassType_Final,
	nzRenderPassType_Fog,
	nzRenderPassType_Forward,
	nzRenderPassType_Lighting,
	nzRenderPassType_Geometry,
	nzRenderPassType_SSAO,

	nzRenderPassType_Max = nzRenderPassType_SSAO
};

enum nzRenderTechniqueType
{
	nzRenderTechniqueType_AdvancedForward, // NzAdvancedForwardRenderTechnique
	nzRenderTechniqueType_BasicForward,    // NzBasicForwardRenderTechnique
	nzRenderTechniqueType_DeferredShading, // NzDeferredRenderTechnique
	nzRenderTechniqueType_LightPrePass,    // NzLightPrePassRenderTechnique
	nzRenderTechniqueType_User,

	nzRenderTechniqueType_Max = nzRenderTechniqueType_User
};

enum nzSceneNodeType
{
	nzSceneNodeType_Light,  // NzLight
	nzSceneNodeType_Model,  // NzModel
	nzSceneNodeType_Root,   // NzSceneRoot
	nzSceneNodeType_Sprite, // NzSprite
	nzSceneNodeType_User,

	nzSceneNodeType_Max = nzSceneNodeType_User
};

#endif // NAZARA_ENUMS_GRAPHICS_HPP
