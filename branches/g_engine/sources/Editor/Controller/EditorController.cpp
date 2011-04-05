#include "EditorController.h"
#include "../../Core/Input.h"

using namespace Enviroment;

EditorController::EditorController(CDummy* _landscape)
{
	m_landscape = _landscape;

	std::vector<SResource> brushResourceContainer;
	SResource brushResource;
	brushResource.m_ShaderFile = "Content\\shaders\\brush";
	brushResourceContainer.push_back(brushResource);
	m_brush = new CBrush((CLandscape*)m_landscape);
	m_brush->Load(brushResourceContainer);

	m_IncValue = 2.7f;
	m_DecValue = -2.7f;
}

void EditorController::KeyboardControl()
{
	if(core::Input::keys[KEY_EDIT_HEIGHT_DOWN])
	{
		m_editType = E_LANDSCAPE_HEIGHT;
		m_editHeightDir = E_LANDSCAPE_HEIGHT_DOWN;
		EditHeight();
	}

	if(core::Input::keys[KEY_EDIT_HEIGHT_UP])
	{
		m_editType = E_LANDSCAPE_HEIGHT;
		m_editHeightDir = E_LANDSCAPE_HEIGHT_UP;
		EditHeight();
	}

	if(core::Input::keys[KEY_EDIT_SMOOTH_TRIGER])
	{
		if(m_editSmoothing == E_SMOOTH)
			m_editSmoothing = E_FLAT;
		else
			m_editSmoothing = E_SMOOTH;
	}
}

void EditorController::Update()
{
	KeyboardControl();
}

void EditorController::EditHeight()
{
	float** landscapeData = ((CLandscape*)m_landscape)->GetHeightData();
	unsigned int landscapeWidth = ((CLandscape*)m_landscape)->GetWidth();
	unsigned int landscapeHeight = ((CLandscape*)m_landscape)->GetHeight();

	int minIndX = (int)floor(m_vWorkingPosition.x - m_fWorkingArea);
	int minIndZ = (int)floor(m_vWorkingPosition.z - m_fWorkingArea);
	int maxIndX = (int)floor(m_vWorkingPosition.x + m_fWorkingArea);
	int maxIndZ = (int)floor(m_vWorkingPosition.z + m_fWorkingArea);

	for (int x = minIndX; x < maxIndX; x++)
	{
		 for (int z = minIndZ; z < maxIndZ; z++) 
		 {
                if((x <= 0) || (z <= 0) || x >= landscapeWidth || z >= landscapeHeight) 
					continue;

				float distance = math::Vector3d(x - m_vWorkingPosition.x, 0.0f, z - m_vWorkingPosition.z).length();

                if (distance > m_fWorkingArea)
                    continue;

                float riseCoeff = distance / m_fWorkingArea;
                riseCoeff = 1.0f - riseCoeff * riseCoeff;
                float deltaHeight = 0; 
				if(m_editHeightDir == E_LANDSCAPE_HEIGHT_DOWN)
					deltaHeight = m_DecValue * riseCoeff;
				if(m_editHeightDir == E_LANDSCAPE_HEIGHT_UP)
					deltaHeight = m_IncValue * riseCoeff;
                float height =  landscapeData[x][z] + deltaHeight;
                height = floor(height + 0.5f);
				landscapeData[x][z] = height;
         }
	}

	if(m_editSmoothing == E_SMOOTH)
	{
		float middleHeight = 0;
		for (int x = minIndX; x < maxIndX; x++)
		{
                for (int z = minIndZ; z < maxIndZ; z++) 
				{
                        if((x <= 0) || (z <= 0) || x >= landscapeWidth || z >= landscapeHeight) 
							continue;

                        float distance = math::Vector3d(x - m_vWorkingPosition.x, 0.0f, z - m_vWorkingPosition.z).length();
                        float coeff = m_fWorkingArea - distance;

                        float height = landscapeData[x][z];
                        middleHeight = 0;
                        if (coeff > 0) 
						{
                            middleHeight = height;
                            middleHeight += landscapeData[x-1][z];
                            middleHeight += landscapeData[x+1][z];
                            middleHeight += landscapeData[x-1][z-1];
                            middleHeight += landscapeData[x][z-1];
                            middleHeight += landscapeData[x+1][z-1];
                            middleHeight += landscapeData[x-1][z+1];
                            middleHeight += landscapeData[x][z+1];
                            middleHeight += landscapeData[x+1][z+1];
                            height = middleHeight / 9.0f;
                            height = floor(height + 0.5f);
                        }
                        landscapeData[x][z] = height;
                }
		}
	}

	((CLandscape*)m_landscape)->RefreshVB(0);
}