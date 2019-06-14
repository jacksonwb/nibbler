/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render2.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jackson <jbeall@student.42.us.org>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:45:31 by jbeall            #+#    #+#             */
/*   Updated: 2019/06/13 19:45:57 by jackson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Render2.hpp"

void Render::init(void) {
	SDL_DisplayMode DM;
	double scale = 1;
	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL Initialization Error" << std::endl;
		return;
	}
	SDL_GetCurrentDisplayMode(0, &DM);
	if (DM.w > 1920)
		scale = 1.5;
	std::cout << "w" << DM.w << "h" << DM.h << std::endl;
	win = SDL_CreateWindow("nibbler", 100, 100, (game.map_width + 1) * RATIO * scale, (game.map_height + 2) * RATIO * scale, SDL_WINDOW_SHOWN);
	if (win == nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		destroy();
		exit(EXIT_FAILURE);
	}
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr){
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		destroy();
		exit(EXIT_FAILURE);
	}
	TTF_Init();
	font = TTF_OpenFont("fnt/slkscr.ttf", 36);
	if (!font) {
		std::cout << "Error: font not found" << std::endl;
		destroy();
		exit(EXIT_FAILURE);
	}
	SDL_RenderSetScale(ren, scale, scale);
};

char Render::getInput(void) {
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT)
			return 'q';
		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_ESCAPE)
				return 'q';
			if (e.key.keysym.sym == SDLK_q)
				return 'q';
			if (e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_UP)
				return 'w';
			if (e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_DOWN)
				return 's';
			if (e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_LEFT)
				return 'a';
			if (e.key.keysym.sym == SDLK_d || e.key.keysym.sym == SDLK_RIGHT)
				return 'd';
			if (e.key.keysym.sym == SDLK_SPACE)
				return ' ';
			if (e.key.keysym.sym == SDLK_1)
				return '1';
			if (e.key.keysym.sym == SDLK_3)
				return '3';
		}
	}
	return 'e';
}

void Render::destroy(void) {
	delete this;
}

void Render::drawWindow(void) {
	SDL_Rect board;

	board.x = RATIO;
	board.y = RATIO;
	board.h = RATIO * game.map_height - 1 * RATIO;
	board.w = RATIO * game.map_width - 1 * RATIO;

	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255 );
    SDL_RenderFillRect(ren, &board);
}

bool Render::isHeadChar(char c) {
	if (c == H_U || c == H_D || c == H_L || c == H_R)
		return true;
	return false;
}

void Render::drawGame(void) {
	SDL_Rect piece;
	piece.w = RATIO;
	piece.h = RATIO;
	for (int i = 0; i <= game.map_height; i++) {
		for (int j = 0; j <= game.map_width; j++) {
			if (game.ar[j][i]) {
				switch (game.ar[j][i]) {
					case (FOOD_CHAR):
						SDL_SetRenderDrawColor(ren, 83, 126, 252, 99);
						break;
					default:
						if (isHeadChar(game.ar[j][i]))
							SDL_SetRenderDrawColor(ren, 148, 57, 235, 92);
						else
							SDL_SetRenderDrawColor(ren, 152, 105, 255, 100);
						break;
				}
				piece.x = j * RATIO;
				piece.y = game.map_height * RATIO - i * RATIO;
				SDL_RenderFillRect(ren, &piece);
			}
		}
	}
}

void Render::drawGameOver(void) {
	SDL_Color textColor = {0, 0, 0, 255};
	SDL_Surface *gameOverSurface = TTF_RenderText_Blended(font, "Game Over", textColor);
	SDL_Texture *text = SDL_CreateTextureFromSurface(ren, gameOverSurface);
	SDL_Rect renderQuad = {(int)game.map_width / 2 * RATIO - 100, (int)game.map_height / 2 * RATIO, gameOverSurface->w, gameOverSurface->h};
	SDL_RenderCopy(ren, text, NULL, &renderQuad);

	SDL_FreeSurface(gameOverSurface);
	SDL_DestroyTexture(text);
}

void Render::drawScore(void) {
	std::string score_txt = std::string("Score: " + std::to_string(game.score));
	SDL_Color textColor = {255, 255, 255, 255};
	SDL_Surface *gameOverSurface = TTF_RenderText_Blended(font, score_txt.c_str(), textColor);
	SDL_Texture *text = SDL_CreateTextureFromSurface(ren, gameOverSurface);
	SDL_Rect renderQuad = {20, (int)game.map_height * RATIO + 2, gameOverSurface->w, gameOverSurface->h};
	SDL_RenderCopy(ren, text, NULL, &renderQuad);

	SDL_FreeSurface(gameOverSurface);
	SDL_DestroyTexture(text);
}

void Render::drawPause(void) {
	SDL_Color textColor = {0, 0, 0, 255};
	SDL_Surface *gameOverSurface = TTF_RenderText_Blended(font, "Pause", textColor);
	SDL_Texture *text = SDL_CreateTextureFromSurface(ren, gameOverSurface);
	SDL_Rect renderQuad = {(int)game.map_width / 2 * RATIO - 50, (int)game.map_height / 2 * RATIO, gameOverSurface->w, gameOverSurface->h};
	SDL_RenderCopy(ren, text, NULL, &renderQuad);

	SDL_FreeSurface(gameOverSurface);
	SDL_DestroyTexture(text);
}

void Render::render(void) {
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
	SDL_RenderClear(ren);
	drawWindow();
	drawGame();
	drawScore();
	if (game.game_over)
		drawGameOver();
	if (game.paused && !game.game_over)
		drawPause();
	SDL_RenderPresent(ren);
};

Render::~Render() {
	if (win)
		SDL_DestroyWindow(win);
	if (font)
		TTF_CloseFont(font);
	if (ren)
		SDL_DestroyRenderer(ren);
	TTF_Quit();
	SDL_Quit();
};

