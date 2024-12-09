#include <iostream>
#include <limits>
#include <algorithm>

const int MAX_FRAGMENTS = 5;
struct Fraction {
    int numerator;
    int denominator;

    bool operator<(const Fraction& other) const {
        return static_cast<double>(numerator) / denominator > static_cast<double>(other.numerator) / other.denominator;
    }

    bool operator>(const Fraction& other) const {
        return !(*this < other);
    }
};

// Function to input fractions into an array
void inputFractions(Fraction* f, int maxCount, int& count) {
    count = 0;
    while (count < maxCount) {
        std::cout << "Enter numerator and denominator for fraction (" << (count + 1) << "/): ";
        std::cin >> f[count].numerator >> f[count].denominator;

        if (f[count].denominator == 0) {
            std::cout << "Error: Denominator cannot be zero. Please try again.\n";
            continue; // Ask for input again
        }

        ++count;
    }
}

// Function to output fractions from an array
void outputFractions(const Fraction* f, int count) {
    for (int i = 0; i < count; ++i) {
        std::cout << f[i].numerator << "/" << f[i].denominator << "\n";
    }
}

void copyArray(const Fraction* source, Fraction* destination, int count) {
    std::copy(source, source + count, destination);
}

// Bubble sort function
void bubbleSort(Fraction* f, int count) {
    int comparisons = 0;
    int swaps = 0;
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            ++comparisons;
            if (f[j] > f[j + 1]) {
                std::swap(f[j], f[j + 1]);
                ++swaps;
            }
        }
    }
    std::cout << "Bubble sort comparisons: " << comparisons << "\n";
    std::cout << "Bubble sort swaps: " << swaps << "\n";
}

// Insertion sort function
void insertionSort(Fraction* f, int count) {
    int comparisons = 0;
    int shift = 0;

    for (int i = 1; i < count; ++i) {
        Fraction key = f[i];
        int j = i - 1;

        // Compare and shift elements
        while (j >= 0) {
            ++comparisons;
            if (f[j] > key) {
                f[j + 1] = f[j];
                --j;
                ++shift;
            }
            else {
                break;
            }
        }
        f[j + 1] = key;
    }
    std::cout << "Insertion sort comparisons: " << comparisons << "\n";
    std::cout << "Insertion sort shifts: " << shift << "\n";
}

// Shell sort function
void shellSort(Fraction* f, int count) {
    int comparisons = 0;
    int swaps = 0;
    int gap = count / 2;

    while (gap > 0) {
        for (int i = gap; i < count; ++i) {
            Fraction temp = f[i];
            int j = i;

            // Compare elements and shift if necessary
            while (j >= gap && f[j - gap] > temp) {
                f[j] = f[j - gap];
                --j;
                ++comparisons;
            }
            f[j] = temp;
            ++swaps;
        }
        gap /= 2;
    }

    std::cout << "Shell sort comparisons: " << comparisons << "\n";
    std::cout << "Shell sort swaps: " << swaps << "\n";
}

// Heapify function for pyramid sort
void heapify(Fraction* f, int count, int root, int& comparisons, int& swaps) {
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    // Compare left child with root
    if (left < count && f[left] > f[largest]) {
        largest = left;
    }

    // Compare right child with the largest so far
    if (right < count && f[right] > f[largest]) {
        largest = right;
    }

    // If the largest is not the root, swap and continue heapifying
    if (largest != root) {
        std::swap(f[root], f[largest]);
        swaps++;
        comparisons++;

        // Recursively heapify the affected subtree
        heapify(f, count, largest, comparisons, swaps);
    }
}

