TARGET=closest
CXX=c++
LD=c++
OBJS=main.cpp
closest:$(OBJS)
	$(LD) -o $(TARGET) $(OBJS)
clean:
	rm -rf *.o