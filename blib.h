// Libreria personalizada , by becus25//
// 01.01.2007 Via: http://www.becus25.blogspot.com //
// Esta libreria incluye funciones para programar sin añadir tantas librerias y con nombres
// más cortos. //
// Actualización 6 el 4.04.2007 a las 12:31 horas //
#include <pspkerneltypes.h>
#include <pspmodulemgr.h>
#include <pspiofilemgr.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <psploadexec.h>
#include <pspkernel.h> // Incluye esta libreria SIEMPRE en tus proyectos!! //
#include <pspumd.h>
#include <pspusb.h>
#include <pspthreadman.h>
#include <pspmodulemgr.h>
#include <string.h>
#include <pspthreadman.h>
// _________________PSP DEBUG_____________________________________ //
#define printf pspDebugScreenPrintf
#define delaythread sceKernelDelayThread
#define exitthread sceKernelExitDeleteThread
#define screeninit pspDebugScreenInit
#define backcolor pspDebugScreenSetBackColor
#define textcolor pspDebugScreenSetTextColor
#define setxy pspDebugScreenSetXY
#define clearscreen pspDebugScreenClear
// Permite cambiar el color del texto //
// Ejemplo 1 : textcolor(0xFFFF0000);
// Ejemplo 2 : textcolor(GREEN);
void pspDebugScreenSetTextColor(u32 color);
// Inicializa la pantalla para poder escribir en ella //
// Ejemplo : screeninit(); //
void pspDebugScreenInit(void);
// Imprime texto en pantalla 
// Ejemplo : printf("Hola Mundo"); //
void pspDebugScreenPrintf(const char *fmt, ...) __attribute__((format(printf,1,2)));
// Permite cambiar el color de fondo //
// Ejemplo 1 : backcolor(0xFFFF0000);
// Ejemplo 2 : backcolor(RED);
void pspDebugScreenSetBackColor(u32 color);
// Permite específicar en coordenadas donde se mostrará el texto //
// Ejemplo: setxy(20,10); //
void pspDebugScreenSetXY(int x, int y);
// Limpia la pantalla //
// Ejemplo : clearscreen; //
void pspDebugScreenClear(void);



// ___________________PSP USB___________________________________ //
#define PSP_USBBUS_DRIVERNAME "USBBusDriver"


#define PSP_USB_ACTIVATED              0x200
#define PSP_USB_CABLE_CONNECTED        0x020 
#define PSP_USB_CONNECTION_ESTABLISHED 0x002
#define startusb sceUsbStart
#define stopusb sceUsbStop
#define ausb sceUsbActivate
#define dusb sceUsbDeactivate
#define stateusb sceUsbGetState
// Inicializa el USB 
// Ejemplo : startusb(PSP_USBSTOR_DRIVERNAME, 0, 0);  //
int sceUsbStart(const char* driverName, int size, void *args);
// Detiene el USB
// Ejemplo: stopusb(PSP_USBSTOR_DRIVERNAME, 0, 0); //
int sceUsbStop(const char* driverName, int size, void *args);
// Activa el USB 
// Ejemplo : ausb(0x1c8); //
int sceUsbActivate(u32 pid);
// Desactiva el USB 
// Ejemplo : dusb(0x1c8); //
int sceUsbDeactivate(u32 pid);
// Devuelve un valor y indica el estado del USB //
// Ejemplo : stateusb(); //
int sceUsbGetState(void);

// ___________________PSP UMD___________________________________ //
#define aumd sceUmdActivate


// Activa el UMD
// Ejemplo : aumd(1, "disc0:");
//           sceUmdWaitDriveStat(UMD_WAITFORINIT); // 
int sceUmdActivate(int unit, const char *drive);

// ___________________PSP IO FILE MGR___________________________________ //

