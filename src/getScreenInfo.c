#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

int writeInfoToFile(int width, int height)
{
   FILE *fptr;

   fptr = fopen("/home/akamenskyi/Dokumente/Files/Zeiterfassung_V2/data/screen.txt","wb"); // CHANGE THIS

   if(fptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }

   fprintf(fptr,"%d", width);
   fprintf(fptr, "\n");
   fprintf(fptr,"%d", height);

   fclose(fptr);

   return 0;
}

int print_display_resolution_by_X11()
{
    Display *display;
    Window window;
    XWindowAttributes xw_attrs;

    if ((display = XOpenDisplay(NULL)) == NULL) {
        fprintf(stderr, "Failed to open default display\n");
        return -1;
    }

    window = DefaultRootWindow(display);

    XGetWindowAttributes(display, window, &xw_attrs);
    
    writeInfoToFile(xw_attrs.width, xw_attrs.height);

    XCloseDisplay(display);

    return 0;
}
