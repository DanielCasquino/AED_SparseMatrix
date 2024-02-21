#include <iostream>
#include <vector>
#include <unordered_map>

template <typename T = int>
class listlist_sparse_matrix
{
    struct HorizontalNode
    {
        int col;
        T data;
        HorizontalNode *next = nullptr;
        HorizontalNode(int col, T data) : col(col), data(data) {}
    };
    struct VerticalNode
    {
        int row;
        VerticalNode *below = nullptr;
        HorizontalNode *head = nullptr;
        VerticalNode(int row) : row(row) {}
    };

    VerticalNode *origin = nullptr;

public:
    listlist_sparse_matrix() {}

    void insert(int row, int col, T data)
    {
        // Base case, if vertical list is empty
        if (origin == nullptr)
        {
            origin = new VerticalNode(row);
            origin->head = new HorizontalNode(col, data);
        }
        else
        {
            VerticalNode *prevVertical = nullptr;
            VerticalNode *currVertical = origin;

            // Find correct position to insert the new row (should be ordered from top to bottom, like a matrix)
            while (currVertical != nullptr && currVertical->row < row)
            {
                prevVertical = currVertical;
                currVertical = currVertical->below;
            }

            // If the row doesn't exist, create it
            if (currVertical == nullptr || currVertical->row != row)
            {
                VerticalNode *newRow = new VerticalNode(row);
                newRow->below = currVertical;
                if (prevVertical != nullptr)
                {
                    prevVertical->below = newRow;
                }
                else
                {
                    origin = newRow;
                }
                currVertical = newRow;
            }

            // Insert the new element into the horizontal list in sorted order
            HorizontalNode *prevHorizontal = nullptr;
            HorizontalNode *currentHorizontal = currVertical->head;

            while (currentHorizontal != nullptr && currentHorizontal->col < col)
            {
                prevHorizontal = currentHorizontal;
                currentHorizontal = currentHorizontal->next;
            }

            // Insert new node
            if (prevHorizontal == nullptr)
            {
                currVertical->head = new HorizontalNode(col, data);
                currVertical->head->next = currentHorizontal;
            }
            else
            {
                prevHorizontal->next = new HorizontalNode(col, data);
                prevHorizontal->next->next = currentHorizontal;
            }
        }
    } // Holy mother of brain farts

    void remove(int row, int col)
    {
        if (origin == nullptr) // Base case
            return;
        else
        {
            // Vertical Search
            VerticalNode *prevV = nullptr;
            VerticalNode *v = origin; // It towards bottom

            while (v != nullptr && v->row != row)
            {
                prevV = v;
                v = v->below;
            }

            if (v == nullptr || v->head == nullptr) // Row not found or empty
                return;

            // Horizontal search
            HorizontalNode *prevH = nullptr;
            HorizontalNode *h = v->head;

            while (h != nullptr && h->col != col)
            {
                prevH = h;
                h = h->next;
            }
            if (h == nullptr) // Element not found in row
                return;

            if (prevH == nullptr) // First element in row
            {
                v->head = h->next;
                delete h;
            }
            else // Element in middle or end of row, splices accordingly
            {
                prevH->next = h->next;
                delete h;
            }

            if (v->head == nullptr) // Deletes row if empty
            {
                if (prevV == nullptr) // First row
                {
                    origin = v->below;
                }
                else
                {
                    prevV->below = v->below; // splices vertically
                }
                delete v;
            }
        }
    }

    void traverse()
    {
        VerticalNode *v = origin;
        while (v != nullptr)
        {
            HorizontalNode *h = v->head;
            std::cout << v->row << ": ";
            while (h != nullptr)
            {
                std::cout << '[' << v->row << "," << h->col << "," << h->data << ']' << " ";
                h = h->next;
            }
            v = v->below;
            std::cout << std::endl;
        }
    }
};

// TODO
// template <typename T = int>
// class hash_sparse_matrix
// {

// public:
//     hash_sparse_matrix(){};
// };

template <typename T = int>
class triple_vector_sparse_matrix
{
    std::vector<int> rows;
    std::vector<int> cols;
    std::vector<T> data;
    int sz = 0;

public:
    triple_vector_sparse_matrix() {}
    void insert(int row, int col, T dat)
    {
        rows.push_back(row);
        cols.push_back(col);
        data.push_back(dat);
        ++sz;
    }
    void remove(int row, int col)
    {
        for (int i = 0; i < sz; ++i)
        {
            if (rows[i] == row && cols[i] == col)
            {
                cols.erase(cols.begin() + i);
                rows.erase(rows.begin() + i);
                data.erase(data.begin() + i);
                --sz;
                return;
            }
        }
    }
    void traverse()
    {
        for (int i = 0; i < sz; ++i)
        {
            std::cout << '[' << rows[i] << "," << cols[i] << "," << data[i] << ']' << " ";
        }
    }
};

template <typename T = int>
class linked_list_sparse_matrix
{
    struct Node
    {
        int row, col;
        T data;
        Node *next = nullptr;
        Node(int row, int col, T data, Node *next = nullptr) : row(row), col(col), data(data), next(next) {}
    };

public:
    Node *head = nullptr;
    linked_list_sparse_matrix() {}
    void insert(int row, int col, T data)
    {
        if (head == nullptr)
        {
            head = new Node(row, col, data);
        }
        else
        {
            auto it = head;
            while (it->next != nullptr)
            {
                it = it->next;
            }
            it->next = new Node(row, col, data);
        }
    }

    void remove(int row, int col)
    {
        auto it = head;
        while (it->next != nullptr)
        {
            if (it->next->row == row && it->next->col == col)
            {
                auto rightAnchor = it->next->next;
                delete it->next;
                it->next = nullptr;
                it->next = rightAnchor;
                return;
            }
            it = it->next;
        }
    }

    void traverse()
    {
        auto it = head;
        while (it != nullptr)
        {
            std::cout << '[' << it->row << "," << it->col << "," << it->data << ']' << " ";
            it = it->next;
        }
    }
};