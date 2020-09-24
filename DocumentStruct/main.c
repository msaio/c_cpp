#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5


// TO DO: Get input from user.
// First line is number of paragraphs.
// Next ones is paragraph.
// Every sentence is seprated by '.' and every word is seprated by ' ' and every paragraph, by '\n'
// At the end of input, there is no '\n' and the position strlen(intput) + 1 is '\0'.
char* get_input_text() {	
	int paragraph_count;
	scanf("%d", &paragraph_count);

	char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
	memset(doc, 0, sizeof(doc));
	getchar();
	for (int i = 0; i < paragraph_count; i++) {
		scanf("%[^\n]%*c", p[i]);
		strcat(doc, p[i]);
		if (i != paragraph_count - 1)
			strcat(doc, "\n");
	}

	char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
	strcpy(returnDoc, doc);
	return returnDoc;
}

// TO DO: Define the document structure
struct word {
	char* data;
};

struct sentence {
	struct word* data;
	int word_count;//denotes number of words in a sentence
};

struct paragraph {
	struct sentence* data  ;
	int sentence_count;//denotes number of sentences in a paragraph
};

struct document {
	struct paragraph* data;
	int paragraph_count;//denotes number of paragraphs in a document
};

typedef struct word word; // word is a list of char
typedef struct sentence sentence; // sentence is a list of word
typedef struct paragraph paragraph; // paragraph is a list of sentence
typedef struct document document; // document is a list of paragraph

// TO DO: Add to document
// add char to word
void add_char(word* _word, char _char){
	//Original style of mine, but got problem with hackerrank
	if(_word->data == NULL){
		_word->data = (char*)malloc(0);
	}
	int len = strlen(_word->data);
	_word->data = (char*)realloc( _word->data,(len+1)* sizeof(char));
	_word->data[len] = _char;

	// Work fine in hackerrank
	// The point is we need '\0' or ASCII 0(NULL) at the end of string.
	/*static int size;
		if (_word->data == NULL){
		_word->data = (char*)malloc(0);
		size = 2;
		}
		_word->data = (char*)realloc(_word->data, size * sizeof(char));
		_word->data[size - 2] = _char;
		_word->data[size - 1] = 0;
		size++;*/

	// Another style, with strcpy() from string.h lib
	/*if(_word->data == NULL){
		_word->data = (char*)malloc(0);
	}
	int len = strlen(_word->data);
	char* t = calloc(len+1, sizeof(char));
	for(int i=0; i<len; i++){
		t[i] = _word->data[i];
	}
	t[len] = _char;
	t[len+1] = 0;
	strcpy(_word->data, t);*/

	// Just for testing
	/*printf("%d", (int)strlen(_word->data));*/
}
// add word to sentence
void add_word(sentence* _sentence, word *_word){
	if(_word->data == NULL) return;
	if(_sentence->data == NULL){
		_sentence->data = (word*)malloc(0);
		_sentence->word_count = 0;
	}
	_sentence->word_count++;
	_sentence->data = (word*)realloc(_sentence->data, (_sentence->word_count)*sizeof(word));
	_sentence->data[_sentence->word_count-1] = *_word;
	_word->data = NULL;
}
// add sentence to paragraph
void add_sentence(paragraph* _paragraph, sentence* _sentence){
	if(_paragraph->data == NULL){
		_paragraph->data = (sentence*)malloc(0);
		_paragraph->sentence_count = 0;
	}
	_paragraph->sentence_count++;
	_paragraph->data = (sentence*)realloc(_paragraph->data, (_paragraph->sentence_count)*sizeof(sentence));
	_paragraph->data[_paragraph->sentence_count - 1] = *_sentence;
	_sentence->data = NULL;
}

// add paragraph to document
void add_paragraph(document* _document, paragraph* _paragraph){
	if(_document->data == NULL){
		_document->data = (paragraph*)malloc(0);
		_document->paragraph_count = 0;
	}

	_document->paragraph_count++;
	_document->data = (paragraph*)realloc(_document->data, (_document->paragraph_count)*sizeof(paragraph));
	_document->data[_document->paragraph_count - 1] = *_paragraph;
	_paragraph->data = NULL;
}

