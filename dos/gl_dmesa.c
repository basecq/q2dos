/*
** GLW_IMP.C
**
** This file contains ALL Linux specific stuff having to do with the
** OpenGL refresh.  When a port is being made the following functions
** must be implemented by the port:
**
** GLimp_EndFrame
** GLimp_Init
** GLimp_Shutdown
** GLimp_SwitchFullscreen
**
*/

#include <termios.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <stdio.h>

#include "../ref_gl/gl_local.h"
#include "../client/keys.h"
#include "vid_dos.h"

#include <GL/dmesa.h>

/*****************************************************************************/

// Gamma stuff
#define	USE_GAMMA_RAMPS			0

/* 3dfx gamma hacks: stuff are in fx_gamma.c
 * Note: gamma ramps crashes voodoo graphics */
#define	USE_3DFX_RAMPS			0
#if defined(USE_3DFXGAMMA)
#include "fx_gamma.h"
#endif

#if (USE_GAMMA_RAMPS) || (defined(USE_3DFXGAMMA) && (USE_3DFX_RAMPS))
static unsigned short	orig_ramps[3][256];
#endif

static qboolean	fx_gamma   = false;	// 3dfx-specific gamma control
static qboolean	gammaworks = false;	// whether hw-gamma works

#if !defined(USE_3DFXGAMMA)
static inline int Init_3dfxGammaCtrl (void)		{ return 0; }
static inline void Shutdown_3dfxGamma (void)		{ }
static inline int do3dfxGammaCtrl (float value)			{ return 0; }
static inline int glGetDeviceGammaRamp3DFX (void *arrays)	{ return 0; }
static inline int glSetDeviceGammaRamp3DFX (void *arrays)	{ return 0; }
static inline qboolean VID_Check3dfxGamma (void)	{ return false; }
#else
static qboolean VID_Check3dfxGamma (void)
{
	int		ret;

#if USE_3DFX_RAMPS /* not recommended for Voodoo1, currently crashes */
	ret = glGetDeviceGammaRamp3DFX(orig_ramps);
	if (ret != 0)
	{
		ri.Con_Printf(PRINT_ALL, "Using 3dfx glide3 specific gamma ramps\n");
		return true;
	}
#else
	ret = Init_3dfxGammaCtrl();
	if (ret > 0)
	{
		ri.Con_Printf(PRINT_ALL, "Using 3dfx glide%d gamma controls\n", ret);
		return true;
	}
#endif
	return false;
}
#endif	/* USE_3DFXGAMMA */

static void VID_InitGamma (void)
{
	const char *gl_renderer = (const char *)qglGetString (GL_RENDERER);

	gammaworks = fx_gamma = false;
	/* we don't have WGL_3DFX_gamma_control or an equivalent in dos. */
	/* Here is an evil hack abusing the exposed Glide symbols: */
	if (gl_renderer &&
		(!strnicmp(gl_renderer, "3dfx", 4)	  ||
		 !strnicmp(gl_renderer, "SAGE Glide", 10) ||
		 !strnicmp(gl_renderer, "Glide ", 6)	  || /* possible with Mesa 3.x/4.x/5.0.x */
		 !strnicmp(gl_renderer, "Mesa Glide", 10)))
	{
		fx_gamma = VID_Check3dfxGamma();
	}

	if (!gammaworks && !fx_gamma)
		ri.Con_Printf(PRINT_ALL, "gamma adjustment not available\n");
	else	vid_gamma->modified = true;/* let refresh loop update gamma */
}

static void VID_ShutdownGamma (void)
{
#if USE_3DFX_RAMPS
	if (fx_gamma) glSetDeviceGammaRamp3DFX(orig_ramps);
#else
/*	if (fx_gamma) do3dfxGammaCtrl(1);*/
#endif
	Shutdown_3dfxGamma();
}

/*****************************************************************************/

qboolean GLimp_InitGL (void);

extern cvar_t *vid_fullscreen;
extern cvar_t *vid_ref;

static DMesaVisual dv;
static DMesaContext dc;
static DMesaBuffer db;

#define NUM_GL_RESOLUTIONS 8

static vmodeinfo_t resolutions[NUM_GL_RESOLUTIONS] = {
	{ 240,320,  "[320x240]" },
	{ 300,400,  "[400x300]" },
	{ 384,512,  "[512x384]" },
	{ 480,640,  "[640x480]" },
	{ 600,800,  "[800x600]" },
	{ 768,1024,  "[1024x768]" },
	{ 1024,1280,  "[1280x1024]" },
	{ 1200,1600,  "[1600x1200]" }
};

