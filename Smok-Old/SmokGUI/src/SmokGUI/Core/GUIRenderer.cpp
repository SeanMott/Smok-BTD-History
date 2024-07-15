#include "GUIRenderer.h"

#include <imgui.h>
#include <SmokGUI\Core\ImGUIContext.h>

#include <Renderer\Display.h>

#include <Core\Keycodes.h>
#include <Core\Events\InputEvents.h>
#include <Core\Events\EngineEvents.h>
#include <Core\Events\WindowEvents.h>
//#include <Core\Events\ScriptEvents.h>

#include <SmokGUI\ImGUIBuild.h>

ImGUIContext* GUIRenderer::context = nullptr;
bool GUIRenderer::flags[(int)GUIFlags::GUIFlagsCount]; //the flags for GUI

//inits the renderer
void GUIRenderer::Init()
{
#ifdef DISABLE_SMOK_GUI
    return;
#endif

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    SetStyle();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    UpdateImGUIFlags();

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    context = ImGUIContext::Create();
    context->Init();

    OnResize(100, 100);

    //set events
    KeyPressEvent::AddMethod(&GUIRenderer::KeyPressed);
    KeyTypedEvent::AddMethod(&GUIRenderer::KeyTyped);
    KeyReleasedEvent::AddMethod(&GUIRenderer::KeyReleased);
    MousePressEvent::AddMethod(&GUIRenderer::MousePressed);
    MouseReleasedEvent::AddMethod(&GUIRenderer::MouseReleased);
    MouseMoveEvent::AddMethod(&GUIRenderer::MouseMove);
    MouseScrollEvent::AddMethod(&GUIRenderer::MouseScroll);
    //WindowResizeEvent::AddMethod(&GUIRenderer::OnResize);
    ECSUpdateEvent::AddMethod(&GUIRenderer::UpdateDeltaTime);

    ECSGUIRenderEvent::RendererBind(&GUIRenderer::Begin, &GUIRenderer::End);
}

//destroys the renderer
void GUIRenderer::Shutdown()
{
#ifdef DISABLE_SMOK_GUI
    return;
#endif

    context->Destroy();
}

//updates the GUI flags for ImGUI
void GUIRenderer::UpdateImGUIFlags()
{
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    if (GetFlagState(GUIFlags::Keyboard))
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; //enable keyboard
    if (GetFlagState(GUIFlags::GamePad))
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; //enable game pad
    if (GetFlagState(GUIFlags::Docking))
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; //enable docking
    if (GetFlagState(GUIFlags::ViewPort))
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; //enable multi viewport / windows
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons; //disable task bar icons
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge; //disable viewport merging
}

//updates the style
void GUIRenderer::SetStyle(GUIStyle style)
{
    if (style == GUIStyle::Dark)
        ImGui::StyleColorsDark();
    else if (style == GUIStyle::Light)
        ImGui::StyleColorsLight();
    else
        ImGui::StyleColorsClassic();
}

//starts a section of render code
void GUIRenderer::Begin()
{
#ifdef DISABLE_SMOK_GUI
    return;
#endif

    context->NewFrame();

    //load docking
    if (GetFlagState(GUIFlags::Docking))
    {
        static bool opt_fullscreen_persistant = true;
        bool opt_fullscreen = opt_fullscreen_persistant;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->GetWorkPos());
            ImGui::SetNextWindowSize(viewport->GetWorkSize());
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background 
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace", nullptr, window_flags);
        ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
    }
}

//ends a section of render code
void GUIRenderer::End()
{
#ifdef DISABLE_SMOK_GUI
    return;
#endif

    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)DisplayI.GetScreenWidth(), (float)DisplayI.GetScreenHeight());
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

    //load docking
    if (GetFlagState(GUIFlags::Docking))
        ImGui::End();

        context->Render();

    //renders seprate window instances
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGUIPlatformContextType platformContext = ImGUIPlatformGetContext;
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        ImGUIPlatformMakeContext(platformContext);
    }
}

//-----------------------EVENTS-----------------------//
void GUIRenderer::KeyPressed(int key, bool isRepeat)
{
    ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[key] = true;

    io.KeyCtrl = io.KeysDown[SMOK_KEY_LEFT_CONTROL] || io.KeysDown[SMOK_KEY_RIGHT_CONTROL];
    io.KeyShift = io.KeysDown[SMOK_KEY_LEFT_SHIFT] || io.KeysDown[SMOK_KEY_RIGHT_SHIFT];
    io.KeyAlt = io.KeysDown[SMOK_KEY_LEFT_ALT] || io.KeysDown[SMOK_KEY_RIGHT_ALT];
    io.KeySuper = io.KeysDown[SMOK_KEY_LEFT_SUPER] || io.KeysDown[SMOK_KEY_RIGHT_SUPER];
}

void GUIRenderer::KeyReleased(int key)
{
    ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[key] = false;
}

void GUIRenderer::KeyTyped(int key)
{
    ImGuiIO& io = ImGui::GetIO();
    if (key > 0 && key < 0x10000)
        io.AddInputCharacter((unsigned short)key);
}

bool GUIRenderer::MousePressed(int button)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[button] = true;

    return false;
}

bool GUIRenderer::MouseReleased(int button)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[button] = false;

    return false;
}

void GUIRenderer::MouseMove(double xPos, double yPos)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(xPos, yPos);
}

void GUIRenderer::MouseScroll(double xOffset, double yOffset)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseWheelH += xOffset;
    io.MouseWheel += yOffset;
}

void GUIRenderer::OnResize(unsigned int width, unsigned int height)
{
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(width, height);
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
}

void GUIRenderer::UpdateDeltaTime(float deltaTime)
{
    ImGuiIO& io = ImGui::GetIO();
    if (deltaTime < 0.5f)
        io.DeltaTime = 30.0f;
    else
        io.DeltaTime = deltaTime;
}