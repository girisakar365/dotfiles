/* See LICENSE file for copyright and license details. */

// for audio and brightness keys
#include <X11/XF86keysym.h>
#include "fibonacci.c"

/* alt-tab configuration */
static const unsigned int tabModKey 		= 0x40;	/* if this key is hold the alt-tab functionality stays acitve. This key must be the same as key that is used to active functin altTabStart `*/
static const unsigned int tabCycleKey 		= 0x17;	/* if this key is hit the alt-tab program moves one position forward in clients stack. This key must be the same as key that is used to active functin altTabStart */
static const unsigned int tabPosY 			= 1;	/* tab position on Y axis, 0 = bottom, 1 = center, 2 = top */
static const unsigned int tabPosX 			= 1;	/* tab position on X axis, 0 = left, 1 = center, 2 = right */
static const unsigned int maxWTab 			= 600;	/* tab menu width */
static const unsigned int maxHTab 			= 100;	/* tab menu height */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

//fonts
static const char *fonts[]          = { "Liberation Mono:pixelsize=12:antialias=true:autohint=true" };
static const char dmenufont[]       = "Liberation Mono:pixelsize=12:antialias=true:autohint=true";

//color
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[]=",      tile },    /* first entry is default */
	{ "[@]",      spiral },
	{ "[\\]",      dwindle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ ALTKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ ALTKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ ALTKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ ALTKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	
	// spwan
	{ MODKEY, 						XK_1, 	   spawn,	   SHCMD("st -e ranger")}, 
	{ MODKEY, 						XK_2, 	   spawn,	   SHCMD("firefox")}, 
	{ MODKEY, 						XK_3, 	   spawn,	   SHCMD("code")}, 
	{ MODKEY, 						XK_s, 	   spawn,	   {.v = dmenucmd} }, 
	{ MODKEY|ShiftMask,				XK_s,  	   spawn,      SHCMD("flameshot gui") },
	{ MODKEY,            			XK_Return, spawn,      {.v = termcmd } },
	{ MODKEY, 						XK_e, 	   spawn,	   SHCMD("st -e ranger")}, 
	{ MODKEY, 						XK_b, 	   spawn,	   SHCMD("firefox")}, 
	{ MODKEY, 						XK_c, 	   spawn,	   SHCMD("code")},
	{ MODKEY, 						XK_i, 	   spawn,	   SHCMD("st -e btop")},
	

	//toggle bar
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	
	//focus win
	{ MODKEY,                       XK_bracketleft, focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_bracketright, focusstack,    {.i = -1 } },
	
	//stack view
	{ MODKEY|ShiftMask,				XK_h,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,				XK_l,      incnmaster,     {.i = -1 } },
	
	//increase/decrease master area
	{ MODKEY,                       XK_j,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_k,      setmfact,       {.f = +0.05} },
	
	//zoom
	{ MODKEY,                       XK_u,	   zoom,           {0} },

	//toggle tag
	{ MODKEY,                       XK_Tab,    view,           {0} },
	
	//set layouts
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_d,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_d,      setlayout,      {.v = &layouts[4]} },
	
	//toggle layouts
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	//toggle floating
	{ MODKEY|ShiftMask,             XK_f,      togglefloating, {0} },
	
	//veiw all windows
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	//tag all windows
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

	//multimonitor setup
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	//xrdb
	{ MODKEY, 				XF86XK_AudioPlay,  spawn,           SHCMD("xrdb -merge ~/.Xresources") },

	{ ALTKEY,                       XK_Tab,    altTabStart,           {0} },
	
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	
	{ MODKEY,             			XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	// restart dwm
	{ MODKEY|ShiftMask, 			XK_r,      quit,           {1} }, 

	// sleep / lock
	{ MODKEY,                       XK_l,      spawn,           SHCMD("slock lock") },
	// shutdown
	{ MODKEY,             			XK_x,      spawn,           SHCMD("shutdown now") },

	// brightness
	{ 0, XF86XK_MonBrightnessUp,   spawn,  SHCMD("brightnessctl set +5%") },
	{ 0, XF86XK_MonBrightnessDown, spawn,  SHCMD("brightnessctl set 5%-") },

	// volume
	{ 0, XF86XK_AudioRaiseVolume, spawn, SHCMD("volumeup") },
	{ 0, XF86XK_AudioLowerVolume, spawn, SHCMD("volumedown") },
	{ 0, XF86XK_AudioMute, 		  spawn, SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

