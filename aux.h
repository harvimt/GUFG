/*Header file for some utility functions used in "GUFG",
 *Written by Ashley Fisher in 2012 for her project, "srpg",
 *and used with her permission
 */

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>

class aux{
	private:
		static void scale  (SDL_Surface* source, SDL_Surface* destination);
		static void bilinear_scale  (SDL_Surface* source, SDL_Surface* destination);
		static SDL_Surface* scale2x(SDL_Surface* source);
	public:
		static SDL_Surface* init_screen(int width, int height, int bpp);
		static void update_screen(SDL_Surface* source, SDL_Surface* destination);

		static SDL_Surface* load_image(std::string filename);
		static void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);
	static bool checkCollision(SDL_Rect, SDL_Rect);
};
