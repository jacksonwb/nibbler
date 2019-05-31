/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nibbler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:45:05 by jbeall            #+#    #+#             */
/*   Updated: 2019/05/30 21:24:22 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NIBBLER_H
# define NIBBLER_H

# define GAME_SIZE_MAX 80
# define GAME_SIZE_MIN 10

# define FOOD_CHAR 'f'
# define HEAD_CHAR 'h'
# define SECTION_CHAR 's'
# define ESC_KEY 27

enum class eDirection {Up = 1, Right, Down, Left};

#endif