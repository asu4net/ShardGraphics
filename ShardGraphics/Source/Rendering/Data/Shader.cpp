﻿#include "Shader.h"
#include <cassert>
#include <fstream>
#include <vector>
#include <glad/glad.h>

#include "glm/gtc/type_ptr.hpp"

namespace Shard::Graphics
{
    std::shared_ptr<Shader> Shader::Create(const std::string& fileLocation)
    {
        return std::make_shared<Shader>(fileLocation);
    }

    Shader::Shader(const std::string& fileLocation)
        : m_ShaderId(0)
    {
        std::string vertexSource, fragmentSource;
        ReadFromFile(fileLocation, vertexSource, fragmentSource);
        
        // Create an empty vertex shader handle
        const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        // Send the vertex shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        const GLchar* source = vertexSource.c_str();
        glShaderSource(vertexShader, 1, &source, nullptr);

        // Compile the vertex shader
        glCompileShader(vertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, infoLog.data());

            // We don't need the shader anymore.
            glDeleteShader(vertexShader);

            assert(false && "Vertex shader compilation failed!");
        }

        // Create an empty fragment shader handle
        const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        // Send the fragment shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        source = fragmentSource.c_str();
        glShaderSource(fragmentShader, 1, &source, nullptr);

        // Compile the fragment shader
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, infoLog.data());

            // We don't need the shader anymore.
            glDeleteShader(fragmentShader);
            // Either of them. Don't leak shaders.
            glDeleteShader(vertexShader);

            assert(false && "Fragment shader compilation failed!");
        }

        // Vertex and fragment shaders are successfully compiled.
        // Now time to link them together into a program.
        // Get a program object.
        m_ShaderId = glCreateProgram();

        // Attach our shaders to our program
        glAttachShader(m_ShaderId, vertexShader);
        glAttachShader(m_ShaderId, fragmentShader);

        // Link our program
        glLinkProgram(m_ShaderId);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(m_ShaderId, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_ShaderId, GL_INFO_LOG_LENGTH, &maxLength);
            
            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m_ShaderId, maxLength, &maxLength, infoLog.data());

            // We don't need the program anymore.
            glDeleteProgram(m_ShaderId);
            // Don't leak shaders either.
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            
            assert(false && "Shader linkage failed!");
        }

        // Always detach shaders after a successful link.
        glDetachShader(m_ShaderId, vertexShader);
        glDetachShader(m_ShaderId, fragmentShader);
    }
    
    Shader::~Shader()
    {
        glDeleteProgram(m_ShaderId);
    }
    
    void Shader::ReadFromFile(const std::string& fileLocation, std::string& vertexSource, std::string& fragmentSource)
    {
        static std::string content;
        std::ifstream fileStream(fileLocation, std::ios::in);

        if (!fileStream.is_open())
        {
            printf("Failed to read %s! File doesn't exist.", fileLocation.c_str());
            return;
        }
        
        std::string line;

        enum class ShaderType { None, Vertex, Fragment };
        ShaderType currentShader = ShaderType::None;
        
        while (!fileStream.eof())
        {
            std::getline(fileStream, line);

            if (line.find("#type") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                {
                    currentShader = ShaderType::Vertex;
                    continue;
                }

                if (line.find("fragment") != std::string::npos)
                {
                    currentShader = ShaderType::Fragment;
                    continue;
                }
            }

            switch (currentShader)
            {
            case ShaderType::None: continue;
            case ShaderType::Vertex: vertexSource.append(line + "\n"); continue;
            case ShaderType::Fragment: fragmentSource.append(line + "\n"); continue;
            }
        }

        fileStream.close();
    }

    void Shader::SetUniformMat4(const char* uniformName, const glm::mat4& mat) const
    {
        const uint32_t id = glGetUniformLocation(m_ShaderId, uniformName);
        glUniformMatrix4fv(id, 1, false, glm::value_ptr(mat));
    }

    void Shader::SetUniformVec4(const char* uniformName, const glm::vec4& vec) const
    {
        const uint32_t id = glGetUniformLocation(m_ShaderId, uniformName);
        glUniform4fv(id, 1, glm::value_ptr(vec));
    }

    void Shader::Bind() const
    {
        glUseProgram(m_ShaderId);
    }

    void Shader::Unbind() const
    {
        glUseProgram(0);
    }
}