#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

pair<int, int> cscan(int n, vector<int> RQ, int initial, int size, int move) {
    // Sorting the request array
    sort(RQ.begin(), RQ.end());

    int TotalMovement1 = 0;
    int TotalMovement2 = 0;

    // To find the index where initial head position lies
    int index = 0;
    for (int i = 0; i < n; i++) {
        if (initial < RQ[i]) {
            index = i;
            break;
        }
    }

    cout << initial << " ";
    if (move == 1) {
        // Movement towards high values
        for (int i = index; i < n; i++) {
            cout << RQ[i] << " ";
        }
        TotalMovement1 = RQ[n - 1] - initial;
        TotalMovement1 += (size - RQ[n - 1] - 1);
        initial = 0;
        for (int i = 0; i < index; i++) {
            cout << RQ[i] << " ";
            TotalMovement1 += RQ[i] - initial;
            initial = RQ[i];
        }
    } else {
        // Movement towards low values
        for (int i = index - 1; i >= 0; i--) {
            cout << RQ[i] << " ";
        }
        TotalMovement1 = initial - RQ[0];
        TotalMovement1 += (size - 1 - RQ[0]);
        initial = size - 1;
        for (int i = n - 1; i >= index; i--) {
            cout << RQ[i] << " ";
            TotalMovement1 += RQ[i] - initial;
            initial = RQ[i];
        }
    }

    // Calculate TotalMovement2 circularly
    TotalMovement2 = TotalMovement1 + size - 1; // Add total disk size to the circular movement

    return make_pair(TotalMovement1, TotalMovement2);
}

void four() {
    int n, initial, size, move;
    cout << "Enter the number of requests: ";
    cin >> n;

    vector<int> RQ(n);
    cout << "Enter the request sequence: ";
    for (int i = 0; i < n; i++) {
        cin >> RQ[i];
    }

    cout << "Enter the initial head position: ";
    cin >> initial;

    cout << "Enter the total disk size: ";
    cin >> size;

    cout << "Enter the direction of movement (1 for towards high values, 0 for towards low values): ";
    cin >> move;

    pair<int, int> movements = cscan(n, RQ, initial, size, move);
    cout << "\nTotal Head Movement with circular: " << movements.first << endl;
    cout << "Total Head Movement return: " << movements.second << endl;

    return ;
}
