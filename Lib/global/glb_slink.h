#ifndef GLOBAL_SLINK_H
#define GLOBAL_SLINK_H

//#include <QtCore/QSemaphore>
//#include <QtCore/QtDebug>

// 定义单向链表数据元素
template<typename T>
struct SLinkItem{
    SLinkItem(const T & data = T()):_next(0), _data(data){}
    SLinkItem * _next;
    T _data;
};

// 定义单向链表数据结构
// 保存首尾指针，实现快速的从首部获取元素和快速的在首尾添加元素
template<typename T>
struct SLink{
    typedef SLinkItem<T> ItemType;

    SLink():_first(0),_last(0),_size(0){}

    SLinkItem<T> * first() const    {   return _first;  }
    SLinkItem<T> * last () const    {   return _last;   }
    SLinkItem<T> * first()     {   return _first;  }
    SLinkItem<T> * last ()     {   return _last;   }

    /* 将item->_next = 0;移到if(_first)范围内，避免空链时错误，mofi 20150129. */
    SLinkItem<T> * takeFirst()
    {
        SLinkItem<T> * item = _first;
        if(_first)
        {
            if(_last == _first)
                _first = _last = 0;
            else
                _first = _first->_next;
            item->_next = 0;
            _size --;
        }
        return item;
    }

    unsigned int size() const
    {   return _size;   }
    bool isEmpty() const
    {   return (_first == 0);  }
    bool check() const
    {
        unsigned int checkSize = 0;
        for(SLinkItem<T> * item = _first; item; item = item->_next)
            checkSize++;
        return checkSize == size();
    }

    void append(SLinkItem<T> * item)
    {
        if(_last)
        {   // insert to last
            _last->_next = item;
            _last = item;
        }
        else
        {   // insert to empty link
            _first = _last = item;
        }
        item->_next = 0;

        _size++;
    }

	void append(SLink<T> * slink)
	{
        // check empty
        if(slink->isEmpty())
            return;

        if(_last)
        {   // insert to last
			_last->_next = slink->first();
        }
        else
        {   // insert to empty link
            _first = slink->first();
        }
			
		_last = slink->last();
		slink->_first = slink->_last = 0;

        _size += slink->size();
	}

    void prepend(SLinkItem<T> * item)
    {
        if(_first)
        {   // insert to first
            item->_next = _first;
            _first = item;
        }
        else
        {   // insert to empty link
            _first = _last = item;
            item->_next = 0;
        }

        _size ++;
    }

    void prepend(SLink<T> * slink)
    {
        // check empty
        if(slink->isEmpty())
            return;

        if(_first)
        {   // insert to first
            slink->_last->_next = _first;
        }
        else
        {   // insert to empty link
             _last = slink->_last;
        }

		_first = slink->_first;
		slink->_first = slink->_last = 0;

        _size += slink->size();
    }

	void clear()
	{
		_first = _last = _size = 0;
	}
	
    SLinkItem<T> * _first;
    SLinkItem<T> * _last;
    unsigned int   _size;
};

// 使用单向链表实现的数据池对象
template<typename T>
struct DataPool
{
    DataPool(unsigned char autoApply = 1, const int count = 500)
        :_autoApplyData(autoApply),_capacity(0)
    {
        applyData(count);
    }

    // 分配数据对象
    void applyData(const int count = 500)
    {
        _capacity += count;
        //SLinkItem<T>* pitems = new SLinkItem<T>[count];
        for(int i=0; i<count; i++)
            _dataLink.append(new SLinkItem<T>);
            //_dataLink.append(&pitems[i]);
        //_memeryPitch.append(pitems);
    }

    // 申请一个数据对象
    SLinkItem<T>* alloc()
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
    void free(SLinkItem<T>* item)
    {
        _dataLink.append(item);
    }

    // 释放一组数据对象到数据池中
    void free(SLink<T>* slink)
    {
        _dataLink.append(slink);
    }

