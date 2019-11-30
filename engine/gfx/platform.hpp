#ifndef PLATFORM_HPP_
#define PLATFORM_HPP_

#include "common.hpp"
#include <glad/glad.h>

namespace gfx {
#ifdef OPEN_GL
    typedef u32 VertexArrObj;    // Vertex Array object 
    typedef u32 VertexBuffer;  // vertex array object
    typedef u32 IndexBuffer;   // index buffer
    typedef u32 TextureObject; // texture object
    typedef u32 ShaderStageProgram;
    typedef u32 ShaderProgram; // shader object
    typedef u32 Buffer;        // general buffer
    typedef GLenum Enum;
#elif DIRECTX
#error "DirectX unsupported"
#endif
    
    VertexArrObj create_vao();
    
    VertexBuffer create_streaming_vbo(void* data, u32 size);
    VertexBuffer create_static_vbo(void * data, u32 size);
    
    IndexBuffer create_stream_ibo(u32* data, u32 size);
    IndexBuffer create_static_ibo(u32* data, u32 size);
    
    ShaderStageProgram create_shader_stage(Enum type);
    ShaderProgram create_shader();
    
    Buffer create_buffer();
    
    void bind_buffer(Enum type, Buffer buffer);
    
    void bind_vertex_buffer(VertexBuffer buffer);
    
    void bind_index_buffer(IndexBuffer buffer);
}

#endif