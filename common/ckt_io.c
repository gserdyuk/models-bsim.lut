#include <stdlib.h>
#include "spice.h"
#include <stdio.h>
#include "cktdefs.h"
#include "bsim3def.h"

// include "cktdefs.h"
//typedef struct {...} CKTcircuit;
int print_ckt(FILE * logfile, int count, CKTcircuit *ckt, char* msg);
int read_ckt(FILE * logfile, CKTcircuit *ckt);
int create_ckt(CKTcircuit **ckt);
int free_ckt(CKTcircuit **ckt);
/*-  print_ckt --------------------------------------------------------------------------------------------*/
int print_ckt(FILE * logfile, int count, CKTcircuit *ckt, char* msg){

int i;

fprintf(logfile,"  === run no %i %s \n", count, msg);  
//fprintf(logfile, "      GENmodel *CKThead[MAXNUMDEVS]   = 0 = %X \n", 0);         
//fprintf(logfile, "      STATistics *CKTstat     = 0 = %X \n", 0 );    
//fprintf(logfile, " +012! CKTstates  (rw)         = %lX %lX %lX %lX %lX %lX %lX \n",   
//            ckt->CKTstates[0], ckt->CKTstates[1], ckt->CKTstates[2], ckt->CKTstates[3],
//            ckt->CKTstates[4], ckt->CKTstates[5], ckt->CKTstates[6], ckt->CKTstates[7]);
fprintf(logfile, " BSIM3numStates (not struct)   = %i\n",BSIM3numStates);

for (i=0; i<BSIM3numStates; i++)
    fprintf(logfile, "          CKTstates[0][%i](rw) = %e \n",i, (ckt->CKTstates[0])[i]); 
for (i=0; i<BSIM3numStates; i++)
    fprintf(logfile, "          CKTstates[1][%i](rw) = %e \n",i, (ckt->CKTstates[1])[i]); 
for (i=0; i<BSIM3numStates; i++)
    fprintf(logfile, "          CKTstates[2][%i](rw) = %e \n",i, (ckt->CKTstates[2])[i]); 

                                                                        
fprintf(logfile, "      double CKTtime          = %g \n", ckt->CKTtime);
fprintf(logfile, " +    double CKTdelta         = %g \n",ckt->CKTdelta);
fprintf(logfile, " +1   double CKTdeltaOld[7]  = %e %e %e %e %e %e %e \n",
            ckt->CKTdeltaOld[0], ckt->CKTdeltaOld[1], ckt->CKTdeltaOld[2], ckt->CKTdeltaOld[3], 
            ckt->CKTdeltaOld[4], ckt->CKTdeltaOld[5], ckt->CKTdeltaOld[6], ckt->CKTdeltaOld[7]);
                                                                     
fprintf(logfile, " +    double CKTtemp          = %g \n",ckt->CKTtemp); 
fprintf(logfile, "      double CKTnomTemp       = %g \n",ckt->CKTnomTemp);  
fprintf(logfile, "      double CKTvt            = %g \n",ckt->CKTvt);       

fprintf(logfile, " +0   double CKTag[7]         = %g %g %g %g %g %g %g \n",
            ckt->CKTag[0],  ckt->CKTag[1],  ckt->CKTag[2],  ckt->CKTag[3],  
            ckt->CKTag[4],  ckt->CKTag[5], ckt->CKTag[6]);

fprintf(logfile, "      double CKTagp[7]        = %g %g %g %g %g %g %g \n",
            ckt->CKTagp[0], ckt->CKTagp[1], ckt->CKTagp[2], ckt->CKTagp[3], 
            ckt->CKTagp[4], ckt->CKTagp[7], ckt->CKTagp[6]); 

fprintf(logfile, "      int CKTorder            = %i \n",ckt->CKTorder);    
fprintf(logfile, "      int CKTmaxOrder         = %i \n",ckt->CKTmaxOrder);  

fprintf(logfile, "      int CKTintegrateMethod  = %i \n",ckt->CKTintegrateMethod);
//fprintf(logfile, "    ! SMPmatrix *CKTmatrix    = %lX \n",ckt->CKTmatrix);
fprintf(logfile, "      int CKTniState          = %i \n",ckt->CKTniState);

//fprintf(logfile, "      double *CKTrhs  (rw)    = %X \n",ckt->CKTrhs);

for (i=0; i<BSIM3numStates; i++)
    fprintf(logfile, "          CKTrhs[%i]   (rw)    = %e \n",i, (ckt->CKTrhs)[i]);

//fprintf(logfile, " +    double *CKTrhsOld       = %X \n",ckt->CKTrhsOld);

for (i=0; i<BSIM3numStates; i++)
    fprintf(logfile, "          CKTrhsOld[%i](rw)    = %e \n",i, (ckt->CKTrhsOld)[i]); 
    
//fprintf(logfile, "      double *CKTrhsSpare     = %X \n",ckt->CKTrhsSpare);      // may not be alloctaed
//fprintf(logfile, "      double *CKTirhs         = %X \n ",ckt->CKTirhs);   
//fprintf(logfile, "      double *CKTirhsOld      = %lX \n ",ckt->CKTirhsOld);     // may not be alloctaed
//fprintf(logfile, "      double *CKTirhsSpare    = %lX\n",ckt->CKTirhsSpare);     // may not be alloctaed
//fprintf(logfile, "    ! double *CKTpred         = %lX \n",ckt->CKTpred);     

//fprintf(logfile, "    ! double *CKTsols[8]      = %lX %lX %lX %lX %lX %lX %lX %lX \n",
//                ckt->CKTsols[0], ckt->CKTsols[1], ckt->CKTsols[2], ckt->CKTsols[3], 
//                ckt->CKTsols[4], ckt->CKTsols[5], ckt->CKTsols[6], ckt->CKTsols[7]);  

//fprintf(logfile, "    ! double *CKTrhsOp        = %lX \n", ckt->CKTrhsOp);
//fprintf(logfile, "      double *CKTsenRhs       = 0 = %lX \n", ckt->CKTsenRhs);
//fprintf(logfile, "      double *CKTseniRhs      = 0 = %lX \n", ckt->CKTseniRhs);
fprintf(logfile, "      int CKTmaxEqNum         = %i \n", ckt->CKTmaxEqNum);
fprintf(logfile, "      int CKTcurrentAnalysis  = %i \n", ckt->CKTcurrentAnalysis);
//fprintf(logfile, "    ! CKTnode *CKTnodes       = 0 = %lX\n", ckt->CKTnodes);   
//fprintf(logfile, "    ! CKTnode *CKTlastNode    = 0 = %lX\n", ckt->CKTlastNode);

fprintf(logfile, "      int CKTnumStates        = %i \n",ckt->CKTnumStates);
fprintf(logfile, "      long CKTmode            = %li \n",ckt->CKTmode);
fprintf(logfile, "      int CKTbypass           = %i \n",ckt->CKTbypass);
fprintf(logfile, "      int CKTdcMaxIter        = %i \n",ckt->CKTdcMaxIter);
fprintf(logfile, "      int CKTdcTrcvMaxIter    = %i \n",ckt->CKTdcTrcvMaxIter  );
fprintf(logfile, "      int CKTtranMaxIter      = %i \n",ckt->CKTtranMaxIter    );
fprintf(logfile, "      int CKTbreakSize        = %i \n",ckt->CKTbreakSize  );
fprintf(logfile, "      int CKTbreak            = %i \n",ckt->CKTbreak      );
fprintf(logfile, "      double CKTsaveDelta     = %e \n",ckt->CKTsaveDelta   );
fprintf(logfile, "      double CKTminBreak      = %e \n",ckt->CKTminBreak    );
//fprintf(logfile, "    ! double *CKTbreaks       = %lX \n",ckt->CKTbreaks      );
fprintf(logfile, " +    double CKTabstol        = %e \n",ckt->CKTabstol      );
fprintf(logfile, "      double CKTpivotAbsTol   = %e \n",ckt->CKTpivotAbsTol );
fprintf(logfile, "      double CKTpivotRelTol   = %e \n",ckt->CKTpivotRelTol );
fprintf(logfile, " +    double CKTreltol        = %e \n",ckt->CKTreltol      );
fprintf(logfile, "      double CKTchgtol        = %e \n",ckt->CKTchgtol      );
fprintf(logfile, " +    double CKTvoltTol       = %e \n",ckt->CKTvoltTol     );
fprintf(logfile, " +    double CKTgmin          = %e \n",ckt->CKTgmin        );
fprintf(logfile, "      double CKTdelmin        = %e \n",ckt->CKTdelmin      );
fprintf(logfile, "      double CKTtrtol         = %e \n",ckt->CKTtrtol       );
fprintf(logfile, "      double CKTfinalTime     = %e \n",ckt->CKTfinalTime   );
fprintf(logfile, "      double CKTstep          = %e \n",ckt->CKTstep        );
fprintf(logfile, "      double CKTmaxStep       = %e \n",ckt->CKTmaxStep     );
fprintf(logfile, "      double CKTinitTime      = %e \n",ckt->CKTinitTime    );
fprintf(logfile, "      double CKTomega         = %e \n",ckt->CKTomega       );
fprintf(logfile, "      double CKTsrcFact       = %e \n",ckt->CKTsrcFact     );
fprintf(logfile, "      double CKTdiagGmin      = %e \n",ckt->CKTdiagGmin    );
fprintf(logfile, "      int CKTnumSrcSteps      = %i \n",ckt->CKTnumSrcSteps    );
fprintf(logfile, "      int CKTnumGminSteps     = %i \n",ckt->CKTnumGminSteps   );
fprintf(logfile, " +    int CKTnoncon           = %i \n",ckt->CKTnoncon         );
fprintf(logfile, "      double CKTdefaultMosL   = %e \n",ckt->CKTdefaultMosL );
fprintf(logfile, "      double CKTdefaultMosW   = %e \n",ckt->CKTdefaultMosW );
fprintf(logfile, "      double CKTdefaultMosAD  = %e \n",ckt->CKTdefaultMosAD);
fprintf(logfile, "      double CKTdefaultMosAS  = %e \n",ckt->CKTdefaultMosAS);
fprintf(logfile, "      unsigned int CKThadNodeset:1  = %u \n",ckt->CKThadNodeset);
fprintf(logfile, "      unsigned int CKTfixLimit:1    = %u \n",ckt->CKTfixLimit);
fprintf(logfile, "      unsigned int CKTnoOpIter:1    = %u \n",ckt->CKTnoOpIter);
fprintf(logfile, "      unsigned int CKTisSetup:1     = %u \n",ckt->CKTisSetup);
//fprintf(logfile, "    ! JOB *CKTcurJob        = 0 = %lX \n",ckt->CKTcurJob);
//fprintf(logfile, "      SENstruct *CKTsenInfo = 0 = %lX \n",ckt->CKTsenInfo);
//fprintf(logfile, "    ! double *CKTtimePoints = %lX \n",ckt->CKTtimePoints);
//fprintf(logfile, "    ! double *CKTdeltaList  = %lX \n",ckt->CKTdeltaList);
fprintf(logfile, "      int CKTtimeListSize   = %i \n",ckt->CKTtimeListSize);
fprintf(logfile, "      int CKTtimeIndex      = %i \n",ckt->CKTtimeIndex);
fprintf(logfile, "      int CKTsizeIncr       = %i \n",ckt->CKTsizeIncr);
fprintf(logfile, "      unsigned int CKTtryToCompact:1= %u \n",ckt->CKTtryToCompact);
fprintf(logfile, "      unsigned int CKTbadMos3:1     = %u \n",ckt->CKTbadMos3);
fprintf(logfile, "      unsigned int CKTkeepOpInfo:1  = %u \n",ckt->CKTkeepOpInfo);
fprintf(logfile, "      int CKTtroubleNode    = %i \n",ckt->CKTtroubleNode);
//fprintf(logfile, "    ! GENinstance *CKTtroubleElt  = %lX \n",ckt->CKTtroubleElt);

fprintf(logfile,"  === end ckt\n");  

return 1;
}

