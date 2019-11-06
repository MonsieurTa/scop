/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:02:39 by william           #+#    #+#             */
/*   Updated: 2019/11/05 15:40:30 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tga_loader.h"

// TODO: Pass t_tga_loader *struct to clean clear the structure before exit

int		tga_throw_error(int err_code, char *msg)
{
	if (!err_code)
		return (err_code);
	ft_putstr_fd("scop:error", STDERR_FILENO);
	ft_putnbr_fd(err_code, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	return (-1);
}