#define open sceIoOpen
#define write sceIoWrite
#define read sceIoRead
#define close sceIoClose
#define remove sceIoRemove
#define mkdir sceIoMkdir
#define rename sceIoRename
// Abre un archivo //
// Nueva función : open //
SceUID sceIoOpen(const char *file, int flags, SceMode mode);
// Escribe un archivo //
// Nueva función : write //
int sceIoWrite(SceUID fd, const void *data, SceSize size);
// Lee un archivo //
// Nueva función : read //
int sceIoRead(SceUID fd, void *data, SceSize size);
// Cierra el archivo //
// Cúando abres un archivo , es muy importante después usar esta función!!...
// si no lo haces la consola se puede bloquear! //
// Nueva función : close //

int sceIoClose(SceUID fd);
// Elimina un archivo 
// Ejemplo : remove("ms0:/xxx.txt"); //
// Nueva función : remove //
int sceIoRemove(const char *file);
// Crea un nuevo directorio //
// Ejemplo : mkdir("ms0:/nuevodirectorio", 0777); //
int sceIoMkdir(const char *dir, SceMode mode);
// Cambia el nombre a un archivo //
// Ejemplo : rename("ms0:/oldname.txt", "ms0:/newname.txt"); //
int sceIoRename(const char *oldname, const char *newname);

// ___________________PSP Kernel Debug___________________________________ //
#define kprintf Kprintf
// Imprime el texto en modo kernel //
// Ejemplo : kprintf("Hola mundo ,imprimido en modo kernel");
// NOTA: Esta función requiere modo kernel, sino no será ejecutada ni el texto será imprimido en pantalla! //
void Kprintf(const char *format, ...) __attribute__((format(printf, 1, 2)));

// ___________________PSP Loadexec___________________________________ //
#define exit sceKernelExitGame
#define loadexec sceKernelLoadExec

// Finaliza el programa o el juego
// Ejemplo : exit();
void sceKernelExitGame(void);
// Ejecuta un nuevo programa //
// Ejemplo : loadexec("ms0:/eboot.pbp", NULL); //
int sceKernelLoadExec(const char *file, struct SceKernelLoadExecParam *param);

// ___________________PSP threadman___________________________________ //
#define screensleep sceKernelSleepThread
#define screensleepcb sceKernelSleepThreadCB
// Pausa la pantalla
// Esta función es necesaria siempre para imprimir información en pantalla !!! //
// Ejemplo : screensleep(); //
int sceKernelSleepThread(void);
// También pausa la pantalla pero permite usar los callbacks 
// Ejemplo : screensleepcb();
int sceKernelSleepThreadCB(void);
void timer(){
     sceKernelDelayThread(400000); /* Stop the screen 1 second
                                       Example : timer();
                                         
                                       */   
}

// ___________________PSP MODULE MGR___________________________________ //
#define loadmodule sceKernelLoadModule
#define loadmodulems sceKernelLoadModuleMs
#define stopmodule sceKernelStopModule
#define unloadmodule sceKernelUnloadModule
// Carga un módulo (prx,elf,pbp, etc...)
// Ejemplo : loadmodule("ms0:/mymodule.prx", 0, NULL); //
SceUID sceKernelLoadModule(const char *path, int flags, SceKernelLMOption *option);
// Carga un módulo desde la Memory Stick
// Ejemplo : loadmodulems("ms0:/mymodule.prx", 0, NULL); //
SceUID sceKernelLoadModuleMs(const char *path, int flags, SceKernelLMOption *option);
// Detiene un módulo
// Ejemplo : mymodule = stopmodule(modid, 0, NULL, &status, NULL);
int sceKernelStopModule(SceUID modid, SceSize argsize, void *argp, int *status, SceKernelSMOption *option);
// Carga un módulo ya cargado anteriormente 
// Ejemplo : SceModule *mymodule;
//           unloadmodule(mymodule->modid); //
int sceKernelUnloadModule(SceUID modid);

// ___________________PSP CTRL___________________________________ //
// Estas funciones simplifican los modos de control de la PSP. //
#define cactivate1 SceCtrlData
#define cactivate2 sceCtrlSetSamplingCycle
#define cactivate3 sceCtrlSetSamplingMode
#define digital PSP_CTRL_MODE_DIGITAL
#define analog PSP_CTRL_MODE_ANALOG
#define cactivate4 sceCtrlReadBufferPositive
#define cross PSP_CTRL_CROSS
#define square PSP_CTRL_SQUARE
#define circle PSP_CTRL_CIRCLE
#define triangle PSP_CTRL_TRIANGLE
#define rtrigger PSP_CTRL_RTRIGGER
#define ltrigger PSP_CTRL_LTRIGGER
#define start PSP_CTRL_START
#define select PSP_CTRL_SELECT
#define dleft PSP_CTRL_LEFT
#define dright PSP_CTRL_RIGHT
#define ddown PSP_CTRL_DOWN
#define dup PSP_CTRL_UP

