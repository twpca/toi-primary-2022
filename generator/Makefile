CC = g++
CCARGS = -O2 -Wall -Wshadow -std=gnu++1z -march=native
GENERATOR_LIST = 2022 bike entrance keyboard spy

all: $(GENERATOR_LIST)

clean:
	rm -f $(GENERATOR_LIST)

2022: 2022.cc
	$(CC) 2022.cc $(CCARGS) -o 2022

run_2022: 2022
	./2022

entrance: entrance.cc
	$(CC) entrance.cc $(CCARGS) -o entrance

run_entrance: entrance
	./entrance

keyboard: keyboard.cc
	$(CC) keyboard.cc $(CCARGS) -o keyboard

run_keyboard: keyboard
	./keyboard

spy: spy.py
	echo "OAO"

run_spy: spy.py
	python3 spy.py

bike: bike.cpp
	$(CC) bike.cpp $(CCARGS) -o bike

run_bike: bike
	./bike 10000   1   1 10 10 1 1000 line   random_uniform > 1_0000.in
	./bike 10001  90 100  2  2 1 1000 line   random_uniform > 1_0001.in
	./bike 10002  90 100  9 10 1 1000 line   random_uniform > 1_0002.in
	./bike 10003 100 100  9 10 1 1000 line   random_normal  > 1_0003.in
	./bike 10004  90 100  2  2 1 1000 star   random_uniform > 1_0004.in
	./bike 10005 100 100  9 10 1 1000 star   random_uniform > 1_0005.in
	./bike 10006  90 100  9 10 1 1000 star   random_normal  > 1_0006.in
	./bike 10007  90 100  2  2 1 1000 random random_uniform > 1_0007.in
	./bike 10008 100 100  9 10 1 1000 random random_uniform > 1_0008.in
	./bike 10009  90 100  9 10 1 1000 random random_normal  > 1_0009.in
	./bike 10010 100 100  9 10 1 1000 random random_normal  > 1_0010.in

	./bike 20001  95000 100000  2  2 1 1000 line   large_one > 2_0001.in
	./bike 20002  95000 100000  9 10 1 1000 line   large_one > 2_0002.in
	./bike 20003 100000 100000  9 10 1 1000 line   large_one > 2_0003.in
	./bike 20004  95000 100000  2  2 1 1000 line   large_one > 2_0004.in
	./bike 20005 100000 100000  9 10 1 1000 star   large_one > 2_0005.in
	./bike 20006  95000 100000  9 10 1 1000 star   large_one > 2_0006.in
	./bike 20007  95000 100000  2  2 1 1000 star   large_one > 2_0007.in
	./bike 20008 100000 100000  9 10 1 1000 random large_one > 2_0008.in
	./bike 20009  95000 100000  9 10 1 1000 random large_one > 2_0009.in
	./bike 20010 100000 100000  9 10 1 1000 random large_one > 2_0010.in

	./bike 30001  95000 100000  2  2 1 1000 line   random_uniform > 3_0001.in
	./bike 30002  95000 100000  9 10 1 1000 line   random_normal  > 3_0002.in
	./bike 30003 100000 100000  9 10 1 1000 line   random_uniform > 3_0003.in
	./bike 30004  95000 100000  2  2 1 1000 line   random_uniform > 3_0004.in
	./bike 30005 100000 100000  9 10 1 1000 line   random_uniform > 3_0005.in
	./bike 30006  95000 100000  9 10 1 1000 line   random_normal  > 3_0006.in
	./bike 30007  95000 100000  2  2 1 1000 line   random_uniform > 3_0007.in
	./bike 30008 100000 100000  9 10 1 1000 line   random_uniform > 3_0008.in
	./bike 30009  95000 100000  9 10 1 1000 line   random_uniform > 3_0009.in
	./bike 30010 100000 100000  9 10 1 1000 line   random_normal  > 3_0010.in

	./bike 40001  99900 100000  9 10 1 1000 line   random_uniform > 4_0001.in
	./bike 40002  99900 100000  9 10 1 1000 star   random_normal  > 4_0002.in
	./bike 40003  99900 100000  9 10 1 1000 random random_uniform > 4_0003.in
	./bike 40004  99900 100000  9 10 1 1000 random random_normal  > 4_0004.in
	./bike 40005  99900 100000  9 10 1 1000 random random_uniform > 4_0005.in
	./bike 40006  99900 100000  9 10 1 1000 random random_normal  > 4_0006.in
	./bike 40007  99900 100000  9 10 1 1000 random random_uniform > 4_0007.in
	./bike 40008  99900 100000  9 10 1 1000 random random_normal  > 4_0008.in
	./bike 40009  99900 100000  9 10 1 1000 random random_uniform > 4_0009.in
	./bike 40010 100000 100000  9 10 1 1000 random random_normal  > 4_0010.in
