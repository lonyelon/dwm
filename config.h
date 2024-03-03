/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */

/* Fonts */
static const char *fonts[]          = { "SourceCodePro:size=10", "JoyPixels:size=10" };
static const char dmenufont[]       = "SourceCodePro:size=10";

/* Colors */
static const char col_fg[]          = "#fbf1c7";
static const char col_fg_sel[]      = "#fbf1c7";
static const char col_bg[]          = "#1d2021";
static const char col_bg_sel[]      = "#458588";
static const char col_br[]          = "#282828";
static const char col_br_sel[]      = "#458588";
static const char *colors[][3]      = {
	[SchemeNorm] = { col_fg,     col_bg,     col_br },
	[SchemeSel]  = { col_fg_sel, col_bg_sel, col_br_sel  },
};

static int attachdirection = 3;

/* Allow window selection and movement to operate in a cyclic behavior, i.e.
 * when the master is selected and you try to select it's parent, select the
 * last window in the stack. Uncomment to enable.
 */
//#define WINDOW_CYCLIC_BEHAVIOR

/* Same as above but with monitors */
//#define MONITOR_CYCLIC_BEHAVIOR

/* If defined, windows will move between monitors like if they shared a single
 * stack.
 */
#define MONS_SHARE_STACK

/*
 * XF86 Keys. very useful for laptops.
 */
#define defSink    "43"  /* Default alsa sink */
#define sinkVolInc "+5%" /* Percentage of volume increased for each key press */ 
#define sinkVolDec "-5%" /* Percentage of volume decreased for each key press */
#define defSource  "42"  /* Default alsa source */
#define brnInc     "5"   /* Brightness increment and decrement amount */

/* tagging */
/* TODO Make tags dynamic. */
static char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0" };


static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "float",    NULL,       NULL,       0,            1,           0 },
};

/* layout(s) */
static const float mfact        = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;    /* number of clients in master area */
static const int resizehints    = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "dwindle.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[\\]",     dwindle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \


//                                                                      COMMANDS
////////////////////////////////////////////////////////////////////////////////

static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *termcmd[]      = { "st",         NULL };
static const char *librewolfCmd[] = { "librewolf",  NULL };
static const char *dmenucmd[]     = { "dmenu_run",  "-l", "30",     "-m", dmenumon,  "-fn", dmenufont,  "-nb", col_bg, "-nf", col_fg, "-sb", col_bg_sel, "-sf", col_fg_sel, NULL };
static const char *neomuttCmd[]   = { "st",         "-g", "150x50", "-e", "neomutt", NULL };
static const char *mailsyncCmd[]  = { "st",         "-c", "float",  "-g", "60x30",   "-e",  "mbsync",   "-a",  NULL };
static const char *nvimCmd[]      = { "st",         "-e", "nvim",   NULL };

#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key                       function        argument */
	{ MODKEY,                       XK_d,                     spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,                spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,                     spawn,          {.v = librewolfCmd} },
	{ MODKEY,                       XK_m,                     spawn,          {.v = neomuttCmd } },
	{ MODKEY|ShiftMask,             XK_m,                     spawn,          {.v = mailsyncCmd } },
	{ MODKEY,                       XK_n,                     spawn,          {.v = nvimCmd } },

	{ MODKEY|ShiftMask,             XK_q,                     killclient,     {0} },

	/* Alternating layouts */
	{ MODKEY|ControlMask|ShiftMask, XK_d,                     setlayout,      {.v = &layouts[0]} },

	{ MODKEY,                       XK_Up,                    focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Down,                  focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Up,                    movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Down,                  movestack,      {.i = +1 } },

	{ MODKEY,                       XK_Left,                  setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_Right,                 setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_space,                 togglefloating, {0} },

	TAGKEYS(                        XK_comma,                 0)
	TAGKEYS(                        XK_period,                1)
	TAGKEYS(                        XK_ntilde,                2)
	TAGKEYS(                        XK_p,                     3)
	TAGKEYS(                        XK_y,                     4)
	TAGKEYS(                        XK_f,                     5)
	TAGKEYS(                        XK_g,                     6)
	TAGKEYS(                        XK_c,                     7)
	TAGKEYS(                        XK_h,                     8)
	TAGKEYS(                        XK_l,                     9)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
};
