#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// ------------------------------ PART 1: Min-Priority Queue with Min-Heap ------------------------------
class MinHeap {
private:
    vector<int> heap;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void heapifyDown(int i) {
        int smallest = i;
        int left = leftChild(i);
        int right = rightChild(i);

        if (left < heap.size() && heap[left] < heap[smallest])
            smallest = left;
        if (right < heap.size() && heap[right] < heap[smallest])
            smallest = right;
        
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }

    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)] > heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

public:
    void minHeapInsert(int key) {
        heap.push_back(key);
        heapifyUp(heap.size() - 1);
    }

    int heapMinimum() {
        return heap.empty() ? INT_MAX : heap[0];
    }

    int heapExtractMin() {
        if (heap.empty()) return INT_MAX;

        int minVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return minVal;
    }

    void heapDecreaseKey(int i, int newValue) {
        if (newValue > heap[i]) {
            cout << "New key is greater than current key!" << endl;
            return;
        }
        heap[i] = newValue;
        heapifyUp(i);
    }

    void printHeap() {
        for (int val : heap) cout << val << " ";
        cout << endl;
    }
};

// ------------------------------ PART 2: Heapsort Algorithm ------------------------------
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = n / 2 - 1; i >= 0; i--) 
        heapify(arr, n, i);
    
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// ------------------------------ PART 3: Find Largest Element in Unsorted Array ------------------------------
int findLargest(vector<int>& arr) {
    int maxVal = arr[0];
    for (int num : arr) {
        if (num > maxVal) maxVal = num;
    }
    return maxVal;
}

// ------------------------------ PART 4: Convert BST to Min-Heap ------------------------------
class TreeNode {
public:
    int key;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) {
        key = value;
        left = right = nullptr;
    }
};

void storeInOrder(TreeNode* root, vector<int>& arr) {
    if (!root) return;
    storeInOrder(root->left, arr);
    arr.push_back(root->key);
    storeInOrder(root->right, arr);
}

void convertToMinHeap(TreeNode* root, vector<int>& arr, int& index) {
    if (!root) return;
    root->key = arr[index++];
    convertToMinHeap(root->left, arr, index);
    convertToMinHeap(root->right, arr, index);
}

void printPreOrder(TreeNode* root) {
    if (!root) return;
    cout << root->key << " ";
    printPreOrder(root->left);
    printPreOrder(root->right);
}

TreeNode* insertBST(TreeNode* root, int key) {
    if (!root) return new TreeNode(key);
    if (key < root->key) root->left = insertBST(root->left, key);
    else root->right = insertBST(root->right, key);
    return root;
}

// ------------------------------ MAIN FUNCTION ------------------------------
int main() {
    // PART 1: Min-Heap Operations
    MinHeap h;
    h.minHeapInsert(10);
    h.minHeapInsert(5);
    h.minHeapInsert(20);
    h.minHeapInsert(2);
    
    cout << "Min Heap: ";
    h.printHeap();

    cout << "Minimum Element: " << h.heapMinimum() << endl;

    cout << "Extract Min: " << h.heapExtractMin() << endl;
    h.printHeap();

    h.heapDecreaseKey(1, 1);
    cout << "After Decrease Key: ";
    h.printHeap();

    cout << "--------------------------------------" << endl;

    // PART 2: HeapSort Algorithm
    vector<int> arr = {10, 7, 15, 30, 2, 5};
    heapSort(arr);
    
    cout << "Sorted in Descending Order: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    cout << "--------------------------------------" << endl;

    // PART 3: Find Largest Element in Unsorted Array
    vector<int> arr2 = {10, 7, 15, 30, 2, 5};
    cout << "Largest Element in Array: " << findLargest(arr2) << endl;

    cout << "--------------------------------------" << endl;

    // PART 4: Convert BST to Min-Heap
    TreeNode* root = nullptr;
    root = insertBST(root, 10);
    root = insertBST(root, 5);
    root = insertBST(root, 15);
    root = insertBST(root, 2);
    root = insertBST(root, 7);

    vector<int> inOrderValues;
    storeInOrder(root, inOrderValues);

    int index = 0;
    convertToMinHeap(root, inOrderValues, index);

    cout << "Pre-order Traversal of Min-Heap: ";
    printPreOrder(root);
    cout << endl;

    return 0;
}