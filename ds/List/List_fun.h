
#pragma once
#include "List.h"//引用模板类


template <typename T> void List<T>::init()//列表初始化，在创建列表对象时统一调用
{
	header = new ListNode<T>;//创建头哨兵节点
	trailer = new ListNode<T>;//创建尾哨兵节点
	header->succ = trailer; header->pred = NULL;//向前链接
	trailer->pred = header; trailer->succ = NULL;//向后链接
	_size = 0;//记录规模
}

template <typename T> Rank List<T>::clear()//清空列表
{
	Rank oldSize = _size;
	while (0 < _size) remove(header->succ);//反复删除首节点，直至列表变空
	return oldSize;
}

template <typename T>//列表内部方法：复制列表中自位置p起的n项
void List<T>::copyNodes(ListNodePosi<T> p, Rank n)// p合法，且至少有n-1个真后继
{
	init();//创建头、尾哨兵节点并做初始化
	while (n--) { insertAsLast(p->data); p = p->succ; }//将起自p的n项依次作为末节点插入
}

template <typename T> //有序列表的归并：当前列表中自p起的n个元素，与列表L中自q起的m个元素归并
ListNodePosi<T> List<T>::merge(ListNodePosi<T> p, Rank n,
	List<T>& L, ListNodePosi<T> q, Rank m) {
	// this.valid(p) && Rank(p) + n <= size && this.sorted(p, n)
	// L.valid(q) && Rank(q) + m <= L._size && L.sorted(q, m)
	// 注意：在归并排序之类的场合，有可能this == &L && Rank(p) + n = Rank(q)
	ListNodePosi<T> pp = p->pred; //归并之后p可能不再指向首节点，故需先记忆，以便在返回前更新
	while ((0 < m) && (q != p)) //q尚未出界（或在mergeSort()中，p亦尚未出界）之前
		if ((0 < n) && (p->data <= q->data)) //若p尚未出界且v(p) <= v(q)，则
		{
			p = p->succ; n--;
		} //p直接后移，即完成归入
		else //否则，将q转移至p之前，以完成归入
		{
			insert(L.remove((q = q->succ)->pred), p); m--;
		}
	return pp->succ; //更新的首节点
}

template <typename T> //列表的归并排序算法：对起始于位置p的n个元素排序
void List<T>::mergeSort(ListNodePosi<T>& p, Rank n) // valid(p) && Rank(p) + n <= size
{
	if (n < 2) return; //若待排序范围已足够小，则直接返回；否则...
	Rank m = n >> 1; //以中点为界
	ListNodePosi<T> q = p; for (Rank i = 0; i < m; i++) q = q->succ; //找到后子列表起点
	mergeSort(p, m); mergeSort(q, n - m); //前、后子列表各分别排序
	p = merge(p, m, *this, q, n - m); //归并
} //注意：排序后，p依然指向归并后区间的（新）起点

template <typename T> //对列表中起始于位置p、宽度为n的区间做选择排序
void List<T>::selectionSort(ListNodePosi<T> p, Rank n)// valid(p) && Rank(p) + n <= size
{
	ListNodePosi<T> head = p->pred, tail = p;
	for (Rank i = 0; i < n; i++) tail = tail->succ; //待排序区间为(head, tail)
	while (1 < n)  //在至少还剩两个节点之前，在待排序区间内
	{
		ListNodePosi<T> max = selectMax(head->succ, n); //找出最大者（歧义时后者优先）
		insert(remove(max), tail); //将其移至无序区间末尾（作为有序区间新的首元素）
		/*DSA*///swap(tail->pred->data, selectMax( head->succ, n )->data );
		tail = tail->pred; n--;
	}
}

template <typename T> //对列表中起始于位置p、宽度为n的区间做插入排序
void List<T>::insertionSort(ListNodePosi<T> p, Rank n)// valid(p) && Rank(p) + n <= size
{
	for (Rank r = 0; r < n; r++) //逐一为各节点
	{
		insert(search(p->data, r, p), p->data); //查找适当的位置并插入
		p = p->succ; remove(p->pred); //转向下一节点
	}
}

template <typename T> //复制列表中自位置p起的n项（assert: p为合法位置，且至少有n-1个后继节点）
List<T>::List(ListNodePosi<T> p, Rank n) { copyNodes(p, n); }

template <typename T> //整体复制列表L
List<T>::List(List<T> const& L) { copyNodes(L.first(), L._size); }

template <typename T> //复制L中自第r项起的n项（assert: r+n <= L._size）
List<T>::List(List<T> const& L, Rank r, Rank n)
{
	ListNodePosi<T> p = L.first();
	while (0 < r--) p = p->succ;
	copyNodes(p, n);
}

template <typename T> List<T>::~List() //列表析构器
{
	clear(); delete header; delete trailer; //清空列表，释放头、尾哨兵节点
}

template <typename T> //重载下标操作符，以通过秩直接访问列表节点（虽方便，效率低，需慎用）O(r)效率
ListNodePosi<T> List<T>::operator[](Rank r) const // assert: 0 <= r < size
{
	ListNodePosi<T> p = first(); //从首节点出发
	while (0 < r--) p = p->succ; //顺数第r个节点即是
	return p; //目标节点
}

template<typename T>
inline Rank List<T>::disordered() const
{
	Rank n = 0;
	ListNodePosi<T> p = first();
	for (; p != trailer; p = p->succ) //O(n)
		if (p->data > (p->succ)->data)//此时出现一个逆序
			n++; //记录下逆序
	return n;//当且仅当n=0时列表有序 
}

