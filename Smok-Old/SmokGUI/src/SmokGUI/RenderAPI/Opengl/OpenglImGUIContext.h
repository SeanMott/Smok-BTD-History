//Opengl implementation of ImGUI

#ifndef OpengImGUIContext_h
#define OpengImGUIContext_h

#include <SmokGUI\Core\ImGUIContext.h>

class OpenglImGUIContext : public ImGUIContext
{
public:

	OpenglImGUIContext() {}
	virtual ~OpenglImGUIContext() { Destroy(); }

	// Inherited via ImGUIContext
	void Init() override;

	void Destroy() override;

	void NewFrame() override;

	void Render() override;

};

#endif