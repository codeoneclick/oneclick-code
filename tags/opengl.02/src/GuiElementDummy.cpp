#include "GuiElementDummy.h"

#include "Window.h"

GuiElementDummy::GuiElementDummy()
{
	command = "none";
	
	x = 0;
	y = 0;

	width = 0;
	height = 0;
	visible = false;

	_textureFileName = "";
	_textureId = 0;
	name = "";

	_colors[0] = 1.0f; _colors[1] = 1.0f; _colors[2] = 1.0f;

	_slideState = SLIDE_NONE;
}

void GuiElementDummy::Update()
{
	if(!_textureId)
		_textureId = Resource::TextureContainer()->GetTexture(_textureFileName);

	switch(_slideState)
	{
		case SLIDE_RIGHT :
			if(x < 5)
				x += 1;
			else
				_slideState = SLIDE_NONE;
		break;
		case SLIDE_LEFT : 
			if(x > (Window::currentWidth - width - 5))
				x -= 1;
			else
				_slideState = SLIDE_NONE;
		break;
		case SLIDE_TOP : 
			if(y < 5)
				y += 1;
			else
				_slideState = SLIDE_NONE;
		break;
		case SLIDE_BOTTOM : 
			if(y > Window::currentHeight - height)
				y -= 1;
			else
				_slideState = SLIDE_NONE;
		break;
	}
}

void GuiElementDummy::Render()
{
	if(!_textureId) return;
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	glColor3f(_colors[0],_colors[1],_colors[2]);
	
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

void GuiElementDummy::Show(SlideState _state)
{
	_slideState = _state;

	switch(_slideState)
	{
		case SLIDE_RIGHT :
			x = 0 - width;
		break;
		case SLIDE_LEFT : 
			x = Window::currentWidth;
		break;
		case SLIDE_TOP : 
			y = 0 - height;
		break;
		case SLIDE_BOTTOM : 
			y = Window::currentHeight;
		break;
	}
}

void GuiElementDummy::Hide()
{
	visible = false;
	_slideState = SLIDE_NONE;
}