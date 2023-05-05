#pragma once
#define DSA_STACK_VECTOR


#include "../Queue/Queue.h" 
#include "../Stack/Stack.h" 

#if defined( DSA_REDBLACK ) //�ں������
#define stature( p ) ( ( p ) ? ( p )->height : 0 ) //�ⲿ�ڵ㣨�ڣ��߶�Ϊ0�����ϵ���
#else //����BST��
#define stature( p ) ( (int)( ( p ) ? ( p )->height : -1 ) ) //�ⲿ�ڵ�߶�Ϊ-1�����ϵ���
#endif

typedef enum { RB_RED, RB_BLACK } RBColor; //�ڵ���ɫ
template <typename T> struct BinNode;
template <typename T> using BinNodePosi = BinNode<T>*; //�ڵ�λ��


template <typename T> struct BinNode
{ //�������ڵ�ģ��ṹ
	// ��Ա��Ϊ���������ͳһ����
	T data; //��ֵ
	BinNodePosi<T> parent, lc, rc; //���ڵ㼰���Һ���
	Rank height; //�߶ȣ�ͨ�ã�
	Rank npl; //Null Path Length����ʽ�ѣ�Ҳ��ֱ����height���棩
	RBColor color; //��ɫ���������
	// ���캯��
	BinNode() :
		parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) {}
	BinNode(T e, BinNodePosi<T> p = NULL, BinNodePosi<T> lc = NULL,
		BinNodePosi<T> rc = NULL, int h = 0, int l = 1, RBColor c = RB_RED) :
		data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {}
	// �����ӿ�
	Rank size(); //ͳ�Ƶ�ǰ�ڵ����������༴����Ϊ���������Ĺ�ģ
	BinNodePosi<T> insertAsLC(T const&); //��Ϊ��ǰ�ڵ�����Ӳ����½ڵ�
	BinNodePosi<T> insertAsRC(T const&); //��Ϊ��ǰ�ڵ���Һ��Ӳ����½ڵ�
	BinNodePosi<T> succ(); //ȡ��ǰ�ڵ��ֱ�Ӻ��
	template <typename VST> void travLevel(VST&); //������α���
	template <typename VST> void travPre(VST&); //�����������
	template <typename VST> void travIn(VST&); //�����������
	template <typename VST> void travPost(VST&); //�����������
	// �Ƚ������е���
	bool operator< (BinNode const& bn) { return data < bn.data; } //С��
	bool operator<= (BinNode const& bn) { return data <= bn.data; } //С�ڵ���
	bool operator> (BinNode const& bn) { return data > bn.data; } //����
	bool operator>= (BinNode const& bn) { return data >= bn.data; } //���ڵ���
	bool operator== (BinNode const& bn) { return data == bn.data; } //����
	bool operator!= (BinNode const& bn) { return data != bn.data; } //������
};

template <typename T> Rank BinNode<T>::size() //ͳ�Ƶ�ǰ�ڵ���������������Ϊ����������ģ
{
	Rank s = 1; //���뱾��
	if (lc) s += lc->size(); //�ݹ������������ģ
	if (rc) s += rc->size(); //�ݹ������������ģ
	return s;
}

template <typename T> BinNodePosi<T> BinNode<T>::insertAsLC(T const& e)
{
	return lc = new BinNode(e, this); //��e��Ϊ��ǰ�ڵ�����Ӳ��������
}

template <typename T> BinNodePosi<T> BinNode<T>::insertAsRC(T const& e)
{
	return rc = new BinNode(e, this); //��e��Ϊ��ǰ�ڵ���Һ��Ӳ��������
}

template <typename T> BinNodePosi<T> BinNode<T>::succ() //��λ�ڵ�v��ֱ�Ӻ��
{
	BinNodePosi<T> s = this; //��¼��̵���ʱ����
	if (rc)//�����Һ��ӣ���ֱ�Ӻ�̱�����������
	{ //����ؾ���
		s = rc; //��������
		while (HasLChild(*s)) s = s->lc; //�����С���Ľڵ�
	}
	else //����ֱ�Ӻ��Ӧ�ǡ�����ǰ�ڵ���������������е�������ȡ�
	{ //����ؾ���
		while (IsRChild(*s)) s = s->parent; //������������֧�����ϳ����Ϸ��ƶ�
		s = s->parent; //����ٳ����Ϸ��ƶ�һ�������ִ�ֱ�Ӻ�̣�������ڣ�
	}
	return s;
}

template <typename T> template <typename VST> //Ԫ�����͡�������
void BinNode <T>::travLevel(VST& visit) //��������α����㷨
{
	Queue<BinNodePosi<T>> Q; Q.enqueue(this); //���븨�����У����ڵ����
	while (!Q.empty()) //�ڶ����ٴα��֮ǰ����������
	{
		BinNodePosi<T> x = Q.dequeue(); visit(x->data); //ȡ�����׽ڵ㲢����֮
		if (HasLChild(*x)) Q.enqueue(x->lc); //�������
		if (HasRChild(*x)) Q.enqueue(x->rc); //�Һ������
	}
}

