#ifndef TEXTURE_ATLAS_HPP_
#define TEXTURE_ATLAS_HPP_

#include "common.hpp"
#include "texture.hpp"
#include <functional>


namespace gfx {
	class TextureAtlas : public Texture {
		public:
			/// Texture Atlas constructor.
			///
			/// Texture atlas does not start with any data.
			TextureAtlas(u32 width, u32 height, PixelFormat format);

			/// add an image to the atlas.
			bool add_image(const res::Image& image);

			/// retrieve texture coordinates for an image to (x, y)
			glm::vec4* get_image_at(u32 x, u32 y);

		private:

			/// determine if the next image will fit
			bool should_advance(const res::Image& image);

			/// move the y position up the image.
			void next_line();

			/// Reprsents a single image in the atlas.
			struct ImageInfo {
				/// Used for looking up the image.
				/// x location of this image in terms of images.
				u32 x;
				/// y location of this image in terms of images.
				u32 y;
				/// base u coordinate
				f32 u;
				/// base v coordinate
				f32 v;
				/// width of the image in texture coordinate space
				f32 delta_u;
				/// height of the image in texture coordinate space
				f32 delta_v;
			};

			u32 sub_x;

			u32 sub_y;

			u32 max_height;

			u32 x_index;

			u32 y_index;

			std::unordered_map<std::pair<u32, u32>, ImageInfo> image_info;
	};
}

#endif
