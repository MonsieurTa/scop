/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 14:18:33 by wta               #+#    #+#             */
/*   Updated: 2019/10/23 14:54:32 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ERR_NOERROR		0x0
# define ERR_SDL_VIDEO		0x1
# define ERR_SDL_CREAT_WIN	0x2
# define ERR_SDL_GL_CTX		0x4

int	throw_error(int err_code);

#endif
