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
#define  N_CHAR  (0x80 - 0x20)//仅以可打印字符为例
using namespace std;
struct HuffChar//Huffman字符
{
    char ch; unsigned int weight; //字符、频率
    HuffChar(char c = '^', unsigned int w = 0) : ch(c), weight(w) {};
    // 比较器、判等器
    bool operator< (HuffChar const& hc) { return weight > hc.weight; } 
    bool operator!= (HuffChar const& hc) { return weight != hc.weight; }
};


class HuffTable//Huffman编码表
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

using HuffTree = BinTree<HuffChar>; //Huffman树，由BinTree派生，节点类型为HuffChar
using HuffForest = List<HuffTree*>; //Huffman森林
using HuffCode = Bitmap; //Huffman二进制编码



int* statistics(const char* sample_text_file) {
    FILE* fp;
    if (fopen_s(&fp, sample_text_file, "r") != 0) {
        std::cerr << "Error: cannot open file \"" << sample_text_file << "\"." << std::endl;
        return nullptr;
    }

    int* freq = new int[N_CHAR]();  //初始化为 0
    char ch;
    while (fscanf_s(fp, "%c", &ch, 1) == 1) {
        if (ch >= 0x20 && ch < 0x7F) {
            freq[ch - 0x20]++;
        }
    }

    fclose(fp);
    return freq;
}
HuffForest* initForest(int* freq)//根据频率统计表，为每个字符创建一棵树
{
    HuffForest* forest = new HuffForest; //以List实现的Huffman森林
    for (int i = 0; i < N_CHAR; i++) //为每个字符
    {
        forest->insertAsLast(new HuffTree); //生成一棵树，并将字符及其频率
        forest->last()->data->insertAsRoot(HuffChar(0x20 + i, freq[i])); //存入其中
    }
    return forest;
}
HuffTree* minHChar(HuffForest* forest)//在Huffman森林中找出权重最小的Huffman字符
{
    ListNodePosi<HuffTree*> m = forest->first(); //从首节点出发，遍历所有节点
    for (ListNodePosi<HuffTree*> p = m->succ; forest->valid(p); p = p->succ)
    {
        if (m->data->root()->data.weight > p->data->root()->data.weight) //不断更新
        {
            m = p; //找到最小节点（所对应的Huffman子树）
        }
    }
    return forest->remove(m); //从森林中取出该子树，并返回
}
HuffTree* generateTree(HuffForest* forest) //Huffman编码算法
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
    if (IsLeaf(*v)) //若是叶节点
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
HuffTable* generateTable(HuffTree* tree) //将各字符编码统一存入以散列表实现的编码表中
{
    HuffTable* table = new HuffTable; Bitmap* code = new Bitmap;
    generateCT(code, 0, table, tree->root()); release(code); return table;
};
int encode(HuffTable* table, Bitmap* codeString, char* s) //按照编码表对Bitmap串编码
{
    int n = 0; //待返回的编码串总长n
    for (size_t m = strlen(s), i = 0; i < m; i++) //对于明文中的每个字符
    {
        char** pCharCode = table->get(s[i]); //取出其对应的编码串
        if (!pCharCode) pCharCode = table->get(s[i] + 'A' - 'a'); //小写字母转为大写
        if (!pCharCode) pCharCode = table->get(' '); //无法识别的字符统一视作空格
        printf("%s", *pCharCode); //输出当前字符的编码
        for (size_t m = strlen(*pCharCode), j = 0; j < m; j++) //将当前字符的编码接入编码串
            '1' == *(*pCharCode + j) ? codeString->set(n++) : codeString->clear(n++);
    }
    printf("\n");
    return n;
} //二进制编码串记录于位图codeString中
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
    int* freq = statistics("dream.txt"); //根据样本文件，统计各字符的出现频率
    HuffForest* forest = initForest(freq); release(freq); //创建Huffman森林
    HuffTree* tree = generateTree(forest); release(forest); //生成Huffman编码树
    HuffTable* table = generateTable(tree); //将Huffman编码树转换为编码表
    char str[30][30] = { "a","b","c","go","dream"};
    for (int i = 0; str[i][0] != '\0'; i++) 
    {
        Bitmap* codeString = new Bitmap; 
        int n = encode(table, codeString, str[i]); 
        decode(tree, codeString, n); 
        cout << endl;
        release(codeString);
    }
    release(tree); //释放编码树
    return 0;
}