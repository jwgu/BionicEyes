//
// Created by be_linux on 2020/6/15.
//

#include <evo_be_Common.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>

// detect keyboard press, keyValue_Linux can be found in "/usr/include/X11/keysymdef.h"
// for example: XK_Shift_L, XK_A, XK_a, XK_0
static Display *be_keypress_dpy = XOpenDisplay(NULL);
static bool KEY_DOWN(KeySym keyValue_Linux)
{
	char keys_return[32];
	XQueryKeymap(be_keypress_dpy, keys_return);
	KeyCode kc2 = XKeysymToKeycode(be_keypress_dpy, keyValue_Linux);
	return !!(keys_return[kc2 >> 3] & (1 << (kc2 & 7)));
}

int main()
{
	int a = 0;
	while(++a)
	{
		printf("%d\tKey is %spressed\n", a, KEY_DOWN(XK_a) ? "" : "not ");
		msleep(30);
	}
	XCloseDisplay(be_keypress_dpy);
	return 0;
}