/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>
/* appearance */
static const unsigned int borderpx       = 1;   /* border pixel of windows */
static const unsigned int snap           = 32;  /* snap pixel */
static const int swallowfloating         = 1;   /* 1 means swallow floating windows by default */
static const unsigned int gappih         = 4;  /* horiz inner gap between windows */
static const unsigned int gappiv         = 4;  /* vert inner gap between windows */
static const unsigned int gappoh         = 4;  /* horiz outer gap between windows and screen edge */
static const unsigned int gappov         = 4;  /* vert outer gap between windows and screen edge */
static const int smartgaps_fact          = 1;   /* gap factor when there is only one client; 0 = no gaps, 3 = 3x outer gaps */
static const char autostartblocksh[]     = "autostart_blocking.sh";
static const char autostartsh[]          = "autostart.sh";
static const char dwmdir[]               = "dwm";
static const char localshare[]           = ".local/share";
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 1;   /* 0 means bottom bar */
static const int vertpad                 = 0;  /* vertical padding of bar */
static const int sidepad                 = 0;  /* horizontal padding of bar */
/* Status is to be shown on: -1 (all monitors), 0 (a specific monitor by index), 'A' (active monitor) */
static const int statusmon               = 'A';
static const unsigned int systrayspacing = 1;   /* systray spacing */
static const int showsystray             = 1;   /* 0 means no systray */



/* Indicators: see patch/bar_indicators.h for options */
static int tagindicatortype              = INDICATOR_TOP_LEFT_SQUARE;
static int tiledindicatortype            = INDICATOR_NONE;
static int floatindicatortype            = INDICATOR_TOP_LEFT_SQUARE;
static int fakefsindicatortype           = INDICATOR_PLUS;
static int floatfakefsindicatortype      = INDICATOR_PLUS_AND_LARGER_SQUARE;
static const char *fonts[]               = { "BerkeleyMono Nerd Font:size=10:style=Bold" };
static const char dmenufont[]            = "BerkeleyMono Nerd Font:size=10:style=Bold";

static char c000000[]                    = "#000000"; // placeholder value

static char normfgcolor[]                = "#bbbbbb";
static char normbgcolor[]                = "#1b1b1b";
static char normbordercolor[]            = "#444444";
static char normfloatcolor[]             = "#96df71";

static char selfgcolor[]                 = "#eeeeee";
static char selbgcolor[]                 = "#005577";
static char selbordercolor[]             = "#005577";
static char selfloatcolor[]              = "#005577";

static char titlenormfgcolor[]           = "#bbbbbb";
static char titlenormbgcolor[]           = "#1b1b1b";
static char titlenormbordercolor[]       = "#444444";
static char titlenormfloatcolor[]        = "#96df71";

static char titleselfgcolor[]            = "#eeeeee";
static char titleselbgcolor[]            = "#005577";
static char titleselbordercolor[]        = "#005577";
static char titleselfloatcolor[]         = "#005577";

static char tagsnormfgcolor[]            = "#bbbbbb";
static char tagsnormbgcolor[]            = "#1b1b1b";
static char tagsnormbordercolor[]        = "#444444";
static char tagsnormfloatcolor[]         = "#96df71";

static char tagsselfgcolor[]             = "#eeeeee";
static char tagsselbgcolor[]             = "#005577";
static char tagsselbordercolor[]         = "#005577";
static char tagsselfloatcolor[]          = "#005577";

static char hidnormfgcolor[]             = "#005577";
static char hidselfgcolor[]              = "#08e7c5";
static char hidnormbgcolor[]             = "#1b1b1b";
static char hidselbgcolor[]              = "#1b1b1b";

static char urgfgcolor[]                 = "#bbbbbb";
static char urgbgcolor[]                 = "#1b1b1b";
static char urgbordercolor[]             = "#ff0000";
static char urgfloatcolor[]              = "#96df71";

