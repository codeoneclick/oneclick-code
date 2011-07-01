#ifndef CM2_H
#define CM2_H

#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include "../../Game/Enviroment/Mesh.h"
#include "../../Math/Util.h"

namespace Loader
{
	class CM2
	{
	private :

		enum EM3VERSION { M3_01 = 0, M3_02, M3_03, M3_UNKNOWN };

		struct SHeader
		{
			char id[4];
			unsigned int offset;
			unsigned int tagsCount;
			unsigned int unknown_01;
			unsigned int unknown_02;
		};

		struct STag 
		{
			char name[4];
			unsigned int offset;
			unsigned int size;
			unsigned int version;
		};

		struct STagRef
		{
			unsigned int entries;
			unsigned int ref;
		};

		struct STagCutoff
		{
			unsigned int unknown_01[88];
			STagRef globalBonesIndecesList;
		};

		struct SRegion 
		{
			unsigned short vertecesOffset;
			unsigned short nVertices;
			unsigned int   indecesOffset;
			unsigned int   nIndices; 
		};

		struct SAnimationRef
		{
			unsigned short flag_01; 
			unsigned short flag_02; 
			unsigned int id; 
		};

		struct SBoneData
		{
			SAnimationRef translationId;
			SAnimationRef rotationId;

			math::Vector3d initPosition;
			math::Vector4d initRotation;
			math::Vector3d initScale;

			unsigned short parent;

			math::Matrix4x4 matrix;

			SBoneData *parentPtr;
		};

		struct SVertexBone
		{
			unsigned char boneWeight[4];
			unsigned char boneIndex[4];
		};

		struct SSequence
		{
			unsigned int *transformId;
			unsigned int nTransforms;
			math::Vector3d *vTranslation;
			unsigned int nTranslation;
			math::Vector4d *qRotation;
			unsigned int nRotation;
		};

		struct SAnimationData 
		{
			STagRef frames; 
			unsigned long unknown_01;
			unsigned long unknown_02;
			STagRef keys;
		};

		struct SAnimationTranslationData
		{
			unsigned int nFrames;
			math::Vector3d *vTranslation;
		};

		struct SAnimationRotationData
		{
			unsigned int nFrames;
			math::Vector4d *vRotation;
		};

		struct SIndexBlock
		{
			 STagRef faces; 
			 STagRef regions; 
			 STagRef BAT;
			 STagRef MSEC;
		};

		struct SVertexBlock_01
		{
			math::Vector3d position;
			unsigned char  boneWeight[4];
			unsigned char  boneIndex[4];
			unsigned char  normal[4];
			unsigned short uv[2];
			unsigned int   unknown_01;
			unsigned char  tangent[4];
		};

		struct SVertexBlock_02
		{
			math::Vector3d position;
			unsigned char  boneWeight[4];
			unsigned char  boneIndex[4];
			unsigned char  normal[4];
			unsigned short uv[2];
			unsigned char  tangent[4];
		};

		struct SVertexBlock_03
		{
			math::Vector3d position;
			unsigned char  boneWeight[4];
			unsigned char  boneIndex[4];
			unsigned char  normal[4];
			unsigned short uv[2];
			unsigned char  unknown_01[10];
		};
public :
		struct SMeshBuffer
		{
			math::Vector3d *position;
			math::Vector3d *normal;
			math::Vector3d *tangent;
			math::Vector2d *texcoord;
			
			unsigned int *indeces;

			unsigned int nVerteces;
			unsigned int nIndeces;
		};

		struct SM3Vertex
		{
			math::Vector3d vPosition;
			math::Vector2d vTexCoord;
			math::Vector3d vNormal;
			math::Vector3d vTangent;
			math::Vector3d vBinormal;
		};

		/*struct SMeshBuffer
		{
			math::Vector3d *position;
			math::Vector3d *normal;
			math::Vector2d *texcoord;
			
			unsigned int *indeces;

			unsigned int nVerteces;
			unsigned int nIndeces;

			SRegion *regionDataPtr;
			unsigned int nRegions;

			SBoneData *boneDataPtr;
			unsigned int nBones;

			SVertexBone *vertexBonePtr;

			SSequence *sequence;

			SAnimationData *translationAnimation;
			unsigned int nTranslationAnimation;

			SAnimationData *rotationAnimation;
			unsigned int nRotationAnimation;

			SAnimationTranslationData *translationData;
			SAnimationRotationData *rotationData;

			//_m3_SequenceBlock _sequenceBlock;

			math::Matrix4x4 *staticBonesMatrices;

			unsigned short *globalBonesIndecesList;

			std::string *animationSequencesNames;
		};*/
	
	public :
		static SMeshBuffer* ReadData(std::string value);
		static void Commit(SMeshBuffer* in_value, Core::CMesh *out_value);
		
};
};

#endif