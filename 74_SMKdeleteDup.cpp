//how to compile: g++ -g -Wall -std=c++11  74_SMKdeleteDup.cpp -o 74_SMKdeleteDup

#include <iostream>
#include <vector>
using namespace std;
 
// Given a sorted array nums, remove the duplicates in-place
int removeDuplicates(vector<int>& nums)
{
  int k=0;
  for(int i=0; i<nums.size()-1; i++){
     if(nums[i]!=nums[i+1]){
       nums[k++] = nums[i]; 
     } 
  }
  nums[k++] = nums[nums.size()-1];
    
  nums.resize(k);  
  return nums.size();
}
 
// Given a sorted array nums, remove the duplicates in-place such that duplicates appeared at most k times and return the new length.
int removeDuplicatesK(vector<int>& nums, int k)
{
  int kk=0;
  int l=0;
  for(int i=0; i<nums.size()-1; i++){
     if(nums[i] == nums[i+1]){
      l++; 
     } 
     else if(nums[i]!=nums[i+1]){
      
       if(l<k){
         nums[kk++] = nums[i];
       } 
       l=0;
     } 
  }
  nums[kk++] = nums[nums.size()-1];
    
  nums.resize(kk);  
 
  return nums.size();
}
 
void PrintArray(const vector<int>& nums, int len)
{
  for (int i = 0; i < len; ++i)
  {
    cout << nums[i] << " ";
  } 
  cout << endl << endl;
}
 
int main()
{
  vector<int> nums = {0,0,1,1,1,1,2,3,3,3,3,3, 4, 4, 4, 4, 5, 7, 9, 11, 11};
  cout << "Original Array" << endl;
  PrintArray(nums, nums.size()); 
  
  vector<int> A(nums);
  vector<int> B(nums);
 
  cout << "Removed Duplicates from Array" << endl;
  int len = removeDuplicates(A);
  PrintArray(A, len);
 
  int k = 2;
  len = removeDuplicatesK(B, k);
  cout << "Removed Duplicates from Array where duplicates appear at most k = " << k << " times" << endl;
  PrintArray(B, len); 
}
