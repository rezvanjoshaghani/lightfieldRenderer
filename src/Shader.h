#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include"glm/glm.hpp"





struct ShaderProgramSource {
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendrerID;
	std::unordered_map <std::string, int>m_UniformLocationCach;
public:
	Shader(const std::string& filePath);
	~Shader();


	void bind()const;
	void unbind()const;

	void setUniform1i(const std::string& name, int v0);
	void setUniform1f(const std::string& name, float v0);
	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void setUniformMat4f(const std::string& name, glm::mat4& matrix);

	void setUniformVec2f(const std::string& name, float v0, float v1);

	void setUniformVec3f(const std::string& name, float v0, float v1, float v2);

private:
	ShaderProgramSource parseShader(const std::string& filePath);
	unsigned int compileShader(unsigned int type, const std:: string & source);
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
	int getUniformLocation(const std::string& name);

};

