#ifndef D_MULTISET_H
#define D_MULTISET_H

#include <iostream>

namespace std {
    template <class key>
    class less;

    template <class VertexType>
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
        forward_iterator(VertexType *pntr) { pointer = pntr; }
        forward_iterator(const forward_iterator &) = default;
        forward_iterator(forward_iterator &&) noexcept = default;

        forward_iterator & minElem () {
            while(pointer->leftChild != nullptr)
                pointer = pointer->leftChild;
            return *this;
        }

        forward_iterator & maxElem () {
            pointer = nullptr;
            return *this;
        }

        VertexType * findParentForNew(VertexType *newVer) {
            VertexType * y = nullptr;
            VertexType * x = pointer;
            while (x != nullptr) {
                y = x;
                if (newVer->elem < x->elem) {
                    x = x->leftChild;
                }
                else {
                    x = x->rightChild;
                }
            }
            return y;
        }

        void walkVertexOUT(VertexType * ver, std::ostream & stream = std::cout) { //DEBUG METHOD
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

        forward_iterator & operator++() {
            VertexType * next = successor(pointer);
            pointer = next;
            return *this;
        }

        forward_iterator operator++(int) const { //postfix
            forward_iterator retIt(pointer);
            VertexType * suc = retIt.successor(pointer);
            retIt.pointer = suc;
            return retIt;
        }
        //and *, +, -, =

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
        size_t max_size() const { /* I DONT KNOW */}

        typedef forward_iterator<Vertex> iterator;

        iterator begin() {
            auto iter(top);
            return iter.minElem();
        }

        iterator end() {
            auto iter(top);
            return iter.maxElem();
        }

        iterator insert(elemType newVal) {
            forward_iterator iter(top);
            Vertex * newVer = new Vertex(newVal);
            Vertex * parent = iter.findParentForNew(newVer);
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
            forward_iterator iter(top);
            iter.walkVertexOUT(top);
        }
    };


}
#endif //D_MULTISET_H
