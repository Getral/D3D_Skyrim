#pragma once
class InvenUI
{
public:
	InvenUI();
	~InvenUI();

	void Update();
	void Render();
	void GUIRender();

private:
	Quad* frame;
};

