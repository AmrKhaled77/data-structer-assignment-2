#include <bits/stdc++.h>


using namespace std;

int minFlips(int arr[], int len, int k) {
    int flips = 0;      // Total number of flips performed
    int cwFlips = 0;    // Current window's flip effect count

    for(int i = 0; i < len; i++) {
        // If we're beyond the first k elements and a flip started k steps ago,
        // remove its effect from the current window
        if(i - k >= 0 && arr[i - k] == 2) {
            cwFlips -= 1;
        }

        // If the current bit + the number of flips affecting it is even,
        // then it must be 0, and we need to flip starting at this index
        if((arr[i] + cwFlips) % 2 == 0) {
            // If a flip starting here would exceed the array bounds, it's not possible
            if(i + k > len) {
                return -1;
            }

            flips += 1;
            cwFlips += 1;    
            arr[i] = 2; // Mark this position to indicate a flip started here
        }
    }

    return flips;
}

int main()
{
    int k;
    int len;
    cout<<"Enter the length of your array\n";
    cin >> len;
    cout<<"Enter your array elements\n";
    int *arr = new int [len];
    for(int i = 0 ; i< len ; i++)
    {
        cin>>arr[i];
    }
    cout<<"Enter the length of your subarray (k)\n";
    cin >> k;
    cout<<  minFlips(arr,len,k); 
    
}