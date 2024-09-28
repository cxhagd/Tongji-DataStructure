#include <unordered_map>
class FreqStack {
    unordered_map<int, int> freq; // Stores the frequency of elements
    unordered_map<int, stack<int>> group; // Maps frequency to a stack of elements with that frequency
    int maxfreq = 0; // Stores the maximum frequency
 
public:
    FreqStack() {
        
    }
    
    void push(int val) {
        // Increase the frequency of val and update the maximum frequency
        maxfreq = max(maxfreq, ++freq[val]);
        // Add val to the stack corresponding to its frequency
        group[freq[val]].push(val);
    }
    
    int pop() {
        // Pop the element from the stack of the current maximum frequency
        int val = group[maxfreq].top();
        group[maxfreq].pop();
        // Decrease the frequency of the element
        freq[val]--;
        // If no element is left in the current max frequency, decrease the max frequency
        if (group[maxfreq].empty()) {
            maxfreq--;
        }
        return val;
    }
};