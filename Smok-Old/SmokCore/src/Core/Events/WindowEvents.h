//stores window events || Window Resize, Window Close

#ifndef WindowEvents_h
#define WindowEvents_h

#include <vector>
#include <FastDelegate.h>

//window close event
class WindowResizeEvent
{
	//vars
private:
	static std::vector<fastdelegate::DelegateMemento> methods;
	static fastdelegate::FastDelegate2<unsigned int, unsigned int> windowResize;

	//methods
public:

	//adds a method || pass as a pointer
	template<typename ClassInstance, typename MethodName>
	static inline void AddMethod(ClassInstance classInstance, MethodName methodName)
	{
		windowResize.bind(classInstance, methodName);
		methods.emplace_back(windowResize.GetMemento());
	}

	//adds a method || pass as a pointer
	template<typename MethodName>
	static inline void AddMethod(MethodName methodName)
	{
		windowResize.bind(methodName);
		methods.emplace_back(windowResize.GetMemento());
	}

	//removes a method

	//calls all methods
	static inline void Call(unsigned int width, unsigned int height)
	{
		if (methods.size() > 0)
		{
			for (unsigned int i = 0; i < methods.size(); i++)
			{
				windowResize.SetMemento(methods[i]);
				windowResize(width, height);
			}
		}
	}
};

//window resize event
class WindowCloseEvent
{
	//vars
private:
	static std::vector<fastdelegate::DelegateMemento> methods;
	static fastdelegate::FastDelegate0<> windowClose;

	//methods
public:

	//adds a method || pass as a pointer
	template<typename ClassInstance, typename MethodName>
	static inline void AddMethod(ClassInstance classInstance, MethodName methodName)
	{
		windowClose.bind(classInstance, methodName);
		methods.emplace_back(windowClose.GetMemento());
	}

	/*adds a method || pass as a pointer
	template<typename MethodName>
	static inline void AddMethod(MethodName methodName)
	{
		windowClose.bind(methodName);
		methods.emplace_back(windowClose.GetMemento());
	}*/

	//removes a method

	//calls all methods
	static inline void Call()
	{
		if (methods.size() > 0)
		{
			for (unsigned int i = 0; i < methods.size(); i++)
			{
				windowClose.SetMemento(methods[i]);
				windowClose();
			}
		}
	}
};

#endif