//TO DO: Print word, sentence, paragrapn, document.
void print_word(struct word w) {
	printf("%s", w.data);
}

void print_sentence(struct sentence sen) {
	for(int i = 0; i < sen.word_count; i++) {
		print_word(sen.data[i]);
		if (i != sen.word_count - 1) {
			printf(" ");
		}
	}
}

void print_paragraph(struct paragraph para) {
	for(int i = 0; i < para.sentence_count; i++){
		print_sentence(para.data[i]);
		printf(". ");
	}
}

void print_document(struct document doc) {
	for(int i = 0; i < doc.paragraph_count; i++) {
		print_paragraph(doc.data[i]);
		if (i != doc.paragraph_count - 1)
			printf("\n");
	}
}

// TO DO: 
// 1. Get the kth word in mth sentence of nth paragraph:
word kth_word_in_mth_sentence_of_nth_paragraph(document doc, int k, int m, int n){
	return doc.data[n-1].data[m-1].data[k-1];
}
// 2. Get the kth sentence is mth paragraph:
sentence kth_sentence_in_mth_paragraph(document doc, int k, int m){
	return doc.data[m-1].data[k-1];
}
// 3. Get the kth paragraph:
paragraph kth_paragraph(document doc, int k){
	return doc.data[k-1];
}

// TO DO: From input to document
document get_document(char *text){
	word _w;
	_w.data = NULL;
	sentence _s;
	_s.data = NULL;
	paragraph _p;
	_p.data = NULL;
	document _d;
	_d.data = NULL;

	for(int i=0; i<strlen(text)+1; i++){
		switch (text[i]) {
			case ' ':
				/*printf(" => addWord\n");*/
				add_word(&_s, &_w);
				break;
			case '.':
				/*printf("\naddSentence\n");*/
				add_word(&_s, &_w);
				add_sentence(&_p, &_s);
				break;
			case '\n':
			case '\0':
				/*printf("addParagraph\n");*/
				add_paragraph(&_d, &_p);
				break;
			default:
				/*printf(" AC ");*/
				add_char(&_w, text[i]);
				break;
		}
	}
	return _d;
}

// MAIN
int main(int argc, char *argv[])
{
	// What happen inside input
	/*
		 char* text = get_input_text();
		 printf("\n%s\n\n", text);

		 for(int i=0; i<strlen(text)+1; i++){
		 switch (text[i]) {
		 case '\n':
		 printf("newLine confirmed\n");	
		 break;
		 case '\0':
		 printf("theEnd of Doc\n");
		 default:
		 break;

		 }
		 }
		 */

	// How is text added to document.
	/*char _t[] = "   Nice to See you Fuck you.\nHere we go again.   Ur mom is gay.\n\0";
		word _w;
		_w.data = NULL;
		sentence _s;
		_s.data = NULL;
		paragraph _p;
		_p.data = NULL;
		document _d;
		_d.data = NULL;

		for(int i=0; i<strlen(_t); i++){
		switch (_t[i]) {
		case ' ':
		printf(" => addWord\n");
		add_word(&_s, &_w);
		break;
		case '.':
		printf(" => addWord\n");
		printf("addSentence\n");
		add_word(&_s, &_w);
		add_sentence(&_p, &_s);
		break;
		case '\n':
		case '\0':
		printf("addParagraph\n");
		add_paragraph(&_d, &_p);
		break;
		default:
		printf(" AC ");
		add_char(&_w, _t[i]);
		break;
		}
		}
		printf("\n");
		print_document(_d);	
		printf("\n");
		print_paragraph(kth_paragraph(_d, 2));	
		*/

	// RUN AND FUN
	char* text = get_input_text();
	document Doc = get_document(text);

	int q;
	scanf("%d", &q);

	while (q--) {
		int type;
		scanf("%d", &type);

		if (type == 3){
			int k, m, n;
			scanf("%d %d %d", &k, &m, &n);
			struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
			print_word(w);
		}

		else if (type == 2) {
			int k, m;
			scanf("%d %d", &k, &m);
			struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
			print_sentence(sen);
		}

		else{
			int k;
			scanf("%d", &k);
			struct paragraph para = kth_paragraph(Doc, k);
			print_paragraph(para);
		}
		printf("\n");
	}     

	return 0;
}
