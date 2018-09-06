#ifndef GLOBAL_DLINK_H_MOFI_20170306
#define GLOBAL_DLINK_H_MOFI_20170306


// 定义双向链表数据元素
template<typename T>
struct DLinkItem{
    DLinkItem(const T & data = T()):_prev(0),_next(0),_data(data){}
    DLinkItem *_prev, *_next;
    T _data;
};

// 定义双向链表数据结构
// 保存首尾指针，实现快速的从首部获取元素和快速的在首尾添加元素
template<typename T>
struct DLink{
    typedef DLinkItem<T> ItemType;

    DLink():_head(0),_tail(0),_size(0){}

    ItemType * head() const    {   return _head;  }
    ItemType * tail () const    {   return _tail;   }
    ItemType * head()     {   return _head;  }
    ItemType * tail ()     {   return _tail;   }

    /* 取链头对象 */
    ItemType * takeFirst()
    {
        ItemType * item = _head;
        if(_head)
        {
            if(_tail == _head){
                _head = _tail = 0;
            }
            else {
                _head = _head->_next;
                _head->_prev = 0;
            }
            item->_prev = item->_next = 0;
            _size --;
        }
        return item;
    }

    /* 取链尾对象 */
    ItemType * takeLast()
    {
        ItemType * item = _tail;
        if(_tail)
        {
            if(_tail == _head){
                _head = _tail = 0;
            }
            else {
                _tail = _tail->_prev;
                _tail->_next = 0;
            }
            item->_prev = item->_next = 0;
            _size --;
        }
        return item;
    }

    // 释放链中一个结点对象
    void release(ItemType * item)
    {
        if(item)
        {
            if(_head == item)
                takeFirst();
            else if(_tail == item)
                takeLast();
            else {
                item->_prev->_next = item->_next;
                item->_next->_prev = item->_prev;
                item->_prev = item->_next = 0;
                _size --;
            }
        }
    }

    void release(const T & data)
    {
        release(find(data));
    }

    // 取指定对象
    ItemType * take(ItemType * item)
    {
        release(item);
        return item;
    }

    // 根据值取链表元素对象
    ItemType * take(const T & data)
    {
        return take(find(data));
    }

    // 根据值查找链表元素对象
    ItemType * find(const T & data)
    {
        ItemType * item = _head;
        for(; item; item = item->_next)
        {
            if(data == item->_data)
                break;
        }
        return item;
    }

    unsigned int size() const
    {   return _size;   }
    bool isEmpty() const
    {   return (_head == 0);  }

    void append(ItemType * item)
    {
        item->_prev = item->_next = 0;
        if(_tail)
        {   // insert to tail
            _tail->_next = item;
            item->_prev = _tail;
            _tail = item;
        }
        else
        {   // insert to empty link
            _head = _tail = item;
        }

        _size++;
    }

    void append(DLink<T> * slink)
    {
        // check empty
        if(slink->isEmpty())
            return;

        if(_tail)
        {   // insert to tail
            _tail->_next = slink->_head;
            slink->_head->_prev = _tail;
            _tail = slink->_tail;
        }
        else
        {   // insert to empty link
            _head = slink->_head;
            _tail = slink->_tail;
        }

        _size += slink->size();
    }

    void prepend(ItemType * item)
    {
        item->_prev = item->_next = 0;
        if(_head)
        {   // insert to head
            item->_next = _head;
            _head->_prev = item;
            _head = item;
        }
        else
        {   // insert to empty link
            _head = _tail = item;
        }

        _size ++;
    }

    void prepend(DLink<T> * slink)
    {
        // check empty
        if(slink->isEmpty())
            return;

        if(_head)
        {   // insert to head
            slink->_tail->_next = _head;
            _head->_prev = slink->_tail;
            _head = slink->_head;
        }
        else
        {   // insert to empty link
            _head = slink->_head;
            _tail = slink->_tail;
        }

        _size += slink->size();
    }

    void clear()
    {
        _head = _tail = _size = 0;
    }

    ItemType * _head;
    ItemType * _tail;
    unsigned int   _size;
};

// 使用链表实现的数据池对象
template<typename Item, typename Link>
struct LinkItemPool
{
    typedef Item ItemType;
    typedef Link LinkType;

    LinkItemPool(unsigned char autoApply = 1)
        :_autoApplyData(autoApply),_capacity(0)
    {
    }

    // 分配数据对象
    void applyData(const int count = 500)
    {
        _capacity += count;
        for(int i=0; i<count; i++)
            _dataLink.append(new ItemType);
    }

    // 申请一个数据对象
    ItemType * alloc()
    {
        if(_dataLink.isEmpty())
        {
            if(_autoApplyData)
                applyData();
            else
                return 0;
        }
        return _dataLink.takeFirst();
    }

    // 判断数据池是否为空
    bool isEmpty() const
    {   return _dataLink.isEmpty(); }

    // 释放一个数据对象到数据池中
    void free(ItemType* item)
    {
        _dataLink.append(item);
    }

    // 释放一组数据对象到数据池中
    void free(LinkType* slink)
    {
        _dataLink.append(slink);
    }

    // 释放申请的内存对象
    void clear()
    {
        ItemType* item = _dataLink.first(), *item_next = 0;
        while(item)
        {
            item_next = item->_next;
            delete[] item;
            item = item_next;
        }
        //_memeryPitch.clear();
        _dataLink.clear();
        _capacity = 0;
    }

    void setAutoApply(unsigned char flag=1){
        _autoApplyData = flag;
    }

    // 获取数据池容量
    unsigned int capacity() const
    {   return _capacity;           }
    unsigned int size() const
    {   return _dataLink.size();    }

    //SLink<T> _memeryPitch;
    LinkType _dataLink;
    unsigned char   _autoApplyData;
    unsigned int    _capacity;
};

//template<typename T>
//typedef struct _LinkItemPool<T, SLinkItem<T>, SLink<T> > SLinkItemPool;
//template<typename T>
//typedef struct _LinkItemPool<T, DLinkItem<T>, DLink<T> > DLinkItemPool;

//typedef LinkItemPool<int, DLinkItem, DLink > DIntLinkItemPool;

#endif
