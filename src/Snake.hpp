/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:45:31 by jbeall            #+#    #+#             */
/*   Updated: 2019/05/30 16:38:27 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKE_HPP
# define  SNAKE_HPP
#include <vector>
#include "nibbler.hpp"

class SnakeSection {
	public:
		SnakeSection(SnakeSection const &);
		SnakeSection(unsigned x, unsigned y) : x(x), y(y) {};
		SnakeSection &operator=(SnakeSection const &);
		unsigned x;
		unsigned y;
};

class Snake {
	enum eDirection s_direct;
	public:
	std::vector<SnakeSection> snake_segments;
		Snake(unsigned, unsigned);
		SnakeSection const &head(void);
		void move(void);
		void turn(enum eDirection);
		void grow(void);
		unsigned getX(void) const;
		unsigned getY(void) const;
		~Snake();
};
#endif
