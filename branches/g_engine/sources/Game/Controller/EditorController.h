#ifndef EDITORCONTROLLER_H
#define EDITORCONTROLLER_H

#include "../Enviroment/Landscape.h"
#include "../Enviroment/EditBrush.h"
#include <stdlib.h>
#include <string>
#include <map>

#define KEY_EDIT_HEIGHT_UP 88
#define KEY_EDIT_HEIGHT_DOWN 90
#define KEY_EDIT_SMOOTH_TRIGER 67

namespace Enviroment
{
class EditorController
{
public :
	enum EDIT_TYPE { E_LANDSCAPE_HEIGHT = 0, E_LANDSCAPE_TEXTURE };
private :
	enum EDIT_HEIGHT_DIR { E_LANDSCAPE_HEIGHT_UP = 0,  E_LANDSCAPE_HEIGHT_DOWN };
	enum EDIT_HEIGHT_SMOOTHING { E_FLAT = 0, E_SMOOTH };
private :
	CDummy* m_landscape;
	math::Vector3d m_vWorkingPosition;
	float m_fWorkingArea;

	void KeyboardControl();

	void EditHeight();
	void EditTexture();

	float m_IncValue;
	float m_DecValue;

	EDIT_TYPE m_editType;
	EDIT_HEIGHT_DIR m_editHeightDir;
	EDIT_HEIGHT_SMOOTHING m_editSmoothing;

	CDummy *m_brush;

public :
	EditorController(CDummy* _landscape);
	inline void SetWorkingPosition(math::Vector3d _position) { m_vWorkingPosition = _position; };
	inline void SetWorkingArea(float _area) { m_fWorkingArea = _area; };
	inline void SetIncValue(float _value) { m_IncValue = _value; };
	inline void SetDecValue(float _value) { m_DecValue = _value; };
	inline void SetEditType(EDIT_TYPE _type) { m_editType = _type; };
	inline CDummy* GetBrush() { return m_brush; };
	void Update();
};
};

#endif