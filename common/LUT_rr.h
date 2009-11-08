/* $Id$ 
 * Copyright (C) 2009 Gennadiy Serdyuk
 * Author: Gennadiy Serdyuk <gserdyuk@gserdyuk.com>
 *
 * This file is distributed as is, completely without warranty or
 * service support. The author and its employees are not liable for
 * the condition or performance of the software.
 *
 * The author owns the copyright but shall not be liable for any
 * infringement of copyright or other proprietary rights brought by
 * third parties against the users of the software.
 *
 * The author hereby disclaims all implied warranties.
 *
 * This author grants the users the right to modify, copy, and
 * redistribute this file, for any purpose, both within the user's
 * organization and externally.
 */

/*
LUT_rr - Look Up Table _ Rectangular Regular 

*/

#ifndef LUT_RR_H
#define LUT_RR_H

#define TRUE 1
#define FALSE 0

typedef struct  sLUT_Axis {
  double minval;
  double maxval;
  int size;         /* including corner points, so size=1 for single point, size = 2 for segment*/
  double dx;        /* derivative, = (maxval-minval)/ (numpoints-1) */
} LUT_Axis;

typedef struct sLUT_rr {
  double * grid;     /* x1.size * x2.size * x3.size of double[] */
  int  * filled;     /* x1.size * x2.size * x3.size of bool     */
  LUT_Axis x[3];
  int NValues;       /* how many doubles store each Value      */
  long int fills_count;
  long int interpolates_count;
} LUT3D_rr;

/* coordinates and information if they are filled */
typedef struct sIntNode3D {
int x[3];
} IntNode3D;   /*node indices and flag is_filled/not*/

typedef struct sDoubleNode3D {
double x[3];
}  DoubleNode3D;   /* actual node double coordinates */


/*basic operations*/

/* returns sucess code */
int LUT_Init (LUT3D_rr *lut, int NVals, double xmin, double xmax, int xsize, double ymin, double ymax, int ysize, double zmin, double zmax, int zsize);
/* returns sucess code */
int LUT_Destroy(LUT3D_rr *lut);
/* returns number of node at axis a, which is lower than x, -1 if lower than a.minval, -2 if higher than a.maxval */
int LUT_AxisSearch(LUT_Axis a, double x);
/* 1 if belongs, -1 if lower, -2 if higher */
int LUT_AxisBelongs(LUT_Axis a, double x); 

double LUT_AxisValue(LUT_Axis a, int i);

int LUT_NValues(LUT3D_rr *lut);

/*adds val to point x-y-z */
int LUT_AddVal (LUT3D_rr *lut, int x, int y, int z, double val[/*lut->NValues*/]);
/* returns value for x-y-z point */
int LUT_GetValue(LUT3D_rr *lut, int x, int y, int z, double val[/*lut->NValues*/]);

int  LUT_isFilled (LUT3D_rr *lut, int x, int y, int z);

/* high-level operations */

int LUT_GetNode(LUT3D_rr *lut, double x, double y, double z, IntNode3D *n);

int LUT_Interpolate(LUT3D_rr *lut, double x, double y, double z, double val[/*lut->NValues*/]);

int fills_counter(LUT3D_rr *lut);    
int interpolates_counter(LUT3D_rr *lut);

#endif
