/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRender.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 13:40:50 by jbeall            #+#    #+#             */
/*   Updated: 2019/05/30 14:33:06 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRENDER_HPP
# define IRENDER_HPP

class IRender {
	public:
		IRender(void) {};
		virtual void init(void) = 0;
		virtual char getInput(void) = 0;
		virtual void destroy(void) = 0;
		virtual void render(void) = 0;
		virtual ~IRender(void) {};
};

#endif