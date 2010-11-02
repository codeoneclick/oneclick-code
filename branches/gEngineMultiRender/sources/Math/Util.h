#ifndef UTIL_H
#define UTIL_H

#include "../Vector3d.h"

namespace Math
{
	class Util
	{
	public :
		struct SVertexTBN
		{
			math::Vector3d vNormal;
			math::Vector3d vTangent;
			math::Vector3d vBinormal;
		};
	public :
		static SVertexTBN* CalculateTBN(void *_v_data,unsigned int *_i_data, unsigned int _vertex_count,unsigned int _index_count, unsigned int _vertex_size)
		{
			 char* v_data = reinterpret_cast<char*>(_v_data);
			 SVertexTBN *dataTBN = new SVertexTBN[_vertex_count];
			 for(unsigned int i = 0; i < _index_count; i += 3)
			 {
				 math::Vector3d *p1 = new math::Vector3d();
				 memcpy(p1,v_data + _i_data[i] * _vertex_size,sizeof(math::Vector3d));
				 math::Vector2d *vUV1 = new math::Vector2d();
				 memcpy(vUV1,v_data + _i_data[i] * _vertex_size + sizeof(math::Vector3d),sizeof(math::Vector2d));

				 math::Vector3d *p2 = new math::Vector3d();
				 memcpy(p2,v_data + _i_data[i + 1] * _vertex_size, sizeof(math::Vector3d));
				 math::Vector2d *vUV2 = new math::Vector2d();
				 memcpy(vUV2,v_data + _i_data[i + 1] * _vertex_size + sizeof(math::Vector3d),sizeof(math::Vector2d));
				
				 math::Vector3d *p3 = new math::Vector3d();
				 memcpy(p3,v_data + _i_data[i + 2] * _vertex_size, sizeof(math::Vector3d));
				 math::Vector2d *vUV3 = new math::Vector2d();
				 memcpy(vUV3,v_data + _i_data[i + 2] * _vertex_size + sizeof(math::Vector3d),sizeof(math::Vector2d));

				 math::Vector3d v1 = (*p2) - (*p1);
				 math::Vector3d v2 = (*p3) - (*p1);

				 float fDeltaU1 = vUV2->x - vUV1->x;
				 float fDeltaU2 = vUV3->x - vUV1->x;
				 float fDeltaV1 = vUV2->y - vUV1->y;
				 float fDeltaV2 = vUV3->y - vUV1->y;

				 float div	=(fDeltaU1*fDeltaV2-fDeltaU2*fDeltaV1);

				 math::Vector3d normal = math::cross(v1,v2);
				 normal.normalize();

				 if(div != 0.0f)
				 {
					float fAreaMul2 = fabsf(fDeltaU1*fDeltaV2-fDeltaU2*fDeltaV1);

					float a =  fDeltaV2/div;
					float b	= -fDeltaV1/div;
					float c = -fDeltaU2/div;
					float d	=  fDeltaU1/div;
				
					math::Vector3d tangent = (v1*a + v2*b) * fAreaMul2;
					tangent.normalize();

					math::Vector3d binormal = (v1*c+v2*d) * fAreaMul2;
					binormal.normalize();

					dataTBN[_i_data[i + 1]].vNormal = normal;
					dataTBN[_i_data[i + 1]].vBinormal = binormal;
					dataTBN[_i_data[i + 1]].vTangent = tangent;
				 }
				 else
				 {
					math::Vector3d tangent = math::Vector3d(1.0f,0.0f,0.0f);
					math::Vector3d binormal = math::Vector3d(0.0f,1.0f,0.0f);

					dataTBN[_i_data[i + 1]].vNormal = normal;
					dataTBN[_i_data[i + 1]].vBinormal = binormal;
					dataTBN[_i_data[i + 1]].vTangent = tangent;
				 }

				 delete p1;
				 delete p2;
				 delete p3;

				 delete vUV1;
				 delete vUV2;
				 delete vUV3;
			}
			return dataTBN;
		}
	};
};

#endif
