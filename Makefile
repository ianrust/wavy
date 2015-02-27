CC = g++

TARGET = wavy_test

$(TARGET): $(TARGET).cpp pcmwavgen.h wavytypes.h
	$(CC) $(TARGET).cpp -o $(TARGET)