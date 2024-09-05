#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>


#include "Vertex.h"

namespace Bengine {

	enum class GlyphSortType {
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	// this holds a single sprite, texture and depth
	struct Glyph {
		GLuint texture;
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;

	};

	class RenderBatch {

	};

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();
	
		void init();

		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void end();

		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color); //we pass by reference so there is no copy, but make it constant

		void renderBatch();

	private:
		void createVertexArray();
		void sortGlyphs();

		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBacktoFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

		GLuint _vbo;
		GLuint _vao;

		GlyphSortType _sortType;
		
		std::vector<Glyph*> _glyphs; //make it a pointer to optimize space
	};

}

