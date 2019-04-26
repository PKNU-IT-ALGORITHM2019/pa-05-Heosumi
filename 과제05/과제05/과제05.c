#include <stdio.h>
#include <string.h>
#define len 50

typedef struct WORD {
	char word[len];
	char class[len];
	char meaning[1000];
}Word;
typedef struct tree {
	struct tree *parent;
	struct tree *left;
	struct tree *right;
	Word *k;
}Tree;

Word* dict[170000];
int i = 0;

void Insert(Tree **root, Word *k) {
	Tree *x = *root;
	Tree *y = NULL;
	while (x != NULL) {
		y = x;
		if (strcmp(x->k->word, k->word) < 0)
			x = x->right;
		else
			x = x->left;
	}
	Tree *temp = (Tree *)malloc(sizeof(Tree));
	temp->k = k;
	temp->left = NULL;
	temp->right = NULL;
	temp->parent = y;
	if (y == NULL)
		*root = temp;
	else if (strcmp(y->k->word, k->word) < 0)
		y->right = temp;
	else
		y->left = temp;
	i++;
	return;
}

Tree *searchfind(Tree *x, char WORD[]) {
	if (x == NULL)
		return x;
	if (strcmp(WORD, x->k->word) < 0)
		return searchfind(x->left, WORD);
	else
		return searchfind(x->right, WORD);
}

Tree *successor(Tree *node) {
	if (node->right != NULL)
		return min(node->right);
	Tree *parent = node->parent; 
	while (node != NULL && node == parent->right) {
		node = parent;
		parent = node->parent;
	}
	return parent;
}

Tree *min(Tree *root) {
	while (root->left != NULL)
		root = root->left;
	return root;
}

Tree *Delete(Tree **root, Tree *node) {
	Tree *z;
	if (node->left == NULL || node->right == NULL)
		z = node;
	else
		z = successor(node);
	Tree *y;
	if (z->left != NULL)
		y = z->left;
	else
		y = z->right;
	if (y != NULL)
		y->parent = z->parent;
	if (z->parent == NULL)
		*root = y;
	else if (z == z->parent->left)
		z->parent->left = y;
	else z->parent->right = y;

	if (z != node)
		node->k = z->k;
	i--;
	return z;
}

int Deleteall(Tree **root) {
	int n = 0;

}

int main() {
	Tree *root = NULL;
	FILE *fp;
	fopen_s(&fp, "shuffled_dict.txt", "r");
	while (!feof(fp)) {
		char str[1000];
		fgets(str, 1000, fp);
		dict[i] = (Word *)malloc(sizeof(Word));
		char *token = strtok(str, "()");
		strcpy(dict[i]->word, token);
		dict[i]->word[strlen(dict[i]->word) - 1] = '\0';
		token = strtok(NULL, "()");
		strcpy(dict[i]->class, token);
		token = strtok(NULL, "()");
		if (token == NULL) {
			strcpy(str, dict[i]->class);
			strcpy(dict[i]->meaning, str + 1);
			strcpy(dict[i]->class, "\0");
		}
		else
			strcpy(dict[i]->meaning, token + 1);
		dict[i]->meaning[strlen(dict[i]->meaning) - 1] = '\0';
		Insert(&root, dict[i]);
	}
	char s[len];
	while (1) {
		prinf("$ ");
		scanf_s("%s", s);
		if (strcmp(s, "size") == 0)
			printf("%d\n", i);
		else if (strcmp(s, "find") == 0) {
			char WORD[len];
			scanf_s("%s", WORD);
			Tree *a = searchfind(root, WORD);
			if (a != NULL)
				printf("%s\n", a->k->meaning);
		}
		else if (strcmp(s, "add") == 0) {
			Word *WORD = (Word *)malloc(sizeof(Word));
			printf("word: ");
			gets(WORD->word);
			printf("clss: ");
			gets(WORD->class);
			printf("meaning: ");
			gets(WORD->meaning);
			Insert(&root, WORD);
		}
		else if (strcmp(s, "delete") == 0) {
			char WORD[len];
			scanf_s("%s", WORD);
			Tree *tmp = searchfind(root, WORD);
			if (tmp != NULL) {
				Tree *temp = Delete(&root, tmp);
				printf("%s Deleted successfully.\n", temp->k->word);
			}
		}
		else if (strcmp(s, "deleteall") == 0) {
			int n = Deleteall(&root);
			printf("%d words were deleted successfully.\n", n);
		}
	}
	fclose(fp);
	return 0;
}