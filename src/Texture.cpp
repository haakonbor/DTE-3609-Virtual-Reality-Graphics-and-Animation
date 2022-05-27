#include "../include/Texture.h"

#include "../include/stb_image.h"

Texture::Texture(const std::string& filepath)
	: m_FilePath(filepath), m_LocalBuffer(nullptr),
	m_Width(0), m_Height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_BPP, 4);
    if (!m_LocalBuffer)
    {
        std::cout << "FAILED TO LOAD TEXTURE FROM " << filepath  <<"\nFAILURE REASON: "<< stbi_failure_reason() << std::endl;
    }

	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_LocalBuffer) {
		stbi_image_free(m_LocalBuffer);
	}
}

Texture::Texture(const std::vector<std::string> faces)
    : m_LocalBuffer(nullptr),
      m_Width(0), m_Height(0), m_BPP(0)
{
    stbi_set_flip_vertically_on_load(0);
    GLCall(glGenTextures(1, &m_RendererID));
    GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID));

    for (unsigned int i = 0; i < faces.size(); i++) {
        m_LocalBuffer = stbi_load(faces[i].c_str(), &m_Width, &m_Height, &m_BPP, 4);
        if (!m_LocalBuffer)
        {
            std::cout << "FAILED TO LOAD TEXTURE FROM " << faces[i]  <<"\nFAILURE REASON: "<< stbi_failure_reason() << std::endl;
        }
        else {
            GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                        0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
        }
    }

    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));


    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    if (m_LocalBuffer) {
        stbi_image_free(m_LocalBuffer);
    }
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::BindCubemap(unsigned int slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::UnbindCubemap() const
{
    GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}
