/**** BSIM3v3.3.0, Released by Xuemei Xi 07/29/2005 ****/

/**********
 * Copyright 2004 Regents of the University of California. All rights reserved.
 * File: b3par.c of BSIM3v3.3.0
 * Author: 1995 Min-Chie Jeng and Mansun Chan
 * Author: 1997-1999 Weidong Liu.
 * Author: 2001 Xuemei Xi
 **********/

static char rcsid[] = "$Id: b3par.c, v3.3.0 07/29/2005 18:00:00 Xuemei Xi Release $";

#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "bsim3def.h"
#include "util.h"
#include "sperror.h"
#include "suffix.h"

int
BSIM3param(param,value,inst,select)
int param;
IFvalue *value;
GENinstance *inst;
IFvalue *select;
{
    BSIM3instance *here = (BSIM3instance*)inst;
    switch(param) 
    {   case BSIM3_W:
            here->BSIM3w = value->rValue;
            here->BSIM3wGiven = TRUE;
            break;
        case BSIM3_L:
            here->BSIM3l = value->rValue;
            here->BSIM3lGiven = TRUE;
            break;
        case BSIM3_AS:
            here->BSIM3sourceArea = value->rValue;
            here->BSIM3sourceAreaGiven = TRUE;
            break;
        case BSIM3_AD:
            here->BSIM3drainArea = value->rValue;
            here->BSIM3drainAreaGiven = TRUE;
            break;
        case BSIM3_PS:
            here->BSIM3sourcePerimeter = value->rValue;
            here->BSIM3sourcePerimeterGiven = TRUE;
            break;
        case BSIM3_PD:
            here->BSIM3drainPerimeter = value->rValue;
            here->BSIM3drainPerimeterGiven = TRUE;
            break;
        case BSIM3_NRS:
            here->BSIM3sourceSquares = value->rValue;
            here->BSIM3sourceSquaresGiven = TRUE;
            break;
        case BSIM3_NRD:
            here->BSIM3drainSquares = value->rValue;
            here->BSIM3drainSquaresGiven = TRUE;
            break;
        case BSIM3_OFF:
            here->BSIM3off = value->iValue;
            break;
        case BSIM3_IC_VBS:
            here->BSIM3icVBS = value->rValue;
            here->BSIM3icVBSGiven = TRUE;
            break;
        case BSIM3_IC_VDS:
            here->BSIM3icVDS = value->rValue;
            here->BSIM3icVDSGiven = TRUE;
            break;
        case BSIM3_IC_VGS:
            here->BSIM3icVGS = value->rValue;
            here->BSIM3icVGSGiven = TRUE;
            break;
        case BSIM3_NQSMOD:
            here->BSIM3nqsMod = value->iValue;
            here->BSIM3nqsModGiven = TRUE;
            break;
        case BSIM3_ACNQSMOD:
            here->BSIM3acnqsMod = value->iValue;
            here->BSIM3acnqsModGiven = TRUE;
            break;
        case BSIM3_IC:
            switch(value->v.numValue){
                case 3:
                    here->BSIM3icVBS = *(value->v.vec.rVec+2);
                    here->BSIM3icVBSGiven = TRUE;
                case 2:
                    here->BSIM3icVGS = *(value->v.vec.rVec+1);
                    here->BSIM3icVGSGiven = TRUE;
                case 1:
                    here->BSIM3icVDS = *(value->v.vec.rVec);
                    here->BSIM3icVDSGiven = TRUE;
                    break;
                default:
                    return(E_BADPARM);
            }
            break;
#ifdef LUT
        case BSIM3_LUT_MODE:
            //fprintf(stdout, "BSIM3param BEFORE here->BSIM3lut_mode=%d \n",here->BSIM3lut_mode);
            //fprintf(stdout, "BSIM3param ASSIGNING value->iValue =%d \n",value->iValue);
            here->BSIM3lut_mode = value->iValue;
            here->BSIM3lut_modeGiven = TRUE;
            //fprintf(stdout, "BSIM3param AFTER here->BSIM3lut_mode=%d \n",here->BSIM3lut_mode);
            break;
#endif            
        default:
            return(E_BADPARM);
    }
    return(OK);
}



