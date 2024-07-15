(This project has been abandoned, as all the old Bytes The Dust, Smok, and Hologram code is being condensed and cleaned up. All will fall under the Bytes The Dust SDK)

# Smok
Smok (Polish for dragon, pronounced like smoke) is a game engine for 3D and 2D with ECS. The engine is being created as a learning experience.

# Project Overview
The Smok engine is made of four parts SmokCore, SmokGUI, Smok2D, and Smok3D.

- SmokCore

SmokCore is the heart of the engine, it holds the Platform and Render API specific code. It also manages the engine, and input events. When making a new module you need to link to this lib.

- SmokGUI

SmokGUI has all the GUI based componets and systems. This is buttons, text, bars, ect.

- Smok2D

Smok2D has all the 2D based componets and systems. This is sprite renderer, 2D physics, tile map, ect.

- Smok3D

Smok3D has all the 3D based componets and systems. This is mesh renderer, 3D physics, particals, ect.

# Scripts, Components, and Systems

Smok has three ways to interact with the engine, Systems, Components, and Scripts. Systems are hooked into engine events and use the Components that are attachted to entities. Scripts are created as pointers in a scene, and have specal events that only trigger for Scripts. They are similar to Unreal, Unity, or Godot scripts, they don't require inhereting from a class. The only thing you have to make sure is that the methods hooked into a event matchs the return and paramater type. Otherwise you can change the name of the method and the paramaters.


# Libraries
- [GLM - Math](http://glm.g-truc.net/0.9.8/index.html)
- [GLFW - Input](https://www.glfw.org/)
- [Glad - Opengl](https://github.com/Dav1dde/glad)
- [ImGUI - GUI](https://github.com/ocornut/imgui)
- [stb - Image Loading](https://github.com/nothings/stb)
- [entt - ECS](https://github.com/skypjack/entt)
- [Fast Delegate - C++ Delegates](https://www.codeproject.com/Articles/7150/Member-Function-Pointers-and-the-Fastest-Possible)

# To Do

- Docs
- Batch rendering
- Binary scene and prefab file instead of text
- Proper API for prefab loading and saving instead of load scene
- Sound asset load and play
- Text component
- Button component
- Tilemap loading
- asset file list loading
