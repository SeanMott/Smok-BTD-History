#include <smpch.h>
#include "InputEvents.h"

std::vector<fastdelegate::DelegateMemento> KeyPressEvent::methods;
std::vector<fastdelegate::DelegateMemento> KeyReleasedEvent::methods;
std::vector<fastdelegate::DelegateMemento> KeyTypedEvent::methods;
std::vector<fastdelegate::DelegateMemento> MousePressEvent::methods;
std::vector<fastdelegate::DelegateMemento> MouseReleasedEvent::methods;
std::vector<fastdelegate::DelegateMemento> MouseMoveEvent::methods;
std::vector<fastdelegate::DelegateMemento> MouseScrollEvent::methods;

fastdelegate::FastDelegate2<int, bool> KeyPressEvent::keyPress;
fastdelegate::FastDelegate1<int> KeyReleasedEvent::keyRelease;
fastdelegate::FastDelegate1<int> KeyTypedEvent::keyTyped;
fastdelegate::FastDelegate1<int, bool> MousePressEvent::mousePress;
fastdelegate::FastDelegate1<int, bool> MouseReleasedEvent::mouseRelease;
fastdelegate::FastDelegate2<double, double> MouseMoveEvent::mouseMove;
fastdelegate::FastDelegate2<double, double> MouseScrollEvent::mouseScroll;