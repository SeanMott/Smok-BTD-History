#include <smpch.h>
#include "ScriptEvents.h"

std::vector<fastdelegate::DelegateMemento> ScriptUpdateEvent::methods;
std::vector<fastdelegate::DelegateMemento> ScriptFixedUpdateEvent::methods;
std::vector<fastdelegate::DelegateMemento> ScriptStartEvent::methods;
std::vector<fastdelegate::DelegateMemento> ScriptEndEvent::methods;

fastdelegate::FastDelegate1<float> ScriptUpdateEvent::update;
fastdelegate::FastDelegate1<float> ScriptFixedUpdateEvent::fixedUpdate;
fastdelegate::FastDelegate0<void> ScriptStartEvent::start;
fastdelegate::FastDelegate0<void> ScriptEndEvent::end;