#include <smpch.h>
#include "OpenglTexture.h"

#include <stb_image.h>

using namespace std;

//static bool isFlipped = false;

//Constructor
OpenglTexture::OpenglTexture(const std::string& filePath)
{
	//gets extention
	string extention = ""; extention += filePath[filePath.length() - 3]; extention += filePath[filePath.length() - 2]; extention += filePath[filePath.length() - 1];

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /* load image, create texture and generate mipmaps
    if (!isFlipped)
    {
        stbi_set_flip_vertically_on_load(true);
        isFlipped = true;
    }
    */

    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        if (extention == "jpg")
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        else if (extention == "png")
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
        Logger::LogErrorAlways("Texture", "Failed to load texture, Filepath: " + filePath);

    stbi_image_free(data);
}

void OpenglTexture::Bind(unsigned int slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, id);
}
