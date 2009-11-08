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

*/

#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h> 

#include "LUT_rr.h"
#define TRUE 1
#define FALSE 0
/* returns sucess code */
int LUT_Init (LUT3D_rr *lut, int NVals, double xmin, double xmax, int xsize, double ymin, double ymax, int ysize, double zmin, double zmax, int zsize){

    int i;
    int N;

    assert(xmin != xmax);
    assert(ymin != ymax);
    assert(zmin != zmax);

    assert(xsize>=2);
    assert(ysize>=2);
    assert(zsize>=2);

    lut->x[0].minval=xmin;
    lut->x[0].maxval=xmax;
    lut->x[1].minval=ymin;
    lut->x[1].maxval=ymax;
    lut->x[2].minval=zmin;
    lut->x[2].maxval=zmax;

    lut->x[0].size=xsize;
    lut->x[1].size=ysize;
    lut->x[2].size=zsize;
    
    lut->NValues=NVals;

    for (i=0; i<3; i++)
        lut->x[i].dx=(lut->x[i].maxval-lut->x[i].minval)/(lut->x[i].size-1);

    N=xsize*ysize*zsize;

    lut->grid= (double*) calloc(N,sizeof(double)*lut->NValues);
    lut->filled = (int*) calloc(N,sizeof(int));
    assert (lut->grid != NULL);

    lut->fills_count=0;
    lut->interpolates_count=0;
    
    assert(lut->grid != NULL);
    assert(lut->filled != NULL);
    assert(lut->x[0].dx != 0);
    assert(lut->x[1].dx != 0);
    assert(lut->x[2].dx != 0);
    
    return 1;
}


/* returns sucess code */
int LUT_Destroy(LUT3D_rr *lut){
    assert(lut);
    assert(lut->grid);
    
    free(lut->grid);
    free(lut->filled);
    return 1;
}


/* returns number of node at axis a, which is lower than x, -1 if lower than a.minval, -2 if higher than a.maxval */
int LUT_AxisSearch(LUT_Axis a, double x){
    int n; 
    double mineps=1.e-12;
    if (x<a.minval)
        return -1;
    if (x>a.maxval)
        return -2;
    assert(LUT_AxisBelongs(a,x)==1);
    n= (int)( floor( (x-a.minval)/a.dx ) );
    
    /*fprintf(stdout, " ** LUT_AxisValue(a,n) LUT_AxisValue(a,n+1) x  x-LUT_AxisValue(a,n) %e %e %e %e\n", LUT_AxisValue(a,n), LUT_AxisValue(a,n+1), x, x-LUT_AxisValue(a,n) );
    */
    assert( LUT_AxisValue(a,n)  -mineps <= x);
    assert( LUT_AxisValue(a,n+1)+mineps >  x);    
    
    return n;
}

/* 1 if belongs, -1 if lower, -2 if higher */
int LUT_AxisBelongs(LUT_Axis a, double x){
    if (x<a.minval)
        return -1;
    if (x>a.maxval)
        return -2;
    return 1;
} 

double LUT_AxisValue(LUT_Axis a, int i){
    double v;
    assert(i<a.size);
    v = a.minval+i*a.dx;
    return v;
}

/* returns array index value for x-y-z point */
int LUT_Index(LUT3D_rr *lut, int x, int y, int z){
    assert(x<lut->x[0].size);
    assert(y<lut->x[1].size);
    assert(z<lut->x[2].size);
    return (x + (lut->x[0].size)*y + (lut->x[0].size)* (lut->x[1].size)*z);
}

int LUT_NValues(LUT3D_rr *lut){
    return lut->NValues;
}


int LUT_AddVal (LUT3D_rr *lut, int x, int y, int z, double val[/*lut->NValues*/]){
    int i;
    memcpy(lut->grid+LUT_Index(lut,x,y,z)*LUT_NValues(lut), val,sizeof(double)*lut->NValues);
    lut->filled[LUT_Index(lut,x,y,z)]=TRUE;
    lut->fills_count++;
    return 1;
}


int LUT_GetValue(LUT3D_rr *lut, int x, int y, int z, double val[/*lut->NValues*/]){
    int i;
    memcpy(val, lut->grid+LUT_Index(lut,x,y,z)*LUT_NValues(lut),sizeof(double)*lut->NValues); 
    return 1;
}

