/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: william <william@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 12:14:27 by william           #+#    #+#             */
/*   Updated: 2019/11/05 12:30:29 by william          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga_loader.h"

int32_t	getWidth(t_tga_loader *ctx)
{
	return ctx->header.width;
}

int32_t	getHeight(t_tga_loader *ctx)
{
	return ctx->header.height;
}
