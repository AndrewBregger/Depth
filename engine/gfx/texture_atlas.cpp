#include "texture_atlas.hpp"


namespace std {
	size_t hash<std::pair<u32, u32>>::operator() (const std::pair<u32, u32>& val) const {
		return std::hash<u32>()(val.first) ^ std::hash<u32>()(val.second);
	}
}

namespace gfx {
	TextureAtlas::TextureAtlas(u32 width, u32 height, PixelFormat format) :
		Texture(width, height, format), sub_x(0), sub_y(0), max_height(0),
		x_index(0), y_index(0) {
	}

	bool TextureAtlas::add_image(const res::Image& image) {
		// determine if we should go to the next line
		if (should_advance(image)) {
			next_line();
		}

		/// maybe return something else to indicate if failed to be added.
		if (sub_y + image.get_height() > height()) {
			return false;
		}

		bind();
		// add the image to the gl texture.
		glTexSubImage2D(GL_TEXTURE_2D, 0, 
						sub_x, sub_y, image.get_width(), image.get_height(),
						GL_RGBA, GL_UNSIGNED_BYTE, image.buffer);
		unbind();
		
		// create the ImageInfo data structure.
		auto info = ImageInfo {
			x_index,
			y_index,
			(f32) sub_x / width(),
			(f32) sub_y / height(),
			(f32) image.get_width() / width(),
			(f32) image.get_height() / height(),
		};

		image_info.emplace(std::make_pair(x_index, y_index), info);
		
		
		sub_x += image.get_width();
		++x_index;

		if (image.get_height() > max_height) {
			max_height = image.get_height();
		}
		return true;
	}
	
	glm::vec4* TextureAtlas::get_image_at(u32 x, u32 y) {
		auto image_info_iter = image_info.find(std::make_pair(x, y));
		if (image_info_iter != image_info.end()) {
			const auto& info = image_info_iter->second;
			return (glm::vec4*) &info.u;
		}
		else return nullptr;
	}

	bool TextureAtlas::should_advance(const res::Image& image) {
		return (sub_x + image.get_width() > width());
	}

	void TextureAtlas::next_line() {
		sub_y += max_height;
		max_height = 0;
		++y_index;
		x_index = 0;
	}
}
