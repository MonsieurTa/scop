/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:05:04 by wta               #+#    #+#             */
/*   Updated: 2019/11/07 18:16:38 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"
#include "tga_loader.h"

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

static int		load(t_tga_loader *ctx, char *img_path,
	int (*store_data)(t_file *, const char *))
{
	store_data(&ctx->file, img_path);
	ft_printf("TGA(%s): Mapped into memory\n", ctx->file.filepath);
	ft_memcpy(&ctx->header, ctx->file.content, sizeof(t_tga_header));
	if (is_supported_tga(&ctx->header) != -1)
	{
		ft_printf("TGA(%s): Loading...\n", ctx->file.filepath);
		ctx->cm_size = ctx->header.cm_len * (ctx->header.cm_entry_size >> 3);
		ctx->img_size = ctx->getWidth(ctx) * ctx->getHeight(ctx);
		assign_read(ctx);
		get_texel_size(ctx);
		// TODO: Protect malloc
		ctx->data = malloc(sizeof(uint8_t)
			* ctx->getWidth(ctx) * ctx->getHeight(ctx) * ctx->texel_size);
		ctx->read(ctx);
		ft_printf("TGA(%s): Loaded\n", ctx->file.filepath);
		munmap(ctx->file.content, ctx->file.file_stat.st_size);
		ft_printf("TGA(%s): Unmapped from memory\n", ctx->file.filepath);
		return (0);
	}
	return (-1);
}

static void		destroy(t_tga_loader *ctx)
{
	ft_printf("TGA(%s): Data freed from memory\n", ctx->file.filepath);
	ft_memdel(&ctx->data);
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
