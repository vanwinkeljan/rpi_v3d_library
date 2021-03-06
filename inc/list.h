/* ============================================================================
Copyright (c) 2007-2014, Broadcom Corporation
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
3. Neither the name of the copyright holder nor the names of its contributors
   may be used to endorse or promote products derived from this software without
   specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
============================================================================ */

#ifndef _LIST_H_
#define _LIST_H_

#include <map>
#include "utils/Log.h"
#include <assert.h>

/*template <class T>
class Node {
public:
    Node(T obj, unsigned int key):mObject(obj),mKey(key),mNext(NULL),mPrev(NULL) {
    };
    ~Node() {
        if((mNext != NULL) || (mPrev != NULL)) {
            ALOGE("Node has valid Next and Prev in destructor");
        }
        mPrev = mNext = 0;
        mObject = 0; mKey = 0;
    };
    T get() { return mObject;};
    unsigned int getKey() { return mKey;};
    Node<T>* getNext() {return mNext;};
    Node<T>* getPrev() {return mPrev;};
    void remove() {
        if(mNext) mNext->mPrev = mPrev;
        if(mPrev) mPrev->mNext = mNext;
        mPrev =NULL;
        mNext = NULL;
    }
    void insert(Node<T>* node) {
        if(node->mPrev) node->mPrev->mNext = NULL;
        node->mPrev = this;
        if(mNext) {
            node->mNext = mNext;
            mNext->mPrev = node;
        }
        mNext = node;
    };
private:
    T mObject;
    unsigned int mKey;
    Node<T>* mNext;
    Node<T>* mPrev;
};

template <class T>
class List {
public:
    List() :mHead(NULL),mTail(NULL),mCount(0) {};
    ~List() {
        if(mHead) {
            ALOGE("List has valid Head in destructor");
        }
        if(mTail) {
            ALOGE("List has valid Tail in destructor");
        }
    };
    int getCount() { return mCount;};
    Node<T>* getHead() { return mHead;};
    Node<T>* getTail() { return mTail;};
    Node<T>* addElement(T obj,unsigned int key) {
        if(mHead) {
            Node<T>* prev = mHead;
            Node<T>* next = prev->getNext();
            if(prev->getKey() <= key ) {
                while(next) {
                    if( (prev->getKey() <= key) && (next->getKey() >= key)) break;
                    prev = next;
                    next = next->getNext();
                }
            prev->insert(new Node<T>(obj,key));
            prev = prev->getNext();
            } else {
                Node<T>* head  = new Node<T>(obj,key);
                head->insert(mHead);
                mHead = head;
                prev = mHead;
            }
            mCount++;
            if(mTail->getNext()) mTail = mTail->getNext();
            return prev;
        }
        else {
            mTail = mHead = new Node<T>(obj,key);
            mCount++;
            return mHead;
        }
    };
    // Unimplemented
    void removeElement(T obj) {
		Node<T>* node = mHead;
		while(node) {
			if(node->get() == obj) {
				removeNode(node);
				break;
			}
			node = node->getNext();
		}
    };
    void removeNode(Node<T>* node) {
        if(node == NULL) return;
        if( node == mHead) {
                mHead = mHead->getNext();
        }
        if( node == mTail ) {
                mTail = mTail->getPrev();
        }
        node->remove();
        delete node;
        mCount--;
    };
private:
    Node<T>* mHead;
    Node<T>* mTail;
    int mCount;
};*/

template <class T>
class List;


template <class T>
class Node {
public:
    Node(List<T> &rParent, T obj, unsigned int key)
	: mObject(obj),
	  mKey(key),
	  m_rParent(rParent)
	{
    };
    ~Node() {
        mObject = 0; mKey = 0;
    };
    T get() { return mObject;};
    unsigned int getKey() { return mKey;};
    Node<T>* getNext()
    {
    	typename std::map<unsigned int, Node<T> *>::iterator it;
    	it = m_rParent.m_map.find(getKey());

    	assert(it != m_rParent.m_map.end());
    	it++;

    	if (it == m_rParent.m_map.end())
    		return 0;
    	else
    		return it->second;
    };
    Node<T>* getPrev()
	{
		typename std::map<unsigned int, Node<T> *>::iterator it;
    	it = m_rParent.m_map.find(getKey());

    	assert(it != m_rParent.m_map.end());
    	it--;

    	if (it == m_rParent.m_map.end())
    		return 0;
    	else
    		return it->second;
	};

private:
    T mObject;
    unsigned int mKey;

    List<T> &m_rParent;
};

template <class T>
class List {
public:
    List()
	{
	}

    ~List()
    {
    }

    int getCount()
    {
    	return m_map.size();
    }

    Node<T>* getHead()
	{
    	typename std::map<unsigned int, Node<T> *>::iterator it;
    	it = m_map.begin();

    	if (it == m_map.end())
    		return 0;

    	return it->second;
	}

    Node<T>* getTail()
	{
    	typename std::map<unsigned int, Node<T> *>::reverse_iterator it;
    	it = m_map.rbegin();

    	if (it == m_map.rend())
    		return 0;

    	return it->second;
	}

    Node<T>* addElement(T obj, unsigned int key)
	{
    	Node<T> *p = new Node<T>(*this, obj, key);
    	m_map[key] = p;
    	return p;
	}

  /*  void removeElement(T obj)
    {
    }*/

    void removeNode(Node<T>* node)
    {
    	m_map.erase(node->getKey());
    }

    std::map<unsigned int, Node<T> *> m_map;
};

#endif
