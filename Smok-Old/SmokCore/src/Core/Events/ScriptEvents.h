//the events triggered for events

#ifndef ScriptEvents_h
#define ScriptEvents_h

#include <vector>
#include <FastDelegate.h>

//triggers Update events for scripts
class ScriptUpdateEvent
{
	//vars
private:
	static std::vector<fastdelegate::DelegateMemento> methods;
	static fastdelegate::FastDelegate1<float> update;

	//methods
public:

	//adds a method || pass as a pointer
	template<typename ClassInstance, typename MethodName>
	static inline void AddMethod(ClassInstance classInstance, MethodName methodName)
	{
		update.bind(classInstance, methodName);
		methods.emplace_back(update.GetMemento());
	}

	//adds a method || pass as a pointer
	template<typename MethodName>
	static inline void AddMethod(MethodName methodName)
	{
		update.bind(methodName);
		methods.emplace_back(update.GetMemento());
	}

	//removes a method

	//calls all methods
	static inline void Call(float deltaTime)
	{
		if (methods.size() > 0)
		{
			for (unsigned int i = 0; i < methods.size(); i++)
			{
				update.SetMemento(methods[i]);
				update(deltaTime);
			}
		}
	}
};

//triggers Fixed Update events for scripts
class ScriptFixedUpdateEvent
{
	//vars
private:
	static std::vector<fastdelegate::DelegateMemento> methods;
	static fastdelegate::FastDelegate1<float> fixedUpdate;

	//methods
public:

	//adds a method || pass as a pointer
	template<typename ClassInstance, typename MethodName>
	static inline void AddMethod(ClassInstance classInstance, MethodName methodName)
	{
		fixedUpdate.bind(classInstance, methodName);
		methods.emplace_back(fixedUpdate.GetMemento());
	}

	//adds a method || pass as a pointer
	template<typename MethodName>
	static inline void AddMethod(MethodName methodName)
	{
		fixedUpdate.bind(methodName);
		methods.emplace_back(fixedUpdate.GetMemento());
	}

	//removes a method

	//calls all methods
	static inline void Call(float fixedDeltaTime)
	{
		if (methods.size() > 0)
		{
			for (unsigned int i = 0; i < methods.size(); i++)
			{
				fixedUpdate.SetMemento(methods[i]);
				fixedUpdate(fixedDeltaTime);
			}
		}
	}
};

//triggers start events for scripts
class ScriptStartEvent
{
	//vars
private:
	static std::vector<fastdelegate::DelegateMemento> methods;
	static fastdelegate::FastDelegate0<void> start;

	//methods
public:

	//adds a method || pass as a pointer
	template<typename ClassInstance, typename MethodName>
	static inline void AddMethod(ClassInstance classInstance, MethodName methodName)
	{
		start.bind(classInstance, methodName);
		methods.emplace_back(start.GetMemento());
	}

	//adds a method || pass as a pointer
	template<typename MethodName>
	static inline void AddMethod(MethodName methodName)
	{
		start.bind(methodName);
		methods.emplace_back(start.GetMemento());
	}

	//removes a method

	//calls all methods
	static inline void Call()
	{
		if (methods.size() > 0)
		{
			for (unsigned int i = 0; i < methods.size(); i++)
			{
				start.SetMemento(methods[i]);
				start();
			}
		}
	}
};

//triggers end events for scripts
class ScriptEndEvent
{
	//vars
private:
	static std::vector<fastdelegate::DelegateMemento> methods;
	static fastdelegate::FastDelegate0<void> end;

	//methods
public:

	//adds a method || pass as a pointer
	template<typename ClassInstance, typename MethodName>
	static inline void AddMethod(ClassInstance classInstance, MethodName methodName)
	{
		end.bind(classInstance, methodName);
		methods.emplace_back(end.GetMemento());
	}

	//adds a method || pass as a pointer
	template<typename MethodName>
	static inline void AddMethod(MethodName methodName)
	{
		end.bind(methodName);
		methods.emplace_back(end.GetMemento());
	}

	//removes a method

	//calls all methods
	static inline void Call()
	{
		if (methods.size() > 0)
		{
			for (unsigned int i = 0; i < methods.size(); i++)
			{
				end.SetMemento(methods[i]);
				end();
			}
		}
	}
};

#endif