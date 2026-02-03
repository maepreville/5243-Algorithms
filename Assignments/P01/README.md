## Assignment 3 - BST Delete

**Write a short explanation (minimum 200 words)** covering:
   - The cases you handled for deletion.
   - The logic behind choosing a replacement value for nodes with two children.
   - Any challenges you faced while implementing deletion.

Three cases are handled in the code. The first case handles a leaf node. If there are no children, then the subroot is deleted. So this part checks if both subroot left and right is empty then the subroot is deleted. The second case handles deleting one child (left or right). If the subroot does not have a left child or if subroot->left is empty, the subroot is moved to the right and that node is deleted. The same is done if the subroot does not have a right child. The last (third) case handles two children. It checks to see which node has the smallest value in the tree. It then copies the value into the subroot which is the current node, overwriting whatever value was there, then deletes. When choosing a replacement value for nodes with two children, it is necessary to try to preserve the BST as much as possible. If one child is deleted, then linked up, it will break the ordering of the BST. With two children, no child can simply replace another. It is necessary to replace it with values that are able to maintain the BST order. The most challenging part was understanding why it was not as simple with nodes that had two children. Also, finding instances and testing where these  cases would be handled and run properly.
