// rGameboot v0.6 , plugin for Custom Firmware 3.0X oe-x by becus25//
#include <stdlib.h>
#include "blib.h"
#include <time.h>
PSP_MODULE_INFO("rGameboot v0.7", 0, 1, 1); /* VSH MODE */

char write_buffer[128*1024];
int num;
SceUID load_module(const char *path, int flags, int type)
{
	SceKernelLMOption option;
	SceUID mpid;

	/* If the type is 0, then load the module in the kernel partition, otherwise load it
	   in the user partition. */
	if (type == 0) {
		mpid = 1;
	} else {
		mpid = 2;
	}

	memset(&option, 0, sizeof(option));
	option.size = sizeof(option);
	option.mpidtext = mpid;
	option.mpiddata = mpid;
	option.position = 0;
	option.access = 1;

	return sceKernelLoadModule(path, flags, type > 0 ? &option : NULL);
}


int main()
{
    SceUID modid;
	
	SceModule *mod;
	
	int ret;
	int fd;
    screeninit();
    
    printf(" rGameboot v0.7 by becus25\n Via : http://becus25.blogspot.com");
    int num;
    srand(time(NULL));

    num=rand()%3; 
    
    sceKernelDelayThread(400000);
    printf("\n Testing opening_plugin.prx... ");
    writetoflashzero("flash0:/vsh/nodule/opening_plugin.prx", "flash0:/vsh/nodule/opening_plug-in.prx");
    printf(" Finally.\n");
    int primero;
	int segundo;
   
	primero = open("ms0:/RG/1/opening_plugin.prx", PSP_O_RDONLY, 0777);
	//Activa el modo lectura/escritura de la FLASH0//
	if(primero < 0){
               num = 1;
               printf("\n\nCorrupted file in ms0:/RG/1/opening_plugin.prx");
               }
	if(num == 0)
	{
        printf("\n\nGameboot redirected to flash0:/vsh/resource");
        sceIoUnassign("flash0:");
        sceIoAssign("flash0:", "lflash0:0,0", "flashfat0:", IOASSIGN_RDWR, NULL, 0);
		int bytesleidos = 1;
		segundo = open("flash0:/vsh/nodule/opening_plugin.prx", PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
		bytesleidos = read(primero, write_buffer, sizeof(write_buffer));
		while((bytesleidos > 0) && (segundo >= 0))
		{
			write(segundo, write_buffer, bytesleidos);
			bytesleidos = read(primero, write_buffer, sizeof(write_buffer));
		}

		if(segundo >= 0)
		{
			close(segundo);
		}

		if(primero >= 0)
		{
			close(primero);
		}
	}
	int primera;
	int segunda;
	primera = open("ms0:/RG/2/opening_plugin.prx", PSP_O_RDONLY, 0777);
	if(primera < 0){
               num = 2;
               printf("\n\nCorrupted file in ms0:/RG/2/opening_plugin.prx");
               }
    if(num == 1)
	{
        printf("\n\nGameboot redirected to flash1:/vsh/resource");
        sceIoUnassign("flash0:");
        sceIoAssign("flash0:", "lflash0:0,0", "flashfat0:", IOASSIGN_RDWR, NULL, 0);
		int bytesleidoss = 1;
		segunda = open("flash0:/vsh/nodule/opening_plugin.prx", PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
		bytesleidoss = read(primera, write_buffer, sizeof(write_buffer));
		while((bytesleidoss > 0) && (segunda >= 0))
		{
			write(segunda, write_buffer, bytesleidoss);
			bytesleidoss = read(primera, write_buffer, sizeof(write_buffer));
		}

		if(segunda >= 0)
		{
			close(segunda);
		}

		if(primera >= 0)
		{
			close(primera);
		}
	}
	int primerb;
	int segundb;
	primerb = open("ms0:/RG/3/opening_plugin.prx", PSP_O_RDONLY, 0777);
	if(primerb < 0){
               num = 0;
               printf("\n\nCorrupted file in ms0:/RG/3/opening_plugin.prx");
               }
    if(num == 2)
	{
        printf("\n\nGameboot redirected to ms0:/PSP/SYSTEM/RG");
        sceIoUnassign("flash0:");
        sceIoAssign("flash0:", "lflash0:0,0", "flashfat0:", IOASSIGN_RDWR, NULL, 0);
		int bytesleidosv = 1;
		segundb = open("flash0:/vsh/nodule/opening_plugin.prx", PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
		bytesleidosv = read(primerb, write_buffer, sizeof(write_buffer));
		while((bytesleidosv > 0) && (segundb >= 0))
		{
			write(segundb, write_buffer, bytesleidosv);
			bytesleidosv = read(primerb, write_buffer, sizeof(write_buffer));
		}

		if(segundb >= 0)
		{
			close(segundb);
		}

		if(primerb >= 0)
		{
			close(primerb);
		}
	}
    
	
	primero = open("ms0:/RG/1/opening_plugin.prx", PSP_O_RDONLY, 0777);
	primera = open("ms0:/RG/2/opening_plugin.prx", PSP_O_RDONLY, 0777);
	primerb = open("ms0:/RG/3/opening_plugin.prx", PSP_O_RDONLY, 0777);
	if(primero < 0){
               if(primera < 0){
                          if(primerb < 0){
                                     exit();
                                     }
                                     }
                                     }
     if(primero >= 0)
		{
			close(primero);
		}
	 if(primera >= 0)
		{
			close(primera);
		}
	 if(primerb >= 0)
		{
			close(primerb);
		}
    
    
    
    printf("\n Starting opening_plug-in.prx...");
    modid = load_module("flash0:/vsh/nodule/opening_plug-in.prx", 0, 0);
    mod = sceKernelFindModuleByUID(modid);     
    if(mod != NULL){
    
	ret = sceKernelStartModule(modid, 0, NULL, &fd, NULL);
	printf(" Done");
	
	sceKernelExitDeleteThread(0);
    }
    
    screensleep();
    return 0;
}
	
	
    
   
    
	


/* Exported function returns the address of module_info */
void* getModuleInfo(void)
{
	return (void *) &module_info;
}