template <typename T> template <typename VST> //Ԫ�����͡�������
void BinNode <T>::travPre(VST& visit) //��������������㷨ͳһ���
{
	switch (rand() % 2) 
	{
	case 1: travPre_I1(this, visit); break; //������#1
	case 2: travPre_I2(this, visit); break; //������#2
	default: travPre_R(this, visit); break; //�ݹ��
	}
}

//�ӵ�ǰ�ڵ�����������֧�������룬ֱ��û�����֧�Ľڵ㣻��;�ڵ���������������
template <typename T, typename VST> //Ԫ�����͡�������
static void visitAlongVine(BinNodePosi<T> x, VST& visit, Stack<BinNodePosi<T>>& S)
{
	while (x)
	{
		visit(x->data); //���ʵ�ǰ�ڵ�
		S.push(x->rc); //�Һ�����ջ�ݴ棨���Ż���ͨ���жϣ�����յ��Һ�����ջ��
		x = x->lc; //�����֧����һ��
	}
}

template <typename T, typename VST> //Ԫ�����͡�������
void travPre_I2(BinNodePosi<T> x, VST& visit)//��������������㷨��������#2��
{
	Stack<BinNodePosi<T>> S; //����ջ
	while (true)
	{
		visitAlongVine(x, visit, S); //�ӵ�ǰ�ڵ��������������
		if (S.empty()) break; //ֱ��ջ��
		x = S.pop(); //������һ�������
	}
}

template <typename T> template <typename VST> //Ԫ�����͡�������
void BinNode<T>::travIn(VST& visit) //��������������㷨ͳһ���
{
	switch (rand() % 3)  //�˴����ֵ����汾���ѡ��
	{
	case 1: travIn_I1(this, visit); break; //������#1
	case 2: travIn_I2(this, visit); break; //������#2
	case 3: travIn_I3(this, visit); break; //������#3
	default: travIn_R(this, visit); break; //�ݹ��
	}
}

template <typename T> //�ӵ�ǰ�ڵ�����������֧�������룬ֱ��û�����֧�Ľڵ�
static void goAlongVine(BinNodePosi<T> x, Stack<BinNodePosi<T>>& S)
{
	while (x) { S.push(x); x = x->lc; } //��ǰ�ڵ���ջ���漴������֧���룬����ֱ��������
}

template <typename T, typename VST> //Ԫ�����͡�������
void travIn_I1(BinNodePosi<T> x, VST& visit) //��������������㷨��������#1��
{
	Stack<BinNodePosi<T>> S; //����ջ
	while (true)
	{
		goAlongVine(x, S); //�ӵ�ǰ�ڵ������������ջ
		if (S.empty()) break; //ֱ�����нڵ㴦�����
		x = S.pop(); visit(x->data); //����ջ���ڵ㲢����֮
		x = x->rc; //ת��������
	}
}

template <typename T, typename VST> //Ԫ�����͡�������
void travIn_I2(BinNodePosi<T> x, VST& visit) //��������������㷨��������#2��
{
	Stack<BinNodePosi<T>> S; //����ջ
	while (true)
	{
		if (x)
		{
			S.push(x); //���ڵ��ջ
			x = x->lc; //�������������
		}
		else if (!S.empty())
		{
			x = S.pop(); //��δ���ʵ�������Ƚڵ���ջ
			visit(x->data); //���ʸ����Ƚڵ�
			x = x->rc; //�������ȵ�������
		}
		else
			break; //�������
	}
}

template <typename T, typename VST> //Ԫ�����͡�������
void travIn_I3(BinNodePosi<T> x, VST& visit)//��������������㷨��������#3�����踨��ջ��
{
	bool backtrack = false; //ǰһ���Ƿ�մ����������ݡ���ʡȥջ����O(1)�����ռ�
	while (true)
	{
		if (!backtrack && HasLChild(*x)) //�����������Ҳ��Ǹոջ��ݣ���
		{
			x = x->lc; //�������������
		}
		else //���򡪡�����������ոջ��ݣ��൱������������
		{
			visit(x->data); //���ʸýڵ�
			if (HasRChild(*x)) //�����������ǿգ���
			{
				x = x->rc; //������������������
				backtrack = false; //���رջ��ݱ�־
			}
			else //���������գ���
			{
				if (!(x = x->succ())) break; //���ݣ����ִ�ĩ�ڵ�ʱ���˳����أ�
				backtrack = true; //�����û��ݱ�־
			}
		}
	}
}

