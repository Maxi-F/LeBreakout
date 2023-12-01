#include "fonts.h"

#include <SFML/Graphics.hpp>
#include <string>

#include "colors.h"
#include "window.h"
#include "vector.h"

namespace LeBreakout {
	namespace Fonts {
		static sf::Font ACTIVE_FONT;
		static int FONT_SIZE;

		void initFont(const char* filename) {
			ACTIVE_FONT.loadFromFile(filename);
		};

		void setFontSize(int fontSize) {
			FONT_SIZE = fontSize;
		}

		Vectors::Vector2 getTextSize(const char* text) {
			sf::Text textToMeasure;
			
			textToMeasure.setFont(ACTIVE_FONT);
			textToMeasure.setCharacterSize(FONT_SIZE);
			textToMeasure.setString(text);

			return { textToMeasure.getLocalBounds().width, static_cast<double>(FONT_SIZE) };
		}

		void writeText(sf::RenderWindow& window, const char* text, Vectors::Vector2 position, Colors::Color color, int fontSize) {
			sf::Text textToDraw;

			textToDraw.setFont(ACTIVE_FONT);
			textToDraw.setCharacterSize(fontSize);
			textToDraw.setString(text);

			textToDraw.setFillColor(sf::Color(color.r));
			textToDraw.setPosition(sf::Vector2f(position.x, position.y));
			
			window.draw(textToDraw);
		}
	}
}
