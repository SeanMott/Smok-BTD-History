#pragma once

//defines a attachment

#include <vulkan/vulkan.h>

namespace BTD::Graphics::Image
{
    //generates a render attachment info
    inline VkRenderingAttachmentInfo GenerateInfoStruct_RenderingAttachment(VkImageView view, VkClearValue* clear, VkImageLayout layout)
    {
        VkRenderingAttachmentInfo colorAttachment{};
        colorAttachment.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO;
        colorAttachment.pNext = nullptr;

        colorAttachment.imageView = view;
        colorAttachment.imageLayout = layout;
        colorAttachment.loadOp = clear ? VK_ATTACHMENT_LOAD_OP_CLEAR : VK_ATTACHMENT_LOAD_OP_LOAD;
        colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        if (clear)
            colorAttachment.clearValue = *clear;

        return colorAttachment;
    }

    //generates a depth render attachment info
    inline VkRenderingAttachmentInfo GenerateInfoStruct_DepthRenderingAttachment(VkImageView view, VkImageLayout layout)
    {
        VkRenderingAttachmentInfo depthAttachment{};
        depthAttachment.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO;
        depthAttachment.pNext = nullptr;

        depthAttachment.imageView = view;
        depthAttachment.imageLayout = layout;
        depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        depthAttachment.clearValue.depthStencil.depth = 0.f;

        return depthAttachment;
    }

    //generates a dynamic render info
    inline VkRenderingInfo GenerateInfoStruct_Rendering(VkExtent2D renderExtent, VkRenderingAttachmentInfo* colorAttachment,
        VkRenderingAttachmentInfo* depthAttachment)
    {
        VkRenderingInfo renderInfo{};
        renderInfo.sType = VK_STRUCTURE_TYPE_RENDERING_INFO;
        renderInfo.pNext = nullptr;

        renderInfo.renderArea = VkRect2D{ VkOffset2D { 0, 0 }, renderExtent };
        renderInfo.layerCount = 1;
        renderInfo.colorAttachmentCount = 1;
        renderInfo.pColorAttachments = colorAttachment;
        renderInfo.pDepthAttachment = depthAttachment;
        renderInfo.pStencilAttachment = nullptr;

        return renderInfo;
    }
}