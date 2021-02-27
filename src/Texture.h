#pragma once

#include"Renderer.h"


class Texture
{
private:
	unsigned int m_RenderID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture(const std::string& path);
	~Texture();

	void bind(unsigned int slot=0) const;
	void unbind();
	

	inline int getWidth() const { return m_Width; }
	inline int getHeight() const { return m_Height; }

};