static char scratchselfgcolor[]          = "#FFF7D4";
static char scratchselbgcolor[]          = "#1b1b1b";
static char scratchselbordercolor[]      = "#005577";
static char scratchselfloatcolor[]       = "#005577";

static char scratchnormfgcolor[]         = "#FFF7D4";
static char scratchnormbgcolor[]         = "#1b1b1b";
static char scratchnormbordercolor[]     = "#005577";
static char scratchnormfloatcolor[]      = "#005577";



static char *colors[][ColCount] = {
	/*                       fg                bg                border                float */
	[SchemeNorm]         = { normfgcolor,      normbgcolor,      normbordercolor,      normfloatcolor },
	[SchemeSel]          = { selfgcolor,       selbgcolor,       selbordercolor,       selfloatcolor },
	[SchemeTitleNorm]    = { titlenormfgcolor, titlenormbgcolor, titlenormbordercolor, titlenormfloatcolor },
	[SchemeTitleSel]     = { titleselfgcolor,  titleselbgcolor,  titleselbordercolor,  titleselfloatcolor },
	[SchemeTagsNorm]     = { tagsnormfgcolor,  tagsnormbgcolor,  tagsnormbordercolor,  tagsnormfloatcolor },
	[SchemeTagsSel]      = { tagsselfgcolor,   tagsselbgcolor,   tagsselbordercolor,   tagsselfloatcolor },
	[SchemeHidNorm]      = { hidnormfgcolor,   hidnormbgcolor,   c000000,              c000000 },
	[SchemeHidSel]       = { hidselfgcolor,    hidselbgcolor,    c000000,              c000000 },
	[SchemeUrg]          = { urgfgcolor,       urgbgcolor,       urgbordercolor,       urgfloatcolor },
	[SchemeScratchSel]  = { scratchselfgcolor, scratchselbgcolor, scratchselbordercolor, scratchselfloatcolor },
	[SchemeScratchNorm] = { scratchnormfgcolor, scratchnormbgcolor, scratchnormbordercolor, scratchnormfloatcolor },
};




static const char *scratchpadcmd[] = {"s", "alacritty", "-n", "spterm", NULL};

/* Tags
 * In a traditional dwm the number of tags in use can be changed simply by changing the number
 * of strings in the tags array. This build does things a bit different which has some added
 * benefits. If you need to change the number of tags here then change the NUMTAGS macro in dwm.c.
 *
 * Examples:
 *
 *  1) static char *tagicons[][NUMTAGS*2] = {
 *         [DEFAULT_TAGS] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I" },
 *     }
 *
 *  2) static char *tagicons[][1] = {
 *         [DEFAULT_TAGS] = { "•" },
 *     }
 *
 * The first example would result in the tags on the first monitor to be 1 through 9, while the
 * tags for the second monitor would be named A through I. A third monitor would start again at
 * 1 through 9 while the tags on a fourth monitor would also be named A through I. Note the tags
 * count of NUMTAGS*2 in the array initialiser which defines how many tag text / icon exists in
 * the array. This can be changed to *3 to add separate icons for a third monitor.
 *
 * For the second example each tag would be represented as a bullet point. Both cases work the
 * same from a technical standpoint - the icon index is derived from the tag index and the monitor
 * index. If the icon index is is greater than the number of tag icons then it will wrap around
 * until it an icon matches. Similarly if there are two tag icons then it would alternate between
 * them. This works seamlessly with alternative tags and alttagsdecoration patches.
 */
static char *tagicons[][NUMTAGS] =
{
	[DEFAULT_TAGS]        = { "1", "2", "3", "4", "5", "6", "7", "8", "9" },
	[ALTERNATIVE_TAGS]    = { "A", "B", "C", "D", "E", "F", "G", "H", "I" },
	[ALT_TAGS_DECORATION] = { "<1>", "<2>", "<3>", "<4>", "<5>", "<6>", "<7>", "<8>", "<9>" },
};


