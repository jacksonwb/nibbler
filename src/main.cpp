/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:31:20 by jbeall            #+#    #+#             */
/*   Updated: 2019/06/03 17:09:26 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nibbler.hpp"
#include "Game.hpp"
#include "IRender.hpp"
#include <iostream>
#include <dlfcn.h>

void load_helper(std::string path, void** lib, IRender **render, Game& game) {
	IRender*(*getRender)(Game&);
	*lib = dlopen(path.c_str(), RTLD_LOCAL);
	if (!*lib) {
		std::cout << "error: could not load graphics library" << std::endl;
		exit(EXIT_FAILURE);
	}
	getRender = (IRender*(*)(Game&))dlsym(*lib, "getRender");
	*render = getRender(game);
	(*render)->init();
}

void unload_helper(void **lib, IRender **render) {
	(*render)->destroy();
	render = NULL;
	dlclose(*lib);
	lib = NULL;
}

void init_helper(int argc, char **argv, unsigned *w, unsigned *h, bool *hard) {
	if (argc < 3 || argc > 4) {
		std::cout << "usage: ./nibbler [-h] width height" << std::endl;
		exit(0);
	}
	if (argc == 4) {
		if (!strcmp(argv[1], "-h"))
			*hard = true;
		else {
			std::cout << "usage: ./nibbler [-h] width height" << std::endl;
			exit(0);
		}
	}
	*w = std::stoul(argv[1 + (*hard ? 1 : 0)]);
	*h = std::stoul(argv[2 + (*hard ? 1 : 0)]);
	if (*w > GAME_SIZE_MAX || *w < GAME_SIZE_MIN || *h > GAME_SIZE_MAX
		|| *h < GAME_SIZE_MIN)
	{
		std::cout << "bad dimensions - must be in range [" << GAME_SIZE_MIN
			<< " - " << GAME_SIZE_MAX << "]" << std::endl;
		exit(0);
	}
}

int main(int argc, char **argv)
{
	void *lib;
	IRender *render;
	unsigned width = 0;
	unsigned height = 0;
	bool hard = false;
	srand(time(NULL));
	init_helper(argc, argv, &width, &height, &hard);
	Game game(width, height, hard);
	load_helper("lib/lib2.dylib", &lib, &render, game);
	unsigned in = 0;

	while (in != 'q') {
		if (!game.isPaused())
			game.update();
		in = render->getInput();
		switch (in) {
			case ('a'):
				game.getSnake().turn(eDirection::Left);
				break;
			case ('w'):
				game.getSnake().turn(eDirection::Up);
				break;
			case('d'):
				game.getSnake().turn(eDirection::Right);
				break;
			case('s'):
				game.getSnake().turn(eDirection::Down);
				break;
			case(' '):
				game.paused = !game.paused;
				render->render();
				break;
			case('1'):
				unload_helper(&lib, &render);
				load_helper("lib/lib1.dylib", &lib, &render, game);
				break;
			case('2'):
				unload_helper(&lib, &render);
				load_helper("lib/lib2.dylib", &lib, &render, game);
				break;
			case('3'):
				unload_helper(&lib, &render);
				load_helper("lib/lib3.dylib", &lib, &render, game);
				break;
		}
		render->render();
		if (game.game_over && in == ' ')
			game.reset();
	}
	unload_helper(&lib, &render);
	return (0);
}