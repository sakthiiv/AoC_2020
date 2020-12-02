#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct node
{
    int key;
    struct node *left, *right;
};

struct node *newNode(int item)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

struct node *insert(struct node *node, int key)
{
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);

    return node;
}

struct node *search(struct node *node, int key)
{
    if (node == NULL || key == node->key)
    {
        return node;
    }

    if (key < node->key)
    {
        return search(node->left, key);
    }
    return search(node->right, key);
}

void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        cout << root->key << " -> ";
        inorder(root->right);
    }
}

int part_one(int sum, vector<int> v)
{
    int result;
    struct node *root = NULL;

    for (int n : v)
    {
        root = insert(root, n);
    }

    for (int n : v)
    {
        struct node *resultNode = search(root, sum - n);
        if (resultNode)
        {
            result = n * resultNode->key;
            cout << result << endl;
            break;
        }
    }
    return result;
}

int part_two(int sum, vector<int> v)
{
    sort(v.begin(), v.end());
    int l, r, n, result = 0;
    n = v.size() - 1;

    //// Solution failed
    // for (unsigned i = 0; i < v.size(); i++)
    //     std::cout << ' ' << v.at(i);

    // std::cout << endl;

    // for (int i = 0; i < v.size() - 2; i++)
    // {
    //     l = i + 1;
    //     r = n;
    //     while (l < r)
    //     {
    //         if (v.at(i) == 297)
    //         {
    //             cout << "l & r: " << v.at(l) << " " << v.at(r) << " " << endl;
    //         }
    //         if (sum == (v.at(i) + v.at(l) + v.at(r)))
    //         {
    //             result = (v.at(i) * v.at(l) * v.at(r));
    //             cout << result << endl;
    //             return true;
    //         }
    //         else if (sum > (v.at(l) + v.at(r)))
    //             l++;
    //         else
    //             r--;
    //     }
    // }

    for (auto i = v.begin(); i + 2 != v.end(); ++i)
    {
        for (auto j = i + 1; j + 1 != v.end(); ++j)
        {
            int another = 2020 - *i - *j;
            if (std::binary_search(j + 1, v.end(), another))
            {
                result = *i * *j * another;
                return result;
            }
        }
    }

    return result;
}

int main()
{
    int sum = 2020;
    int result;
    std::ifstream f("inputs/Day01.txt");

    std::vector<int> v{std::istream_iterator<int>(f), {}};
    result = part_two(sum, v);
    cout << result << endl;
}