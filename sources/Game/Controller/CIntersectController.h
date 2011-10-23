#ifndef _CINTERSECTCONTROLLER_H_
#define _CINTERSECTCONTROLLER_H_

#include "../../Math/Matrix4x4.h"
#include "../../Math/Vector3d.h"

#include <stdlib.h>
#include <string>
#include <map>

namespace Enviroment
{
	class CIntersectController
	{
		public :

			struct SIntersectBlock
			{
				unsigned int    nIndeces;
				math::Vector3d* vertexData;
				unsigned int*   indexData;
			}; 

			struct SIntersectResult
			{
				bool isIntersected;
				math::Vector3d intersectPoint;
			};

	private :
		std::map<std::string,SIntersectBlock*> m_intesectBlockList;
		std::map<std::string,SIntersectResult*> m_intesectResultList;
	public  :
		CIntersectController();
		void AddIntersectBlock(std::string _name, SIntersectBlock* _block);
		SIntersectResult* GetIntersectResult(std::string _name);
		void Update();
		math::Vector3d m_intersectPoint;
	};
};

#endif