#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void SCAN(vector<int>& arr, int head, int disk_size, string direction) {
    int seek_count = 0;
    int distance, cur_track;
    vector<int> left, right;
    vector<int> seek_sequence;

    // Appending end values which has to be visited
    // before reversing the direction
    if (direction == "left")
        left.push_back(0);
    else if (direction == "right")
        right.push_back(disk_size - 1);

    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] < head)
            left.push_back(arr[i]);
        if (arr[i] > head)
            right.push_back(arr[i]);
    }

    // Sorting left and right vectors
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    // Run the while loop two times.
    // One by one scanning right and left of the head
    int run = 2;
    while (run--) {
        if (direction == "left") {
            for (int i = left.size() - 1; i >= 0; i--) {
                cur_track = left[i];
                // Appending current track to seek sequence
                seek_sequence.push_back(cur_track);

                // Calculate absolute distance
                distance = abs(cur_track - head);

                // Increase the total count
                seek_count += distance;

                // Accessed track is now the new head
                head = cur_track;
            }
            direction = "right";
        } else if (direction == "right") {
            for (int i = 0; i < right.size(); i++) {
                cur_track = right[i];
                // Appending current track to seek sequence
                seek_sequence.push_back(cur_track);

                // Calculate absolute distance
                distance = abs(cur_track - head);

                // Increase the total count
                seek_count += distance;

                // Accessed track is now new head
                head = cur_track;
            }
            direction = "left";
        }
    }

    cout << "Total number of seek operations = " << seek_count << endl;

    cout << "Seek Sequence is" << endl;
    for (int i = 0; i < seek_sequence.size(); i++) {
        cout << seek_sequence[i] << " ";
    }
}

void three() {
    int size, head, disk_size;
    string direction;

    cout << "Enter the number of requests: ";
    cin >> size;

    vector<int> arr(size);
    cout << "Enter the request sequence: ";
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    cout << "Enter the initial head position: ";
    cin >> head;

    cout << "Enter the total disk size: ";
    cin >> disk_size;

    cout << "Enter the direction of movement (left or right): ";
    cin >> direction;

    SCAN(arr, head, disk_size, direction);

    return ;
}

