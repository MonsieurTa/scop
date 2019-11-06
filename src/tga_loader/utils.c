/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:00:05 by william           #+#    #+#             */
/*   Updated: 2019/11/06 14:35:17 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga_loader.h"

int	is_supported_tga(t_tga_header *header)
{
	if (!header->image_type)
		return (tga_throw_error(ERR_NO_DATA, "No image data detected"));
	return (0);
}
