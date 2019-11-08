#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "R2Graph/R2Graph.h"
#include "R2Conv.h"
#include "GWindow/gwindow.h"

class MyWindow: public GWindow {
    R2Convex    conv;
    double dist;
    virtual void onExpose(XEvent& event);
    virtual void onKeyPress(XEvent& event);
    virtual void onButtonPress(XEvent& event);
};

//----------------------------------------------------------
// Implementation of class "MyWindow"
//
void MyWindow::onExpose(XEvent& /* event */) { // Draw a window
    // Erase a window
    setForeground(getBackground());
    fillRectangle(m_RWinRect);

    // Draw the coordinate axes and the grid
    drawAxes("black", true, "gray");

    // Draw the convex
    int n = conv.size();
    if (n > 0) {
        setForeground("blue");
        R2Convex::const_iterator b, e, i, j;
        b = conv.begin();       // Pointer to beginning
        e = conv.end();         // Pointer to after-end
        i = b;                  // Pointer to current vertex
        j = b;                  // Pointer to the next vertex
        ++j;

        while (i != e) {
            R2Point v0 = *i;    // Edge beginning
            R2Point v1;         // Edge end
            if (j != e)
                v1 = *j;
            else
                v1 = *b;        // Close the polygon

            drawLine(v0, v1);   // Draw current edge
            i = j; ++j;         // Go to the next edge
        }

        // Draw convex perimeter and area
        setForeground("brown");
        double area = conv.area();
        double perimeter = conv.perimeter();

        char str[256];
        I2Point p(10, 20);

        sprintf(str, "Area = %.3f", area);
        drawString(p, str);
        p.y += 20;

        sprintf(str, "Perimeter = %.3f", perimeter);
        drawString(p, str, strlen(str));
	p.y += 20;

        sprintf(str, "Dist = %.3f", dist);
        drawString(p, str);
    } else {
        setForeground("brown");
        I2Point p(10, 20);
        drawString(p, "Add points by mouse click.");
        p.y += 20;
        drawString(p, "Initialize by middle button.");
    }
}

//
// Process the KeyPress event: 
// if "q" is pressed, then close the window
//
void MyWindow::onKeyPress(XEvent& event) {
    KeySym key;
    char keyName[256];
    int nameLen = XLookupString(&(event.xkey), keyName, 255, &key, 0);

    if (nameLen == 1) {
        keyName[nameLen] = 0;
        printf("\"%s\" button pressed.\n", keyName);
        if (keyName[0] == 'q') { // quit => close window
            destroyWindow();
        }
    }
}

// Process mouse click
void MyWindow::onButtonPress(XEvent& event) {
    int x = event.xbutton.x;
    int y = event.xbutton.y;
    unsigned int button = event.xbutton.button;

    // printf("Mouse click: x=%d, y=%d, button=%d\n", x, y, mouseButton);

    R2Point t = invMap(I2Point(x, y));  // Mouse point in real coordinates
    if (button == Button1) {
        // Left mouse button, add the point to the convex
        conv.addPoint(t);
    } else if (button == Button2) {
        // Middle mouse button
        // Initialize the convex hull
        conv.initialize();
    } else if (button == Button3) {
	    dist = conv.distance(t);
    }

    redraw();
}

/////////////////////////////////////////////////////////////
// Main: initialize X, create an instance of MyWindow class,
//       and start the message loop
int main() {
    // Initialize X stuff
    if (!GWindow::initX()) {
        printf("Could not connect to X-server.\n");
        exit(1);
    }

    MyWindow w;
    w.createWindow(
        I2Rectangle(                    // Window frame rectangle:
            I2Point(100, 100),            //     left-top corner
            GWindow::screenMaxX()/2,    //     width
            GWindow::screenMaxY()/2     //     height
        ),
        R2Rectangle(                    // Coordinate rectangle:
            R2Point(-12., -9.),         //     bottom-right corner
            24., 18.                    //     width, height
         ),
        "Convex Hull"                   // Window title
    );
    w.setBackground("lightGray");

    GWindow::messageLoop();

    GWindow::closeX();
    return 0;
}
