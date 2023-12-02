// struct TreeNode {
//     int val;
//     TreeNode *left;
//     TreeNode *right;
//     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
// };
// // 
// TreeNode* deleteNode(TreeNode* root, int key) {
//     if (!root) {
//         return NULL;
//     }

//     if (key < root->val) {
//         root->left = deleteNode(root->left, key);
//     } else if (key > root->val) {
//         root->right = deleteNode(root->right, key);
//     } else {
//         if (!root->left) {
//             return root->right;
//         }
//         if (!root->right) {
//             return root->left;
//         }

//         TreeNode* min_node = findMin(root->right);
//         root->val = min_node->val;
//         root->right = deleteNode(root->right, min_node->val);
//     }

//     return root;
// }

// TreeNode* findMin(TreeNode* node) {
//     while (node->left) {
//         node = node->left;
//     }
//     return node;
// }
