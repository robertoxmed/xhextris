#include "xhextris.h"

GC xhextrisFont(char *name, char *dir, unsigned long fg, unsigned long bg)
{
    XGCValues values;

    if (!(textfont = XLoadQueryFont(dpy, name))) {
      if (*dir) {
	int i, font_length;
	char **path = XGetFontPath(dpy, &font_length);
	char **new_path=(char **) malloc((font_length+1)*sizeof(char *));
	if (new_path) {
	  for(i = 0; i < font_length; i++) {
	    if (!strcmp(path[i],dir)) break;
	    new_path[i+1]=path[i];
	  }
	  if (i >= font_length) {
	    DEBUGPRINT(("extending font path to %s\n", dir));
	    new_path[0] = dir;
	    XSetFontPath(dpy, new_path, font_length + 1);
	  }
	  free(new_path);
	  if (!(textfont = XLoadQueryFont(dpy, name))) {
	    fprintf(stderr, "xhextris: cannot find %s font.\n",name);
	    xhextrisEnd(-1);
	  }
	}
	if (path) XFreeFontPath(path);
      }
    }

    values.font=textfont->fid;
    values.foreground= fg;
    values.background= bg;
    return XCreateGC(dpy,
		     DefaultRootWindow(dpy),
		     GCFont|GCForeground|GCBackground,
		     &values);
}

/*GC xhextrisFont(char *name, char *dir, unsigned long fg, unsigned long bg){
    XFontStruct retour;
    retour = XLoadQuery(dpy, name);

    if(!retour){
        char **les_path;
        int size, i;
        les_fonts = XGetFontPath(dpy, &size);
        XSetFontPath(dpy, &dir, size+1);
        les_fonts = XGetFontPath(dpy, &size);        
        for(i=0; i<size; i++){
            if(!strncmp(les_fonts[i], name, strlen(name))){
                retour = XLoadQuery(dpy, les_fonts[i]);
            }
        }
    }
    textfont = &retour;
    return retour;
}*/
