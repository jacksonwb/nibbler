/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render2.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:45:31 by jbeall            #+#    #+#             */
/*   Updated: 2019/06/04 10:37:17 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER2_HPP
# define  RENDER2_HPP
#include "IRender.hpp"
#include "Game.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

#define RATIO 20

class Render : public IRender {
	Game &game;
	SDL_Window *win;
	SDL_Renderer *ren;
	TTF_Font *font;
	SDL_Event e;
	void drawWindow(void);
	void drawGame(void);
	void drawPause(void);
	void drawGameOver(void);
	void drawScore(void);
	bool isHeadChar(char c);
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
