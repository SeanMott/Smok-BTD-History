//the base ImGUI context

#ifndef ImGUIContext_h
#define ImGUIContext_h

class ImGUIContext
{
public:

	virtual ~ImGUIContext() {}

	//creates the context
	static ImGUIContext* Create();

	//inits the context
	virtual void Init() = 0;
	//destroys the context
	virtual void Destroy() = 0;

	//creates a new frame
	virtual void NewFrame() = 0;
	//renders the data
	virtual void Render() = 0;
};

#endif