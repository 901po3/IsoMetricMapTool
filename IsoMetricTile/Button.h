#pragma once
#include"Object.h"

class Button : public Object
{
private:
	ButtonStruct CurButton;
	bool m_bPressed;
public:
	Button();
	void dealloc() {}

	ButtonType GetCurButton() {return CurButton.typeName;}
	void SetCurButton(ButtonStruct bs) { CurButton = bs;}
	bool GetPressed() {return m_bPressed;}
	void SetPressed(bool pressed) {m_bPressed = pressed;}


	static Button *create()
	{
		Button *button = new Button();
		return button;
	}
	void render();
	void update(float dt);
};