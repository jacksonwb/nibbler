/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:31:20 by jbeall            #+#    #+#             */
/*   Updated: 2019/05/30 21:32:12 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nibbler.hpp"
#include "Game.hpp"
#include "IRender.hpp"
#include <iostream>
#include <dlfcn.h>

int main(int argc, char **argv)
{
	IRender*(*getRender)(Game&);
	unsigned width = 0;
	unsigned height = 0;
	if (argc != 3) {
		std::cout << "usage: ./nibbler width height" << std::endl;
		exit(0);
	}
	width = std::stoul(argv[1]);
	height = std::stoul(argv[2]);
	if (width > GAME_SIZE_MAX || width < GAME_SIZE_MIN || height > GAME_SIZE_MAX
		|| height < GAME_SIZE_MIN)
	{
		std::cout << "bad dimensions - must be in range [" << GAME_SIZE_MIN
			<< " - " << GAME_SIZE_MAX << "]" << std::endl;
		exit(0);
	}
	srand(time(NULL));

	void *lib_handle = dlopen("lib/lib1.dylib", RTLD_LOCAL);
	if (!lib_handle) {
		std::cout << "error: could not load graphics library" << std::endl;
		exit(EXIT_FAILURE);
	}

	Game game(width, height);
	getRender = (IRender*(*)(Game&))dlsym(lib_handle, "getRender");
	IRender* render = getRender(game);
	render->init();

	char in = 0;
	while (in != 'q' && in != ESC_KEY) {
		game.update();
		do {
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
			}
		} while (game.paused);
		render->render();
		if (game.game_over && in == ' ')
		game.reset();
	}
	render->destroy();
	return (0);
}