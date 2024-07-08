#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void LOOK(vector<int>& arr, int head, string direction) {
    int seek_count = 0;
    int distance, cur_track;
    vector<int> left, right;
    vector<int> seek_sequence;

    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] < head)
            left.push_back(arr[i]);
        if (arr[i] > head)
            right.push_back(arr[i]);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    for (int i = 0; i < 2; i++) {
        if (direction == "left") {
            for (int j = left.size() - 1; j >= 0; j--) {
                cur_track = left[j];
                seek_sequence.push_back(cur_track);
                seek_count += abs(cur_track - head);
                head = cur_track;
            }
            direction = "right";
        }
        else if (direction == "right") {
            for (int j = 0; j < right.size(); j++) {
                cur_track = right[j];
                seek_sequence.push_back(cur_track);
                seek_count += abs(cur_track - head);
                head = cur_track;
            }
            direction = "left";
        }
    }

    cout << "Total number of seek operations = " << seek_count << endl;
    cout << "Seek Sequence is: " << " ";

    for (int i = 0; i < seek_sequence.size(); i++) {
        cout << seek_sequence[i] << " ";
    }
}

void five() {
    vector<int> arr;
    int head;
    string direction;

    int n;
    cout << "Enter the number of requests: ";
    cin >> n;
    cout << "Enter the requests: ";
    for (int i = 0; i < n; i++) {
        int request;
        cin >> request;
        arr.push_back(request);
    }

    cout << "Enter the initial head position: ";
    cin >> head;

    cout << "Enter the direction (left or right): ";
    cin >> direction;

    LOOK(arr, head, direction);

    return ;
}
