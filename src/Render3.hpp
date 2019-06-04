/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render3.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:45:31 by jbeall            #+#    #+#             */
/*   Updated: 2019/06/04 10:38:38 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER3_HPP
# define  RENDER3_HPP
#include "IRender.hpp"
#include "Game.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <iostream>

#define RATIO 30
#define SPRITE_SIZE 64

class Render : public IRender {
	Game &game;
	SDL_Window *win;
	SDL_Renderer *ren;
	TTF_Font *font;
	SDL_Event e;
	SDL_Texture *sprite;
	void drawWindow(void);
	void drawGame(void);
	void drawPause(void);
	void drawGameOver(void);
	void drawScore(void);
	void drawHead(int, int, int);
	void drawFood(int, int);
	void drawSection(int, int, int);
	void drawTail(int, int, int);
	public:
		Render(Game &in) : game(in) {};
		void init(void);
		char getInput(void);
		void destroy();
		void render();
		~Render();
};

extern "C" IRender *getRender(Game &in) {
	return new Render(in);
}

#endif
