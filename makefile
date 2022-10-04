NUM?=2
numbers=1 2 3 10 11 12 13 14 15 16 17 18 19 20 61 62
tests=assets/testfiles

run:
	for number in $(numbers); \
	do \
		./lab$(NUM) $(tests)/in$$number.txt > $(tests)/out.txt ; \
		diff $(tests)/out$$number.txt $(tests)/out.txt || (echo "diff failed on test $$number \n") ; \
	done
	rm $(tests)/out.txt

compile:
	g++ -Wall -Werror -std=c++17 -g *.cpp automaton/*.cpp -o lab$(NUM)
