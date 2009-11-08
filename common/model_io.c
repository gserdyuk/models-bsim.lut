#include <stdlib.h>
#include "spice.h"
#include <stdio.h>
#include "cktdefs.h"
#include "bsim3def.h"

#define CHECK(n) if (ret != n) printf("alert- input error at line %d , expected: %d, obtained: %d parameters \n",__LINE__, n, ret); \
                 else          if (verbose==1) printf ("ok, at %i read %i values \n",__LINE__,ret);



int print_instances(FILE * logfile, int count, BSIM3model *model, char* msg);
int print_BSIM3model(FILE * logfile, int count, BSIM3model *model, char* msg);

int read_instances(FILE * infile, BSIM3model *model);
int read_BSIM3model(FILE * logfile, BSIM3model *model);

int create_BSIM3model (BSIM3model **model);
int free_BSIM3model (BSIM3model **model);

/*------------------------------------------------------------------------------------------------*/
// #include "bsim3def.h"
/* typedef struct sBSIM3instance {
    struct sBSIM3model *BSIM3modPtr;
    struct sBSIM3instance *BSIM3nextInstance;
    ....
} BSIM3instance ;

struct bsim3SizeDependParam
{
    ...
    struct bsim3SizeDependParam  *pNext;
};
*/

int print_instances(FILE * logfile, int count, BSIM3model *model, char* msg){

BSIM3instance * here;
struct bsim3SizeDependParam  *pParam;

fprintf(logfile,"  === run no %i %s : instances\n", count, msg);  fflush(logfile);
   for (here = model->BSIM3instances; here != NULL;  here = here->BSIM3nextInstance){
        fprintf(logfile,"  = instance \n");  
        //fprintf(logfile," instance address = %X\n", here); 
/*    
printf("print_instance: model                 = %X \n", model);
printf("print_instance: model->BSIM3instances = %X \n", model->BSIM3instances);
printf("create_BSIM3model: here = %X \n", here);
*/
    
//fprintf(logfile,"         struct sBSIM3model *BSIM3modPtr           = %X \n",   here->BSIM3modPtr);
//fprintf(logfile,"         struct sBSIM3instance *BSIM3nextInstance  =%X \n",    here->BSIM3nextInstance);
fprintf(logfile,"         IFuid BSIM3name                           = %s \n",   here->BSIM3name);
fprintf(logfile,"     +   int BSIM3states				= %i \n", here->BSIM3states);                                                // index into state table for this device 
fprintf(logfile,"     *   int BSIM3dNode				= %i \n", here->BSIM3dNode);
fprintf(logfile,"     +   int BSIM3gNode				= %i \n", here->BSIM3gNode);
fprintf(logfile,"     *   int BSIM3sNode				= %i \n", here->BSIM3sNode);
fprintf(logfile,"     +   int BSIM3bNode				= %i \n", here->BSIM3bNode);
fprintf(logfile,"     +   int BSIM3dNodePrime			= %i \n", here->BSIM3dNodePrime);
fprintf(logfile,"     +   int BSIM3sNodePrime			= %i \n", here->BSIM3sNodePrime);
fprintf(logfile,"     +   int BSIM3qNode				= %i \n", here->BSIM3qNode);                                                 // MCJ 
fflush(logfile);
    // MCJ b
fprintf(logfile,"     +   double BSIM3ueff				= %e \n", here->BSIM3ueff);
fprintf(logfile,"     +   double BSIM3thetavth			= %e \n", here->BSIM3thetavth); 
fprintf(logfile,"     +   double BSIM3von				= %e \n", here->BSIM3von);
fprintf(logfile,"     +   double BSIM3vdsat				= %e \n", here->BSIM3vdsat);
fprintf(logfile,"     *   double BSIM3cgdo				= %e \n", here->BSIM3cgdo);
fprintf(logfile,"     *   double BSIM3cgso				= %e \n", here->BSIM3cgso);
fprintf(logfile,"     +   double BSIM3vjsm				= %e \n", here->BSIM3vjsm);
fprintf(logfile,"     +   double BSIM3IsEvjsm			= %e \n", here->BSIM3IsEvjsm);
fprintf(logfile,"     +   double BSIM3vjdm				= %e \n", here->BSIM3vjdm);
fprintf(logfile,"     +   double BSIM3IsEvjdm			= %e \n", here->BSIM3IsEvjdm);

fprintf(logfile,"     *   double BSIM3l				    = %e \n", here->BSIM3l);
fprintf(logfile,"     *   double BSIM3w				    = %e \n", here->BSIM3w);
fprintf(logfile,"     +   double BSIM3drainArea			= %e \n", here->BSIM3drainArea);
fprintf(logfile,"     +   double BSIM3sourceArea		= %e \n", here->BSIM3sourceArea);
fprintf(logfile,"     *   double BSIM3drainSquares		= %e \n", here->BSIM3drainSquares);
fprintf(logfile,"     *   double BSIM3sourceSquares		= %e \n", here->BSIM3sourceSquares);
fprintf(logfile,"     +   double BSIM3drainPerimeter	= %e \n", here->BSIM3drainPerimeter);
fprintf(logfile,"     +   double BSIM3sourcePerimeter	= %e \n", here->BSIM3sourcePerimeter);
fprintf(logfile,"     *   double BSIM3sourceConductance	= %e \n", here->BSIM3sourceConductance);
fprintf(logfile,"     *   double BSIM3drainConductance	= %e \n", here->BSIM3drainConductance);

fprintf(logfile,"     +   double BSIM3icVBS				= %e \n", here->BSIM3icVBS);
fprintf(logfile,"     +   double BSIM3icVDS				= %e \n", here->BSIM3icVDS);
fprintf(logfile,"     +   double BSIM3icVGS				= %e \n", here->BSIM3icVGS);
fprintf(logfile,"     +   int BSIM3off				    = %i \n", here->BSIM3off);
fprintf(logfile,"     +   int BSIM3mode				    = %i \n", here->BSIM3mode);
fprintf(logfile,"     *   int BSIM3nqsMod				= %i \n", here->BSIM3nqsMod);
fprintf(logfile,"     *   int BSIM3acnqsMod				= %i \n", here->BSIM3acnqsMod);

    // OP point 
fprintf(logfile,"     *   double BSIM3qinv				= %e \n", here->BSIM3qinv);
fprintf(logfile,"     +   double BSIM3cd				= %e \n", here->BSIM3cd);
fprintf(logfile,"     +   double BSIM3cbs				= %e \n", here->BSIM3cbs);
fprintf(logfile,"     +   double BSIM3cbd				= %e \n", here->BSIM3cbd);
fprintf(logfile,"     +   double BSIM3csub				= %e \n", here->BSIM3csub);
fprintf(logfile,"     +   double BSIM3gm				= %e \n", here->BSIM3gm);
fprintf(logfile,"     +   double BSIM3gds				= %e \n", here->BSIM3gds);
fprintf(logfile,"     +   double BSIM3gmbs				= %e \n", here->BSIM3gmbs);
fprintf(logfile,"     +   double BSIM3gbd				= %e \n", here->BSIM3gbd);
fprintf(logfile,"     +   double BSIM3gbs				= %e \n", here->BSIM3gbs);

fprintf(logfile,"     +   double BSIM3gbbs				= %e \n", here->BSIM3gbbs);
fprintf(logfile,"     +   double BSIM3gbgs				= %e \n", here->BSIM3gbgs);
fprintf(logfile,"     +   double BSIM3gbds				= %e \n", here->BSIM3gbds);

fprintf(logfile,"     +   double BSIM3cggb				= %e \n", here->BSIM3cggb);
fprintf(logfile,"     +   double BSIM3cgdb				= %e \n", here->BSIM3cgdb);
fprintf(logfile,"     +   double BSIM3cgsb				= %e \n", here->BSIM3cgsb);
fprintf(logfile,"     *   double BSIM3cbgb				= %e \n", here->BSIM3cbgb);
fprintf(logfile,"     *   double BSIM3cbdb				= %e \n", here->BSIM3cbdb);
fprintf(logfile,"     *   double BSIM3cbsb				= %e \n", here->BSIM3cbsb);
fprintf(logfile,"     *   double BSIM3cdgb				= %e \n", here->BSIM3cdgb);
fprintf(logfile,"     *   double BSIM3cddb				= %e \n", here->BSIM3cddb);
fprintf(logfile,"     *   double BSIM3cdsb				= %e \n", here->BSIM3cdsb);
fprintf(logfile,"     *   double BSIM3capbd				= %e \n", here->BSIM3capbd);
fprintf(logfile,"     *   double BSIM3capbs				= %e \n", here->BSIM3capbs);

fprintf(logfile,"     *   double BSIM3cqgb				= %e \n", here->BSIM3cqgb);
fprintf(logfile,"     *   double BSIM3cqdb				= %e \n", here->BSIM3cqdb);
fprintf(logfile,"     *   double BSIM3cqsb				= %e \n", here->BSIM3cqsb);
fprintf(logfile,"     *   double BSIM3cqbb				= %e \n", here->BSIM3cqbb);

fprintf(logfile,"     +   double BSIM3qgate				= %e \n", here->BSIM3qgate);
fprintf(logfile,"     +   double BSIM3qbulk				= %e \n", here->BSIM3qbulk);
fprintf(logfile,"     +   double BSIM3qdrn				= %e \n", here->BSIM3qdrn);

fprintf(logfile,"     *   double BSIM3gtau				= %e \n", here->BSIM3gtau);
fprintf(logfile,"     *   double BSIM3gtg				= %e \n", here->BSIM3gtg);
fprintf(logfile,"     *   double BSIM3gtd				= %e \n", here->BSIM3gtd);
fprintf(logfile,"     *   double BSIM3gts				= %e \n", here->BSIM3gts);
fprintf(logfile,"     *   double BSIM3gtb				= %e \n", here->BSIM3gtb);
fprintf(logfile,"     +   double BSIM3rds				= %e \n", here->BSIM3rds);                                                                // Noise bugfix 
fprintf(logfile,"     +   double BSIM3Vgsteff			= %e \n", here->BSIM3Vgsteff);
fprintf(logfile,"     +   double BSIM3Vdseff			= %e \n", here->BSIM3Vdseff);
fprintf(logfile,"     +   double BSIM3Abulk				= %e \n", here->BSIM3Abulk);
fprintf(logfile,"     +   double BSIM3AbovVgst2Vtm		= %e \n", here->BSIM3AbovVgst2Vtm);
fprintf(logfile,"     *   double BSIM3taunet			= %e \n", here->BSIM3taunet);

//fprintf(logfile,"     +! struct bsim3SizeDependParam  *pParam   = %X \n",pParam);
/*
    unsigned BSIM3lGiven :1;
    unsigned BSIM3wGiven :1;
    unsigned BSIM3drainAreaGiven :1;
    unsigned BSIM3sourceAreaGiven    :1;
    unsigned BSIM3drainSquaresGiven  :1;
    unsigned BSIM3sourceSquaresGiven :1;
    unsigned BSIM3drainPerimeterGiven    :1;
    unsigned BSIM3sourcePerimeterGiven   :1;
    unsigned BSIM3dNodePrimeSet  :1;
    unsigned BSIM3sNodePrimeSet  :1;
    unsigned BSIM3icVBSGiven :1;
    unsigned BSIM3icVDSGiven :1;
    unsigned BSIM3icVGSGiven :1;
    unsigned BSIM3nqsModGiven :1;
    unsigned BSIM3acnqsModGiven :1;
*/
fprintf(logfile,"     +   double *BSIM3DdPtr = %e \n",*(here->BSIM3DdPtr));
fprintf(logfile,"     +   double *BSIM3GgPtr = %e \n",*(here->BSIM3GgPtr));
fprintf(logfile,"     +   double *BSIM3SsPtr = %e \n",*(here->BSIM3SsPtr));
fprintf(logfile,"     +   double *BSIM3BbPtr = %e \n",*(here->BSIM3BbPtr));
fprintf(logfile,"     +   double *BSIM3DPdpPtr = %e \n",*(here->BSIM3DPdpPtr));
fprintf(logfile,"     *   double *BSIM3SPspPtr = %e \n",*(here->BSIM3SPspPtr));
fprintf(logfile,"     *   double *BSIM3DdpPtr = %e \n",*(here->BSIM3DdpPtr));
fprintf(logfile,"     *   double *BSIM3GbPtr = %e \n",*(here->BSIM3GbPtr));
fprintf(logfile,"     *   double *BSIM3GdpPtr = %e \n",*(here->BSIM3GdpPtr));
fprintf(logfile,"     *   double *BSIM3GspPtr = %e \n",*(here->BSIM3GspPtr));
fprintf(logfile,"     *   double *BSIM3SspPtr = %e \n",*(here->BSIM3SspPtr));
fprintf(logfile,"     *   double *BSIM3BdpPtr = %e \n",*(here->BSIM3BdpPtr));
fprintf(logfile,"     *   double *BSIM3BspPtr = %e \n",*(here->BSIM3BspPtr));
fprintf(logfile,"     *   double *BSIM3DPspPtr = %e \n",*(here->BSIM3DPspPtr));
fprintf(logfile,"     *   double *BSIM3DPdPtr = %e \n",*(here->BSIM3DPdPtr));
fprintf(logfile,"     *   double *BSIM3BgPtr = %e \n",*(here->BSIM3BgPtr));
fprintf(logfile,"     *   double *BSIM3DPgPtr = %e \n",*(here->BSIM3DPgPtr));
fprintf(logfile,"     *   double *BSIM3SPgPtr = %e \n",*(here->BSIM3SPgPtr));
fprintf(logfile,"     *   double *BSIM3SPsPtr = %e \n",*(here->BSIM3SPsPtr));
fprintf(logfile,"     *   double *BSIM3DPbPtr = %e \n",*(here->BSIM3DPbPtr));
fprintf(logfile,"     *   double *BSIM3SPbPtr = %e \n",*(here->BSIM3SPbPtr));
fprintf(logfile,"     *   double *BSIM3SPdpPtr = %e \n",*(here->BSIM3SPdpPtr));

fprintf(logfile,"     *   double *BSIM3QqPtr = %e \n",*(here->BSIM3QqPtr));
fprintf(logfile,"     *   double *BSIM3QdpPtr = %e \n",*(here->BSIM3QdpPtr));
fprintf(logfile,"     *   double *BSIM3QgPtr = %e \n",*(here->BSIM3QgPtr));
fprintf(logfile,"     *   double *BSIM3QspPtr = %e \n",*(here->BSIM3QspPtr));
fprintf(logfile,"     *   double *BSIM3QbPtr = %e \n",*(here->BSIM3QbPtr));
fprintf(logfile,"     *   double *BSIM3DPqPtr = %e \n",*(here->BSIM3DPqPtr));
fprintf(logfile,"     *   double *BSIM3GqPtr = %e \n",*(here->BSIM3GqPtr));
fprintf(logfile,"     *   double *BSIM3SPqPtr = %e \n",*(here->BSIM3SPqPtr));
fprintf(logfile,"     *   double *BSIM3BqPtr = %e \n",*(here->BSIM3BqPtr));
        
        fprintf(logfile,"  = end instance \n", count, msg);  

/*------------------------------------------------------------------------*/        
        pParam=here->pParam;

        fprintf(logfile,"  = pParam \n", count, msg);  
//        fprintf(logfile," pParam address = %X\n", pParam);
         // store/restore all
        fprintf(logfile," double Width			    = %e \n", pParam->Width);           
        fprintf(logfile," double Length			    = %e \n", pParam->Length);

        fprintf(logfile," double BSIM3cdsc			= %e \n", pParam->BSIM3cdsc);           
        fprintf(logfile," double BSIM3cdscb			= %e \n", pParam->BSIM3cdscb);    
        fprintf(logfile," double BSIM3cdscd			= %e \n", pParam->BSIM3cdscd);       
        fprintf(logfile," double BSIM3cit			= %e \n", pParam->BSIM3cit);           
        fprintf(logfile," double BSIM3nfactor		= %e \n", pParam->BSIM3nfactor);      
        fprintf(logfile," double BSIM3xj			= %e \n", pParam->BSIM3xj);
        fprintf(logfile," double BSIM3vsat			= %e \n", pParam->BSIM3vsat);         
        fprintf(logfile," double BSIM3at			= %e \n", pParam->BSIM3at);         
        fprintf(logfile," double BSIM3a0			= %e \n", pParam->BSIM3a0);   
        fprintf(logfile," double BSIM3ags			= %e \n", pParam->BSIM3ags);      
        fprintf(logfile," double BSIM3a1			= %e \n", pParam->BSIM3a1);         
        fprintf(logfile," double BSIM3a2			= %e \n", pParam->BSIM3a2);         
        fprintf(logfile," double BSIM3keta			= %e \n", pParam->BSIM3keta);     
        fprintf(logfile," double BSIM3nsub			= %e \n", pParam->BSIM3nsub);
        fprintf(logfile," double BSIM3npeak			= %e \n", pParam->BSIM3npeak);        
        fprintf(logfile," double BSIM3ngate			= %e \n", pParam->BSIM3ngate);        
        fprintf(logfile," double BSIM3gamma1		= %e \n", pParam->BSIM3gamma1);      
        fprintf(logfile," double BSIM3gamma2		= %e \n", pParam->BSIM3gamma2);     
        fprintf(logfile," double BSIM3vbx			= %e \n", pParam->BSIM3vbx);      
        fprintf(logfile," double BSIM3vbi			= %e \n", pParam->BSIM3vbi);       
        fprintf(logfile," double BSIM3vbm			= %e \n", pParam->BSIM3vbm);       
        fprintf(logfile," double BSIM3vbsc			= %e \n", pParam->BSIM3vbsc);       
        fprintf(logfile," double BSIM3xt			= %e \n", pParam->BSIM3xt);       
        fprintf(logfile," double BSIM3phi			= %e \n", pParam->BSIM3phi);
        fprintf(logfile," double BSIM3litl			= %e \n", pParam->BSIM3litl);
        fprintf(logfile," double BSIM3k1			= %e \n", pParam->BSIM3k1);
        fprintf(logfile," double BSIM3kt1			= %e \n", pParam->BSIM3kt1);
        fprintf(logfile," double BSIM3kt1l			= %e \n", pParam->BSIM3kt1l);
        fprintf(logfile," double BSIM3kt2			= %e \n", pParam->BSIM3kt2);
        fprintf(logfile," double BSIM3k2			= %e \n", pParam->BSIM3k2);
        fprintf(logfile," double BSIM3k3			= %e \n", pParam->BSIM3k3);
        fprintf(logfile," double BSIM3k3b			= %e \n", pParam->BSIM3k3b);
        fprintf(logfile," double BSIM3w0			= %e \n", pParam->BSIM3w0);
        fprintf(logfile," double BSIM3nlx			= %e \n", pParam->BSIM3nlx);
        fprintf(logfile," double BSIM3dvt0			= %e \n", pParam->BSIM3dvt0);      
        fprintf(logfile," double BSIM3dvt1			= %e \n", pParam->BSIM3dvt1);      
        fprintf(logfile," double BSIM3dvt2			= %e \n", pParam->BSIM3dvt2);      
        fprintf(logfile," double BSIM3dvt0w			= %e \n", pParam->BSIM3dvt0w);      
        fprintf(logfile," double BSIM3dvt1w			= %e \n", pParam->BSIM3dvt1w);      
        fprintf(logfile," double BSIM3dvt2w			= %e \n", pParam->BSIM3dvt2w);      
        fprintf(logfile," double BSIM3drout			= %e \n", pParam->BSIM3drout);      
        fprintf(logfile," double BSIM3dsub			= %e \n", pParam->BSIM3dsub);      
        fprintf(logfile," double BSIM3vth0			= %e \n", pParam->BSIM3vth0);
        fprintf(logfile," double BSIM3ua			= %e \n", pParam->BSIM3ua);
        fprintf(logfile," double BSIM3ua1			= %e \n", pParam->BSIM3ua1);
        fprintf(logfile," double BSIM3ub			= %e \n", pParam->BSIM3ub);
        fprintf(logfile," double BSIM3ub1			= %e \n", pParam->BSIM3ub1);
        fprintf(logfile," double BSIM3uc			= %e \n", pParam->BSIM3uc);
        fprintf(logfile," double BSIM3uc1			= %e \n", pParam->BSIM3uc1);
        fprintf(logfile," double BSIM3u0			= %e \n", pParam->BSIM3u0);
        fprintf(logfile," double BSIM3ute			= %e \n", pParam->BSIM3ute);
        fprintf(logfile," double BSIM3voff			= %e \n", pParam->BSIM3voff);
        fprintf(logfile," double BSIM3vfb			= %e \n", pParam->BSIM3vfb);
        fprintf(logfile," double BSIM3delta			= %e \n", pParam->BSIM3delta);
        fprintf(logfile," double BSIM3rdsw			= %e \n", pParam->BSIM3rdsw);       
        fprintf(logfile," double BSIM3rds0			= %e \n", pParam->BSIM3rds0);       
        fprintf(logfile," double BSIM3prwg			= %e \n", pParam->BSIM3prwg);       
        fprintf(logfile," double BSIM3prwb			= %e \n", pParam->BSIM3prwb);       
        fprintf(logfile," double BSIM3prt			= %e \n", pParam->BSIM3prt);       
        fprintf(logfile," double BSIM3eta0			= %e \n", pParam->BSIM3eta0);         
        fprintf(logfile," double BSIM3etab			= %e \n", pParam->BSIM3etab);         
        fprintf(logfile," double BSIM3pclm			= %e \n", pParam->BSIM3pclm);      
        fprintf(logfile," double BSIM3pdibl1		= %e \n", pParam->BSIM3pdibl1);      
        fprintf(logfile," double BSIM3pdibl2		= %e \n", pParam->BSIM3pdibl2);      
        fprintf(logfile," double BSIM3pdiblb		= %e \n", pParam->BSIM3pdiblb);      
        fprintf(logfile," double BSIM3pscbe1		= %e \n", pParam->BSIM3pscbe1);       
        fprintf(logfile," double BSIM3pscbe2		= %e \n", pParam->BSIM3pscbe2);       
        fprintf(logfile," double BSIM3pvag			= %e \n", pParam->BSIM3pvag);       
        fprintf(logfile," double BSIM3wr			= %e \n", pParam->BSIM3wr);
        fprintf(logfile," double BSIM3dwg			= %e \n", pParam->BSIM3dwg);
        fprintf(logfile," double BSIM3dwb			= %e \n", pParam->BSIM3dwb);
        fprintf(logfile," double BSIM3b0			= %e \n", pParam->BSIM3b0);
        fprintf(logfile," double BSIM3b1			= %e \n", pParam->BSIM3b1);
        fprintf(logfile," double BSIM3alpha0		= %e \n", pParam->BSIM3alpha0);
        fprintf(logfile," double BSIM3alpha1		= %e \n", pParam->BSIM3alpha1);
        fprintf(logfile," double BSIM3beta0			= %e \n", pParam->BSIM3beta0);

    //  fprintf(logfile," CV model                       
        fprintf(logfile," double BSIM3elm			= %e \n", pParam->BSIM3elm);
        fprintf(logfile," double BSIM3cgsl			= %e \n", pParam->BSIM3cgsl);
        fprintf(logfile," double BSIM3cgdl			= %e \n", pParam->BSIM3cgdl);
        fprintf(logfile," double BSIM3ckappa		= %e \n", pParam->BSIM3ckappa);
        fprintf(logfile," double BSIM3cf			= %e \n", pParam->BSIM3cf);
        fprintf(logfile," double BSIM3clc			= %e \n", pParam->BSIM3clc);
        fprintf(logfile," double BSIM3cle			= %e \n", pParam->BSIM3cle);
        fprintf(logfile," double BSIM3vfbcv			= %e \n", pParam->BSIM3vfbcv);
        fprintf(logfile," double BSIM3noff			= %e \n", pParam->BSIM3noff);
        fprintf(logfile," double BSIM3voffcv		= %e \n", pParam->BSIM3voffcv);
        fprintf(logfile," double BSIM3acde			= %e \n", pParam->BSIM3acde);
        fprintf(logfile," double BSIM3moin			= %e \n", pParam->BSIM3moin);

    //  fprintf(logfile," Pre-calculated constants        

        fprintf(logfile," double BSIM3dw			= %e \n", pParam->BSIM3dw);
        fprintf(logfile," double BSIM3dl			= %e \n", pParam->BSIM3dl);
        fprintf(logfile," double BSIM3leff			= %e \n", pParam->BSIM3leff);
        fprintf(logfile," double BSIM3weff			= %e \n", pParam->BSIM3weff);

        fprintf(logfile," double BSIM3dwc			= %e \n", pParam->BSIM3dwc);
        fprintf(logfile," double BSIM3dlc			= %e \n", pParam->BSIM3dlc);
        fprintf(logfile," double BSIM3leffCV		= %e \n", pParam->BSIM3leffCV);
        fprintf(logfile," double BSIM3weffCV		= %e \n", pParam->BSIM3weffCV);
        fprintf(logfile," double BSIM3abulkCVfactor	= %e \n", pParam->BSIM3abulkCVfactor);
        fprintf(logfile," double BSIM3cgso			= %e \n", pParam->BSIM3cgso);
        fprintf(logfile," double BSIM3cgdo			= %e \n", pParam->BSIM3cgdo);
        fprintf(logfile," double BSIM3cgbo			= %e \n", pParam->BSIM3cgbo);
        fprintf(logfile," double BSIM3tconst		= %e \n", pParam->BSIM3tconst);

        fprintf(logfile," double BSIM3u0temp		= %e \n", pParam->BSIM3u0temp);       
        fprintf(logfile," double BSIM3vsattemp		= %e \n", pParam->BSIM3vsattemp);   
        fprintf(logfile," double BSIM3sqrtPhi		= %e \n", pParam->BSIM3sqrtPhi);   
        fprintf(logfile," double BSIM3phis3			= %e \n", pParam->BSIM3phis3);   
        fprintf(logfile," double BSIM3Xdep0			= %e \n", pParam->BSIM3Xdep0);          
        fprintf(logfile," double BSIM3sqrtXdep0		= %e \n", pParam->BSIM3sqrtXdep0);          
        fprintf(logfile," double BSIM3theta0vb0		= %e \n", pParam->BSIM3theta0vb0);
        fprintf(logfile," double BSIM3thetaRout		= %e \n", pParam->BSIM3thetaRout); 

        fprintf(logfile," double BSIM3cof1			= %e \n", pParam->BSIM3cof1);
        fprintf(logfile," double BSIM3cof2			= %e \n", pParam->BSIM3cof2);
        fprintf(logfile," double BSIM3cof3			= %e \n", pParam->BSIM3cof3);
        fprintf(logfile," double BSIM3cof4			= %e \n", pParam->BSIM3cof4);
        fprintf(logfile," double BSIM3cdep0			= %e \n", pParam->BSIM3cdep0);
        fprintf(logfile," double BSIM3vfbzb			= %e \n", pParam->BSIM3vfbzb);
        fprintf(logfile," double BSIM3ldeb			= %e \n", pParam->BSIM3ldeb);
        fprintf(logfile," double BSIM3k1ox			= %e \n", pParam->BSIM3k1ox);
        fprintf(logfile," double BSIM3k2ox			= %e \n", pParam->BSIM3k2ox);

//        fprintf(logfile," struct bsim3SizeDependParam = %X \n", pParam->pNext );  
        
        fprintf(logfile,"  = end pParam \n", count, msg);  

   }
   
fprintf(logfile,"  === end instances\n", count, msg);  

return 1;

}