/* There are two options when it comes to per-client rules:
 *  - a typical struct table or
 *  - using the RULE macro
 *
 * A traditional struct table looks like this:
 *    // class      instance  title  wintype  tags mask  isfloating  monitor
 *    { "Gimp",     NULL,     NULL,  NULL,    1 << 4,    0,          -1 },
 *    { "Firefox",  NULL,     NULL,  NULL,    1 << 7,    0,          -1 },
 *
 * The RULE macro has the default values set for each field allowing you to only
 * specify the values that are relevant for your rule, e.g.
 *
 *    RULE(.class = "Gimp", .tags = 1 << 4)
 *    RULE(.class = "Firefox", .tags = 1 << 7)
 *
 * Refer to the Rule struct definition for the list of available fields depending on
 * the patches you enable.
 */
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 *	WM_WINDOW_ROLE(STRING) = role
	 *	_NET_WM_WINDOW_TYPE(ATOM) = wintype
	 */
	RULE(.wintype = WTYPE "DIALOG", .isfloating = 1)
	RULE(.wintype = WTYPE "UTILITY", .isfloating = 1)
	RULE(.wintype = WTYPE "TOOLBAR", .isfloating = 1)
	RULE(.wintype = WTYPE "SPLASH", .isfloating = 1)
	RULE(.class = "Gimp", .tags = 1 << 4)
	RULE(.class = "firefox", .tags = 1 << 2)
	RULE(.class = "st-256color", .isterminal = 1)
	RULE(.class = "Alacritty", .isterminal = 1)
    RULE(.class = "kitty", .isterminal = 1)
	RULE(.class = "qBittorrent", .tags = 1 << 4)
	RULE(.class = "Xarchiver", .isfloating = 1)
	RULE(.class = "mpv", .noswallow = 1, .tags = 1 << 3)
	RULE(.title = "Event Tester", .noswallow = 1)
    RULE(.class = "jetbrains-clion", .isfloating = 0)
};

static const MonitorRule monrules[] = {
	/* monitor  tag   layout  mfact  nmaster  showbar  topbar */
	{  1,       -1,   2,      -1,    -1,      -1,      -1     }, // use a different layout for the second monitor
	{  -1,      -1,   0,      -1,    -1,      -1,      -1     }, // default
};


/* Bar rules allow you to configure what is shown where on the bar, as well as
 * introducing your own bar modules.
 *
 *    monitor:
 *      -1  show on all monitors
 *       0  show on monitor 0
 *      'A' show on active monitor (i.e. focused / selected) (or just -1 for active?)
 *    bar - bar index, 0 is default, 1 is extrabar
 *    alignment - how the module is aligned compared to other modules
 *    widthfunc, drawfunc, clickfunc - providing bar module width, draw and click functions
 *    name - does nothing, intended for visual clue and for logging / debugging
 */