template <typename T> //在无序列表内节点p（可能是trailer）的n个（真）前驱中，找到等于e的最后者
ListNodePosi<T> List<T>::find(T const& e, Rank n, ListNodePosi<T> p) const
{
	while (0 < n--) //（0 <= n <= Rank(p) < _size）对于p的最近的n个前驱，从右向左
		if (e == (p = p->pred)->data) return p; //逐个比对，直至命中或范围越界
	return NULL; //p越出左边界意味着区间内不含e，查找失败
} //失败时，返回NULL

template <typename T> //在有序列表内节点p（可能是trailer）的n个（真）前驱中，找到不大于e的最后者
ListNodePosi<T> List<T>::search(T const& e, Rank n, ListNodePosi<T> p) const
{
	do  // 0 <= n <= Rank(p) < _size
	{
		p = p->pred; n--;  //从右向左  
	} while ((-1 != n) && (e < p->data)); //逐个比较，直至命中或越界  
	return p; //返回查找终止的位置
} //失败时，返回区间左边界的前驱（可能是header）——调用者可通过valid()判断成功与否

template <typename T> //从起始于位置p的n个元素中选出最大者
ListNodePosi<T> List<T>::selectMax(ListNodePosi<T> p, Rank n)
{
	ListNodePosi<T> max = p; //最大者暂定为首节点p
	for (ListNodePosi<T> cur = p; 1 < n; n--) //从首节点p出发，将后续节点逐一与max比较
		if (!lt((cur = cur->succ)->data, max->data)) //若当前元素不小于max，则
			max = cur; //更新最大元素位置记录
	return max; //返回最大节点位置
}

template <typename T> ListNodePosi<T> List<T>::insertAsFirst(T const& e)
{
	_size++; return header->insertAsSucc(e);// e当作首节点插入
}

template <typename T> ListNodePosi<T> List<T>::insertAsLast(T const& e)
{
	_size++; return trailer->insertAsPred(e);// e当作末节点插入
}

template <typename T> ListNodePosi<T> List<T>::insert(ListNodePosi<T> p, T const& e)
{
	_size++; return p->insertAsSucc(e);// e当作p的后继插入
}

template <typename T> ListNodePosi<T> List<T>::insert(T const& e, ListNodePosi<T> p)
{
	_size++; return p->insertAsPred(e);// e当作p的前驱插入
}

template <typename T> T List<T>::remove(ListNodePosi<T> p)//删除合法节点p，返回其数值
{
	T e = p->data; //备份待删除节点的数值（假定T类型可直接赋值）
	p->pred->succ = p->succ; p->succ->pred = p->pred; //后继、前驱
	delete p; _size--; //释放节点，更新规模
	return e; //返回备份的数值
}

template <typename T> void List<T>::sort(ListNodePosi<T> p, Rank n)
{ //列表区间排序
	switch (rand() % 3) { //随机选取排序算法。可根据具体问题的特点灵活选取或扩充
	case 1: insertionSort(p, n); break; //插入排序
	case 2: selectionSort(p, n); break; //选择排序
	default:     mergeSort(p, n); break; //归并排序
	}
}

template <typename T> Rank List<T>::deduplicate()
{
	Rank oldSize = _size; ListNodePosi<T> p = first();
	for (Rank r = 0; p != trailer; p = p->succ) //O(n)
		if (ListNodePosi<T> q = find(p->data, r, p))
			remove(q); //此时q与p雷同，但删除前者更为简明
		else r++; //r为无重前缀的长度
	return oldSize - _size; //删除元素总数
}

template <typename T> Rank List<T>::uniquify() //成批剔除重复元素，效率更高
{
	if (_size < 2) return 0; //平凡列表自然无重复
	Rank oldSize = _size; //记录原规模
	ListNodePosi<T> p = first(); ListNodePosi<T> q; //p为各区段起点，q为其后继
	while (trailer != (q = p->succ)) //反复考查紧邻的节点对(p, q)
		if (p->data != q->data) p = q; //若互异，则转向下一区段
		else remove(q); //否则（雷同）直接删除后者，不必如向量那样间接地完成删除
	return oldSize - _size; //列表规模变化量，即被删除元素总数
}

template <typename T> void List<T>::reverse()//前后倒置
{
	ListNodePosi<T> p = header; ListNodePosi<T> q = trailer; //头、尾节点
	for (Rank i = 1; i < _size; i += 2) //（从首、末节点开始）由外而内
		swap((p = p->succ)->data, (q = q->pred)->data); //交换对称节点的数据项
}

template <typename T> void List<T>::traverse(void (*visit)(T&)) //借助函数指针机制遍历
{
	for (ListNodePosi<T> p = header->succ; p != trailer; p = p->succ) visit(p->data);
}

template <typename T> template <typename VST> //元素类型、操作器
void List<T>::traverse(VST& visit) //借助函数对象机制遍历
{
	for (ListNodePosi<T> p = header->succ; p != trailer; p = p->succ) visit(p->data);
}
template <typename T>
ListNodePosi<T> ListNode<T>::insertAsPred(T const& e)
{
	ListNodePosi<T> x = new ListNode(e, pred, this);
	pred->succ = x; pred = x;
	return x;
}

template <typename T>
ListNodePosi<T> ListNode<T>::insertAsSucc(T const& e)
{
	ListNodePosi<T> x = new ListNode(e, this, succ);
	succ->pred = x; succ = x;
	return x;
}

