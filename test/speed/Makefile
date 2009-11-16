#
# requires gnucap/src at ../../Gnucap
CCC=g++
CC=gcc

GNUCAP=../../Gnucap
BSIM=../../BSIM3v330.lut
SPICE=../../Include
COMMON=../../common


INCLUDE=-I./ -I$(GNUCAP) -I$(BSIM) -I$(SPICE) -I$(COMMON)

C_FLAGS= $(INCLUDE) -g -DPREDICTOR -DNDEBUG 

CC_FLAGS=$(C_FLAGS)

C_FLAGS_O2=$(C_FLAGS) -O2

CC_FLAGS_O2=$(CC_FLAGS) -02

all: timing_test timing_test.lut

timing_test: timing_test.o l_timer.o ckt_io.o model_io.o b3ld.o devsup.o support-functions.o
	$(CCC) $^ -o $@

timing_test.lut: timing_test.lut.o l_timer.o LUT_rr.o ckt_io.o model_io.lut.o b3ld.lut.o devsup.o support-functions.o
	$(CCC) $^ -o $@

timing_test.o: timing_test.cc
	$(CCC) $(CC_FLAGS) -c $< -o $@

timing_test.lut.o: timing_test.cc
	$(CCC) $(CC_FLAGS) -DLUT -c $< -o $@

l_timer.o: l_timer.cc
	$(CCC) $(CC_FLAGS) -c $< -o $@

LUT_rr.o: $(COMMON)/LUT_rr.c
	$(CC) $(C_FLAGS_O2) -c $< -o $@

ckt_io.o: ckt_io.c
	$(CC) $(C_FLAGS) -c $< -o $@

model_io.o: model_io.c
	$(CC) $(C_FLAGS) -c $< -o $@

model_io.lut.o: model_io.c
	$(CC) $(C_FLAGS) -DLUT -c $< -o $@

b3ld.o: $(BSIM)/b3ld.c
	$(CC) $(C_FLAGS_O2) -DHAS_STDLIB -c $< -o $@

b3ld.lut.o: $(BSIM)/b3ld.c
	$(CC) $(C_FLAGS_O2) -DLUT -DHAS_STDLIB -c $< -o $@

devsup.o: $(SPICE)/devsup.c
	$(CC) $(C_FLAGS_O2)  -DHAS_STDLIB -c $< -o $@

support-functions.o: support-functions.cc
	$(CCC) $(CC_FLAGS_O2) -c $< -o $@

b3ld.lut.o: $(COMMON)/LUT_rr.h

b3ld.o:$(COMMON)/LUT_rr.h

clean:
	rm -f *.o

cleanall: clean
	rm -f 20run.out
	rm -f inlogfile.echo
	rm -f timing_test timing_test.lut
	