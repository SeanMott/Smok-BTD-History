//stores the render API

#ifndef RenderAPI_h
#define RenderAPI_h

enum class RenderAPIType
{
	Opengl,
	Vulkin,
	DirectX,
	Metal
};

class RenderAPI
{
	//vars
private:

	static RenderAPIType type;

	//methods
public:

	//gets API
	static inline RenderAPIType GetAPI() { return type; }
	//sets API
	static inline void SetAPI(RenderAPIType t) { type = t; }
};

#endif