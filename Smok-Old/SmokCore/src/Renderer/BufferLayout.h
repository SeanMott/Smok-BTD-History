//handles packing data for a vertex buffer

#ifndef BufferLayout_h
#define BufferLayout_h

#include "ShaderDataType.h"

#include <string>
#include <vector>

struct BufferElement
{
	std::string name;
	ShaderDataType type;
	bool isNormalized;
	uint32_t size;
	uint32_t offset;

	//Constructor
	BufferElement() {}
	BufferElement(ShaderDataType _type, const std::string& _name, const bool _isNormalized = false)
		:name(_name), type(_type), size(ShaderTypeSize(_type)), offset(0), isNormalized(_isNormalized)
	{}
};

//buffer layout
class BufferLayout
{
	//vars
private:
	std::vector<BufferElement> elements;

	uint32_t stride = 0;

	//methods
public:

	//constructor
	BufferLayout() {}
	BufferLayout(const std::initializer_list<BufferElement>& _elements)
		:elements(_elements)
	{
		CalStrideOffset();
	}

	//iteraters
	std::vector<BufferElement>::iterator begin() { return elements.begin(); }
	std::vector<BufferElement>::iterator end() { return elements.end(); }

	//returns elements
	inline const std::vector<BufferElement>& GetElements() const { return elements; }
	//returns stride
	inline uint32_t GetStride() { return stride; }

private:

	//calls the offset and stride
	void CalStrideOffset()
	{
		uint32_t offset = 0;
		stride = 0;

		for (auto& e : elements)
		{
			e.offset = offset;
			offset += e.size;
			stride += e.size;
		}
	}
};

#endif