#include <SmokTyGUI/WidgetRenderer.hpp>

#include <BTDSTD/Logger.hpp>

#include <imgui.h>
#include <imgui_impl_vulkan.h>
#include <imgui_impl_glfw.h>

void Smok::TyGUI::Widget::WidgetRenderer::Init(Smok::Graphics::Core::GraphicsContext* GContex, SMGraphics_Core_GPU* _GPU,
	SMWindow_Desktop_Window* _window, SMWindow_Desktop_Swapchain* _swapchain, SMGraphics_Pool_CommandPool* comPool,
	const WidgetRendererSettings& settings)
{
	device = _GPU->device;
	window = _window; swapchain = _swapchain;

	//1: create descriptor pool for IMGUI
	// the size of the pool is very oversize, but it's copied from imgui demo itself.
	VkDescriptorPoolSize pool_sizes[11] =
	{
		{ VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
		{ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
		{ VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
		{ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
		{ VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
		{ VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
		{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
		{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
		{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
		{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
		{ VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
	};

	VkDescriptorPoolCreateInfo pool_info = {};
	pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
	pool_info.maxSets = 1000;
	pool_info.poolSizeCount = 11;
	pool_info.pPoolSizes = pool_sizes;

	if (vkCreateDescriptorPool(device, &pool_info, nullptr, &pool) != VK_SUCCESS)
	{
		BTD::Logger::LogError("SmokTyGUI", "WidgetRenderer", "Init", "Failed to make desc pool for ImGUI!");
		return;
	}

	// 2: initialize imgui library

	//this initializes the core structures of imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& ImGUIIO = ImGui::GetIO(); (void)ImGUIIO;

	//if docking is enabled
	if (settings.isDockingEnabled)
	{
		ImGUIIO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		isDockingEnabled = settings.isDockingEnabled;
	}

	//if seprate view ports are enabled
	if (settings.isSeprateViewportsEnabled)
	{
		ImGUIIO.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		isSeprateViewportsEnabled = settings.isSeprateViewportsEnabled;
	}

	//sets up styling so view ports match
	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();
	if (isSeprateViewportsEnabled)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	//this initializes imgui for GLFW
	ImGui_ImplGlfw_InitForVulkan((GLFWwindow*)window->window, true);

	//this initializes imgui for Vulkan
	ImGui_ImplVulkan_InitInfo init_info = {};
	init_info.Instance = GContex->vulkanInstance;

	init_info.PhysicalDevice = _GPU->gpu;
	init_info.Device = device;

	init_info.Queue = _GPU->graphicsQueue;
	init_info.QueueFamily = 1;

	init_info.DescriptorPool = pool;

	init_info.MinImageCount = 3;
	init_info.ImageCount = swapchain->imageCount;

	init_info.Allocator = nullptr;
	
	//init_info.PipelineCache = VK_NULL_HANDLE;
	//init_info.Subpass = -1;

	init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;

	//generate color attachment
	VkAttachmentDescription colorAttachment = { 0 };
	colorAttachment.format = VK_FORMAT_B8G8R8A8_SRGB;
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;

	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;

	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL; // VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = /*VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;*/ VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference colorAttachmentRef = { 0 };
	colorAttachmentRef.attachment = 0;
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	//generate depth attachment
	VkAttachmentDescription depthAttachment = { 0 };
	depthAttachment.format = swapchain->depthFormat;
	depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;

	depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

	depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

	depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	VkAttachmentReference depthAttachmentRef = { 0 };
	depthAttachmentRef.attachment = 1;
	depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	//subpass
	VkSubpassDescription subpass = { 0 };
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentRef;

	subpass.pDepthStencilAttachment = &depthAttachmentRef;

	VkSubpassDependency dependency = { 0 };
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.dstSubpass = 0;
	dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
	dependency.srcAccessMask = 0;
	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

	VkAttachmentDescription _attachments[2] = { colorAttachment, depthAttachment };
	VkRenderPassCreateInfo renderPassInfo = { 0 };
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = 2;
	renderPassInfo.pAttachments = _attachments;
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;
	renderPassInfo.dependencyCount = 1;
	renderPassInfo.pDependencies = &dependency;

	if (vkCreateRenderPass(device, &renderPassInfo, NULL, &renderPass) != VK_SUCCESS)
	{
		//DestroySwapchain(swapchain, device, allocator);
		BTD_LogError("Smok Ty GUI", "Widget Renderer", "Init", "Failed to create render pass!");
		return;
	}

	//initalize
	ImGui_ImplVulkan_Init(&init_info, renderPass);

	//execute a gpu command to upload imgui font textures
	SMGraphics_Pool_CommandBuffer b;
	SMGraphics_Pool_CommandPool_StartSingleUseCommandBuffer(comPool, &b, _GPU->device);
	ImGui_ImplVulkan_CreateFontsTexture(b.comBuffer);
	SMGraphics_Pool_CommandPool_EndSingleUseCommandBuffer(comPool, &b, _GPU->device, _GPU->graphicsQueue);

	//clear font textures from cpu data
	ImGui_ImplVulkan_DestroyFontUploadObjects();

	//creates the render pass render graph command struct
	SMGraphics_RenderCommands_RenderPass_Create(&GUIRenderPassSettings, &BTD_Math_Color_Blue(), "GUI Pass");
}

void Smok::TyGUI::Widget::WidgetRenderer::Shutdown()
{
	ImGui_ImplVulkan_Shutdown();
	vkDestroyRenderPass(device, renderPass, nullptr);
	ImGui_ImplGlfw_Shutdown();
	vkDestroyDescriptorPool(device, pool, nullptr);
	
	device = VK_NULL_HANDLE;
}

void Smok::TyGUI::Widget::WidgetRenderer::StartFrame(VkCommandBuffer& comBuffer,
	VkFramebuffer& framebuffer, const BTD_Math_U32Vec2& frameSize)
{
	//starts a GUI render pass
	SMGraphics_RenderCommands_RenderPass_StartRenderPass(&GUIRenderPassSettings, comBuffer,
		framebuffer, renderPass, frameSize, { 0, 0 });

	//starts a new frame
	ImGui_ImplVulkan_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Smok::TyGUI::Widget::WidgetRenderer::SubmitFrame(VkCommandBuffer& comBuffer)
{
	ImGui::GetIO().DisplaySize = ImVec2(window->size.x, window->size.y);

	//renders the stuff
	ImGui::Render();
	ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), comBuffer);

	//handles viewports and sends platform OS updates that they exist
	//if (isSeprateViewportsEnabled)
	//{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	//}

	//ends the render pass
	SMGraphics_RenderCommands_RenderPass_EndRenderPass(&GUIRenderPassSettings, comBuffer);
}

void Smok::TyGUI::Widget::WidgetRenderer::StartDockSpace()
{
	// If you strip some features of, this demo is pretty much equivalent to calling DockSpaceOverViewport()!
   // In most cases you should be able to just call DockSpaceOverViewport() and ignore all the code below!
   // In this specific demo, we are not using DockSpaceOverViewport() because:
   // - we allow the host window to be floating/moveable instead of filling the viewport (when opt_fullscreen == false)
   // - we allow the host window to have padding (when opt_padding == true)
   // - we have a local menu bar in the host window (vs. you could use BeginMainMenuBar() + DockSpaceOverViewport() in your code!)
   // TL;DR; this demo is more complicated than what you would normally use.
   // If we removed all the options we are showcasing, this demo would become:
   //     void ShowExampleAppDockSpace()
   //     {
   //         ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
   //     }

	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

	//static bool opt_fullscreen = true;
	//static bool opt_padding = false;
	//static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
	//
	//// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	//// because it would be confusing to have two docking targets within each others.
	//ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	//if (opt_fullscreen)
	//{
	//	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	//	ImGui::SetNextWindowPos(viewport->WorkPos);
	//	ImGui::SetNextWindowSize(viewport->WorkSize);
	//	ImGui::SetNextWindowViewport(viewport->ID);
	//	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	//	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	//	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	//	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	//}
	//else
	//{
	//	dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
	//}
	//
	//// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
	//// and handle the pass-thru hole, so we ask Begin() to not render a background.
	//if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
	//	window_flags |= ImGuiWindowFlags_NoBackground;
	//
	//// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	//// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	//// all active windows docked into it will lose their parent and become undocked.
	//// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	//// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	//if (!opt_padding)
	//	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	//bool s = true;
	//ImGui::Begin("DockSpace Demo", &s, window_flags);
	//if (!opt_padding)
	//	ImGui::PopStyleVar();
	//
	//if (opt_fullscreen)
	//	ImGui::PopStyleVar(2);
	//
	//// Submit the DockSpace
	//ImGuiIO& io = ImGui::GetIO();
	//if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	//{
	//	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	//	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	//}
	//else
	//{
	//	ShowDockingDisabledMessage();
	//}

	//if (ImGui::BeginMenuBar())
	//{
	//	if (ImGui::BeginMenu("Options"))
	//	{
	//		// Disabling fullscreen would allow the window to be moved to the front of other windows,
	//		// which we can't undo at the moment without finer window depth/z control.
	//		ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
	//		ImGui::MenuItem("Padding", NULL, &opt_padding);
	//		ImGui::Separator();
	//
	//		if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
	//		if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
	//		if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
	//		if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
	//		if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
	//		ImGui::Separator();
	//
	//		//if (ImGui::MenuItem("Close", NULL, false, p_open != NULL))
	//		//	*p_open = false;
	//		ImGui::EndMenu();
	//	}
	//	//HelpMarker(
	//	//	"When docking is enabled, you can ALWAYS dock MOST window into another! Try it now!" "\n"
	//	//	"- Drag from window title bar or their tab to dock/undock." "\n"
	//	//	"- Drag from window menu button (upper-left button) to undock an entire node (all windows)." "\n"
	//	//	"- Hold SHIFT to disable docking (if io.ConfigDockingWithShift == false, default)" "\n"
	//	//	"- Hold SHIFT to enable docking (if io.ConfigDockingWithShift == true)" "\n"
	//	//	"This demo app has nothing to do with enabling docking!" "\n\n"
	//	//	"This demo app only demonstrate the use of ImGui::DockSpace() which allows you to manually create a docking node _within_ another window." "\n\n"
	//	//	"Read comments in ShowExampleAppDockSpace() for more details.");
	//
	//	ImGui::EndMenuBar();
	//}
}

void Smok::TyGUI::Widget::WidgetRenderer::EndDockSpace()
{
	//ImGui::End();
}