// Library AllFlash by becus25 //
#include <blib.h>
int punteroa = 0;
int punterob = 0;


// Includes bLib by becus25's //
char write_buffer[128*1024];
void writetoflash(const char *origen, const char *destino) { //Write files//
	int primero;
	int segundo;

	primero = open(origen, PSP_O_RDONLY, 0777);
	if(primero >= 0)
	{
		int bytesleidos = 1;
		segundo = open(destino, PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
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
	clearscreen();
	printf("\nHecho!");
	
		
}
void assignflashone(){//Assign FLASH1 to write files in here //
     sceIoUnassign("flash1:");
     sceIoAssign("flash1:", "lflash0:0,1", "flashfat1:", 0, NULL, 0);
     }
void assignflashcero(){//Assign FLASH0 to write files in here //
     sceIoUnassign("flash0:"); 
	 sceIoAssign("flash0:", "lflash0:0,0", "flashfat0:", 0, NULL, 0);
  }

     
