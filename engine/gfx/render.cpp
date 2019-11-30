#include "render.hpp"
#include "entity/entity.hpp"
#include "entity/components/sprite.hpp"

namespace gfx {
    
	Batch::Batch() = default;
	
	inline u32 Batch::size() { return elements; } 
    
	inline bool Batch::is_full() {
		return size() >= BATCH_SIZE;
	}
    
	void Batch::push(const RenderInstanceData& instance) {
		if (!is_full()) {
			data[elements++] = instance;
		}
	}
    
	inline void Batch::clear() { elements = 0; }
    
	Renderer::Renderer(view::Camera* camera) : camera(camera) {
		asset_manager = assets::AssetManager::get();
	}
    
	void Renderer::submit(entity::Entity* entity) {
		// @todo change Entity::get_state name
		// this is checking if the entity is enabled.
		if (!entity->get_state()) return;
        
        auto sprite = entity->find_component<entity::Sprite>();
		if(sprite == nullptr) return;
        
		auto asset = sprite->asset();
		const auto& coords = sprite->coords();
		const auto& hue = sprite->hue();
        
		const auto& transform = entity->transform();
        
		Batch::RenderInstanceData instance;
		instance.position = transform.position;
		instance.size = transform.scale;
		instance.uv = glm::vec2(coords.x, coords.y);
		instance.uv_size = glm::vec2(coords.z, coords.w);
		instance.hue = hue;
		instance.alpha = 1.0;
		instance.rotation = transform.rotation;
        
		submit_instance(asset, instance);
		
		/* this will add opacity to a texture.
  auto opacity = entity->get_component<Opacity>();
  */
    }
    
	void Renderer::submit_instance(assets::AssetId asset, const Batch::RenderInstanceData& instance) {
		
		/// I do not know if this is the correct way to handle this.
		if (batches[asset].is_full()) {
			present_batch(asset, batches[asset]);
			batches[asset].clear();
		}

        batches[asset].push(instance);
		// auto batch_iter = batches.find(asset);
		// if (batch_iter == batches.end()) {
		// }
	}
    
	void Renderer::present() {
		for (auto& [asset, batch] : batches) {
			present_batch(asset, batch);
		}
	}
    
	void Renderer::present_batch(assets::AssetId asset, const Batch& batch) {
		
		/// because this is an unsigned integer, this will wrap on its own.
		static u32 call_count = 0;
		u32 buffer_number = call_count++ % NUM_VERTEX_BUFFERS;

        glCheck(glBindVertexArray(vao));
		glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
		
		
		/// I do not know what this timeout should be yet.
		const u32 TIMEOUT = 1;
		auto result = glClientWaitSync(vbo_fences[buffer_number], 0, TIMEOUT);

		if (result == GL_TIMEOUT_EXPIRED || result == GL_WAIT_FAILED) {
			LOG_ERR("Buffer Sync Failed");
			// return?
		}

		glCheck(glBindBuffer(GL_ARRAY_BUFFER, vbos[buffer_number]));
		u32 size_needed = batch.elements * sizeof(Batch::RenderInstanceData);
        // 1. map buffer
		void* buffer = nullptr;
		glCheck(buffer =
				glMapBufferRange(GL_ARRAY_BUFFER, 0, size_needed, 
				GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT));
        if (!buffer) {
            std::cout << "Failed to bind buffer" << std::endl;
            return;
        }

        // 2. copy batch buffer to mapped buffer
		memcpy(buffer, batch.data.data(), size_needed);

        // 3. unmap buffer.
        glCheck(glUnmapBuffer(GL_ARRAY_BUFFER));

		vbo_fences[buffer_number] = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);

		// 4. draw.
		shader->use();

		auto texture = asset_manager->get_asset_as<gfx::Texture>(asset);

		texture->activate();
		texture->bind();
		shader->set_uniform("tex", (i32) texture->id());

        glCheck(glDrawElements(GL_POINTS, batch.elements, GL_UNSIGNED_INT,
                                        nullptr));

		texture->unbind();
        shader->unuse();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
	void Renderer::clear() {
		for (auto& [asset, batch] : batches) {
			batch.clear();
		}
	}
    
	void Renderer::set_shader(Shader* shader) {
		this->shader = shader;
	}
	
	void Renderer::set_shader(const std::string& name) {
		set_shader(asset_manager->get_asset_as<Shader>(name));
	}
	
	void Renderer::set_shader(assets::AssetId asset_id) {
		set_shader(asset_manager->get_asset_as<Shader>(asset_id));
	}
    
	void Renderer::set_camera(view::Camera* camera) {
		this->camera = camera;
	}
}
