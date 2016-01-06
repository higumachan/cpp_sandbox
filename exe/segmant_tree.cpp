#include <iostream>

template<typename Target>
class SegmentTree {
public:
    SegmentTree(int _size)
        : tree_nodes(_size), 
        size(_size) {}
    SegmentTree(std::vector<Target> array);
    
    void set_value(int index, const Target& value);
    void set_value_detail(int index, int tree_index, const Target& value, int size);
    Target eval(int start_index, int end_index);
    Target eval_detail(int start_index, int end_index, int tree_index, int size);
private:
    std::vector<Target> tree_nodes;
    int size;
};

SegmentTree::SegmentTree(std::vector<Target> array) 
    tree_nodes(array.size() * 2), size(array.size())
{
}


void SegmentTree::set_value(int index, const Target& value)
{
    set_value_detail(index, 0, value, size);
}

void SegmentTree::set_value_detail(int index, int tree_index, const Target& value, int size)
{
    if (tree_index >= tree_nodes){
        return;
    }
    tree_nodes[tree_index] += value;

    if (index < size / 2){
        set_value_detail(index, (tree_index * 2) + 1, value, size / 2);
    }
    else {
        set_value_detail(index - size / 2, (tree_index * 2) + 2, value, size - size / 2);
    }
}

Target eval(int start_index, int end_index)
{
    
}