// Ejemplo de activación de controles usando esta libreria //
// cactivate1 pad;
// cactivate2(0);
// cactivate3(analog);
// 
// while(1){
// cactivate4(&pad, 1);
// if (pad.Buttons & cross)
// {
//         printf("Prueva de botones con la libreria bLib");   
//         }
//         } 

// ___________________PSP SetupCallbacks___________________________________ //
// Ejemplo : SetupCallbacks();          NOTA: introducelo en la función main  NOTA2: No hace falta incluir todo el código de los SetupCallbacks en tu proyecto.  //
#define SetupCallbacks SetupCallbacks
void dump_threadstatus(void);

int done = 0;

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
	done = 1;
	return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();

	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", CallbackThread,
				     0x11, 0xFA0, 0, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}
//_________ SystemCtrl.h from Custom firmware 3.0X OE-X by Dark_AleX _______________//
// NOTA: Estas funciones estan sacadas de la libreria SystemCTRL.h de Dark_AleX //
/** 
 * All of these functions can be accessed in both, SE-C (or later) and
 * HEN-D (or later) in both, normal and devhook
 *
 * All of the functions can be used in both, user or kernel mode.
*/

/**
 * Restart the vsh.
 *
 * @param param - Pointer to a ::SceKernelLoadExecVSHParam structure, or NULL
 *
 * @returns < 0 on some errors.
 *
*/
int sctrlKernelExitVSH(struct SceKernelLoadExecVSHParam *param);

/**
 * Executes a new executable from a disc.
 * It is the function used by the firmware to execute the EBOOT.BIN from a disc.
 *
 * @param file - The file to execute.
 * @param param - Pointer to a ::SceKernelLoadExecVSHParam structure, or NULL.
 *
 * @returns < 0 on some errors. 
*/
int sctrlKernelLoadExecVSHDisc(const char *file, struct SceKernelLoadExecVSHParam *param);

/**
 * Executes a new executable from a disc.
 * It is the function used by the firmware to execute an updater from a disc.
 *
 * @param file - The file to execute.
 * @param param - Pointer to a ::SceKernelLoadExecVSHParam structure, or NULL.
 *
 * @returns < 0 on some errors. 
*/
int sctrlKernelLoadExecVSHDiscUpdater(const char *file, struct SceKernelLoadExecVSHParam *param);

/**
 * Executes a new executable from a memory stick.
 * It is the function used by the firmware to execute an updater from a memory stick.
 *
 * @param file - The file to execute.
 * @param param - Pointer to a ::SceKernelLoadExecVSHParam structure, or NULL.
 *
 * @returns < 0 on some errors. 
*/
int sctrlKernelLoadExecVSHMs1(const char *file, struct SceKernelLoadExecVSHParam *param);

/**
 * Executes a new executable from a memory stick.
 * It is the function used by the firmware to execute games (and homebrew :P) from a memory stick.
 *
 * @param file - The file to execute.
 * @param param - Pointer to a ::SceKernelLoadExecVSHParam structure, or NULL.
 *
 * @returns < 0 on some errors. 
*/
int sctrlKernelLoadExecVSHMs2(const char *file, struct SceKernelLoadExecVSHParam *param);

/**
 * Executes a new executable from a memory stick.
 * It is the function used by the firmware to execute ... ?
 *
 * @param file - The file to execute.
 * @param param - Pointer to a ::SceKernelLoadExecVSHParam structure, or NULL.
 *
 * @returns < 0 on some errors. 
*/
int sctrlKernelLoadExecVSHMs3(const char *file, struct SceKernelLoadExecVSHParam *param);

