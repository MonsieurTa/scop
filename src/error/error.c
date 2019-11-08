/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 12:51:45 by wta               #+#    #+#             */
/*   Updated: 2019/10/23 14:25:15 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "error.h"

int	throw_error(int err_code)
{
	if (err_code == ERR_SDL_VIDEO)
		ft_putstr_fd("scop: Couldn't init SDL video\n", STDERR_FILENO);
	else if (err_code == ERR_SDL_CREAT_WIN)
		ft_putstr_fd("scop: Couldn't create SDL window\n", STDERR_FILENO);
	else if (err_code == ERR_SDL_GL_CTX)
		ft_putstr_fd("scop: Couldn't create SDL OpenGL context\n", STDERR_FILENO);
return (-1);
}