	// 释放申请的内存对象
	void clear()
	{
        SLinkItem<T>* item = _dataLink.first(), *item_next = 0;
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
	
    // 获取数据池容量
    unsigned int capacity() const
    {   return _capacity;           }
    unsigned int size() const
    {   return _dataLink.size();    }
    bool check() const
    {   return _dataLink.check();   }

    //SLink<T> _memeryPitch;
    SLink<T> _dataLink;
    unsigned char   _autoApplyData;
    unsigned int    _capacity;
};

// 环形缓存区
template<typename T, int MaxSize>
struct RingBuffer
{
#define NextIndex(idx) (idx+1)%MaxSize
#define PrevIndex(idx) (idx+MaxSize-1)%MaxSize

    RingBuffer():_maxSize(MaxSize),_rindex(0),_windex(0){}

    // 添加数据，调用者确保缓存区非满
    void push(const T & data)
    {
//        if(!__tryCheckFreeSize(1))
//            return;

        _buffer[_windex] = data;
        _windex = NextIndex(_windex);
    }

    void push(const T * lpdata, int length)
    {
//        if(!__tryCheckFreeSize(length))
//            return;

        int wi = _windex;
        for(int i=0; i<length; i++)
        {
            _buffer[wi] = lpdata[i];
            wi = NextIndex(wi);
        }
        _windex = wi;
    }

    // 取出最早放入的数据
    const T & pop()
    {
        const T & data = _buffer[_rindex];
        _rindex = NextIndex(_rindex);
        return data;
    }

    // 释放一个数据
    void removeLast()
    {
        if(!isEmpty()){
            _rindex = NextIndex(_rindex);
        }
    }

    void reset()
    {
        _rindex = _windex = 0;
    }

    const T & dataTop(int index=0) const
    {
        const int dataIdx = (_windex+MaxSize-index-1)%MaxSize;
        return _buffer[dataIdx];
    }

    const T & dataBottom(int index=0) const
    {
        const int dataIdx = (_rindex+index)%MaxSize;
        return _buffer[dataIdx];
    }

    int size() const
    {   return (_windex >= _rindex ? _windex-_rindex : _maxSize+_windex-_rindex); }
    int freeSize() const
    {   return _maxSize - 1 - size();   }
    bool isEmpty() const
    {   return (_windex == _rindex);   }
    bool isFull() const
    {   return (NextIndex(_windex) == _rindex); }

    bool __tryCheckFreeSize(const int datasize)
    {
        if(freeSize() <= datasize)
        {
//            QSemaphore sem(0);
//            int tryCount = 50;
//            while(tryCount > 0 && freeSize() <= datasize)
//            {
//                sem.tryAcquire(1, 1);
//                tryCount --;
//            }

            if(freeSize() <= datasize){
                //qDebug() << __FUNCTION__ << "is full...";
                return false;
            }
        }
        return true;
    }

    T   _buffer[MaxSize];
    int _rindex, _windex;
    int _maxSize;
};

template<typename T, int MaxSize>
struct RingStore
{
#define NextIndex(idx) (idx+1)%MaxSize
#define PrevIndex(idx) (idx+MaxSize-1)%MaxSize
    enum {Size = MaxSize };

    RingStore():_windex(0){}

    // 添加数据,返回存放数据的位置索引
    int push(const T & data)
    {
        _buffer[_windex] = data;
        _windex = NextIndex(_windex);
        return PrevIndex(_windex);
    }
    // 添加数据，返回最后一个数据的存放位置索引
    int push(const T * lpdata, int length)
    {
        int wi = _windex;
        for(int i=0; i<length; i++)
        {
            _buffer[wi] = lpdata[i];
            wi = NextIndex(wi);
        }
        _windex = wi;
        return PrevIndex(_windex);
    }
    // 取最近的index数据
    T & data(int index=0)
    {
        const int dataIdx = (_windex+MaxSize-index-1)%MaxSize;
        return _buffer[dataIdx];
    }
    const T & data(int index=0) const
    {
        const int dataIdx = (_windex+MaxSize-index-1)%MaxSize;
        return _buffer[dataIdx];
    }
    // 取指定索引位置的数据
    const T & dataAt(int index) const
    {
        return _buffer[index];
    }

    int prevIndex(int idx) const{
        return PrevIndex(idx);
    }
    int nextIndex(int idx) const {
        return NextIndex(idx);
    }

//    int maxSize() const{
//        return MaxSize;
//    }

    T   _buffer[MaxSize];
    int _windex;
};

#endif // GLOBAL_SLINK_H