/**
 * Executes a new executable with the specified apitype
 *
 * @param apitype - The apitype
 * @param file - The file to execute.
 * @param param - Pointer to a ::SceKernelLoadExecVSHParam structure, or NULL.
 *
 * @returns < 0 on some errors. 
*/
int sctrlKernelLoadExecVSHWithApitype(int apitype, const char *file, struct SceKernelLoadExecVSHParam *param);

/**
 * Sets the api type 
 *
 * @param apitype - The apitype to set
 * @returns 0 on success
 *
 * @Note - this will modify also the value of sceKernelBootFrom, since the value of
 * bootfrom is calculated from the apitype
*/
int sctrlKernelSetInitApitype(int apitype);

/**
 * Sets the filename of the launched executable.
 *
 * @param filename - The filename to set
 * @returns 0 on success
*/
int sctrlKernelSetInitFileName(char *filename);

/**
 * Sets the user level of the current thread
 *
 * @param level - The user level
 * @return the previous user level on success
 */
int sctrlKernelSetUserLevel(int level);

/**
 * Sets the devkit version
 * 
 * @param version - The devkit version to set
 * @return 0 on success
 * 
*/
int sctrlKernelSetDevkitVersion(int version);

/**
 * Checks if we are in SE.
 *
 * @returns 1 if we are in SE-C or later, 0 if we are in HEN-D or later,
 * and < 0 (a kernel error code) in any other case
*/
int	sctrlHENIsSE();

/**
 * Checks if we are in Devhook.
 *
 * @returns 1 if we are in SE-C/HEN-D for devhook  or later, 0 if we are in normal SE-C/HEN-D or later,
 * and < 0 (a kernel error code) in any other case
*/
int	sctrlHENIsDevhook();

/**
 * Gets the HEN version
 *
 * @returns - The HEN version
 *
 * HEN D / SE-C :  0x00000400
 */
int sctrlHENGetVersion();

/**
 * Finds a driver
 *
 * @param drvname - The name of the driver (without ":" or numbers)
 *
 * @returns the driver if found, NULL otherwise
 *
 */
PspIoDrv *sctrlHENFindDriver(char *drvname);

/** 
 * Finds a function.
 *
 * @param modname - The module where to search the function
 * @param libname - The library name
 * @nid - The nid of the function
 *
 * @returns - The function address or 0 if not found
 *
*/
u32 sctrlHENFindFunction(char *modname, char *libname, u32 nid);
     /*
     SDK INCORPORATED TO WRITE FILES ON FLASH0 AND FLASH1 by becus25 
     */
void fassign(){ // Activate the flash0 and 1 to read and write files //
    sceIoUnassign("flash0:"); 
    sceIoAssign("flash0:", "lflash0:0,0", "flashfat0:", IOASSIGN_RDWR, NULL, 0);
    sceIoUnassign("flash1:"); 
    sceIoAssign("flash1:", "lflash0:0,1", "flashfat1:", IOASSIGN_RDWR, NULL, 0);
}
void writetoflashone(const char *origen, const char *destino) { // Write a file from Memory Stick to flash1 //
	char write_buffer[128*1024];                                /* Example: */
    sceIoUnassign("flash1:");                               //   writetoflashone("ms0:/file.txt", "flash1:/vsh/file.txt");
    sceIoAssign("flash1:", "lflash0:0,1", "flashfat1:", IOASSIGN_RDWR, NULL, 0);
    int primero;
	int segundo;
    
	primero = open(origen, PSP_O_RDONLY, 0777);
	if(primero < 0){
               
               }
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
	
}
void writetoflashzero(const char *origen, const char *destino) { // Write a file from Memory Stick to flash0 //
	char write_buffer[128*1024];                                /* Example: */
    sceIoUnassign("flash0:");                               //   writetoflashone("ms0:/file.txt", "flash0:/vsh/file.txt");
    sceIoAssign("flash0:", "lflash0:0,0", "flashfat0:", IOASSIGN_RDWR, NULL, 0);
    int primero;
	int segundo;
    
	primero = open(origen, PSP_O_RDONLY, 0777);
	if(primero < 0){
               
               }
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
	
}


