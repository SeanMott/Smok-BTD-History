//base Texture

#ifndef Texture_h
#define Texture_h

#include <string>

class Texture
{
public:

	virtual ~Texture() {}

	//creates a texture
	static Texture* Create(const std::string& filePath);

	//gets the texture's id
	virtual unsigned int GetID() = 0;

	//destroys a texture
	virtual void Destroy() = 0;

	//binds a texture
	virtual void Bind(unsigned int slot = 0) = 0;
	//unbinds a texture
	virtual void UnBind() = 0;

	//gets the height
	virtual int GetHeight() = 0;
	//gets the width
	virtual int GetWidth() = 0;
};

#endif