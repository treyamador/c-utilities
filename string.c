#include <stdio.h>
#include <stdlib.h>

#define CHAR_END '\0'


struct String {
	char* str;
	int length;
};


void allocate(struct String* str, int elems) {
	str->str = malloc(elems*sizeof(char));
	str->length = elems;
}


struct String init(char* characters) {
	int i = 0;
	struct String str;
	while (characters[i] != '\0')
		++i;
	allocate(&str, i+1);
	for (i = 0; i < str.length; ++i)
		str.str[i] = characters[i];
	return str;
}


struct String empty() {
	struct String str = { NULL, 0 };
	return str;
}



void clear(struct String* str) {
	if (str->str != NULL)
		free(str->str);
	str->str = NULL;
	str->length = 0;
}


struct String copy(struct String* src) {
	struct String trg = empty();
	int i = 0;
	allocate(&trg, src->length);
	for (i = 0; i < trg.length; ++i)
		trg.str[i] = src->str[i];
	return trg;
}


struct String slice(struct String* str, int b, int f) {
	struct String sub = empty();
	int i = 0;
	allocate(&sub, f-b+1);
	while (b < f)
		sub.str[i++] = str->str[b++];
	sub.str[i] = '\0';
	return sub;
}


struct String* split(struct String* str, char delim) {
	
	int i = 0, j = 0, c = 0, d = 0;
	struct String* strs = NULL;
	struct String sub = empty();

	for (j = 0; j < str->length; ++j)
		if (str->str[j] == delim)
			++c;
	strs = malloc(c*sizeof(struct String));
	strs[c] = empty();

	for (j = 0; j < str->length; ++j) {
		if (str->str[j] == delim || str->str[j] == '\0') {
			clear(&sub);
			sub = slice(str, i, j);
			strs[d++] = copy(&sub);
			i = ++j;
		}
	}

	return strs;
	
}


struct String join(struct String* strs, char delim) {
	int i = 0, j = 0, c = 0, d = 0;
	struct String str = empty();
	while (strs[i++].str != NULL) {
		while (strs[i].str[j] != '\0') {
			++j;
		}
		if (delim != '\0') {
			++j;
		}
		c += j;
		j = 0;
	}
	allocate(&str, c+1);

	i = 0, j = 0;
	while (strs[i].str != NULL) {
		while (strs[i].str[j] != '\0') {
			str.str[d++] = strs[i].str[j++];
		}

		if (delim != '\0') {
			str.str[d++] = delim;
		}

		++i;
		j = 0;
	}

	str.str[d] = '\0';

	return str;
}



int main(int argc, char* argv) {

	int i = 0, s = 0;
	struct String str = init("abcdefg\0");
	struct String* strs = split(&str, 'e');

	s = sizeof(strs);
	s = 3;

	for (i = 0; i < s; ++i) {
		printf("%s\n", strs[i].str);
	}

	return 0;	
}

