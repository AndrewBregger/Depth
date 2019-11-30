#include "quad_render.hpp"
#include <glad/glad.h>
#include <algorithm>

namespace gfx {

	QuadRenderer::QuadRenderer(view::Camera* camera) : Renderer(camera) {
		set_shader("quad");
	}

	void QuadRenderer::init() {

		glCheck(glGenVertexArrays(1, &vao));
		glCheck(glGenBuffers(NUM_VERTEX_BUFFERS, vbos));

		glCheck(glGenBuffers(1, &ibo));

		glCheck(glBindVertexArray(vao));

		for (u32 i = 0; i < NUM_VERTEX_BUFFERS; ++i) {
			glBindBuffer(GL_ARRAY_BUFFER, vbos[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(Batch::RenderInstanceData) * BATCH_SIZE, nullptr, GL_STREAM_DRAW);
			vbo_fences[i] = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
		}
		
		std::vector<u32> indices(BATCH_SIZE);

		u32 num = 0;
		std::generate(indices.begin(), indices.end(), [&num]() {
					return num++;
				});
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * indices.size(), indices.data(), GL_STATIC_DRAW);
		
		u64 attributeSizes[] = {4, 4, 4, 1};
		u64 stride = 0;
		
		for(u32 i = 0; i < 4; ++i) {
			glVertexAttribPointer(i, attributeSizes[i], GL_FLOAT, GL_FALSE, sizeof(Batch::RenderInstanceData), (void*) (stride * sizeof(f32)));
			glEnableVertexAttribArray(i);
			// glVertexAttribDivisor(i, 1);
			stride += attributeSizes[i];
		}

		shader->use();
		shader->add_uniform("tex");
		shader->add_uniform("perspective");
		shader->add_uniform("view");
		shader->unuse();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);	
		glCheck(glBindVertexArray(0));
	}
}
