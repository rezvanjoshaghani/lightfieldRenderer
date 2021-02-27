#pragma once

class IndexBuffer {
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	// Assuming 32 bits are enough for the number of the indecies, if you have less indecies change unsigned int to char
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void bind() const;
	void unbind() const;

	inline unsigned int getCount() const { return m_Count; }
};