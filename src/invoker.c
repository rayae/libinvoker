#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	if(argc < 2) return 1;
	setbuf(stdout, NULL);
	char *arg = argv[1];
	argc--;
	argv++;
	if(!strcmp(arg, "mkbootimg")){
		return mkbootimg_main(argc, argv);
	}else if(!strcmp(arg, "unpackbootimg")){
		return unpackbootimg_main(argc, argv);
	}else if(!strcmp(arg, "uncpio")){
		return uncpio_main(argc, argv);
	}else if(!strcmp(arg, "mkcpio")){
		return mkcpio_main(argc, argv);
	}else if(!strcmp(arg, "sdat2img")){
		return sdat2img_main(argc, argv);
	}else if(!strcmp(arg, "img2simg")){
		return img2simg_main(argc, argv);
	}else if(!strcmp(arg, "simg2img")){
		return simg2img_main(argc, argv);
	}else if(!strcmp(arg, "minigzip")){
		return minigzip_main(argc, argv);
	}
	return 1;
}
