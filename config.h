/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */

/* Fonts */
static const char *fonts[]          = { "monospace:size=10", "JoyPixels:size=10" };
static const char dmenufont[]       = "monospace:size=10";

/* Colors */
static const char col_fg[]          = "#fbf1c7";
static const char col_fg_sel[]      = "#1d2021";
static const char col_bg[]          = "#1d2021";
static const char col_bg_sel[]      = "#d65d0e";
static const char col_br[]          = "#282828";
static const char col_br_sel[]      = "#d65d0e";
static const char *colors[][3]      = {
	[SchemeNorm] = { col_fg,     col_bg,     col_br },
	[SchemeSel]  = { col_fg_sel, col_bg_sel, col_br_sel  },
};

static int attachdirection = 3;

/* Allow window selection and movement to operate in a cyclic behavior, i.e.
 * when the master is selected and you try to select it's parent, select the
 * last window in the stack. Uncomment to enable.
 */
//#define ALLOW_WINDOW_CYCLIC_BEHAVIOR

/* Same as above but with monitors */
//#define ALLOW_MONITOR_CYCLIC_BEHAVIOR

/* TODO make the screeCount dynamic so that DWM doesn't have to be recompiled
 * every time it's executed on a different system.
 */
static const int screenCount = 2;

/* tagging */
/* TODO Make tags dynamic. */
static char *tags[] = { "1", "2", "3", "4" };


static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "float",    NULL,       NULL,       1 << 8,       1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "dwindle.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
 	{ "[\\]",     dwindle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      focusnthmon,    {.i  = TAG*screenCount/8} },        \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << (TAG - 8/screenCount*(TAG*screenCount/8))} }, \
    { MODKEY|ShiftMask,             KEY,      tagnthmon,      {.i  = TAG*screenCount/8} },        \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << (TAG - 8/screenCount*(TAG*screenCount/8))} }, \

//                                                                      COMMANDS
////////////////////////////////////////////////////////////////////////////////

static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-l", "30", "-m", dmenumon, "-fn", dmenufont, "-nb", col_bg, "-nf", col_fg, "-sb", col_bg_sel, "-sf", col_fg_sel, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *quteCmd[]  = { "qutebrowser", NULL };
static const char *neomuttCmd[] =  { "st", "-c", "float", "-g", "150x50", "-e",  "neomutt", NULL };
static const char *mailsyncCmd[] = { "st", "-c", "float", "-g",  "80x50", "-e", "mailsync", NULL };
static const char *newsboatCmd[] = { "st", "-c", "float", "-g", "150x50", "-e", "newsboat", NULL };

/* Personal audio hack, you should probably remove it */
static const char *pactlCmd[] = { "pactl", "set-card-profile", "alsa_card.pci-0000_08_00.1", "output:hdmi-stereo-extra4", NULL };

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      spawn,          {.v = quteCmd } },
	{ MODKEY,                       XK_m,      spawn,          {.v = neomuttCmd } },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          {.v = mailsyncCmd } },
	{ MODKEY,                       XK_n,      spawn,          {.v = newsboatCmd } },
	{ MODKEY|ShiftMask,             XK_a,      spawn,          {.v = pactlCmd } },

	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },

	/* Alternating layouts */
	{ MODKEY|ControlMask|ShiftMask, XK_d,      setlayout,      {.v = &layouts[0]} },

//  { MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_Up,     focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Down,   focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Up,     movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Down,   movestack,      {.i = +1 } },

	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },

	{ MODKEY,                       XK_Left,   setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_Right,  setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	{ MODKEY|ShiftMask,             XK_c,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
};
