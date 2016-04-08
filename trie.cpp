/*trie（字典树）模板，参考自百度百科
http://baike.baidu.com/view/2759664.htm
和http://blog.csdn.net/program_shun/article/details/6581420
*/
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

#define maxc 2 //字符集大小

struct trie
{
	int count; //记录该字符出现次数
	struct trie *next[maxc];
};

trie* trie_new()
{
	trie* t = (struct trie*)malloc(sizeof(struct trie));
	t->count = 0;
	memset(t->next, NULL, sizeof(t->next));
	return t;
}

void trie_add(trie* root, const char code[])
{
	int p=0, len=strlen(code), suffix;
	trie* node = root;
	while(p < len){
		switch(code[p]){
		case '.':
			suffix = 0;
			break;
		case '-':
			suffix = 1;
			break;
		}
		if(node->next[suffix] == NULL)
			node->next[suffix] = trie_new();
		node = node->next[suffix];
		++p;
	}
	++node->count;
}

void trie_free(trie *p)
{
	if(p){
		for(int i=0; i<maxc; ++i)
			trie_free(p->next[i]);
		free(p);
	}
}
