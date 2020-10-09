CC = g++ $(CFALGS)
# For debugging
CFLAGS = -O0 -g

GF_p2: GF_p2.h GF_p2.cpp Test_GF_p2.cpp
        $(CC) -o GF_p2 Test_GF_p2.cpp Test_GF_p2.cpp

clean
        rm -f GF_p2