#ifndef D_MULTISET_H
#define D_MULTISET_H

#include <stdlib.h>

namespace std {

    template <class VertexType, class elemType>
    class tree_iterator {
    protected:
        VertexType * pointer; //not work without mutable

        VertexType * successor() {
            return successor(pointer);
        }

        VertexType * successor(VertexType * target) {
            if (target->getRightChild() != nullptr)
                return findMinElem(target->getRightChild());
            VertexType * y = target->getParent();
            while (y != nullptr && target == y->getRightChild()) {
                target = y;
                y = y->getParent();
            }
            return y;
        }

        VertexType * findMinElem(VertexType * verPrt) {
            while(verPrt->getLeftChild() != nullptr)
                verPrt = verPrt->getLeftChild();
            return verPrt;
        }

        VertexType * predecessor() {
            return predecessor(pointer);
        }

        VertexType * predecessor(VertexType * target) {
            if (target->getLeftChild() != nullptr)
                return findMaxElem(target->getLeftChild());
            VertexType * y = target->getParent();
            while (y != nullptr && target == y->getLeftChild()) {
                target = y;
                y = y->getParent();
            }
            return y;
        }

        VertexType * findMaxElem(VertexType * verPrt) {
            while(verPrt->getRightChild() != nullptr)
                verPrt = verPrt->getRightChild();
            return verPrt;
        }

    public:
        friend bool operator==(const tree_iterator &lft, const tree_iterator &rgh) {
            if (lft.pointer == rgh.pointer)
                return true;
        }

        friend bool operator!=(const tree_iterator &lft, const tree_iterator &rgh) {
            if (lft.pointer != rgh.pointer)
                return true;
        }

        elemType operator * () {
            if (pointer == nullptr) {
                throw std::invalid_argument("input of non-exist iterator"); //WHAT TO DO THERE????
            }
            return pointer->getElem();
        }

        VertexType * getVerPointer() {
            return pointer;
        }

    };

    template <class VertexType, class elemType>
    class forward_iterator : public tree_iterator<VertexType, elemType> {
        using tree_iterator<VertexType, elemType>::pointer;
        using tree_iterator<VertexType, elemType>::successor;
    public:
        explicit forward_iterator(VertexType *pntr = nullptr) : tree_iterator<VertexType, elemType>() { pointer = pntr; } // HOW TO DO NICE???

        forward_iterator & operator++() { //prefix
            VertexType * next = successor();
            pointer = next;
            return *this;
        }

        forward_iterator operator++(int) { //postfix
            forward_iterator retIt(pointer);
            pointer = retIt.successor();
            return retIt;
        }
    };

    template <class VertexType, class elemType>
    class back_iterator : public tree_iterator<VertexType, elemType> {
        using tree_iterator<VertexType, elemType>::pointer;
        using tree_iterator<VertexType, elemType>::predecessor;
    public:
        explicit back_iterator(VertexType *pntr = nullptr) : tree_iterator<VertexType, elemType>() { pointer = pntr; } // HOW TO DO NICE???

        back_iterator & operator++() { //prefix
            VertexType * next = predecessor();
            pointer = next;
            return *this;
        }

        back_iterator operator++(int) { //postfix
            back_iterator retIt(pointer);
            pointer = retIt.predecessor();
            return retIt;
        }
    };

    template <class elemType, class compare = std::less<elemType> >
    class dmultiset {
    private:
        class Vertex {
        private:
            Vertex() = default;
            elemType elem;
            Vertex *leftChild;
            Vertex *rightChild;
            Vertex *parent;
            //bool color; //red - true, black - false

        public:
            Vertex(elemType &newEl) : elem(newEl), leftChild(nullptr), rightChild(nullptr), parent(nullptr) {}
            elemType getElem() { return elem; }
            elemType & getElemLink() { return elem; }
            Vertex * getLeftChild() { return leftChild; }
            Vertex * getRightChild() { return rightChild; }
            Vertex * getParent() { return parent; }

            void setLeftChild(Vertex * lc) { leftChild = lc; }
            void setRightChild(Vertex * rc) { rightChild = rc; }
            void setParent(Vertex * pp) { parent = pp; }
            void setElem(Vertex * y) { elem = y->getElem(); }
        };

        Vertex * top; //vertex
        size_t elCount;


    public:
        dmultiset() : top(nullptr), elCount(0) {}

        dmultiset(std::initializer_list<elemType> ilist) : top(nullptr), elCount(0) {
            insert(ilist);
        }

        dmultiset(const dmultiset & copy_st) {
            try {
                top = clone(copy_st.top, nullptr);
            } catch (std::bad_alloc &ba) {
                //std::cerr << "No memory" << std::endl;
                throw &ba;
            }

            elCount = copy_st.count();
        }

        dmultiset(dmultiset && move_st) noexcept : elCount(move_st.count()), top(move_st.top) {
            move_st.top = nullptr;
        }

        ~dmultiset() {
            clear();
            top = nullptr;
        }

        dmultiset &operator=(const dmultiset & copy_st) {
            clear();
            try {
                top = clone(copy_st.top, nullptr);
            } catch (std::bad_alloc &ba) {
                //std::cerr << "No memory" << std::endl;
                exit(EXIT_FAILURE);
            }
            elCount = copy_st.count();

            return *this;
        }