int print_BSIM3model(FILE * logfile, int count, BSIM3model *model, char* msg){

fprintf(logfile,"  == run no %i %s : model \n", count, msg); fflush(logfile); 

print_instances(logfile, count, model, msg);fflush(logfile);

fprintf(logfile,"        int BSIM3modType                   = %i \n",model->BSIM3modType);fflush(logfile);
//fprintf(logfile,"        struct sBSIM3model *BSIM3nextModel = %X \n",model->BSIM3nextModel);
//fprintf(logfile,"        BSIM3instance *BSIM3instances      = %X \n",model->BSIM3instances);          // here
fprintf(logfile,"        IFuid BSIM3modName                 = 0  \n"); 
fprintf(logfile,"    +   int BSIM3type                  = %i \n",model->BSIM3type);
fprintf(logfile,"    +   int    BSIM3mobMod             = %i \n",model->BSIM3mobMod);
fprintf(logfile,"    +   int    BSIM3capMod             = %i \n",model->BSIM3capMod);
fprintf(logfile,"        int    BSIM3noiMod             = %i \n",model->BSIM3noiMod);
fprintf(logfile,"        int    BSIM3acnqsMod		    = %i \n",model->BSIM3acnqsMod);
fprintf(logfile,"        int    BSIM3binUnit		    = %i \n",model->BSIM3binUnit);
fprintf(logfile,"        int    BSIM3paramChk			= %i \n",model->BSIM3paramChk);
fprintf(logfile,"        char   *BSIM3version ? 	    = %c \n",model->BSIM3version);             
fprintf(logfile,"    +   double BSIM3tox			    = %e \n",model->BSIM3tox);             
fprintf(logfile,"        double BSIM3toxm			    = %e \n",model->BSIM3toxm);
fprintf(logfile,"        double BSIM3cdsc 	    		= %e \n", model->BSIM3cdsc);           
fprintf(logfile,"        double BSIM3cdscb		    	= %e \n", model->BSIM3cdscb); 
fprintf(logfile,"        double BSIM3cdscd		    	= %e \n", model->BSIM3cdscd);          
fprintf(logfile,"        double BSIM3cit		    	= %e \n", model->BSIM3cit);           
fprintf(logfile,"        double BSIM3nfactor			= %e \n", model->BSIM3nfactor);      
fprintf(logfile,"        double BSIM3xj			        = %e \n", model->BSIM3xj);
fprintf(logfile,"        double BSIM3vsat		    	= %e \n", model->BSIM3vsat);         
fprintf(logfile,"        double BSIM3at			        = %e \n", model->BSIM3at);         
fprintf(logfile,"        double BSIM3a0		          	= %e \n", model->BSIM3a0);   
fprintf(logfile,"        double BSIM3ags	       		= %e \n", model->BSIM3ags);      
fprintf(logfile,"        double BSIM3a1			        = %e \n", model->BSIM3a1);         
fprintf(logfile,"        double BSIM3a2		        	= %e \n", model->BSIM3a2);         
fprintf(logfile,"        double BSIM3keta			    = %e \n", model->BSIM3keta);     
fprintf(logfile,"        double BSIM3nsub		    	= %e \n", model->BSIM3nsub);
fprintf(logfile,"        double BSIM3npeak	    		= %e \n", model->BSIM3npeak);        
fprintf(logfile,"        double BSIM3ngate		    	= %e \n", model->BSIM3ngate);        
fprintf(logfile,"        double BSIM3gamma1			    = %e \n", model->BSIM3gamma1);      
fprintf(logfile,"        double BSIM3gamma2	    		= %e \n", model->BSIM3gamma2);     
fprintf(logfile,"        double BSIM3vbx		    	= %e \n", model->BSIM3vbx);      
fprintf(logfile,"        double BSIM3vbm			    = %e \n", model->BSIM3vbm);       
fprintf(logfile,"        double BSIM3xt	        		= %e \n", model->BSIM3xt);       
fprintf(logfile,"        double BSIM3k1			        = %e \n", model->BSIM3k1);
fprintf(logfile,"        double BSIM3kt1	    		= %e \n", model->BSIM3kt1);
fprintf(logfile,"        double BSIM3kt1l		    	= %e \n", model->BSIM3kt1l);
fprintf(logfile,"        double BSIM3kt2			    = %e \n", model->BSIM3kt2);
fprintf(logfile,"        double BSIM3k2	    	    	= %e \n", model->BSIM3k2);
fprintf(logfile,"        double BSIM3k3		    	    = %e \n", model->BSIM3k3);
fprintf(logfile,"        double BSIM3k3b			    = %e \n", model->BSIM3k3b);
fprintf(logfile,"        double BSIM3w0	    	    	= %e \n", model->BSIM3w0);
fprintf(logfile,"        double BSIM3nlx	    		= %e \n", model->BSIM3nlx);
fprintf(logfile,"        double BSIM3dvt0			    = %e \n", model->BSIM3dvt0);      
fprintf(logfile,"        double BSIM3dvt1   			= %e \n", model->BSIM3dvt1);      
fprintf(logfile,"        double BSIM3dvt2	    		= %e \n", model->BSIM3dvt2);      
fprintf(logfile,"        double BSIM3dvt0w		    	= %e \n", model->BSIM3dvt0w);      
fprintf(logfile,"        double BSIM3dvt1w			    = %e \n", model->BSIM3dvt1w);      
fprintf(logfile,"        double BSIM3dvt2w	    		= %e \n", model->BSIM3dvt2w);      
fprintf(logfile,"        double BSIM3drout		    	= %e \n", model->BSIM3drout);      
fprintf(logfile,"        double BSIM3dsub			    = %e \n", model->BSIM3dsub);      
fprintf(logfile,"        double BSIM3vth0		    	= %e \n", model->BSIM3vth0);
fprintf(logfile,"        double BSIM3ua		           	= %e \n", model->BSIM3ua);
fprintf(logfile,"        double BSIM3ua1	    		= %e \n", model->BSIM3ua1);
fprintf(logfile,"        double BSIM3ub		        	= %e \n", model->BSIM3ub);
fprintf(logfile,"        double BSIM3ub1	    		= %e \n", model->BSIM3ub1);
fprintf(logfile,"        double BSIM3uc		        	= %e \n", model->BSIM3uc);
fprintf(logfile,"        double BSIM3uc1	    		= %e \n", model->BSIM3uc1);
fprintf(logfile,"        double BSIM3u0		        	= %e \n", model->BSIM3u0);
fprintf(logfile,"        double BSIM3ute			= %e \n", model->BSIM3ute);
fprintf(logfile,"        double BSIM3voff			= %e \n", model->BSIM3voff);
fprintf(logfile,"        double BSIM3delta			= %e \n", model->BSIM3delta);
fprintf(logfile,"        double BSIM3rdsw			= %e \n", model->BSIM3rdsw);       
fprintf(logfile,"        double BSIM3prwg			= %e \n", model->BSIM3prwg);
fprintf(logfile,"        double BSIM3prwb			= %e \n", model->BSIM3prwb);
fprintf(logfile,"        double BSIM3prt			= %e \n", model->BSIM3prt);       
fprintf(logfile,"        double BSIM3eta0			= %e \n", model->BSIM3eta0);         
fprintf(logfile,"        double BSIM3etab			= %e \n", model->BSIM3etab);         
fprintf(logfile,"        double BSIM3pclm			= %e \n", model->BSIM3pclm);      
fprintf(logfile,"        double BSIM3pdibl1			= %e \n", model->BSIM3pdibl1);      
fprintf(logfile,"        double BSIM3pdibl2			= %e \n", model->BSIM3pdibl2);      
fprintf(logfile,"        double BSIM3pdiblb			= %e \n", model->BSIM3pdiblb);
fprintf(logfile,"        double BSIM3pscbe1			= %e \n", model->BSIM3pscbe1);       
fprintf(logfile,"        double BSIM3pscbe2			= %e \n", model->BSIM3pscbe2);       
fprintf(logfile,"        double BSIM3pvag			= %e \n", model->BSIM3pvag);       
fprintf(logfile,"        double BSIM3wr	    		= %e \n", model->BSIM3wr);
fprintf(logfile,"        double BSIM3dwg			= %e \n", model->BSIM3dwg);
fprintf(logfile,"        double BSIM3dwb			= %e \n", model->BSIM3dwb);
fprintf(logfile,"        double BSIM3b0		    	= %e \n", model->BSIM3b0);
fprintf(logfile,"        double BSIM3b1			    = %e \n", model->BSIM3b1);
fprintf(logfile,"        double BSIM3alpha0			= %e \n", model->BSIM3alpha0);
fprintf(logfile,"        double BSIM3alpha1			= %e \n", model->BSIM3alpha1);
fprintf(logfile,"        double BSIM3beta0			= %e \n", model->BSIM3beta0);
fprintf(logfile,"    +   double BSIM3ijth			= %e \n", model->BSIM3ijth);
fprintf(logfile,"        double BSIM3vfb			= %e \n", model->BSIM3vfb);

fprintf(logfile,"        double BSIM3elm			= %e \n", model->BSIM3elm);
fprintf(logfile,"        double BSIM3cgsl			= %e \n", model->BSIM3cgsl);
fprintf(logfile,"        double BSIM3cgdl			= %e \n", model->BSIM3cgdl);
fprintf(logfile,"        double BSIM3ckappa			= %e \n", model->BSIM3ckappa);
fprintf(logfile,"        double BSIM3cf			    = %e \n", model->BSIM3cf);
fprintf(logfile,"        double BSIM3vfbcv			= %e \n", model->BSIM3vfbcv);
fprintf(logfile,"        double BSIM3clc			= %e \n", model->BSIM3clc);
fprintf(logfile,"        double BSIM3cle			= %e \n", model->BSIM3cle);
fprintf(logfile,"        double BSIM3dwc			= %e \n", model->BSIM3dwc);
fprintf(logfile,"        double BSIM3dlc			= %e \n", model->BSIM3dlc);
fprintf(logfile,"        double BSIM3noff			= %e \n", model->BSIM3noff);
fprintf(logfile,"        double BSIM3voffcv			= %e \n", model->BSIM3voffcv);
fprintf(logfile,"        double BSIM3acde			= %e \n", model->BSIM3acde);
fprintf(logfile,"        double BSIM3moin			= %e \n", model->BSIM3moin);
fprintf(logfile,"        double BSIM3tcj			= %e \n", model->BSIM3tcj);
fprintf(logfile,"        double BSIM3tcjsw			= %e \n", model->BSIM3tcjsw);
fprintf(logfile,"        double BSIM3tcjswg			= %e \n", model->BSIM3tcjswg);
fprintf(logfile,"        double BSIM3tpb			= %e \n", model->BSIM3tpb);
fprintf(logfile,"        double BSIM3tpbsw			= %e \n", model->BSIM3tpbsw);
fprintf(logfile,"        double BSIM3tpbswg			= %e \n", model->BSIM3tpbswg);
fprintf(logfile,"        double BSIM3lcdsc			= %e \n", model->BSIM3lcdsc);           
fprintf(logfile,"        double BSIM3lcdscb			= %e \n", model->BSIM3lcdscb); 
fprintf(logfile,"        double BSIM3lcdscd			= %e \n", model->BSIM3lcdscd);          
fprintf(logfile,"        double BSIM3lcit			= %e \n", model->BSIM3lcit);           
fprintf(logfile,"        double BSIM3lnfactor		= %e \n", model->BSIM3lnfactor);      
fprintf(logfile,"        double BSIM3lxj			= %e \n", model->BSIM3lxj);
fprintf(logfile,"        double BSIM3lvsat			= %e \n", model->BSIM3lvsat);         
fprintf(logfile,"        double BSIM3lat			= %e \n", model->BSIM3lat);         
fprintf(logfile,"        double BSIM3la0			= %e \n", model->BSIM3la0);   
fprintf(logfile,"        double BSIM3lags			= %e \n", model->BSIM3lags);      
fprintf(logfile,"        double BSIM3la1			= %e \n", model->BSIM3la1);         
fprintf(logfile,"        double BSIM3la2			= %e \n", model->BSIM3la2);         
fprintf(logfile,"        double BSIM3lketa			= %e \n", model->BSIM3lketa);     
fprintf(logfile,"        double BSIM3lnsub			= %e \n", model->BSIM3lnsub);
fprintf(logfile,"        double BSIM3lnpeak			= %e \n", model->BSIM3lnpeak);        
fprintf(logfile,"        double BSIM3lngate			= %e \n", model->BSIM3lngate);        
fprintf(logfile,"        double BSIM3lgamma1		= %e \n", model->BSIM3lgamma1);      
fprintf(logfile,"        double BSIM3lgamma2		= %e \n", model->BSIM3lgamma2);     
fprintf(logfile,"        double BSIM3lvbx			= %e \n", model->BSIM3lvbx);      
fprintf(logfile,"        double BSIM3lvbm			= %e \n", model->BSIM3lvbm);       
fprintf(logfile,"        double BSIM3lxt			= %e \n", model->BSIM3lxt);       
fprintf(logfile,"        double BSIM3lk1			= %e \n", model->BSIM3lk1);
fprintf(logfile,"        double BSIM3lkt1			= %e \n", model->BSIM3lkt1);
fprintf(logfile,"        double BSIM3lkt1l			= %e \n", model->BSIM3lkt1l);
fprintf(logfile,"        double BSIM3lkt2			= %e \n", model->BSIM3lkt2);
fprintf(logfile,"        double BSIM3lk2			= %e \n", model->BSIM3lk2);
fprintf(logfile,"        double BSIM3lk3			= %e \n", model->BSIM3lk3);
fprintf(logfile,"        double BSIM3lk3b			= %e \n", model->BSIM3lk3b);
fprintf(logfile,"        double BSIM3lw0			= %e \n", model->BSIM3lw0);
fprintf(logfile,"        double BSIM3lnlx			= %e \n", model->BSIM3lnlx);
fprintf(logfile,"        double BSIM3ldvt0			= %e \n", model->BSIM3ldvt0);      
fprintf(logfile,"        double BSIM3ldvt1			= %e \n", model->BSIM3ldvt1);      
fprintf(logfile,"        double BSIM3ldvt2			= %e \n", model->BSIM3ldvt2);      
fprintf(logfile,"        double BSIM3ldvt0w			= %e \n", model->BSIM3ldvt0w);      
fprintf(logfile,"        double BSIM3ldvt1w			= %e \n", model->BSIM3ldvt1w);      
fprintf(logfile,"        double BSIM3ldvt2w			= %e \n", model->BSIM3ldvt2w);      
fprintf(logfile,"        double BSIM3ldrout			= %e \n", model->BSIM3ldrout);      
fprintf(logfile,"        double BSIM3ldsub			= %e \n", model->BSIM3ldsub);      
fprintf(logfile,"        double BSIM3lvth0			= %e \n", model->BSIM3lvth0);
fprintf(logfile,"        double BSIM3lua			= %e \n", model->BSIM3lua);
fprintf(logfile,"        double BSIM3lua1			= %e \n", model->BSIM3lua1);
fprintf(logfile,"        double BSIM3lub			= %e \n", model->BSIM3lub);
fprintf(logfile,"        double BSIM3lub1			= %e \n", model->BSIM3lub1);
fprintf(logfile,"        double BSIM3luc			= %e \n", model->BSIM3luc);
fprintf(logfile,"        double BSIM3luc1			= %e \n", model->BSIM3luc1);
fprintf(logfile,"        double BSIM3lu0			= %e \n", model->BSIM3lu0);
fprintf(logfile,"        double BSIM3lute			= %e \n", model->BSIM3lute);
fprintf(logfile,"        double BSIM3lvoff			= %e \n", model->BSIM3lvoff);
fprintf(logfile,"        double BSIM3ldelta			= %e \n", model->BSIM3ldelta);
fprintf(logfile,"        double BSIM3lrdsw			= %e \n", model->BSIM3lrdsw);       
fprintf(logfile,"        double BSIM3lprwg			= %e \n", model->BSIM3lprwg);
fprintf(logfile,"        double BSIM3lprwb			= %e \n", model->BSIM3lprwb);
fprintf(logfile,"        double BSIM3lprt			= %e \n", model->BSIM3lprt);       
fprintf(logfile,"        double BSIM3leta0			= %e \n", model->BSIM3leta0);         
fprintf(logfile,"        double BSIM3letab			= %e \n", model->BSIM3letab);         
fprintf(logfile,"        double BSIM3lpclm			= %e \n", model->BSIM3lpclm);      
fprintf(logfile,"        double BSIM3lpdibl1		= %e \n", model->BSIM3lpdibl1);      
fprintf(logfile,"        double BSIM3lpdibl2		= %e \n", model->BSIM3lpdibl2);      
fprintf(logfile,"        double BSIM3lpdiblb		= %e \n", model->BSIM3lpdiblb);
fprintf(logfile,"        double BSIM3lpscbe1		= %e \n", model->BSIM3lpscbe1);       
fprintf(logfile,"        double BSIM3lpscbe2		= %e \n", model->BSIM3lpscbe2);       
fprintf(logfile,"        double BSIM3lpvag			= %e \n", model->BSIM3lpvag);       
fprintf(logfile,"        double BSIM3lwr			= %e \n", model->BSIM3lwr);
fprintf(logfile,"        double BSIM3ldwg			= %e \n", model->BSIM3ldwg);
fprintf(logfile,"        double BSIM3ldwb			= %e \n", model->BSIM3ldwb);
fprintf(logfile,"        double BSIM3lb0			= %e \n", model->BSIM3lb0);
fprintf(logfile,"        double BSIM3lb1			= %e \n", model->BSIM3lb1);
fprintf(logfile,"        double BSIM3lalpha0		= %e \n", model->BSIM3lalpha0);
fprintf(logfile,"        double BSIM3lalpha1		= %e \n", model->BSIM3lalpha1);
fprintf(logfile,"        double BSIM3lbeta0			= %e \n", model->BSIM3lbeta0);
fprintf(logfile,"        double BSIM3lvfb			= %e \n", model->BSIM3lvfb);

fprintf(logfile,"        double BSIM3lelm			= %e \n", model->BSIM3lelm);
fprintf(logfile,"        double BSIM3lcgsl			= %e \n", model->BSIM3lcgsl);
fprintf(logfile,"        double BSIM3lcgdl			= %e \n", model->BSIM3lcgdl);
fprintf(logfile,"        double BSIM3lckappa		= %e \n", model->BSIM3lckappa);
fprintf(logfile,"        double BSIM3lcf			= %e \n", model->BSIM3lcf);
fprintf(logfile,"        double BSIM3lclc			= %e \n", model->BSIM3lclc);
fprintf(logfile,"        double BSIM3lcle			= %e \n", model->BSIM3lcle);
fprintf(logfile,"        double BSIM3lvfbcv			= %e \n", model->BSIM3lvfbcv);
fprintf(logfile,"        double BSIM3lnoff			= %e \n", model->BSIM3lnoff);
fprintf(logfile,"        double BSIM3lvoffcv		= %e \n", model->BSIM3lvoffcv);
fprintf(logfile,"        double BSIM3lacde			= %e \n", model->BSIM3lacde);
fprintf(logfile,"        double BSIM3lmoin			= %e \n", model->BSIM3lmoin);

// Width Dependence 
fprintf(logfile,"        double BSIM3wcdsc			= %e \n", model->BSIM3wcdsc);           
fprintf(logfile,"        double BSIM3wcdscb			= %e \n", model->BSIM3wcdscb); 
fprintf(logfile,"        double BSIM3wcdscd			= %e \n", model->BSIM3wcdscd);          
fprintf(logfile,"        double BSIM3wcit			= %e \n", model->BSIM3wcit);           
fprintf(logfile,"        double BSIM3wnfactor		= %e \n", model->BSIM3wnfactor);      
fprintf(logfile,"        double BSIM3wxj			= %e \n", model->BSIM3wxj);
fprintf(logfile,"        double BSIM3wvsat			= %e \n", model->BSIM3wvsat);         
fprintf(logfile,"        double BSIM3wat			= %e \n", model->BSIM3wat);         
fprintf(logfile,"        double BSIM3wa0			= %e \n", model->BSIM3wa0);   
fprintf(logfile,"        double BSIM3wags			= %e \n", model->BSIM3wags);      
fprintf(logfile,"        double BSIM3wa1			= %e \n", model->BSIM3wa1);         
fprintf(logfile,"        double BSIM3wa2			= %e \n", model->BSIM3wa2);         
fprintf(logfile,"        double BSIM3wketa			= %e \n", model->BSIM3wketa);     
fprintf(logfile,"        double BSIM3wnsub			= %e \n", model->BSIM3wnsub);
fprintf(logfile,"        double BSIM3wnpeak			= %e \n", model->BSIM3wnpeak);        
fprintf(logfile,"        double BSIM3wngate			= %e \n", model->BSIM3wngate);        
fprintf(logfile,"        double BSIM3wgamma1		= %e \n", model->BSIM3wgamma1);      
fprintf(logfile,"        double BSIM3wgamma2		= %e \n", model->BSIM3wgamma2);     
fprintf(logfile,"        double BSIM3wvbx			= %e \n", model->BSIM3wvbx);      
fprintf(logfile,"        double BSIM3wvbm			= %e \n", model->BSIM3wvbm);       
fprintf(logfile,"        double BSIM3wxt			= %e \n", model->BSIM3wxt);       
fprintf(logfile,"        double BSIM3wk1			= %e \n", model->BSIM3wk1);
fprintf(logfile,"        double BSIM3wkt1			= %e \n", model->BSIM3wkt1);
fprintf(logfile,"        double BSIM3wkt1l			= %e \n", model->BSIM3wkt1l);
fprintf(logfile,"        double BSIM3wkt2			= %e \n", model->BSIM3wkt2);
fprintf(logfile,"        double BSIM3wk2			= %e \n", model->BSIM3wk2);
fprintf(logfile,"        double BSIM3wk3			= %e \n", model->BSIM3wk3);
fprintf(logfile,"        double BSIM3wk3b			= %e \n", model->BSIM3wk3b);
fprintf(logfile,"        double BSIM3ww0			= %e \n", model->BSIM3ww0);
fprintf(logfile,"        double BSIM3wnlx			= %e \n", model->BSIM3wnlx);
fprintf(logfile,"        double BSIM3wdvt0			= %e \n", model->BSIM3wdvt0);      
fprintf(logfile,"        double BSIM3wdvt1			= %e \n", model->BSIM3wdvt1);      
fprintf(logfile,"        double BSIM3wdvt2			= %e \n", model->BSIM3wdvt2);      
fprintf(logfile,"        double BSIM3wdvt0w			= %e \n", model->BSIM3wdvt0w);      
fprintf(logfile,"        double BSIM3wdvt1w			= %e \n", model->BSIM3wdvt1w);      
fprintf(logfile,"        double BSIM3wdvt2w			= %e \n", model->BSIM3wdvt2w);      
fprintf(logfile,"        double BSIM3wdrout			= %e \n", model->BSIM3wdrout);      
fprintf(logfile,"        double BSIM3wdsub			= %e \n", model->BSIM3wdsub);      
fprintf(logfile,"        double BSIM3wvth0			= %e \n", model->BSIM3wvth0);
fprintf(logfile,"        double BSIM3wua			= %e \n", model->BSIM3wua);
fprintf(logfile,"        double BSIM3wua1			= %e \n", model->BSIM3wua1);
fprintf(logfile,"        double BSIM3wub			= %e \n", model->BSIM3wub);
fprintf(logfile,"        double BSIM3wub1			= %e \n", model->BSIM3wub1);
fprintf(logfile,"        double BSIM3wuc			= %e \n", model->BSIM3wuc);
fprintf(logfile,"        double BSIM3wuc1			= %e \n", model->BSIM3wuc1);
fprintf(logfile,"        double BSIM3wu0			= %e \n", model->BSIM3wu0);
fprintf(logfile,"        double BSIM3wute			= %e \n", model->BSIM3wute);
fprintf(logfile,"        double BSIM3wvoff			= %e \n", model->BSIM3wvoff);
fprintf(logfile,"        double BSIM3wdelta			= %e \n", model->BSIM3wdelta);
fprintf(logfile,"        double BSIM3wrdsw			= %e \n", model->BSIM3wrdsw);       
fprintf(logfile,"        double BSIM3wprwg			= %e \n", model->BSIM3wprwg);
fprintf(logfile,"        double BSIM3wprwb			= %e \n", model->BSIM3wprwb);
fprintf(logfile,"        double BSIM3wprt			= %e \n", model->BSIM3wprt);       
fprintf(logfile,"        double BSIM3weta0			= %e \n", model->BSIM3weta0);         
fprintf(logfile,"        double BSIM3wetab			= %e \n", model->BSIM3wetab);         
fprintf(logfile,"        double BSIM3wpclm			= %e \n", model->BSIM3wpclm);      
fprintf(logfile,"        double BSIM3wpdibl1		= %e \n", model->BSIM3wpdibl1);      
fprintf(logfile,"        double BSIM3wpdibl2		= %e \n", model->BSIM3wpdibl2);      
fprintf(logfile,"        double BSIM3wpdiblb		= %e \n", model->BSIM3wpdiblb);
fprintf(logfile,"        double BSIM3wpscbe1		= %e \n", model->BSIM3wpscbe1);       
fprintf(logfile,"        double BSIM3wpscbe2		= %e \n", model->BSIM3wpscbe2);       
fprintf(logfile,"        double BSIM3wpvag			= %e \n", model->BSIM3wpvag);       
fprintf(logfile,"        double BSIM3wwr			= %e \n", model->BSIM3wwr);
fprintf(logfile,"        double BSIM3wdwg			= %e \n", model->BSIM3wdwg);
fprintf(logfile,"        double BSIM3wdwb			= %e \n", model->BSIM3wdwb);
fprintf(logfile,"        double BSIM3wb0			= %e \n", model->BSIM3wb0);
fprintf(logfile,"        double BSIM3wb1			= %e \n", model->BSIM3wb1);
fprintf(logfile,"        double BSIM3walpha0		= %e \n", model->BSIM3walpha0);
fprintf(logfile,"        double BSIM3walpha1		= %e \n", model->BSIM3walpha1);
fprintf(logfile,"        double BSIM3wbeta0			= %e \n", model->BSIM3wbeta0);
fprintf(logfile,"        double BSIM3wvfb			= %e \n", model->BSIM3wvfb);

// CV model 
fprintf(logfile,"        double BSIM3welm			= %e \n", model->BSIM3welm);
fprintf(logfile,"        double BSIM3wcgsl			= %e \n", model->BSIM3wcgsl);
fprintf(logfile,"        double BSIM3wcgdl			= %e \n", model->BSIM3wcgdl);
fprintf(logfile,"        double BSIM3wckappa		= %e \n", model->BSIM3wckappa);
fprintf(logfile,"        double BSIM3wcf			= %e \n", model->BSIM3wcf);
fprintf(logfile,"        double BSIM3wclc			= %e \n", model->BSIM3wclc);
fprintf(logfile,"        double BSIM3wcle			= %e \n", model->BSIM3wcle);
fprintf(logfile,"        double BSIM3wvfbcv			= %e \n", model->BSIM3wvfbcv);
fprintf(logfile,"        double BSIM3wnoff			= %e \n", model->BSIM3wnoff);
fprintf(logfile,"        double BSIM3wvoffcv		= %e \n", model->BSIM3wvoffcv);
fprintf(logfile,"        double BSIM3wacde			= %e \n", model->BSIM3wacde);
fprintf(logfile,"        double BSIM3wmoin			= %e \n", model->BSIM3wmoin);

// Cross-term Dependence 
fprintf(logfile,"        double BSIM3pcdsc			= %e \n", model->BSIM3pcdsc);           
fprintf(logfile,"        double BSIM3pcdscb			= %e \n", model->BSIM3pcdscb); 
fprintf(logfile,"        double BSIM3pcdscd			= %e \n", model->BSIM3pcdscd);          
fprintf(logfile,"        double BSIM3pcit			= %e \n", model->BSIM3pcit);           
fprintf(logfile,"        double BSIM3pnfactor		= %e \n", model->BSIM3pnfactor);      
fprintf(logfile,"        double BSIM3pxj			= %e \n", model->BSIM3pxj);
fprintf(logfile,"        double BSIM3pvsat			= %e \n", model->BSIM3pvsat);         
fprintf(logfile,"        double BSIM3pat			= %e \n", model->BSIM3pat);         
fprintf(logfile,"        double BSIM3pa0			= %e \n", model->BSIM3pa0);   
fprintf(logfile,"        double BSIM3pags			= %e \n", model->BSIM3pags);      
fprintf(logfile,"        double BSIM3pa1			= %e \n", model->BSIM3pa1);         
fprintf(logfile,"        double BSIM3pa2			= %e \n", model->BSIM3pa2);         
fprintf(logfile,"        double BSIM3pketa			= %e \n", model->BSIM3pketa);     
fprintf(logfile,"        double BSIM3pnsub			= %e \n", model->BSIM3pnsub);
fprintf(logfile,"        double BSIM3pnpeak			= %e \n", model->BSIM3pnpeak);        
fprintf(logfile,"        double BSIM3pngate			= %e \n", model->BSIM3pngate);        
fprintf(logfile,"        double BSIM3pgamma1		= %e \n", model->BSIM3pgamma1);      
fprintf(logfile,"        double BSIM3pgamma2		= %e \n", model->BSIM3pgamma2);     
fprintf(logfile,"        double BSIM3pvbx			= %e \n", model->BSIM3pvbx);      
fprintf(logfile,"        double BSIM3pvbm			= %e \n", model->BSIM3pvbm);       
fprintf(logfile,"        double BSIM3pxt			= %e \n", model->BSIM3pxt);       
fprintf(logfile,"        double BSIM3pk1			= %e \n", model->BSIM3pk1);
fprintf(logfile,"        double BSIM3pkt1			= %e \n", model->BSIM3pkt1);
fprintf(logfile,"        double BSIM3pkt1l			= %e \n", model->BSIM3pkt1l);
fprintf(logfile,"        double BSIM3pkt2			= %e \n", model->BSIM3pkt2);
fprintf(logfile,"        double BSIM3pk2			= %e \n", model->BSIM3pk2);
fprintf(logfile,"        double BSIM3pk3			= %e \n", model->BSIM3pk3);
fprintf(logfile,"        double BSIM3pk3b			= %e \n", model->BSIM3pk3b);
fprintf(logfile,"        double BSIM3pw0			= %e \n", model->BSIM3pw0);
fprintf(logfile,"        double BSIM3pnlx			= %e \n", model->BSIM3pnlx);
fprintf(logfile,"        double BSIM3pdvt0			= %e \n", model->BSIM3pdvt0);      
fprintf(logfile,"        double BSIM3pdvt1			= %e \n", model->BSIM3pdvt1);      
fprintf(logfile,"        double BSIM3pdvt2			= %e \n", model->BSIM3pdvt2);      
fprintf(logfile,"        double BSIM3pdvt0w			= %e \n", model->BSIM3pdvt0w);      
fprintf(logfile,"        double BSIM3pdvt1w			= %e \n", model->BSIM3pdvt1w);      
fprintf(logfile,"        double BSIM3pdvt2w			= %e \n", model->BSIM3pdvt2w);      
fprintf(logfile,"        double BSIM3pdrout			= %e \n", model->BSIM3pdrout);      
fprintf(logfile,"        double BSIM3pdsub			= %e \n", model->BSIM3pdsub);      
fprintf(logfile,"        double BSIM3pvth0			= %e \n", model->BSIM3pvth0);
fprintf(logfile,"        double BSIM3pua			= %e \n", model->BSIM3pua);
fprintf(logfile,"        double BSIM3pua1			= %e \n", model->BSIM3pua1);
fprintf(logfile,"        double BSIM3pub			= %e \n", model->BSIM3pub);
fprintf(logfile,"        double BSIM3pub1			= %e \n", model->BSIM3pub1);
fprintf(logfile,"        double BSIM3puc			= %e \n", model->BSIM3puc);
fprintf(logfile,"        double BSIM3puc1			= %e \n", model->BSIM3puc1);
fprintf(logfile,"        double BSIM3pu0			= %e \n", model->BSIM3pu0);
fprintf(logfile,"        double BSIM3pute			= %e \n", model->BSIM3pute);
fprintf(logfile,"        double BSIM3pvoff			= %e \n", model->BSIM3pvoff);
fprintf(logfile,"        double BSIM3pdelta			= %e \n", model->BSIM3pdelta);
fprintf(logfile,"        double BSIM3prdsw			= %e \n", model->BSIM3prdsw);
fprintf(logfile,"        double BSIM3pprwg			= %e \n", model->BSIM3pprwg);
fprintf(logfile,"        double BSIM3pprwb			= %e \n", model->BSIM3pprwb);
fprintf(logfile,"        double BSIM3pprt			= %e \n", model->BSIM3pprt);       
fprintf(logfile,"        double BSIM3peta0			= %e \n", model->BSIM3peta0);         
fprintf(logfile,"        double BSIM3petab			= %e \n", model->BSIM3petab);         
fprintf(logfile,"        double BSIM3ppclm			= %e \n", model->BSIM3ppclm);      
fprintf(logfile,"        double BSIM3ppdibl1		= %e \n", model->BSIM3ppdibl1);      
fprintf(logfile,"        double BSIM3ppdibl2		= %e \n", model->BSIM3ppdibl2);      
fprintf(logfile,"        double BSIM3ppdiblb		= %e \n", model->BSIM3ppdiblb);
fprintf(logfile,"        double BSIM3ppscbe1		= %e \n", model->BSIM3ppscbe1);       
fprintf(logfile,"        double BSIM3ppscbe2		= %e \n", model->BSIM3ppscbe2);       
fprintf(logfile,"        double BSIM3ppvag			= %e \n", model->BSIM3ppvag);       
fprintf(logfile,"        double BSIM3pwr			= %e \n", model->BSIM3pwr);
fprintf(logfile,"        double BSIM3pdwg			= %e \n", model->BSIM3pdwg);
fprintf(logfile,"        double BSIM3pdwb			= %e \n", model->BSIM3pdwb);
fprintf(logfile,"        double BSIM3pb0			= %e \n", model->BSIM3pb0);
fprintf(logfile,"        double BSIM3pb1		    = %e \n", model->BSIM3pb1);
fprintf(logfile,"        double BSIM3palpha0		= %e \n", model->BSIM3palpha0);
fprintf(logfile,"        double BSIM3palpha1		= %e \n", model->BSIM3palpha1);
fprintf(logfile,"        double BSIM3pbeta0			= %e \n", model->BSIM3pbeta0);
fprintf(logfile,"        double BSIM3pvfb			= %e \n", model->BSIM3pvfb);

            //CV model 
fprintf(logfile,"        double BSIM3pelm			= %e \n", model->BSIM3pelm);
fprintf(logfile,"        double BSIM3pcgsl			= %e \n", model->BSIM3pcgsl);
fprintf(logfile,"        double BSIM3pcgdl			= %e \n", model->BSIM3pcgdl);
fprintf(logfile,"        double BSIM3pckappa		= %e \n", model->BSIM3pckappa);
fprintf(logfile,"        double BSIM3pcf			= %e \n", model->BSIM3pcf);
fprintf(logfile,"        double BSIM3pclc			= %e \n", model->BSIM3pclc);
fprintf(logfile,"        double BSIM3pcle			= %e \n", model->BSIM3pcle);
fprintf(logfile,"        double BSIM3pvfbcv			= %e \n", model->BSIM3pvfbcv);
fprintf(logfile,"        double BSIM3pnoff			= %e \n", model->BSIM3pnoff);
fprintf(logfile,"        double BSIM3pvoffcv		= %e \n", model->BSIM3pvoffcv);
fprintf(logfile,"        double BSIM3pacde			= %e \n", model->BSIM3pacde);
fprintf(logfile,"        double BSIM3pmoin			= %e \n", model->BSIM3pmoin);

fprintf(logfile,"    +   double BSIM3tnom			= %e \n", model->BSIM3tnom);
fprintf(logfile,"        double BSIM3cgso			= %e \n", model->BSIM3cgso);
fprintf(logfile,"        double BSIM3cgdo			= %e \n", model->BSIM3cgdo);
fprintf(logfile,"        double BSIM3cgbo			= %e \n", model->BSIM3cgbo);
fprintf(logfile,"    +   double BSIM3xpart			= %e \n", model->BSIM3xpart);
fprintf(logfile,"        double BSIM3cFringOut		= %e \n", model->BSIM3cFringOut);
fprintf(logfile,"        double BSIM3cFringMax		= %e \n", model->BSIM3cFringMax);

fprintf(logfile,"        double BSIM3sheetResistance			    = %e \n", model->BSIM3sheetResistance);
fprintf(logfile,"        double BSIM3jctSatCurDensity			    = %e \n", model->BSIM3jctSatCurDensity);
fprintf(logfile,"        double BSIM3jctSidewallSatCurDensity		= %e \n", model->BSIM3jctSidewallSatCurDensity);
fprintf(logfile,"        double BSIM3bulkJctPotential			    = %e \n", model->BSIM3bulkJctPotential);
fprintf(logfile,"    +   double BSIM3bulkJctBotGradingCoeff		    = %e \n", model->BSIM3bulkJctBotGradingCoeff);
fprintf(logfile,"    +   double BSIM3bulkJctSideGradingCoeff		= %e \n", model->BSIM3bulkJctSideGradingCoeff);
fprintf(logfile,"    +   double BSIM3bulkJctGateSideGradingCoeff	= %e \n", model->BSIM3bulkJctGateSideGradingCoeff);
fprintf(logfile,"        double BSIM3sidewallJctPotential			= %e \n", model->BSIM3sidewallJctPotential);
fprintf(logfile,"        double BSIM3GatesidewallJctPotential		= %e \n", model->BSIM3GatesidewallJctPotential);
fprintf(logfile,"        double BSIM3unitAreaJctCap			        = %e \n", model->BSIM3unitAreaJctCap);
fprintf(logfile,"        double BSIM3unitLengthSidewallJctCap		= %e \n", model->BSIM3unitLengthSidewallJctCap);
fprintf(logfile,"        double BSIM3unitLengthGateSidewallJctCap	= %e \n", model->BSIM3unitLengthGateSidewallJctCap);
fprintf(logfile,"    +   double BSIM3jctEmissionCoeff			    = %e \n", model->BSIM3jctEmissionCoeff);
fprintf(logfile,"        double BSIM3jctTempExponent			    = %e \n", model->BSIM3jctTempExponent);

fprintf(logfile,"        double BSIM3Lint			= %e \n", model->BSIM3Lint);
fprintf(logfile,"        double BSIM3Ll			    = %e \n", model->BSIM3Ll);
fprintf(logfile,"        double BSIM3Llc			= %e \n", model->BSIM3Llc);
fprintf(logfile,"        double BSIM3Lln			= %e \n", model->BSIM3Lln);
fprintf(logfile,"        double BSIM3Lw			    = %e \n", model->BSIM3Lw);
fprintf(logfile,"        double BSIM3Lwc			= %e \n", model->BSIM3Lwc);
fprintf(logfile,"        double BSIM3Lwn			= %e \n", model->BSIM3Lwn);
fprintf(logfile,"        double BSIM3Lwl			= %e \n", model->BSIM3Lwl);
fprintf(logfile,"        double BSIM3Lwlc			= %e \n", model->BSIM3Lwlc);
fprintf(logfile,"        double BSIM3Lmin			= %e \n", model->BSIM3Lmin);
fprintf(logfile,"        double BSIM3Lmax			= %e \n", model->BSIM3Lmax);


fprintf(logfile,"        double BSIM3Wint			= %e \n", model->BSIM3Wint);
fprintf(logfile,"        double BSIM3Wl			    = %e \n", model->BSIM3Wl);
fprintf(logfile,"        double BSIM3Wlc			= %e \n", model->BSIM3Wlc);
fprintf(logfile,"        double BSIM3Wln			= %e \n", model->BSIM3Wln);
fprintf(logfile,"        double BSIM3Ww			    = %e \n", model->BSIM3Ww);
fprintf(logfile,"        double BSIM3Wwc			= %e \n", model->BSIM3Wwc);
fprintf(logfile,"        double BSIM3Wwn			= %e \n", model->BSIM3Wwn);
fprintf(logfile,"        double BSIM3Wwl			= %e \n", model->BSIM3Wwl);
fprintf(logfile,"        double BSIM3Wwlc			= %e \n", model->BSIM3Wwlc);
fprintf(logfile,"        double BSIM3Wmin			= %e \n", model->BSIM3Wmin);
fprintf(logfile,"        double BSIM3Wmax			= %e \n", model->BSIM3Wmax);

                  // Pre-calculated constants 
                  // MCJ: move to size-dependent param. 
fprintf(logfile,"    +   double BSIM3vtm			= %e \n", model->BSIM3vtm);   
fprintf(logfile,"    +   double BSIM3cox			= %e \n", model->BSIM3cox);
fprintf(logfile,"        double BSIM3cof1			= %e \n", model->BSIM3cof1);
fprintf(logfile,"        double BSIM3cof2			= %e \n", model->BSIM3cof2);
fprintf(logfile,"        double BSIM3cof3			= %e \n", model->BSIM3cof3);
fprintf(logfile,"        double BSIM3cof4			= %e \n", model->BSIM3cof4);
fprintf(logfile,"    +   double BSIM3vcrit			= %e \n", model->BSIM3vcrit);
fprintf(logfile,"    +   double BSIM3factor1		= %e \n", model->BSIM3factor1);
fprintf(logfile,"    +   double BSIM3PhiB			= %e \n", model->BSIM3PhiB);
fprintf(logfile,"    +   double BSIM3PhiBSW		    = %e \n", model->BSIM3PhiBSW);
fprintf(logfile,"    +   double BSIM3PhiBSWG		= %e \n", model->BSIM3PhiBSWG);
fprintf(logfile,"    +   double BSIM3jctTempSatCurDensity			    = %e \n", model->BSIM3jctTempSatCurDensity);
fprintf(logfile,"    +   double BSIM3jctSidewallTempSatCurDensity		= %e \n", model->BSIM3jctSidewallTempSatCurDensity);
fprintf(logfile,"    +   double BSIM3unitAreaTempJctCap			        = %e \n", model->BSIM3unitAreaTempJctCap);
fprintf(logfile,"    +   double BSIM3unitLengthSidewallTempJctCap		= %e \n", model->BSIM3unitLengthSidewallTempJctCap);
fprintf(logfile,"    +   double BSIM3unitLengthGateSidewallTempJctCap	= %e \n", model->BSIM3unitLengthGateSidewallTempJctCap);

fprintf(logfile,"        double BSIM3oxideTrapDensityA			        = %e \n", model->BSIM3oxideTrapDensityA);      
fprintf(logfile,"        double BSIM3oxideTrapDensityB			        = %e \n", model->BSIM3oxideTrapDensityB);     
fprintf(logfile,"        double BSIM3oxideTrapDensityC			        = %e \n", model->BSIM3oxideTrapDensityC);  
fprintf(logfile,"        double BSIM3em			    = %e \n", model->BSIM3em);  
fprintf(logfile,"        double BSIM3ef			    = %e \n", model->BSIM3ef);  
fprintf(logfile,"        double BSIM3af			    = %e \n", model->BSIM3af);  
fprintf(logfile,"        double BSIM3kf		    	= %e \n", model->BSIM3kf);  
fprintf(logfile,"        double BSIM3lintnoi		= %e \n", model->BSIM3lintnoi);  // lint offset for noise calculation  lation  

//fprintf(logfile,"        struct bsim3SizeDependParam *pSizeDependParamKnot = %X \n", model->pSizeDependParamKnot);

fprintf(logfile,"  == model end \n", count, msg); 
return 1;
}