template <typename T> template <typename VST> //Ԫ�����͡�������
void BinNode <T>::travPost(VST& visit)//��������������㷨ͳһ���
{
	switch (1)  //�˴�ѡ������棬��Ԥ���ݹ��
	{
	case 1: travPost_I(this, visit); break; //������
	default: travPost_R(this, visit); break; //�ݹ��
	}
}

template <typename T> //����Sջ���ڵ�Ϊ���������У��ҵ�������ɼ�Ҷ�ڵ�
static void gotoLeftmostLeaf(Stack<BinNodePosi<T>>& S) //��;�����ڵ�������ջ
{
	while (BinNodePosi<T> x = S.top()) //�Զ����£�������鵱ǰ�ڵ㣨��ջ����
	{
		if (HasLChild(*x)) //����������
		{
			if (HasRChild(*x)) S.push(x->rc); //�����Һ��ӣ�������ջ
			S.push(x->lc); //Ȼ���ת������
		}
		else //ʵ������
		{
			S.push(x->rc); //������
		}
	}
	S.pop(); //����֮ǰ������ջ���Ŀսڵ�
}

template <typename T, typename VST>
void travPost_I(BinNodePosi<T> x, VST& visit) //�������ĺ�������������棩
{
	Stack<BinNodePosi<T>> S; //����ջ
	if (x) S.push(x); //���ڵ���ջ
	while (!S.empty())// xʼ��Ϊ��ǰ�ڵ�
	{
		if (S.top() != x->parent) ////��ջ����x֮������Ϊ���֣�
		{
			gotoLeftmostLeaf(S); //�����������������ҵ�HLVFL���൱�ڵݹ����룩
		}
		x = S.pop(); visit(x->data); //����ջ������ǰһ�ڵ�֮��̣���������֮
	}
}


#define IsRoot(x) ( ! ( (x).parent ) )
#define IsLChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->lc ) )
#define IsRChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->rc ) )
#define HasParent(x) ( ! IsRoot(x) )
#define HasLChild(x) ( (x).lc )
#define HasRChild(x) ( (x).rc )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) ) //����ӵ��һ������
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) ) //ͬʱӵ����������
#define IsLeaf(x) ( ! HasChild(x) )
#define sibling( p ) ( IsLChild( * (p) ) ? (p)->parent->rc : (p)->parent->lc ) /*�ֵ�*/
#define uncle( x ) ( sibling( (x)->parent ) ) /*����*/
#define FromParentTo( x ) /*���Ը��׵�����*/ \
   ( IsRoot(x) ? _root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) )


template <typename T> class BinTree//������ģ����
{
protected:
	Rank _size; BinNodePosi<T> _root; //��ģ�����ڵ�
	virtual Rank updateHeight(BinNodePosi<T> x); //���½ڵ�x�ĸ߶�
	void updateHeightAbove(BinNodePosi<T> x); //���½ڵ�x�������ȵĸ߶�
public:
	BinTree() : _size(0), _root(NULL) {} //���캯��
	~BinTree() { if (0 < _size) remove(_root); } //��������
	Rank size() const { return _size; } //��ģ
	bool empty() const { return !_root; } //�п�
	BinNodePosi<T> root() const { return _root; } //����
	BinNodePosi<T> insertAsRoot(T const& e); //������ڵ�
	BinNodePosi<T> insertAsLC(BinNodePosi<T>x, T const& e); //e��Ϊx�����ӣ�ԭ�ޣ�����
	BinNodePosi<T> insertAsRC(BinNodePosi<T>x, T const& e); //e��Ϊx���Һ��ӣ�ԭ�ޣ�����
	BinNodePosi<T> attachAsLC(BinNodePosi<T>x, BinTree<T>*& T); //T��Ϊx����������
	BinNodePosi<T> attachAsRC(BinNodePosi<T>x, BinTree<T>*& T); //T��Ϊx����������
	Rank remove(BinNodePosi<T>x); //ɾ����λ��x���ڵ�Ϊ�������������ظ�����ԭ�ȵĹ�ģ
	BinTree<T>* secede(BinNodePosi<T>x); //������x�ӵ�ǰ����ժ����������ת��Ϊһ�ö�������
	template <typename VST> //������
	void travLevel(VST& visit) { if (_root) _root->travLevel(visit); } //��α���
	template <typename VST> //������
	void travPre(VST& visit) { if (_root) _root->travPre(visit); } //�������
	template <typename VST> //������
	void travIn(VST& visit) { if (_root) _root->travIn(visit); } //�������
	template <typename VST> //������
	void travPost(VST& visit) { if (_root) _root->travPost(visit); } //�������
	bool operator<(BinTree<T> const& t) //�Ƚ���
	{
		return _root && t._root && lt(_root, t._root);
	}
	bool operator<=(BinTree<T> const& t) //�Ƚ���
	{
		return _root && t._root && !(mt(_root, t._root));
	}
	bool operator>(BinTree<T> const& t) //�Ƚ���
	{
		return _root && t._root && mt(_root, t._root);
	}
	bool operator>=(BinTree<T> const& t) //�Ƚ���
	{
		return _root && t._root && !(lt(_root, t._root));
	}
	bool operator==(BinTree<T> const& t) //�е���
	{
		return _root && t._root && (_root == t._root);
	}
	bool operator!=(BinTree<T> const& t) //�е���
	{
		return _root && t._root && (_root != t._root);
	}
}; //BinTree
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

