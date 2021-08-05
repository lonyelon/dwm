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

#include "fibonacci.c"
#include "tcl.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
 	{ "[\\]",     dwindle },
 	{ "[@]",      spiral },
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "|||",      tcl },
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
	{ MODKEY|ControlMask|ShiftMask, XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ControlMask|ShiftMask, XK_s,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ControlMask|ShiftMask, XK_t,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ControlMask|ShiftMask, XK_m,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ControlMask|ShiftMask, XK_3,      setlayout,      {.v = &layouts[4]} },

//  { MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_Up,     focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Down,   focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Up,     movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Down,   movestack,      {.i = +1 } },

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
//	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
//	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
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
