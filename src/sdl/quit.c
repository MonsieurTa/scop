/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 13:02:50 by wta               #+#    #+#             */
/*   Updated: 2019/10/23 14:54:07 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "scop.h"

/*
**	clean exit
**	SDL_GL_DeleteContext: Delete SDL OpenGL context
**	SDL_DestroyWindow
*/
void	sdl_ctx_destroy(t_sdl_ctx *ctx)
{
	SDL_GL_DeleteContext(ctx->gl_ctx);
	SDL_DestroyWindow(ctx->window);
}

void	sdl_ctx_quit(void)
{
	ft_putstr("Quiting SDL.\n");
	SDL_Quit();
	ft_putstr("Quiting...\n");
}
