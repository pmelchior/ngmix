CC=g++

prefix := /usr/local

extra_ldflags :=

CFLAGS = -I. -Wall -O2
#LDFLAGS = -lm -static
LDFLAGS = -lm $(extra_ldflags)

TEST_GMIX = test/test-gmix
TEST_GMIX_MODEL = test/test-gmix-model
TEST_FASTEXP = test/test-fastexp
TEST_FASTEXP_SPEED = test/test-fastexp-speed
TEST_IMAGE = test/test-image
TEST_SHAPE = test/test-shape
TEST_MCA = test/test-mca

ALLTESTS = $(TEST_GMIX) $(TEST_GMIX_MODEL) $(TEST_FASTEXP) \
		   $(TEST_FASTEXP_SPEED) $(TEST_IMAGE) $(TEST_SHAPE) \
		   $(TEST_MCA);

tests: $(ALLTESTS)

$(TEST_GMIX): gmix.h image.h mtrng.h jacobian.h test/test-gmix.cc
	$(CC) -o test/test-gmix test/test-gmix.cc $(CFLAGS) $(LDFLAGS)

$(TEST_GMIX_MODEL): gmix.h image.h mtrng.h jacobian.h test/test-gmix-model.cc
	$(CC) -o test/test-gmix-model test/test-gmix-model.cc $(CFLAGS) $(LDFLAGS)

$(TEST_FASTEXP): fastexp.h test/test-fastexp.cc
	$(CC) -o test/test-fastexp test/test-fastexp.cc $(CFLAGS) $(LDFLAGS)

$(TEST_FASTEXP_SPEED): fastexp.h test/test-fastexp-speed.cc
	$(CC) -o test/test-fastexp-speed test/test-fastexp-speed.cc $(CFLAGS) $(LDFLAGS)

$(TEST_IMAGE): image.h mtrng.h test/test-image.cc
	$(CC) -o test/test-image test/test-image.cc $(CFLAGS) $(LDFLAGS)

$(TEST_SHAPE): shape.h test/test-shape.cc
	$(CC) -o test/test-shape test/test-shape.cc $(CFLAGS) $(LDFLAGS)

$(TEST_MCA): mca.h test/test-mca.cc
	$(CC) -o test/test-mca test/test-mca.cc $(CFLAGS) $(LDFLAGS)


clean:
	rm -f $(ALLTESTS)
