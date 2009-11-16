// $Id$
// test for BSIM3 (BSIM3load) function 
//
//
// this test reads from 
// ./serial_objects/inlogfile.piece.txt and 
// then it calls BSIM3load

// input files 
// ./inlogfile.piece.txt and 

// spice includes
extern "C" {
  #define _complex CompleX
  #define NODE NodE
  #define public PubliC
  #define bool BooL
  #define main MaiN
  #include "capabil.h"
  #include "const.h"
  #include "iferrmsg.h"
  #include "devdefs.h"
  #include "ftedefs.h"
  #include "optdefs.h"
  #undef main
  #undef bool
  #undef public
  #undef NODE
  #undef _complex

  #undef eq
  #undef OPT
  #undef LINEAR
  #undef STRING
  #undef BOOLEAN
  
  #undef VT_BOOL
  #undef VT_NUM
  #undef VT_REAL
  #undef VT_STRING
  #undef VT_LIST

#include "cktdefs.h"
#include "bsim3def.h"

}

extern "C" {
    int BSIM3load( GENmodel *inModel, CKTcircuit *ckt);
}

extern "C" {
    int print_ckt(FILE * logfile, int count, CKTcircuit *ckt, char* msg);
    int read_ckt(FILE * logfile, CKTcircuit *ckt);
    int create_ckt(CKTcircuit **ckt);
    int free_ckt(CKTcircuit **ckt);
    
    int print_BSIM3model(FILE * logfile, int count, BSIM3model *model, char* msg);
    int read_BSIM3model(FILE * logfile, BSIM3model *model);
    int create_BSIM3model (BSIM3model **model);
    int free_BSIM3model (BSIM3model **model);
    int BSIM3_set_lut(BSIM3model *model, int lut);
}

#include <iostream>
#include "l_timer.h"


int main (int argc, char* arrgv[] ) {


CKTcircuit *ckt;
BSIM3model  *model;

/*
this example ensures, that model is correctly detached from the SPICE.
as far as input data are reproduced correctly, results coinside with SPICE.

this is sinokes test:
1. read ckt
2. set lut=0,1,2
3. BSIM3load 10000 times

*/


create_ckt(&ckt);

FILE * cktfile= fopen("./inlogfile.txt","r");
if (cktfile !=0) {
    int ret=read_ckt(cktfile, ckt);
    }

FILE * ckt_echo_file= fopen("./inlogfile.echo","w");
if (ckt_echo_file !=0) {
     int ret= print_ckt (ckt_echo_file, 1, ckt, "echo ckt");
    }

 
create_BSIM3model(&model);

//model_spice:

FILE *modelin= cktfile;
if (modelin !=0) {
    int ret=read_BSIM3model(modelin, model);
    }

FILE * model_echo= ckt_echo_file;
if (model_echo !=0 ) {
     int ret= print_BSIM3model (model_echo, 1, model, "echo model");
    }

BSIM3_set_lut(model,2);

// timer 1
TIMER timer1;
int N=1000000;

timer1.start();
for (int i=0; i<N; i++){
    BSIM3load( (GENmodel*)model, ckt);
    }
// timer 2
timer1.stop();
std::cout<<" "<<timer1.elapsed()<<std::endl;
free_ckt(&ckt);
free_BSIM3model(&model);
return 1;
}

