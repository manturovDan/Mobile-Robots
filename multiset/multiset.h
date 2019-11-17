#ifndef MY_MULTIMAP_H
#define MY_MULTIMAP_H

namespace std {
    template <class key>
    class less;

    class set_iterator {

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

        typedef set_iterator iterator;

    };


}
#endif //MY_MULTIMAP_H
