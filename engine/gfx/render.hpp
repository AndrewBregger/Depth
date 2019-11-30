#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include "assets/asset.hpp"
#include "assets/asset_manager.hpp"
#include "color.hpp"
#include "common.hpp"
#include "utils/noncopyable.hpp"
#include "shader.hpp"
#include "view/camera.hpp"

#include <glm/glm.hpp>
#include <array>

namespace entity {
	struct Entity;
}

namespace gfx {
	const u32 BATCH_SIZE = 1024;
	const u32 NUM_VERTEX_BUFFERS = 4;
    
    typedef u32 VertexArrObj;    // Vertex Array object 
    typedef u32 VertexBuffer;  // vertex array object
    typedef u32 IndexBuffer;   // index buffer
    typedef u32 TextureObject; // texture object
    typedef u32 ShaderStageProgram;
    typedef u32 ShaderProgram; // shader object
    typedef u32 Buffer;        // general buffer
    
    struct Batch : public utils::NonCopyable {
        struct RenderInstanceData {
            glm::vec2 position;
            glm::vec2 size;
            glm::vec2 uv;
            glm::vec2 uv_size;
            Color hue;
			f32 alpha;
            f32 rotation;
        };
        
		Batch();
		
		inline u32 size();
        
		inline bool is_full();
        
		void push(const RenderInstanceData& data);
        
		inline void clear();
		
        u32 elements{0};
		std::array<RenderInstanceData, BATCH_SIZE> data;
	};
    
	class Renderer {
		public:
        
        /// constructor
        Renderer(view::Camera* camera);
        
        /// Submit an entity to be rendered.
        void submit(entity::Entity* entity);
        
        /// Submit raw render data to be rendered.
		void submit_instance(assets::AssetId asset, const Batch::RenderInstanceData& instance);
        
        /// draw all cached drawn elements. Clears caches afterward.
        void present();
        
        /// present the contents of a current batch.
		void present_batch(assets::AssetId asset, const Batch& batch);
		
        /// clear cache.
        void clear();
		
		/// sets shader directly
		void set_shader(Shader* shader);
		
		/// sets shader from given name
		void set_shader(const std::string& name);
		
		/// sets shader from id.
		void set_shader(assets::AssetId asset_id);
        
		void set_camera(view::Camera* camera);
        
		virtual void init() = 0;
		
		protected:
        /// Direct access to accet manager.
		assets::AssetManager* asset_manager;
        
		// Shader used by this renderer.
		Shader* shader{nullptr};
		
		// view of the render
		view::Camera* camera{nullptr};
        
        /// Map of all the access that need to be rendered.
        std::unordered_map<assets::AssetId, Batch> batches;
        
        /// vertex array object
        VertexArrObj vao;
        
        /// render vertex buffer object
        VertexBuffer vbos[NUM_VERTEX_BUFFERS];
		GLsync vbo_fences[NUM_VERTEX_BUFFERS];
        
        /// index bufer
        IndexBuffer ibo;
    };
}

#endif