/*-------------------------------------------------------------------------------------*/


/*-- create_model -------------------------------------------------------------*/


int create_BSIM3model (BSIM3model **model){

BSIM3instance *here;

(*model)                    = (BSIM3model *) malloc(sizeof(BSIM3model));
(*model)->BSIM3nextModel    =NULL;      // no next model
(*model)->BSIM3instances    =(BSIM3instance*) malloc(sizeof(BSIM3instance));
/* 
printf("create_BSIM3model: sizeof(BSIM3instance)= %i\n", sizeof(BSIM3instance));
printf("create_BSIM3model: (*model) = %X \n", (*model));
printf("create_BSIM3model: (*model)->BSIM3instances = %X \n",(*model)->BSIM3instances);
*/
here=(*model)->BSIM3instances;;

//printf("create_BSIM3model: here = %X \n", here);

here->BSIM3modPtr = NULL;               // upper
here->BSIM3nextInstance=NULL;           // no next instances
here->pParam = (struct bsim3SizeDependParam *)malloc (sizeof(struct bsim3SizeDependParam));

(here->BSIM3DdPtr)  =(double*)malloc(sizeof(double));
(here->BSIM3GgPtr)  =(double*)malloc(sizeof(double));
(here->BSIM3SsPtr)  =(double*)malloc(sizeof(double));
(here->BSIM3BbPtr)  =(double*)malloc(sizeof(double));
(here->BSIM3DPdpPtr)=(double*)malloc(sizeof(double));
(here->BSIM3SPspPtr)=(double*)malloc(sizeof(double));
(here->BSIM3DdpPtr) =(double*)malloc(sizeof(double));
(here->BSIM3GbPtr)  =(double*)malloc(sizeof(double));
(here->BSIM3GdpPtr) =(double*)malloc(sizeof(double));
(here->BSIM3GspPtr) =(double*)malloc(sizeof(double));
(here->BSIM3SspPtr) =(double*)malloc(sizeof(double));
(here->BSIM3BdpPtr) =(double*)malloc(sizeof(double));
(here->BSIM3BspPtr) =(double*)malloc(sizeof(double));
(here->BSIM3DPspPtr)=(double*)malloc(sizeof(double));
(here->BSIM3DPdPtr) =(double*)malloc(sizeof(double));
(here->BSIM3BgPtr)  =(double*)malloc(sizeof(double));
(here->BSIM3DPgPtr) =(double*)malloc(sizeof(double));
(here->BSIM3SPgPtr) =(double*)malloc(sizeof(double));
(here->BSIM3SPsPtr) =(double*)malloc(sizeof(double));
(here->BSIM3DPbPtr) =(double*)malloc(sizeof(double));
(here->BSIM3SPbPtr) =(double*)malloc(sizeof(double));
(here->BSIM3SPdpPtr)=(double*)malloc(sizeof(double));

(here->BSIM3QqPtr)  =(double*)malloc(sizeof(double));
(here->BSIM3QdpPtr) =(double*)malloc(sizeof(double));
(here->BSIM3QgPtr)  =(double*)malloc(sizeof(double));
(here->BSIM3QspPtr) =(double*)malloc(sizeof(double));
(here->BSIM3QbPtr)  =(double*)malloc(sizeof(double));
(here->BSIM3DPqPtr) =(double*)malloc(sizeof(double));
(here->BSIM3GqPtr)  =(double*)malloc(sizeof(double));
(here->BSIM3SPqPtr) =(double*)malloc(sizeof(double));
(here->BSIM3BqPtr)  =(double*)malloc(sizeof(double));

}

