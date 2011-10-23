#ifndef _GUIELEMENTDUMMY_H_
#define _GUIELEMENTDUMMY_H_

#include <string>
#include "Resource.h"

enum SlideState { SLIDE_NONE = 0, SLIDE_RIGHT, SLIDE_LEFT, SLIDE_TOP, SLIDE_BOTTOM };

class GuiElementDummy
{
	protected:
		unsigned int _textureId;
		std::string  _textureFileName;
		float _colors[3];
		SlideState _slideState;

	public:
		GuiElementDummy();

		float x;
		float y;
		float width;
		float height;
		bool  visible;
		std::string command;
		std::string name;

		__forceinline void SetTexture(std::string value) { _textureFileName = value; }

		virtual bool CheckCollision(float mouseX, float mouseY, bool press) = 0;
		void Update();
		void Render();
		virtual void UpdateResizer() = 0;
		void Show(SlideState _state);
		void Hide();
};

#endif