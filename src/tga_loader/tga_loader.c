/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:05:04 by wta               #+#    #+#             */
/*   Updated: 2019/11/06 15:56:33 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"
#include "tga_loader.h"

#include <stdio.h>

static void		get_texel_size(t_tga_loader *ctx)
{
	uint8_t	img_type;

	img_type = ctx->header.image_type;
	if (img_type == 11)
	{
		if (ctx->header.depth ==  8)
			ctx->texel_size = 1;
		else
			ctx->texel_size = 2;
	}
	if (img_type == 10 || img_type == 2)
	{
		if (ctx->header.depth <= 24)
			ctx->texel_size = 3;
		else
			ctx->texel_size = 4;
	}
}

static int		load(t_tga_loader *ctx, char *img_path)
{
	store_data(&ctx->file, img_path);
	ft_memcpy(&ctx->header, ctx->file.content, sizeof(t_tga_header));
	if (is_supported_tga(&ctx->header) != -1)
	{
		ft_printf("TGA: Loading %s\n", ctx->file.filepath);
		ctx->cm_size = ctx->header.cm_len * (ctx->header.cm_entry_size >> 3);
		ctx->img_size = ctx->getWidth(ctx) * ctx->getHeight(ctx);
		assign_read(ctx);
		get_texel_size(ctx);
		// TODO: Protect malloc
		ctx->data = malloc(sizeof(uint8_t)
			* ctx->getWidth(ctx) * ctx->getHeight(ctx) * ctx->texel_size);
		ctx->read(ctx);
		// ctx->data = ctx->file.content;
		ft_printf("TGA: Image loaded\n");
	}
	return (0);
}

static void		destroy(t_tga_loader *ctx)
{
	munmap(ctx->file.content, ctx->file.file_stat.st_size);
}

t_tga_loader	new_tga_loader(void)
{
	t_tga_loader	ctx;

	ft_bzero(&ctx, sizeof(t_tga_loader));
	ctx.load = load;
	ctx.destroy = destroy;
	ctx.getWidth = getWidth;
	ctx.getHeight = getHeight;
	return (ctx);
}
