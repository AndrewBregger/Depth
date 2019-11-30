
#include <thread>
#include <cassert>

#include "common.hpp"
#include "window.hpp"
#include "entity/entity.hpp"
#include "entity/components/sprite.hpp"
#include "events/input.hpp"
#include "events/events.hpp"
#include "listener/camera_listener.hpp"
#include "listener/window_listener.hpp"

#include "assets/asset_manager.hpp"
#include "utils/image.hpp"
#include "gfx/texture.hpp"
#include "gfx/texture_atlas.hpp"
#include "gfx/shader.hpp"
#include "gfx/quad_render.hpp"

extern std::shared_ptr<utils::logging::Logger> logger;
using namespace event;

void render(gfx::Shader& shader, view::Camera& camera, u32 vao, u32 vbo, u32 ibo, u32 num) {
    
	shader.set_uniform("perspective", camera.get_projection());
	shader.set_uniform("view", camera.get_transform());
    
	glCheck(shader.use());
	glCheck(glBindVertexArray(vao));
    
	glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    
	glCheck(glDrawElements(GL_POINTS, num, GL_UNSIGNED_INT, nullptr));
    
	glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    
	glCheck(glBindVertexArray(0));
	glCheck(shader.unuse());
}

void handle_events(view::Camera& camera) {
	auto position = camera.get_position();
	f32 theta = camera.get_rotation();
    
	// translation
	if (Input::is_key_pressed(Key_A)) {
		position.x -= 5;
	}
    
	if (Input::is_key_pressed(Key_D)) {
		position.x += 5;
	}
    
	if (Input::is_key_pressed(Key_W)) {
		position.y -= 5;
	}
    
	if (Input::is_key_pressed(Key_S)) {
		position.y += 5;
	}
    
    
	// rotation
	if (Input::is_key_pressed(Key_Q)) {
		theta -= 5.f / 180.0f;
	}
    
	if (Input::is_key_pressed(Key_E)) {
		theta += 5.0f / 180.0f;
	}
    
	bool updated_pos = false;
	bool updated_rotation = false;
	
    // only update if moved.
	if (position != camera.get_position()) {
		camera.set_position(position);
    }
    
	if (theta != camera.get_rotation()) {
		camera.set_rotation(theta);
    }
}

class WorldCell : public entity::Entity {
    public:
    
    WorldCell() : entity::Entity(nullptr, "cell") {
    }
};

class Chuck {
    
};

