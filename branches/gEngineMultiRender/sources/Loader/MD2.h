#ifndef _MD2_H_
#define _MD2_H_

#include <windows.h>
#include <string>
#include <vector>
#include "Mesh.h"
#include "Math/Util.h"

namespace Loader
{
class CMD2
{
public :
	static S3DSFile* ReadData(std::string value);
	static void Commit(S3DSFile *in_value, Core::CMesh *out_value);
};
};

#endif