int free_BSIM3model (BSIM3model **model){

BSIM3instance *here;

here=(*model)->BSIM3instances;;

free(here->pParam);

free(here->BSIM3DdPtr)  ;
free(here->BSIM3GgPtr)  ;
free(here->BSIM3SsPtr)  ;
free(here->BSIM3BbPtr)  ;
free(here->BSIM3DPdpPtr);
free(here->BSIM3SPspPtr);
free(here->BSIM3DdpPtr) ;
free(here->BSIM3GbPtr)  ;
free(here->BSIM3GdpPtr) ;
free(here->BSIM3GspPtr) ;
free(here->BSIM3SspPtr) ;
free(here->BSIM3BdpPtr) ;
free(here->BSIM3BspPtr) ;
free(here->BSIM3DPspPtr);
free(here->BSIM3DPdPtr) ;
free(here->BSIM3BgPtr)  ;
free(here->BSIM3DPgPtr) ;
free(here->BSIM3SPgPtr) ;
free(here->BSIM3SPsPtr) ;
free(here->BSIM3DPbPtr) ;
free(here->BSIM3SPbPtr) ;
free(here->BSIM3SPdpPtr);

free(here->BSIM3QqPtr)  ;
free(here->BSIM3QdpPtr) ;
free(here->BSIM3QgPtr)  ;
free(here->BSIM3QspPtr) ;
free(here->BSIM3QbPtr)  ;
free(here->BSIM3DPqPtr) ;
free(here->BSIM3GqPtr)  ;
free(here->BSIM3SPqPtr) ;
free(here->BSIM3BqPtr)  ;

free (here);
free (*model);
}

