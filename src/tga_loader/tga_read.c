/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:08:35 by wta               #+#    #+#             */
/*   Updated: 2019/11/06 18:34:41 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga_loader.h"

static void	tga_read8(t_tga_loader *ctx)
{
	(void)ctx;
}

static void	tga_read16(t_tga_loader *ctx)
{
	(void)ctx;
}

static void	tga_read24(t_tga_loader *ctx)
{
	uint32_t	i;
	uint32_t	total_size;
	uint8_t		*entry_index;
	uint8_t		*data;

	i = 0;
	data = (uint8_t *)ctx->data;
	total_size = ctx->img_size * ctx->texel_size;
	entry_index = ctx->file.content + sizeof(t_tga_header) + ctx->header.id_len + ctx->cm_size;
	while (i < total_size)
	{
		data[i + 2] = entry_index[i];
		data[i + 1] = entry_index[i + 1];
		data[i] = entry_index[i + 2];
		i += ctx->texel_size;
	}
}

static void	tga_read32(t_tga_loader *ctx)
{
	uint32_t	i;
	uint32_t	total_size;
	uint8_t		*entry_index;
	uint8_t		*data;

	i = 0;
	data = (uint8_t *)ctx->data;
	total_size = ctx->img_size * ctx->texel_size;
	entry_index = ctx->file.content + sizeof(t_tga_header) + ctx->header.id_len + ctx->cm_size;
	while (i < total_size)
	{
		data[i + 2] = entry_index[i];
		data[i + 1] = entry_index[i + 1];
		data[i] = entry_index[i + 2];
		data[i + 3] = entry_index[i + 3];
		i += ctx->texel_size;
	}
}

void	assign_read(t_tga_loader *ctx)
{
	if (ctx->header.depth == 8)
		ctx->read = tga_read8;
	else if (ctx->header.depth == 16)
		ctx->read = tga_read16;
	else if (ctx->header.depth == 24)
		ctx->read = tga_read24;
	else if (ctx->header.depth == 32)
		ctx->read = tga_read32;
}
