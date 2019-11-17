#ifndef MY_MULTIMAP_H
#define MY_MULTIMAP_H

namespace std {
    template <class key>
    class less;

    template <class elemType, class compare = std::less<elemType> >
    class multimap {
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
    };
}
#endif //MY_MULTIMAP_H
