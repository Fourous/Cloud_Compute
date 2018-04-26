#pragma warning(disable : 4996)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAXSIZE = 128;  

typedef struct node {
	char word[MAXSIZE];
	int size;
	struct node *next;
}*List, *pNode;

List Init() {
	List head;
	head = (pNode)malloc(sizeof(struct node));
	head->size = 0;
	head->word[0] = '\0';
	head->next = NULL;
	return head;
}

char *toLower(char s[]) {
	int i = 0;
	while (s[i]) {
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] += 'a' - 'A';
		++i;
	}
	return s;
}

int toWord(char s[],char* word2[]) {
	int n = 0;
	int word2num=0;
	for (; s[n] != '\0'; n++);
	for (int i = 0; i<n;i++) {
		if (s[i] >= 'a'&&s[i] <= 'z' || s[i] >= 'A'&&s[i] <= 'Z');
		else {
			if (s[i] == '-' || s[i] == '\'') {
				continue;
			}
			if (i > 0 && i < n - 1) {
				for(int k=i+1;s[k]!='\0';k++){
					if (s[k] >= 'a'&&s[k] <= 'z' || s[k] >= 'A'&&s[k] <= 'Z') {
						word2[word2num++] = &s[k];
						break;
					}
				}
				s[i] = '\0';
				continue;
			}
			for (int j = i; s[j] != '\0';j++) {
				s[j] = s[j+1];
			}
		}
	}
	return word2num;
}

void Add(List head, char s[]) {
	pNode p = head;
	char t[MAXSIZE];
	strcpy(t, toLower(s));
	while (p->next) {
		if (strcmp(p->next->word, t) == 0) {
			++p->next->size;
			return;
		}
		p = p->next;
	}
	p->next = (pNode)malloc(sizeof(struct node));
	strcpy(p->next->word, t);
	p->next->size = 1;
	p->next->next = NULL;
}

void Sort(List head) { 
	pNode p, q, qt;
	char ct[MAXSIZE];
	int it;
	for (p = head; p->next; p = p->next) {
		qt = p;
		for (q = p->next; q->next; q = q->next) {
			if (qt->next->size < q->next->size)
				qt = q;
		}
		if (p != qt) {
			strcpy(ct, p->next->word);
			strcpy(p->next->word, qt->next->word);
			strcpy(qt->next->word, ct);
			it = qt->next->size;
			qt->next->size = p->next->size;
			p->next->size = it;
		}
	}
}

void Show(List head, int n, FILE *fp) { 
	int i;
	pNode p = head->next;
	for (i = 0; p; ++i) {
		fprintf(fp, "%3d : %s\n", p->size, p->word);
		if (i < n) printf("%3d : %s\n", p->size, p->word);
		p = p->next;
	}
}

int main() {
	char word[MAXSIZE];
	List head = Init();
	FILE *fin = fopen("/home/fourous/yun/data.dat", "rt");
	FILE *fout = fopen("/home/fourous/yun/data1.txt", "wt");
	List list = Init();
	if (fin == NULL || fout == NULL) {
		printf("文件不存在\n");
		return 1;
	}
	while (fscanf(fin, "%s", word) == 1) {
		char *word2[MAXSIZE];
		int word2num=toWord(word,&word2[0]);
		Add(head, word);
		for (int i = 0; i < word2num; i++)
			Add(head, word2[i]);
	}
	fclose(fin);
	Sort(head);
	Show(head, 3, fout);
	fclose(fout);
	system("pause");
	return 0;
}
