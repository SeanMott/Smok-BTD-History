#include <smpch.h>
#include "EngineEvents.h"

std::vector<fastdelegate::DelegateMemento> ECSSystemEvent::methods;
std::vector<fastdelegate::DelegateMemento> ECSGUIRenderEvent::methods;
std::vector<fastdelegate::DelegateMemento> ECSUpdateEvent::methods;
std::vector<fastdelegate::DelegateMemento> ECSFixedUpdateEvent::methods;

fastdelegate::FastDelegate0<void> ECSSystemEvent::system;
fastdelegate::FastDelegate0<void> ECSGUIRenderEvent::system;
fastdelegate::FastDelegate1<float> ECSFixedUpdateEvent::fixedUpdate;
fastdelegate::FastDelegate1<float> ECSUpdateEvent::update;

//the begin and end of the Smok GUI Renderer
fastdelegate::FastDelegate0<void> ECSGUIRenderEvent::begin;
fastdelegate::FastDelegate0<void> ECSGUIRenderEvent::end;