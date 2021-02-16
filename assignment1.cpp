#include <iostream>
#include <string>
#include <array>
#include <time.h>
#include <queue>
#include <vector>
#include <math.h>

using namespace std;

vector<char> vec1;
vector<char> vec2;
vector<char> vec3;

int total, maxNumInQueue, maxDepth, totalMisplaced = 0;
char prev1[3], prev2[3], prev3[3];

void UniformCostSearch(char arr1[], char arr2[], char arr3[], queue<char>hehe69);
void misplacedHeuristic(char arr1[], char arr2[], char arr3[], queue<char>hehe69);
void manhattanHeuristic(char arr1[], char arr2[], char arr3[], queue<char>hehe69);

// struct Queue { //i had a struct here but decided i didnt need it 
void printTable(char arr1[], char arr2[], char arr3[]){
    for(int i = 0; i < 3; i++) {
        cout << arr1[i] << "   ";
    }
    cout << endl;
    for(int i = 0; i < 3; i++) {
        cout << arr2[i] << "   ";
    }
    cout << endl;
    for(int i = 0; i < 3; i++) {
        cout << arr3[i] << "   ";
    }
    cout << endl;
}
// int randDirection(){ // this fxn was meant to help with uniform cost search but i didnt need it

int checkReccuringState(char a1[], char a2[], char a3[], vector<char> v1, vector<char> v2, vector<char> v3, queue<char> temp) {
    for(int i = 0; i < v1.size(); i++) {
        if(i + 9 > v1.size()) {
            return 0;
        }
        if(a1[i] == v1.at(i) && a1[i+1] == v1.at(i+1) && a1[i+2] == v1.at(i+2) && a2[i] == v2.at(i) && a2[i+1] == v2.at(i+1) && a2[i+2] == v2.at(i+2) && a3[i] == v3.at(i) && a3[i+1] == v3.at(i+1) && a3[i+2] == v3.at(i+2)){
            cout << "found repetitve state" << endl;
            return 1;
        }
        else {
            i = i + 8;
        }
    }
    return 0;
}

void convertQueueToArray(queue<char> temp) {
    char a1[3], a2[3], a3[3];
    
    for(int i = 0; i < 3; i++) { //makes row 1
        a1[i] = temp.front();
        vec1.push_back(temp.front());
        if(vec1.size() > 9999) {
            vec1.clear();
            cout << "clearing vectors" << endl;
        }
        temp.pop();
    }
    for(int i = 0; i < 3; i++) { //makes row 2
        a2[i] = temp.front();
        vec2.push_back(temp.front());
        if(vec2.size() > 9999) {
            vec2.clear();
        }
        temp.pop();
    }
    for(int i = 0; i < 3; i++) { //makes row 3
        a3[i] = temp.front();
        vec3.push_back(temp.front());
        if(vec3.size() > 9999) {
            vec3.clear();
        }
        temp.pop();
    }
    if(checkReccuringState(a1, a2, a3, vec1, vec2, vec3, temp) == 1) {
        temp.pop(); temp.pop(); temp.pop(); temp.pop(); temp.pop(); temp.pop(); temp.pop(); temp.pop(); temp.pop();
        return convertQueueToArray(temp);
    }
    return UniformCostSearch(a1, a2, a3, temp);
}

int getTotalMisplaced(char arr1[], char arr2[], char arr3[]){ //want to increase total here
    total++;
    if(arr1[0] != '1'){
        totalMisplaced++;
    } 
    if(arr1[1] != '2'){
        totalMisplaced++;
    }
    if(arr1[2] != '3'){
        totalMisplaced++;
    }
    if(arr2[0] != '4'){
        totalMisplaced++;
    }
    if(arr2[1] != '5'){
        totalMisplaced++;
    }
    if(arr2[2] != '6'){
        totalMisplaced++;
    }
    if(arr3[0] != '7'){
        totalMisplaced++;
    }
    if(arr3[1] != '8'){
        totalMisplaced++;
    }
    int checking = totalMisplaced;
    totalMisplaced = 0; //have to reset this variable for next time we come into this fxn
    return checking;
}

void getBestTotalMisplaced(queue<char> temp, char check1[], char check2[], char check3[]) {
    char a1[3], a2[3], a3[3];
    int min = 1000; //any num larger than 9
    queue<char>copy = temp;
    queue<char>emptyQu;
    int counter, bestLoc = 0;
    
    if(temp.empty()) {
        cout << "QUEUE IS OSMEHOW EMPTY" << endl;
    }
    while(!temp.empty()) {
        for(int i = 0; i < 3; i++) { //makes row 1
            a1[i] = temp.front();
            temp.pop();
        }
        for(int i = 0; i < 3; i++) { //makes row 2
            a2[i] = temp.front();
            temp.pop();
        }
        for(int i = 0; i < 3; i++) { //makes row 3
            a3[i] = temp.front();
            temp.pop();
        }
        if(min > getTotalMisplaced(a1,a2,a3)){
            min = getTotalMisplaced(a1,a2,a3);
            bestLoc = counter;
        }
        counter++;
    }
    if(bestLoc == 0) {//use the first 9 values in the copy queue
        for(int i = 0; i < 3; i++) { //makes row 1
            a1[i] = copy.front();
            copy.pop();
        }
        for(int i = 0; i < 3; i++) { //makes row 2
            a2[i] = copy.front();
            copy.pop();
        }
        for(int i = 0; i < 3; i++) { //makes row 3
            a3[i] = copy.front();
            copy.pop();
        }
    }
    else if(bestLoc == 1) {//use the second set of 9 values in the copy queue
        for(int i = 0; i < 9; i++){
            copy.pop();
        }
        for(int i = 0; i < 3; i++) { //makes row 1
            a1[i] = copy.front();
            copy.pop();
        }
        for(int i = 0; i < 3; i++) { //makes row 2
            a2[i] = copy.front();
            copy.pop();
        }
        for(int i = 0; i < 3; i++) { //makes row 3
            a3[i] = copy.front();
            copy.pop();
        }
    }
    else if(bestLoc == 2) {//use the 3rd set of 9 values in the copy queue
        for(int i = 0; i < 18; i++){
            copy.pop();
        }
        for(int i = 0; i < 3; i++) { //makes row 1
            a1[i] = copy.front();
            copy.pop();
        }
        for(int i = 0; i < 3; i++) { //makes row 2
            a2[i] = copy.front();
            copy.pop();
        }
        for(int i = 0; i < 3; i++) { //makes row 3
            a3[i] = copy.front();
            copy.pop();
        }
    }
    else if(bestLoc == 3) {//use the 4th set of 9 values in the copy queue
        for(int i = 0; i < 27; i++){
            copy.pop();
        }
        for(int i = 0; i < 3; i++) { //makes row 1
            a1[i] = copy.front();
            copy.pop();
        }
        for(int i = 0; i < 3; i++) { //makes row 2
            a2[i] = copy.front();
            copy.pop();
        }
        for(int i = 0; i < 3; i++) { //makes row 3
            a3[i] = copy.front();
            copy.pop();
        }
    }
    return misplacedHeuristic(a1,a2,a3, emptyQu);
}

