/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_loader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:05:28 by wta               #+#    #+#             */
/*   Updated: 2019/11/06 18:07:03 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TGA_LOADER_H
# define TGA_LOADER_H

# define ALPHA_BITS(x) ((x) & 0xF)

# define ERR_NO_DATA	0x1

# include "scop.h"
# include <stdint.h>

# pragma pack(push, 1)

typedef struct	s_tga_header
{
	uint8_t						id_len;
	uint8_t						color_map_type;
	uint8_t						image_type;

	uint16_t					cm_index;
	uint16_t					cm_len;
	uint8_t						cm_entry_size;

	int16_t						x_origin;
	int16_t						y_origin;
	uint16_t					width;
	uint16_t					height;
	uint8_t						depth;
	uint8_t						descriptor;
}				t_tga_header;

typedef struct	s_tga_loader
{
	t_file				file;
	t_tga_header	header;

	uint32_t			cm_size;
	uint32_t			img_size;
	uint8_t				texel_size;

	void					*color_map;
	void					*data;

	void					(*read)(struct s_tga_loader *);
	int						(*load)(struct s_tga_loader *, char *);
	void					(*destroy)(struct s_tga_loader *);
	int32_t				(*getWidth)(struct s_tga_loader *);
	int32_t				(*getHeight)(struct s_tga_loader *);
}				t_tga_loader;

# pragma pack(pop)

t_tga_loader	new_tga_loader(void);

int32_t				getWidth(t_tga_loader *ctx);
int32_t				getHeight(t_tga_loader *ctx);
int						is_supported_tga(t_tga_header *header);

void					assign_read(t_tga_loader *ctx);

int						tga_throw_error(int err_code, char *msg);

#endif
