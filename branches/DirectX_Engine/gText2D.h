#pragma once
class gText2D{
private :
	LPD3DXFONT font;
	RECT font_rectangle;

	DWORD text_align;

	D3DXVECTOR3 color;

	char text[1024];
public : 
	D3DXVECTOR2 Position;

public :
	gText2D();
	~gText2D();

	void SetText(std::string text);
	void SetText(int text,D3DXVECTOR3 pick);
	void SetText(float text);
	void SetText(double text);
	__forceinline void SetColor(D3DXVECTOR3 color){ this->color = color; }
	void Update();
	void Render();
	void SetTextAlign(TextAlignFlag flag);
};

gText2D::gText2D(){
	this->Position = D3DXVECTOR2(0.0f,0.0f);
	this->color = D3DXVECTOR3(1.0f,1.0f,0.0f);
	this->text_align = 0;
	D3DXCreateFont(gDevice::device, 24, 24, 0, 1, TRUE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE, "Arial", &this->font);
    font_rectangle.top = 0;
    font_rectangle.left = 0;
	font_rectangle.right = gWindow::wndWidth;
	font_rectangle.bottom = gWindow::wndHeight;
}

gText2D::~gText2D(){
}

void gText2D::SetText(std::string text){
	if(text.length() <= 1024)
		for(int index = 0; index < text.length(); ++index){
			this->text[index] = text[index];
		}
}

void gText2D::SetTextAlign(TextAlignFlag flag){
	switch(flag){
		case T_LEFT:
			this->text_align = DT_LEFT;
			break;
		case T_RIGHT:
			this->text_align = DT_RIGHT;
			break;
		case T_TOP:
			this->text_align = DT_TOP;
			break;
		case T_BOTTOM:
			this->text_align = DT_BOTTOM;
			break;
		case T_VERTICAL_CENTER:
			this->text_align = DT_VCENTER;
			break;
		case T_HORIZONTAL_CENTER:
			this->text_align = DT_CENTER;
			break;
	}
}

void gText2D::SetText(int text,D3DXVECTOR3 pick){
	
	sprintf_s(this->text,"%i FPS ( %f ,%i ,%i )",text,pick.x,(int)pick.y,(int)pick.z);
}

void gText2D::SetText(float text){
	sprintf_s(this->text,"%f",text);
}

void gText2D::SetText(double text){
	sprintf_s(this->text,"%d",text);
}

void gText2D::Update(){
	this->font_rectangle.top = this->Position.y;
	this->font_rectangle.left = this->Position.x;
}

void gText2D::Render(){
	this->font->DrawText(NULL,this->text, -1, &this->font_rectangle,this->text_align , D3DXCOLOR(this->color.x,this->color.y,this->color.z,1.0f));
}