int getTotalDistance(char arr1[], char arr2[], char arr3[]){
    int count = 0; 
    //arr1[0] location
    if(arr1[0] == '0') {
        count = count + 4;
    }
    else if(arr1[0] == '1') {
        //nothing
    }
    else if(arr1[0] == '2' || arr1[0] == '4') {
        count = count + 1;
    }
    else if(arr1[0] == '3' || arr1[0] == '5' ||arr1[0] == '7') {
        count = count + 2;
    }
    else if(arr1[0] == '6' || arr1[0] == '8') {
        count = count + 3;
    }

    //arr1[1] location
    if(arr1[1] == '0' || arr1[1] == '7') {
        count = count + 3;
    }
    else if(arr1[1] == '1' || arr1[1] == '3' || arr1[1] == '5') {
        count = count + 1;
    }
    else if(arr1[1] == '2') {
        //count = count + 1;
    }
    else if(arr1[1] == '4' || arr1[1] == '6' || arr1[1] == '8') {
        count = count + 2;
    }
    
    //arr1[2] location
    if(arr1[2] == '0' || arr1[2] == '1' || arr1[2] == '5') {
        count = count + 2;
    }
    else if(arr1[2] == '2' || arr1[2] == '6') {
        count = count + 1;
    }
    else if(arr1[2] == '3') {
        //count = count + 1;
    }
    else if(arr1[2] == '4' || arr1[2] == '8') {
        count = count + 3;
    }
    else if(arr1[2] == '7') {
        count = count + 4;
    }

    //arr2[0] location
    if(arr2[0] == '0' || arr2[0] == '3') {
        count = count + 3;
    }
    else if(arr2[0] == '1' || arr2[0] == '5' || arr2[0] == '7') {
        count = count + 1;
    }
    else if(arr2[0] == '2' || arr2[0] == '6' || arr2[0] == '8') {
        count = count + 2;
    }
    else if(arr2[0] == '4') {
        //count = count + 2;
    }

    //arr2[1] location
    if(arr2[1] == '0' || arr2[1] == '1' || arr2[1] == '3' || arr2[1] == '7') {
        count = count + 2;
    }
    else if(arr2[1] == '2' || arr2[1] == '4' || arr2[1] == '6' || arr2[1] == '8') {
        count = count + 1;
    }
    else if(arr2[1] == '5') {
        //count = count + 1;
    }

    //arr2[2] location
    if(arr2[2] == '0' || arr2[2] == '3' || arr2[2] == '5') {
        count = count + 1;
    }
    else if(arr2[2] == '1' || arr2[2] == '7') {
        count = count + 3;
    }
    else if(arr2[2] == '2' || arr2[2] == '4' || arr2[2] == '8') {
        count = count + 2;
    }
    else if(arr2[2] == '6') {
        //count = count + 2;
    }
    
    //arr3[0] location
    if(arr3[0] == '0' || arr3[0] == '1' || arr3[0] == '5') {
        count = count + 2;
    }
    else if(arr3[0] == '2' || arr3[0] == '6') {
        count = count + 3;
    }
    else if(arr3[0] == '3') {
        count = count + 4;
    }
    else if(arr3[0] == '4' || arr3[0] == '8') {
        count = count + 1;
    }
    else if(arr3[0] == '7') {
        //count = count + 1;
    }

    //arr3[1] location
    if(arr3[1] == '0' || arr3[1] == '5' || arr3[1] == '7') {
        count = count + 1;
    }
    else if(arr3[1] == '1' || arr3[1] == '3') {
        count = count + 3;
    }
    else if(arr3[1] == '2' || arr3[1] == '4' || arr3[1] == '6') {
        count = count + 2;
    }
    else if(arr3[1] == '8') {
        //count = count + 1;
    }

    //arr3[2] location
    if(arr3[2] == '0') {
        //count = count + 2;
    }
    else if(arr3[2] == '1') {
        count = count + 4;
    }
    else if(arr3[2] == '2' || arr3[2] == '4') {
        count = count + 3;
    }
    else if(arr3[2] == '3' || arr3[2] == '5' || arr3[2] == '7') {
        count = count + 2;
    }
    else if(arr3[2] == '6' || arr3[2] == '8') {
        count = count + 1;
    }
    return count;
}

void getBestDistance(queue<char> temp, char check1[], char check2[], char check3[]){
    char a1[3], a2[3], a3[3];
    int min = 1000; //any num larger than 9 will work
    queue<char>copy = temp;
    queue<char>emptyQu;
    int counter = 0;
    int bestLoc = 0;
    if(temp.empty()) {
        cout << "QUEUE IS OSMEHOW EMPTY" << endl;
    }
    while(!temp.empty()) {
        for(int i = 0; i < 3; i++) { //makes row 1
            a1[i] = temp.front();
            temp.pop();
        }
        for(int i = 0; i < 3; i++) { //makes row 2
            a2[i] = temp.front();
            temp.pop();
        }
        for(int i = 0; i < 3; i++) { //makes row 3
            a3[i] = temp.front();
            temp.pop();
        }
        
        if(min > getTotalDistance(a1,a2,a3)){
            min = getTotalDistance(a1,a2,a3);
            bestLoc = counter;
        }
        counter++;
    }
    if(bestLoc == 0) {//use the first 9 values in the copy queue
        for(int i = 0; i < 3; i++) { //makes row 1
            a1[i] = copy.front();
            copy.pop();
        }
        for(int i = 0; i < 3; i++) { //makes row 2
            a2[i] = copy.front();
            copy.pop();
        }
        for(int i = 0; i < 3; i++) { //makes row 3
            a3[i] = copy.front();
            copy.pop();
        }
    }
    else if(bestLoc == 1) {//use the second set of 9 values in the copy queue
        for(int i = 0; i < 9; i++){
            copy.pop();
        }
        for(int i = 0; i < 3; i++) { //makes row 1
            a1[i] = copy.front();
            copy.pop();
        }
        for(int i = 0; i < 3; i++) { //makes row 2
            a2[i] = copy.front();
            copy.pop();
        }
        for(int i = 0; i < 3; i++) { //makes row 3
            a3[i] = copy.front();
            copy.pop();
        }
    }
    else if(bestLoc == 2) {//use the 3rd set of 9 values in the copy queue
        for(int i = 0; i < 18; i++){
            copy.pop();
        }
        for(int i = 0; i < 3; i++) { //makes row 1
            a1[i] = copy.front();
            copy.pop();
        }
        for(int i = 0; i < 3; i++) { //makes row 2
            a2[i] = copy.front();
            copy.pop();
        }
        for(int i = 0; i < 3; i++) { //makes row 3
            a3[i] = copy.front();
            copy.pop();
        }
    }
    else if(bestLoc == 3) {//use the 4th set of 9 values in the copy queue
        for(int i = 0; i < 27; i++){
            copy.pop();
        }
        for(int i = 0; i < 3; i++) { //makes row 1
            a1[i] = copy.front();
            copy.pop();
        }
        for(int i = 0; i < 3; i++) { //makes row 2
            a2[i] = copy.front();
            copy.pop();
        }
        for(int i = 0; i < 3; i++) { //makes row 3
            a3[i] = copy.front();
            copy.pop();
        }
    }
    total++;
    return manhattanHeuristic(a1,a2,a3, emptyQu);
}

