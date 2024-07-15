//stores input events || Key Typed, Key Down, Key Release, Mouse Press, Mouse Release, Mouse Move, Mouse Scroll

#ifndef InputEvent_h
#define InputEvent_h

#include <vector>
#include <FastDelegate.h>

//key typed event
class KeyTypedEvent
{
	//vars
private:
	static std::vector<fastdelegate::DelegateMemento> methods;
	static fastdelegate::FastDelegate1<int> keyTyped;

	//methods
public:

	//adds a method || pass as a pointer
	template<typename ClassInstance, typename MethodName>
	static inline void AddMethod(ClassInstance classInstance, MethodName methodName)
	{
		keyTyped.bind(classInstance, methodName);
		methods.emplace_back(keyTyped.GetMemento());
	}

	//adds a method || pass as a pointer
	template<typename MethodName>
	static inline void AddMethod(MethodName methodName)
	{
		keyTyped.bind(methodName);
		methods.emplace_back(keyTyped.GetMemento());
	}

	//removes a method

	//calls all methods
	static inline void Call(int keycode)
	{
		if (methods.size() > 0)
		{
			for (unsigned int i = 0; i < methods.size(); i++)
			{
				keyTyped.SetMemento(methods[i]);
				keyTyped(keycode);
			}
		}
	}
};

//key pressed event
class KeyPressEvent
{
	//vars
private:
	static std::vector<fastdelegate::DelegateMemento> methods;
	static fastdelegate::FastDelegate2<int, bool> keyPress;

	//methods
public: 

	//adds a method || pass as a pointer
	template<typename ClassInstance, typename MethodName>
	static inline void AddMethod(ClassInstance classInstance, MethodName methodName)
	{
		keyPress.bind(classInstance, methodName);
		methods.emplace_back(keyPress.GetMemento());
	}

	//adds a method || pass as a pointer
	template<typename MethodName>
	static inline void AddMethod(MethodName methodName)
	{
		keyPress.bind(methodName);
		methods.emplace_back(keyPress.GetMemento());
	}

	//removes a method

	//calls all methods
	static inline void Call(int keycode, bool isRepeat)
	{
		if (methods.size() > 0)
		{
			for (unsigned int i = 0; i < methods.size(); i++)
			{
				keyPress.SetMemento(methods[i]);
				keyPress(keycode, isRepeat);
			}
		}
	}
};

//key released event
class KeyReleasedEvent
{
	//vars
private:
	static std::vector<fastdelegate::DelegateMemento> methods;
	static fastdelegate::FastDelegate1<int> keyRelease;

	//methods
public:

	//adds a method || pass as a pointer
	template<typename ClassInstance, typename MethodName>
	static inline void AddMethod(ClassInstance classInstance, MethodName methodName)
	{
		keyRelease.bind(classInstance, methodName);
		methods.emplace_back(keyRelease.GetMemento());
	}
	
	//adds a method || pass as a pointer
	template<typename MethodName>
	static inline void AddMethod(MethodName methodName)
	{
		keyRelease.bind(methodName);
		methods.emplace_back(keyRelease.GetMemento());
	}

	//removes a method

	//calls all methods
	static inline void Call(int keycode)
	{
		if (methods.size() > 0)
		{
			for (unsigned int i = 0; i < methods.size(); i++)
			{
				keyRelease.SetMemento(methods[i]);
				keyRelease(keycode);
			}
		}
	}

};

//mouse button down event
class MousePressEvent
{
	//vars
private:
	static std::vector<fastdelegate::DelegateMemento> methods;
	static fastdelegate::FastDelegate1<int, bool> mousePress;

	//methods
public:

	//adds a method || pass as a pointer
	template<typename ClassInstance, typename MethodName>
	static inline void AddMethod(ClassInstance classInstance, MethodName methodName)
	{
		mousePress.bind(classInstance, methodName);
		methods.emplace_back(mousePress.GetMemento());
	}
	
	//adds a method || pass as a pointer
	template<typename MethodName>
	static inline void AddMethod(MethodName methodName)
	{
		mousePress.bind(methodName);
		methods.emplace_back(mousePress.GetMemento());
	}

	//removes a method

	//calls all methods
	static inline void Call(int keycode)
	{
		if (methods.size() > 0)
		{
			for (unsigned int i = 0; i < methods.size(); i++)
			{
				mousePress.SetMemento(methods[i]);
				if (mousePress(keycode))
					break;
			}
		}
	}

};

//mouse button release event
class MouseReleasedEvent
{
	//vars
private:
	static std::vector<fastdelegate::DelegateMemento> methods;
	static fastdelegate::FastDelegate1<int, bool> mouseRelease;

	//methods
public:

	//adds a method || pass as a pointer
	template<typename ClassInstance, typename MethodName>
	static inline void AddMethod(ClassInstance classInstance, MethodName methodName)
	{
		mouseRelease.bind(classInstance, methodName);
		methods.emplace_back(mouseRelease.GetMemento());
	}
	
	//adds a method || pass as a pointer
	template<typename MethodName>
	static inline void AddMethod(MethodName methodName)
	{
		mouseRelease.bind(methodName);
		methods.emplace_back(mouseRelease.GetMemento());
	}

	//removes a method

	//calls all methods
	static inline void Call(int keycode)
	{
		if (methods.size() > 0)
		{
			for (unsigned int i = 0; i < methods.size(); i++)
			{
				mouseRelease.SetMemento(methods[i]);
				if (mouseRelease(keycode))
					break;
			}
		}
	}

};

//mouse move event
class MouseMoveEvent
{
	//vars
private:
	static std::vector<fastdelegate::DelegateMemento> methods;
	static fastdelegate::FastDelegate2<double, double> mouseMove;

	//methods
public:

	//adds a method || pass as a pointer
	template<typename ClassInstance, typename MethodName>
	static inline void AddMethod(ClassInstance classInstance, MethodName methodName)
	{
		mouseMove.bind(classInstance, methodName);
		methods.emplace_back(mouseMove.GetMemento());
	}
	
	//adds a method || pass as a pointer
	template<typename MethodName>
	static inline void AddMethod(MethodName methodName)
	{
		mouseMove.bind(methodName);
		methods.emplace_back(mouseMove.GetMemento());
	}

	//removes a method

	//calls all methods
	static inline void Call(double x, double y)
	{
		if (methods.size() > 0)
		{
			for (unsigned int i = 0; i < methods.size(); i++)
			{
				mouseMove.SetMemento(methods[i]);
				mouseMove(x, y);
			}
		}
	}

};

//mouse scroll event
class MouseScrollEvent
{
	// vars
private:
	static std::vector<fastdelegate::DelegateMemento> methods;
	static fastdelegate::FastDelegate2<double, double> mouseScroll;

	//methods
public:

	//adds a method || pass as a pointer
	template<typename ClassInstance, typename MethodName>
	static inline void AddMethod(ClassInstance instance, MethodName methodName)
	{
		mouseScroll.bind(instance, methodName);
		methods.emplace_back(mouseScroll.GetMemento());
	}

	//adds a method || pass as a pointer
	template<typename MethodName>
	static inline void AddMethod(MethodName methodName)
	{
		mouseScroll.bind(methodName);
		methods.emplace_back(mouseScroll.GetMemento());
	}

	//removes a method

	//calls all methods
	static inline void Call(double x, double y)
	{
		if (methods.size() > 0)
		{
			for (unsigned int i = 0; i < methods.size(); i++)
			{
				mouseScroll.SetMemento(methods[i]);
				mouseScroll(x, y);
			}
		}
	}

};

#endif