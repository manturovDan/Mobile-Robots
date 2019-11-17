#ifndef MY_MULTIMAP_H
#define MY_MULTIMAP_H

namespace std {
    template <class key>
    class less;

    template <class VertexType>
    class forward_iterator {
    public:
        forward_iterator() = default;
        forward_iterator(VertexType *pntr) { pointer = pntr; }
        forward_iterator(const forward_iterator &) = default;
        forward_iterator(forward_iterator &&) noexcept = default;

        forward_iterator minElem () {
            while(pointer->leftChild != nullptr)
                pointer = pointer->leftChild;
            return *this;
        }

    private:
        VertexType * pointer;
    };

    template <class elemType, class compare = std::less<elemType> >
    class multiset {
    private:
        class Vertex {
        private:
            Vertex () = default;
            elemType * elem;
            Vertex * leftChild;
            Vertex * rightChild;
            Vertex * parent;
            bool color; //red - true, black - false
        };

        Vertex * top; //vertex
        int elCount;


    public:
        multiset() : top(nullptr), elCount(0) {}

        bool empty () const { return !elCount; }
        size_t count() const { return elCount; }
        size_t max_size() const { /* I DONT KNOW */}

        typedef forward_iterator<Vertex> iterator;

        iterator begin() {
            auto iter(top);
            return iter.minElem();
        }
    };


}
#endif //MY_MULTIMAP_H
