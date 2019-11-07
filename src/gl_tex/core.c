/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:44:15 by wta               #+#    #+#             */
/*   Updated: 2019/11/07 17:19:19 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga_loader.h"
#include "gl_tex.h"

static int	load(t_gl_tex *ctx, char *img_path,
	 int (*store_data)(t_file *, const char *))
{
	if (ctx->tga_loader.load(&ctx->tga_loader, img_path, store_data) != -1)
	{
		ctx->width = ctx->tga_loader.getWidth(&ctx->tga_loader);
		ctx->height = ctx->tga_loader.getHeight(&ctx->tga_loader);
		get_gl_format(ctx);
		ctx->data = ctx->tga_loader.data;
		return (0);
	}
	return (-1);
}

static void	destroy(t_gl_tex *ctx)
{
	ctx->tga_loader.destroy(&ctx->tga_loader);
}

t_gl_tex		gl_tex_init(void)
{
	t_gl_tex	ctx;

	ctx.tga_loader = new_tga_loader();
	ctx.load = load;
	ctx.destroy = destroy;
	ctx.enable_alpha = enable_alpha;
	return ctx;
}
