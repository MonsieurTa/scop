#include "tga_loader.h"
#include "stdio.h"

void	display_test(t_tga_loader *ctx)
{
	printf("========== %s ==========\n", ctx->file.filepath);
	printf("img id: %d\n", ctx->header.id_len);
	printf("img type: %d\n", ctx->header.image_type);
	printf("color map type: %d\n", ctx->header.color_map_type);

	printf("width: %d\n", ctx->header.width);
	printf("height: %d\n", ctx->header.height);
	printf("bpp: %d\n", ctx->header.depth);
	printf("alpha bits: %d\n", ALPHA_BITS(ctx->header.descriptor));

	printf("xO: %d\n", ctx->header.x_origin);
	printf("yO: %d\n", ctx->header.y_origin);
	printf("map color bpp: %d\n", ctx->header.cm_entry_size);
	printf("map len: %d\n", ctx->header.cm_len);
	printf("index: %d\n", ctx->header.cm_entry_size);
	printf("sizeof tga header: %d\n", sizeof(t_tga_header));
	printf("file size: %d\n", ctx->file.file_stat.st_size);
	printf("========== %s ==========\n\n", ctx->file.filepath);
}

int main()
{
	t_tga_loader	loader;

	loader = new_tga_loader();
	loader.load(&loader, "resources/textures/img1.tga");
	display_test(&loader);
	loader.destroy(&loader);

	loader.load(&loader, "resources/textures/awesomeface.tga");
	display_test(&loader);
	loader.destroy(&loader);

}
