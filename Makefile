CC = gcc
CFLAGS = -O2 -g -Wall -Werror

all: minify_json

minify_json:
	@echo "[+] Building project..."
	$(CC) $(CFLAGS) -o minify_json ./src/minify_json.c

clean:
	@echo "[+] Cleaning..."
	rm -f minify_json
