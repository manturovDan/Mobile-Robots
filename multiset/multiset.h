#ifndef D_MULTISET_H
#define D_MULTISET_H

#include <iostream>

namespace std {
    template <class key>
    class less;

    template <class VertexType, class elemType>
    class forward_iterator {
    private:
        VertexType * pointer;

        VertexType * successor(VertexType * target) {
            if (target->rightChild != nullptr)
                return findMinElem(target->rightChild);
            VertexType * y = target->parent;
            while (y != nullptr && target == y->rightChild) {
                target = y;
                y = y->parent;
            }
            return y;
        }

        VertexType * findMinElem(VertexType * verPrt) {
            while(verPrt->leftChild != nullptr)
                verPrt = verPrt->leftChild;
            return verPrt;
        }

    public:
        forward_iterator() = default;
        explicit forward_iterator(VertexType *pntr) { pointer = pntr; }

        forward_iterator & operator++() { //prefix
            VertexType * next = successor();
            pointer = next;
            return *this;
        }

        forward_iterator operator++(int) const { //postfix
            forward_iterator retIt();
            VertexType * suc = retIt.successor(pointer);
            retIt.pointer = suc;
            return retIt;
        }

        elemType operator * () {
            return pointer->elem;
        }

        friend bool operator==(const forward_iterator &lft, const forward_iterator &rgh) {
            if (lft.pointer == rgh.pointer)
                return true;
        }

        friend bool operator!=(const forward_iterator &lft, const forward_iterator &rgh) {
            if (lft.pointer != rgh.pointer)
                return true;
        }

    };

    template <class elemType, class compare = std::less<elemType> >
    class dmultiset {
    private:
        class Vertex {
        private:
            Vertex() = default;

            bool color; //red - true, black - false

        public:
            Vertex(elemType &newEl) : elem(newEl), leftChild(nullptr), rightChild(nullptr), parent(nullptr) {}
            //go to public
            elemType elem;
            Vertex *leftChild;
            Vertex *rightChild;
            Vertex *parent;
        };

        Vertex * top; //vertex
        int elCount;


    public:
        dmultiset() : top(nullptr), elCount(0) {}

        bool empty () const { return !elCount; }
        size_t count() const { return elCount; }
        size_t max_size() const { /* I DONT KNOW HOW TO DO IT */}

        typedef forward_iterator<Vertex, elemType> iterator;

        iterator begin() {
            Vertex * pntr = top;
            while(pntr->leftChild != nullptr)
                pntr = pntr->leftChild;
            iterator iter(pntr);
            return iter;
        }

        iterator end() {
            return nullptr;
        }

        iterator insert(elemType newVal) {
            iterator iter(top);
            Vertex * newVer = new Vertex(newVal);

            Vertex * parent = nullptr;
            Vertex* x = top;
            while (x != nullptr) {
                parent = x;
                if (newVer->elem < x->elem) {
                    x = x->leftChild;
                }
                else {
                    x = x->rightChild;
                }
            }

            newVer->parent = parent;

            if (parent == nullptr) {
                top = newVer;
            }
            else if (newVer->elem < parent->elem)
                parent->leftChild = newVer;
            else
                parent->rightChild = newVer;

            return iter;
        }

        void printTree() {
            walkVertexOUT(top);
        }

        void walkVertexOUT(Vertex * ver) {
            if (ver != nullptr) {
                walkVertexOUT(ver->leftChild);

                std::cout << "Element: " << ver->elem << std::endl;
                std::cout << "Address: " << ver << std::endl;
                std::cout << "Left: " << ver->leftChild << std::endl;
                std::cout << "Right: " << ver->rightChild << std::endl;
                std::cout << "Parent: " << ver->parent << std::endl << std::endl;

                walkVertexOUT(ver->rightChild);
            }
        }
    };


}
#endif //D_MULTISET_H
