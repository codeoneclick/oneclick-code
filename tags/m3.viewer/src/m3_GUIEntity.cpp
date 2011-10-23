#include "m3_GUIEntity.h"

m3_GUIEntity::m3_GUIEntity()
{
	command = "none";
	
	x = 0;
	y = 0;

	width = 0;
	height = 0;

	visible = false;

	_textureFileName = "";

	_textureId = 0;

	_pressButtonDelay = BUTTONPRESSDELAY_FPS;
	_pressButtonFlag = BUTTON_NONE;
}

void m3_GUIEntity::Update()
{
	if(!_textureId)
		_textureId = m3_Resource::TextureContainer()->GetTexture(_textureFileName);

	switch(_pressButtonFlag)
	{
		case BUTTON_ON_MOUSE:
			_pressButtonDelay--;
			if(_pressButtonDelay == 0)
				_pressButtonFlag = BUTTON_NONE;
		break;
		case BUTTON_PRESS:
			_pressButtonDelay--;
			if(_pressButtonDelay == 0)
				_pressButtonFlag = BUTTON_NONE;
		break;
	}
}

void m3_GUIEntity::Render()
{
	if(!_textureId) return;
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	switch(_pressButtonFlag)
	{
		case BUTTON_NONE:
			glColor3f(1.0f,1.0f,1.0f);
		break;
		case BUTTON_PRESS:
			glColor3f(0.1f,0.5f,0.1f);
		break;
		case BUTTON_ON_MOUSE:
			glColor3f(0.5f,0.1f,0.1f);
		break;
		case BUTTON_DISABLE:
			glColor3f(0.2f,0.2f,0.2f);
		break;
	}

	glBindTexture(GL_TEXTURE_2D,_textureId);	
	glBegin(GL_QUADS);	
		glTexCoord2f(0,0);		
		glVertex2f( x, y );		
		glTexCoord2f(0,1);	
		glVertex2f( x, y + height );	
		glTexCoord2f(1,1);			
		glVertex2f( x + width, y + height );
		glTexCoord2f(1,0);		
		glVertex2f( x + width, y);								
	glEnd();
	glColor3f(1.0f,1.0f,1.0f);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}

bool m3_GUIEntity::CheckCollision(float mouseX, float mouseY, bool press)
{
	if(mouseX > x)
		if(mouseX < (x + width))
			if(mouseY > y)
				if(mouseY < (y + height))
				{
					if(press)
					{
						_pressButtonFlag = BUTTON_PRESS;
						_pressButtonDelay = BUTTONPRESSDELAY_FPS;
						return true;
					}

					if(!press && _pressButtonFlag != BUTTON_PRESS)
					{
						_pressButtonFlag = BUTTON_ON_MOUSE;
						_pressButtonDelay = BUTTONPRESSDELAY_FPS/BUTTONPRESSDELAY_FPS;
						return false;
					}
				}

	return false;
}