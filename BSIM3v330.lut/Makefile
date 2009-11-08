# $Id$

SPICE_INCLUDE = ../Include
GNUCAP_INCLUDE= ../../src
LUT_INCLUDE   = ../common

TARGET=bsim330

$(TARGET):

include makedefs

HDRS = bsim3def.h bsim3ext.h bsim3itf.h
#wrapper.h

SPICE_VERSION = SPICE_3f

C_SRCS = $(CFILES) devsup.c ckt_io.c model_io.c 
CC_SRCS = spice-wrapper.cc

VPATH=./:$(SPICE_INCLUDE):$(GNUCAP_INCLUDE)

OBJS       = ${C_SRCS:.c=.o} ${CC_SRCS:.cc=.o} 
OBJS_LUT   = ${OBJS:.o=.lut.o} ../common/LUT_rr.o
HDRS = bsim3def.h bsim3ext.h bsim3itf.h 

CC = gcc
CCC = g++
# -O2
CFLAGS =  -g  -I. -I$(SPICE_INCLUDE) -I$(LUT_INCLUDE) -DTRACE_UNTESTED -D$(SPICE_VERSION) \
 -DPREDICTOR -DHAS_STDLIB -fPIC  

CCFLAGS = $(CFLAGS) -I$(GNUCAP_INCLUDE) -Wall -Wextra 

CFLAGS_LUT= $(CFLAGS) -DLUT -DSERIALIZATION

CCFLAGS_LUT=  $(CCFLAGS) -DLUT -DSERIALIZATION

LDFLAGS = -shared -g

SO_EXTENSION = .so
LUT_SUFFIX   = .lut

%.o: %.cc
		$(CCC) $(CCFLAGS) -c $<
%.o: %.c
		$(CC) $(CFLAGS) -c $<
%.lut.o: %.cc
		$(CCC) $(CCFLAGS_LUT) -c $< -o $@
%.lut.o: %.c
		$(CC) $(CFLAGS_LUT) -c $< -o $@


spice-wrapper.o: spice-wrapper.cc wrapper.h
devsup.o: ../Include/devsup.c

$(TARGET) : $(TARGET)$(SO_EXTENSION)  $(TARGET)$(LUT_SUFFIX)$(SO_EXTENSION)  

	echo $(TARGET) done

$(TARGET)$(SO_EXTENSION) : $(OBJS) Makefile
	$(CCC) $(LDFLAGS) $(OBJS) $(LIBS) -o $(TARGET)$(SO_EXTENSION)

$(TARGET)$(LUT_SUFFIX)$(SO_EXTENSION): $(OBJS_LUT) Makefile
	echo "LUT rule"
	$(CCC) $(LDFLAGS) $(OBJS_LUT) $(LIBS) -o $(TARGET)$(LUT_SUFFIX)$(SO_EXTENSION)

$(OBJS): $(HDRS)

$(OBJS_LUT): $(HDRS) ../common/LUT_rr.h

../common/LUT_rr.o: ../common/LUT_rr.c  ../common/LUT_rr.h
		$(CC) $(CFLAGS) -c $< -o $@


clean: 
	rm *.so
	rm *.o
	rm ../common/*.o

list:
	echo OBJS = $(OBJS)
	echo OBJS_LUT = $(OBJS_LUT)
    