static const BarRule barrules[] = {
	/* monitor   bar    alignment         widthfunc                 drawfunc                clickfunc                hoverfunc                name */
	{ -1,        0,     BAR_ALIGN_LEFT,   width_tags,               draw_tags,              click_tags,              hover_tags,              "tags" },
	{  0,        0,     BAR_ALIGN_RIGHT,  width_systray,            draw_systray,           click_systray,           NULL,                    "systray" },
	{ -1,        0,     BAR_ALIGN_LEFT,   width_ltsymbol,           draw_ltsymbol,          click_ltsymbol,          NULL,                    "layout" },
    { statusmon, 0,     BAR_ALIGN_RIGHT,  width_status2d,           draw_status2d,          click_status,            NULL,                    "status" },
	{ -1,        0,     BAR_ALIGN_NONE,   width_awesomebar,         draw_awesomebar,        click_awesomebar,        NULL,                    "awesomebar" },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int nstack      = 0;    /* number of clients in primary stack area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int decorhints  = 1;    /* 1 means respect decoration hints */


/* mouse scroll resize */
static const int scrollsensetivity = 30; /* 1 means resize window by 1 pixel for each scroll event */
/* resizemousescroll direction argument list */
static const int scrollargs[][2] = {
	/* width change         height change */
	{ +scrollsensetivity,	0 },
	{ -scrollsensetivity,	0 },
	{ 0, 				  	+scrollsensetivity },
	{ 0, 					-scrollsensetivity },
};

static const Layout layouts[] = {
	/* symbol     arrange function, { nmaster, nstack, layout, master axis, stack axis, secondary stack axis, symbol func } */
	{ "[D]",      flextile,         { -1, -1, SPLIT_VERTICAL, TOP_TO_BOTTOM, MONOCLE, 0, NULL } }, // deck
 	{ "><>",      NULL,             {0} },    /* no layout function means floating behavior */
	{ "[M]",      flextile,         { -1, -1, NO_SPLIT, MONOCLE, MONOCLE, 0, NULL } }, // monocle
	{ "|||",      flextile,         { -1, -1, SPLIT_VERTICAL, LEFT_TO_RIGHT, TOP_TO_BOTTOM, 0, NULL } }, // columns (col) layout
	{ ">M>",      flextile,         { -1, -1, FLOATING_MASTER, LEFT_TO_RIGHT, LEFT_TO_RIGHT, 0, NULL } }, // floating master
	{ "[]=",      flextile,         { -1, -1, SPLIT_VERTICAL, TOP_TO_BOTTOM, TOP_TO_BOTTOM, 0, NULL } }, // default tile layout
	{ "TTT",      flextile,         { -1, -1, SPLIT_HORIZONTAL, LEFT_TO_RIGHT, LEFT_TO_RIGHT, 0, NULL } }, // bstack
	{ "===",      flextile,         { -1, -1, SPLIT_HORIZONTAL, LEFT_TO_RIGHT, TOP_TO_BOTTOM, 0, NULL } }, // bstackhoriz
	{ "|M|",      flextile,         { -1, -1, SPLIT_CENTERED_VERTICAL, LEFT_TO_RIGHT, TOP_TO_BOTTOM, TOP_TO_BOTTOM, NULL } }, // centeredmaster
	{ "-M-",      flextile,         { -1, -1, SPLIT_CENTERED_HORIZONTAL, TOP_TO_BOTTOM, LEFT_TO_RIGHT, LEFT_TO_RIGHT, NULL } }, // centeredmaster horiz
	{ ":::",      flextile,         { -1, -1, NO_SPLIT, GAPPLESSGRID, GAPPLESSGRID, 0, NULL } }, // gappless grid
	{ "[\\]",     flextile,         { -1, -1, NO_SPLIT, DWINDLE, DWINDLE, 0, NULL } }, // fibonacci dwindle
	{ "(@)",      flextile,         { -1, -1, NO_SPLIT, SPIRAL, SPIRAL, 0, NULL } }, // fibonacci spiral
	{ "[T]",      flextile,         { -1, -1, SPLIT_VERTICAL, LEFT_TO_RIGHT, TATAMI, 0, NULL } }, // tatami mats
	{ "[]=",      tile,             {0} },
	{ "[M]",      monocle,          {0} },
	{ "TTT",      bstack,           {0} },
	{ "[D]",      deck,             {0} },
	{ "(@)",      spiral,           {0} },
	{ "[\\]",     dwindle,          {0} },
};


/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      combotag,       {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },



/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
	"dmenu_run",
	// "-m", dmenumon,
	// "-fn", dmenufont,
	// "-nb", normbgcolor,
	// "-nf", normfgcolor,
	// "-sb", "#073642",
	// "-sf", selfgcolor,
	NULL
};
static const char *termcmd[]  = { "alacritty", NULL };
static const char *thunarcmd[]  = { "thunar", NULL };
static const char *mutevol[] = {"pamixer", "--toggle-mute"};
static const char *upvol[] = {"pamixer", "-i", "2"};
static const char *downvol[] = {"pamixer", "-d", "2"};
static const char *prtscrcmd[] = {"flameshot", "gui", NULL};
static const char *brupcmd[] = {"brightnessctl", "set", "10%+", NULL};
static const char *brdowncmd[] = {"brightnessctl", "set", "10%-", NULL};
static const char *dmenu_desktop[] = {"j4-dmenu-desktop", "--dmenu=\"dmenu\"", "NULL"};
static const char *monitor_ext[] = {"monitor-ext.sh", "NULL"};
static const char *monitor_int[] = {"monitor-int.sh", "NULL"};



