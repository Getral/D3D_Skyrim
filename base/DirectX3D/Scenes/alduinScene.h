#pragma once
class alduinScene : public Scene
{
public:

	alduinScene();
	~alduinScene();

	virtual void Update() override;

	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUIRender() override;


private:

	alduin* aldu;

};

