#include "tga_loader.h"
#include "stdio.h"

int main()
{
	t_tga_loader	loader;

	loader = new_tga_loader();
	loader.load(&loader, "resources/textures/alpha_test.tga");
	printf("img id: %d\n", loader.header.id_len);
	printf("img type: %d\n", loader.header.image_type);
	printf("color map type: %d\n", loader.header.color_map_type);
	printf("width: %d\n", loader.header.width);
	printf("height: %d\n", loader.header.height);
	printf("bpp: %d\n", loader.header.depth);
	printf("alpha bits: %d\n", ALPHA_BITS(loader.header.descriptor));
	printf("xO: %d\n", loader.header.x_origin);
	printf("yO: %d\n", loader.header.y_origin);
	printf("map color bpp: %d\n", loader.header.cm_entry_size);
	printf("map len: %d\n", loader.header.cm_len);
	printf("index: %d\n", loader.header.cm_index);
}