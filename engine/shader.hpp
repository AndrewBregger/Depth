#ifndef SHADER_HPP_
#define SHADER_HPP_

#include "common.hpp"

#include <unordered_map>

namespace gfx {
    class Shader {
        public:
            /// constructs a shader program
            /// name: name of this shader can be used to reference it later.
            /// vs_file_path: path to the vertex shander source code.
            /// fs_file_path: path to the fragment shader source code.
            /// gs_file_path: optional path to the geometry shader source code.
            Shader(const std::string& name, const std::string& vs_file_path, const std::string& fs_file_path, std::optional<std::string> gs_file_path = std::optional<std::string>());

            /// binds this shader to be used for rendering.
            void use();

            /// resets the shader state.
            void unuse();

            /// adds a uniform name to be cached
            /// name: the name of the uniform
            void add_uniform(const std::string& name);

            /// returns the value of uniform name
            /// name: the name of the uniform
            i32 get_uniform(const std::string& name);

        private:
            /// returns the location of this uniform for reference
            /// name: the name of the uniform
            i32 uniform_location(const std::string& name);


        private:
            /// builds a shader program
            /// file_path: path to the source
            /// type: which type of shader should be build.
            bool build_shader(const std::string& file_path, u32 type);

        private:
            std::string name;
            u32 handle;
            std::unordered_map<std::string, i32> uniforms;
    };
}

#endif