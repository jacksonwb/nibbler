/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render1.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 11:15:20 by jbeall            #+#    #+#             */
/*   Updated: 2019/05/30 17:20:46 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER1_H
# define RENDER1_H
# include <ncurses.h>
#include "IRender.hpp"
#include "Game.hpp"

class Render : public IRender {
	Game &game;
	void drawWindow(void);
	void drawFood(void);
	void drawSnake(void);
	void drawGame(void);
	void drawPause(void);
	void drawGameOver(void);
	bool checkSize();
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