/*-- read_instance -------------------------------------------------------------*/


int read_instances(FILE * logfile, BSIM3model *model){
char msg1[25], msg2[25];
int dummy;
BSIM3instance * here;
struct bsim3SizeDependParam  *pParam;
int verbose=0;
int ret;

ret=fscanf(logfile,"  === run no %i %s %s : instances\n", &dummy, msg1, msg2);  CHECK(3);
/*int size;
char * buf = malloc(sizeof(char) * 256);
getline ( &buf, &size,logfile);
printf(" #### %s \n", buf);
*/
    { // process one instance only!!!
here=model->BSIM3instances;
ret=fscanf(logfile,"  = instance \n"); CHECK(0); 
//ret=fscanf(logfile," instance address = %X\n", &dummy); CHECK(1);
//ret=fscanf(logfile,"         struct sBSIM3model *BSIM3modPtr           = %X \n",   &dummy); CHECK(1);
//ret=fscanf(logfile,"         struct sBSIM3instance *BSIM3nextInstance  = %X \n",    &dummy); CHECK(1);
ret=fscanf(logfile,"         IFuid BSIM3name                           = %s \n",   &dummy); CHECK(1);
ret=fscanf(logfile,"     +   int BSIM3states				= %i \n", &(here->BSIM3states)); CHECK(1);                                                // index into state table for this device 

ret=fscanf(logfile,"     *   int BSIM3dNode				= %i \n", &(here->BSIM3dNode)); CHECK(1);
ret=fscanf(logfile,"     +   int BSIM3gNode				= %i \n", &(here->BSIM3gNode)); CHECK(1);  //!!
ret=fscanf(logfile,"     *   int BSIM3sNode				= %i \n", &(here->BSIM3sNode)); CHECK(1);
ret=fscanf(logfile,"     +   int BSIM3bNode				= %i \n", &(here->BSIM3bNode)); CHECK(1);
ret=fscanf(logfile,"     +   int BSIM3dNodePrime			= %i \n", &here->BSIM3dNodePrime); CHECK(1);
ret=fscanf(logfile,"     +   int BSIM3sNodePrime			= %i \n", &here->BSIM3sNodePrime); CHECK(1);
ret=fscanf(logfile,"     +   int BSIM3qNode				= %i \n", &here->BSIM3qNode); CHECK(1);                                                 // MCJ 

    // MCJ b
ret=fscanf(logfile,"     +   double BSIM3ueff				= %le \n", &here->BSIM3ueff); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3thetavth			= %le \n", &here->BSIM3thetavth); CHECK(1); 
ret=fscanf(logfile,"     +   double BSIM3von				= %le \n", &here->BSIM3von); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3vdsat				= %le \n", &here->BSIM3vdsat); CHECK(1);
ret=fscanf(logfile,"     *   double BSIM3cgdo				= %le \n", &here->BSIM3cgdo); CHECK(1);
ret=fscanf(logfile,"     *   double BSIM3cgso				= %le \n", &here->BSIM3cgso); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3vjsm				= %le \n", &here->BSIM3vjsm); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3IsEvjsm			= %le \n", &here->BSIM3IsEvjsm); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3vjdm				= %le \n", &here->BSIM3vjdm); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3IsEvjdm			= %le \n", &here->BSIM3IsEvjdm); CHECK(1);

ret=fscanf(logfile,"     *   double BSIM3l				    = %le \n", &here->BSIM3l); CHECK(1);
ret=fscanf(logfile,"     *   double BSIM3w				    = %le \n", &here->BSIM3w); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3drainArea			= %le \n", &here->BSIM3drainArea); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3sourceArea		= %le \n", &here->BSIM3sourceArea); CHECK(1);
ret=fscanf(logfile,"     *   double BSIM3drainSquares		= %le \n", &here->BSIM3drainSquares); CHECK(1);
ret=fscanf(logfile,"     *   double BSIM3sourceSquares		= %le \n", &here->BSIM3sourceSquares); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3drainPerimeter	= %le \n", &here->BSIM3drainPerimeter); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3sourcePerimeter	= %le \n", &here->BSIM3sourcePerimeter); CHECK(1);
ret=fscanf(logfile,"     *   double BSIM3sourceConductance	= %le \n", &here->BSIM3sourceConductance); CHECK(1);
ret=fscanf(logfile,"     *   double BSIM3drainConductance	= %le \n", &here->BSIM3drainConductance); CHECK(1);

ret=fscanf(logfile,"     +   double BSIM3icVBS				= %le \n", &here->BSIM3icVBS); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3icVDS				= %le \n", &here->BSIM3icVDS); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3icVGS				= %le \n", &here->BSIM3icVGS); CHECK(1);
ret=fscanf(logfile,"     +   int BSIM3off				    = %i \n", &here->BSIM3off); CHECK(1);
ret=fscanf(logfile,"     +   int BSIM3mode				    = %i \n", &here->BSIM3mode); CHECK(1);
ret=fscanf(logfile,"     *   int BSIM3nqsMod				= %i \n", &here->BSIM3nqsMod); CHECK(1);
ret=fscanf(logfile,"     *   int BSIM3acnqsMod				= %i \n", &here->BSIM3acnqsMod); CHECK(1);

    // OP point 
ret=fscanf(logfile,"     *   double BSIM3qinv				= %le \n", &here->BSIM3qinv); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3cd				= %le \n", &here->BSIM3cd); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3cbs				= %le \n", &here->BSIM3cbs); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3cbd				= %le \n", &here->BSIM3cbd); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3csub				= %le \n", &here->BSIM3csub); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3gm				= %le \n", &here->BSIM3gm); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3gds				= %le \n", &here->BSIM3gds); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3gmbs				= %le \n", &here->BSIM3gmbs); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3gbd				= %le \n", &here->BSIM3gbd); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3gbs				= %le \n", &here->BSIM3gbs); CHECK(1);

ret=fscanf(logfile,"     +   double BSIM3gbbs				= %le \n", &here->BSIM3gbbs); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3gbgs				= %le \n", &here->BSIM3gbgs); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3gbds				= %le \n", &here->BSIM3gbds); CHECK(1);

ret=fscanf(logfile,"     +   double BSIM3cggb				= %le \n", &here->BSIM3cggb); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3cgdb				= %le \n", &here->BSIM3cgdb); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3cgsb				= %le \n", &here->BSIM3cgsb); CHECK(1);
ret=fscanf(logfile,"     *   double BSIM3cbgb				= %le \n", &here->BSIM3cbgb); CHECK(1);
ret=fscanf(logfile,"     *   double BSIM3cbdb				= %le \n", &here->BSIM3cbdb); CHECK(1);
ret=fscanf(logfile,"     *   double BSIM3cbsb				= %le \n", &here->BSIM3cbsb); CHECK(1);
ret=fscanf(logfile,"     *   double BSIM3cdgb				= %le \n", &here->BSIM3cdgb); CHECK(1);
ret=fscanf(logfile,"     *   double BSIM3cddb				= %le \n", &here->BSIM3cddb); CHECK(1);
ret=fscanf(logfile,"     *   double BSIM3cdsb				= %le \n", &here->BSIM3cdsb); CHECK(1);
ret=fscanf(logfile,"     *   double BSIM3capbd				= %le \n", &here->BSIM3capbd); CHECK(1);
ret=fscanf(logfile,"     *   double BSIM3capbs				= %le \n", &here->BSIM3capbs); CHECK(1);

ret=fscanf(logfile,"     *   double BSIM3cqgb				= %le \n", &here->BSIM3cqgb); CHECK(1);
ret=fscanf(logfile,"     *   double BSIM3cqdb				= %le \n", &here->BSIM3cqdb); CHECK(1);
ret=fscanf(logfile,"     *   double BSIM3cqsb				= %le \n", &here->BSIM3cqsb); CHECK(1);
ret=fscanf(logfile,"     *   double BSIM3cqbb				= %le \n", &here->BSIM3cqbb); CHECK(1);

ret=fscanf(logfile,"     +   double BSIM3qgate				= %le \n", &here->BSIM3qgate); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3qbulk				= %le \n", &here->BSIM3qbulk); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3qdrn				= %le \n", &here->BSIM3qdrn); CHECK(1);

ret=fscanf(logfile,"     *   double BSIM3gtau				= %le \n", &here->BSIM3gtau); CHECK(1);
ret=fscanf(logfile,"     *   double BSIM3gtg				= %le \n", &here->BSIM3gtg); CHECK(1);
ret=fscanf(logfile,"     *   double BSIM3gtd				= %le \n", &here->BSIM3gtd); CHECK(1);
ret=fscanf(logfile,"     *   double BSIM3gts				= %le \n", &here->BSIM3gts); CHECK(1);
ret=fscanf(logfile,"     *   double BSIM3gtb				= %le \n", &here->BSIM3gtb); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3rds				= %le \n", &here->BSIM3rds); CHECK(1);                                                                // Noise bugfix 
ret=fscanf(logfile,"     +   double BSIM3Vgsteff			= %le \n", &here->BSIM3Vgsteff); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3Vdseff			= %le \n", &here->BSIM3Vdseff); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3Abulk				= %le \n", &here->BSIM3Abulk); CHECK(1);
ret=fscanf(logfile,"     +   double BSIM3AbovVgst2Vtm		= %le \n", &here->BSIM3AbovVgst2Vtm); CHECK(1);
ret=fscanf(logfile,"     *   double BSIM3taunet			= %le \n", &here->BSIM3taunet); CHECK(1);

//ret=fscanf(logfile,"     +! struct bsim3SizeDependParam  *pParam   = %X \n",&dummy); CHECK(1);
/*
    unsigned BSIM3lGiven :1;
    unsigned BSIM3wGiven :1;
    unsigned BSIM3drainAreaGiven :1;
    unsigned BSIM3sourceAreaGiven    :1;
    unsigned BSIM3drainSquaresGiven  :1;
    unsigned BSIM3sourceSquaresGiven :1;
    unsigned BSIM3drainPerimeterGiven    :1;
    unsigned BSIM3sourcePerimeterGiven   :1;
    unsigned BSIM3dNodePrimeSet  :1;
    unsigned BSIM3sNodePrimeSet  :1;
    unsigned BSIM3icVBSGiven :1;
    unsigned BSIM3icVDSGiven :1;
    unsigned BSIM3icVGSGiven :1;
    unsigned BSIM3nqsModGiven :1;
    unsigned BSIM3acnqsModGiven :1;
*/

ret=fscanf(logfile,"     +   double *BSIM3DdPtr = %le \n",here->BSIM3DdPtr);  CHECK(1);
ret=fscanf(logfile,"     +   double *BSIM3GgPtr = %le \n",here->BSIM3GgPtr);  CHECK(1);
ret=fscanf(logfile,"     +   double *BSIM3SsPtr = %le \n",here->BSIM3SsPtr);  CHECK(1);
ret=fscanf(logfile,"     +   double *BSIM3BbPtr = %le \n",here->BSIM3BbPtr);  CHECK(1);
ret=fscanf(logfile,"     +   double *BSIM3DPdpPtr = %le \n",here->BSIM3DPdpPtr);  CHECK(1);
ret=fscanf(logfile,"     *   double *BSIM3SPspPtr = %le \n",here->BSIM3SPspPtr);  CHECK(1);
ret=fscanf(logfile,"     *   double *BSIM3DdpPtr = %le \n",here->BSIM3DdpPtr);  CHECK(1);
ret=fscanf(logfile,"     *   double *BSIM3GbPtr = %le \n",here->BSIM3GbPtr);  CHECK(1);
ret=fscanf(logfile,"     *   double *BSIM3GdpPtr = %le \n",here->BSIM3GdpPtr);  CHECK(1);
ret=fscanf(logfile,"     *   double *BSIM3GspPtr = %le \n",here->BSIM3GspPtr);  CHECK(1);
ret=fscanf(logfile,"     *   double *BSIM3SspPtr = %le \n",here->BSIM3SspPtr);  CHECK(1);
ret=fscanf(logfile,"     *   double *BSIM3BdpPtr = %le \n",here->BSIM3BdpPtr);  CHECK(1);
ret=fscanf(logfile,"     *   double *BSIM3BspPtr = %le \n",here->BSIM3BspPtr);  CHECK(1);
ret=fscanf(logfile,"     *   double *BSIM3DPspPtr = %le \n",here->BSIM3DPspPtr);  CHECK(1);
ret=fscanf(logfile,"     *   double *BSIM3DPdPtr = %le \n",here->BSIM3DPdPtr);  CHECK(1);
ret=fscanf(logfile,"     *   double *BSIM3BgPtr = %le \n",here->BSIM3BgPtr);  CHECK(1);
ret=fscanf(logfile,"     *   double *BSIM3DPgPtr = %le \n",here->BSIM3DPgPtr);  CHECK(1);
ret=fscanf(logfile,"     *   double *BSIM3SPgPtr = %le \n",here->BSIM3SPgPtr);  CHECK(1);
ret=fscanf(logfile,"     *   double *BSIM3SPsPtr = %le \n",here->BSIM3SPsPtr);  CHECK(1);
ret=fscanf(logfile,"     *   double *BSIM3DPbPtr = %le \n",here->BSIM3DPbPtr);  CHECK(1);
ret=fscanf(logfile,"     *   double *BSIM3SPbPtr = %le \n",here->BSIM3SPbPtr);  CHECK(1);
ret=fscanf(logfile,"     *   double *BSIM3SPdpPtr = %le \n",here->BSIM3SPdpPtr);  CHECK(1);

ret=fscanf(logfile,"     *   double *BSIM3QqPtr = %le \n",here->BSIM3QqPtr);  CHECK(1);
ret=fscanf(logfile,"     *   double *BSIM3QdpPtr = %le \n",here->BSIM3QdpPtr);  CHECK(1);
ret=fscanf(logfile,"     *   double *BSIM3QgPtr = %le \n",here->BSIM3QgPtr);  CHECK(1);
ret=fscanf(logfile,"     *   double *BSIM3QspPtr = %le \n",here->BSIM3QspPtr);  CHECK(1);
ret=fscanf(logfile,"     *   double *BSIM3QbPtr = %le \n",here->BSIM3QbPtr);  CHECK(1);
ret=fscanf(logfile,"     *   double *BSIM3DPqPtr = %le \n",here->BSIM3DPqPtr);  CHECK(1);
ret=fscanf(logfile,"     *   double *BSIM3GqPtr = %le \n",here->BSIM3GqPtr);  CHECK(1);
ret=fscanf(logfile,"     *   double *BSIM3SPqPtr = %le \n",here->BSIM3SPqPtr);  CHECK(1);
ret=fscanf(logfile,"     *   double *BSIM3BqPtr = %le \n",here->BSIM3BqPtr);  CHECK(1);
        
ret=fscanf(logfile,"  = end instance \n"); CHECK(0);  

/*------------------------------------------------------------------------*/        
        pParam=here->pParam;

        ret=fscanf(logfile,"  = pParam \n");                    CHECK(0);  
