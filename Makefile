COMPILER = gcc
CFLAGS = -O2 -g -Wall -Werror

all: minify_json

minify_json:
	@echo "[+] Building project..."
	$(COMPILER) $(CFLAGS) -o minify_json ./src/minify_json.c

clean:
	@echo "[+] Cleaning..."
	rm -f minify_json