// Pyramid sort function
void pyramidSort(Fraction* f, int count) {
    int comparisons = 0;
    int swaps = 0;

    // Build a max heap
    for (int i = count / 2 - 1; i >= 0; --i) {
        heapify(f, count, i, comparisons, swaps);
    }

    // Extract elements one by one from the heap
    for (int i = count - 1; i > 0; --i) {
        // Move the current root (largest element) to the end
        std::swap(f[0], f[i]);
        swaps++;

        // Call heapify on the reduced heap
        heapify(f, i, 0, comparisons, swaps);
    }

    std::cout << "Pyramid sort comparisons: " << comparisons << "\n";
    std::cout << "Pyramid sort swaps: " << swaps << "\n";
}
// Sequential search function
int sequentialSearch(const Fraction* f, int count, const Fraction& target) {
    for (int i = 0; i < count; ++i) {
        if (f[i].numerator == target.numerator && f[i].denominator == target.denominator) {
            return i;  // Found at index i
        }
    }
    return -1; // Not found
}

// Binary search function
int binarySearch(const Fraction* f, int count, const Fraction& target) {
    int left = 0, right = count - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (f[mid].numerator == target.numerator && f[mid].denominator == target.denominator) {
            return mid;  // Found at index mid
        }
        else if (f[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1; // Not found
}


// Display menu function
void displayMenu() {
    std::cout << "\nMenu:\n"
        << "1. Input data\n"
        << "2. Output original data\n"
        << "3. Sort using bubble sort\n"
        << "4. Sort using insertion sort\n"
        << "5. Sort using Shell sort\n"
        << "6. Sort using Pyramid sort\n"
        << "7. Perform sequential search\n"
        << "8. Perform binary search\n"
        << "9. Exit\n"
        << "Choose action: ";
}

// Check for valid input
bool isValidInput(int value) {
    return value >= 1 && value <= 9;
}

int main() {
    Fraction fractions[MAX_FRAGMENTS];
    Fraction originalFractions[MAX_FRAGMENTS]; // Array to hold the original data
    int count = 0;
    Fraction target;
    int index;
    while (true) {
        displayMenu();
        int choice;
        std::cin >> choice;

        if (!isValidInput(choice)) {
            std::cout << "Invalid choice. Please try again.\n";
            continue;
        }

        switch (choice) {
        case 1:
            inputFractions(fractions, MAX_FRAGMENTS, count);
            copyArray(fractions, originalFractions, count); // Save the original data
            break;
        case 2:
            std::cout << "Original array:\n";
            outputFractions(originalFractions, count);
            break;
        case 3:
            copyArray(originalFractions, fractions, count); // Restore original data for sorting
            bubbleSort(fractions, count);
            std::cout << "Sorted array after bubble sort:\n";
            outputFractions(fractions, count);
            break;
        case 4:
            copyArray(originalFractions, fractions, count); // Restore original data for sorting
            insertionSort(fractions, count);
            std::cout << "Sorted array after insertion sort:\n";
            outputFractions(fractions, count);
            break;
        case 5:
            copyArray(originalFractions, fractions, count); // Restore original data for sorting
            shellSort(fractions, count);
            std::cout << "Sorted array after Shell sort:\n";
            outputFractions(fractions, count);
            break;
        case 6:
            copyArray(originalFractions, fractions, count); // Restore original data for sorting
            pyramidSort(fractions, count);
            std::cout << "Sorted array after Pyramid sort:\n";
            outputFractions(fractions, count);
            break;
        case 7:
            
            std::cout << "Enter the fraction to search (numerator and denominator): ";
            std::cin >> target.numerator >> target.denominator;
            index = sequentialSearch(fractions, count, target);
            if (index != -1) {
                std::cout << "Fraction found at index " << index << ".\n";
            }
            else {
                std::cout << "Fraction not found.\n";
            }
            break;

        case 8:
            
            std::cout << "Enter the fraction to search (numerator and denominator): ";
            std::cin >> target.numerator >> target.denominator;
             index = binarySearch(fractions, count, target);
            if (index != -1) {
                std::cout << "Fraction found at index " << index << ".\n";
            }
            else {
                std::cout << "Fraction not found.\n";
            }
            break;

        case 9:
            exit(0);
            break;
        }
    }
}