static const Key keys[] = {
	/* modifier                     key            function                argument */
	{ MODKEY,                       XK_d,          spawn,                  {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_d,          spawn,                  {.v = dmenu_desktop } },
	{ MODKEY,                       XK_Return,     spawn,                  {.v = termcmd } },
	{ MODKEY,                       XK_b,          togglebar,              {0} },
	{ MODKEY|ShiftMask,             XK_b,          toggletopbar,           {0} },
	{ MODKEY,                       XK_j,          focusstack,             {.i = +1 } },
	{ MODKEY,                       XK_k,          focusstack,             {.i = -1 } },
	{ MODKEY|ControlMask,           XK_Left,       placedir,               {.i = 0 } }, // left
	{ MODKEY|ControlMask,           XK_Right,      placedir,               {.i = 1 } }, // right
	{ MODKEY|ControlMask,           XK_Up,         placedir,               {.i = 2 } }, // up
	{ MODKEY|ControlMask,           XK_Down,       placedir,               {.i = 3 } }, // down
	/* { MODKEY,                       XK_i,          incnmaster,             {.i = +1 } }, */
	/* { MODKEY,                       XK_d,          incnmaster,             {.i = -1 } }, */
	{ MODKEY|ControlMask,           XK_i,          incnstack,              {.i = +1 } },
	{ MODKEY|ControlMask,           XK_u,          incnstack,              {.i = -1 } },
	{ MODKEY,                       XK_h,          setmfact,               {.f = -0.05} },
	{ MODKEY,                       XK_l,          setmfact,               {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,          setcfact,               {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,          setcfact,               {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,          setcfact,               {0} },
	{ MODKEY,                       XK_z,          zoom,                   {0} },
	{ MODKEY|Mod1Mask,              XK_u,          incrgaps,               {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_u,          incrgaps,               {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_i,          incrigaps,              {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_i,          incrigaps,              {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_o,          incrogaps,              {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_o,          incrogaps,              {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_6,          incrihgaps,             {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_6,          incrihgaps,             {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_7,          incrivgaps,             {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_7,          incrivgaps,             {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_8,          incrohgaps,             {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_8,          incrohgaps,             {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_9,          incrovgaps,             {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_9,          incrovgaps,             {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,          togglegaps,             {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,          defaultgaps,            {0} },
	{ MODKEY,                       XK_Tab,        view,                   {0} },
	{ MODKEY|Mod1Mask,              XK_Tab,        shiftviewclients,       { .i = -1 } },
	{ MODKEY|Mod1Mask,              XK_backslash,  shiftviewclients,       { .i = +1 } },
	{ MODKEY|ControlMask,           XK_Left,       shiftboth,              { .i = -1 } }, // note keybinding conflict with focusadjacenttag tagandviewtoleft placedir
	{ MODKEY|ControlMask,           XK_Right,      shiftboth,              { .i = +1 } }, // note keybinding conflict with focusadjacenttag tagandviewtoright placedir
	{ MODKEY|ControlMask,           XK_z,          showhideclient,         {0} },
	{ MODKEY,                       XK_q,          killclient,             {0} },
	{ MODKEY|ShiftMask,             XK_q,          quit,                   {0} },
	{ MODKEY,                       XK_t,          setlayout,              {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,          setlayout,              {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,          setlayout,              {.v = &layouts[2]} },
	{ MODKEY|ControlMask,           XK_t,          rotatelayoutaxis,       {.i = +1 } },   /* flextile, 1 = layout axis */
	{ MODKEY|ControlMask,           XK_Tab,        rotatelayoutaxis,       {.i = +2 } },   /* flextile, 2 = master axis */
	{ MODKEY|ControlMask|ShiftMask, XK_Tab,        rotatelayoutaxis,       {.i = +3 } },   /* flextile, 3 = stack axis */
	{ MODKEY|ControlMask|Mod1Mask,  XK_Tab,        rotatelayoutaxis,       {.i = +4 } },   /* flextile, 4 = secondary stack axis */
	{ MODKEY|Mod5Mask,              XK_t,          rotatelayoutaxis,       {.i = -1 } },   /* flextile, 1 = layout axis */
	{ MODKEY|Mod5Mask,              XK_Tab,        rotatelayoutaxis,       {.i = -2 } },   /* flextile, 2 = master axis */
	{ MODKEY|Mod5Mask|ShiftMask,    XK_Tab,        rotatelayoutaxis,       {.i = -3 } },   /* flextile, 3 = stack axis */
	{ MODKEY|Mod5Mask|Mod1Mask,     XK_Tab,        rotatelayoutaxis,       {.i = -4 } },   /* flextile, 4 = secondary stack axis */
	{ MODKEY|ControlMask,           XK_Return,     mirrorlayout,           {0} },          /* flextile, flip master and stack areas */
	{ MODKEY,                       XK_space,      setlayout,              {0} },
	{ MODKEY|ShiftMask,             XK_space,      togglefloating,         {0} },
	{ MODKEY,                       XK_grave,      togglescratch,          {.v = scratchpadcmd } },
	{ MODKEY|ControlMask,           XK_grave,      setscratch,             {.v = scratchpadcmd } },
	{ MODKEY|ShiftMask,             XK_grave,      removescratch,          {.v = scratchpadcmd } },
	{ MODKEY,                       XK_y,          togglefullscreen,       {0} },
	{ MODKEY|ShiftMask,             XK_y,          togglefakefullscreen,   {0} },
	{ MODKEY,                       XK_0,          view,                   {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,          tag,                    {.ui = ~0 } },
	{ MODKEY,                       XK_comma,      focusmon,               {.i = -1 } },
	{ MODKEY,                       XK_period,     focusmon,               {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,      tagmon,                 {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,     tagmon,                 {.i = +1 } },
	{ MODKEY|ControlMask,           XK_comma,      cyclelayout,            {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period,     cyclelayout,            {.i = +1 } },
	{ MODKEY,                       XK_F1,         mpdchange,              {.i = -1} },
	{ MODKEY,                       XK_F2,         mpdchange,              {.i = +1} },
	{ MODKEY,                       XK_Escape,     mpdcontrol,             {0} },
    // Custom shortcuts
	{ MODKEY,                       XK_e,          spawn,                  {.v = thunarcmd } },
	{ MODKEY,                       XK_i,          spawn,                  {.v = monitor_int } },
	{ MODKEY|ShiftMask,             XK_i,          spawn,                  {.v = monitor_ext } },
    {0,                             XK_Print,      spawn,                  {.v = prtscrcmd}},
    {0,                   XF86XK_MonBrightnessUp,  spawn,                  {.v = brupcmd}},
    {0,                  XF86XK_MonBrightnessDown, spawn,                  {.v = brdowncmd}},
    {0,                  XF86XK_AudioLowerVolume,  spawn,                  {.v = downvol}},
    {0,                  XF86XK_AudioRaiseVolume,  spawn,                  {.v = upvol}},
    {0,                      XF86XK_AudioMute,     spawn,                  {.v = mutevol}},
	TAGKEYS(                        XK_1,                                  0)
	TAGKEYS(                        XK_2,                                  1)
	TAGKEYS(                        XK_3,                                  2)
	TAGKEYS(                        XK_4,                                  3)
	TAGKEYS(                        XK_5,                                  4)
	TAGKEYS(                        XK_6,                                  5)
	TAGKEYS(                        XK_7,                                  6)
	TAGKEYS(                        XK_8,                                  7)
	TAGKEYS(                        XK_9,                                  8)
};


/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask           button          function        argument */
	{ ClkLtSymbol,          0,                   Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,                   Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,                   Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,                   Button3,        showhideclient, {0} },
	{ ClkWinTitle,          0,                   Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                   Button2,        spawn,          {.v = termcmd } },
	/* placemouse options, choose which feels more natural:
	 *    0 - tiled position is relative to mouse cursor
	 *    1 - tiled postiion is relative to window center
	 *    2 - mouse pointer warps to window center
	 *
	 * The moveorplace uses movemouse or placemouse depending on the floating state
	 * of the selected client. Set up individual keybindings for the two if you want
	 * to control these separately (i.e. to retain the feature to move a tiled window
	 * into a floating position).
	 */
	{ ClkClientWin,         MODKEY,              Button1,        moveorplace,    {.i = 1} },
	{ ClkClientWin,         MODKEY,              Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,              Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY,              Button4,        resizemousescroll, {.v = &scrollargs[0]} },
	{ ClkClientWin,         MODKEY,              Button5,        resizemousescroll, {.v = &scrollargs[1]} },
	{ ClkClientWin,         MODKEY,              Button6,        resizemousescroll, {.v = &scrollargs[2]} },
	{ ClkClientWin,         MODKEY,              Button7,        resizemousescroll, {.v = &scrollargs[3]} },
	{ ClkClientWin,         MODKEY|ShiftMask,    Button3,        dragcfact,      {0} },
	{ ClkClientWin,         MODKEY|ShiftMask,    Button1,        dragmfact,      {0} },
	{ ClkTagBar,            0,                   Button1,        view,           {0} },
	{ ClkTagBar,            0,                   Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,              Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,              Button3,        toggletag,      {0} },
};

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static const Signal signals[] = {
	/* signum                    function */
	{ "focusstack",              focusstack },
	{ "setmfact",                setmfact },
	{ "togglebar",               togglebar },
	{ "toggletopbar",            toggletopbar },
	{ "incnmaster",              incnmaster },
	{ "togglefloating",          togglefloating },
	{ "focusmon",                focusmon },
	{ "incnstack",               incnstack },
	{ "rotatelayoutaxis",        rotatelayoutaxis },
	{ "setlayoutaxisex",         setlayoutaxisex },
	{ "mirrorlayout",            mirrorlayout },
	{ "setcfact",                setcfact },
	{ "tagmon",                  tagmon },
	{ "zoom",                    zoom },
	{ "incrgaps",                incrgaps },
	{ "incrigaps",               incrigaps },
	{ "incrogaps",               incrogaps },
	{ "incrihgaps",              incrihgaps },
	{ "incrivgaps",              incrivgaps },
	{ "incrohgaps",              incrohgaps },
	{ "incrovgaps",              incrovgaps },
	{ "togglegaps",              togglegaps },
	{ "defaultgaps",             defaultgaps },
	{ "setgaps",                 setgapsex },
	{ "view",                    view },
	{ "viewall",                 viewallex },
	{ "viewex",                  viewex },
	{ "toggleview",              toggleview },
	{ "showhideclient",          showhideclient },
	{ "shiftboth",               shiftboth },
	{ "shiftviewclients",        shiftviewclients },
	{ "cyclelayout",             cyclelayout },
	{ "mpdchange",               mpdchange },
	{ "mpdcontrol",              mpdcontrol },
	{ "toggleviewex",            toggleviewex },
	{ "tag",                     tag },
	{ "tagall",                  tagallex },
	{ "tagex",                   tagex },
	{ "toggletag",               toggletag },
	{ "toggletagex",             toggletagex },
	{ "togglefullscreen",        togglefullscreen },
	{ "togglefakefullscreen",    togglefakefullscreen },
	{ "killclient",              killclient },
	{ "quit",                    quit },
	{ "setlayout",               setlayout },
	{ "setlayoutex",             setlayoutex },
};

