#include<iostream>
#include <cstdlib>
#include <cstdio>
#include <memory.h>
#include"../../vector+complex/vector.h"
#include"../../List/List.h"
#include"../../BinTree/BinTree.h"
#include"../../Bitmap/Bitmap.h"
#include <fstream>
#include <string> 
#define _CRT_SECURE_NO_WARNINGS
#define  N_CHAR  (0x80 - 0x20)//���Կɴ�ӡ�ַ�Ϊ��
using namespace std;
struct HuffChar//Huffman�ַ�
{
    char ch; unsigned int weight; //�ַ���Ƶ��
    HuffChar(char c = '^', unsigned int w = 0) : ch(c), weight(w) {};
    // �Ƚ������е���
    bool operator< (HuffChar const& hc) { return weight > hc.weight; } 
    bool operator!= (HuffChar const& hc) { return weight != hc.weight; }
};


class HuffTable//Huffman�����
{
public:
    HuffTable() {};
    HuffTable(char, char*);
    ~HuffTable();
    bool put(char, char*);
    char** get(char k);
private:
    Vector<char> key;
    Vector<char*> value;
};
HuffTable::HuffTable(char k, char* v)
{
    key.insert(k);
    value.insert(v);
}
HuffTable::~HuffTable()
{
    key.~Vector();
    value.~Vector();
}
inline bool HuffTable::put(char k, char* v)
{
    if (key.find(k) != -1)
    {
        return false;
    }
    key.insert(k);
    value.insert(v);
    return true;
}
inline char** HuffTable::get(char k)
{
    Rank r = key.find(k);
    if (r == -1)
    {
        return nullptr;
    }
    else
    {
        return &value[r];
    }
}

using HuffTree = BinTree<HuffChar>; //Huffman������BinTree�������ڵ�����ΪHuffChar
using HuffForest = List<HuffTree*>; //Huffmanɭ��
using HuffCode = Bitmap; //Huffman�����Ʊ���



int* statistics(const char* sample_text_file) {
    FILE* fp;
    if (fopen_s(&fp, sample_text_file, "r") != 0) {
        std::cerr << "Error: cannot open file \"" << sample_text_file << "\"." << std::endl;
        return nullptr;
    }

    int* freq = new int[N_CHAR]();  //��ʼ��Ϊ 0
    char ch;
    while (fscanf_s(fp, "%c", &ch, 1) == 1) {
        if (ch >= 0x20 && ch < 0x7F) {
            freq[ch - 0x20]++;
        }
    }

    fclose(fp);
    return freq;
}
HuffForest* initForest(int* freq)//����Ƶ��ͳ�Ʊ�Ϊÿ���ַ�����һ����
{
    HuffForest* forest = new HuffForest; //��Listʵ�ֵ�Huffmanɭ��
    for (int i = 0; i < N_CHAR; i++) //Ϊÿ���ַ�
    {
        forest->insertAsLast(new HuffTree); //����һ�����������ַ�����Ƶ��
        forest->last()->data->insertAsRoot(HuffChar(0x20 + i, freq[i])); //��������
    }
    return forest;
}
HuffTree* minHChar(HuffForest* forest)//��Huffmanɭ�����ҳ�Ȩ����С��Huffman�ַ�
{
    ListNodePosi<HuffTree*> m = forest->first(); //���׽ڵ�������������нڵ�
    for (ListNodePosi<HuffTree*> p = m->succ; forest->valid(p); p = p->succ)
    {
        if (m->data->root()->data.weight > p->data->root()->data.weight) //���ϸ���
        {
            m = p; //�ҵ���С�ڵ㣨����Ӧ��Huffman������
        }
    }
    return forest->remove(m); //��ɭ����ȡ����������������
}
HuffTree* generateTree(HuffForest* forest) //Huffman�����㷨
{
    while (1 < forest->size())
    {
        HuffTree* T1 = minHChar(forest); HuffTree* T2 = minHChar(forest);
        HuffTree* S = new HuffTree();
        S->insertAsRoot(HuffChar('^', T1->root()->data.weight + T2->root()->data.weight));
        S->attachAsLC(S->root(), T1);
        S->attachAsRC(S->root(), T2);
        forest->insertAsLast(S);
    } 
    return forest->first()->data;
}
static void generateCT(Bitmap* code, int length, HuffTable* table, BinNodePosi <HuffChar> v)
{
    if (IsLeaf(*v)) //����Ҷ�ڵ�
    {
        table->put(v->data.ch, code->bits2string(length));
        return;
    }
    if (HasLChild(*v)) //Left = 0
    {
        code->clear(length);
        generateCT(code, length + 1, table, v->lc);
    }
    if (HasRChild(*v)) //Right = 1
    {
        code->set(length);
        generateCT(code, length + 1, table, v->rc);
    }
}
HuffTable* generateTable(HuffTree* tree) //�����ַ�����ͳһ������ɢ�б�ʵ�ֵı������
{
    HuffTable* table = new HuffTable; Bitmap* code = new Bitmap;
    generateCT(code, 0, table, tree->root()); release(code); return table;
};
int encode(HuffTable* table, Bitmap* codeString, char* s) //���ձ�����Bitmap������
{
    int n = 0; //�����صı��봮�ܳ�n
    for (size_t m = strlen(s), i = 0; i < m; i++) //���������е�ÿ���ַ�
    {
        char** pCharCode = table->get(s[i]); //ȡ�����Ӧ�ı��봮
        if (!pCharCode) pCharCode = table->get(s[i] + 'A' - 'a'); //Сд��ĸתΪ��д
        if (!pCharCode) pCharCode = table->get(' '); //�޷�ʶ����ַ�ͳһ�����ո�
        printf("%s", *pCharCode); //�����ǰ�ַ��ı���
        for (size_t m = strlen(*pCharCode), j = 0; j < m; j++) //����ǰ�ַ��ı��������봮
            '1' == *(*pCharCode + j) ? codeString->set(n++) : codeString->clear(n++);
    }
    printf("\n");
    return n;
} //�����Ʊ��봮��¼��λͼcodeString��
void decode(HuffTree* tree, Bitmap* code, int n)
{   BinNodePosi<HuffChar> x = tree->root();
    for (int i = 0; i < n; i++)
    {
        x = code->test(i) ? x->rc : x->lc;
        if (IsLeaf(*x))
        {
            printf("%c", x->data.ch);
            x = tree->root();
        }
    }
} 

int main() 
{
    int* freq = statistics("dream.txt"); //���������ļ���ͳ�Ƹ��ַ��ĳ���Ƶ��
    HuffForest* forest = initForest(freq); release(freq); //����Huffmanɭ��
    HuffTree* tree = generateTree(forest); release(forest); //����Huffman������
    HuffTable* table = generateTable(tree); //��Huffman������ת��Ϊ�����
    char str[30][30] = { "a","b","c","go","dream"};
    for (int i = 0; str[i][0] != '\0'; i++) 
    {
        Bitmap* codeString = new Bitmap; 
        int n = encode(table, codeString, str[i]); 
        decode(tree, codeString, n); 
        cout << endl;
        release(codeString);
    }
    release(tree); //�ͷű�����
    return 0;
}