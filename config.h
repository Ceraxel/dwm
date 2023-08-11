/* See LICENSE file for copyright and license details */
#include <X11/XF86keysym.h>
/* appearance */
static const unsigned int borderpx = 1; /* border pixel size of windows */
static const unsigned int gappx = 2;    /* gaps size between windows */
static const unsigned int snap = 5;     /* snap pixel */
static const unsigned int systraypinning =
    0; /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor
          X */
static const unsigned int systrayspacing = 2; /* systray spacing */
static const int systraypinningfailfirst =
    1; /* 1: if pinning fails, display systray on the first monitor, False:
          display systray on the last monitor*/
static const int showsystray = 1; /* 0 means no systray */
static const int swallowfloating =
    0;                        /* 1 means swallow floating windows by default */
static const int showbar = 1; /* 0 means no bar */
static const int topbar = 1;  /* 0 means bottom bar */
// static const char *fonts[]          = { "monospace:size=10",
// "fontawesome:size=10" };
static const char *fonts[] = {"JetbrainsMono Nerd Font:size=10:style=Bold",
                              "Iosevka Nerd Font:size=10"};
static const char dmenufont[] = "Iosevka Nerd Font:size=10";
static const char *brupcmd[] = {"brightnessctl", "set", "10%+", NULL};
static const char *brdowncmd[] = {"brightnessctl", "set", "10%-", NULL};
// background color
// static const char col_gray1[]       = "#0b0b0b";
static const char col_gray1[] = "#000000";
// inactive window border color
static const char col_blue[] = "#2ac3de";
// font color
static const char col_green[] = "#04db3e";
static const char col_white[] = "#ffffff";
// current tag and current window font color
static const char col_gray4[] = "#0b0f10";
static const char col_gray5[] = "#152238";
// Top bar second color (blue) and active window border color
static const char col_cyan[] = "#1798bc";
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {col_white, col_gray1, col_gray1},
    [SchemeSel] = {col_blue, col_gray1, col_white},
};
// tag names (upper left)
static const char *tags[] = {
    "1", "2", "3", "4", "5", "6", "7", "8", "9",
};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class            instance    title       tags mask     isfloating monitor
    { "Gimp",           NULL,       NULL,       0,            1,           -1 },
    { "firefox",        NULL,       NULL,       1 << 2,       0,           -1 },
    { "mpv",            NULL,       NULL,       1 << 3,       0,           -1 },
    { "Thunar",         NULL,       NULL,       1 << 4,       0,           -1 },
    { "Xarchiver",      NULL,       NULL,       0,            1,           -1
    },*/
    /* class          instance  title           tags mask  isfloating isterminal
       noswallow  monitor */
    {"Gimp", NULL, NULL, 0, 1, 0, 0, -1},
    {"Code", NULL, NULL, 1 << 1, 0, 0, -1, -1},
    {"firefox", NULL, NULL, 1 << 2, 0, 0, -1, -1},
    {"mpv", NULL, NULL, 1 << 3, 0, 0, 0, -1},
    {"qBittorrent", NULL, NULL, 1 << 4, 0, 0, 0, -1},
    {"Xarchiver", NULL, NULL, 0, 1, 0, 0, -1},
    {"St", NULL, NULL, 0, 0, 1, 0, -1},
    {NULL, NULL, "Event Tester", 0, 0, 0, 1, -1}, /* xev */
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    0; /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},
    {"[@]", spiral},
    {"[\\]", dwindle},
    {"|M|", centeredmaster},
    {">M>", centeredfloatingmaster},
    {NULL, NULL},
};
/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
// static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn",
// dmenufont, "-nb", col_gray1, "-nf", col_white, "-sb", col_white, "-sf",
// col_gray4, NULL };
static const char *dmenucmd[] = {"rofi",
                                 "-show",
                                 "drun",
                                 "-theme",
                                 "~/.config/rofi/launchers/type-1/style-5.rasi",
                                 NULL};
static const char *runcmd[] = {"rofi", "-show", "run", NULL};
// static const char *filemanager[] = { "
// launches htop
static const char *monitor[] = {"st", "-e", "htop", NULL};
// sets st as the default terminal
static const char *termcmd[] = {"st", NULL};
static const char *pavuctrl[] = {"pavucontrol", "-t", "3", NULL};
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = {"st", "-t",     scratchpadname,
                                      "-g", "120x34", NULL};
// sets st as the default terminal
// volume controls
static const char *mutevol[] = {"pamixer", "--toggle-mute"};
static const char *upvol[] = {"pamixer", "-i", "5"};
static const char *downvol[] = {"pamixer", "-d", "5"};
static const char *prtscrcmd[] = {"flameshot", "gui", NULL};

#include "shiftview.c"
// static char *endx[] = { "/bin/sh", "-c", "endx", "externalpipe", NULL };
static Key keys[] = {
    /* modifier                     key              function argument */
    {MODKEY, XK_d, spawn, {.v = dmenucmd}},
    {MODKEY | ShiftMask, XK_d, spawn, {.v = runcmd}},
    {MODKEY, XK_Return, spawn, {.v = termcmd}},
    {MODKEY | ShiftMask, XK_Return, togglescratch, {.v = scratchpadcmd}},
    {MODKEY, XK_t, togglebar, {0}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_u, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY, XK_z, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY, XK_q, killclient, {0}},
    {MODKEY | ShiftMask, XK_t, setlayout, {.v = &layouts[0]}},
    //{ MODKEY|ShiftMask,           XK_f,            setlayout,              {.v
    //= &layouts[1]} },
    {MODKEY | ShiftMask, XK_m, setlayout, {.v = &layouts[2]}},
    //{ MODKEY,                     XK_r,            setlayout,              {.v
    //= &layouts[3]} }, { MODKEY|ShiftMask,           XK_r, setlayout, {.v =
    //&layouts[4]} }, { MODKEY,                     XK_o,            setlayout,
    //{.v = &layouts[5]} }, { MODKEY|ShiftMask,           XK_o, setlayout, {.v =
    //&layouts[6]} },
    {0, XF86XK_MonBrightnessUp, spawn, {.v = brupcmd}},
    {0, XF86XK_MonBrightnessDown, spawn, {.v = brdowncmd}},
    {0, XF86XK_AudioLowerVolume, spawn, {.v = downvol}},
    {0, XF86XK_AudioRaiseVolume, spawn, {.v = upvol}},
    {0, XF86XK_AudioMute, spawn, {.v = mutevol}},
    {0, XK_Print, spawn, {.v = prtscrcmd}},
    {MODKEY | ControlMask, XK_comma, cyclelayout, {.i = -1}},
    {MODKEY | ControlMask, XK_period, cyclelayout, {.i = +1}},
    {MODKEY | ShiftMask, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY, XK_minus, setgaps, {.i = -1}},
    {MODKEY, XK_equal, setgaps, {.i = +1}},
    {MODKEY | Mod1Mask, XK_equal, setgaps, {.i = 0}},
    {MODKEY | ShiftMask, XK_minus, setborderpx, {.i = -1}},
    {MODKEY | ShiftMask, XK_equal, setborderpx, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    {MODKEY, XK_grave, shiftviewclients, {.i = +1}},
    {MODKEY | ControlMask, XK_grave, shiftviewclients, {.i = -1}},
    /* {MODKEY, XK_F8, spawn, {.v = upvol}}, */
    /* {MODKEY, XK_F7, spawn, {.v = downvol}}, */
    /* {MODKEY, XK_F5, spawn, {.v = mutevol}}, */
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_q, quit, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = monitor}},
    {ClkStatusText, MODKEY, Button2, spawn, {.v = pavuctrl}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
