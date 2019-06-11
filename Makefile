all: snowflake.so

snowflake.so: lsnowflake.c snowflake.c
	gcc -fPIC --shared -g -O0 -Wall -I/usr/local/include -o $@ $^ -L/usr/local/lib

test: all
	lua test.lua

clean:
	rm -f snowflake.so