/// main render loop.
void gmain() {
	LOG_INFO("App Start");
	auto window = win::Window();
    assets::AssetManager asset_manager;
    
	const auto width = window.get_width();
	const auto height = window.get_height();
    
	LOG_INFO("App Setup");
    
	view::Camera camera(window);
	camera.set_position(glm::vec3(width/2, height/2, 10));
    //camera.set_position(glm::vec3(0.0, 0.0, 1.0));
	camera.set_rotation(0.0f);
	camera.set_zoom(1, 1);
    
	window.make_current();
    
	event::EventManager emanager(&window);
	listener::WindowListener wlist(&window);
	listener::CameraListener clist(&camera);
    
	glViewport(0, 0, width, height);
    
	emanager.register_callback(event::WindowResizeEvent, &wlist, [](Listener* listener) {
                               auto w = (listener::WindowListener*) listener;
                               auto size = event::Input::window_resize();
                               // LOG_INFO("Window Update Size: {} {}", size.x, size.y);
							   glViewport(0, 0, size.x, size.y);
                               w->window->set_size(size.x, size.y);
                               });
    
	emanager.register_callback(event::WindowResizeEvent, &wlist, [](Listener* listener) {
                               auto c = (listener::CameraListener*) listener;
                               auto size = event::Input::window_resize();
                               // LOG_INFO("Camera Updated Size: {} {}", size.x, size.y);
                               // c->camera->set_aspect_ratio((f32) size.x / (f32) size.y);
                               c->camera->set_window_size(size);
                               });
	
	emanager.register_callback(event::ScrollEvent, &clist, [](Listener* listener) {
                auto c = (listener::CameraListener*) listener;
				auto zoom_x = event::Input::scroll_x();
				auto zoom_y = event::Input::scroll_y();
				const auto& zoom = c->camera->get_zoom();

				if (zoom_y > 0.0 || zoom_y < 0.0) {
					c->camera->set_zoom(zoom.x + (f32) zoom_y / 64.0, zoom.y + (f32) zoom_y / 64.0);
				}

			});
    
	LOG_INFO("Post Setup");
    
    
    //auto texture_id = asset_manager.load_texture("./res/test.jpg");
    //auto texture = asset_manager.get_asset_as<gfx::Texture>(texture_id);

    //auto texture_id_2 = asset_manager.load_texture("./res/stone.png");
    //auto texture_2 = asset_manager.get_asset_as<gfx::Texture>(texture_id);

	//std::cout << texture->id() << std::endl;
	//std::cout << texture_2->id() << std::endl;
	
	assets::AtlasInfo atlas_info = {
		2048,
		2048,
		PixelFormat::Rgba,
		{
			"./res/test.jpg",
			"./res/stone2.png"
		}
	};
	
	auto texture_id = asset_manager.load_texture_atlas(atlas_info);
	auto atlas = asset_manager.get_asset_as<gfx::TextureAtlas>(texture_id);
    
    assets::ShaderInfo shader_info = {
        "quad",
        "./res/shaders/quad_vs.glsl",
        std::optional("./res/shaders/quad_gs.glsl"),
        "./res/shaders/quad_fs.glsl",
    };
    
    auto shader_id = asset_manager.load_shader(shader_info);
    auto shader = asset_manager.get_asset_as<gfx::Shader>(shader_id);
    
	gfx::QuadRenderer render(&camera);
    render.set_shader(shader);
	render.init();
    glCheck();
    
    std::vector<WorldCell> entities;
	
	auto coords = atlas->get_image_at(0, 0);
	assert(coords);

	auto coord2 = atlas->get_image_at(1, 0);
	assert(coord2);

    // entity::Sprite sprite = entity::Sprite(texture_id);
    entity::Sprite sprite = entity::Sprite(texture_id, *coords);
    entity::Sprite sprite2 = entity::Sprite(texture_id, *coord2);

	u32 count = 0; 
	for (i32 i = -10; i < 10; ++i) {
		for (i32 j = -10; j < 10; ++j) {
            auto cell = WorldCell();
			cell.set_state(true);
            cell.set_position({32.0f * i, 32.0f * j});
            cell.set_size({32.0f, 32.0f});
	 		if (count++ % 2 == 0) 
				cell.add_component(&sprite);
			else
		 		cell.add_component(&sprite2);
            entities.push_back(cell);
        }
    }
    
    
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glfwSetTime(0);
    auto prev_frame = glfwGetTime();
    
    u32 counter = 0;

	//std::cout << "glDrawElementsInstanced: " << (void*) glDrawElementsInstanced << std::endl;
	//std::cout << "glUseProgram: " << (void*) glUseProgram << std::endl;
	//std::cout << "glBindTexture: " << (void*) glBindTexture << std::endl;
	//std::cout << "glMapBufferRange: " << (void*) glMapBufferRange << std::endl;
	//std::cout << "glMapBuffer: " << (void*) glMapBuffer << std::endl;
	//std::cout << "glDrawElements: " << (void*) glDrawElements << std::endl;
	//std::cout << "glBindBuffer: " << (void*) glBindBuffer << std::endl;
	//std::cout << "glBindVertexArray: " << (void*) glBindVertexArray << std::endl;
	//std::cout << "glUnmapBuffer: " << (void*) glUnmapBuffer << std::endl;
	//std::cout << "glGetError: " << (void*) glGetError << std::endl;
    
    while(!glfwWindowShouldClose(window.get_handle())) {
        ++counter;
        auto current_time = glfwGetTime();
        auto delta = current_time - prev_frame;
        
        if (counter >= 100) {
            std::cout << "FPS: " << counter / delta << std::endl;
            prev_frame = current_time;
            counter = 0;
        }
        
        // event::Input::new_frame();
        emanager.process_events();
		emanager.process_callbacks();
        
        handle_events(camera);
        
        camera.update();
        
		glCheck(glClear(GL_COLOR_BUFFER_BIT));
		
		shader->use();
        shader->set_uniform("perspective", camera.get_projection());
        shader->set_uniform("view", camera.get_transform());
		shader->unuse();
        
        // maybe?
        // render.update_uniforms();
        
        for (auto& e : entities)
            render.submit(&e);
        
		render.present();
		render.clear();
        
		window.swapbuffers();
    }
}

int main() {
    utils::logging::init_logger();
    
    logger->send_to_console(true);
    
    gmain();
    
    // std::thread main_loop(gmain);	
    
    // main_loop.join();
    
    return 0;
}