/*-------------------------------------------------------------------------------------------------*/

/*- read_ckt --------------------------------------------------------------------------------------*/

int create_ckt(CKTcircuit **ckt){
(*ckt)              =(CKTcircuit*)malloc(sizeof(CKTcircuit));
(*ckt)->CKTstates[0]=(double *) malloc(sizeof(double)*BSIM3numStates);
(*ckt)->CKTstates[1]=(double *)malloc(sizeof(double)*BSIM3numStates);
(*ckt)->CKTstates[2]=(double *)malloc(sizeof(double)*BSIM3numStates);
(*ckt)->CKTstates[3]=(double *)malloc(sizeof(double)*BSIM3numStates);
(*ckt)->CKTstates[4]=(double *)malloc(sizeof(double)*BSIM3numStates);
(*ckt)->CKTstates[5]=(double *)malloc(sizeof(double)*BSIM3numStates);
(*ckt)->CKTstates[6]=(double *)malloc(sizeof(double)*BSIM3numStates);

(*ckt)->CKTrhs      =(double*)malloc(sizeof(double)*BSIM3numStates);
(*ckt)->CKTrhsOld   =(double*)malloc(sizeof(double)*BSIM3numStates);
}

int free_ckt(CKTcircuit **ckt){
free((*ckt)->CKTstates[0]);
free((*ckt)->CKTstates[1]);
free((*ckt)->CKTstates[2]);
free((*ckt)->CKTstates[3]);
free((*ckt)->CKTstates[4]);
free((*ckt)->CKTstates[5]);
free((*ckt)->CKTstates[6]);

free((*ckt)->CKTrhs);
free((*ckt)->CKTrhsOld);
free((*ckt));
}

