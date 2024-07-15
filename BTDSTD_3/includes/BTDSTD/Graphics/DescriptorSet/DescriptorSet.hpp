#pragma once

//defines a descriptor set pool, layout, and set manager

#include <BTDSTD/Logger.hpp>

#include <BTDSTD/Graphics/GPU.hpp>

#include <unordered_map>
#include <vector>

namespace BTD::Graphics::DescriptorSet
{
	//generates a descriptor set layout binding
	inline VkDescriptorSetLayoutBinding DescriptorSetLayoutBinding_GenerateBindingInfo(uint32_t bindingIndex, VkDescriptorType type, VkShaderStageFlags shaderStages)
	{
		VkDescriptorSetLayoutBinding binding{};
		binding.binding = bindingIndex;
		binding.descriptorCount = 1;
		binding.descriptorType = type;
		binding.stageFlags = shaderStages;
		return binding;
	}

	//descriptor set layout
	struct DescriptorSetLayout
	{
		VkDescriptorSetLayout handle = VK_NULL_HANDLE;

		//creates the layout
		inline bool Create(VkDevice& device, const std::vector<VkDescriptorSetLayoutBinding>& bindings)
		{
			VkDescriptorSetLayoutCreateInfo info = { VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO };
			info.pNext = nullptr;

			info.pBindings = bindings.data();
			info.bindingCount = (uint32_t)bindings.size();
			info.flags = 0;

			if (vkCreateDescriptorSetLayout(device, &info, nullptr, &handle) != VK_SUCCESS)
			{
				BTD::Util::Logger::LogErrorToConsole("BTD STD", "Descriptor Set Layout", "Create", "Failed to create descriptor layout");
				return false;
			}

			return true;
		}

		//destroys the layout
		inline void Destroy(VkDevice& device)
		{
			if (handle == VK_NULL_HANDLE)
				return;

			vkDestroyDescriptorSetLayout(device, handle, nullptr);
		}
	};

	//defines a storage image
	struct StorageImage
	{
		VkDescriptorImageInfo imgInfo{};
	};

	//defines a descriptor set
	struct DescriptorSet
	{
		VkDescriptorSet handle = VK_NULL_HANDLE;

		//the bind infos for updating
		std::vector<VkWriteDescriptorSet> writeDatas;

		//the uniform datas
		std::unordered_map<const char*, StorageImage> uniform_storageImage;

		//updates all write datas
		inline void UpdateBindDataAllUniforms(BTD::Graphics::GPU* gpu)
		{
			vkUpdateDescriptorSets(gpu->device, writeDatas.size(), writeDatas.data(), 0, nullptr);
		}

		//gets the storage image
		inline StorageImage* Get_StorageImage(const char* name)
		{
			for (auto& SI : uniform_storageImage)
			{
				if (!strcmp(SI.first, name))
					return &SI.second;
			}

			return nullptr;
		}

		//registers a storage image uniform
		inline StorageImage* UniformRegister_StorageImage(const char* name)
		{
			StorageImage* SI = Get_StorageImage(name);
			if (SI)
			{
				printf("%s is already a registered uniform storage image!\n", name);
				return SI;
			}

			return &(uniform_storageImage[name] = StorageImage());
		}

		//unregisters a storage image uniform

		//updates what image the storage image points to
		inline StorageImage* UpdateBindData_StorageImage(const char* name, const VkImageView imageView, const VkImageLayout imageLayout)
		{
			StorageImage* SI = Get_StorageImage(name);
			if (!SI)
				return nullptr;

			SI->imgInfo.imageLayout = imageLayout;
			SI->imgInfo.imageView = imageView;

			VkWriteDescriptorSet write = {};
			write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			write.pNext = nullptr;

			write.dstBinding = 0;
			write.dstSet = handle;
			write.descriptorCount = 1;
			write.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			write.pImageInfo = &SI->imgInfo;
			writeDatas.emplace_back(write);
		}
	};

	//defines a descriptor set pool info
	struct DescriptorSetPool_Info
	{
		uint32 maxStorageImageCount = 1,

			maxSetCount = 1;
	};

	//defines a descriptor set pool
	struct DescriptorSetPool
	{
		DescriptorSetPool_Info maxStats;

		VkDescriptorPool handle = VK_NULL_HANDLE;

		//creates a descriptor pool
		inline bool Create(VkDevice& device, const DescriptorSetPool_Info* info)
		{
			maxStats = *info; //sets the stats

			//allocates the pool
			std::vector<VkDescriptorPoolSize> poolSizes;
			poolSizes = {
				{.type = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, .descriptorCount = maxStats.maxSetCount * maxStats.maxStorageImageCount}
			};

			VkDescriptorPoolCreateInfo pool_info = { VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO };
			pool_info.flags = 0;
			pool_info.maxSets = maxStats.maxSetCount;
			pool_info.poolSizeCount = (uint32_t)poolSizes.size();
			pool_info.pPoolSizes = poolSizes.data();

			if (vkCreateDescriptorPool(device, &pool_info, nullptr, &handle) != VK_SUCCESS)
			{
				BTD::Util::Logger::LogErrorToConsole("BTD STD", "Descriptor Set Pool", "Create", "Failed to create descriptor set pool");
				return false;
			}

			return true;
		}

		//destorys a descriptor pool
		inline void Destroy(VkDevice& device)
		{
			if (handle == VK_NULL_HANDLE)
				return;

			vkDestroyDescriptorPool(device, handle, nullptr);
		}

		//allocates a descriptor set
		DescriptorSet AllocateDescriptorSet(VkDevice device, VkDescriptorSetLayout layout)
		{
			VkDescriptorSetAllocateInfo allocInfo = { VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO };
			allocInfo.pNext = nullptr;
			allocInfo.descriptorPool = handle;
			allocInfo.descriptorSetCount = 1;
			allocInfo.pSetLayouts = &layout;

			DescriptorSet set;
			if (vkAllocateDescriptorSets(device, &allocInfo, &set.handle) != VK_SUCCESS)
			{
				BTD::Util::Logger::LogErrorToConsole("Projekt Swerve", "Descriptor Set", "Build", "Failed to create descriptor set");
			}

			return set;
		}

		//rests the pool (deletes all the descriptors)
		inline void Clear(VkDevice& device)
		{
			vkResetDescriptorPool(device, handle, 0);
		}
	};
}