//        ret=fscanf(logfile," pParam address = %X\n", &dummy);   CHECK(1);
         // store/restore all
        ret=fscanf(logfile," double Width			    = %le \n", &pParam->Width); CHECK(1);           
        ret=fscanf(logfile," double Length			    = %le \n", &pParam->Length); CHECK(1);

        ret=fscanf(logfile," double BSIM3cdsc			= %le \n", &pParam->BSIM3cdsc); CHECK(1);           
        ret=fscanf(logfile," double BSIM3cdscb			= %le \n", &pParam->BSIM3cdscb); CHECK(1);    
        ret=fscanf(logfile," double BSIM3cdscd			= %le \n", &pParam->BSIM3cdscd); CHECK(1);       
        ret=fscanf(logfile," double BSIM3cit			= %le \n", &pParam->BSIM3cit); CHECK(1);           
        ret=fscanf(logfile," double BSIM3nfactor		= %le \n", &pParam->BSIM3nfactor); CHECK(1);      
        ret=fscanf(logfile," double BSIM3xj			= %le \n", &pParam->BSIM3xj); CHECK(1);
        ret=fscanf(logfile," double BSIM3vsat			= %le \n", &pParam->BSIM3vsat); CHECK(1);         
        ret=fscanf(logfile," double BSIM3at			= %le \n", &pParam->BSIM3at); CHECK(1);         
        ret=fscanf(logfile," double BSIM3a0			= %le \n", &pParam->BSIM3a0); CHECK(1);   
        ret=fscanf(logfile," double BSIM3ags			= %le \n", &pParam->BSIM3ags); CHECK(1);      
        ret=fscanf(logfile," double BSIM3a1			= %le \n", &pParam->BSIM3a1); CHECK(1);         
        ret=fscanf(logfile," double BSIM3a2			= %le \n", &pParam->BSIM3a2); CHECK(1);         
        ret=fscanf(logfile," double BSIM3keta			= %le \n", &pParam->BSIM3keta); CHECK(1);     
        ret=fscanf(logfile," double BSIM3nsub			= %le \n", &pParam->BSIM3nsub); CHECK(1);
        ret=fscanf(logfile," double BSIM3npeak			= %le \n", &pParam->BSIM3npeak); CHECK(1);        
        ret=fscanf(logfile," double BSIM3ngate			= %le \n", &pParam->BSIM3ngate); CHECK(1);        
        ret=fscanf(logfile," double BSIM3gamma1		= %le \n", &pParam->BSIM3gamma1); CHECK(1);      
        ret=fscanf(logfile," double BSIM3gamma2		= %le \n", &pParam->BSIM3gamma2); CHECK(1);     
        ret=fscanf(logfile," double BSIM3vbx			= %le \n", &pParam->BSIM3vbx); CHECK(1);      
        ret=fscanf(logfile," double BSIM3vbi			= %le \n", &pParam->BSIM3vbi); CHECK(1);       
        ret=fscanf(logfile," double BSIM3vbm			= %le \n", &pParam->BSIM3vbm); CHECK(1);       
        ret=fscanf(logfile," double BSIM3vbsc			= %le \n", &pParam->BSIM3vbsc); CHECK(1);       
        ret=fscanf(logfile," double BSIM3xt			= %le \n", &pParam->BSIM3xt); CHECK(1);       
        ret=fscanf(logfile," double BSIM3phi			= %le \n", &pParam->BSIM3phi); CHECK(1);
        ret=fscanf(logfile," double BSIM3litl			= %le \n", &pParam->BSIM3litl); CHECK(1);
        ret=fscanf(logfile," double BSIM3k1			= %le \n", &pParam->BSIM3k1); CHECK(1);
        ret=fscanf(logfile," double BSIM3kt1			= %le \n", &pParam->BSIM3kt1); CHECK(1);
        ret=fscanf(logfile," double BSIM3kt1l			= %le \n", &pParam->BSIM3kt1l); CHECK(1);
        ret=fscanf(logfile," double BSIM3kt2			= %le \n", &pParam->BSIM3kt2); CHECK(1);
        ret=fscanf(logfile," double BSIM3k2			= %le \n", &pParam->BSIM3k2); CHECK(1);
        ret=fscanf(logfile," double BSIM3k3			= %le \n", &pParam->BSIM3k3); CHECK(1);
        ret=fscanf(logfile," double BSIM3k3b			= %le \n", &pParam->BSIM3k3b); CHECK(1);
        ret=fscanf(logfile," double BSIM3w0			= %le \n", &pParam->BSIM3w0); CHECK(1);
        ret=fscanf(logfile," double BSIM3nlx			= %le \n", &pParam->BSIM3nlx); CHECK(1);
        ret=fscanf(logfile," double BSIM3dvt0			= %le \n", &pParam->BSIM3dvt0); CHECK(1);      
        ret=fscanf(logfile," double BSIM3dvt1			= %le \n", &pParam->BSIM3dvt1); CHECK(1);      
        ret=fscanf(logfile," double BSIM3dvt2			= %le \n", &pParam->BSIM3dvt2); CHECK(1);      
        ret=fscanf(logfile," double BSIM3dvt0w			= %le \n", &pParam->BSIM3dvt0w); CHECK(1);      
        ret=fscanf(logfile," double BSIM3dvt1w			= %le \n", &pParam->BSIM3dvt1w); CHECK(1);      
        ret=fscanf(logfile," double BSIM3dvt2w			= %le \n", &pParam->BSIM3dvt2w); CHECK(1);      
        ret=fscanf(logfile," double BSIM3drout			= %le \n", &pParam->BSIM3drout); CHECK(1);      
        ret=fscanf(logfile," double BSIM3dsub			= %le \n", &pParam->BSIM3dsub); CHECK(1);      
        ret=fscanf(logfile," double BSIM3vth0			= %le \n", &pParam->BSIM3vth0); CHECK(1);
        ret=fscanf(logfile," double BSIM3ua			= %le \n", &pParam->BSIM3ua); CHECK(1);
        ret=fscanf(logfile," double BSIM3ua1			= %le \n", &pParam->BSIM3ua1); CHECK(1);
        ret=fscanf(logfile," double BSIM3ub			= %le \n", &pParam->BSIM3ub); CHECK(1);
        ret=fscanf(logfile," double BSIM3ub1			= %le \n", &pParam->BSIM3ub1); CHECK(1);
        ret=fscanf(logfile," double BSIM3uc			= %le \n", &pParam->BSIM3uc); CHECK(1);
        ret=fscanf(logfile," double BSIM3uc1			= %le \n", &pParam->BSIM3uc1); CHECK(1);
        ret=fscanf(logfile," double BSIM3u0			= %le \n", &pParam->BSIM3u0); CHECK(1);
        ret=fscanf(logfile," double BSIM3ute			= %le \n", &pParam->BSIM3ute); CHECK(1);
        ret=fscanf(logfile," double BSIM3voff			= %le \n", &pParam->BSIM3voff); CHECK(1);
        ret=fscanf(logfile," double BSIM3vfb			= %le \n", &pParam->BSIM3vfb); CHECK(1);
        ret=fscanf(logfile," double BSIM3delta			= %le \n", &pParam->BSIM3delta); CHECK(1);
        ret=fscanf(logfile," double BSIM3rdsw			= %le \n", &pParam->BSIM3rdsw); CHECK(1);       
        ret=fscanf(logfile," double BSIM3rds0			= %le \n", &pParam->BSIM3rds0); CHECK(1);       
        ret=fscanf(logfile," double BSIM3prwg			= %le \n", &pParam->BSIM3prwg); CHECK(1);       
        ret=fscanf(logfile," double BSIM3prwb			= %le \n", &pParam->BSIM3prwb); CHECK(1);       
        ret=fscanf(logfile," double BSIM3prt			= %le \n", &pParam->BSIM3prt); CHECK(1);       
        ret=fscanf(logfile," double BSIM3eta0			= %le \n", &pParam->BSIM3eta0); CHECK(1);         
        ret=fscanf(logfile," double BSIM3etab			= %le \n", &pParam->BSIM3etab); CHECK(1);         
        ret=fscanf(logfile," double BSIM3pclm			= %le \n", &pParam->BSIM3pclm); CHECK(1);      
        ret=fscanf(logfile," double BSIM3pdibl1		= %le \n", &pParam->BSIM3pdibl1); CHECK(1);      
        ret=fscanf(logfile," double BSIM3pdibl2		= %le \n", &pParam->BSIM3pdibl2); CHECK(1);      
        ret=fscanf(logfile," double BSIM3pdiblb		= %le \n", &pParam->BSIM3pdiblb); CHECK(1);      
        ret=fscanf(logfile," double BSIM3pscbe1		= %le \n", &pParam->BSIM3pscbe1); CHECK(1);       
        ret=fscanf(logfile," double BSIM3pscbe2		= %le \n", &pParam->BSIM3pscbe2); CHECK(1);       
        ret=fscanf(logfile," double BSIM3pvag			= %le \n", &pParam->BSIM3pvag); CHECK(1);       
        ret=fscanf(logfile," double BSIM3wr			= %le \n", &pParam->BSIM3wr); CHECK(1);
        ret=fscanf(logfile," double BSIM3dwg			= %le \n", &pParam->BSIM3dwg); CHECK(1);
        ret=fscanf(logfile," double BSIM3dwb			= %le \n", &pParam->BSIM3dwb); CHECK(1);
        ret=fscanf(logfile," double BSIM3b0			= %le \n", &pParam->BSIM3b0); CHECK(1);
        ret=fscanf(logfile," double BSIM3b1			= %le \n", &pParam->BSIM3b1); CHECK(1);
        ret=fscanf(logfile," double BSIM3alpha0		= %le \n", &pParam->BSIM3alpha0); CHECK(1);
        ret=fscanf(logfile," double BSIM3alpha1		= %le \n", &pParam->BSIM3alpha1); CHECK(1);
        ret=fscanf(logfile," double BSIM3beta0			= %le \n", &pParam->BSIM3beta0); CHECK(1);

    //  ret=fscanf(logfile," CV model                       
        ret=fscanf(logfile," double BSIM3elm			= %le \n", &pParam->BSIM3elm); CHECK(1);
        ret=fscanf(logfile," double BSIM3cgsl			= %le \n", &pParam->BSIM3cgsl); CHECK(1);
        ret=fscanf(logfile," double BSIM3cgdl			= %le \n", &pParam->BSIM3cgdl); CHECK(1);
        ret=fscanf(logfile," double BSIM3ckappa		= %le \n", &pParam->BSIM3ckappa); CHECK(1);
        ret=fscanf(logfile," double BSIM3cf			= %le \n", &pParam->BSIM3cf); CHECK(1);
        ret=fscanf(logfile," double BSIM3clc			= %le \n", &pParam->BSIM3clc); CHECK(1);
        ret=fscanf(logfile," double BSIM3cle			= %le \n", &pParam->BSIM3cle); CHECK(1);
        ret=fscanf(logfile," double BSIM3vfbcv			= %le \n", &pParam->BSIM3vfbcv); CHECK(1);
        ret=fscanf(logfile," double BSIM3noff			= %le \n", &pParam->BSIM3noff); CHECK(1);
        ret=fscanf(logfile," double BSIM3voffcv		= %le \n", &pParam->BSIM3voffcv); CHECK(1);
        ret=fscanf(logfile," double BSIM3acde			= %le \n", &pParam->BSIM3acde); CHECK(1);
        ret=fscanf(logfile," double BSIM3moin			= %le \n", &pParam->BSIM3moin); CHECK(1);

    //  ret=fscanf(logfile," Pre-calculated constants        

        ret=fscanf(logfile," double BSIM3dw			= %le \n", &pParam->BSIM3dw); CHECK(1);
        ret=fscanf(logfile," double BSIM3dl			= %le \n", &pParam->BSIM3dl); CHECK(1);
        ret=fscanf(logfile," double BSIM3leff			= %le \n", &pParam->BSIM3leff); CHECK(1);
        ret=fscanf(logfile," double BSIM3weff			= %le \n", &pParam->BSIM3weff); CHECK(1);

        ret=fscanf(logfile," double BSIM3dwc			= %le \n", &pParam->BSIM3dwc); CHECK(1);
        ret=fscanf(logfile," double BSIM3dlc			= %le \n", &pParam->BSIM3dlc); CHECK(1);
        ret=fscanf(logfile," double BSIM3leffCV		= %le \n", &pParam->BSIM3leffCV); CHECK(1);
        ret=fscanf(logfile," double BSIM3weffCV		= %le \n", &pParam->BSIM3weffCV); CHECK(1);
        ret=fscanf(logfile," double BSIM3abulkCVfactor	= %le \n", &pParam->BSIM3abulkCVfactor); CHECK(1);
        ret=fscanf(logfile," double BSIM3cgso			= %le \n", &pParam->BSIM3cgso); CHECK(1);
        ret=fscanf(logfile," double BSIM3cgdo			= %le \n", &pParam->BSIM3cgdo); CHECK(1);
        ret=fscanf(logfile," double BSIM3cgbo			= %le \n", &pParam->BSIM3cgbo); CHECK(1);
        ret=fscanf(logfile," double BSIM3tconst		= %le \n", &pParam->BSIM3tconst); CHECK(1);

        ret=fscanf(logfile," double BSIM3u0temp		= %le \n", &pParam->BSIM3u0temp); CHECK(1);       
        ret=fscanf(logfile," double BSIM3vsattemp		= %le \n", &pParam->BSIM3vsattemp); CHECK(1);   
        ret=fscanf(logfile," double BSIM3sqrtPhi		= %le \n", &pParam->BSIM3sqrtPhi); CHECK(1);   
        ret=fscanf(logfile," double BSIM3phis3			= %le \n", &pParam->BSIM3phis3); CHECK(1);   
        ret=fscanf(logfile," double BSIM3Xdep0			= %le \n", &pParam->BSIM3Xdep0); CHECK(1);          
        ret=fscanf(logfile," double BSIM3sqrtXdep0		= %le \n", &pParam->BSIM3sqrtXdep0); CHECK(1);          
        ret=fscanf(logfile," double BSIM3theta0vb0		= %le \n", &pParam->BSIM3theta0vb0); CHECK(1);
        ret=fscanf(logfile," double BSIM3thetaRout		= %le \n", &pParam->BSIM3thetaRout); CHECK(1); 

        ret=fscanf(logfile," double BSIM3cof1			= %le \n", &pParam->BSIM3cof1); CHECK(1);
        ret=fscanf(logfile," double BSIM3cof2			= %le \n", &pParam->BSIM3cof2); CHECK(1);
        ret=fscanf(logfile," double BSIM3cof3			= %le \n", &pParam->BSIM3cof3); CHECK(1);
        ret=fscanf(logfile," double BSIM3cof4			= %le \n", &pParam->BSIM3cof4); CHECK(1);
        ret=fscanf(logfile," double BSIM3cdep0			= %le \n", &pParam->BSIM3cdep0); CHECK(1);
        ret=fscanf(logfile," double BSIM3vfbzb			= %le \n", &pParam->BSIM3vfbzb); CHECK(1);
        ret=fscanf(logfile," double BSIM3ldeb			= %le \n", &pParam->BSIM3ldeb); CHECK(1);
        ret=fscanf(logfile," double BSIM3k1ox			= %le \n", &pParam->BSIM3k1ox); CHECK(1);
        ret=fscanf(logfile," double BSIM3k2ox			= %le \n", &pParam->BSIM3k2ox); CHECK(1);

//        ret=fscanf(logfile," struct bsim3SizeDependParam = %X \n", &pParam->pNext ); CHECK(1);  
        
        ret=fscanf(logfile,"  = end pParam \n");    CHECK(0);

   }
   
ret=fscanf(logfile,"  === end instances\n");        CHECK(0);  

return 1;

}


/*------------------------------------------------------------------------------------*/
// #define "bsim3def.h"
// typedef struct sBSIM3model {...} BSIM3model;


int read_BSIM3model(FILE * logfile, BSIM3model *model){

int ret;
char msg1[25], msg2[25];
int dummy;
int verbose=0;
char sdummy[25];

// //printf("read_BSIM3model: model                      = %X\n", model);
ret=fscanf(logfile,"  == run no %i %s %s : model \n", &dummy, msg1, msg2);    CHECK(3); // printf("$$$ %i, %s %s \n",dummy, msg1, msg2 );

read_instances(logfile, model);
// //printf("read_BSIM3model after read_instances: model = %X\n", model);

ret=fscanf(logfile,"        int BSIM3modType                   = %i \n",&model->BSIM3modType); CHECK(1);

//ret=fscanf(logfile,"        struct sBSIM3model *BSIM3nextModel = %X \n",&dummy); CHECK(1);
//ret=fscanf(logfile,"        BSIM3instance *BSIM3instances      = %X \n",&dummy); CHECK(1);          // here
ret=fscanf(logfile,"        IFuid BSIM3modName                 = %s  \n",sdummy); CHECK(1); 
ret=fscanf(logfile,"    +   int BSIM3type                  = %i \n",&model->BSIM3type); CHECK(1);
ret=fscanf(logfile,"    +   int    BSIM3mobMod             = %i \n",&model->BSIM3mobMod); CHECK(1);
ret=fscanf(logfile,"    +   int    BSIM3capMod             = %i \n",&model->BSIM3capMod); CHECK(1);
ret=fscanf(logfile,"        int    BSIM3noiMod             = %i \n",&model->BSIM3noiMod); CHECK(1);
ret=fscanf(logfile,"        int    BSIM3acnqsMod		    = %i \n",&model->BSIM3acnqsMod); CHECK(1);
ret=fscanf(logfile,"        int    BSIM3binUnit		    = %i \n",&model->BSIM3binUnit); CHECK(1);
ret=fscanf(logfile,"        int    BSIM3paramChk			= %i \n",&model->BSIM3paramChk); CHECK(1);
ret=fscanf(logfile,"        char   *BSIM3version ? 	    = %c \n",&model->BSIM3version); CHECK(1);             
ret=fscanf(logfile,"    +   double BSIM3tox			    = %le \n",&model->BSIM3tox); CHECK(1);             
ret=fscanf(logfile,"        double BSIM3toxm			    = %le \n",&model->BSIM3toxm); CHECK(1);
ret=fscanf(logfile,"        double BSIM3cdsc 	    		= %le \n", &model->BSIM3cdsc); CHECK(1);           
ret=fscanf(logfile,"        double BSIM3cdscb		    	= %le \n", &model->BSIM3cdscb); CHECK(1); 
ret=fscanf(logfile,"        double BSIM3cdscd		    	= %le \n", &model->BSIM3cdscd); CHECK(1);          
ret=fscanf(logfile,"        double BSIM3cit		    	= %le \n", &model->BSIM3cit); CHECK(1);           
ret=fscanf(logfile,"        double BSIM3nfactor			= %le \n", &model->BSIM3nfactor); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3xj			        = %le \n", &model->BSIM3xj); CHECK(1);
ret=fscanf(logfile,"        double BSIM3vsat		    	= %le \n", &model->BSIM3vsat); CHECK(1);         
ret=fscanf(logfile,"        double BSIM3at			        = %le \n", &model->BSIM3at); CHECK(1);         
ret=fscanf(logfile,"        double BSIM3a0		          	= %le \n", &model->BSIM3a0); CHECK(1);   
ret=fscanf(logfile,"        double BSIM3ags	       		= %le \n", &model->BSIM3ags); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3a1			        = %le \n", &model->BSIM3a1); CHECK(1);         
ret=fscanf(logfile,"        double BSIM3a2		        	= %le \n", &model->BSIM3a2); CHECK(1);         
ret=fscanf(logfile,"        double BSIM3keta			    = %le \n", &model->BSIM3keta); CHECK(1);     
ret=fscanf(logfile,"        double BSIM3nsub		    	= %le \n", &model->BSIM3nsub); CHECK(1);
ret=fscanf(logfile,"        double BSIM3npeak	    		= %le \n", &model->BSIM3npeak); CHECK(1);        
ret=fscanf(logfile,"        double BSIM3ngate		    	= %le \n", &model->BSIM3ngate); CHECK(1);        
ret=fscanf(logfile,"        double BSIM3gamma1			    = %le \n", &model->BSIM3gamma1); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3gamma2	    		= %le \n", &model->BSIM3gamma2); CHECK(1);     
ret=fscanf(logfile,"        double BSIM3vbx		    	= %le \n", &model->BSIM3vbx); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3vbm			    = %le \n", &model->BSIM3vbm); CHECK(1);       
ret=fscanf(logfile,"        double BSIM3xt	        		= %le \n", &model->BSIM3xt); CHECK(1);       
ret=fscanf(logfile,"        double BSIM3k1			        = %le \n", &model->BSIM3k1); CHECK(1);
ret=fscanf(logfile,"        double BSIM3kt1	    		= %le \n", &model->BSIM3kt1); CHECK(1);
ret=fscanf(logfile,"        double BSIM3kt1l		    	= %le \n", &model->BSIM3kt1l); CHECK(1);
ret=fscanf(logfile,"        double BSIM3kt2			    = %le \n", &model->BSIM3kt2); CHECK(1);
ret=fscanf(logfile,"        double BSIM3k2	    	    	= %le \n", &model->BSIM3k2); CHECK(1);
ret=fscanf(logfile,"        double BSIM3k3		    	    = %le \n", &model->BSIM3k3); CHECK(1);
ret=fscanf(logfile,"        double BSIM3k3b			    = %le \n", &model->BSIM3k3b); CHECK(1);
ret=fscanf(logfile,"        double BSIM3w0	    	    	= %le \n", &model->BSIM3w0); CHECK(1);
ret=fscanf(logfile,"        double BSIM3nlx	    		= %le \n", &model->BSIM3nlx); CHECK(1);
ret=fscanf(logfile,"        double BSIM3dvt0			    = %le \n", &model->BSIM3dvt0); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3dvt1   			= %le \n", &model->BSIM3dvt1); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3dvt2	    		= %le \n", &model->BSIM3dvt2); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3dvt0w		    	= %le \n", &model->BSIM3dvt0w); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3dvt1w			    = %le \n", &model->BSIM3dvt1w); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3dvt2w	    		= %le \n", &model->BSIM3dvt2w); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3drout		    	= %le \n", &model->BSIM3drout); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3dsub			    = %le \n", &model->BSIM3dsub); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3vth0		    	= %le \n", &model->BSIM3vth0); CHECK(1);
ret=fscanf(logfile,"        double BSIM3ua		           	= %le \n", &model->BSIM3ua); CHECK(1);
ret=fscanf(logfile,"        double BSIM3ua1	    		= %le \n", &model->BSIM3ua1); CHECK(1);
ret=fscanf(logfile,"        double BSIM3ub		        	= %le \n", &model->BSIM3ub); CHECK(1);
ret=fscanf(logfile,"        double BSIM3ub1	    		= %le \n", &model->BSIM3ub1); CHECK(1);
ret=fscanf(logfile,"        double BSIM3uc		        	= %le \n", &model->BSIM3uc); CHECK(1);
ret=fscanf(logfile,"        double BSIM3uc1	    		= %le \n", &model->BSIM3uc1); CHECK(1);
ret=fscanf(logfile,"        double BSIM3u0		        	= %le \n", &model->BSIM3u0); CHECK(1);
ret=fscanf(logfile,"        double BSIM3ute			= %le \n", &model->BSIM3ute); CHECK(1);
ret=fscanf(logfile,"        double BSIM3voff			= %le \n", &model->BSIM3voff); CHECK(1);
ret=fscanf(logfile,"        double BSIM3delta			= %le \n", &model->BSIM3delta); CHECK(1);
ret=fscanf(logfile,"        double BSIM3rdsw			= %le \n", &model->BSIM3rdsw); CHECK(1);       
ret=fscanf(logfile,"        double BSIM3prwg			= %le \n", &model->BSIM3prwg); CHECK(1);
ret=fscanf(logfile,"        double BSIM3prwb			= %le \n", &model->BSIM3prwb); CHECK(1);
ret=fscanf(logfile,"        double BSIM3prt			= %le \n", &model->BSIM3prt); CHECK(1);       
ret=fscanf(logfile,"        double BSIM3eta0			= %le \n", &model->BSIM3eta0); CHECK(1);         
ret=fscanf(logfile,"        double BSIM3etab			= %le \n", &model->BSIM3etab); CHECK(1);         
ret=fscanf(logfile,"        double BSIM3pclm			= %le \n", &model->BSIM3pclm); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3pdibl1			= %le \n", &model->BSIM3pdibl1); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3pdibl2			= %le \n", &model->BSIM3pdibl2); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3pdiblb			= %le \n", &model->BSIM3pdiblb); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pscbe1			= %le \n", &model->BSIM3pscbe1); CHECK(1);       
ret=fscanf(logfile,"        double BSIM3pscbe2			= %le \n", &model->BSIM3pscbe2); CHECK(1);       
ret=fscanf(logfile,"        double BSIM3pvag			= %le \n", &model->BSIM3pvag); CHECK(1);       
ret=fscanf(logfile,"        double BSIM3wr	    		= %le \n", &model->BSIM3wr); CHECK(1);
ret=fscanf(logfile,"        double BSIM3dwg			= %le \n", &model->BSIM3dwg); CHECK(1);
ret=fscanf(logfile,"        double BSIM3dwb			= %le \n", &model->BSIM3dwb); CHECK(1);
ret=fscanf(logfile,"        double BSIM3b0		    	= %le \n", &model->BSIM3b0); CHECK(1);
ret=fscanf(logfile,"        double BSIM3b1			    = %le \n", &model->BSIM3b1); CHECK(1);
ret=fscanf(logfile,"        double BSIM3alpha0			= %le \n", &model->BSIM3alpha0); CHECK(1);
ret=fscanf(logfile,"        double BSIM3alpha1			= %le \n", &model->BSIM3alpha1); CHECK(1);
ret=fscanf(logfile,"        double BSIM3beta0			= %le \n", &model->BSIM3beta0); CHECK(1);
ret=fscanf(logfile,"    +   double BSIM3ijth			= %le \n", &model->BSIM3ijth); CHECK(1);
ret=fscanf(logfile,"        double BSIM3vfb			= %le \n", &model->BSIM3vfb); CHECK(1);

