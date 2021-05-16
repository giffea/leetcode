#include <iostream>
#include <vector>
using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
private:
    vector<int> output;

public:
    Solution() = default;

    vector<int> inorderTraversal(TreeNode* root) {
        output.clear();
        travel(root);
        return output;
    }

    void travel(TreeNode* root) {
        if (root) {
            if (root->left) {
                travel(root->left);
            }
            output.push_back(root->val);

            if (root->right) {
                travel(root->right);
            }
        }
    }
};

void runAndPrint(Solution& sol, TreeNode* root)
{
    auto result = sol.inorderTraversal(root);
    for (auto val : result) {
        cout << val << ' ';
    }
    cout << endl;
}

int main()
{
    cout << "haha" << endl;
    // case1:
    TreeNode* case1 = new TreeNode{1};
    auto now = case1->right = new TreeNode{2};
    now->left = new TreeNode{3};

    // case2:
    TreeNode* case2 = nullptr;

    // case3:
    TreeNode* case3 = new TreeNode{1};

    // case4: 
    TreeNode* case4 = new TreeNode{1};
    case4->left = new TreeNode{2};

    // case5: 
    TreeNode* case5 = new TreeNode{1};
    case5->right = new TreeNode{2};

    Solution sol;
    runAndPrint(sol, case1);
    runAndPrint(sol, case2);
    runAndPrint(sol, case3);
    runAndPrint(sol, case4);
    runAndPrint(sol, case5);
    
    return 0;
}