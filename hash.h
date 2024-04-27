#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
      unsigned long long segmentValues[5] = {0}; // Array to store the base-36 converted values of each segment

      int segmentIndex = 4; // Start from the last segment
      for (int charIndex = static_cast<int>(k.length()) - 1; charIndex >= 0; charIndex -= 6) {
        // Generate a substring for the current segment
        std::string currentSegment("");

        for (int i = 5; i >= 0; i--) {
          if (charIndex - i >= 0) {
            currentSegment.push_back(k[charIndex - i]);
          }
        }

        // Calculate the base-36 value of the current segment
        unsigned long long segmentValue = letterDigitToNumber(currentSegment[0]);
        for (size_t pos = 1; pos < currentSegment.size(); pos++) {
            segmentValue = segmentValue * 36 + letterDigitToNumber(currentSegment[pos]);
        }
        segmentValues[segmentIndex--] = segmentValue; // Store the calculated value in the segment array
      }

      // Calculate the final hash value using the pre-defined rValues
      HASH_INDEX_T hashValue = 0;
      for (int i = 0; i < 5; i++) {
        hashValue += rValues[i] * segmentValues[i];
      }
      return hashValue;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
      if (letter >= '0' && letter <= '9') {
        return letter - '0' + 26;
      }
      else if (letter >= 'A' && letter <= 'Z') {
        return letter - 'A'; 
      } 
      else {
        return letter - 'a'; 
      }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