ret=fscanf(logfile,"        double BSIM3elm			= %le \n", &model->BSIM3elm); CHECK(1);
ret=fscanf(logfile,"        double BSIM3cgsl			= %le \n", &model->BSIM3cgsl); CHECK(1);
ret=fscanf(logfile,"        double BSIM3cgdl			= %le \n", &model->BSIM3cgdl); CHECK(1);
ret=fscanf(logfile,"        double BSIM3ckappa			= %le \n", &model->BSIM3ckappa); CHECK(1);
ret=fscanf(logfile,"        double BSIM3cf			    = %le \n", &model->BSIM3cf); CHECK(1);
ret=fscanf(logfile,"        double BSIM3vfbcv			= %le \n", &model->BSIM3vfbcv); CHECK(1);
ret=fscanf(logfile,"        double BSIM3clc			= %le \n", &model->BSIM3clc); CHECK(1);
ret=fscanf(logfile,"        double BSIM3cle			= %le \n", &model->BSIM3cle); CHECK(1);
ret=fscanf(logfile,"        double BSIM3dwc			= %le \n", &model->BSIM3dwc); CHECK(1);
ret=fscanf(logfile,"        double BSIM3dlc			= %le \n", &model->BSIM3dlc); CHECK(1);
ret=fscanf(logfile,"        double BSIM3noff			= %le \n", &model->BSIM3noff); CHECK(1);
ret=fscanf(logfile,"        double BSIM3voffcv			= %le \n", &model->BSIM3voffcv); CHECK(1);
ret=fscanf(logfile,"        double BSIM3acde			= %le \n", &model->BSIM3acde); CHECK(1);
ret=fscanf(logfile,"        double BSIM3moin			= %le \n", &model->BSIM3moin); CHECK(1);
ret=fscanf(logfile,"        double BSIM3tcj			= %le \n", &model->BSIM3tcj); CHECK(1);
ret=fscanf(logfile,"        double BSIM3tcjsw			= %le \n", &model->BSIM3tcjsw); CHECK(1);
ret=fscanf(logfile,"        double BSIM3tcjswg			= %le \n", &model->BSIM3tcjswg); CHECK(1);
ret=fscanf(logfile,"        double BSIM3tpb			= %le \n", &model->BSIM3tpb); CHECK(1);
ret=fscanf(logfile,"        double BSIM3tpbsw			= %le \n", &model->BSIM3tpbsw); CHECK(1);
ret=fscanf(logfile,"        double BSIM3tpbswg			= %le \n", &model->BSIM3tpbswg); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lcdsc			= %le \n", &model->BSIM3lcdsc); CHECK(1);           
ret=fscanf(logfile,"        double BSIM3lcdscb			= %le \n", &model->BSIM3lcdscb); CHECK(1); 
ret=fscanf(logfile,"        double BSIM3lcdscd			= %le \n", &model->BSIM3lcdscd); CHECK(1);          
ret=fscanf(logfile,"        double BSIM3lcit			= %le \n", &model->BSIM3lcit); CHECK(1);           
ret=fscanf(logfile,"        double BSIM3lnfactor		= %le \n", &model->BSIM3lnfactor); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3lxj			= %le \n", &model->BSIM3lxj); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lvsat			= %le \n", &model->BSIM3lvsat); CHECK(1);         
ret=fscanf(logfile,"        double BSIM3lat			= %le \n", &model->BSIM3lat); CHECK(1);         
ret=fscanf(logfile,"        double BSIM3la0			= %le \n", &model->BSIM3la0); CHECK(1);   
ret=fscanf(logfile,"        double BSIM3lags			= %le \n", &model->BSIM3lags); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3la1			= %le \n", &model->BSIM3la1); CHECK(1);         
ret=fscanf(logfile,"        double BSIM3la2			= %le \n", &model->BSIM3la2); CHECK(1);         
ret=fscanf(logfile,"        double BSIM3lketa			= %le \n", &model->BSIM3lketa); CHECK(1);     
ret=fscanf(logfile,"        double BSIM3lnsub			= %le \n", &model->BSIM3lnsub); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lnpeak			= %le \n", &model->BSIM3lnpeak); CHECK(1);        
ret=fscanf(logfile,"        double BSIM3lngate			= %le \n", &model->BSIM3lngate); CHECK(1);        
ret=fscanf(logfile,"        double BSIM3lgamma1		= %le \n", &model->BSIM3lgamma1); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3lgamma2		= %le \n", &model->BSIM3lgamma2); CHECK(1);     
ret=fscanf(logfile,"        double BSIM3lvbx			= %le \n", &model->BSIM3lvbx); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3lvbm			= %le \n", &model->BSIM3lvbm); CHECK(1);       
ret=fscanf(logfile,"        double BSIM3lxt			= %le \n", &model->BSIM3lxt); CHECK(1);       
ret=fscanf(logfile,"        double BSIM3lk1			= %le \n", &model->BSIM3lk1); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lkt1			= %le \n", &model->BSIM3lkt1); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lkt1l			= %le \n", &model->BSIM3lkt1l); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lkt2			= %le \n", &model->BSIM3lkt2); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lk2			= %le \n", &model->BSIM3lk2); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lk3			= %le \n", &model->BSIM3lk3); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lk3b			= %le \n", &model->BSIM3lk3b); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lw0			= %le \n", &model->BSIM3lw0); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lnlx			= %le \n", &model->BSIM3lnlx); CHECK(1);
ret=fscanf(logfile,"        double BSIM3ldvt0			= %le \n", &model->BSIM3ldvt0); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3ldvt1			= %le \n", &model->BSIM3ldvt1); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3ldvt2			= %le \n", &model->BSIM3ldvt2); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3ldvt0w			= %le \n", &model->BSIM3ldvt0w); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3ldvt1w			= %le \n", &model->BSIM3ldvt1w); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3ldvt2w			= %le \n", &model->BSIM3ldvt2w); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3ldrout			= %le \n", &model->BSIM3ldrout); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3ldsub			= %le \n", &model->BSIM3ldsub); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3lvth0			= %le \n", &model->BSIM3lvth0); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lua			= %le \n", &model->BSIM3lua); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lua1			= %le \n", &model->BSIM3lua1); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lub			= %le \n", &model->BSIM3lub); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lub1			= %le \n", &model->BSIM3lub1); CHECK(1);
ret=fscanf(logfile,"        double BSIM3luc			= %le \n", &model->BSIM3luc); CHECK(1);
ret=fscanf(logfile,"        double BSIM3luc1			= %le \n", &model->BSIM3luc1); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lu0			= %le \n", &model->BSIM3lu0); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lute			= %le \n", &model->BSIM3lute); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lvoff			= %le \n", &model->BSIM3lvoff); CHECK(1);
ret=fscanf(logfile,"        double BSIM3ldelta			= %le \n", &model->BSIM3ldelta); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lrdsw			= %le \n", &model->BSIM3lrdsw); CHECK(1);       
ret=fscanf(logfile,"        double BSIM3lprwg			= %le \n", &model->BSIM3lprwg); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lprwb			= %le \n", &model->BSIM3lprwb); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lprt			= %le \n", &model->BSIM3lprt); CHECK(1);       
ret=fscanf(logfile,"        double BSIM3leta0			= %le \n", &model->BSIM3leta0); CHECK(1);         
ret=fscanf(logfile,"        double BSIM3letab			= %le \n", &model->BSIM3letab); CHECK(1);         
ret=fscanf(logfile,"        double BSIM3lpclm			= %le \n", &model->BSIM3lpclm); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3lpdibl1		= %le \n", &model->BSIM3lpdibl1); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3lpdibl2		= %le \n", &model->BSIM3lpdibl2); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3lpdiblb		= %le \n", &model->BSIM3lpdiblb); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lpscbe1		= %le \n", &model->BSIM3lpscbe1); CHECK(1);       
ret=fscanf(logfile,"        double BSIM3lpscbe2		= %le \n", &model->BSIM3lpscbe2); CHECK(1);       
ret=fscanf(logfile,"        double BSIM3lpvag			= %le \n", &model->BSIM3lpvag); CHECK(1);       
ret=fscanf(logfile,"        double BSIM3lwr			= %le \n", &model->BSIM3lwr); CHECK(1);
ret=fscanf(logfile,"        double BSIM3ldwg			= %le \n", &model->BSIM3ldwg); CHECK(1);
ret=fscanf(logfile,"        double BSIM3ldwb			= %le \n", &model->BSIM3ldwb); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lb0			= %le \n", &model->BSIM3lb0); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lb1			= %le \n", &model->BSIM3lb1); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lalpha0		= %le \n", &model->BSIM3lalpha0); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lalpha1		= %le \n", &model->BSIM3lalpha1); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lbeta0			= %le \n", &model->BSIM3lbeta0); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lvfb			= %le \n", &model->BSIM3lvfb); CHECK(1);

ret=fscanf(logfile,"        double BSIM3lelm			= %le \n", &model->BSIM3lelm); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lcgsl			= %le \n", &model->BSIM3lcgsl); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lcgdl			= %le \n", &model->BSIM3lcgdl); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lckappa		= %le \n", &model->BSIM3lckappa); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lcf			= %le \n", &model->BSIM3lcf); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lclc			= %le \n", &model->BSIM3lclc); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lcle			= %le \n", &model->BSIM3lcle); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lvfbcv			= %le \n", &model->BSIM3lvfbcv); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lnoff			= %le \n", &model->BSIM3lnoff); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lvoffcv		= %le \n", &model->BSIM3lvoffcv); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lacde			= %le \n", &model->BSIM3lacde); CHECK(1);
ret=fscanf(logfile,"        double BSIM3lmoin			= %le \n", &model->BSIM3lmoin); CHECK(1);

// Width Dependence 
ret=fscanf(logfile,"        double BSIM3wcdsc			= %le \n", &model->BSIM3wcdsc); CHECK(1);           
ret=fscanf(logfile,"        double BSIM3wcdscb			= %le \n", &model->BSIM3wcdscb); CHECK(1); 
ret=fscanf(logfile,"        double BSIM3wcdscd			= %le \n", &model->BSIM3wcdscd); CHECK(1);          
ret=fscanf(logfile,"        double BSIM3wcit			= %le \n", &model->BSIM3wcit); CHECK(1);           
ret=fscanf(logfile,"        double BSIM3wnfactor		= %le \n", &model->BSIM3wnfactor); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3wxj			= %le \n", &model->BSIM3wxj); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wvsat			= %le \n", &model->BSIM3wvsat); CHECK(1);         
ret=fscanf(logfile,"        double BSIM3wat			= %le \n", &model->BSIM3wat); CHECK(1);         
ret=fscanf(logfile,"        double BSIM3wa0			= %le \n", &model->BSIM3wa0); CHECK(1);   
ret=fscanf(logfile,"        double BSIM3wags			= %le \n", &model->BSIM3wags); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3wa1			= %le \n", &model->BSIM3wa1); CHECK(1);         
ret=fscanf(logfile,"        double BSIM3wa2			= %le \n", &model->BSIM3wa2); CHECK(1);         
ret=fscanf(logfile,"        double BSIM3wketa			= %le \n", &model->BSIM3wketa); CHECK(1);     
ret=fscanf(logfile,"        double BSIM3wnsub			= %le \n", &model->BSIM3wnsub); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wnpeak			= %le \n", &model->BSIM3wnpeak); CHECK(1);        
ret=fscanf(logfile,"        double BSIM3wngate			= %le \n", &model->BSIM3wngate); CHECK(1);        
ret=fscanf(logfile,"        double BSIM3wgamma1		= %le \n", &model->BSIM3wgamma1); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3wgamma2		= %le \n", &model->BSIM3wgamma2); CHECK(1);     
ret=fscanf(logfile,"        double BSIM3wvbx			= %le \n", &model->BSIM3wvbx); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3wvbm			= %le \n", &model->BSIM3wvbm); CHECK(1);       
ret=fscanf(logfile,"        double BSIM3wxt			= %le \n", &model->BSIM3wxt); CHECK(1);       
ret=fscanf(logfile,"        double BSIM3wk1			= %le \n", &model->BSIM3wk1); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wkt1			= %le \n", &model->BSIM3wkt1); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wkt1l			= %le \n", &model->BSIM3wkt1l); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wkt2			= %le \n", &model->BSIM3wkt2); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wk2			= %le \n", &model->BSIM3wk2); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wk3			= %le \n", &model->BSIM3wk3); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wk3b			= %le \n", &model->BSIM3wk3b); CHECK(1);
ret=fscanf(logfile,"        double BSIM3ww0			= %le \n", &model->BSIM3ww0); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wnlx			= %le \n", &model->BSIM3wnlx); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wdvt0			= %le \n", &model->BSIM3wdvt0); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3wdvt1			= %le \n", &model->BSIM3wdvt1); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3wdvt2			= %le \n", &model->BSIM3wdvt2); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3wdvt0w			= %le \n", &model->BSIM3wdvt0w); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3wdvt1w			= %le \n", &model->BSIM3wdvt1w); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3wdvt2w			= %le \n", &model->BSIM3wdvt2w); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3wdrout			= %le \n", &model->BSIM3wdrout); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3wdsub			= %le \n", &model->BSIM3wdsub); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3wvth0			= %le \n", &model->BSIM3wvth0); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wua			= %le \n", &model->BSIM3wua); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wua1			= %le \n", &model->BSIM3wua1); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wub			= %le \n", &model->BSIM3wub); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wub1			= %le \n", &model->BSIM3wub1); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wuc			= %le \n", &model->BSIM3wuc); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wuc1			= %le \n", &model->BSIM3wuc1); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wu0			= %le \n", &model->BSIM3wu0); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wute			= %le \n", &model->BSIM3wute); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wvoff			= %le \n", &model->BSIM3wvoff); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wdelta			= %le \n", &model->BSIM3wdelta); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wrdsw			= %le \n", &model->BSIM3wrdsw); CHECK(1);       
ret=fscanf(logfile,"        double BSIM3wprwg			= %le \n", &model->BSIM3wprwg); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wprwb			= %le \n", &model->BSIM3wprwb); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wprt			= %le \n", &model->BSIM3wprt); CHECK(1);       
ret=fscanf(logfile,"        double BSIM3weta0			= %le \n", &model->BSIM3weta0); CHECK(1);         
ret=fscanf(logfile,"        double BSIM3wetab			= %le \n", &model->BSIM3wetab); CHECK(1);         
ret=fscanf(logfile,"        double BSIM3wpclm			= %le \n", &model->BSIM3wpclm); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3wpdibl1		= %le \n", &model->BSIM3wpdibl1); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3wpdibl2		= %le \n", &model->BSIM3wpdibl2); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3wpdiblb		= %le \n", &model->BSIM3wpdiblb); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wpscbe1		= %le \n", &model->BSIM3wpscbe1); CHECK(1);       
ret=fscanf(logfile,"        double BSIM3wpscbe2		= %le \n", &model->BSIM3wpscbe2); CHECK(1);       
ret=fscanf(logfile,"        double BSIM3wpvag			= %le \n", &model->BSIM3wpvag); CHECK(1);       
ret=fscanf(logfile,"        double BSIM3wwr			= %le \n", &model->BSIM3wwr); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wdwg			= %le \n", &model->BSIM3wdwg); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wdwb			= %le \n", &model->BSIM3wdwb); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wb0			= %le \n", &model->BSIM3wb0); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wb1			= %le \n", &model->BSIM3wb1); CHECK(1);
ret=fscanf(logfile,"        double BSIM3walpha0		= %le \n", &model->BSIM3walpha0); CHECK(1);
ret=fscanf(logfile,"        double BSIM3walpha1		= %le \n", &model->BSIM3walpha1); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wbeta0			= %le \n", &model->BSIM3wbeta0); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wvfb			= %le \n", &model->BSIM3wvfb); CHECK(1);