/*
** GLimp_SetMode
*/
rserr_t GLimp_SetMode( int *pwidth, int *pheight, int mode, qboolean fullscreen )
{
	int width, height;

	ri.Con_Printf( PRINT_ALL, "Initializing OpenGL display\n");

	ri.Con_Printf (PRINT_ALL, "...setting mode %d:", mode );

	if ( !ri.Vid_GetModeInfo( &width, &height, mode ) )
	{
		ri.Con_Printf( PRINT_ALL, " invalid mode\n" );
		return rserr_invalid_mode;
	}

	ri.Con_Printf( PRINT_ALL, " %d %d\n", width, height );

	// destroy the existing window
	GLimp_Shutdown ();

	dv = DMesaCreateVisual((GLint)width, (GLint)height, 16, 0, true, true, 2, 16, 0, 0); /* FS: TODO: Add something like ri.COM_CheckParm so we can control bpp to be 15 or 32 on Voodoo 5 */
	if (!dv)
		return rserr_invalid_mode;
	
	dc = DMesaCreateContext(dv, NULL);
	if (!dc)
		return rserr_invalid_mode;
	db = DMesaCreateBuffer(dv, 0,0,(GLint)width,(GLint)height);
	if (!db)
		return rserr_invalid_mode;

	DMesaMakeCurrent(dc, db);

	VID_InitGamma();

	*pwidth = width;
	*pheight = height;

	// let the sound and input subsystems know about the new window
	ri.Vid_NewWindow (width, height);

	return rserr_ok;
}

/*
** GLimp_Shutdown
**
** This routine does all OS specific shutdown procedures for the OpenGL
** subsystem.  Under OpenGL this means NULLing out the current DC and
** HGLRC, deleting the rendering context, and releasing the DC acquired
** for the window.  The state structure is also nulled out.
**
*/
void GLimp_Shutdown( void )
{
	VID_ShutdownGamma();
	if (db)
	{
		DMesaDestroyBuffer(db);
		db = NULL;
	}
	if (dc)
	{
		DMesaDestroyContext(dc);
		dc = NULL;
	}
	if (dv)
	{
		DMesaDestroyVisual(dv);
		dv = NULL;
	}
}

/*
** GLimp_Init
**
** This routine is responsible for initializing the OS specific portions
** of OpenGL.  
*/

int GLimp_Init( void *nummodes, void *modeinfos )
{
	vmodeinfo_t *vi;
	int	i;

	/* HACK HACK HACK: sending the video mode infos to vid_dos.c
	 * by exploiting our params. See: vid_dos.c:VID_LoadRefresh() */
	vi = malloc(sizeof(resolutions) * sizeof(vmodeinfo_t));
	for (i = 0; i < NUM_GL_RESOLUTIONS; ++i)
	{
		vi[i].height = resolutions[i].height;
		vi[i].width = resolutions[i].width;
		strcpy(vi[i].menuname, resolutions[i].menuname);
	}
	*(int *) nummodes = NUM_GL_RESOLUTIONS;
	*(vmodeinfo_t **) modeinfos = vi;

	return true;
}

/*
** GLimp_BeginFrame
*/
void GLimp_BeginFrame( float camera_seperation )
{
}

/*
** GLimp_EndFrame
** 
** Responsible for doing a swapbuffers and possibly for other stuff
** as yet to be determined.  Probably better not to make this a GLimp
** function and instead do a call to GLimp_SwapBuffers.
*/
void GLimp_EndFrame (void)
{
	glFlush();
	DMesaSwapBuffers(db);
}

/*
** GLimp_AppActivate
*/
void GLimp_AppActivate( qboolean active )
{
}

#define GAMMA_MAX	3.0
void UpdateGammaRamp (void)
{
#if (!USE_GAMMA_RAMPS) || (!USE_3DFX_RAMPS)
	float	value = (vid_gamma->value > (1.0 / GAMMA_MAX)) ?
			(1.0 / vid_gamma->value) : GAMMA_MAX;
#endif
#if USE_3DFX_RAMPS
	if (fx_gamma) glSetDeviceGammaRamp3DFX(ramps);
#else
	if (fx_gamma) do3dfxGammaCtrl(value);
#endif
}
