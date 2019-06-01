/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render1.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 11:15:21 by jbeall            #+#    #+#             */
/*   Updated: 2019/05/31 18:36:18 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Render1.hpp"
#include <unistd.h>

void Render::drawWindow(void) {
	mvhline(0, 0, 0, game.map_width);
	mvhline(game.map_height, 0, 0, game.map_width);
    mvvline(0, 0, 0, game.map_height);
    mvvline(0, game.map_width, 0, game.map_height);
    mvaddch(0, 0, ACS_ULCORNER);
    mvaddch(game.map_height, 0, ACS_LLCORNER);
    mvaddch(0, game.map_width, ACS_URCORNER);
    mvaddch(game.map_height, game.map_width, ACS_LRCORNER);
}

void Render::drawGame(void) {
	for (int i = 1; i < game.map_height; i++) {
		for (int j = 1; j < game.map_width; j++) {
			if (game.ar[j][i]) {
				int c = '0';
			switch (game.ar[j][i]) {
				case (HEAD_CHAR):
					c = '@';
					break;
				case (SECTION_CHAR):
					c = '#';
					break;
			}
				mvaddch(game.map_height - i, j, c);
			}
		}
	}
}

void Render::drawPause(void) {
	mvprintw(game.map_height / 2, (game.map_width / 2) - 4, "Paused");
}

void Render::drawGameOver(void) {
	mvprintw(game.map_height / 2, (game.map_width / 2) - 4, "Game Over");
}

bool Render::checkSize(void) {
	unsigned x;
	unsigned y;
	getmaxyx(stdscr, y, x);
	if (game.map_height > y || game.map_width > x) {
		mvprintw((int)y / 2, ((int)x / 2) - 10, "Increase sceen size");
		return (false);
	}
	return (true);
}

void Render::init(void) {
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	curs_set(0);
	keypad(stdscr, TRUE);
	refresh();
	ESCDELAY = 0;
}

char Render::getInput(void) {
	char c = getch();
	if (c == ESC_KEY)
		return ('q');
	return (c);
}

void Render::destroy(void) {
	delete this;
}

void Render::render(void) {
	erase();
	if(!checkSize()) {
		refresh();
		return;
	}
	drawWindow();
	drawGame();
	if (game.paused && !game.game_over)
		drawPause();
	if (game.game_over)
		drawGameOver();
	mvprintw(game.map_height + 1, 1, "Score: %d", game.score);
	refresh();
}

Render::~Render(void) {
	endwin();
}