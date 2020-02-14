DIR_SRC = ./src
DIR_OBJ = ./obj

OUT_FILE=LG_P76071218
SRC = $(wildcard ${DIR_SRC}/*.cpp)  
OBJ = $(patsubst %.cpp,${DIR_OBJ}/%.o,$(notdir ${SRC})) 

CC = g++
CFLAGS = -Wall -O3

main:${OBJ}
	$(CC) $(OBJ) -o ${OUT_FILE}
${DIR_OBJ}/%.o:${DIR_SRC}/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@
.PHONY:clean
clean:
	@find ${DIR_OBJ} -name *.o -exec rm -rf {} \;
	@rm -f ${OUT_FILE};

sb1:
	@./${OUT_FILE} -bench Benchmark/superblue1/superblue1 -output ${OUT_FILE}_superblue1.pl
sb5:
	@./${OUT_FILE} -bench Benchmark/superblue5/superblue5 -output ${OUT_FILE}_superblue5.pl 
sb19:
	@./${OUT_FILE} -bench Benchmark/superblue19/superblue19 -output ${OUT_FILE}_superblue19.pl 

test_all:
	@./${OUT_FILE} -bench Benchmark/superblue1/superblue1 -output ${OUT_FILE}_superblue1.pl
	@./${OUT_FILE} -bench Benchmark/superblue5/superblue5 -output ${OUT_FILE}_superblue5.pl 
	@./${OUT_FILE} -bench Benchmark/superblue19/superblue19 -output ${OUT_FILE}_superblue19.pl 

legal1:
	@./iccad2013_check_legality Benchmark/superblue1/superblue1.aux ${OUT_FILE}_superblue1.pl
legal5:
	@./iccad2013_check_legality Benchmark/superblue5/superblue5.aux ${OUT_FILE}_superblue5.pl
legal19:
	@./iccad2013_check_legality Benchmark/superblue19/superblue19.aux ${OUT_FILE}_superblue19.pl

legal_all:
	@./iccad2013_check_legality Benchmark/superblue1/superblue1.aux ${OUT_FILE}_superblue1.pl
	@./iccad2013_check_legality Benchmark/superblue5/superblue5.aux ${OUT_FILE}_superblue5.pl
	@./iccad2013_check_legality Benchmark/superblue19/superblue19.aux ${OUT_FILE}_superblue19.pl

hpwl1:
	@./iccad2013_get_hpwl Benchmark/superblue1/superblue1.aux ${OUT_FILE}_superblue1.pl
hpwl5:
	@./iccad2013_get_hpwl Benchmark/superblue5/superblue5.aux ${OUT_FILE}_superblue5.pl
hpwl19:
	@./iccad2013_get_hpwl Benchmark/superblue19/superblue19.aux ${OUT_FILE}_superblue19.pl

hpwl_all:
	@./iccad2013_get_hpwl Benchmark/superblue1/superblue1.aux ${OUT_FILE}_superblue1.pl
	@./iccad2013_get_hpwl Benchmark/superblue5/superblue5.aux ${OUT_FILE}_superblue5.pl
	@./iccad2013_get_hpwl Benchmark/superblue19/superblue19.aux ${OUT_FILE}_superblue19.pl
