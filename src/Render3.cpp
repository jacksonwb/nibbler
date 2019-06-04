/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render3.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:45:31 by jbeall            #+#    #+#             */
/*   Updated: 2019/06/03 19:16:05 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Render3.hpp"

void Render::init(void) {
	SDL_Surface *tmp;
	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL Initialization Error" << std::endl;
		return;
	}
	win = SDL_CreateWindow("nibbler", 100, 100, (game.map_width + 1) * RATIO, (game.map_height + 2) * RATIO, SDL_WINDOW_SHOWN);
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

	IMG_Init(IMG_INIT_PNG);

	tmp = IMG_Load("sprite/snake-graphics.png");
	if (!tmp) {
		std::cout << "Error: textures not found" << std::endl;
		destroy();
		exit(EXIT_FAILURE);
	}
	sprite = SDL_CreateTextureFromSurface(ren, tmp);
	if (!sprite) {
		std::cout << "SDL_Texture Error: " << SDL_GetError() << std::endl;
		destroy();
		exit(EXIT_FAILURE);
	}
	SDL_FreeSurface(tmp);
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
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
			if (e.key.keysym.sym == SDLK_2)
				return '2';
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

	SDL_SetRenderDrawColor(ren, 247, 230, 152, 100 );
    SDL_RenderFillRect(ren, &board);
}

void Render::drawHead(int piece, int i, int j) {
	SDL_Rect src;
	SDL_Rect dst;

	src.x = piece == H_U || piece == H_L ? 3 * SPRITE_SIZE : 4 * SPRITE_SIZE;
	src.y = piece == H_U || piece == H_R ? 0 : 1 * SPRITE_SIZE;

	src.w = SPRITE_SIZE;
	src.h = SPRITE_SIZE;

	dst.x = j * RATIO;
	dst.y = game.map_height * RATIO - i * RATIO;
	dst.w = RATIO;
	dst.h = RATIO;

	SDL_RenderCopy(ren, sprite, &src, &dst);
}

void Render::drawFood(int i, int j) {
	SDL_Rect src;
	SDL_Rect dst;

	src.x = 0;
	src.y = 3 * SPRITE_SIZE;

	src.w = SPRITE_SIZE;
	src.h = SPRITE_SIZE;

	dst.x = j * RATIO;
	dst.y = game.map_height * RATIO - i * RATIO;
	dst.w = RATIO;
	dst.h = RATIO;

	SDL_RenderCopy(ren, sprite, &src, &dst);
}

void Render::drawSection(int piece, int i, int j) {
	SDL_Rect src;
	SDL_Rect dst;

	if (piece == S_UD) {
		src.x = 2 * SPRITE_SIZE;
		src.y = 1 * SPRITE_SIZE;
	}
	else if (piece == S_RL) {
		src.x = 1 * SPRITE_SIZE;
		src.y = 0 * SPRITE_SIZE;
	}
	else if (piece == S_LU) {
		src.x = 2 * SPRITE_SIZE;
		src.y = 2 * SPRITE_SIZE;
	}
	else if (piece == S_RU) {
		src.x = 0;
		src.y = 1 * SPRITE_SIZE;
	}
	else if (piece == S_DR) {
		src.x = 0;
		src.y = 0;
	}
	else {
		src.x = 2 * SPRITE_SIZE;
		src.y = 0 * SPRITE_SIZE;
	}
	src.w = SPRITE_SIZE;
	src.h = SPRITE_SIZE;

	dst.x = j * RATIO;
	dst.y = game.map_height * RATIO - i * RATIO;
	dst.w = RATIO;
	dst.h = RATIO;

	SDL_RenderCopy(ren, sprite, &src, &dst);

}

void Render::drawTail(int piece, int i, int j) {
	SDL_Rect src;
	SDL_Rect dst;

	src.x = piece == T_U || piece == T_L ? 3 * SPRITE_SIZE : 4 * SPRITE_SIZE;
	src.y = piece == T_U || piece == T_R ? 2 * SPRITE_SIZE : 3 * SPRITE_SIZE;

	src.w = SPRITE_SIZE;
	src.h = SPRITE_SIZE;

	dst.x = j * RATIO;
	dst.y = game.map_height * RATIO - i * RATIO;
	dst.w = RATIO;
	dst.h = RATIO;

	SDL_RenderCopy(ren, sprite, &src, &dst);
}

void Render::drawGame(void) {
	SDL_Rect piece;
	piece.w = RATIO;
	piece.h = RATIO;
	for (int i = 0; i <= game.map_height; i++) {
		for (int j = 0; j <= game.map_width; j++) {
			char c = game.ar[j][i];
			if (c) {
				if (c == H_U || c == H_D || c == H_L || c == H_R)
					drawHead(c, i, j);
				else if (c == T_U || c == T_D || c == T_L || c == T_R)
					drawTail(c, i, j);
				else if (c == S_UD || c == S_RL || c == S_LU || c == S_RU || c == S_DR || c == S_LD)
					drawSection(c, i, j);
				else if (c == FOOD_CHAR)
					drawFood(i, j);
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
	SDL_SetRenderDrawColor(ren, 187, 174, 121, 100);
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

