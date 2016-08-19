//Sequence.h
#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <string>

typedef std::string ItemType;

class Sequence
{
  private:
    int m_nSize;
    struct Node
    {
        ItemType m_data;
        int m_nPosition;
        Node* pNext;
        Node* pPrev;
    };

    Node* pHead;

    void eraseData(int pos);
  public:
    void dump() const;
    Sequence();
    Sequence(const Sequence& cSource);
    Sequence& operator=(const Sequence& cSource);
    ~Sequence();
    bool empty() const;
    int size() const;
    bool insert(int pos, const ItemType& value);
    bool insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);
#endif