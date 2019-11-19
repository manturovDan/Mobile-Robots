#ifndef D_MULTISET_H
#define D_MULTISET_H

#include <iostream>

namespace std {
    template <class key>
    class less;

    template <class VertexType, class elemType>
    class tree_iterator {
    protected:
        mutable VertexType * pointer;

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
            return pointer->getElem();
        }

    };

    template <class VertexType, class elemType>
    class forward_iterator : public tree_iterator<VertexType, elemType> {
        using tree_iterator<VertexType, elemType>::pointer;
    public:
        explicit forward_iterator(VertexType *pntr = nullptr) : tree_iterator<VertexType, elemType>() { pointer = pntr; } // HOW TO DO NICE???

        /*const_forward_iterator & operator++() { //prefix
            VertexType * next = successor();
            pointer = next;
            return *this;
        }*/

        forward_iterator operator++(int) const { //postfix
            forward_iterator retIt(pointer);
            pointer = retIt.successor();
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
        };

        Vertex * top; //vertex
        size_t elCount;


    public:
        dmultiset() : top(nullptr), elCount(0) {}

        bool empty () const { return !elCount; }
        size_t count() const { return elCount; }
        size_t max_size() const { /* I DONT KNOW HOW TO DO IT */}

        typedef forward_iterator<Vertex, elemType> iterator;

        iterator begin() {
            Vertex * pntr = top;
            while(pntr->getLeftChild() != nullptr)
                pntr = pntr->getLeftChild();
            iterator iter(pntr);
            return iter;
        }

        iterator end() {
            iterator iter;
            return iter;
        }

        iterator insert(elemType newVal) {
            iterator iter(top);
            Vertex * newVer = new Vertex(newVal);

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

        void printTree() {
            walkVertexOUT(top);
        }

        void walkVertexOUT(Vertex * ver) {
            if (ver != nullptr) {
                walkVertexOUT(ver->getLeftChild());

                std::cout << "Element: " << ver->getElem() << std::endl;
                std::cout << "Address: " << ver << std::endl;
                std::cout << "Left: " << ver->getLeftChild() << std::endl;
                std::cout << "Right: " << ver->getRightChild() << std::endl;
                std::cout << "Parent: " << ver->getParent() << std::endl << std::endl;

                walkVertexOUT(ver->getRightChild());
            }
        }
    };


}
#endif //D_MULTISET_H
