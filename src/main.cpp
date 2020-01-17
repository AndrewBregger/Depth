
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
#include "gfx/spritesheet.hpp"

extern std::shared_ptr<utils::logging::Logger> logger;
using namespace event;

void handle_events(view::Camera& camera) {
	auto position = camera.get_position();
	f32 theta = camera.get_rotation();

	// translation
	if (Input::is_key_pressed(Key_A)) {
		position.x -= 10;
	}

	if (Input::is_key_pressed(Key_D)) {
		position.x += 10;
	}

	if (Input::is_key_pressed(Key_W)) {
		position.y += 10;
	}

	if (Input::is_key_pressed(Key_S)) {
		position.y -= 10;
	}

	// rotation
	if (Input::is_key_pressed(Key_Q)) {
		theta += 5.f / 180.0f;
	}

	if (Input::is_key_pressed(Key_E)) {
		theta -= 5.0f / 180.0f;
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
		WorldCell(entity::Sprite* sprite) : entity::Entity(nullptr, "") {
			add_component(sprite);
		}

		void set_sprite(entity::Sprite* sprite) {
			// @Note: if this is a common pattern then maybe there should be a replace
			// api on Entity.

			// remove the old
			remove_component<entity::Sprite>();
			// add the new one
			add_component(sprite);	
		}

		void set_location(const glm::ivec2& cell_loc) {
			cell_location = cell_loc;
		}

	private:
		glm::ivec2 cell_location;
};

class Chunk {
	public:
		Chunk(u32 x, u32 y) : size(x, y), cells(x * y, nullptr) {
		}

		void set_cell(u32 x, u32 y, WorldCell* cell) {
			set_cell_index(y * size.x + x, cell);
		}

		void set_cell_index(u32 index, WorldCell* cell) {
			cells[index] = cell;
		}

		void on_render(gfx::Renderer* renderer) {
			for (auto cell : cells) 
				renderer->submit(cell);
		}

		void update() {
			for (auto cell : cells)
				if(cell) cell->update();
		}
	private:
		glm::ivec2 size;
		std::vector<WorldCell*> cells;
};

// u32 chunk_size_x = 64;
// u32 chunk_size_y = 64;
u32 chunk_size_x = 32;
u32 chunk_size_y = 32;

Chunk build_chunk(gfx::SpriteSheet* sheet) {
	Chunk chunk(chunk_size_x, chunk_size_y);
	// 1 -> water
	// 2 -> dirt
	// 3 -> grass
	// 4 -> wall


	std::vector<std::vector<u32>> map = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{1,1,1,1,1,1,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{1,1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{1,1,1,1,1,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{1,1,1,1,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{1,1,1,1,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{1,1,1,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{1,1,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,3,3,3,3,3,3,3,3,3},
		{1,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,4,3,3,3,4,3,3,3,3,3,3,3,3,3},
		{2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,3,3,3,4,3,3,3,3,3,3,3,3,3},
		{2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,3,3,3,4,3,3,3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,3,3,3,3,3,3,3,3,3,4,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,3,3,3,3,3,3,3,3,3,4,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,3,3,3,3,3,3,3,3,3,4,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,3,3,3,3,3,3,3,3,3,4,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,3,3,3,3,3,3,3,3,3,4,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,3,3,3,3,3,3,3,3,3,4,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,3,3,3,3,3,3,3,3,3,4,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,3,3,3,3,3,3,3,3,3,4,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	};
	bool valid;
	std::unordered_map<u32, entity::Sprite*> mapping = {
		{1 , new entity::Sprite(sheet->get_id(), sheet->get_at(0, 0, valid))},
		{2 , new entity::Sprite(sheet->get_id(), sheet->get_at(1, 1, valid))},
		{3 , new entity::Sprite(sheet->get_id(), sheet->get_at(1, 0, valid))},
		{4 , new entity::Sprite(sheet->get_id(), sheet->get_at(0, 1, valid))}
	};

	for (u32 i = 0; i < chunk_size_x; ++i) {
		for (u32 j = 0; j < chunk_size_y; ++j) {
			auto sprite_id = map[i][j];
			auto cell = new WorldCell(mapping[sprite_id]);

			cell->set_state(true);
			cell->set_position({32.0f * i, 32.0f * j, 0.0});
			cell->set_size({32.0f, 32.0f});
			cell->set_location({i, j});

			chunk.set_cell(i, j, cell);
		}
	}

	return chunk;
}


/// main render loop.
void gmain() {
	LOG_INFO("App Start");
	auto window = win::Window();
    assets::AssetManager asset_manager;

	const auto width = window.get_width();
	const auto height = window.get_height();

	LOG_INFO("App Setup");

	view::Camera camera(window);
	camera.set_position(glm::vec3(0, 0, 10));
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

				if (zoom_y > 0.0 || zoom_y < 0.0)
					c->camera->set_zoom(zoom.x + (f32) zoom_y / 64.0, zoom.y + (f32) zoom_y / 64.0);
			});

	LOG_INFO("Post Setup");

    assets::SpriteSheetInfo sheet_info = {
        "./res/sprite.png",
        {32, 32}
    };

    auto texture_id = asset_manager.load_spritesheet(sheet_info);
    auto sheet = asset_manager.get_asset_as<gfx::SpriteSheet>(texture_id);

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

	Chunk chunk = build_chunk(sheet);

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

        event::Input::new_frame();
		event::Input::set_delta(delta);

        emanager.process_events();
		emanager.process_callbacks();

        handle_events(camera);

        camera.update();

		glCheck(glClear(GL_COLOR_BUFFER_BIT));

		shader->use();
        shader->set_uniform("perspective", camera.get_projection());
        shader->set_uniform("view", camera.get_transform());
		shader->unuse();

		chunk.update();

        // maybe?
        // render.update_uniforms();

		chunk.on_render(&render);

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
