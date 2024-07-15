#include <smpch.h>
#include "WindowEvents.h"

std::vector<fastdelegate::DelegateMemento> WindowResizeEvent::methods;
std::vector<fastdelegate::DelegateMemento> WindowCloseEvent::methods;

fastdelegate::FastDelegate2<unsigned int, unsigned int> WindowResizeEvent::windowResize;
fastdelegate::FastDelegate0<> WindowCloseEvent::windowClose;