// CV model 
ret=fscanf(logfile,"        double BSIM3welm			= %le \n", &model->BSIM3welm); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wcgsl			= %le \n", &model->BSIM3wcgsl); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wcgdl			= %le \n", &model->BSIM3wcgdl); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wckappa		= %le \n", &model->BSIM3wckappa); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wcf			= %le \n", &model->BSIM3wcf); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wclc			= %le \n", &model->BSIM3wclc); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wcle			= %le \n", &model->BSIM3wcle); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wvfbcv			= %le \n", &model->BSIM3wvfbcv); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wnoff			= %le \n", &model->BSIM3wnoff); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wvoffcv		= %le \n", &model->BSIM3wvoffcv); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wacde			= %le \n", &model->BSIM3wacde); CHECK(1);
ret=fscanf(logfile,"        double BSIM3wmoin			= %le \n", &model->BSIM3wmoin); CHECK(1);

// Cross-term Dependence 
ret=fscanf(logfile,"        double BSIM3pcdsc			= %le \n", &model->BSIM3pcdsc); CHECK(1);           
ret=fscanf(logfile,"        double BSIM3pcdscb			= %le \n", &model->BSIM3pcdscb); CHECK(1); 
ret=fscanf(logfile,"        double BSIM3pcdscd			= %le \n", &model->BSIM3pcdscd); CHECK(1);          
ret=fscanf(logfile,"        double BSIM3pcit			= %le \n", &model->BSIM3pcit); CHECK(1);           
ret=fscanf(logfile,"        double BSIM3pnfactor		= %le \n", &model->BSIM3pnfactor); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3pxj			= %le \n", &model->BSIM3pxj); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pvsat			= %le \n", &model->BSIM3pvsat); CHECK(1);         
ret=fscanf(logfile,"        double BSIM3pat			= %le \n", &model->BSIM3pat); CHECK(1);         
ret=fscanf(logfile,"        double BSIM3pa0			= %le \n", &model->BSIM3pa0); CHECK(1);   
ret=fscanf(logfile,"        double BSIM3pags			= %le \n", &model->BSIM3pags); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3pa1			= %le \n", &model->BSIM3pa1); CHECK(1);         
ret=fscanf(logfile,"        double BSIM3pa2			= %le \n", &model->BSIM3pa2); CHECK(1);         
ret=fscanf(logfile,"        double BSIM3pketa			= %le \n", &model->BSIM3pketa); CHECK(1);     
ret=fscanf(logfile,"        double BSIM3pnsub			= %le \n", &model->BSIM3pnsub); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pnpeak			= %le \n", &model->BSIM3pnpeak); CHECK(1);        
ret=fscanf(logfile,"        double BSIM3pngate			= %le \n", &model->BSIM3pngate); CHECK(1);        
ret=fscanf(logfile,"        double BSIM3pgamma1		= %le \n", &model->BSIM3pgamma1); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3pgamma2		= %le \n", &model->BSIM3pgamma2); CHECK(1);     
ret=fscanf(logfile,"        double BSIM3pvbx			= %le \n", &model->BSIM3pvbx); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3pvbm			= %le \n", &model->BSIM3pvbm); CHECK(1);       
ret=fscanf(logfile,"        double BSIM3pxt			= %le \n", &model->BSIM3pxt); CHECK(1);       
ret=fscanf(logfile,"        double BSIM3pk1			= %le \n", &model->BSIM3pk1); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pkt1			= %le \n", &model->BSIM3pkt1); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pkt1l			= %le \n", &model->BSIM3pkt1l); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pkt2			= %le \n", &model->BSIM3pkt2); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pk2			= %le \n", &model->BSIM3pk2); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pk3			= %le \n", &model->BSIM3pk3); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pk3b			= %le \n", &model->BSIM3pk3b); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pw0			= %le \n", &model->BSIM3pw0); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pnlx			= %le \n", &model->BSIM3pnlx); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pdvt0			= %le \n", &model->BSIM3pdvt0); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3pdvt1			= %le \n", &model->BSIM3pdvt1); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3pdvt2			= %le \n", &model->BSIM3pdvt2); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3pdvt0w			= %le \n", &model->BSIM3pdvt0w); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3pdvt1w			= %le \n", &model->BSIM3pdvt1w); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3pdvt2w			= %le \n", &model->BSIM3pdvt2w); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3pdrout			= %le \n", &model->BSIM3pdrout); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3pdsub			= %le \n", &model->BSIM3pdsub); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3pvth0			= %le \n", &model->BSIM3pvth0); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pua			= %le \n", &model->BSIM3pua); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pua1			= %le \n", &model->BSIM3pua1); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pub			= %le \n", &model->BSIM3pub); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pub1			= %le \n", &model->BSIM3pub1); CHECK(1);
ret=fscanf(logfile,"        double BSIM3puc			= %le \n", &model->BSIM3puc); CHECK(1);
ret=fscanf(logfile,"        double BSIM3puc1			= %le \n", &model->BSIM3puc1); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pu0			= %le \n", &model->BSIM3pu0); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pute			= %le \n", &model->BSIM3pute); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pvoff			= %le \n", &model->BSIM3pvoff); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pdelta			= %le \n", &model->BSIM3pdelta); CHECK(1);
ret=fscanf(logfile,"        double BSIM3prdsw			= %le \n", &model->BSIM3prdsw); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pprwg			= %le \n", &model->BSIM3pprwg); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pprwb			= %le \n", &model->BSIM3pprwb); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pprt			= %le \n", &model->BSIM3pprt); CHECK(1);       
ret=fscanf(logfile,"        double BSIM3peta0			= %le \n", &model->BSIM3peta0); CHECK(1);         
ret=fscanf(logfile,"        double BSIM3petab			= %le \n", &model->BSIM3petab); CHECK(1);         
ret=fscanf(logfile,"        double BSIM3ppclm			= %le \n", &model->BSIM3ppclm); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3ppdibl1		= %le \n", &model->BSIM3ppdibl1); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3ppdibl2		= %le \n", &model->BSIM3ppdibl2); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3ppdiblb		= %le \n", &model->BSIM3ppdiblb); CHECK(1);
ret=fscanf(logfile,"        double BSIM3ppscbe1		= %le \n", &model->BSIM3ppscbe1); CHECK(1);       
ret=fscanf(logfile,"        double BSIM3ppscbe2		= %le \n", &model->BSIM3ppscbe2); CHECK(1);       
ret=fscanf(logfile,"        double BSIM3ppvag			= %le \n", &model->BSIM3ppvag); CHECK(1);       
ret=fscanf(logfile,"        double BSIM3pwr			= %le \n", &model->BSIM3pwr); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pdwg			= %le \n", &model->BSIM3pdwg); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pdwb			= %le \n", &model->BSIM3pdwb); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pb0			= %le \n", &model->BSIM3pb0); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pb1		    = %le \n", &model->BSIM3pb1); CHECK(1);
ret=fscanf(logfile,"        double BSIM3palpha0		= %le \n", &model->BSIM3palpha0); CHECK(1);
ret=fscanf(logfile,"        double BSIM3palpha1		= %le \n", &model->BSIM3palpha1); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pbeta0			= %le \n", &model->BSIM3pbeta0); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pvfb			= %le \n", &model->BSIM3pvfb); CHECK(1);

            //CV model 
ret=fscanf(logfile,"        double BSIM3pelm			= %le \n", &model->BSIM3pelm); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pcgsl			= %le \n", &model->BSIM3pcgsl); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pcgdl			= %le \n", &model->BSIM3pcgdl); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pckappa		= %le \n", &model->BSIM3pckappa); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pcf			= %le \n", &model->BSIM3pcf); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pclc			= %le \n", &model->BSIM3pclc); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pcle			= %le \n", &model->BSIM3pcle); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pvfbcv			= %le \n", &model->BSIM3pvfbcv); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pnoff			= %le \n", &model->BSIM3pnoff); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pvoffcv		= %le \n", &model->BSIM3pvoffcv); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pacde			= %le \n", &model->BSIM3pacde); CHECK(1);
ret=fscanf(logfile,"        double BSIM3pmoin			= %le \n", &model->BSIM3pmoin); CHECK(1);

ret=fscanf(logfile,"    +   double BSIM3tnom			= %le \n", &model->BSIM3tnom); CHECK(1);
ret=fscanf(logfile,"        double BSIM3cgso			= %le \n", &model->BSIM3cgso); CHECK(1);
ret=fscanf(logfile,"        double BSIM3cgdo			= %le \n", &model->BSIM3cgdo); CHECK(1);
ret=fscanf(logfile,"        double BSIM3cgbo			= %le \n", &model->BSIM3cgbo); CHECK(1);
ret=fscanf(logfile,"    +   double BSIM3xpart			= %le \n", &model->BSIM3xpart); CHECK(1);
ret=fscanf(logfile,"        double BSIM3cFringOut		= %le \n", &model->BSIM3cFringOut); CHECK(1);
ret=fscanf(logfile,"        double BSIM3cFringMax		= %le \n", &model->BSIM3cFringMax); CHECK(1);

ret=fscanf(logfile,"        double BSIM3sheetResistance			    = %le \n", &model->BSIM3sheetResistance); CHECK(1);
ret=fscanf(logfile,"        double BSIM3jctSatCurDensity			    = %le \n", &model->BSIM3jctSatCurDensity); CHECK(1);
ret=fscanf(logfile,"        double BSIM3jctSidewallSatCurDensity		= %le \n", &model->BSIM3jctSidewallSatCurDensity); CHECK(1);
ret=fscanf(logfile,"        double BSIM3bulkJctPotential			    = %le \n", &model->BSIM3bulkJctPotential); CHECK(1);
ret=fscanf(logfile,"    +   double BSIM3bulkJctBotGradingCoeff		    = %le \n", &model->BSIM3bulkJctBotGradingCoeff); CHECK(1);
ret=fscanf(logfile,"    +   double BSIM3bulkJctSideGradingCoeff		= %le \n", &model->BSIM3bulkJctSideGradingCoeff); CHECK(1);
ret=fscanf(logfile,"    +   double BSIM3bulkJctGateSideGradingCoeff	= %le \n", &model->BSIM3bulkJctGateSideGradingCoeff); CHECK(1);
ret=fscanf(logfile,"        double BSIM3sidewallJctPotential			= %le \n", &model->BSIM3sidewallJctPotential); CHECK(1);
ret=fscanf(logfile,"        double BSIM3GatesidewallJctPotential		= %le \n", &model->BSIM3GatesidewallJctPotential); CHECK(1);
ret=fscanf(logfile,"        double BSIM3unitAreaJctCap			        = %le \n", &model->BSIM3unitAreaJctCap); CHECK(1);
ret=fscanf(logfile,"        double BSIM3unitLengthSidewallJctCap		= %le \n", &model->BSIM3unitLengthSidewallJctCap); CHECK(1);
ret=fscanf(logfile,"        double BSIM3unitLengthGateSidewallJctCap	= %le \n", &model->BSIM3unitLengthGateSidewallJctCap); CHECK(1);
ret=fscanf(logfile,"    +   double BSIM3jctEmissionCoeff			    = %le \n", &model->BSIM3jctEmissionCoeff); CHECK(1);
ret=fscanf(logfile,"        double BSIM3jctTempExponent			    = %le \n", &model->BSIM3jctTempExponent); CHECK(1);

ret=fscanf(logfile,"        double BSIM3Lint			= %le \n", &model->BSIM3Lint); CHECK(1);
ret=fscanf(logfile,"        double BSIM3Ll			    = %le \n", &model->BSIM3Ll); CHECK(1);
ret=fscanf(logfile,"        double BSIM3Llc			= %le \n", &model->BSIM3Llc); CHECK(1);
ret=fscanf(logfile,"        double BSIM3Lln			= %le \n", &model->BSIM3Lln); CHECK(1);
ret=fscanf(logfile,"        double BSIM3Lw			    = %le \n", &model->BSIM3Lw); CHECK(1);
ret=fscanf(logfile,"        double BSIM3Lwc			= %le \n", &model->BSIM3Lwc); CHECK(1);
ret=fscanf(logfile,"        double BSIM3Lwn			= %le \n", &model->BSIM3Lwn); CHECK(1);
ret=fscanf(logfile,"        double BSIM3Lwl			= %le \n", &model->BSIM3Lwl); CHECK(1);
ret=fscanf(logfile,"        double BSIM3Lwlc			= %le \n", &model->BSIM3Lwlc); CHECK(1);
ret=fscanf(logfile,"        double BSIM3Lmin			= %le \n", &model->BSIM3Lmin); CHECK(1);
ret=fscanf(logfile,"        double BSIM3Lmax			= %le \n", &model->BSIM3Lmax); CHECK(1);


ret=fscanf(logfile,"        double BSIM3Wint			= %le \n", &model->BSIM3Wint); CHECK(1);
ret=fscanf(logfile,"        double BSIM3Wl			    = %le \n", &model->BSIM3Wl); CHECK(1);
ret=fscanf(logfile,"        double BSIM3Wlc			= %le \n", &model->BSIM3Wlc); CHECK(1);
ret=fscanf(logfile,"        double BSIM3Wln			= %le \n", &model->BSIM3Wln); CHECK(1);
ret=fscanf(logfile,"        double BSIM3Ww			    = %le \n", &model->BSIM3Ww); CHECK(1);
ret=fscanf(logfile,"        double BSIM3Wwc			= %le \n", &model->BSIM3Wwc); CHECK(1);
ret=fscanf(logfile,"        double BSIM3Wwn			= %le \n", &model->BSIM3Wwn); CHECK(1);
ret=fscanf(logfile,"        double BSIM3Wwl			= %le \n", &model->BSIM3Wwl); CHECK(1);
ret=fscanf(logfile,"        double BSIM3Wwlc			= %le \n", &model->BSIM3Wwlc); CHECK(1);
ret=fscanf(logfile,"        double BSIM3Wmin			= %le \n", &model->BSIM3Wmin); CHECK(1);
ret=fscanf(logfile,"        double BSIM3Wmax			= %le \n", &model->BSIM3Wmax); CHECK(1);

                  // Pre-calculated constants 
                  // MCJ: move to size-dependent param. 
ret=fscanf(logfile,"    +   double BSIM3vtm			= %le \n", &model->BSIM3vtm); CHECK(1);   
ret=fscanf(logfile,"    +   double BSIM3cox			= %le \n", &model->BSIM3cox); CHECK(1);
ret=fscanf(logfile,"        double BSIM3cof1			= %le \n", &model->BSIM3cof1); CHECK(1);
ret=fscanf(logfile,"        double BSIM3cof2			= %le \n", &model->BSIM3cof2); CHECK(1);
ret=fscanf(logfile,"        double BSIM3cof3			= %le \n", &model->BSIM3cof3); CHECK(1);
ret=fscanf(logfile,"        double BSIM3cof4			= %le \n", &model->BSIM3cof4); CHECK(1);
ret=fscanf(logfile,"    +   double BSIM3vcrit			= %le \n", &model->BSIM3vcrit); CHECK(1);
ret=fscanf(logfile,"    +   double BSIM3factor1			= %le \n", &model->BSIM3factor1); CHECK(1);
ret=fscanf(logfile,"    +   double BSIM3PhiB			= %le \n", &model->BSIM3PhiB); CHECK(1);
ret=fscanf(logfile,"    +   double BSIM3PhiBSW		    = %le \n", &model->BSIM3PhiBSW); CHECK(1);
ret=fscanf(logfile,"    +   double BSIM3PhiBSWG		= %le \n", &model->BSIM3PhiBSWG); CHECK(1);
ret=fscanf(logfile,"    +   double BSIM3jctTempSatCurDensity			    = %le \n", &model->BSIM3jctTempSatCurDensity); CHECK(1);
ret=fscanf(logfile,"    +   double BSIM3jctSidewallTempSatCurDensity		= %le \n", &model->BSIM3jctSidewallTempSatCurDensity); CHECK(1);
ret=fscanf(logfile,"    +   double BSIM3unitAreaTempJctCap			        = %le \n", &model->BSIM3unitAreaTempJctCap); CHECK(1);
ret=fscanf(logfile,"    +   double BSIM3unitLengthSidewallTempJctCap		= %le \n", &model->BSIM3unitLengthSidewallTempJctCap); CHECK(1);
ret=fscanf(logfile,"    +   double BSIM3unitLengthGateSidewallTempJctCap	= %le \n", &model->BSIM3unitLengthGateSidewallTempJctCap); CHECK(1);

ret=fscanf(logfile,"        double BSIM3oxideTrapDensityA			        = %le \n", &model->BSIM3oxideTrapDensityA); CHECK(1);      
ret=fscanf(logfile,"        double BSIM3oxideTrapDensityB			        = %le \n", &model->BSIM3oxideTrapDensityB); CHECK(1);     
ret=fscanf(logfile,"        double BSIM3oxideTrapDensityC			        = %le \n", &model->BSIM3oxideTrapDensityC); CHECK(1);  
ret=fscanf(logfile,"        double BSIM3em			    = %le \n", &model->BSIM3em); CHECK(1);  
ret=fscanf(logfile,"        double BSIM3ef			    = %le \n", &model->BSIM3ef); CHECK(1);  
ret=fscanf(logfile,"        double BSIM3af			    = %le \n", &model->BSIM3af); CHECK(1);  
ret=fscanf(logfile,"        double BSIM3kf		    	= %le \n", &model->BSIM3kf); CHECK(1);  
ret=fscanf(logfile,"        double BSIM3lintnoi		= %le \n", &model->BSIM3lintnoi); CHECK(1);  // lint offset for noise calculation  lation  

//ret=fscanf(logfile,"        struct bsim3SizeDependParam *pSizeDependParamKnot = %X \n", &model->pSizeDependParamKnot); CHECK(1);
//??
ret=fscanf(logfile,"  == model end \n");   CHECK(0); 
return 1;
}
