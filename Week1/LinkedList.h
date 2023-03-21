#pragma once
#include <iterator>

//可以考虑让这个类的使用更优雅一点
//不想折腾的删除这个定义
#define LL_ITERATOR_FEATURE ///可选 [迭代器]

template<class T>

class LinkedList
{
	//...
	struct Node
	{
		T data{};
		Node* next{};
		Node* prev{};
		
	};
	Node* m_head{};
	Node* m_tail{};
	int m_add;//当前位置
	int m_length;//链表长度
	//向后插入
	T*_InsertAfter(const T&data,Node*p_Node){
		//创建临时结点
		Node*newnode=new Node;
		newnode->data=data;
		if(m_head)//判断头节点是否创建
		{
			//插入链表
			newnode->next=p_Node->next;
			//插入结点下一个位置为空则更新m_tail位置和m_length的值，否则连接结点
			if(p_Node->next)
			   p_Node->next->pre=newnode;
			else
				m_tail=newnode;
			p_Node->next = newnode;
			newnode->prev =p_Node;
			m_length++;
		}
		else
		{
			//创建第一节点
			newnode->next = nullptr;
			newnode->prev = nullptr;
			m_head = m_tail = newnode;
			m_length = 1;
		}
		return &newnode->data;
	}
	//向前插入
	T* _InsertBefore(const T& data, Node* p_Node)
	{
		Node* newnode = new Node;
		newnode->data = data;
		
		if (m_head)
		{
			newnode->prev = p_node->prev;
			//插入结点前一个位置为空则更新m_head位置和m_length的值，否则连接结点
			if (p_Node != m_front)
				p_Node->prev->next = newnode;
			else
				m_head = newnode;
			p_Node->prev = newnode;
			newnode->next = p_Node;
			m_length++;
		}
		else
		{
			//创建第一节点
			newnode->next = nullptr;
			newnode->prev = nullptr;
			m_head = m_tail = newnode;
			m_length = 1;
		}
		return &newnode->data;
	}
public:
#ifdef LL_ITERATOR_FEATURE
	class iterator
	{
	private:
		//...
	public:
		using iterator_concept = std::bidirectional_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		//重新定义运算符，能在类内使用运算符
		reference operator*() const;
		pointer operator->() const;
		iterator& operator++();
		iterator operator++(int);
		iterator& operator--();
		iterator operator--(int);
		bool operator==(const iterator& other) const;
		bool operator!=(const iterator& other) const;
		reference operator[](difference_type  i) const;
		auto operator<=>(const iterator&) const = default;
	};

	iterator begin();
	iterator end();
	iterator rbegin();
	iterator rend();
#endif

public:
	LinkedList();
	~LinkedList();

	T& operator[](int i);
#ifdef LL_ITERATOR_FEATURE
	//default insert after iter
	void Insert(const T& val, const iterator& iter, bool insert_prev = false);
	iterator Erase(const iterator& iter);
#else
	//default insert after node
	void Insert(const T& val, T* node, bool insert_prev = false);
	T* Erase(T* node);
#endif

	T& Front(){return m_head->data;};
	T& Back(){return m_back->data};
	void PushFront(const T& val){_InsertLine(val,m_head)};
	void PushBack(const T& val){_InsertLine(val,m_tail)};
	void PopFront();
	void PopBack();

	size_t Count(){return m_length};
	bool Empty();

	void Clear();

	//... other methods
};