        dmultiset &operator=(dmultiset && move_st) {
            clear();
            top = move_st.top;
            elCount = move_st.count();
            move_st.top = nullptr;

            return *this;
        }

        Vertex * clone(Vertex * root, Vertex * parent) {
            if (root == nullptr)
                return nullptr;

            elemType newVal = root->getElem(); //copy
            Vertex *tmp;

            tmp = new Vertex(newVal);

            tmp->setParent(parent);

            tmp->setLeftChild(clone(root->getLeftChild(), tmp));
            tmp->setRightChild(clone(root->getRightChild(), tmp));


            return tmp;
        }

        bool empty () const { return !elCount; }
        size_t count() const { return elCount; }

        typedef forward_iterator<Vertex, elemType> iterator;
        typedef forward_iterator<Vertex, elemType> const_iterator;
        typedef back_iterator<Vertex, elemType> reverse_iterator;
        typedef back_iterator<Vertex, elemType> const_reverse_iterator;

    private:
        void findElByIter(Vertex * ver, iterator & it, Vertex *& target) {
            if (ver != nullptr) {
                if (target != nullptr)
                    return;

                findElByIter(ver->getLeftChild(), it, target);
                if (ver->getElem() == *it) {
                    target = ver;
                    return;
                }
                findElByIter(ver->getRightChild(), it, target);
            }
        }

    public:
        template <class IterType>
        IterType begin() const {
            Vertex * pntr = top;
            if (pntr == nullptr)
                return IterType(nullptr);
            while(pntr->getLeftChild() != nullptr)
                pntr = pntr->getLeftChild();
            IterType iter(pntr);
            return iter;
        }

        template <class IterType>
        IterType end() const {
            IterType iter;
            return iter;
        }

        template <class IterType>
        IterType rbegin() const {
            Vertex * pntr = top;
            while(pntr->getRightChild() != nullptr)
                pntr = pntr->getRightChild();
            IterType iter(pntr);
            return iter;
        }

        iterator begin() const {
            return begin<iterator>();
        }

        iterator end() const {
            return end<iterator>();
        }

        reverse_iterator rbegin() const {
            return rbegin<reverse_iterator>();
        }

        reverse_iterator rend() const {
            return end<reverse_iterator>();
        }

        const_iterator cbegin() const {
            return begin<const_iterator>();
        }

        const_iterator cend() const {
            return end<const_iterator>();
        }

        const_reverse_iterator crbegin() const {
            return rbegin<const_reverse_iterator>();
        }

        const_reverse_iterator crend() const {
            return end<const_reverse_iterator>();
        }

        iterator insert(const elemType & val) {
            iterator iter(top);
            elemType newVal = val; //copy
            Vertex * newVer;

            try {
                newVer = new Vertex(newVal);
            } catch (std::bad_alloc &ba) {
                //std::cerr << "No memory" << std::endl;
                throw &ba;
            }

            Vertex * parent = nullptr;
            Vertex * x = top;
            while (x != nullptr) {
                parent = x;
                if (newVer->getElem() < x->getElem()) {
                    x = x->getLeftChild();
                }
                else {
                    x = x->getRightChild();
                }
            }

            newVer->setParent(parent);

            if (parent == nullptr) {
                top = newVer;
            }
            else if (newVer->getElem() < parent->getElem())
                parent->setLeftChild(newVer);
            else
                parent->setRightChild(newVer);

            elCount++;
            return iter;
        }

        template<class InputIt>
        void insert(InputIt first, InputIt last) {
            InputIt current = first;
            while (current != last) {
                insert(*current);

                current++;
            }
        }

        void insert(std::initializer_list<elemType> ilist) {
            for (auto x : ilist) {
                insert(x);
            }
        }

        iterator erase(iterator pos) {
            Vertex * target = pos.getVerPointer();

            iterator retIt = pos;
            retIt++;

            Vertex * y = nullptr;
            Vertex * x = nullptr;
            if (target->getLeftChild() == nullptr || target->getRightChild() == nullptr) {
                y = target;
            }
            else {
                iterator retIt = pos;
                retIt++;
                y = retIt.getVerPointer();
            }

            if (y->getLeftChild() != nullptr) {
                x = y->getLeftChild();
            }
            else {
                x = y->getRightChild();
            }

            if (x != nullptr) {
                x->setParent(y->getParent());
            }

            if(y->getParent() == nullptr) {
                top = x;
            }
            else if (y == y->getParent()->getLeftChild()) {
                y->getParent()->setLeftChild(x);
            }
            else {
                y->getParent()->setRightChild(x);
            }

            if (y != target) {
                target->setElem(y);// make private method
            }

            delete y;

            elCount--;

            return iterator(target);
        }

        iterator find(const elemType & x) const {
            return search(x, top);
        }

        iterator search(const elemType& x, Vertex * goer) const {
            if (goer == nullptr || x == goer->getElem())
                return iterator(goer);
            if (x < goer->getElem())
                return search(x, goer->getLeftChild());
            else
                return search(x, goer->getRightChild());
        }

        void clear() noexcept {
            delVer(top);
            top = nullptr;
        }

        void delVer(Vertex * dv) {
            if (dv != nullptr) {
                delVer(dv->getLeftChild());
                delVer(dv->getRightChild());

                dv->setLeftChild(nullptr);
                dv->setRightChild(nullptr);
                dv->setParent(nullptr);
                delete dv;

                elCount--;
            }
        }
    };


}
#endif //D_MULTISET_H
