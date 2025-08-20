CC = gcc
CFLAGS = -Itests/unity
TESTS = tests/test_calculator.c
UNITY = tests/unity/unity.c
TARGET = test_calculator

all: $(TARGET)

$(TARGET): $(TESTS) $(UNITY)
	$(CC) $(CFLAGS) -o $(TARGET) $(TESTS) $(UNITY)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)