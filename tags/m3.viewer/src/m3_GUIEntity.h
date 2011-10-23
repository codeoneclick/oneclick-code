#pragma once
#ifndef _M3_GUIENTITY_H_
#define _M3_GUIENTITY_H_

#define BUTTONPRESSDELAY_FPS 15

#include <string>
#include "m3_Resource.h"

enum BtnState { BUTTON_NONE = 0, BUTTON_ON_MOUSE, BUTTON_PRESS, BUTTON_DISABLE }; 

class m3_GUIEntity
{
	private:
		GLuint _textureId;
		unsigned int _pressButtonDelay;
		BtnState _pressButtonFlag;
		std::string _textureFileName;
	public:
		
		float x;
		float y;
		
		float width;
		float height;
		
		bool  visible;

		std::string command;

		m3_GUIEntity();

		__forceinline void SetPosition(float _x, float _y) { x = _x; y = _y; }
		__forceinline void SetSize(float _width, float _height) { width = _width; height = _height; }
		__forceinline void SetVisible(bool _visible) { visible = _visible; }	
		__forceinline void SetCommand(std::string _command) { command = _command; }
		__forceinline void SetTexture(std::string _textureName) { _textureFileName = _textureName; }

		bool CheckCollision(float mouseX, float mouseY, bool press);
		void Update();
		void Render();

};
#endif