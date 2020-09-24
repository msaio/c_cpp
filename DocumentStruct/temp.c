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
		printf(".");
	}
}

void print_document(struct document doc) {
	for(int i = 0; i < doc.paragraph_count; i++) {
		print_paragraph(doc.data[i]);
		if (i != doc.paragraph_count - 1)
			printf("\n");
	}
}

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
