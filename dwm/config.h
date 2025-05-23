/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* alt-tab configuration */
static const unsigned int tabModKey 		= 0x40;	/* if this key is hold the alt-tab functionality stays acitve. This key must be the same as key that is used to active functin altTabStart `*/
static const unsigned int tabCycleKey 		= 0x17;	/* if this key is hit the alt-tab program moves one position forward in clients stack. This key must be the same as key that is used to active functin altTabStart */


/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 16;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 0;       /* vertical padding of bar */
static const int sidepad            = 0;       /* horizontal padding of bar */
static const char *fonts[]          = { "monospace:size=12", "Noto Color Emoji:size=12", "Font Awesome 12 Free:size=12"};
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
// static const char col_cyan[]        = "#005577";
// static const char col_cyan[]        = "#9006c7";
static const char col_cyan[]        = "#030303";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	// { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",      monocle }, /* first entry is default */
	{ "[T]",      tile },    
	{ "><>",      NULL },    /* no layout function means floating behavior */
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };
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
	{ MODKEY|ShiftMask, 			XK_m, 	   spawn,	   SHCMD("st -e btop")},

	
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },

	{ MODKEY|ShiftMask,				XK_j,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,						XK_Tab,    view,           {0} },
	{ MODKEY,             			XK_q,      killclient,     {0} },

	// mode shift
	{ MODKEY,                    	XK_m,      setlayout,      {.v = &layouts[0]} }, // M
	{ MODKEY,                    	XK_t,      setlayout,      {.v = &layouts[1]} }, // T
	{ MODKEY,                    	XK_f,      setlayout,      {.v = &layouts[2]} }, // FF
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	
	{ ALTKEY,						XK_Tab,    altTabStart,    {0} },
    
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	
	// brightness
	{ 0, XF86XK_MonBrightnessUp,   spawn,  SHCMD("brightnessctl set +10%") },
    { 0, XF86XK_MonBrightnessDown, spawn,  SHCMD("brightnessctl set 10%-") },

	// volume
	{ 0, XF86XK_AudioRaiseVolume, spawn, SHCMD("volumeup") },
    { 0, XF86XK_AudioLowerVolume, spawn, SHCMD("volumedown") },
    { 0, XF86XK_AudioMute, spawn, SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle") },

	// sleep / lock
	{ MODKEY,                       XK_l,      spawn,           SHCMD("slock lock") },

	// tags
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	// kill dwm
	{ MODKEY|ShiftMask,             XK_k,      quit,           {0} },

	//not used
	// { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	// { MODKEY,                       XK_l,      focusstack,     {.i = -1 } },
	// { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	// { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	// { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	// { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	// { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	// { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	// { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	// { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button3,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button2,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