int  LUT_isFilled (LUT3D_rr *lut, int x, int y, int z){
    int n=LUT_Index(lut,x,y,z);
    return lut->filled[LUT_Index(lut,x,y,z)];
}

/* high-level operations */

int LUT_GetNode(LUT3D_rr *lut, double x, double y, double z, IntNode3D *n){
    int ix,iy,iz;
    ///printf(" LUT_GetNode - x,y,z %e %e %e \n",x,y,z);
    ix=LUT_AxisSearch(lut->x[0],x);
    iy=LUT_AxisSearch(lut->x[1],y);
    iz=LUT_AxisSearch(lut->x[2],z);
    
    n->x[0]=n->x[1]=n->x[2]=0;
    
    if ( ix<0 || iy<0 || iz<0 )
        return -1;

    n->x[0]=ix;
    n->x[1]=iy;
    n->x[2]=iz;
    return 1;
}


int LUT_Interpolate(LUT3D_rr *lut, double x, double y, double z, double val[/*lut->NValues*/]){
/*interpolates by 8 points. all 8 points have to be filled */
    /*
    point is covered (Belongs)
    surrounding points filled
    */
    int ix,iy,iz, i;
    IntNode3D n;
    double v000[lut->NValues], v100[lut->NValues], v010[lut->NValues], v110[lut->NValues], v001[lut->NValues], 
           v101[lut->NValues], v011[lut->NValues], v111[lut->NValues];
    double a000, a100, a010, a110, a001, a101, a011, a111;
    double b000, b100, b010, b110, b001, b101, b011, b111;
    double axyz, bxyz;
    double dx, dy, dz, mdx, mdy, mdz;
    
    /*ix,iy,iz are known, may be just pass them in */
    if (LUT_GetNode(lut,x,y,z,&n) <0){
        assert(1);
        }
        
    ix=n.x[0];
    iy=n.x[1];
    iz=n.x[2];

    LUT_GetValue(lut,ix,     iy,     iz, v000);
    LUT_GetValue(lut,ix+1,   iy,     iz, v100); 
    LUT_GetValue(lut,ix,     iy+1,   iz, v010);
    LUT_GetValue(lut,ix+1,   iy+1,   iz, v110);
    LUT_GetValue(lut,ix,     iy,     iz+1, v001);
    LUT_GetValue(lut,ix+1,   iy,     iz+1, v101);
    LUT_GetValue(lut,ix,     iy+1,   iz+1, v011);
    LUT_GetValue(lut,ix+1,   iy+1,   iz+1, v111);

    /* calculate some aux variables. */
    /* formula at http://local.wasp.uwa.edu.au/~pbourke/miscellaneous/interpolation/index.html  
    Vxyz = 	V000 (1 - x) (1 - y) (1 - z) +
            V100 x (1 - y) (1 - z) +
            V010 (1 - x) y (1 - z) +
            V001 (1 - x) (1 - y) z +
            V101 x (1 - y) z +
            V011 (1 - x) y z +
            V110 x y (1 - z) +
            V111 x y z
            
    */

/* corresponds to "x" in Bourke formula*/  

    dx=(x-LUT_AxisValue(lut->x[0],ix))/ lut->x[0].dx;  
    dy=(y-LUT_AxisValue(lut->x[1],iy))/ lut->x[1].dx;
    dz=(z-LUT_AxisValue(lut->x[2],iz))/ lut->x[2].dx;

    mdx=1.-dx;                     /* corresponds to "1-x" in Bourke formula*/
    mdy=1.-dy;
    mdz=1.-dz;


    for ( i=0; i<lut->NValues; i++){  /*LUTVALS - number of doubles stored in Value */   
    /* interpolate */
    val[i] = 	v000[i] * mdx *  mdy * mdz +
            v100[i] *  dx *  mdy * mdz +
            v010[i] * mdx *   dy * mdz +
            v001[i] * mdx *  mdy *  dz +
            v101[i] *  dx *  mdy *  dz +
            v011[i] * mdx *   dy *  dz +
            v110[i] *  dx *   dy * mdz +
            v111[i] *  dx *  dy  *  dz ;
    }
    
    lut->interpolates_count++;
    
    return 1;
}

int fills_counter(LUT3D_rr *lut){
    return lut->fills_count;
    }
    
int interpolates_counter(LUT3D_rr *lut){
    return lut->interpolates_count;
    }
