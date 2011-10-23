#pragma once
#ifndef _G_M2FILEFORMAT_H_
#define _G_M2FILEFORMAT_H_

#include <d3dx9.h>  
#include "gTypes.h"

struct gM2Header 
{
        char id[4];
        uint8 version[4];
        uint32 nameLength;
        uint32 nameOfs;
        uint32 GlobalModelFlags; // 1: tilt x, 2: tilt y, 4:, 8: add another field in header, 16: ; (no other flags as of 3.1.1);

        uint32 nGlobalSequences; // AnimationRelated
        uint32 ofsGlobalSequences; // A list of timestamps.
        uint32 nAnimations; // AnimationRelated
        uint32 ofsAnimations; // Information about the animations in the model.
        uint32 nAnimationLookup; // AnimationRelated
        uint32 ofsAnimationLookup; // Mapping of global IDs to the entries in the Animation sequences block.

        uint32 nBones; // BonesAndLookups
        uint32 ofsBones; // Information about the bones in this model.
        uint32 nKeyBoneLookup; // BonesAndLookups
        uint32 ofsKeyBoneLookup; // Lookup table for key skeletal bones.

        uint32 nVertices; // GeometryAndRendering
        uint32 ofsVertices; // Vertices of the model.
        uint32 nViews; // GeometryAndRendering

        uint32 nColors; // ColorsAndTransparency
        uint32 ofsColors; // Color definitions.

        uint32 nTextures; // TextureAndTheifAnimation
        uint32 ofsTextures; // Textures of this model.

        uint32 nTransparency; // H,  ColorsAndTransparency
        uint32 ofsTransparency; // Transparency of textures.

        uint32 nTexAnims;       // J, TextureAndTheifAnimation
        uint32 ofsTexAnims;
        uint32 nTexReplace; // TextureAndTheifAnimation
        uint32 ofsTexReplace; // Replaceable Textures.

        uint32 nTexFlags; // Render Flags
        uint32 ofsTexFlags; // Blending modes / render flags.
        uint32 nBoneLookup; // BonesAndLookups
        uint32 ofsBoneLookup; // A bone lookup table.

        uint32 nTexLookup; // TextureAndTheifAnimation
        uint32 ofsTexLookup; // The same for textures.

        uint32 nTexUnitLookup;          // L, TextureAndTheifAnimation
        uint32 ofsTexUnitLookup; // And texture units. Somewhere they have to be too.
        uint32 nTransparencyLookup; // M, ColorsAndTransparency
        uint32 ofsTransparencyLookup; // Everything needs its lookup. Here are the transparencies.
        uint32 nTexAnimLookup; // TextureAndTheifAnimation
        uint32 ofsTexAnimLookup; // Wait. Do we have animated Textures? Wasn't ofsTexAnims deleted? oO

        float ps[8];

        uint32 nBoundingTriangles; // Miscellaneous
        uint32 ofsBoundingTriangles;
        uint32 nBoundingVertices; // Miscellaneous
        uint32 ofsBoundingVertices;
        uint32 nBoundingNormals; // Miscellaneous
        uint32 ofsBoundingNormals;

        uint32 nAttachments; // O, Miscellaneous
        uint32 ofsAttachments; // Attachments are for weapons etc.
        uint32 nAttachLookup; // P, Miscellaneous
        uint32 ofsAttachLookup; // Of course with a lookup.
        uint32 nEvents; //
        uint32 ofsEvents; // Used for playing sounds when dying and a lot else.
        uint32 nLights; // R
        uint32 ofsLights; // Lights are mainly used in loginscreens but in wands and some doodads too.
        uint32 nCameras; // S, Miscellaneous
        uint32 ofsCameras; // The cameras are present in most models for having a model in the Character-Tab.
        uint32 nCameraLookup; // Miscellaneous
        uint32 ofsCameraLookup; // And lookup-time again.
        uint32 nRibbonEmitters; // U, Effects
        uint32 ofsRibbonEmitters; // Things swirling around. See the CoT-entrance for light-trails.
        uint32 nParticleEmitters; // V, Effects
        uint32 ofsParticleEmitters; // Spells and weapons, doodads and loginscreens use them. Blood dripping of a blade? Particles.
};

struct gM2VertexBlock 
{
        D3DXVECTOR3 position;
        uint8 weights[4];
        uint8 bones[4];
        D3DXVECTOR3 normal;
        D3DXVECTOR2 textCoords;
        unsigned int unknownValues[2]; 
};

struct gM2IndexGeometryBlock 
{
        char id[4];                             
	    uint32 nIndex;
        uint32 ofsIndex;
        uint32 nTris;
        uint32 ofsTris; 
        uint32 nProps;
        uint32 ofsProps;
        uint32 nSub;
        uint32 ofsSub;  
        uint32 nTex;
        uint32 ofsTex;  
        int32 lod;        
};

#endif