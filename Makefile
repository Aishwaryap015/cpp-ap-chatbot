all:
	g++ main.cpp io.c -o chatbot

run: all
	./chatbot

clean:
	rm -f chatbot
