LD=g++
CXX=g++ -g -c -std=c++11

EXEC_SRC=\
	testGrayLevelImage2D.cpp\
	testColorImage2D.cpp\
	invert-red-blue.cpp\
	save-green-channel.cpp\
	save-channels.cpp\

MODULE_SRC=\

MODULE_OBJ=${MODULE_SRC:.cpp=.o}
EXEC_OBJ=${EXEC_SRC:.cpp=.o}

EXEC_PRG=${EXEC_SRC:.cpp=}

all: ${EXEC_PRG} ${MODULE_OBJ} ${EXEC_OBJ}

testGrayLevelImage2D: testGrayLevelImage2D.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

testColorImage2D: testColorImage2D.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

invert-red-blue: invert-red-blue.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

save-green-channel: save-green-channel.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

save-channels: save-channels.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

.cpp.o: %.cpp %.hpp
	${CXX} $<

clean:
	rm -f ${EXEC_PRG} ${MODULE_OBJ} ${EXEC_OBJ}