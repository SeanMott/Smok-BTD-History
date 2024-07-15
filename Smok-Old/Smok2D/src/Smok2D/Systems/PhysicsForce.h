//allows Physics based objects to move

#ifndef PhysicsForce_h
#define PhysicsForce_h

class PhysicsForce
{
	//vars
private:

	float gravity = 0.0f;

	//methods
public:

	//inits the System
	static void Init();
	//shutsdown the system
	static void Shutdown();

	//performs force cals
	static void ApplyForce();
};

#endif