#include "Shader.h"
#include "Renderer.h"


Shader::Shader(const std::string& filePath)
	:m_FilePath(filePath), m_RendrerID(0)
{
	ShaderProgramSource source = parseShader(filePath);
	m_RendrerID = createShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendrerID));
}

void Shader::bind() const
{
	GLCall(glUseProgram(m_RendrerID));
}

void Shader::unbind() const
{
	GLCall(glDeleteProgram(0));
}

void Shader::setUniform1i(const std::string& name, int v0)
{
	GLCall(glUniform1i(getUniformLocation(name), v0));
}

void Shader::setUniform1f(const std::string& name, float v0)
{
	GLCall(glUniform1f(getUniformLocation(name), v0));
}

ShaderProgramSource Shader::parseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);
	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line)) {

		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else {
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(),ss[1].str() };
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result==GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER,vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER,fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	//Dont need the shaders after linking them to GPU
	glDeleteShader(vs);
	glDeleteShader(vs);

	return program;

}

int Shader::getUniformLocation(const std::string& name)
{
	// check the cache for the uniform
	if (m_UniformLocationCach.find(name) != m_UniformLocationCach.end())
		return m_UniformLocationCach[name];

	// Find it if it is a cache miss
	GLCall(int location= glGetUniformLocation(m_RendrerID, name.c_str()));
	if (location == -1)
		std::cout << "Warning Uniform '" << name << "' does not exist!" << std::endl;
	
	//add the uniform to the cache
	m_UniformLocationCach[name] = location;
	return location;
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniformMat4f(const std::string& name, glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(getUniformLocation(name), 1,GL_FALSE,&matrix[0][0]));
}


void Shader::setUniformVec2f(const std::string& name, float v0, float v1)
{
	GLCall(glUniform2f(getUniformLocation(name), v0, v1));
}


void Shader::setUniformVec3f(const std::string& name, float v0, float v1,float v2)
{
	GLCall(glUniform3f(getUniformLocation(name), v0, v1,v2));
}
