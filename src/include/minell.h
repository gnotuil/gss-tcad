/******************************************************************************
 *
 * File:           minell.h
 *
 * Created:        24/02/2003
 *
 * Author:         Pavel Sakov
 *                 CSIRO Marine Research
 *
 * Purpose:        A header for the minimal ellipse stuff
 *
 * Revisions:      None
 *
 *****************************************************************************/

#if !defined(_MINELL_H)
#define _MINELL_H

#if !defined(_POINT_STRUCT)
#define _POINT_STRUCT
typedef struct {
    double x;
    double y;
    double z;
} point;
#endif

struct minell;
typedef struct minell minell;

/* Note that minell_build() shuffles the input point array */
minell* minell_build(int n, point p[]);
void minell_destroy(minell* me);
void minell_scalepoints(minell* me, int n, point p[]);
void minell_rescalepoints(minell* me, int n, point p[]);

double points_scaletosquare(int n, point* points);
void   points_scale(int n, point* points, double k);
#endif
