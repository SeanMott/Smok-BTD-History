#pragma once

//defines a system for converting other mesh types into ones Smok understands

#include <SmokMesh/Mesh.hpp> //<SmokAsset/Mesh.hpp>

#include <assimp/scene.h> //../Assimp/assimp/scene.h"// <assimp/scene.h> //<assimp/scene.h>
#include <assimp/Importer.hpp> // <assimp/Importer.hpp>
#include <assimp/postprocess.h> // <assimp/postprocess.h>

#include <BTDSTD/Logger.hpp>

namespace SmokTools::AssetConvertion::Mesh
{
    //proceses meshes
    static inline void ProcessMesh(
        const std::string meshDir,
        aiMesh* mesh, const aiScene* scene,
        std::vector<Smok::Mesh::Vertex>& _mesheVertices,
        std::vector<uint32_t>& _meshIndices)
    {
        //goes through the textures and genarates materials and textures needed
        glm::vec4 color = { 0.0f, 0.0f, 0.0f, 1.0f };
        if (mesh->mMaterialIndex >= 0)
        {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

            //gets material color
            aiColor4D diffuse;
            aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse);
            color = { diffuse.r, diffuse.g, diffuse.b, diffuse.a };

            ////material->Get("ambient", )
            //for (uint32 m = 0; m < material->mNumProperties; ++m)
            //    BTD::Logger::LogMessage(std::string(std::string("Material Property: ") + std::string(material->mProperties[m]->mKey.C_Str())).c_str());
        }

        // walk through each of the mesh's vertices
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Smok::Mesh::Vertex vertex;

            // positions
            vertex.position = {
                mesh->mVertices[i].x,
                mesh->mVertices[i].y,
                mesh->mVertices[i].z
            };

            // normals
            if (mesh->HasNormals())
            {
                vertex.normal = {
                    mesh->mNormals[i].x,
                    mesh->mNormals[i].y,
                    mesh->mNormals[i].z
                };
            }

            //vertex color
            if (mesh->HasVertexColors(i))
            {
                vertex.color = {
                    mesh->mColors[i]->r * color.r,
                    mesh->mColors[i]->g * color.g,
                    mesh->mColors[i]->b * color.b ,
                    mesh->mColors[i]->a * color.a,
                };
            }
            else
            {
                vertex.color = {
                  color.r,
                  color.g,
                  color.b ,
                  color.a,
                };
            }

            // texture coordinates
            if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                //cords
                vertex.textureCords = {
                    mesh->mTextureCoords[0][i].x,
                    mesh->mTextureCoords[0][i].y
                };
            }
            else
                vertex.textureCords = { 0.0f, 0.0f };

            _mesheVertices.emplace_back(vertex);
        }

        // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            // retrieve all indices of the face and store them in the indices vector
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                _meshIndices.emplace_back(face.mIndices[j]);
        }
    }

    //processes nodes
    static inline void ProcessNode(
        const std::string meshDir,
        aiNode* node, const aiScene* scene, std::vector<Smok::Mesh::Mesh>& meshes)
    {
        Smok::Mesh::Mesh mesh;

        // process all the node's meshes (if any)
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            //gets mesh data
            aiMesh* _mesh = scene->mMeshes[node->mMeshes[i]];
            std::vector<uint32> indices; std::vector<Smok::Mesh::Vertex> vertices;
            ProcessMesh(meshDir, _mesh, scene, vertices, indices);

            //compacts it into the mesh data
            mesh.vertices.reserve(vertices.size());
            for (uint32 index = 0; index < indices.size(); ++index)
                mesh.vertices.emplace_back(vertices[indices[index]]);

            meshes.emplace_back(mesh);
        }

        // then do the same for each of its children
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            ProcessNode(meshDir, node->mChildren[i], scene, meshes);
        }
    }

	//converts other mesh types into one Smok understands
	inline bool ConvertStaticMeshToSmokFormat(const char* rawMeshPath, std::vector<Smok::Mesh::Mesh>& meshes)
	{
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(rawMeshPath, aiProcess_Triangulate | aiProcess_FlipUVs);
        if (!scene)
        {
            BTD::Logger::LogError("Smok Asset Convertion Tool", "Mesh", "ConvertMesh", importer.GetErrorString());
            BTD::Logger::LogError("Smok Asset Convertion Tool", "Mesh", "ConvertMesh",
                (std::string("Could not load a Model from ") + std::string(rawMeshPath) +
                    std::string(", check path and if it exported properly! If it's not a supported type check Github for updates or help improve Smok, thanks.")).c_str());
            return false;
        }

        //parses the file into the meshes
        ProcessNode(rawMeshPath, scene->mRootNode, scene, meshes);

        //generate render volumes of each mesh

        return true;
	}
}