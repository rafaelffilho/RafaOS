#include "../include/common.h"

int memset(void *ptr, uint32_t val, uint32_t size) {

	for (uint32_t i = 0; i < size; ++i) { ((uint8_t *) ptr)[i] = val; }

	return 0;
}

void swap(char *x, char *y) {
	char t = *x;

	*x = *y;
	*y = t;
}

char *reverse(char *buffer, int i, int j) {
	while (i < j) swap(&buffer[i++], &buffer[j--]);

	return buffer;
}

int32_t abs(int32_t value) { return value < 0 ? -value : value; }

char *itoa(int32_t value, char *buffer, uint32_t base) {
	if (base < 2 || base > 32) return buffer;

	int n = abs(value);

	int i = 0;
	while (n) {
		int r = n % base;

		if (r >= 10)
			buffer[i++] = 65 + (r - 10);
		else
			buffer[i++] = 48 + r;

		n = n / base;
	}

	if (i == 0) buffer[i++] = '0';

	if (value < 0 && base == 10) buffer[i++] = '-';

	buffer[i++] = '\0';

	return reverse(buffer, 0, i - 1);
}