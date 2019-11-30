#include "platform.hpp"

namespace gfx {
    
    VertexArrObj create_vao() {
        return 0;
    }
    
    VertexBuffer create_streaming_vbo(void* data, u32 size) { return 0; }
    VertexBuffer create_static_vbo(void * data, u32 size) { return 0; }
    
    IndexBuffer create_stream_ibo(u32* data, u32 size) { return 0; }
    IndexBuffer create_static_ibo(u32* data, u32 size) { return 0; }
    
    ShaderStageProgram create_shader_stage(Enum type) { return 0; }
    ShaderProgram create_shader() { return 0; }
    
    Buffer create_buffer() { return 0; }
    
    void bind_buffer(Enum type, Buffer buffer) {}
    
    void bind_vertex_buffer(VertexBuffer buffer) {}
    
    void bind_index_buffer(IndexBuffer buffer) {}
}