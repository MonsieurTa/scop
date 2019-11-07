/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:13:44 by wta               #+#    #+#             */
/*   Updated: 2019/11/07 17:08:23 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_tex.h"

// vFragColor.rgb = texture(textureMap,uv).rrr;
// in shader assign it to the remaining channels like this

static void	get_8bit_infos(t_gl_tex *ctx, t_tga_header *header)
{
	if (header->depth == 8)
	{
		ctx->internal_format = GL_RGB8;
		ctx->format = GL_RED;
	}
	else
	{
		ctx->internal_format = GL_RGBA;
		ctx->format = GL_RG;
	}
}

static void	get_truevision_infos(t_gl_tex *ctx, t_tga_header *header)
{
	if (header->depth <= 24)
	{
		ctx->internal_format = GL_RGB8;
		ctx->format = GL_RGB;
	}
	else
	{
		ctx->internal_format = GL_RGBA8;
		ctx->format = GL_RGBA;
	}
}

void	get_gl_format(t_gl_tex *ctx)
{
	t_tga_header *header;

	header = &ctx->tga_loader.header;
	if (header->image_type)
	{

		if (header->image_type == 2)
			get_truevision_infos(ctx, header);
		else if (header->image_type == 11)
			get_8bit_infos(ctx, header);
	}
}