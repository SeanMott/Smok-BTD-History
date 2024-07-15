#pragma once

//defines various image functions and structs

#include <vulkan/vulkan.h>
#include <BTDSTD/Vender/vk_mem_alloc.h>

namespace BTD::Graphics::Image
{
    //generates a image sub resources range
    VkImageSubresourceRange GenerateInfoStruct_ImageSubresourceRange(VkImageAspectFlags aspectMask)
    {
        VkImageSubresourceRange subImage{};
        subImage.aspectMask = aspectMask;
        subImage.baseMipLevel = 0;
        subImage.levelCount = VK_REMAINING_MIP_LEVELS;
        subImage.baseArrayLayer = 0;
        subImage.layerCount = VK_REMAINING_ARRAY_LAYERS;

        return subImage;
    }

    //generates a image create info struct
    VkImageCreateInfo GenerateInfoStruct_ImageCreateInfo(VkFormat format, VkImageUsageFlags usageFlags, VkExtent3D extent)
    {
        VkImageCreateInfo info = {};
        info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        info.pNext = nullptr;

        info.imageType = VK_IMAGE_TYPE_2D;

        info.format = format;
        info.extent = extent;

        info.mipLevels = 1;
        info.arrayLayers = 1;

        //for MSAA. we will not be using it by default, so default it to 1 sample per pixel.
        info.samples = VK_SAMPLE_COUNT_1_BIT;

        //optimal tiling, which means the image is stored on the best gpu format
        info.tiling = VK_IMAGE_TILING_OPTIMAL;
        info.usage = usageFlags;

        return info;
    }

    //generates a image view create info struct
    VkImageViewCreateInfo GenerateInfoStruct_ImageViewCreateInfo(VkFormat format, VkImage image, VkImageAspectFlags aspectFlags)
    {
        // build a image-view for the depth image to use for rendering
        VkImageViewCreateInfo info = {};
        info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        info.pNext = nullptr;

        info.viewType = VK_IMAGE_VIEW_TYPE_2D;
        info.image = image;
        info.format = format;
        info.subresourceRange.baseMipLevel = 0;
        info.subresourceRange.levelCount = 1;
        info.subresourceRange.baseArrayLayer = 0;
        info.subresourceRange.layerCount = 1;
        info.subresourceRange.aspectMask = aspectFlags;

        return info;
    }

    //transitions one image type to another
    inline void TransitionImage(VkCommandBuffer cmd, VkImage image, VkImageLayout currentLayout, VkImageLayout newLayout)
    {
        VkImageMemoryBarrier2 imageBarrier{ VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2 };
        imageBarrier.pNext = nullptr;

        imageBarrier.srcStageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
        imageBarrier.srcAccessMask = VK_ACCESS_2_MEMORY_WRITE_BIT;
        imageBarrier.dstStageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
        imageBarrier.dstAccessMask = VK_ACCESS_2_MEMORY_WRITE_BIT | VK_ACCESS_2_MEMORY_READ_BIT;

        imageBarrier.oldLayout = currentLayout;
        imageBarrier.newLayout = newLayout;

        imageBarrier.subresourceRange = GenerateInfoStruct_ImageSubresourceRange((newLayout == VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL) ? VK_IMAGE_ASPECT_DEPTH_BIT : VK_IMAGE_ASPECT_COLOR_BIT);
        imageBarrier.image = image;

        VkDependencyInfo depInfo{};
        depInfo.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
        depInfo.pNext = nullptr;

        depInfo.imageMemoryBarrierCount = 1;
        depInfo.pImageMemoryBarriers = &imageBarrier;

        vkCmdPipelineBarrier2(cmd, &depInfo);
    }

    //copies one image into another
    inline void CopyImageIntoImage(VkCommandBuffer cmd, VkImage source, VkImage destination, VkExtent2D srcSize, VkExtent2D dstSize)
    {
        VkImageBlit2 blitRegion{ VK_STRUCTURE_TYPE_IMAGE_BLIT_2, nullptr };

        blitRegion.srcOffsets[1].x = srcSize.width;
        blitRegion.srcOffsets[1].y = srcSize.height;
        blitRegion.srcOffsets[1].z = 1;

        blitRegion.dstOffsets[1].x = dstSize.width;
        blitRegion.dstOffsets[1].y = dstSize.height;
        blitRegion.dstOffsets[1].z = 1;

        blitRegion.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        blitRegion.srcSubresource.baseArrayLayer = 0;
        blitRegion.srcSubresource.layerCount = 1;
        blitRegion.srcSubresource.mipLevel = 0;

        blitRegion.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        blitRegion.dstSubresource.baseArrayLayer = 0;
        blitRegion.dstSubresource.layerCount = 1;
        blitRegion.dstSubresource.mipLevel = 0;

        VkBlitImageInfo2 blitInfo{ VK_STRUCTURE_TYPE_BLIT_IMAGE_INFO_2, nullptr };
        blitInfo.dstImage = destination;
        blitInfo.dstImageLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        blitInfo.srcImage = source;
        blitInfo.srcImageLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
        blitInfo.filter = VK_FILTER_LINEAR;
        blitInfo.regionCount = 1;
        blitInfo.pRegions = &blitRegion;

        vkCmdBlitImage2(cmd, &blitInfo);
    }

    //defines a image
    struct Image
    {
        VkImage image;
        VkImageView imageView;
        VmaAllocation allocation;
        VkExtent3D size;
        VkFormat imageFormat;
        VkImageLayout imageLayout = VK_IMAGE_LAYOUT_UNDEFINED;

        //transitions this image format to another || does a quick check to see if it's not in the format we desire
        //for a version with no checks, use the non-member "TransitionImage" or use "ChangeImageLayout_PurgeThePast" to forciablly whip away any previous content with no checks
        inline void ChangeImageLayout(VkCommandBuffer cmd, VkImageLayout newLayout)
        {
            if (imageLayout != newLayout)
                TransitionImage(cmd, image, imageLayout, newLayout);
        }

        //transitions this image format to another || DOES NOT GIVE A SHIT ABOUT THE PREVIOUS FORMAT, WILL JUST BRUTE FORCE
        //it's just "TransitionImage", but forces the previous format to VK_IMAGE_LAYOUT_UNDEFINED
        //does ZERO CHECKS
        inline void ChangeImageLayout_PurgeThePast(VkCommandBuffer cmd, VkImageLayout newLayout)
        {
            TransitionImage(cmd, image, VK_IMAGE_LAYOUT_UNDEFINED, newLayout);
            imageLayout = newLayout;
        }
    };
}