#include "shader.hpp"
#include "utils/platform.hpp"

#include <glad/glad.h>
#include <exception>


namespace gfx {
    Shader::Shader(const std::string& name,
        const std::string& vs_file_path, const std::string& fs_file_path, 
        std::optional<std::string> gs_file_path) :
        name(name) {

        handle = glCreateProgram();
        
        if(!build_shader(vs_file_path, GL_VERTEX_SHADER)) return;

        if(gs_file_path)
            if(!build_shader(gs_file_path.value(), GL_GEOMETRY_SHADER)) return;

        if(!build_shader(fs_file_path, GL_FRAGMENT_SHADER)) return;

        glLinkProgram(handle);
        i32 success;

        glGetProgramiv(handle, GL_LINK_STATUS, &success);

        char log[512];
        if(!success) {
            glad_glGetProgramInfoLog(handle, 512, NULL, log);
            LOG_ERR("Program Linking Failed: {}", log);
        }
    }

    void Shader::use() {
        glCheck(glUseProgram(handle));
    }

    void Shader::unuse() {
        glUseProgram(0);
    }

    void Shader::add_uniform(const std::string& name) {
        auto idx = uniform_location(name);

        if(idx == -1) {
            LOG_ERR("Invalid uniform for shader {}: {}", this->name, name);
            return;
        }

        uniforms.insert(std::make_pair(name, idx));
    }

    i32 Shader::get_uniform(const std::string& name) {
        auto iter = uniforms.find(name);
        if(iter == uniforms.end()) {
            LOG_ERR("Unrecognized uniform: {}", name);
            return -1;
        }
        return iter->second;
    }


    i32 Shader::uniform_location(const std::string& name) {
        use();
        auto idx = glGetUniformLocation(handle, name.c_str());
        unuse();
        return idx;
    }


    bool Shader::build_shader(const std::string& file_path, u32 type) {

        auto shader_type_string = [](u32 type) {
            switch(type) {
                case GL_VERTEX_SHADER: return "Vertex Shader";
                case GL_FRAGMENT_SHADER: return "Fragment Shader";
                case GL_GEOMETRY_SHADER: return "Geometry Shader";
                default: throw std::runtime_error("Invalid shader type");
            }
        };

        auto type_string = shader_type_string(type);

        i32 success;
        auto shader = glCreateShader(type);

        auto file = Platform::read_entire_file(file_path);

        glShaderSource(shader, 1, &file.content, (i32*) &file.length);
        glCompileShader(shader);

        // Print compile errors if any.
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        char log[512];
        if(!success) {
            glGetShaderInfoLog(shader , 512, NULL, log);
            LOG_ERR("{} {} Failed: {}", type_string, file_path, log);
            return false;
        }

        glAttachShader(handle, shader);
        return true;
    }
}