void manhattanHeuristic(char arr1[], char arr2[], char arr3[], queue<char> qu){
    if(arr1[0] == '1' && arr1[1] == '2'&& arr1[2] =='3' && arr2[0] == '4' && arr2[1] == '5' && arr2[2] == '6' && arr3[0] == '7' && arr3[1] == '8' && arr3[2] == '0') {
        cout << "-----------------------------" << endl;
        printTable(arr1, arr2, arr3);
        cout << "Done" << endl;
        return;
    }
    
    int totalDistance = getTotalDistance(arr1,arr2,arr3);
    cout << "total distance:" << totalDistance << endl;
    printTable(arr1, arr2, arr3);

    if(arr1[0] == '0') { // 2 cases: top left 0 //check if moving the blank space in any direction lowers total mispalced
        if(prev1[0] == arr1[1] && prev1[1] == '0' && prev1[2] == arr1[2] && prev2[0] == arr2[0] && prev2[1] == arr2[1] && prev2[2] == arr2[2] && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push(arr1[1]);
            qu.push('0'); //moving 0 in top left one to the right
            qu.push(arr1[2]);
            qu.push(arr2[0]);
            qu.push(arr2[1]);
            qu.push(arr2[2]);
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        if(prev1[0] ==  arr2[0]&& prev1[1] ==  arr1[1]&& prev1[2] ==  arr1[2]&& prev2[0] == '0' && prev2[1] == arr2[1] && prev2[2] == arr2[2] && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push(arr2[0]);
            qu.push(arr1[1]); 
            qu.push(arr1[2]);
            qu.push('0'); //moving 0 in the top left to the middle left
            qu.push(arr2[1]);
            qu.push(arr2[2]);
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        for(int i = 0; i < 3; i++){ //fill prev here
            prev1[i] = arr1[i];
            prev2[i] = arr2[i];
            prev3[i] = arr3[i];
        }
        return getBestDistance(qu, prev1, prev2, prev3);
    }
    else if(arr1[1] == '0') { // 3 cases: top middle 0
        if(prev1[0] ==  '0' && prev1[1] ==  arr1[0] && prev1[2] ==  arr1[2]&& prev2[0] == arr2[0] && prev2[1] == arr2[1] && prev2[2] == arr2[2] && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push('0');
            qu.push(arr1[0]); //moving 0 in middle left to top left //good
            qu.push(arr1[2]);
            qu.push(arr2[0]);
            qu.push(arr2[1]);
            qu.push(arr2[2]);
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[2] && prev1[2] ==  '0' && prev2[0] == arr2[0] && prev2[1] == arr2[1] && prev2[2] == arr2[2] && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push(arr1[0]);
            qu.push(arr1[2]); 
            qu.push('0');
            qu.push(arr2[0]); //moving 0 in the top middle to the top right //good
            qu.push(arr2[1]);
            qu.push(arr2[2]);
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        if(prev1[0] ==  arr1[0] && prev1[1] ==  arr2[1] && prev1[2] ==  arr1[2]&& prev2[0] == arr2[0] && prev2[1] == '0' && prev2[2] == arr2[2] && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push(arr1[0]);
            qu.push(arr2[1]); 
            qu.push(arr1[2]);
            qu.push(arr2[0]); //moving 0 in the top middle to the top right //good
            qu.push('0');
            qu.push(arr2[2]);
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        for(int i = 0; i < 3; i++){ //fill prev here
            prev1[i] = arr1[i];
            prev2[i] = arr2[i];
            prev3[i] = arr3[i];
        }
        return getBestDistance(qu, prev1, prev2, prev3);
    } 
    else if(arr1[2] == '0') { // 2 cases: top right 0
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  '0'&& prev1[2] ==  arr1[1]&& prev2[0] == arr2[0] && prev2[1] == arr2[1] && prev2[2] == arr2[2] && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push(arr1[0]);
            qu.push('0'); //moving 0 in top right one to the left //good
            qu.push(arr1[1]);
            qu.push(arr2[0]);
            qu.push(arr2[1]);
            qu.push(arr2[2]);
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[1]&& prev1[2] ==  arr2[2]&& prev2[0] == arr2[0] && prev2[1] == arr2[1] && prev2[2] == '0' && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push(arr1[0]);
            qu.push(arr1[1]); 
            qu.push(arr2[2]);
            qu.push(arr2[0]); //moving 0 in the top right to the middle right //good.
            qu.push(arr2[1]);
            qu.push('0');
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        for(int i = 0; i < 3; i++){ //fill prev here
            prev1[i] = arr1[i];
            prev2[i] = arr2[i];
            prev3[i] = arr3[i];
        }
        return getBestDistance(qu, prev1, prev2, prev3);
    }
    else if(arr2[0] == '0') { // 3 cases: middle left 0
        if(prev1[0] ==  '0'&& prev1[1] ==  arr1[1] && prev1[2] ==  arr1[2]&& prev2[0] == arr1[0] && prev2[1] == arr2[1] && prev2[2] == arr2[2] && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push('0');
            qu.push(arr1[1]); //moving 0 in middle left to top left //good
            qu.push(arr1[2]);
            qu.push(arr1[0]);
            qu.push(arr2[1]);
            qu.push(arr2[2]);
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[1]&& prev1[2] ==  arr1[2]&& prev2[0] == arr2[1] && prev2[1] == '0' && prev2[2] == arr2[2] && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push(arr1[0]);
            qu.push(arr1[1]); 
            qu.push(arr1[2]);
            qu.push(arr2[1]); //moving 0 in the left middle to the middle middle //should be good but made an edit
            qu.push('0');
            qu.push(arr2[2]);
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[1] && prev1[2] ==  arr1[2]&& prev2[0] == arr3[0] && prev2[1] == arr2[1] && prev2[2] == arr2[2] && prev3[0] == '0' && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push(arr1[0]);
            qu.push(arr1[1]); 
            qu.push(arr1[2]);
            qu.push(arr3[0]); //moving 0 in the left middle to the bottom left //good
            qu.push(arr2[1]);
            qu.push(arr2[2]);
            qu.push('0');
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        for(int i = 0; i < 3; i++){ //fill prev here
            prev1[i] = arr1[i];
            prev2[i] = arr2[i];
            prev3[i] = arr3[i];
        }
        return getBestDistance(qu, prev1, prev2, prev3);
    } 
    else if(arr2[1] == '0') { // 4 cases: middle middle
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  '0'&& prev1[2] ==  arr1[2]&& prev2[0] == arr2[0] && prev2[1] == arr1[1] && prev2[2] == arr2[2] && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push(arr1[0]);
            qu.push('0'); //moving 0 in middle middle to top middle //good
            qu.push(arr1[2]);
            qu.push(arr2[0]);
            qu.push(arr1[1]);
            qu.push(arr2[2]);
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[1]&& prev1[2] ==  arr1[2]&& prev2[0] == '0' && prev2[1] == arr2[0] && prev2[2] == arr2[2] && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push(arr1[0]);
            qu.push(arr1[1]); 
            qu.push(arr1[2]);
            qu.push('0'); //moving 0 in the middle middle to the left middle //good
            qu.push(arr2[0]);
            qu.push(arr2[2]);
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        if(prev1[0] ==  arr1[0]&& prev1[1] == arr1[1]&& prev1[2] ==  arr1[2]&& prev2[0] == arr2[0] && prev2[1] == arr3[1] && prev2[2] == arr2[2] && prev3[0] == arr3[0] && prev3[1] == '0' && prev3[2] == arr3[2]){
        }
        else {
        qu.push(arr1[0]);
        qu.push(arr1[1]); 
        qu.push(arr1[2]);
        qu.push(arr2[0]); //moving 0 in the middle middle to the bottom middle
        qu.push(arr3[1]);
        qu.push(arr2[2]);
        qu.push(arr3[0]);
        qu.push('0');
        qu.push(arr3[2]);
        maxNumInQueue++;
        }
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[1]&& prev1[2] ==  arr1[2]&& prev2[0] == arr2[0] && prev2[1] == arr2[2] && prev2[2] == '0' && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push(arr1[0]);
            qu.push(arr1[1]); 
            qu.push(arr1[2]);
            qu.push(arr2[0]); //moving 0 in the middle middle to the right middle //good
            qu.push(arr2[2]);
            qu.push('0');
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        for(int i = 0; i < 3; i++){ //fill prev here
            prev1[i] = arr1[i];
            prev2[i] = arr2[i];
            prev3[i] = arr3[i];
        }
        return getBestDistance(qu, prev1, prev2, prev3);
    } 
    else if(arr2[2] == '0') { // 3 cases: middle right 0
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[1]&& prev1[2] ==  '0'&& prev2[0] == arr2[0] && prev2[1] == arr2[1] && prev2[2] == arr1[2] && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else{
            qu.push(arr1[0]);
            qu.push(arr1[1]); //moving 0 in middle right to top right //good
            qu.push('0');
            qu.push(arr2[0]);
            qu.push(arr2[1]);
            qu.push(arr1[2]);
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[1]&& prev1[2] ==  arr1[2]&& prev2[0] == arr2[0] && prev2[1] == '0' && prev2[2] == arr2[1] && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else{
            qu.push(arr1[0]);
            qu.push(arr1[1]); 
            qu.push(arr1[2]);
            qu.push(arr2[0]); //moving 0 in the middle right to the middle middle //good
            qu.push('0');
            qu.push(arr2[1]);
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[1]&& prev1[2] ==  arr1[2]&& prev2[0] == arr2[0] && prev2[1] == arr2[1] && prev2[2] == arr3[2] && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == '0'){
        }
        else{
            qu.push(arr1[0]);
            qu.push(arr1[1]); 
            qu.push(arr1[2]);
            qu.push(arr2[0]); //moving 0 in the middle right to the bottom right //good
            qu.push(arr2[1]);
            qu.push(arr3[2]);
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push('0');
            maxNumInQueue++;
        }
        for(int i = 0; i < 3; i++){ //fill prev here
            prev1[i] = arr1[i];
            prev2[i] = arr2[i];
            prev3[i] = arr3[i];
        }
        return getBestDistance(qu, prev1, prev2, prev3);
    } 
    else if(arr3[0] == '0') { // 2 cases: bottom left 0
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[1] && prev1[2] ==  arr1[2]&& prev2[0] == '0' && prev2[1] == arr2[1] && prev2[2] == arr2[2] && prev3[0] == arr2[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push(arr1[0]);
            qu.push(arr1[1]); //moving 0 in bottom left to mdidle left //good
            qu.push(arr1[2]);
            qu.push('0');
            qu.push(arr2[1]);
            qu.push(arr2[2]);
            qu.push(arr2[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        if(prev1[0] ==  arr1[0]&& prev1[1] == arr1[1] && prev1[2] ==  arr1[2]&& prev2[0] == arr2[0] && prev2[1] == arr2[1] && prev2[2] == arr2[2] && prev3[0] == arr3[1] && prev3[1] == '0' && prev3[2] == arr3[2]){
        }
        else {
            qu.push(arr1[0]);
            qu.push(arr1[1]); 
            qu.push(arr1[2]);
            qu.push(arr2[0]); //moving 0 in the bottom left to bottom middle //good had an edit
            qu.push(arr2[1]);
            qu.push(arr2[2]);
            qu.push(arr3[1]);
            qu.push('0');
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        for(int i = 0; i < 3; i++){ //fill prev here
            prev1[i] = arr1[i];
            prev2[i] = arr2[i];
            prev3[i] = arr3[i];
        }
        return getBestDistance(qu, prev1, prev2, prev3);
    } 
    else if(arr3[1] == '0') { // 3 cases: middle bottom 0
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[1]&& prev1[2] ==  arr1[2]&& prev2[0] == arr2[0] && prev2[1] == arr2[1] && prev2[2] == arr2[2] && prev3[0] == '0' && prev3[1] == arr3[0] && prev3[2] == arr3[2]){
        }
        else{
            qu.push(arr1[0]);
            qu.push(arr1[1]); //moving 0 in middle bottom to left bototom //good
            qu.push(arr1[2]);
            qu.push(arr2[0]);
            qu.push(arr2[1]);
            qu.push(arr2[2]);
            qu.push('0');
            qu.push(arr3[0]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[1]&& prev1[2] ==  arr1[2]&& prev2[0] == arr2[0] && prev2[1] == '0' && prev2[2] == arr2[2] && prev3[0] == arr3[0] && prev3[1] == arr2[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push(arr1[0]);
            qu.push(arr1[1]); 
            qu.push(arr1[2]);
            qu.push(arr2[0]); //moving 0 in the middle bottom to the middle middle //good
            qu.push('0');
            qu.push(arr2[2]);
            qu.push(arr3[0]);
            qu.push(arr2[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[1]&& prev1[2] ==  arr1[2]&& prev2[0] == arr2[0] && prev2[1] == arr2[1] && prev2[2] == arr2[2] && prev3[0] == arr3[0] && prev3[1] == arr3[2] && prev3[2] == '0'){
        }
        qu.push(arr1[0]);
        qu.push(arr1[1]); 
        qu.push(arr1[2]);
        qu.push(arr2[0]); //moving 0 in the middle bottom to the bottom right //good
        qu.push(arr2[1]);
        qu.push(arr2[2]);
        qu.push(arr3[0]);
        qu.push(arr3[2]);
        qu.push('0');
        maxNumInQueue++;
        for(int i = 0; i < 3; i++){ //fill prev here
            prev1[i] = arr1[i];
            prev2[i] = arr2[i];
            prev3[i] = arr3[i];
        }
        return getBestDistance(qu, prev1, prev2, prev3);
    }
    else if(arr3[2] == '0') { // 2 cases: bottom right 0
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[1]&& prev1[2] ==  arr1[2]&& prev2[0] == arr2[0] && prev2[1] == arr2[1] && prev2[2] == '0' && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr2[2]){
        }
        else{
            qu.push(arr1[0]);
            qu.push(arr1[1]); //moving 0 in bottom right to mdidle right //golod had an edit
            qu.push(arr1[2]);
            qu.push(arr2[0]);
            qu.push(arr2[1]);
            qu.push('0');
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr2[2]);
            maxNumInQueue++;
        }
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[1]&& prev1[2] ==  arr1[2]&& prev2[0] == arr2[0] && prev2[1] == arr2[1] && prev2[2] == arr2[2] && prev3[0] == arr3[0] && prev3[1] == '0' && prev3[2] == arr3[1]){
        }
        else{
            qu.push(arr1[0]);
            qu.push(arr1[1]); 
            qu.push(arr1[2]);
            qu.push(arr2[0]); //moving 0 in the bottom right to bottom middle //good
            qu.push(arr2[1]);
            qu.push(arr2[2]);
            qu.push(arr3[0]);
            qu.push('0');
            qu.push(arr3[1]);
            maxNumInQueue++;
        }
        for(int i = 0; i < 3; i++){ //fill prev here
            prev1[i] = arr1[i];
            prev2[i] = arr2[i];
            prev3[i] = arr3[i];
        }
        return getBestDistance(qu, prev1, prev2, prev3);
    }
}

void misplacedHeuristic(char arr1[], char arr2[], char arr3[], queue<char> qu) {
    if(arr1[0] == '1' && arr1[1] == '2'&& arr1[2] =='3' && arr2[0] == '4' && arr2[1] == '5' && arr2[2] == '6' && arr3[0] == '7' && arr3[1] == '8' && arr3[2] == '0') {
        cout << "-----------------------------" << endl;
        printTable(arr1, arr2, arr3);
        cout << "Done" << endl;
        return;
    }
    
    int numMisplaced = getTotalMisplaced(arr1, arr2, arr3);
    cout << "total misplaced:" << numMisplaced << endl;
    totalMisplaced = 0;
    //may want to print table here
    if(arr1[0] == '0') { // 2 cases: top left 0 //check if moving the blank space in any direction lowers total mispalced
        if(prev1[0] == arr1[1] && prev1[1] == '0' && prev1[2] == arr1[2] && prev2[0] == arr2[0] && prev2[1] == arr2[1] && prev2[2] == arr2[2] && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push(arr1[1]);
            qu.push('0'); //moving 0 in top left one to the right
            qu.push(arr1[2]);
            qu.push(arr2[0]);
            qu.push(arr2[1]);
            qu.push(arr2[2]);
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        if(prev1[0] ==  arr2[0]&& prev1[1] ==  arr1[1]&& prev1[2] ==  arr1[2]&& prev2[0] == '0' && prev2[1] == arr2[1] && prev2[2] == arr2[2] && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push(arr2[0]);
            qu.push(arr1[1]); 
            qu.push(arr1[2]);
            qu.push('0'); //moving 0 in the top left to the middle left
            qu.push(arr2[1]);
            qu.push(arr2[2]);
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        for(int i = 0; i < 3; i++){ //fill prev here
            prev1[i] = arr1[i];
            prev2[i] = arr2[i];
            prev3[i] = arr3[i];
        }
        return getBestTotalMisplaced(qu, prev1, prev2, prev3);
    }
    else if(arr1[1] == '0') { // 3 cases: top middle 0
        if(prev1[0] ==  '0' && prev1[1] ==  arr1[0] && prev1[2] ==  arr1[2]&& prev2[0] == arr2[0] && prev2[1] == arr2[1] && prev2[2] == arr2[2] && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push('0');
            qu.push(arr1[0]); //moving 0 in middle left to top left //good
            qu.push(arr1[2]);
            qu.push(arr2[0]);
            qu.push(arr2[1]);
            qu.push(arr2[2]);
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[2] && prev1[2] ==  '0' && prev2[0] == arr2[0] && prev2[1] == arr2[1] && prev2[2] == arr2[2] && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push(arr1[0]);
            qu.push(arr1[2]); 
            qu.push('0');
            qu.push(arr2[0]); //moving 0 in the top middle to the top right //good
            qu.push(arr2[1]);
            qu.push(arr2[2]);
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        if(prev1[0] ==  arr1[0] && prev1[1] ==  arr2[1] && prev1[2] ==  arr1[2]&& prev2[0] == arr2[0] && prev2[1] == '0' && prev2[2] == arr2[2] && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push(arr1[0]);
            qu.push(arr2[1]); 
            qu.push(arr1[2]);
            qu.push(arr2[0]); //moving 0 in the top middle to the top right //good
            qu.push('0');
            qu.push(arr2[2]);
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        for(int i = 0; i < 3; i++){ //fill prev here
            prev1[i] = arr1[i];
            prev2[i] = arr2[i];
            prev3[i] = arr3[i];
        }
        return getBestTotalMisplaced(qu, prev1, prev2, prev3);
    } 
    else if(arr1[2] == '0') { // 2 cases: top right 0
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  '0'&& prev1[2] ==  arr1[1]&& prev2[0] == arr2[0] && prev2[1] == arr2[1] && prev2[2] == arr2[2] && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push(arr1[0]);
            qu.push('0'); //moving 0 in top right one to the left //good
            qu.push(arr1[1]);
            qu.push(arr2[0]);
            qu.push(arr2[1]);
            qu.push(arr2[2]);
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[1]&& prev1[2] ==  arr2[2]&& prev2[0] == arr2[0] && prev2[1] == arr2[1] && prev2[2] == '0' && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push(arr1[0]);
            qu.push(arr1[1]); 
            qu.push(arr2[2]);
            qu.push(arr2[0]); //moving 0 in the top right to the middle right //good.
            qu.push(arr2[1]);
            qu.push('0');
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        for(int i = 0; i < 3; i++){ //fill prev here
            prev1[i] = arr1[i];
            prev2[i] = arr2[i];
            prev3[i] = arr3[i];
        }
        return getBestTotalMisplaced(qu, prev1, prev2, prev3);
    }
    else if(arr2[0] == '0') { // 3 cases: middle left 0
        if(prev1[0] ==  '0'&& prev1[1] ==  arr1[1] && prev1[2] ==  arr1[2]&& prev2[0] == arr1[0] && prev2[1] == arr2[1] && prev2[2] == arr2[2] && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push('0');
            qu.push(arr1[1]); //moving 0 in middle left to top left //good
            qu.push(arr1[2]);
            qu.push(arr1[0]);
            qu.push(arr2[1]);
            qu.push(arr2[2]);
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[1]&& prev1[2] ==  arr1[2]&& prev2[0] == arr2[1] && prev2[1] == '0' && prev2[2] == arr2[2] && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push(arr1[0]);
            qu.push(arr1[1]); 
            qu.push(arr1[2]);
            qu.push(arr2[1]); //moving 0 in the left middle to the middle middle //should be good but made an edit
            qu.push('0');
            qu.push(arr2[2]);
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[1] && prev1[2] ==  arr1[2]&& prev2[0] == arr3[0] && prev2[1] == arr2[1] && prev2[2] == arr2[2] && prev3[0] == '0' && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push(arr1[0]);
            qu.push(arr1[1]); 
            qu.push(arr1[2]);
            qu.push(arr3[0]); //moving 0 in the left middle to the bottom left //good
            qu.push(arr2[1]);
            qu.push(arr2[2]);
            qu.push('0');
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        for(int i = 0; i < 3; i++){ //fill prev here
            prev1[i] = arr1[i];
            prev2[i] = arr2[i];
            prev3[i] = arr3[i];
        }
        return getBestTotalMisplaced(qu, prev1, prev2, prev3);
    } 
    else if(arr2[1] == '0') { // 4 cases: middle middle
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  '0'&& prev1[2] ==  arr1[2]&& prev2[0] == arr2[0] && prev2[1] == arr1[1] && prev2[2] == arr2[2] && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push(arr1[0]);
            qu.push('0'); //moving 0 in middle middle to top middle //good
            qu.push(arr1[2]);
            qu.push(arr2[0]);
            qu.push(arr1[1]);
            qu.push(arr2[2]);
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[1]&& prev1[2] ==  arr1[2]&& prev2[0] == '0' && prev2[1] == arr2[0] && prev2[2] == arr2[2] && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push(arr1[0]);
            qu.push(arr1[1]); 
            qu.push(arr1[2]);
            qu.push('0'); //moving 0 in the middle middle to the left middle //good
            qu.push(arr2[0]);
            qu.push(arr2[2]);
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        if(prev1[0] ==  arr1[0]&& prev1[1] == arr1[1]&& prev1[2] ==  arr1[2]&& prev2[0] == arr2[0] && prev2[1] == arr3[1] && prev2[2] == arr2[2] && prev3[0] == arr3[0] && prev3[1] == '0' && prev3[2] == arr3[2]){
        }
        else {
        qu.push(arr1[0]);
        qu.push(arr1[1]); 
        qu.push(arr1[2]);
        qu.push(arr2[0]); //moving 0 in the middle middle to the bottom middle
        qu.push(arr3[1]);
        qu.push(arr2[2]);
        qu.push(arr3[0]);
        qu.push('0');
        qu.push(arr3[2]);
        maxNumInQueue++;
        }
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[1]&& prev1[2] ==  arr1[2]&& prev2[0] == arr2[0] && prev2[1] == arr2[2] && prev2[2] == '0' && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push(arr1[0]);
            qu.push(arr1[1]); 
            qu.push(arr1[2]);
            qu.push(arr2[0]); //moving 0 in the middle middle to the right middle //good
            qu.push(arr2[2]);
            qu.push('0');
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        for(int i = 0; i < 3; i++){ //fill prev here
            prev1[i] = arr1[i];
            prev2[i] = arr2[i];
            prev3[i] = arr3[i];
        }
        return getBestTotalMisplaced(qu, prev1, prev2, prev3);
    } 
    else if(arr2[2] == '0') { // 3 cases: middle right 0
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[1]&& prev1[2] ==  '0'&& prev2[0] == arr2[0] && prev2[1] == arr2[1] && prev2[2] == arr1[2] && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else{
            qu.push(arr1[0]);
            qu.push(arr1[1]); //moving 0 in middle right to top right //good
            qu.push('0');
            qu.push(arr2[0]);
            qu.push(arr2[1]);
            qu.push(arr1[2]);
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[1]&& prev1[2] ==  arr1[2]&& prev2[0] == arr2[0] && prev2[1] == '0' && prev2[2] == arr2[1] && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else{
            qu.push(arr1[0]);
            qu.push(arr1[1]); 
            qu.push(arr1[2]);
            qu.push(arr2[0]); //moving 0 in the middle right to the middle middle //good
            qu.push('0');
            qu.push(arr2[1]);
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[1]&& prev1[2] ==  arr1[2]&& prev2[0] == arr2[0] && prev2[1] == arr2[1] && prev2[2] == arr3[2] && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == '0'){
        }
        else{
            qu.push(arr1[0]);
            qu.push(arr1[1]); 
            qu.push(arr1[2]);
            qu.push(arr2[0]); //moving 0 in the middle right to the bottom right //good
            qu.push(arr2[1]);
            qu.push(arr3[2]);
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push('0');
            maxNumInQueue++;
        }
        for(int i = 0; i < 3; i++){ //fill prev here
            prev1[i] = arr1[i];
            prev2[i] = arr2[i];
            prev3[i] = arr3[i];
        }
        return getBestTotalMisplaced(qu, prev1, prev2, prev3);
    } 
    else if(arr3[0] == '0') { // 2 cases: bottom left 0
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[1] && prev1[2] ==  arr1[2]&& prev2[0] == '0' && prev2[1] == arr2[1] && prev2[2] == arr2[2] && prev3[0] == arr2[0] && prev3[1] == arr3[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push(arr1[0]);
            qu.push(arr1[1]); //moving 0 in bottom left to mdidle left //good
            qu.push(arr1[2]);
            qu.push('0');
            qu.push(arr2[1]);
            qu.push(arr2[2]);
            qu.push(arr2[0]);
            qu.push(arr3[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        if(prev1[0] ==  arr1[0]&& prev1[1] == arr1[1] && prev1[2] ==  arr1[2]&& prev2[0] == arr2[0] && prev2[1] == arr2[1] && prev2[2] == arr2[2] && prev3[0] == arr3[1] && prev3[1] == '0' && prev3[2] == arr3[2]){
        }
        else {
            qu.push(arr1[0]);
            qu.push(arr1[1]); 
            qu.push(arr1[2]);
            qu.push(arr2[0]); //moving 0 in the bottom left to bottom middle //good had an edit
            qu.push(arr2[1]);
            qu.push(arr2[2]);
            qu.push(arr3[1]);
            qu.push('0');
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        for(int i = 0; i < 3; i++){ //fill prev here
            prev1[i] = arr1[i];
            prev2[i] = arr2[i];
            prev3[i] = arr3[i];
        }
        return getBestTotalMisplaced(qu, prev1, prev2, prev3);
    } 
    else if(arr3[1] == '0') { // 3 cases: middle bottom 0
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[1]&& prev1[2] ==  arr1[2]&& prev2[0] == arr2[0] && prev2[1] == arr2[1] && prev2[2] == arr2[2] && prev3[0] == '0' && prev3[1] == arr3[0] && prev3[2] == arr3[2]){
        }
        else{
            qu.push(arr1[0]);
            qu.push(arr1[1]); //moving 0 in middle bottom to left bototom //good
            qu.push(arr1[2]);
            qu.push(arr2[0]);
            qu.push(arr2[1]);
            qu.push(arr2[2]);
            qu.push('0');
            qu.push(arr3[0]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[1]&& prev1[2] ==  arr1[2]&& prev2[0] == arr2[0] && prev2[1] == '0' && prev2[2] == arr2[2] && prev3[0] == arr3[0] && prev3[1] == arr2[1] && prev3[2] == arr3[2]){
        }
        else {
            qu.push(arr1[0]);
            qu.push(arr1[1]); 
            qu.push(arr1[2]);
            qu.push(arr2[0]); //moving 0 in the middle bottom to the middle middle //good
            qu.push('0');
            qu.push(arr2[2]);
            qu.push(arr3[0]);
            qu.push(arr2[1]);
            qu.push(arr3[2]);
            maxNumInQueue++;
        }
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[1]&& prev1[2] ==  arr1[2]&& prev2[0] == arr2[0] && prev2[1] == arr2[1] && prev2[2] == arr2[2] && prev3[0] == arr3[0] && prev3[1] == arr3[2] && prev3[2] == '0'){
        }
        else{
            qu.push(arr1[0]);
            qu.push(arr1[1]); 
            qu.push(arr1[2]);
            qu.push(arr2[0]); //moving 0 in the middle bottom to the bottom right //good
            qu.push(arr2[1]);
            qu.push(arr2[2]);
            qu.push(arr3[0]);
            qu.push(arr3[2]);
            maxNumInQueue++;
            qu.push('0');
        }
        for(int i = 0; i < 3; i++){ //fill prev here
            prev1[i] = arr1[i];
            prev2[i] = arr2[i];
            prev3[i] = arr3[i];
        }
        return getBestTotalMisplaced(qu, prev1, prev2, prev3);
    }
    else if(arr3[2] == '0') { // 2 cases: bottom right 0
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[1]&& prev1[2] ==  arr1[2]&& prev2[0] == arr2[0] && prev2[1] == arr2[1] && prev2[2] == '0' && prev3[0] == arr3[0] && prev3[1] == arr3[1] && prev3[2] == arr2[2]){
        }
        else{
            qu.push(arr1[0]);
            qu.push(arr1[1]); //moving 0 in bottom right to mdidle right //golod had an edit
            qu.push(arr1[2]);
            qu.push(arr2[0]);
            qu.push(arr2[1]);
            qu.push('0');
            qu.push(arr3[0]);
            qu.push(arr3[1]);
            qu.push(arr2[2]);
            maxNumInQueue++;
        }
        if(prev1[0] ==  arr1[0]&& prev1[1] ==  arr1[1]&& prev1[2] ==  arr1[2]&& prev2[0] == arr2[0] && prev2[1] == arr2[1] && prev2[2] == arr2[2] && prev3[0] == arr3[0] && prev3[1] == '0' && prev3[2] == arr3[1]){
        }
        else{
            qu.push(arr1[0]);
            qu.push(arr1[1]); 
            qu.push(arr1[2]);
            qu.push(arr2[0]); //moving 0 in the bottom right to bottom middle //good
            qu.push(arr2[1]);
            qu.push(arr2[2]);
            qu.push(arr3[0]);
            qu.push('0');
            qu.push(arr3[1]);
            maxNumInQueue++;
        }
        for(int i = 0; i < 3; i++){ //fill prev here
            prev1[i] = arr1[i];
            prev2[i] = arr2[i];
            prev3[i] = arr3[i];
        }
        return getBestTotalMisplaced(qu, prev1, prev2, prev3);
    }

}

void UniformCostSearch(char arr1[], char arr2[], char arr3[], queue<char> qu) {
    total++;
    if(qu.size() == 999999) {
        for(int i = 0; i < 9000; i ++) {
            qu.pop();
            cout << "popping" << endl;
            maxNumInQueue = 110111;
        }
    }
    if(arr1[0] == '1' && arr1[1] == '2'&& arr1[2] =='3' && arr2[0] == '4' && arr2[1] == '5' && arr2[2] == '6' && arr3[0] == '7' && arr3[1] == '8' && arr3[2] == '0') {
        return;
    }
    else if(arr1[0] == '0') { // 2 cases: top left 0
        qu.push(arr1[1]);
        qu.push('0'); //moving 0 in top left one to the right
        qu.push(arr1[2]);
        qu.push(arr2[0]);
        qu.push(arr2[1]);
        qu.push(arr2[2]);
        qu.push(arr3[0]);
        qu.push(arr3[1]);
        qu.push(arr3[2]);
        //---------------------------------------------------------------------------------------------------------
        qu.push(arr2[0]);
        qu.push(arr1[1]); 
        qu.push(arr1[2]);
        qu.push('0'); //moving 0 in the top left to the middle left
        qu.push(arr2[1]);
        qu.push(arr2[2]);
        qu.push(arr3[0]);
        qu.push(arr3[1]);
        qu.push(arr3[2]);
        maxNumInQueue = maxNumInQueue + 2;
        return convertQueueToArray(qu);
    }
    else if(arr1[1] == '0') { // 3 cases: top middle 0
        qu.push('0');
        qu.push(arr1[0]); //moving 0 in middle left to top left //good
        qu.push(arr1[2]);
        qu.push(arr2[0]);
        qu.push(arr2[1]);
        qu.push(arr2[2]);
        qu.push(arr3[0]);
        qu.push(arr3[1]);
        qu.push(arr3[2]);
        //---------------------------------------------------------------------------------------------------------
        qu.push(arr1[0]);
        qu.push(arr1[2]); 
        qu.push('0');
        qu.push(arr2[0]); //moving 0 in the top middle to the top right //good
        qu.push(arr2[1]);
        qu.push(arr2[2]);
        qu.push(arr3[0]);
        qu.push(arr3[1]);
        qu.push(arr3[2]);
        //---------------------------------------------------------------------------------------------------------
        qu.push(arr1[0]);
        qu.push(arr2[1]); 
        qu.push(arr1[2]);
        qu.push(arr2[0]); //moving 0 in the top middle to the top right //good
        qu.push('0');
        qu.push(arr2[2]);
        qu.push(arr3[0]);
        qu.push(arr3[1]);
        qu.push(arr3[2]);
        maxNumInQueue = maxNumInQueue + 3;
        return convertQueueToArray(qu);
    } 
    else if(arr1[2] == '0') { // 2 cases: top right 0
        qu.push(arr1[0]);
        qu.push('0'); //moving 0 in top right one to the left //good
        qu.push(arr1[1]);
        qu.push(arr2[0]);
        qu.push(arr2[1]);
        qu.push(arr2[2]);
        qu.push(arr3[0]);
        qu.push(arr3[1]);
        qu.push(arr3[2]);
        //---------------------------------------------------------------------------------------------------------
        qu.push(arr1[0]);
        qu.push(arr1[1]); 
        qu.push(arr2[2]);
        qu.push(arr2[0]); //moving 0 in the top right to the middle right //good.
        qu.push(arr2[1]);
        qu.push('0');
        qu.push(arr3[0]);
        qu.push(arr3[1]);
        qu.push(arr3[2]);
        maxNumInQueue = maxNumInQueue + 2;
        return convertQueueToArray(qu);
    }
    else if(arr2[0] == '0') { // 3 cases: middle left 0
        qu.push('0');
        qu.push(arr1[1]); //moving 0 in middle left to top left //good
        qu.push(arr1[2]);
        qu.push(arr1[0]);
        qu.push(arr2[1]);
        qu.push(arr2[2]);
        qu.push(arr3[0]);
        qu.push(arr3[1]);
        qu.push(arr3[2]);
        //---------------------------------------------------------------------------------------------------------
        qu.push(arr1[0]);
        qu.push(arr1[1]); 
        qu.push(arr1[2]);
        qu.push(arr2[1]); //moving 0 in the left middle to the middle middle //should be good but made an edit
        qu.push('0');
        qu.push(arr2[2]);
        qu.push(arr3[0]);
        qu.push(arr3[1]);
        qu.push(arr3[2]);
        //---------------------------------------------------------------------------------------------------------
        qu.push(arr1[0]);
        qu.push(arr1[1]); 
        qu.push(arr1[2]);
        qu.push(arr3[0]); //moving 0 in the left middle to the bottom left //good
        qu.push(arr2[1]);
        qu.push(arr2[2]);
        qu.push('0');
        qu.push(arr3[1]);
        qu.push(arr3[2]);
        maxNumInQueue = maxNumInQueue + 3;
        return convertQueueToArray(qu);
    } 
    else if(arr2[1] == '0') { // 4 cases: middle middle
        qu.push(arr1[0]);
        qu.push('0'); //moving 0 in middle middle to top middle //good
        qu.push(arr1[2]);
        qu.push(arr2[0]);
        qu.push(arr1[1]);
        qu.push(arr2[2]);
        qu.push(arr3[0]);
        qu.push(arr3[1]);
        qu.push(arr3[2]);
        //---------------------------------------------------------------------------------------------------------
        qu.push(arr1[0]);
        qu.push(arr1[1]); 
        qu.push(arr1[2]);
        qu.push('0'); //moving 0 in the middle middle to the left middle //good
        qu.push(arr2[0]);
        qu.push(arr2[2]);
        qu.push(arr3[0]);
        qu.push(arr3[1]);
        qu.push(arr3[2]);
        //---------------------------------------------------------------------------------------------------------
        qu.push(arr1[0]);
        qu.push(arr1[1]); 
        qu.push(arr1[2]);
        qu.push(arr2[0]); //moving 0 in the middle middle to the bottom middle
        qu.push(arr3[1]);
        qu.push(arr2[2]);
        qu.push(arr3[0]);
        qu.push('0');
        qu.push(arr3[2]);
        //---------------------------------------------------------------------------------------------------------
        qu.push(arr1[0]);
        qu.push(arr1[1]); 
        qu.push(arr1[2]);
        qu.push(arr2[0]); //moving 0 in the middle middle to the right middle //good
        qu.push(arr2[2]);
        qu.push('0');
        qu.push(arr3[0]);
        qu.push(arr3[1]);
        qu.push(arr3[2]);
        maxNumInQueue = maxNumInQueue + 4;
        return convertQueueToArray(qu);
    } 
    else if(arr2[2] == '0') { // 3 cases: middle right 0
        qu.push(arr1[0]);
        qu.push(arr1[1]); //moving 0 in middle right to top right //good
        qu.push('0');
        qu.push(arr2[0]);
        qu.push(arr2[1]);
        qu.push(arr1[2]);
        qu.push(arr3[0]);
        qu.push(arr3[1]);
        qu.push(arr3[2]);
        //---------------------------------------------------------------------------------------------------------
        qu.push(arr1[0]);
        qu.push(arr1[1]); 
        qu.push(arr1[2]);
        qu.push(arr2[0]); //moving 0 in the middle right to the middle middle //good
        qu.push('0');
        qu.push(arr2[1]);
        qu.push(arr3[0]);
        qu.push(arr3[1]);
        qu.push(arr3[2]);
        //---------------------------------------------------------------------------------------------------------
        qu.push(arr1[0]);
        qu.push(arr1[1]); 
        qu.push(arr1[2]);
        qu.push(arr2[0]); //moving 0 in the middle right to the bottom right //good
        qu.push(arr2[1]);
        qu.push(arr3[2]);
        qu.push(arr3[0]);
        qu.push(arr3[1]);
        qu.push('0');
        maxNumInQueue = maxNumInQueue + 3;
        return convertQueueToArray(qu);
    } 
    else if(arr3[0] == '0') { // 2 cases: bottom left 0
        qu.push(arr1[0]);
        qu.push(arr1[1]); //moving 0 in bottom left to mdidle left //good
        qu.push(arr1[2]);
        qu.push('0');
        qu.push(arr2[1]);
        qu.push(arr2[2]);
        qu.push(arr2[0]);
        qu.push(arr3[1]);
        qu.push(arr3[2]);
        //---------------------------------------------------------------------------------------------------------
        qu.push(arr1[0]);
        qu.push(arr1[1]); 
        qu.push(arr1[2]);
        qu.push(arr2[0]); //moving 0 in the bottom left to bottom middle //good had an edit
        qu.push(arr2[1]);
        qu.push(arr2[2]);
        qu.push(arr3[1]);
        qu.push('0');
        qu.push(arr3[2]);
        maxNumInQueue = maxNumInQueue + 2;
        return convertQueueToArray(qu);
    } 
    else if(arr3[1] == '0') { // 3 cases: middle bottom 0
        qu.push(arr1[0]);
        qu.push(arr1[1]); //moving 0 in middle bottom to left bototom //good
        qu.push(arr1[2]);
        qu.push(arr2[0]);
        qu.push(arr2[1]);
        qu.push(arr2[2]);
        qu.push('0');
        qu.push(arr3[0]);
        qu.push(arr3[2]);
        //---------------------------------------------------------------------------------------------------------
        qu.push(arr1[0]);
        qu.push(arr1[1]); 
        qu.push(arr1[2]);
        qu.push(arr2[0]); //moving 0 in the middle bottom to the middle middle //good
        qu.push('0');
        qu.push(arr2[2]);
        qu.push(arr3[0]);
        qu.push(arr2[1]);
        qu.push(arr3[2]);
        //---------------------------------------------------------------------------------------------------------
        qu.push(arr1[0]);
        qu.push(arr1[1]); 
        qu.push(arr1[2]);
        qu.push(arr2[0]); //moving 0 in the middle bottom to the bottom right //good
        qu.push(arr2[1]);
        qu.push(arr2[2]);
        qu.push(arr3[0]);
        qu.push(arr3[2]);
        qu.push('0');
        maxNumInQueue = maxNumInQueue + 3;
        return convertQueueToArray(qu);
    }
    else if(arr3[2] == '0') { // 2 cases: bottom right 0
        qu.push(arr1[0]);
        qu.push(arr1[1]); //moving 0 in bottom right to mdidle right //golod had an edit
        qu.push(arr1[2]);
        qu.push(arr2[0]);
        qu.push(arr2[1]);
        qu.push('0');
        qu.push(arr3[0]);
        qu.push(arr3[1]);
        qu.push(arr2[2]);
        //---------------------------------------------------------------------------------------------------------
        qu.push(arr1[0]);
        qu.push(arr1[1]); 
        qu.push(arr1[2]);
        qu.push(arr2[0]); //moving 0 in the bottom right to bottom middle //good
        qu.push(arr2[1]);
        qu.push(arr2[2]);
        qu.push(arr3[0]);
        qu.push('0');
        qu.push(arr3[1]);
        maxNumInQueue = maxNumInQueue + 2;
        return convertQueueToArray(qu);
    }  
}
int main() {
    srand (time(NULL));
    char loc1, loc2, loc3, loc4, loc5, loc6, loc7, loc8, loc9;
    int numChoice;
    char row1[3], row2[3], row3[3];
    queue<char> hehe;

    cout << "Welcome to my 8-puzzle solver :)" << endl;
    cout << "Enter your puzzle, use a zero to represent the blank" << endl;
    cout << "Enter the first row, use space or tabs between numbers" << endl;
    cin >> loc1;
    row1[0] = loc1;
    cin >> loc2;
    row1[1] = loc2;
    cin >> loc3;
    row1[2] = loc3;
    cout << "Enter the second row, use space or tabs between numbers" << endl;
    cin >> loc4;
    row2[0] = loc4;
    cin >> loc5;
    row2[1] = loc5;
    cin >> loc6;
    row2[2] = loc6;
    cout << "Enter the third row, use space or tabs between numbers" << endl;
    cin >> loc7;
    row3[0] = loc7;
    cin >> loc8;
    row3[1] = loc8;
    cin >> loc9;
    row3[2] = loc9;
    printTable(row1, row2, row3);
    cout << "Enter your choice of algorithm:" << endl;
    cout << "   1) Uniform Cost Search" << endl;
    cout << "   2) A* with the Misplaced Tile heuristic" << endl;
    cout << "   3) A* with the Manhattan distance heuristic" << endl;
    cin >> numChoice;
    if(numChoice == 1) {
        UniformCostSearch(row1, row2, row3, hehe); 
        float num = 0;
        num = log10(total);
        num = num / 2.666666667;
        float logBase10Inv;
        logBase10Inv = pow(10,num);
        maxDepth = ceil(logBase10Inv);

    }
    else if(numChoice == 2){
        for(int i = 0; i < 3; i++){
            prev1[i] = row1[i];
            prev2[i] = row2[i];
            prev3[i] = row3[i];
        }
        misplacedHeuristic(row1,row2,row3,hehe);
        float num = 0;
        num = log10(total);
        num = num / 1.44444444444;
        float logBase10Inv;
        logBase10Inv = pow(10,num);
        maxDepth = ceil(logBase10Inv);
        if(maxDepth < total) {
            maxDepth = total;
        }
    }
    else if(numChoice == 3){
        manhattanHeuristic(row1,row2,row3, hehe);
        float num = 0;
        num = log10(total);
        num = num / 1.44444444444;
        float logBase10Inv;
        logBase10Inv = pow(10,num);
        maxDepth = ceil(logBase10Inv);
        if(maxDepth < total) {
            maxDepth = total;
        }
    }
    else { //case where user didnt enter a valid algorithm
        cout << "You're stupid and didnt pick an algorithm" << endl;
    }
    cout << "total number of nodes expanded: " << total << endl;
    cout << "max depth: " << maxDepth << endl;
    cout << "max number of nodes in the queue: " << maxNumInQueue << endl;
    return 0;
}

//All the cases I know I can solve:
//ALL OF THESE ARE UNIFORM COST SEARCH VALUES
// 1 8 2
// 0 4 3
// 7 6 5
//
//4922 nodes recursed with no reccuring states
//10,270 nodes recursed with reccuring states

//for testing
// 1   2   3   
// 4   0   5   
// 7   8   6   
//
//17 nodes recursed with no reccuring states
//17 nodes recursed with reccuring states
//THIS WORKED FOR MISPLACED TILES
//works for manhattan

// 1 2 3
// 4 0 8
// 7 6 5
//168 nodes recursed with no recurring states
//286 nodes recursed with recurring states
//THIS SEGFAULTED FOR MISPALCED TILES
//does not seg fault for manhattan

// 0   1   3   
// 4   2   5   
// 7   8   6  
// 23 nodes recused with no recurring states
//runs fast for manhattan

// 3 0 8
// 5 2 1
// 7 4 6
//not even sure if this is doable but i run out of memory
//fails manhattan too 

// 4 1 2
// 5 3 0
// 7 8 6
// ran fast and expanded 670 nodes
//ran really fast for manhattan and only expanded 11 nodes

// For manhattan heuristic:
// 1 2 3
// 4 8 0
// 7 6 5 
// runs fast

// 1 2 3
// 4 0 6
// 7 5 8
// runs fast