template <typename T> Rank BinTree<T>::updateHeight(BinNodePosi<T> x) //���½ڵ�x�߶�
{
	return x->height = 1 + max(stature(x->lc), stature(x->rc));//���������������
}

template <typename T> void BinTree<T>::updateHeightAbove(BinNodePosi<T> x) //���¸߶�
{
	while (x) { updateHeight(x); x = x->parent; }//��x�����������������ȡ����Ż�
}

template <typename T> BinNodePosi<T> BinTree<T>::insertAsRoot(T const& e)
{
	_size = 1; return _root = new BinNode<T>(e);//��e�������ڵ����յĶ�����
}

template <typename T> BinNodePosi<T> BinTree<T>::insertAsLC(BinNodePosi<T>x, T const& e)
{
	_size++; x->insertAsLC(e); updateHeightAbove(x); return x->lc;// e����Ϊx������
}

template <typename T> BinNodePosi<T> BinTree<T>::insertAsRC(BinNodePosi<T>x, T const& e)
{
	_size++; x->insertAsRC(e); updateHeightAbove(x); return x->rc;// e����Ϊx���Һ���
}

template <typename T> //��S�����ڵ�x�������������������S�����ÿ�
BinNodePosi<T> BinTree<T>::attachAsLC(BinNodePosi<T>x, BinTree<T>*& S)  // x->lc == NULL
{
	if (x->lc = S->_root) x->lc->parent = x; //����
	_size += S->_size; updateHeightAbove(x); //����ȫ����ģ��x�������ȵĸ߶�
	S->_root = NULL; S->_size = 0; release(S); S = NULL; return x; //�ͷ�ԭ�������ؽ���λ��
}

template <typename T> //��S�����ڵ�x�������������������S�����ÿ�
BinNodePosi<T> BinTree<T>::attachAsRC(BinNodePosi<T>x, BinTree<T>*& S)// x->rc == NULL
{
	if (x->rc = S->_root) x->rc->parent = x; //����
	_size += S->_size; updateHeightAbove(x); //����ȫ����ģ��x�������ȵĸ߶�
	S->_root = NULL; S->_size = 0; release(S); S = NULL; return x; //�ͷ�ԭ�������ؽ���λ��
}

template <typename T> //ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
Rank BinTree<T>::remove(BinNodePosi<T> x)// assert: xΪ�������еĺϷ�λ��
{
	FromParentTo(*x) = NULL; //�ж����Ը��ڵ��ָ��
	updateHeightAbove(x->parent); //�������ȸ߶�
	Rank n = removeAt(x); _size -= n; return n; //ɾ������x�����¹�ģ������ɾ���ڵ�����
}
template <typename T> //ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
static Rank removeAt(BinNodePosi<T> x) // assert: xΪ�������еĺϷ�λ��
{
	if (!x) return 0; //�ݹ��������
	Rank n = 1 + removeAt(x->lc) + removeAt(x->rc); //�ݹ��ͷ���������
	release(x->data); release(x); return n; //�ͷű�ժ���ڵ㣬������ɾ���ڵ�����
} // release()�����ͷŸ��ӽṹ�����㷨��ֱ�ӹ�ϵ������ʵ������

template <typename T> struct Cleaner
{
	static void clean(T x) {} //�൱�ڵݹ��
};

template <typename T> struct Cleaner<T*>
{
	static void clean(T* x)
	{
		if (x) { delete x; } //������а���ָ�룬�ݹ��ͷ�
	}
};

template <typename T> void release(T x) { Cleaner<T>::clean(x); }

template <typename T> //���������������㷨��������x�ӵ�ǰ����ժ���������װΪһ�ö�����������
BinTree<T>* BinTree<T>::secede(BinNodePosi<T> x)// assert: xΪ�������еĺϷ�λ��
{
	FromParentTo(*x) = NULL; //�ж����Ը��ڵ��ָ��
	updateHeightAbove(x->parent); //����ԭ�����������ȵĸ߶�
	BinTree<T>* S = new BinTree<T>; S->_root = x; x->parent = NULL; //������xΪ��
	S->_size = x->size(); _size -= S->_size; return S; //���¹�ģ�����ط������������
}


