/* excerptions from spice-wrapper.cc */

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
}


  //------------------------------------------------
  int NIintegrate(CKTcircuit* ckt,double* geq,double* ceq,double cap,int qcap)
  { //-- used by DEVload (not DC)
/*  
    assert_ckt_localized(ckt);

    METHOD method;
    if (ckt->CKTorder == 1) {
      method = mEULER;
    }else{
      assert(ckt->CKTtimePoints[1] != 0.);
      assert(ckt->CKTorder == 2);
      method = mTRAP;
    }

    std::valarray<FPOLY1> q(OPT::_keep_time_steps);
    std::valarray<FPOLY1> i(OPT::_keep_time_steps);

    for (int ii = 0; ii < OPT::_keep_time_steps; ++ii) {
      assert(ckt->CKTstates[ii]);
      q[ii].x  = NOT_VALID;
      q[ii].f0 = ckt->CKTstates[ii][qcap];
      q[ii].f1 = cap;
      trace3("", ii, q[ii].f0, q[ii].f1);
      i[ii].x  = NOT_VALID;
      i[ii].f0 = ckt->CKTstates[ii][qcap+1];
      i[ii].f1 = q[ii].f1 * ckt->CKTag[0];
      trace3("", ii, i[ii].f0, i[ii].f1);
      assert(q[ii].f0 == q[ii].f0);
      assert(q[ii].f1 == q[ii].f1);
      assert(i[ii].f0 == i[ii].f0);
      assert(i[ii].f1 == i[ii].f1);
    }

    i[0] = differentiate(&q[0], &i[0], ckt->CKTtimePoints, method);
    assert(i[0].f0 == i[0].f0);
    assert(i[0].f1 == i[0].f1);
    trace2("", i[0].f0, i[0].f1);

    ckt->CKTstates[0][qcap+1] = i[0].f0;

    assert(ckt->CKTdelta != 0. || (ckt->CKTag[0] == 0. && i[0].f0 == 0.));
    *ceq = i[0].f0 - q[0].f0 * ckt->CKTag[0];
    *geq = i[0].f1;
    assert(*ceq == *ceq);
    assert(*geq == *geq);
    trace2("", *ceq, *geq);
 */   
    return OK;
  }

  //------------------------------------------------
  // should be constants, but spice wants them to be variables.
  double const P_CELSIUS0	= 273.15;	   // 0 Celsius

  double const P_Q	= 1.6021918e-19;   // charge of an electron, (spice)
  double const P_K	= 1.3806226e-23;   // Boltzmann's constant J/K (spice)
  double const P_K_Q	= P_K/P_Q;

  double CONSTvt0(P_CELSIUS0*P_K_Q);