#define CHECK(n) if (ret != n) printf("alert- input error at line %d , expected: %d, obtained: %d parameters \n",__LINE__, n, ret); \
                 else          if (verbose==1) printf ("ok, at %i read %i values \n",__LINE__,ret);


int read_ckt(FILE * logfile, CKTcircuit *ckt){
int verbose=0;
int i;
int count;
char msg1[256], msg2[256];
int dummy;
unsigned int udummy;
char s1[25], s2[25], s3[25], s4[25], s5[25], s6[25], s7[25];
int ret;
int i_in;

FILE *tmpf;

//1 assume that ckt == NULL. It is not allocated yet at least
/*ckt->CKTstates[0]=(double *) malloc(sizeof(double)*BSIM3numStates);
ckt->CKTstates[1]=(double *)malloc(sizeof(double)*BSIM3numStates);
ckt->CKTstates[2]=(double *)malloc(sizeof(double)*BSIM3numStates);
ckt->CKTstates[3]=(double *)malloc(sizeof(double)*BSIM3numStates);
ckt->CKTstates[4]=(double *)malloc(sizeof(double)*BSIM3numStates);
ckt->CKTstates[5]=(double *)malloc(sizeof(double)*BSIM3numStates);
ckt->CKTstates[6]=(double *)malloc(sizeof(double)*BSIM3numStates);*/

ret=fscanf(logfile,  "  === run no %i %s %s2\n", &count, &msg1, &msg2);             CHECK(3);
//ret=fscanf(logfile, "      GENmodel *CKThead[MAXNUMDEVS]   = 0 = %X \n", &dummy);   CHECK(1);
//ret=fscanf(logfile, "      STATistics *CKTstat     = 0 = %X \n",&dummy );           CHECK(1); 

//ret=fscanf(logfile, " +012! CKTstates  (rw)         = %lX %lX %lX %lX %lX %lX %lX \n", s1, s2, s3, s4, s5, s6, s7  );
ret=fscanf(logfile, " BSIM3numStates (not struct)   = %i\n",&dummy);  // BSIM3numStates

for (i=0; i<BSIM3numStates; i++){
    ret=fscanf(logfile, "          CKTstates[0][%i](rw) = %le \n",&i_in, &(ckt->CKTstates[0])[i]);  CHECK(2); 
    }
for (i=0; i<BSIM3numStates; i++){
    ret=fscanf(logfile, "          CKTstates[1][%i](rw) = %le \n",&i_in, &(ckt->CKTstates[1])[i]);  CHECK(2); 
    }
for (i=0; i<BSIM3numStates; i++){
    ret=fscanf(logfile, "          CKTstates[2][%i](rw) = %le \n",&i_in, &(ckt->CKTstates[2])[i]);  CHECK(2); 
    }
                                                                        
ret=fscanf(logfile, "      double CKTtime          = %le \n", &(ckt->CKTtime));    CHECK(1); 
ret=fscanf(logfile, " +    double CKTdelta         = %le \n",&(ckt->CKTdelta));    CHECK(1); 
ret=fscanf(logfile, " +1   double CKTdeltaOld[7]  = %le %le %le %le %le %le %le \n", 
            &ckt->CKTdeltaOld[0], &ckt->CKTdeltaOld[1], &ckt->CKTdeltaOld[2], &ckt->CKTdeltaOld[3], 
            &ckt->CKTdeltaOld[4], &ckt->CKTdeltaOld[5], &ckt->CKTdeltaOld[6], ckt->CKTdeltaOld[7]); CHECK(7);
ret=fscanf(logfile, " +    double CKTtemp          = %lg \n",&ckt->CKTtemp);     CHECK(1);
ret=fscanf(logfile, "      double CKTnomTemp       = %lg \n",&ckt->CKTnomTemp);  CHECK(1);    
ret=fscanf(logfile, "      double CKTvt            = %lg \n",&ckt->CKTvt);       CHECK(1);
ret=fscanf(logfile, " +0   double CKTag[7]         = %lg %lg %lg %lg %lg %lg %lg \n",
            &ckt->CKTag[0],  &ckt->CKTag[1],  &ckt->CKTag[2],  &ckt->CKTag[3],  &ckt->CKTag[4],  
            &ckt->CKTag[5],  &ckt->CKTag[6]); CHECK(7);
ret=fscanf(logfile, "      double CKTagp[7]        = %lg %lg %lg %lg %lg %lg %lg \n",
            &ckt->CKTagp[0], &ckt->CKTagp[1], &ckt->CKTagp[2], &ckt->CKTagp[3], &ckt->CKTagp[4], 
            &ckt->CKTagp[5], &ckt->CKTagp[6]);CHECK(7); 
ret=fscanf(logfile, "      int CKTorder            = %i \n",&ckt->CKTorder);     CHECK(1);
ret=fscanf(logfile, "      int CKTmaxOrder         = %i \n",&ckt->CKTmaxOrder);  CHECK(1);

ret=fscanf(logfile, "      int CKTintegrateMethod  = %i \n",    &ckt->CKTintegrateMethod);  CHECK(1);
//ret=fscanf(logfile, "    ! SMPmatrix *CKTmatrix    = %lX \n",   &dummy);                    CHECK(1);
ret=fscanf(logfile, "      int CKTniState          = %i \n",    &ckt->CKTniState);          CHECK(1);

//ret=fscanf(logfile, "      double *CKTrhs  (rw)    = %X \n",    &dummy);                    CHECK(1);

/*ckt->CKTrhs=malloc(sizeof(double)*BSIM3numStates);*/

for (i=0; i<BSIM3numStates; i++)
    ret=fscanf(logfile, "          CKTrhs[%i]   (rw)    = %le \n",&dummy, &((ckt->CKTrhs)[i])); CHECK(2);

/*ckt->CKTrhsOld=malloc(sizeof(double)*BSIM3numStates);*/
//ret=fscanf(logfile, " +    double *CKTrhsOld       = %X \n",    &dummy); CHECK(1);
for (i=0; i<BSIM3numStates; i++)
    ret=fscanf(logfile, "          CKTrhsOld[%i](rw)    = %le \n",&dummy, &((ckt->CKTrhsOld)[i])); CHECK(2);
    
//ret=fscanf(logfile, "      double *CKTrhsSpare     = %X \n",    &dummy );               CHECK(1);      // may not be alloctaed
//ret=fscanf(logfile, "      double *CKTirhs         = %X \n ",   &dummy);                CHECK(1);   
//ret=fscanf(logfile, "      double *CKTirhsOld      = %lX \n ",  &dummy);                CHECK(1);      // may not be alloctaed
//ret=fscanf(logfile, "      double *CKTirhsSpare    = %lX\n",    &dummy);                CHECK(1);     // may not be alloctaed
//ret=fscanf(logfile, "    ! double *CKTpred         = %lX \n",   &dummy);                CHECK(1);
//ret=fscanf(logfile, "    ! double *CKTsols[8]      = %lX %lX %lX %lX %lX %lX %lX %lX \n",
//                &ckt->CKTsols[0], &ckt->CKTsols[1], &ckt->CKTsols[2], &ckt->CKTsols[3], &ckt->CKTsols[4], 
//                &ckt->CKTsols[5], &ckt->CKTsols[6], &ckt->CKTsols[7]); CHECK(8);  
//ret=fscanf(logfile, "    ! double *CKTrhsOp        = %lX \n",   &dummy);                CHECK(1);
//ret=fscanf(logfile, "      double *CKTsenRhs       = 0 = %lX \n", &ckt->CKTsenRhs);     CHECK(1);
//ret=fscanf(logfile, "      double *CKTseniRhs      = 0 = %lX \n", &ckt->CKTseniRhs);    CHECK(1);
ret=fscanf(logfile, "      int CKTmaxEqNum         = %i \n",    &ckt->CKTmaxEqNum);     CHECK(1);
ret=fscanf(logfile, "      int CKTcurrentAnalysis  = %i \n",    &ckt->CKTcurrentAnalysis); CHECK(1);
//ret=fscanf(logfile, "    ! CKTnode *CKTnodes       = 0 = %lX\n", &ckt->CKTnodes);       CHECK(1);   
//ret=fscanf(logfile, "    ! CKTnode *CKTlastNode    = 0 = %lX\n", &ckt->CKTlastNode);    CHECK(1);

ret=fscanf(logfile, "      int CKTnumStates        = %i \n",&ckt->CKTnumStates); CHECK(1);
ret=fscanf(logfile, "      long CKTmode            = %li \n",&ckt->CKTmode); CHECK(1);
ret=fscanf(logfile, "      int CKTbypass           = %i \n",&ckt->CKTbypass); CHECK(1);
ret=fscanf(logfile, "      int CKTdcMaxIter        = %i \n",&ckt->CKTdcMaxIter); CHECK(1);
ret=fscanf(logfile, "      int CKTdcTrcvMaxIter    = %i \n",&ckt->CKTdcTrcvMaxIter  ); CHECK(1);
ret=fscanf(logfile, "      int CKTtranMaxIter      = %i \n",&ckt->CKTtranMaxIter    ); CHECK(1);
ret=fscanf(logfile, "      int CKTbreakSize        = %i \n",&ckt->CKTbreakSize  ); CHECK(1);
ret=fscanf(logfile, "      int CKTbreak            = %i \n",&ckt->CKTbreak      ); CHECK(1);
ret=fscanf(logfile, "      double CKTsaveDelta     = %le \n",&ckt->CKTsaveDelta   ); CHECK(1);
ret=fscanf(logfile, "      double CKTminBreak      = %le \n",&ckt->CKTminBreak    ); CHECK(1);
//ret=fscanf(logfile, "    ! double *CKTbreaks       = %lX \n",&ckt->CKTbreaks      ); CHECK(1);
ret=fscanf(logfile, " +    double CKTabstol        = %le \n",&ckt->CKTabstol      ); CHECK(1);
ret=fscanf(logfile, "      double CKTpivotAbsTol   = %le \n",&ckt->CKTpivotAbsTol ); CHECK(1);
ret=fscanf(logfile, "      double CKTpivotRelTol   = %le \n",&ckt->CKTpivotRelTol ); CHECK(1);
ret=fscanf(logfile, " +    double CKTreltol        = %le \n",&ckt->CKTreltol      ); CHECK(1);
ret=fscanf(logfile, "      double CKTchgtol        = %le \n",&ckt->CKTchgtol      ); CHECK(1);
ret=fscanf(logfile, " +    double CKTvoltTol       = %le \n",&ckt->CKTvoltTol     ); CHECK(1);
ret=fscanf(logfile, " +    double CKTgmin          = %le \n",&ckt->CKTgmin        ); CHECK(1);
ret=fscanf(logfile, "      double CKTdelmin        = %le \n",&ckt->CKTdelmin      ); CHECK(1);
ret=fscanf(logfile, "      double CKTtrtol         = %le \n",&ckt->CKTtrtol       ); CHECK(1);
ret=fscanf(logfile, "      double CKTfinalTime     = %le \n",&ckt->CKTfinalTime   ); CHECK(1);
ret=fscanf(logfile, "      double CKTstep          = %le \n",&ckt->CKTstep        ); CHECK(1);
ret=fscanf(logfile, "      double CKTmaxStep       = %le \n",&ckt->CKTmaxStep     ); CHECK(1);
ret=fscanf(logfile, "      double CKTinitTime      = %le \n",&ckt->CKTinitTime    ); CHECK(1);
ret=fscanf(logfile, "      double CKTomega         = %le \n",&ckt->CKTomega       ); CHECK(1);
ret=fscanf(logfile, "      double CKTsrcFact       = %le \n",&ckt->CKTsrcFact     ); CHECK(1);
ret=fscanf(logfile, "      double CKTdiagGmin      = %le \n",&ckt->CKTdiagGmin    ); CHECK(1);
ret=fscanf(logfile, "      int CKTnumSrcSteps      = %i \n",&ckt->CKTnumSrcSteps    ); CHECK(1);
ret=fscanf(logfile, "      int CKTnumGminSteps     = %i \n",&ckt->CKTnumGminSteps   ); CHECK(1);
ret=fscanf(logfile, " +    int CKTnoncon           = %i \n",&ckt->CKTnoncon         ); CHECK(1);
ret=fscanf(logfile, "      double CKTdefaultMosL   = %le \n",&ckt->CKTdefaultMosL ); CHECK(1);
ret=fscanf(logfile, "      double CKTdefaultMosW   = %le \n",&ckt->CKTdefaultMosW ); CHECK(1);
ret=fscanf(logfile, "      double CKTdefaultMosAD  = %le \n",&ckt->CKTdefaultMosAD); CHECK(1);
ret=fscanf(logfile, "      double CKTdefaultMosAS  = %le \n",&ckt->CKTdefaultMosAS); CHECK(1);
ret=fscanf(logfile, "      unsigned int CKThadNodeset:1  = %u \n",&dummy); CHECK(1);
ret=fscanf(logfile, "      unsigned int CKTfixLimit:1    = %u \n",&dummy); CHECK(1);
ret=fscanf(logfile, "      unsigned int CKTnoOpIter:1    = %u \n",&dummy); CHECK(1);
ret=fscanf(logfile, "      unsigned int CKTisSetup:1     = %u \n",&dummy); CHECK(1);
//ret=fscanf(logfile, "    ! JOB *CKTcurJob        = 0 = %lX \n",     &dummy); CHECK(1);
//ret=fscanf(logfile, "      SENstruct *CKTsenInfo = 0 = %lX \n",     &dummy); CHECK(1);
//ret=fscanf(logfile, "    ! double *CKTtimePoints = %lX \n",         &dummy); CHECK(1);
//ret=fscanf(logfile, "    ! double *CKTdeltaList  = %lX \n",         &dummy); CHECK(1);
ret=fscanf(logfile, "      int CKTtimeListSize   = %i \n",&ckt->CKTtimeListSize); CHECK(1);
ret=fscanf(logfile, "      int CKTtimeIndex      = %i \n",&ckt->CKTtimeIndex); CHECK(1);
ret=fscanf(logfile, "      int CKTsizeIncr       = %i \n",&ckt->CKTsizeIncr); CHECK(1);
ret=fscanf(logfile, "      unsigned int CKTtryToCompact:1= %u \n",&dummy); CHECK(1);
ret=fscanf(logfile, "      unsigned int CKTbadMos3:1     = %u \n",&dummy); CHECK(1);
ret=fscanf(logfile, "      unsigned int CKTkeepOpInfo:1  = %u \n",&dummy); CHECK(1);
ret=fscanf(logfile, "      int CKTtroubleNode    = %i \n",  &ckt->CKTtroubleNode); CHECK(1);
//ret=fscanf(logfile, "    ! GENinstance *CKTtroubleElt  = %lX \n",&dummy); CHECK(1);

ret=fscanf(logfile,"  === end ckt\n"); CHECK(0);  

return 1;
}
